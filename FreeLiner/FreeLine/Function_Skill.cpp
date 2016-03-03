// FreeLineView.cpp : CFreeLineView 클래스의 구현
//

#include "stdafx.h"
#include "FreeLine.h"

#include "FreeLineDoc.h"
#include "FreeLineView.h"
#include "BufferDC.h"
#include "Macro.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

/*************************************

		     기술 관련 함수

**************************************/
void CFreeLineView::Update_Skill_input_data(short int level)	// 랜덤한 스킬 입력 생성및 업데이트
{
	for(short int i=0;i<(2+level);i++)
		Skill_input_data[i] = rand()%4;
}

void CFreeLineView::DrawSkill_input(CBufferDC* dc)	// 주인공 위 기술입력표 출력
{
	CDC MemDC;
	MemDC.CreateCompatibleDC(dc);
	CBitmap arrow;
	CBitmap* pOldBmp = NULL;
	arrow.LoadBitmapW(ARROW);
	pOldBmp = MemDC.SelectObject(&arrow);

	int arrow_width=23;
	int arrow_height=22;

	CString str;
	if(Hero.Flag_stat==S_SKILL)
	{
		for(int i=0;i<ARROW_MAX;i++)
		{
			if(Skill_input_data[i]!=-1)
			{
				// 입력과 미입력
				if(Skill_Draw[i]==-1)
				{
					dc->TransparentBlt(Hero.point.x-Hero.size.x+(i*20),Hero.point.y-Hero.size.y-30,
									arrow_width,arrow_height,&MemDC,
									arrow_width*(Skill_input_data[i]*2),0,
									arrow_width,arrow_height, RGB(200,0,200));
									
				}
				else
				{
					dc->TransparentBlt(Hero.point.x-Hero.size.x+(i*20),Hero.point.y-Hero.size.y-30,
									arrow_width,arrow_height,&MemDC,
									arrow_width*(Skill_input_data[i]*2+1),0,
									arrow_width,arrow_height, RGB(200,0,200));
				}
			}
		}
	}
	MemDC.SelectObject(pOldBmp);
}

void CFreeLineView::Skill_input(int input)	// 기술 한개씩 입력받아서 검사
{
	if(Skill_input_data[Skill_Count] == input)
	{
		Skill_Draw[Skill_Count] = 1;
		Skill_Count++;
		if(Skill_Count==Skill_level)
		{
			GetScore(Skill_level*1000);
			if(W_Cou!=NULL)
			{
				GetScore(W_Cou->level*5000+(W_Cou->level-1)*15000);
			}
			SetSuccess();
			StartCombo();
			KillTimer(T_SKILL);	
		}
	}
	else
	{
		SetFail();
		SetCombo();
		KillTimer(T_COMBO);
	}

}

void CFreeLineView::SetSkillData(void)	// 기술 데이터 초기화
{
	for(int i=0;i<5;i++)
	{
		Skill_input_data[i] = -1;
		Skill_Draw[i] = -1;
	}
	W_Cou = NULL;
	Skill_Count=0;
	Skill_level=-1;	
	Skill_item=-1;

	Hero.FLAG_COURSE_WAIT=FALSE;
	Flag_Action_Skill = FALSE;

	Skill_frame = 0;			
	Skill_move =0;
	Flag_Course=FALSE;
	Skill_Bar_Count=20;
}
void CFreeLineView::DrawNormalSkill(CBufferDC* dc)	// 싱글 기술 그리기
{
	CFont font;
	font.CreatePointFont(150,_T("Hobo Std"));
	dc->SelectObject(&font);
	dc->SetBkMode(TRANSPARENT);
	dc->SetTextColor(RGB(55,70,255));
	CDC MemDC;
	MemDC.CreateCompatibleDC(dc);
	CBitmap icon1,icon2,icon3;
	CBitmap* pOldBmp=NULL;
	if(Flag_N_Skill>=SKILL_1 && Hero.Flag_move==EAST)
		icon1.LoadBitmapW(S1_ON);
	else
		icon1.LoadBitmapW(S1_OFF);

	pOldBmp=MemDC.SelectObject(&icon1);
	dc->BitBlt(20,20,ICON_SIZE,ICON_SIZE,&MemDC,0,0,SRCCOPY);
	dc->DrawText(_T("1"),CRect(10,30,70,70),NULL);

	if(Flag_N_Skill>=SKILL_2 && Hero.Flag_move==EAST)
		icon2.LoadBitmapW(S2_ON);
	else
		icon2.LoadBitmapW(S2_OFF);
	MemDC.SelectObject(&icon2);
	dc->BitBlt(90,20,ICON_SIZE,ICON_SIZE,&MemDC,0,0,SRCCOPY);
	dc->DrawText(_T("2"),CRect(80,30,140,70),NULL);

	if(Flag_N_Skill>=SKILL_3 && Hero.Flag_move==EAST)
		icon3.LoadBitmapW(S3_ON);
	else
		icon3.LoadBitmapW(S3_OFF);
	MemDC.SelectObject(&icon3);
	dc->BitBlt(160,20,ICON_SIZE,ICON_SIZE,&MemDC,0,0,SRCCOPY);
	dc->DrawText(_T("3"),CRect(150,30,210,70),NULL);
	MemDC.SelectObject(pOldBmp);
}
void CFreeLineView::CheckNormalSkill(void)			// 싱글 기술 검사
{
	if(A_speed>=SKILL_3)
		Flag_N_Skill=SKILL_3;
	
	else if(A_speed>=SKILL_2)
		Flag_N_Skill=SKILL_2;

	else if(A_speed>=SKILL_1)
		Flag_N_Skill=SKILL_1;

	else
		Flag_N_Skill=FALSE;
}

void CFreeLineView::SetCombo(void)
{
	Combo=0;
	Combo_Count=0;
	Flag_Combo=FALSE;
}

void CFreeLineView::StartCombo(void)
{
	if(Flag_Combo==FALSE)
	{
		SetTimer(T_COMBO,SECOND/2,NULL);
		Combo_Count=MAX_COMBO_COUNT;
		Flag_Combo=TRUE;
	}
	else
	{
		Combo++;
		Combo_Count=MAX_COMBO_COUNT;
	}
}

void CFreeLineView::DrawBar(CBufferDC* dc)
{
	CRect rect;
	GetClientRect(&rect);

	CDC MemDC;
	BITMAP bmpInfo;
	MemDC.CreateCompatibleDC(dc);
	CBitmap bmp;
	CBitmap* pOldBmp = NULL;
	bmp.LoadBitmapW(BAR);
	bmp.GetBitmap(&bmpInfo);
	pOldBmp = MemDC.SelectObject(&bmp);

	FillBar(dc);
	dc->TransparentBlt(rect.left+10,rect.bottom-10-bmpInfo.bmHeight,
				bmpInfo.bmWidth,bmpInfo.bmHeight,&MemDC,
				0,0,
				bmpInfo.bmWidth,bmpInfo.bmHeight,RGB(200,0,200));

	MemDC.SelectObject(pOldBmp);
}

void CFreeLineView::FillBar(CBufferDC* dc)
{
	CRect rect;
	GetClientRect(&rect);
	CBrush speed(RGB(255,0,0));
	CBrush combo(RGB(255,255,0));

	//스피드바
	dc->FillRect(CRect(rect.left+12,rect.bottom-20-((BAR_HEIGHT/MAX_A_SPEED)*A_speed),
				rect.left+12+BAR_WIDTH,rect.bottom-20),&speed);
	//콤보바
	dc->FillRect(CRect(rect.left+40,rect.bottom-20-((BAR_HEIGHT/MAX_COMBO_COUNT)*Combo_Count),
				rect.left+40+BAR_WIDTH,rect.bottom-20),&combo);
}
void CFreeLineView::SetSkillAni(void)		// 기술 애니메이션 초기화
{
	Skill_Ani_Count=0;
	Skill_Ani_MAX_Count=0;
}

int CFreeLineView::PlaySkillAni(int item)	// 리소스 UID를 직접 핸들하여 애니메이션을 사용
{
	int frame;
	switch(item)
	{
	case C1:
		frame=34;					// 프레임수
		Skill_Ani_MAX_Count=190; // UID
		Skill_Ani_Count=190;
		break;
	case C2:
		frame=34;					// 프레임수
		Skill_Ani_MAX_Count=156; // UID
		Skill_Ani_Count=156;
		break;
	case C3:
		frame=25;					// 프레임수
		Skill_Ani_MAX_Count=224; // UID
		Skill_Ani_Count=224;
		break;
	case S1:
		frame=25;					// 프레임수
		Skill_Ani_MAX_Count=249; // UID
		Skill_Ani_Count=249;
		break;
	case S2:
		frame=14;					// 프레임수
		Skill_Ani_MAX_Count=274; // UID
		Skill_Ani_Count=274;
		break;
	case S3:
		frame=15;					// 프레임수
		Skill_Ani_MAX_Count=288; // UID
		Skill_Ani_Count=288;
		break;
	}
	Skill_Ani_MAX_Count+=(frame-1);
	SetTimer(T_SKILL_ANI,ANI_FRAME,NULL);
	Skill_frame = frame;
	return frame;
}

void CFreeLineView::SkillMove(int item, int frame)		// 스킬 애니메이션시 Hero 움직임
{
	CRect rect;
	GetClientRect(&rect);
	int move;
	move = GetSkillWidth(item)/frame;
	if(W_Cou!=NULL && W_Cou->item==1)
	{
		Hero.Flag_move=WEST;
	}
	else if(mode==MODE_EASY&&Hero.Flag_stat==S_SUCCESS)
	{
			switch(Hero.Flag_move)
			{
			case EAST:
				if(Hero.point.x+Hero.size.x<rect.Width()/2)
					Hero.point.x += move;
				else if(Flag_Virtual.x)
					Hero.point.x += move;
				else
					BackGround.x += move;
				Hero.virtual_point.x += move;
				break;
			}
			Skill_move+=move;
	}
}

int CFreeLineView::GetSkillWidth(int item)
{
	int width;
	switch(item)
	{
		case C1:
			width = 260;
			break;
		case C2:
		case C3:
			width = 678;
			break;
		case S1:
			width = 176;
			break;
		case S2:
		case S3:
			width = 211;
			break;
	}
	return width;
}
void CFreeLineView::DrawSkillBar(CBufferDC* dc)
{
	CRect rect;
	GetClientRect(&rect);

	CDC MemDC;
	BITMAP bmpInfo;
	MemDC.CreateCompatibleDC(dc);
	CBitmap bmp;
	CBitmap* pOldBmp = NULL;
	bmp.LoadBitmapW(BAR2);
	bmp.GetBitmap(&bmpInfo);
	pOldBmp = MemDC.SelectObject(&bmp);

	FillSkillBar(dc);
	dc->TransparentBlt(rect.right/2-BAR2_WIDTH/2,rect.bottom-10-bmpInfo.bmHeight,
				bmpInfo.bmWidth,bmpInfo.bmHeight,&MemDC,
				0,0,
				bmpInfo.bmWidth,bmpInfo.bmHeight,RGB(255,0,255));

	MemDC.SelectObject(pOldBmp);
}

void CFreeLineView::FillSkillBar(CBufferDC* dc)
{
	CRect rect;
	GetClientRect(&rect);
	CBrush brush(RGB(255,255,0));

	//기술게이지바
	dc->FillRect(CRect(rect.right/2-BAR2_WIDTH/2,rect.bottom-10,
				rect.right/2-BAR2_WIDTH/2+(BAR2_WIDTH/MAX_SKILL_COUNT)*Skill_Bar_Count,rect.bottom-10-BAR2_HEIGHT),&brush);

}