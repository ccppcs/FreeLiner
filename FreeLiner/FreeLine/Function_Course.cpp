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
/***********************************

		   장애물, 코스

************************************/



void CFreeLineView::SetCourseData(void)	// 코스 구조체 데이터 초기화
{
	//1 번 코스
	cou[0].Hurdle = CRect(1296,398,1500,453);
	cou[0].Contact_area = CRect(cou[0].Hurdle.left-80,cou[0].Hurdle.top-20,
										cou[0].Hurdle.left,cou[0].Hurdle.bottom-50);
	cou[0].item=1;
	cou[0].level = 1;
	cou[0].Direction = 1;

	//2 번 코스
	cou[1].Hurdle = CRect(2743,434,2944,485);
	cou[1].Contact_area = CRect(cou[1].Hurdle.left-80,cou[1].Hurdle.top-20,
										cou[1].Hurdle.left,cou[1].Hurdle.bottom-50);
	cou[1].item=1;
	cou[1].level = 1;
	cou[1].Direction = 1;

	//3 번 코스
	cou[2].Hurdle = CRect(2805,818,3330,906);
	cou[2].Contact_area = CRect(cou[2].Hurdle.left-80,cou[2].Hurdle.bottom-70,
										cou[2].Hurdle.left,cou[2].Hurdle.bottom-30);
	cou[2].item=2;
	cou[2].level = 2;
	cou[2].Direction = 1;

	//4 번 코스
	cou[3].Hurdle = CRect(807,1219,1341,1314);
	cou[3].Contact_area = CRect(cou[3].Hurdle.left-80,cou[3].Hurdle.bottom-70,
										cou[3].Hurdle.left,cou[3].Hurdle.bottom-30);
	cou[3].item=2;
	cou[3].level = 2;
	cou[3].Direction = 1;

	//5 번 코스
	cou[4].Hurdle = CRect(2790,2185,3118,2296);
	cou[4].Contact_area = CRect(cou[4].Hurdle.left-80,cou[4].Hurdle.bottom-70,
										cou[4].Hurdle.left,cou[4].Hurdle.bottom-30);
	cou[4].item=3;
	cou[4].level = 3;
	cou[4].Direction = 1;
}

void CFreeLineView::ContactCourse(void)	// 코스장애물 범위안에 들어왔는지 검사
{
	for(int i=0;i<COURSE_COUNT;i++)
	{
		if(Hero.virtual_point.x>=cou[i].Contact_area.left &&
			Hero.virtual_point.x<=cou[i].Contact_area.right &&
			Hero.virtual_point.y>=cou[i].Contact_area.top &&
			Hero.virtual_point.y<=cou[i].Contact_area.bottom &&
			Hero.Flag_move==cou[i].Direction
			)
		{
			if(Hero.Flag_stat==S_MOVE) {
 				SetTimer(T_CONTACT,FRAME,NULL);
 				W_Cou = &cou[i];
				Hero.FLAG_COURSE_WAIT=TRUE;
				break;

			}
		}
		else
		{
			Hero.FLAG_COURSE_WAIT=FALSE;
			W_Cou=NULL;
		}
	}
}

void CFreeLineView::Action_Skill(COURSE* W_Cou)	// 코스기술입력 시작
{

	SetTimer(T_SKILL,(2*SECOND+(W_Cou->level*200))/MAX_SKILL_COUNT,NULL);
	Update_Skill_input_data(W_Cou->level);
	Hero.Flag_stat=S_SKILL;
	Skill_level=W_Cou->level+2;
	Flag_Action_Skill = TRUE;
}
void CFreeLineView::Action_Skill(unsigned short int level)
{
	SetTimer(T_SKILL,(2*SECOND+(level*200))/MAX_SKILL_COUNT,NULL);
	Update_Skill_input_data(level);
	Hero.Flag_stat=S_SKILL;
	Skill_level=level+2;
	Flag_Action_Skill = TRUE;
}
void CFreeLineView::DrawContactCourse(CBufferDC* dc)	// 장애물 입력 표시
{
	CString str;
	str.Format(_T("SPACE"));
	CFont font;
	
	font.CreatePointFont(100,_T("양재깨비체b"));
	dc->SelectObject(&font);
	dc->SetBkMode(TRANSPARENT);
	if(W_Cou!=NULL && Hero.FLAG_COURSE_WAIT==TRUE&&
		Hero.Flag_stat==S_MOVE && A_speed>=W_Cou->level*2+1)
	{
		dc->SetTextColor(RGB(0,0,0));
		dc->DrawText(str,CRect(Hero.point.x-Hero.size.x+1,Hero.point.y-Hero.size.y-14,
										Hero.point.x-Hero.size.x+41,Hero.point.y-Hero.size.y+1),NULL);
		dc->SetTextColor(RGB(255,0,0));
		dc->DrawText(str,CRect(Hero.point.x-Hero.size.x,Hero.point.y-Hero.size.y-15,
										Hero.point.x-Hero.size.x+40,Hero.point.y-Hero.size.y),NULL);
	}
}


