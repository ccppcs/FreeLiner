// FreeLine.h : FreeLine ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CFreeLineApp:
// �� Ŭ������ ������ ���ؼ��� FreeLine.cpp�� �����Ͻʽÿ�.
//

class CFreeLineApp : public CWinApp
{
public:
	CFreeLineApp();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CFreeLineApp theApp;