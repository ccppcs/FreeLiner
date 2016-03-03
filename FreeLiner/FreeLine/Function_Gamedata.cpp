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

			게임 데이터 설정

*************************************/
void CFreeLineView::SetGameData(void)	// 게임 시작시 필요한 모든 데이터 초기화
{
	menu = INTRO;

	s_rect.menu_selected = 0;

	sub_menu = FALSE;

	s_rect.menu_point.x=0;
	s_rect.menu_point.y=0;
	
	SetSkillData();
	SetIntroData();

	Flag_speed=FALSE;			
	Count_speed=0;			
	A_speed=0;
	Flag_Timer_speed=FALSE;

	Flag_N_Skill=FALSE;

	Timer_Count=0;
	Timer=180;
	
	BackGround.x=0;
	BackGround.y=0;

	SetScore();

	Flag_Virtual.x=TRUE;
	Flag_Virtual.y=TRUE;
	SetWall();
	
	SetCombo();
	Flag_Timer=FALSE;

	Flag_Go=TRUE;
	Flag_How=0;
}

void CFreeLineView::SetMenuRect(CRect rect)	// 메뉴선택 사각형 데이터 초기화
{
	s_rect.menu_point.y = rect.bottom-60*(3-s_rect.menu_selected);

}
void CFreeLineView::GameExit(void)	// 게임종료
{
	PostQuitMessage(0);
}
void CFreeLineView::GameOver(void)
{
	SetGameData();
	SetHeroData();
	SetCourseData();
	SetMenuData();
	Flag_Timer=FALSE;
	PlayMusic(M_MENU_THEME);
}
void CFreeLineView::SetTimerData(void)
{
	Timer = 180;	// 5분, 초단위
	SetTimer(T_TIMER,SECOND/10,NULL);
}

void CFreeLineView::DrawTimer(CBufferDC* dc)
{
	CRect rect;
	GetClientRect(&rect);
	CString str;
	CFont font;
	dc->SetTextColor(RGB(0,0,0));
	font.CreatePointFont(205,_T("Hobo Std"));
	dc->SelectObject(&font);
	dc->SetBkMode(TRANSPARENT);
	str.Format(_T("%2d:%2d"),Timer/60,Timer%60);
	dc->DrawText(str,CRect(rect.Width()/2-20,20,rect.Width()/2+60,60),NULL);
}

void CFreeLineView::DrawScore(CBufferDC* dc)
{
	CRect rect;
	GetClientRect(&rect);
	CString str;
	CFont font;
	
	font.CreatePointFont(180,_T("양재깨비체b"));
	dc->SelectObject(&font);
	str.Format(_T("SCORE %d"),score);
	CBrush brush(RGB(0,255,0));
	dc->SetBkMode(TRANSPARENT);

	dc->SetTextColor(RGB(0,0,0));
	dc->TextOutW(rect.right-191,rect.top+71,str);	
	dc->SetTextColor(RGB(255,255,255));
	dc->TextOutW(rect.right-190,rect.top+70,str);
}

void CFreeLineView::SetScore(void)
{
	score=0;
}

void CFreeLineView::GetScore(int AddScore)
{
	if(AddScore>0)
		score+=AddScore+((Combo/3)*AddScore+Combo*500);
}

void CFreeLineView::TimeOver(void)
{
	SetTimer(T_TIMEOVER,6*SECOND,NULL);
	mode = TIMEOVER;
}

void CFreeLineView::DrawTimeOver(CBufferDC* dc)
{
	CRect rect;
	GetClientRect(&rect);
	CString str;
	str.Format(_T("Time Over"));
	CFont font;
	
	font.CreatePointFont(1000,_T("양재깨비체b"));
	dc->SelectObject(&font);
	dc->SetBkMode(TRANSPARENT);
	
	dc->SetTextColor(RGB(0,0,0));
	dc->TextOutW(rect.Width()/2-300,rect.Height()/2-200,str);
	dc->SetTextColor(RGB(255,255,255));
	dc->TextOutW(rect.Width()/2-305,rect.Height()/2-205,str);
}
