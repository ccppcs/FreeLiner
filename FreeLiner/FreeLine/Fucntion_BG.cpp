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

		 배경, 메뉴 관련 함수

************************************/

void CFreeLineView::DrawBG(CBufferDC* dc)	// 배경 그리기
{
	CRect rect;
	GetClientRect(&rect);

	CDC MemDC;
	MemDC.CreateCompatibleDC(dc);
	CBitmap bmp;
	CBitmap* pOldBmp = NULL;
	bmp.LoadBitmapW(BACKGROUND);
	pOldBmp = MemDC.SelectObject(&bmp);

	dc->BitBlt(0,0,rect.Width(),rect.Height(),&MemDC,BackGround.x,BackGround.y,SRCCOPY);
	MemDC.SelectObject(pOldBmp);
}
void CFreeLineView::SetIntroData(void)
{
	Intro_alpha=0;
	Flag_Alpha=TRUE;
	Flag_Intro=TRUE;
}
void CFreeLineView::DrawIntro(CBufferDC* dc)	// 인트로 그리기
{
	CRect rect;
	GetClientRect(&rect);
	CBrush brush(RGB(0,0,0));

	dc->SelectObject(&brush);
	dc->Rectangle(rect);

	CDC MemDC;
	BITMAP bmpInfo;

	MemDC.CreateCompatibleDC(dc);
	CBitmap bmp;
	CBitmap* pOldBmp = NULL;
	if(Flag_Intro)	// 경북대 로고
		bmp.LoadBitmapW(INTRO_KNU);
	else			// 프리라인 로고
		bmp.LoadBitmapW(INTRO_LOGO);

	bmp.GetBitmap(&bmpInfo);
	pOldBmp = MemDC.SelectObject(&bmp);
	BLENDFUNCTION bf;
	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.SourceConstantAlpha = Intro_alpha;
	bf.AlphaFormat = 0;
	
	dc->AlphaBlend(0,0, rect.right, rect.bottom, &MemDC, 0, 0,
		bmpInfo.bmWidth, bmpInfo.bmHeight, bf);

	MemDC.SelectObject(pOldBmp);
	SetTimer(T_INTRO,50,NULL);
}
void CFreeLineView::SetMenuData(void)	// 메뉴 선택화면 데이터 설정
{
		CRect rect;
		GetClientRect(&rect);
		menu=MENU_SELECT;
		// 메뉴선택 사각형 값 초기화
		s_rect.menu_point.x = rect.right/2-160;
		s_rect.menu_point.y = rect.bottom-60*3;
		RedrawWindow();
		KillTimer(T_INTRO);
}

void CFreeLineView::DrawMenu(CBufferDC* dc)	// 메뉴선택 그리기
{
	CDC MemDC;
	BITMAP bmpInfo;
	MemDC.CreateCompatibleDC(dc);
	CBitmap bmp;
	CBitmap* pOldBmp=NULL;

	CRect rect;
	GetClientRect(&rect);
	CBrush bg(RGB(255,255,255));
	dc->FillRect(rect,&bg);
	bmp.LoadBitmapW(MENU_BG);
	bmp.GetBitmap(&bmpInfo);
	MemDC.SelectObject(&bmp);
	dc->StretchBlt(0,0,
		rect.right,rect.bottom/2,
		&MemDC,0,0,bmpInfo.bmWidth,bmpInfo.bmHeight,SRCCOPY);
	
	// 메뉴선택아이콘.
	bmp.DeleteObject();
	bmp.LoadBitmapW(MENU_CORSER);
	bmp.GetBitmap(&bmpInfo);
	MemDC.SelectObject(&bmp);
	dc->TransparentBlt(rect.right/2-160,s_rect.menu_point.y,
		bmpInfo.bmWidth,bmpInfo.bmHeight,
		&MemDC,0,0,bmpInfo.bmWidth,bmpInfo.bmHeight,RGB(255,255,255));
	
	bmp.DeleteObject();		// 메뉴선택아이콘 이미지 삭제.
	bmp.LoadBitmapW(MENU_MENU);
	bmp.GetBitmap(&bmpInfo);
	MemDC.SelectObject(&bmp);

	if(sub_menu==FALSE)		// 게임시작 미선택시
	{
	// 첫번째 메뉴.
		dc->TransparentBlt(rect.right/2-bmpInfo.bmWidth/2,rect.bottom-60*3,
		bmpInfo.bmWidth,60,
		&MemDC,0,0,bmpInfo.bmWidth,60,RGB(255,255,255));
	// 두번째 메뉴.
		dc->TransparentBlt(rect.right/2-bmpInfo.bmWidth/2,rect.bottom-60*2,
		bmpInfo.bmWidth,60,
		&MemDC,0,60,bmpInfo.bmWidth,60,RGB(255,255,255));
	// 세번째 메뉴.
		dc->TransparentBlt(rect.right/2-bmpInfo.bmWidth/2,rect.bottom-60,
		bmpInfo.bmWidth,60,
		&MemDC,0,120,bmpInfo.bmWidth,60,RGB(255,255,255));
	}
	else
	{
		// 첫번째 메뉴.
		dc->TransparentBlt(rect.right/2-bmpInfo.bmWidth/2,rect.bottom-60*3,
		bmpInfo.bmWidth,60,
		&MemDC,0,180,bmpInfo.bmWidth,60,RGB(255,255,255));
		// 두번째 메뉴.
		dc->TransparentBlt(rect.right/2-bmpInfo.bmWidth/2,rect.bottom-60*2,
		bmpInfo.bmWidth,60,
		&MemDC,0,240,bmpInfo.bmWidth,60,RGB(255,255,255));
	}
	
}
void CFreeLineView::DrawHow(CBufferDC* dc)
{
	CDC MemDC;
	BITMAP bmpInfo;
	MemDC.CreateCompatibleDC(dc);
	CBitmap bmp;

	CRect rect;
	GetClientRect(&rect);
	if(Flag_How==0)
	{
		bmp.LoadBitmapW(HOW_1);
		bmp.GetBitmap(&bmpInfo);
		MemDC.SelectObject(&bmp);
		dc->StretchBlt(0,0,
			rect.right,rect.bottom,
			&MemDC,0,0,bmpInfo.bmWidth,bmpInfo.bmHeight,SRCCOPY);
	}
	else if(Flag_How==1)
	{
		bmp.LoadBitmapW(HOW_2);
		bmp.GetBitmap(&bmpInfo);
		MemDC.SelectObject(&bmp);
		dc->StretchBlt(0,0,
			rect.right,rect.bottom,
			&MemDC,0,0,bmpInfo.bmWidth,bmpInfo.bmHeight,SRCCOPY);
	}
	else
	{
		bmp.LoadBitmapW(HOW_3);
		bmp.GetBitmap(&bmpInfo);
		MemDC.SelectObject(&bmp);
		dc->StretchBlt(0,0,
			rect.right,rect.bottom,
			&MemDC,0,0,bmpInfo.bmWidth,bmpInfo.bmHeight,SRCCOPY);
	}
}
// 인터럽트

void CFreeLineView::SetInterrupt(void)
{
	KillTimer(T_MAIN);
	KillTimer(T_TIMER);
	menu=INTERRUPT;

	i_rect.menu_selected = 0;

	i_rect.menu_point.x=0;
	i_rect.menu_point.y=0;
}

void CFreeLineView::DrawInterrupt(CBufferDC* dc)
{
	CDC MemDC;
	BITMAP bmpInfo;
	MemDC.CreateCompatibleDC(dc);
	CBitmap bmp;
	CBitmap* pOldBmp=NULL;


	// 비트맵 삽입.
	bmp.LoadBitmapW(INT_MENU);
	bmp.GetBitmap(&bmpInfo);
	MemDC.SelectObject(&bmp);
	CRect rect;
	GetClientRect(&rect);
	CRect Inter_Rect(rect.Width()/2-bmpInfo.bmWidth/2,rect.Height()/2-bmpInfo.bmHeight/2,
				rect.Width()/2+bmpInfo.bmWidth/2,rect.Height()/2-bmpInfo.bmHeight/2);
	// 첫번째 메뉴.
	dc->TransparentBlt(Inter_Rect.left,Inter_Rect.top,
		bmpInfo.bmWidth,60,
		&MemDC,0,0,bmpInfo.bmWidth,60,RGB(255,255,255));
	// 두번째 메뉴.
		dc->TransparentBlt(Inter_Rect.left,Inter_Rect.top+bmpInfo.bmHeight/3,
		bmpInfo.bmWidth,60,
		&MemDC,0,60,bmpInfo.bmWidth,60,RGB(255,255,255));
	// 세번째 메뉴.
		dc->TransparentBlt(Inter_Rect.left,Inter_Rect.top+bmpInfo.bmHeight*2/3,
		bmpInfo.bmWidth,60,
		&MemDC,0,120,bmpInfo.bmWidth,60,RGB(255,255,255));

	
	// 아이콘 삽입.
	bmp.DeleteObject();
	bmp.LoadBitmapW(INT_CORSER);
	bmp.GetBitmap(&bmpInfo);
	MemDC.SelectObject(&bmp);
	i_rect.menu_point.x=Inter_Rect.left-100;
	i_rect.menu_point.y=Inter_Rect.top+(i_rect.menu_selected*70);
	dc->TransparentBlt(i_rect.menu_point.x,i_rect.menu_point.y,
		bmpInfo.bmWidth,bmpInfo.bmHeight,
		&MemDC,0,0,bmpInfo.bmWidth,bmpInfo.bmHeight,RGB(255,255,255));
	
}
