// FreeLineView.cpp : CFreeLineView 클래스의 구현
//

#include "stdafx.h"
#include "FreeLine.h"

#include "FreeLineDoc.h"
#include "FreeLineView.h"
#include "BufferDC.h"
#include "Macro.h"

#include "mmsystem.h"
#pragma comment(lib, "winmm.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CFreeLineView

IMPLEMENT_DYNCREATE(CFreeLineView, CView)

BEGIN_MESSAGE_MAP(CFreeLineView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_ERASEBKGND()
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
END_MESSAGE_MAP()

// CFreeLineView 생성/소멸

CFreeLineView::CFreeLineView()
{
	SetGameData();
	SetHeroData();
	SetCourseData();
}

CFreeLineView::~CFreeLineView()
{
}

BOOL CFreeLineView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CFreeLineView 그리기

void CFreeLineView::OnDraw(CDC* /*pDC*/)
{
	CFreeLineDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CFreeLineView 인쇄

BOOL CFreeLineView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CFreeLineView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CFreeLineView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CFreeLineView 진단

#ifdef _DEBUG
void CFreeLineView::AssertValid() const
{
	CView::AssertValid();
}

void CFreeLineView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CFreeLineDoc* CFreeLineView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFreeLineDoc)));
	return (CFreeLineDoc*)m_pDocument;
}
#endif //_DEBUG

/*********************************

	 CFreeLineView 메시지 처리기

*********************************/
void CFreeLineView::OnPaint()
{
	CBufferDC dc(this);
	// 인트로 그리기
	if(menu==INTRO)
	{
		DrawIntro(&dc);
	}
	// 메뉴선택 그리기
	else if(menu==MENU_SELECT)
	{
		DrawMenu(&dc);
	}
	else if(menu==HOW)
	{
		DrawHow(&dc);
	}
	// 게임 실행화면 그리기
	else if(menu==START)
	{
		DrawBG(&dc);		// 배경그리기
		///////////////////
		// 주인공 그리기 //
		///////////////////

		// 상태에 따른 움직임 표현
		if(Hero.Flag_stat==S_FAIL)
			DrawFailAni(&dc);
		else if(Hero.Flag_stat==S_SUCCESS)
			DrawSuccessAni(&dc);
		else
			DrawHero(&dc);		

		DrawSkill_input(&dc); // 기술 입력표 그리기
		DrawContactCourse(&dc); // 장애물 코스 범위 안에 들어왔는지
		DrawTimer(&dc);			// 타이머 그리기
		DrawNormalSkill(&dc);	// 노말 기술 그리기
		DrawScore(&dc);			// 점수 그리기
		DrawBar(&dc);		  // 속도, 콤보 바 그리기
		if(Hero.Flag_stat==S_SKILL)
			DrawSkillBar(&dc);	  // 기술 타이머 게이지바 그리기
		if(mode==TIMEOVER)
			DrawTimeOver(&dc);
	}
	else if(menu==INTERRUPT)
	{
			DrawInterrupt(&dc);	// 인터럽트
	}
}

void CFreeLineView::OnTimer(UINT_PTR nIDEvent)
{
	CRect rect;
	GetClientRect(&rect);
	switch(nIDEvent)
	{
	///////////////////////////
	//      인트로 타이머    //
	///////////////////////////
	case T_INTRO:
		if(Flag_Alpha)
		{
			if(Intro_alpha<255)
				Intro_alpha+=5;
			else
			{
				Flag_Alpha=!Flag_Alpha;
				
			}			
		}
		else
		{
			if(Intro_alpha>0)
				Intro_alpha-=5;
			else
			{
				Flag_Alpha=!Flag_Alpha;
				Flag_Intro=!Flag_Intro;
			}
		}
		if(Flag_Intro==TRUE && Intro_alpha == 0 && Flag_Alpha==TRUE)
		{
			SetMenuData();
			PlayMusic(M_MENU_THEME);
		}
		Invalidate();
		break;
////////////
// 타이머 //
////////////
	case T_TIMER:
		if(Timer>0)
		{
			Timer_Count++;
			if(Timer_Count>10)
			{
				Timer_Count=0;
				Timer--;
			}
			if(Timer==6)
			{
				PlayMusic(M_GAMEOVER);
				StopMusic(M_MAIN_THEME);
			}
		}
		else
		{
			KillTimer(T_TIMER);
			TimeOver();
		}
/****************************************
		   주인공 관련 타이머
****************************************/
	case T_MAIN:	// 메인타이머
		MoveHero();	// 주인공 움직임 표현
		CheckVirtual();	// 가상좌표 검사
		if(Hero.Flag_stat!=S_CRUSH)
			ContactHurdle(); // 장애물 체크
		if(Hero.Flag_stat==S_MOVE)	
		{
			ContactCourse();	// 장애물 코스 검사
			CheckNormalSkill();	// 노말 기술 검사
		}
		if(Count_speed>=MAX_COUNT_SPEED && A_speed <MAX_A_SPEED)	// 스피드 증가 조건
		{
			A_speed++;
			Count_speed=0;
		}
		Invalidate();
		break;
	case T_FAIL:
		KillTimer(T_FAIL);
		Hero.Flag_stat=S_MOVE;
		A_speed=A_speed/2;
		SetSkillAni();
		SetSkillData();
		break;
	case T_CRUSH:
		KillTimer(T_CRUSH);
		Hero.Flag_stat=S_MOVE;
		break;
	case T_HERO_ANI:
		Hero.Count_Ani++;
		if(Hero.Count_Ani>3)
			Hero.Count_Ani=0;
		break;
/****************************************
		   기술 관련 타이머
****************************************/
	case T_SKILL:		// 제한시간내에 기술 입력 못하면 실패처리, 기술 데이터 초기화
		if(Skill_Bar_Count>0)
			Skill_Bar_Count--;
		else
		{
			KillTimer(T_SKILL);
			SetFail();
			SetSkillData();
		}
		break;
	
	case T_CONTACT:		// 코스 범위내에 들어가면
 		Hero.FLAG_COURSE_WAIT = TRUE;	// 코스 사용 대기 중
		break;
	case T_SPEED:
		if(A_speed>0)	
			A_speed--;
		Count_speed = 0;
		break;
	case T_QW:
		if(Flag_Timer_speed==TRUE)
		{
			SetTimer(T_SPEED,3*SECOND,NULL);
			Flag_Timer_speed=FALSE;
		}
		break;
	case T_COMBO:
		Combo_Count--;
		if(Combo_Count<=0)
		{
			KillTimer(T_COMBO);
			SetCombo();
		}
		break;
// '고' 타이머 //
	case T_GO:
		KillTimer(T_GO);
		PlayMusic(M_MAIN_THEME);
		break;
	case T_SKILL_ANI:
		if(Hero.Flag_stat==S_SUCCESS)		// 성공시 애니메이션 처리를 위한 카운터 증가
		{
			if(Skill_Ani_Count>Skill_Ani_MAX_Count)
			{
				KillTimer(T_SKILL_ANI);
				SetSkillAni();
				SetSkillData();
				Hero.Flag_stat=S_MOVE;
			// 점수 증가		
			}
			else
			{
				Skill_Ani_Count++;
				if(W_Cou!=NULL)
					SkillMove(W_Cou->item,Skill_frame);
				else
					SkillMove(Skill_item,Skill_frame);
				
			}
		}
		break;
	case T_TIMEOVER:
		GameOver();
		KillTimer(T_TIMEOVER);
		break;
	}

	CView::OnTimer(nIDEvent);
}

BOOL CFreeLineView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	return true;
	//return CView::OnEraseBkgnd(pDC);
}

void CFreeLineView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	CRect rect;
	GetClientRect(&rect);
	/*******************************
	       인트로 스킵 키조작
    ********************************/
	if(menu==INTRO)
	{
		if(nChar==VK_ESCAPE)
		{
			PlayMusic(M_MENU_THEME);
			SetIntroData();
			SetMenuData();
		}
	}
	/*******************************
	       메뉴 선택시 키조작
    ********************************/
	else if(menu==MENU_SELECT)
	{
		switch(nChar)
		{
		case VK_UP:
			if(s_rect.menu_selected>0)					  // 선택 버튼이 맨 윗항목 위로 못가게 설정
			{
				PlayMusic(M_MENU_MOVE);
				s_rect.menu_selected--;
				SetMenuRect(rect);
				RedrawWindow();
			}
			break;
		case VK_DOWN:
			if(sub_menu==FALSE)		// 게임 시작 첫
			{
				PlayMusic(M_MENU_MOVE);
				if(s_rect.menu_selected<2)
				{
					s_rect.menu_selected++;
				}
				SetMenuRect(rect);
				RedrawWindow();
			}
			else											// 게임 시작 선택후 모드 선택
			{
				PlayMusic(M_MENU_MOVE);
				s_rect.menu_selected=1;
				SetMenuRect(rect);
				RedrawWindow();
			}
			break;
		case VK_SPACE:
		case VK_RETURN:
			if(sub_menu==FALSE)			// 서브 메뉴가 안떳을때
			{
				if(s_rect.menu_selected==0)	// 게임 시작 선택시
				{
					PlayMusic(M_MENU_MOVE);
					sub_menu=TRUE;
					RedrawWindow();
					break;
				}
				else if(s_rect.menu_selected==1)	// 고득점 선택시
				{
					PlayMusic(M_MENU_MOVE);
					//menu=HIGHSCORE;		//	$$$수정$$$
					//StopMusic(M_MENU_THEME);
					break;
				}
				else
				{
					PlayMusic(M_MENU_MOVE);
					menu=EXIT;
					GameExit();
					break;
				}
			}
			else
			{
				if(s_rect.menu_selected==0)		// 게임 시작
				{
					PlayMusic(M_MENU_MOVE);
					menu=START;
					mode=MODE_EASY;
					RedrawWindow();
					StopMusic(M_MENU_THEME);
					PlayMusic(M_READY);
				}
				else							// 게임설명
				{
					PlayMusic(M_MENU_MOVE);
					menu=HOW;			
					RedrawWindow();
				}
			}
		}
	}
	/*******************************
	       게임 실행시 키조작
    ********************************/
	else if(menu==START)
	{
		////////////////
		///   공용    //
		////////////////

		switch(nChar)
		{
		// 게임 시작
		case VK_SPACE:
			if(Flag_Timer==FALSE)
			{
				SetTimer(T_GO,SECOND*2,NULL); // 배경음이 2초 뒤에 나오게 하기 위해
				PlayMusic(M_GO);
				SetTimer(T_MAIN,FRAME,NULL);
				SetTimer(T_HERO_ANI,SECOND/2,NULL);
				SetTimerData();
				Flag_Timer=TRUE;
				SetOutLine();
			}
			if(W_Cou!=NULL && Hero.FLAG_COURSE_WAIT==TRUE&&
		Hero.Flag_stat==S_MOVE &&  A_speed>=W_Cou->level*2+1)	// 장애물 코스 키입력
			{
				if(W_Cou!=NULL)
					Action_Skill(W_Cou);
				Hero.FLAG_COURSE_WAIT=FALSE;
				Flag_Course=TRUE;
			}
			break;
		//인터럽트
		case VK_ESCAPE:
			if(mode!=TIMEOVER)
			{
				SetInterrupt();
				PauseMusic(M_MAIN_THEME);
				RedrawWindow();
			}
			break;
		// 기술 입력
		case VK_LEFT:
			if(Hero.Flag_stat==S_SKILL)
				Skill_input(0);
			break;
		case VK_DOWN:
			if(Hero.Flag_stat==S_SKILL)
				Skill_input(1);
			break;
		case VK_RIGHT:
			if(Hero.Flag_stat==S_SKILL)
				Skill_input(2);
			break;
		case VK_UP:
			if(Hero.Flag_stat==S_SKILL)
				Skill_input(3);
			break;
		// 속도 증가
		case 'q':
		case 'Q':
			Flag_speed=TRUE;
			KillTimer(T_QW);
			KillTimer(T_SPEED);
			break;
		case 'w':
		case 'W':
			if(Flag_speed)
			{
				Count_speed++;
				Flag_speed=FALSE;
			}
			KillTimer(T_QW);
			KillTimer(T_SPEED);
			break;
		// 노말 스킬 사용
		case '1':
			if(Flag_N_Skill>=SKILL_1 && Flag_Action_Skill == FALSE && Hero.Flag_stat==S_MOVE && Hero.Flag_move==EAST)
			{
				Skill_item=S1;
				Action_Skill(1);
			}
			break;
		case '2':
			if(Flag_N_Skill>=SKILL_2 && Flag_Action_Skill == FALSE && Hero.Flag_stat==S_MOVE && Hero.Flag_move==EAST)
			{
				Skill_item=S2;
				Action_Skill(2);
			}
			break;
		case '3':
			if(Flag_N_Skill>=SKILL_3 && Flag_Action_Skill == FALSE && Hero.Flag_stat==S_MOVE && Hero.Flag_move==EAST)
			{
				Skill_item=S3;
				Action_Skill(3);
			}
			break;
		}

		/////////////////
		//   이지 모드 //
		/////////////////
		if(mode==MODE_EASY)
		{
			switch(nChar)
			{
			case VK_UP:
				if(Hero.Flag_stat==S_MOVE)
					Hero.Flag_move= NORTH;
				break;
			case VK_DOWN:
				if(Hero.Flag_stat==S_MOVE)
					Hero.Flag_move= SOUTH;
				break;
			case VK_LEFT:
				if(Hero.Flag_stat==S_MOVE)
					Hero.Flag_move= WEST;
				break;
			case VK_RIGHT:
				if(Hero.Flag_stat==S_MOVE)
					Hero.Flag_move= EAST;
				break;

			}
		}
	}
	/*******************************
	       게임 설명시 키조작
	********************************/
	else if(menu==HOW)
	{
		switch(nChar)
		{
			case VK_LEFT:
				if(Flag_How>0)
					Flag_How--;
				break;
			case VK_RIGHT:
				if(Flag_How<=3)
					Flag_How++;
				if(Flag_How==3)
					GameOver();
				break;
			case VK_ESCAPE:
				GameOver();
				break;
		}
		Invalidate();
	}
	/*******************************
	       인터럽트시 키조작
	********************************/
	else if(menu==INTERRUPT)
	{
		switch(nChar)
		{
		case VK_ESCAPE:
			menu=START;
			SetTimer(T_TIMER,SECOND/10,NULL);
			SetTimer(T_MAIN,FRAME,NULL);
			ResumeMusic(M_MAIN_THEME);
			break;
		case VK_UP:
			if(i_rect.menu_selected>0)
			{
				i_rect.menu_selected--;
				PlayMusic(M_MENU_MOVE);
			}
			Invalidate();
			break;
		case VK_DOWN:
			if(i_rect.menu_selected<2)
			{
				i_rect.menu_selected++;
				PlayMusic(M_MENU_MOVE);
			}
			Invalidate();
			break;
		case VK_RETURN:
		case VK_SPACE:
			if(i_rect.menu_selected==0)				// 계속 하기
			{
				ResumeMusic(M_MAIN_THEME);
				menu=START;
				SetTimer(T_TIMER,SECOND/10,NULL);
				SetTimer(T_MAIN,FRAME,NULL);
			}
			else if(i_rect.menu_selected==1)		// 시작메뉴
			{
				GameOver();
			}
			else									// 게임종료
			{
				GameExit();
			}
			break;
		}
	}
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CFreeLineView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if(menu==START)			// 게임 실행시
	{
	

		switch(nChar)
		{
		case 'q':
		case 'Q':
		case 'w':
		case 'W':
			SetTimer(T_QW,2*SECOND,NULL);
			Flag_Timer_speed=TRUE;
			break;

		}
	}

	CView::OnKeyUp(nChar, nRepCnt, nFlags);
}


