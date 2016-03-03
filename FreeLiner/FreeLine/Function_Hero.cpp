#include "stdafx.h"
#include "FreeLine.h"

#include "FreeLineDoc.h"
#include "FreeLineView.h"
#include "BufferDC.h"
#include "Macro.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

/**********************************************

	           ���ΰ� ���� �Լ� 

***********************************************/

void CFreeLineView::SetHeroData(void)
{
	// ���ΰ� ������ �ʱ�ȭ
	Hero.point.x = 100;
	Hero.point.y = 100;
	Hero.size.x = 15;
	Hero.size.y = 25;
	Hero.virtual_point = Hero.point;

	Hero.Flag_move = EAST;
	Hero.Flag_ani = A_MOVE;
	Hero.Flag_stat = S_MOVE;
	Hero.FLAG_COURSE_WAIT = FALSE;

	Hero.Prev_point.x = 0;
	Hero.Prev_point.y = 0;

	Hero.next = NULL;
	Hero.prev = NULL;

	Hero.level = 3;
	Hero.Count_Ani = 0;
	
}

void CFreeLineView::MoveHero(void)	// ���ΰ� ������
{
	CRect rect;
	GetClientRect(&rect);
	if(mode==MODE_EASY&&Hero.Flag_stat!=S_SUCCESS && Flag_Course==FALSE)
	{
			switch(Hero.Flag_move)
			{
			case EAST:
				if(Hero.point.x+Hero.size.x<rect.Width()/2)
					Hero.point.x += SPEED+A_speed;
				else if(Flag_Virtual.x)
					Hero.point.x += SPEED+A_speed;
				else
					BackGround.x += SPEED+A_speed;
				Hero.virtual_point.x += SPEED+A_speed;
				break;
			case WEST:
				if(Hero.point.x+Hero.size.x>=rect.Width()/2)
					Hero.point.x -= SPEED+A_speed;
				else if(Flag_Virtual.x)
					Hero.point.x -= SPEED+A_speed;
				else
					BackGround.x -= SPEED+A_speed;
				Hero.virtual_point.x -= SPEED+A_speed;
				break;
			case NORTH:
				if(Hero.point.y-Hero.size.y>=rect.Height()/2)
					Hero.point.y -= SPEED+A_speed;
				else if(Flag_Virtual.y)
					Hero.point.y -= SPEED+A_speed;
				else
					BackGround.y -= SPEED+A_speed;
				Hero.virtual_point.y -= SPEED+A_speed;;
				break;
			case SOUTH:
				if(Hero.point.y+Hero.size.y<rect.Height()/2)
					Hero.point.y += SPEED+A_speed;
				else if(Flag_Virtual.y)
					Hero.point.y += SPEED+A_speed;
				else
					BackGround.y += SPEED+A_speed;
				Hero.virtual_point.y += SPEED+A_speed;
				break;
			}
	}
}
void CFreeLineView::DrawHero(CBufferDC* dc)	// ���ΰ� �׸���
{
	CDC MemDC;
	MemDC.CreateCompatibleDC(dc);
	CBitmap bmp;
	CBitmap* pOldBmp = NULL;
	BITMAP bmpInfo;

	UINT uID;
	switch(Hero.Flag_move)		// ���ҽ� ID�� ���� �ڵ�
	{
	case NORTH:
		uID = 152;
		break;
	case SOUTH:
		uID = 140;
		break;
	case EAST:
		uID = 148;
		break;
	case WEST:
		uID = 144;
		break;
	}
	uID= uID+Hero.Count_Ani;

	bmp.LoadBitmapW(uID);
	bmp.GetBitmap(&bmpInfo);
	Hero.size.x = bmpInfo.bmWidth/2;
	Hero.size.y = bmpInfo.bmHeight/2;
	
	pOldBmp = MemDC.SelectObject(&bmp);
	dc->TransparentBlt(Hero.point.x-Hero.size.x,Hero.point.y-Hero.size.y,
						bmpInfo.bmWidth,bmpInfo.bmHeight,&MemDC,
						0,0,bmpInfo.bmWidth,bmpInfo.bmHeight,
						RGB(255,0,255));
	MemDC.SelectObject(pOldBmp);
}
void CFreeLineView::SetFail(void)			// ��� ���� ó��
{
	PlayMusic(M_FAIL);
	Hero.Flag_stat=S_FAIL;
	SetTimer(T_FAIL,1*SECOND,NULL);
	KillTimer(T_SKILL);
}


void CFreeLineView::DrawFailAni(CBufferDC* dc)		// ���� ���ϸ��̼� ó��
{
	DrawHero(dc);
	DrawResultText(dc,FAIL);
}
void CFreeLineView::SetSuccess(void)		// ��� ����  ó��
{
	int frame;		// ������ ���� ����
	PlayMusic(M_SUCCESS);
	if(A_speed>0)
		A_speed-=1;
	if(Hero.Flag_stat==S_SKILL && W_Cou!=NULL)
		frame=PlaySkillAni(W_Cou->item);
	else
		frame=PlaySkillAni(Skill_item);

	Hero.Flag_stat=S_SUCCESS;
	SetTimer(T_SUCCESS,ANI_FRAME*frame,NULL);
	KillTimer(T_SKILL);

}
void CFreeLineView::DrawSuccessAni(CBufferDC* dc)		// ���� ���ϸ��̼� ó��
{
	if(Skill_Ani_Count!=0 && (Skill_Ani_Count<=Skill_Ani_MAX_Count) && (Hero.Flag_stat==S_SUCCESS))
	{
		CDC MemDC;
		BITMAP bmpInfo;
		MemDC.CreateCompatibleDC(dc);
		CBitmap bmp;
		CBitmap* pOldBmp = NULL;
		bmp.LoadBitmapW(Skill_Ani_Count);
		bmp.GetBitmap(&bmpInfo);
		pOldBmp = MemDC.SelectObject(&bmp);
	
		if(Skill_item>0 || W_Cou->item==1)
		{
			dc->TransparentBlt(Hero.point.x-Hero.size.x-Skill_move,Hero.point.y-bmpInfo.bmHeight/2,
							bmpInfo.bmWidth,bmpInfo.bmHeight,&MemDC,
							0,0,bmpInfo.bmWidth,bmpInfo.bmHeight,
							RGB(255,0,255));
		}
		else if(W_Cou->item==2 || W_Cou->item==3)
		{
			dc->TransparentBlt(Hero.point.x-Hero.size.x-Skill_move,Hero.point.y-bmpInfo.bmHeight/2-Hero.size.y,
							bmpInfo.bmWidth,bmpInfo.bmHeight,&MemDC,
							0,0,bmpInfo.bmWidth,bmpInfo.bmHeight,
							RGB(255,0,255));
		}

		MemDC.SelectObject(pOldBmp);
	
		DrawResultText(dc,SUCCESS);
	}
}
void CFreeLineView::DrawResultText(CBufferDC* dc, int Flag)		// ��� �������� ��� ���
{
	CFont font;
	font.CreatePointFont(180,_T("�������üb"));
	dc->SelectObject(&font);
	dc->SetBkMode(TRANSPARENT);
	
	CString str;
	if(Flag==SUCCESS)
	{
		str.Format(_T("%dCombo!!"),Combo+1);
		dc->SetTextColor(RGB(0,0,0));
		dc->DrawText(str,CRect(Hero.point.x-Hero.size.x,Hero.point.y-Hero.size.y-34,
							Hero.point.x-Hero.size.x+99,Hero.point.y-Hero.size.y),NULL);
		dc->SetTextColor(RGB(255,255,0));
	}
	else
	{
		str.Format(_T("����.."));
		dc->SetTextColor(RGB(0,0,0));
		dc->DrawText(str,CRect(Hero.point.x-Hero.size.x,Hero.point.y-Hero.size.y-34,
							Hero.point.x-Hero.size.x+99,Hero.point.y-Hero.size.y),NULL);
		dc->SetTextColor(RGB(255,15,0));
	}

	dc->DrawText(str,CRect(Hero.point.x-Hero.size.x,Hero.point.y-Hero.size.y-35,
							Hero.point.x-Hero.size.x+100,Hero.point.y-Hero.size.y),NULL);
	
	
}
