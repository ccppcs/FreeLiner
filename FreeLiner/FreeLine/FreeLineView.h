// FreeLineView.h : CFreeLineView Ŭ������ �������̽�
//
#include "BufferDC.h"
#include "Macro.h"
#pragma once


class CFreeLineView : public CView
{
protected: // serialization������ ��������ϴ�.
	CFreeLineView();
	DECLARE_DYNCREATE(CFreeLineView)

// Ư���Դϴ�.
public:
	CFreeLineDoc* GetDocument() const;

// �۾��Դϴ�.
public:
	/*******************************************
			     ���� ���� ����
    *******************************************/
	short int menu;	// �޴�����
	short int mode;	// ������
	BOOL sub_menu; // ����޴� ����
	typedef struct S_RECT{		
		CPoint menu_point;			// �޴� ���� ��ư ��ġ
		short int menu_selected;	// �޴� ���� ��ư �÷���
	}S_RECT;
	S_RECT s_rect,i_rect;

	int Intro_alpha;				// ��Ʈ�� ���İ�
	BOOL Flag_Intro;				// ��Ʈ�� �׸� �÷���
	BOOL Flag_Alpha;				// ��Ʈ�� ���İ� �÷���
	unsigned short int Timer;		// Ÿ�̸� �������̽� ��
	unsigned short int Timer_Count;	// ���ͷ�Ʈ ���� ������ Ÿ�̸� ī��Ʈ
	BOOL Flag_Timer;				// Ÿ�̸� �۵������� �÷���
	BOOL Flag_Go;					// '��' ������ ����Ǵ� ���� ����� �����°� �����ϴ� �÷���
	BOOL Flag_How;					// ���Ӽ��� ������ ���� �÷���

	unsigned short int Combo;		// �޺�
	unsigned short int Combo_Count;	// �޺� Ÿ�̸� ī����
	BOOL Flag_Combo;				// �޺� �÷���

	/*******************************************
			      ĳ���� ����
    *******************************************/
	typedef struct MEMBER{
		CPoint size; // ĳ���� �簢�� ũ�� ���� ������ size
		CPoint point;  // ĳ���� �߽� ��ǥ
		CPoint virtual_point;	// ĳ���� ������ǥ
		BOOL Flag_move;  // ���� �÷���
		BOOL Flag_ani;  // �ִϸ��̼� ���� �÷���
		BOOL Flag_stat;  // ĳ���� ���� �÷���
		BOOL FLAG_COURSE_WAIT;			// ��ų ��� �������� üũ �÷���
		CPoint Prev_point; // �̵� �� ��ǥ
		MEMBER* next; // ���� ĳ���� ���� (�������)
		MEMBER* prev; // �� ĳ���� ���� (���ΰ��� �׻� NULL)
		unsigned short int level;// ĳ���� ���� (0~3)
		unsigned short int Count_Ani; // �ִϸ��̼� ī����
	}MEMBER,HERO;
	HERO Hero;	// ���ΰ� ��ü ����
	CPoint Flag_Virtual;				// ���� ��ǥ �÷���
	/*******************************************
			     ��ֹ�, �ڽ� ����
    *******************************************/
	// ��ֹ� 
	typedef CRect HURDLE;
	HURDLE OutLine[4];
	HURDLE Wall[MAX_HURDLE];
	// �ڽ�
		typedef struct COURSE{
		HURDLE Hurdle;		// ��ġ
		int item;			// ����
		int level;			// ����
		BOOL Direction;		// �ڽ���ֹ� Ÿ�� ���� ����
		CRect Contact_area;	// ���� ����
	}COURSE;
	COURSE cou[COURSE_COUNT];			// �ڽ� ��ü ����

	/********************************************
					��� ���� ����
	**********************************************/
	int Skill_input_data[5];	// ��ų �Է¹����� ������ �迭
	int Skill_Draw[5];			// �Է� ����� Ȯ���� �迭
	COURSE* W_Cou;				// � �ڽ��� Ż���� ������ ����
	int Skill_item;				// ���� ��� ���� ����
	int Skill_frame;			// ��ų ������ ����
	int Skill_move;				// ��ų �ִϸ��̼� ȭ���� ������ ����
	int Skill_Count;			// �Է� �� ����
	int Skill_level;			// ī���Ϳ� ���� ������ ����
	BOOL Flag_N_Skill;			// �븻��ų ���ɿ��� �÷���
	BOOL Flag_Course;			// �ڽ� ��ų ��������
	BOOL Flag_Action_Skill;		// �׼� ��������
	BOOL Flag_speed;			// ���ǵ� ���� Ű�Է� �÷���
	int Count_speed;			// ���ǵ� ������ �ʿ��� ī��Ʈ ����
	int A_speed;				// ���ӵ�
	BOOL Flag_Timer_speed;		// T_QW Ÿ�̸� ������ �ֱ�����
	int Skill_Ani_Count;		// ��� �ִϸ��̼� ī����
	int Skill_Ani_MAX_Count;	// �� ������ ��
	int Skill_Bar_Count;		// ��� Ÿ�̸� ������ ī����
	unsigned int score;			// ����
	CPoint BackGround;
// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// �����Դϴ�.
public:
	virtual ~CFreeLineView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);

	//���ӵ����Ͱ���	Function_Gamedata.cpp
	void SetGameData(void);
	void SetMenuRect(CRect rect);
	void GameExit(void);
	void SetTimerData(void);
	void DrawTimer(CBufferDC* dc);
	void GameOver(void);
	void DrawScore(CBufferDC* dc);
	void SetScore(void);
	void GetScore(int AddScore);
	void TimeOver(void);
	void DrawTimeOver(CBufferDC* dc);

	//���ΰ������Լ�	Function_Hero.cpp
	void SetHeroData(void);
	void MoveHero(void);
	void DrawHero(CBufferDC* dc);
	void SetFail(void);
	void DrawFailAni(CBufferDC* dc);
	void SetSuccess(void);
	void DrawSuccessAni(CBufferDC* dc);

	//���,��ֹ������Լ�	Function_BG.cpp
	void SetCourseData(void);
	void DrawBG(CBufferDC* dc);
	void DrawIntro(CBufferDC* dc);
	void SetIntro(void);
	void SetMenuData(void);
	void DrawMenu(CBufferDC* dc);
	void DrawHow(CBufferDC* dc);
	void ContactCourse(void);
	void Action_Skill(COURSE* W_Cou);
	void Action_Skill(unsigned short int level);	// ������
	void DrawContactCourse(CBufferDC* dc);
	void SetIntroData(void);
	void SetInterrupt(void);
	void DrawInterrupt(CBufferDC* dc);
	
	//��� ���� �Լ�	Function_Skill.cpp
	void Update_Skill_input_data(short int level);
	void DrawSkill_input(CBufferDC* dc);
	void Skill_input(int input);
	void SetSkillData(void);
	void DrawResultText(CBufferDC* dc, int Flag);
	void DrawNormalSkill(CBufferDC* dc);
	void CheckNormalSkill(void);
	void SetCombo(void);
	void StartCombo(void);
	void DrawBar(CBufferDC* dc);
	void FillBar(CBufferDC* dc);
	void SetSkillAni(void);
	int PlaySkillAni(int item);
	void SkillMove(int item, int frame);
	int GetSkillWidth(int item);
	void DrawSkillBar(CBufferDC* dc);
	void FillSkillBar(CBufferDC* dc);

	//���� ���� �Լ� Music.cpp
	void PlayMusic(LPCWSTR Music_Path);
	void PauseMusic(LPCWSTR Music_Path);
	void ResumeMusic(LPCWSTR Music_Path);
	void StopMusic(LPCWSTR Music_Path);

	//�浹 ���� �Լ� Function_Crush.cpp
	void CheckVirtual(void);
	void Invert_Direction(void);
	void Crush(void);
	void CrushCheck(CRect Hurdle);
	void SetOutLine(void);
	void ContactHurdle(void);
	void SetWall(void);
	void VirtualCrushCheck(CRect Hurdle);

	
};

#ifndef _DEBUG  // FreeLineView.cpp�� ����� ����
inline CFreeLineDoc* CFreeLineView::GetDocument() const
   { return reinterpret_cast<CFreeLineDoc*>(m_pDocument); }
#endif

