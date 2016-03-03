// FreeLineView.h : CFreeLineView 클래스의 인터페이스
//
#include "BufferDC.h"
#include "Macro.h"
#pragma once


class CFreeLineView : public CView
{
protected: // serialization에서만 만들어집니다.
	CFreeLineView();
	DECLARE_DYNCREATE(CFreeLineView)

// 특성입니다.
public:
	CFreeLineDoc* GetDocument() const;

// 작업입니다.
public:
	/*******************************************
			     게임 설정 관련
    *******************************************/
	short int menu;	// 메뉴상태
	short int mode;	// 모드상태
	BOOL sub_menu; // 서브메뉴 선택
	typedef struct S_RECT{		
		CPoint menu_point;			// 메뉴 선택 버튼 위치
		short int menu_selected;	// 메뉴 선택 버튼 플래그
	}S_RECT;
	S_RECT s_rect,i_rect;

	int Intro_alpha;				// 인트로 알파값
	BOOL Flag_Intro;				// 인트로 그림 플래그
	BOOL Flag_Alpha;				// 인트로 알파값 플래그
	unsigned short int Timer;		// 타이머 인터페이스 값
	unsigned short int Timer_Count;	// 인터럽트 버그 방지용 타이머 카운트
	BOOL Flag_Timer;				// 타이머 작동중인지 플래그
	BOOL Flag_Go;					// '고' 음악이 재생되는 동안 배경음 나오는걸 방지하는 플래그
	BOOL Flag_How;					// 게임설명 페이지 상태 플래그

	unsigned short int Combo;		// 콤보
	unsigned short int Combo_Count;	// 콤보 타이머 카운터
	BOOL Flag_Combo;				// 콤보 플래그

	/*******************************************
			      캐릭터 관련
    *******************************************/
	typedef struct MEMBER{
		CPoint size; // 캐릭터 사각형 크기 값을 가지는 size
		CPoint point;  // 캐릭터 중심 좌표
		CPoint virtual_point;	// 캐릭터 가상좌표
		BOOL Flag_move;  // 방향 플래그
		BOOL Flag_ani;  // 애니메이션 상태 플래그
		BOOL Flag_stat;  // 캐릭터 상태 플래그
		BOOL FLAG_COURSE_WAIT;			// 스킬 대기 상태인지 체크 플래그
		CPoint Prev_point; // 이동 전 좌표
		MEMBER* next; // 다음 캐릭터 지정 (꼬리잡기)
		MEMBER* prev; // 전 캐릭터 지정 (주인공은 항상 NULL)
		unsigned short int level;// 캐릭터 레벨 (0~3)
		unsigned short int Count_Ani; // 애니메이션 카운터
	}MEMBER,HERO;
	HERO Hero;	// 주인공 객체 생성
	CPoint Flag_Virtual;				// 가상 좌표 플래그
	/*******************************************
			     장애물, 코스 관련
    *******************************************/
	// 장애물 
	typedef CRect HURDLE;
	HURDLE OutLine[4];
	HURDLE Wall[MAX_HURDLE];
	// 코스
		typedef struct COURSE{
		HURDLE Hurdle;		// 위치
		int item;			// 종류
		int level;			// 레벨
		BOOL Direction;		// 코스장애물 타는 방향 저장
		CRect Contact_area;	// 접촉 범위
	}COURSE;
	COURSE cou[COURSE_COUNT];			// 코스 객체 생성

	/********************************************
					기술 관련 변수
	**********************************************/
	int Skill_input_data[5];	// 스킬 입력받을거 저장할 배열
	int Skill_Draw[5];			// 입력 됬는지 확인할 배열
	COURSE* W_Cou;				// 어떤 코스를 탈건지 정보를 저장
	int Skill_item;				// 평지 기술 종류 저장
	int Skill_frame;			// 스킬 프레임 저장
	int Skill_move;				// 스킬 애니메이션 화면의 고정을 위해
	int Skill_Count;			// 입력 할 순서
	int Skill_level;			// 카운터와 비교할 레벨을 저장
	BOOL Flag_N_Skill;			// 노말스킬 가능여부 플래그
	BOOL Flag_Course;			// 코스 스킬 상태인지
	BOOL Flag_Action_Skill;		// 액션 상태인지
	BOOL Flag_speed;			// 스피드 증가 키입력 플래그
	int Count_speed;			// 스피드 증가에 필요한 카운트 버퍼
	int A_speed;				// 가속도
	BOOL Flag_Timer_speed;		// T_QW 타이머 조건을 주기위해
	int Skill_Ani_Count;		// 기술 애니메이션 카운터
	int Skill_Ani_MAX_Count;	// 총 프레임 수
	int Skill_Bar_Count;		// 기술 타이머 게이지 카운터
	unsigned int score;			// 점수
	CPoint BackGround;
// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CFreeLineView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);

	//게임데이터관련	Function_Gamedata.cpp
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

	//주인공관련함수	Function_Hero.cpp
	void SetHeroData(void);
	void MoveHero(void);
	void DrawHero(CBufferDC* dc);
	void SetFail(void);
	void DrawFailAni(CBufferDC* dc);
	void SetSuccess(void);
	void DrawSuccessAni(CBufferDC* dc);

	//배경,장애물관련함수	Function_BG.cpp
	void SetCourseData(void);
	void DrawBG(CBufferDC* dc);
	void DrawIntro(CBufferDC* dc);
	void SetIntro(void);
	void SetMenuData(void);
	void DrawMenu(CBufferDC* dc);
	void DrawHow(CBufferDC* dc);
	void ContactCourse(void);
	void Action_Skill(COURSE* W_Cou);
	void Action_Skill(unsigned short int level);	// 재정의
	void DrawContactCourse(CBufferDC* dc);
	void SetIntroData(void);
	void SetInterrupt(void);
	void DrawInterrupt(CBufferDC* dc);
	
	//기술 관련 함수	Function_Skill.cpp
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

	//음악 관련 함수 Music.cpp
	void PlayMusic(LPCWSTR Music_Path);
	void PauseMusic(LPCWSTR Music_Path);
	void ResumeMusic(LPCWSTR Music_Path);
	void StopMusic(LPCWSTR Music_Path);

	//충돌 관련 함수 Function_Crush.cpp
	void CheckVirtual(void);
	void Invert_Direction(void);
	void Crush(void);
	void CrushCheck(CRect Hurdle);
	void SetOutLine(void);
	void ContactHurdle(void);
	void SetWall(void);
	void VirtualCrushCheck(CRect Hurdle);

	
};

#ifndef _DEBUG  // FreeLineView.cpp의 디버그 버전
inline CFreeLineDoc* CFreeLineView::GetDocument() const
   { return reinterpret_cast<CFreeLineDoc*>(m_pDocument); }
#endif

