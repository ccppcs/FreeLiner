#include "stdafx.h"
/********************************
          매크로 정의 
********************************/

//메뉴
#define INTRO  0 // 인트로
#define MENU_SELECT 1 // 메뉴선택
#define START  2 // 게임시작
#define HIGHSCORE  3 // 고득점
#define EXIT  4 // 종료
#define TIMEOVER 5 // 타임오버
#define INTERRUPT -1 // 인터럽트
#define HOW 6		// 게임 설명

//배경 정보
#define BG_WIDTH 3780
#define BG_HEIGHT 2450

//스피드 바 정보(한칸)
#define BAR_WIDTH 24
#define BAR_HEIGHT 281
#define BAR2_WIDTH 300	// 기술게이지 정보
#define BAR2_HEIGHT 30

//평지 기술 아이콘 정보
#define ICON_SIZE 32 // 32x32

//모드 
#define MODE_EASY 1  // 이지 모드

/****방향****/
#define NORTH 3  // 북쪽
#define SOUTH 2  // 남쪽
#define EAST 1  // 동쪽
#define WEST 0  // 서쪽

// 기본 상수 정의
#define SPEED 2 // 최저 스피드
#define MAX_A_SPEED 10 // 최고 스피드
#define MAX_COMBO_COUNT 40 // 콤보 카운터 최대
#define MAX_SKILL_COUNT 20 // 스킬게이지 카운터 최대
#define MAX_COUNT_SPEED 2  // 스피드 카운터 (q,w)
#define SECOND 1000
#define FRAME SECOND/120	// 프레임
#define ANI_FRAME SECOND/120 // 스킬 애니메이션 프레임
#define MAX_HURDLE 72		// 장애물 총 갯수

// 타이머
#define T_INTRO		0  // Intro 처리
#define T_TIMER		1  // 타이머 표현
#define T_TIMEOVER	2  // 타임 오버
#define T_MAIN		11  // 메인 타이머
#define T_HERO_ANI  12  // 주인공 애니메이션
#define T_CONTACT	20	// 코스 탈건지 체크하는 타이머
#define T_SKILL		21	// 스킬 입력 타이머
#define T_SPEED		22 // 시간 지나면 스피드 감소
#define T_QW		23 // T_SPEED가 시작되는 타이머
#define T_FAIL		-1	// 기술 실패
#define T_SUCCESS	24 //  기술 성공
#define T_CRUSH		25 // 충돌
#define T_COMBO		26 // 콤보 타이머
#define T_GO		27 // '고' 타이머
#define T_SKILL_ANI 28 // 스킬 애니메이션


// 애니메이션 상태
#define A_MOVE 0	   // 이동 중
#define	A_FAIL -1		// 실패 중

// 주인공 상태
#define S_FAIL -1		// 기술, 코스 실패
#define S_MOVE 0		// 이동중
#define S_SKILL 1		// 기술 사용중
#define S_SUCCESS 2		// 기술 성공
#define S_CRUSH 3		// 충돌 상태

// 방향이동은 기존 방향 상수로 쓴다

#define SKILL_1 1  // 싱글 기술 1 수치는 필요 속도
#define SKILL_2 3  // 싱글 기술 2
#define SKILL_3 5  // 싱글 기술 3

#define C1		1	// 코스 종류 1
#define C2		2	// 코스 종류 2
#define C3		3	// 코스 종류 3
#define S1		4	// 기술 종류 1
#define S2		5	// 기술 종류 2
#define S3		6	// 기술 종류 3

#define SUCCESS 0  // 기술 성공
#define FAIL -1  // 기술 실패

#define COURSE_COUNT 5 //코스 개수
#define ARROW_MAX 5 // 화살표 갯수

/**********************
    음악 파일 관련
**********************/
// 음악 파일 경로
#define M_MENU_MOVE		 _T("res/sound/Menu_Move.mp3")
#define M_MENU_THEME	 _T("res/sound/Menu_Theme.mp3")
#define M_READY			 _T("res/sound/Ready.mp3")
#define M_GO			 _T("res/sound/Go.mp3")
#define M_MAIN_THEME	 _T("res/sound/Main_Theme.mp3")
#define M_CRUSH			 _T("res/sound/Crush.mp3")
#define M_FAIL			 _T("res/sound/Fail.mp3")
#define M_SUCCESS		 _T("res/sound/Success.mp3")
#define M_GAMEOVER		 _T("res/sound/GameOver.mp3")

