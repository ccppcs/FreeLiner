// FreeLineDoc.cpp : CFreeLineDoc Ŭ������ ����
//

#include "stdafx.h"
#include "FreeLine.h"

#include "FreeLineDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CFreeLineDoc

IMPLEMENT_DYNCREATE(CFreeLineDoc, CDocument)

BEGIN_MESSAGE_MAP(CFreeLineDoc, CDocument)
END_MESSAGE_MAP()


// CFreeLineDoc ����/�Ҹ�

CFreeLineDoc::CFreeLineDoc()
{
	// TODO: ���⿡ ��ȸ�� ���� �ڵ带 �߰��մϴ�.

}

CFreeLineDoc::~CFreeLineDoc()
{
}

BOOL CFreeLineDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: ���⿡ ���ʱ�ȭ �ڵ带 �߰��մϴ�.
	// SDI ������ �� ������ �ٽ� ����մϴ�.

	return TRUE;
}




// CFreeLineDoc serialization

void CFreeLineDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	}
	else
	{
		// TODO: ���⿡ �ε� �ڵ带 �߰��մϴ�.
	}
}


// CFreeLineDoc ����

#ifdef _DEBUG
void CFreeLineDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CFreeLineDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CFreeLineDoc ���
