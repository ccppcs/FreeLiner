// FreeLineView.cpp : CFreeLineView Ŭ������ ����
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
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_ERASEBKGND()
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
END_MESSAGE_MAP()

// CFreeLineView ����/�Ҹ�

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
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CFreeLineView �׸���

void CFreeLineView::OnDraw(CDC* /*pDC*/)
{
	CFreeLineDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
}


// CFreeLineView �μ�

BOOL CFreeLineView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CFreeLineView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CFreeLineView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}


// CFreeLineView ����

#ifdef _DEBUG
void CFreeLineView::AssertValid() const
{
	CView::AssertValid();
}

void CFreeLineView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CFreeLineDoc* CFreeLineView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFreeLineDoc)));
	return (CFreeLineDoc*)m_pDocument;
}
#endif //_DEBUG

/*********************************

	 CFreeLineView �޽��� ó����

*********************************/
void CFreeLineView::OnPaint()
{
	CBufferDC dc(this);
	// ��Ʈ�� �׸���
	if(menu==INTRO)
	{
		DrawIntro(&dc);
	}
	// �޴����� �׸���
	else if(menu==MENU_SELECT)
	{
		DrawMenu(&dc);
	}
	else if(menu==HOW)
	{
		DrawHow(&dc);
	}
	// ���� ����ȭ�� �׸���
	else if(menu==START)
	{
		DrawBG(&dc);		// ���׸���
		///////////////////
		// ���ΰ� �׸��� //
		///////////////////

		// ���¿� ���� ������ ǥ��
		if(Hero.Flag_stat==S_FAIL)
			DrawFailAni(&dc);
		else if(Hero.Flag_stat==S_SUCCESS)
			DrawSuccessAni(&dc);
		else
			DrawHero(&dc);		

		DrawSkill_input(&dc); // ��� �Է�ǥ �׸���
		DrawContactCourse(&dc); // ��ֹ� �ڽ� ���� �ȿ� ���Դ���
		DrawTimer(&dc);			// Ÿ�̸� �׸���
		DrawNormalSkill(&dc);	// �븻 ��� �׸���
		DrawScore(&dc);			// ���� �׸���
		DrawBar(&dc);		  // �ӵ�, �޺� �� �׸���
		if(Hero.Flag_stat==S_SKILL)
			DrawSkillBar(&dc);	  // ��� Ÿ�̸� �������� �׸���
		if(mode==TIMEOVER)
			DrawTimeOver(&dc);
	}
	else if(menu==INTERRUPT)
	{
			DrawInterrupt(&dc);	// ���ͷ�Ʈ
	}
}

void CFreeLineView::OnTimer(UINT_PTR nIDEvent)
{
	CRect rect;
	GetClientRect(&rect);
	switch(nIDEvent)
	{
	///////////////////////////
	//      ��Ʈ�� Ÿ�̸�    //
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
// Ÿ�̸� //
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
		   ���ΰ� ���� Ÿ�̸�
****************************************/
	case T_MAIN:	// ����Ÿ�̸�
		MoveHero();	// ���ΰ� ������ ǥ��
		CheckVirtual();	// ������ǥ �˻�
		if(Hero.Flag_stat!=S_CRUSH)
			ContactHurdle(); // ��ֹ� üũ
		if(Hero.Flag_stat==S_MOVE)	
		{
			ContactCourse();	// ��ֹ� �ڽ� �˻�
			CheckNormalSkill();	// �븻 ��� �˻�
		}
		if(Count_speed>=MAX_COUNT_SPEED && A_speed <MAX_A_SPEED)	// ���ǵ� ���� ����
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
		   ��� ���� Ÿ�̸�
****************************************/
	case T_SKILL:		// ���ѽð����� ��� �Է� ���ϸ� ����ó��, ��� ������ �ʱ�ȭ
		if(Skill_Bar_Count>0)
			Skill_Bar_Count--;
		else
		{
			KillTimer(T_SKILL);
			SetFail();
			SetSkillData();
		}
		break;
	
	case T_CONTACT:		// �ڽ� �������� ����
 		Hero.FLAG_COURSE_WAIT = TRUE;	// �ڽ� ��� ��� ��
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
// '��' Ÿ�̸� //
	case T_GO:
		KillTimer(T_GO);
		PlayMusic(M_MAIN_THEME);
		break;
	case T_SKILL_ANI:
		if(Hero.Flag_stat==S_SUCCESS)		// ������ �ִϸ��̼� ó���� ���� ī���� ����
		{
			if(Skill_Ani_Count>Skill_Ani_MAX_Count)
			{
				KillTimer(T_SKILL_ANI);
				SetSkillAni();
				SetSkillData();
				Hero.Flag_stat=S_MOVE;
			// ���� ����		
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
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	return true;
	//return CView::OnEraseBkgnd(pDC);
}

void CFreeLineView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	CRect rect;
	GetClientRect(&rect);
	/*******************************
	       ��Ʈ�� ��ŵ Ű����
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
	       �޴� ���ý� Ű����
    ********************************/
	else if(menu==MENU_SELECT)
	{
		switch(nChar)
		{
		case VK_UP:
			if(s_rect.menu_selected>0)					  // ���� ��ư�� �� ���׸� ���� ������ ����
			{
				PlayMusic(M_MENU_MOVE);
				s_rect.menu_selected--;
				SetMenuRect(rect);
				RedrawWindow();
			}
			break;
		case VK_DOWN:
			if(sub_menu==FALSE)		// ���� ���� ù
			{
				PlayMusic(M_MENU_MOVE);
				if(s_rect.menu_selected<2)
				{
					s_rect.menu_selected++;
				}
				SetMenuRect(rect);
				RedrawWindow();
			}
			else											// ���� ���� ������ ��� ����
			{
				PlayMusic(M_MENU_MOVE);
				s_rect.menu_selected=1;
				SetMenuRect(rect);
				RedrawWindow();
			}
			break;
		case VK_SPACE:
		case VK_RETURN:
			if(sub_menu==FALSE)			// ���� �޴��� �ȶ�����
			{
				if(s_rect.menu_selected==0)	// ���� ���� ���ý�
				{
					PlayMusic(M_MENU_MOVE);
					sub_menu=TRUE;
					RedrawWindow();
					break;
				}
				else if(s_rect.menu_selected==1)	// ����� ���ý�
				{
					PlayMusic(M_MENU_MOVE);
					//menu=HIGHSCORE;		//	$$$����$$$
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
				if(s_rect.menu_selected==0)		// ���� ����
				{
					PlayMusic(M_MENU_MOVE);
					menu=START;
					mode=MODE_EASY;
					RedrawWindow();
					StopMusic(M_MENU_THEME);
					PlayMusic(M_READY);
				}
				else							// ���Ӽ���
				{
					PlayMusic(M_MENU_MOVE);
					menu=HOW;			
					RedrawWindow();
				}
			}
		}
	}
	/*******************************
	       ���� ����� Ű����
    ********************************/
	else if(menu==START)
	{
		////////////////
		///   ����    //
		////////////////

		switch(nChar)
		{
		// ���� ����
		case VK_SPACE:
			if(Flag_Timer==FALSE)
			{
				SetTimer(T_GO,SECOND*2,NULL); // ������� 2�� �ڿ� ������ �ϱ� ����
				PlayMusic(M_GO);
				SetTimer(T_MAIN,FRAME,NULL);
				SetTimer(T_HERO_ANI,SECOND/2,NULL);
				SetTimerData();
				Flag_Timer=TRUE;
				SetOutLine();
			}
			if(W_Cou!=NULL && Hero.FLAG_COURSE_WAIT==TRUE&&
		Hero.Flag_stat==S_MOVE &&  A_speed>=W_Cou->level*2+1)	// ��ֹ� �ڽ� Ű�Է�
			{
				if(W_Cou!=NULL)
					Action_Skill(W_Cou);
				Hero.FLAG_COURSE_WAIT=FALSE;
				Flag_Course=TRUE;
			}
			break;
		//���ͷ�Ʈ
		case VK_ESCAPE:
			if(mode!=TIMEOVER)
			{
				SetInterrupt();
				PauseMusic(M_MAIN_THEME);
				RedrawWindow();
			}
			break;
		// ��� �Է�
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
		// �ӵ� ����
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
		// �븻 ��ų ���
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
		//   ���� ��� //
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
	       ���� ����� Ű����
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
	       ���ͷ�Ʈ�� Ű����
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
			if(i_rect.menu_selected==0)				// ��� �ϱ�
			{
				ResumeMusic(M_MAIN_THEME);
				menu=START;
				SetTimer(T_TIMER,SECOND/10,NULL);
				SetTimer(T_MAIN,FRAME,NULL);
			}
			else if(i_rect.menu_selected==1)		// ���۸޴�
			{
				GameOver();
			}
			else									// ��������
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
	if(menu==START)			// ���� �����
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


