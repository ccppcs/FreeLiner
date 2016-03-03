// FreeLineView.cpp : CFreeLineView 클래스의 구현
//

#include "stdafx.h"
#include "FreeLine.h"

#include "FreeLineDoc.h"
#include "FreeLineView.h"
#include "Macro.h"
#include <mmsystem.h>

void CFreeLineView::PlayMusic(LPCWSTR Music_Path)
{
	wchar_t szCommand[256], szReturnStr[256];            
	wsprintf(szCommand, _T("open %s alias mydev_%s"),Music_Path,Music_Path);		//mydev 생성,시작
	mciSendString(szCommand, szReturnStr, sizeof(szReturnStr), NULL);
	wsprintf(szCommand, _T("play mydev_%s from 0"),Music_Path);
	mciSendString(szCommand, szReturnStr, sizeof(szReturnStr), NULL);	// 시작
}

void CFreeLineView::PauseMusic(LPCWSTR Music_Path)
{
	wchar_t szCommand[256];
	wsprintf(szCommand, _T("pause mydev_%s"),Music_Path);
	mciSendString(szCommand, NULL, NULL, NULL);  // 일시정지
}

void CFreeLineView::ResumeMusic(LPCWSTR Music_Path)
{
	wchar_t szCommand[256];
	wsprintf(szCommand, _T("resume mydev_%s"),Music_Path);
	mciSendString(szCommand, NULL, NULL, NULL);  // 재시작
}

void CFreeLineView::StopMusic(LPCWSTR Music_Path)
{
	wchar_t szCommand[256];
	wsprintf(szCommand, _T("stop mydev_%s"),Music_Path);
	mciSendString(szCommand, NULL, NULL, NULL);  // 정지
}
