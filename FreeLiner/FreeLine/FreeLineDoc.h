// FreeLineDoc.h : CFreeLineDoc Ŭ������ �������̽�
//


#pragma once


class CFreeLineDoc : public CDocument
{
protected: // serialization������ ��������ϴ�.
	CFreeLineDoc();
	DECLARE_DYNCREATE(CFreeLineDoc)

// Ư���Դϴ�.
public:

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// �����Դϴ�.
public:
	virtual ~CFreeLineDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
};


