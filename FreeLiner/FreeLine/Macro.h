#include "stdafx.h"
/********************************
          ��ũ�� ���� 
********************************/

//�޴�
#define INTRO  0 // ��Ʈ��
#define MENU_SELECT 1 // �޴�����
#define START  2 // ���ӽ���
#define HIGHSCORE  3 // �����
#define EXIT  4 // ����
#define TIMEOVER 5 // Ÿ�ӿ���
#define INTERRUPT -1 // ���ͷ�Ʈ
#define HOW 6		// ���� ����

//��� ����
#define BG_WIDTH 3780
#define BG_HEIGHT 2450

//���ǵ� �� ����(��ĭ)
#define BAR_WIDTH 24
#define BAR_HEIGHT 281
#define BAR2_WIDTH 300	// ��������� ����
#define BAR2_HEIGHT 30

//���� ��� ������ ����
#define ICON_SIZE 32 // 32x32

//��� 
#define MODE_EASY 1  // ���� ���

/****����****/
#define NORTH 3  // ����
#define SOUTH 2  // ����
#define EAST 1  // ����
#define WEST 0  // ����

// �⺻ ��� ����
#define SPEED 2 // ���� ���ǵ�
#define MAX_A_SPEED 10 // �ְ� ���ǵ�
#define MAX_COMBO_COUNT 40 // �޺� ī���� �ִ�
#define MAX_SKILL_COUNT 20 // ��ų������ ī���� �ִ�
#define MAX_COUNT_SPEED 2  // ���ǵ� ī���� (q,w)
#define SECOND 1000
#define FRAME SECOND/120	// ������
#define ANI_FRAME SECOND/120 // ��ų �ִϸ��̼� ������
#define MAX_HURDLE 72		// ��ֹ� �� ����

// Ÿ�̸�
#define T_INTRO		0  // Intro ó��
#define T_TIMER		1  // Ÿ�̸� ǥ��
#define T_TIMEOVER	2  // Ÿ�� ����
#define T_MAIN		11  // ���� Ÿ�̸�
#define T_HERO_ANI  12  // ���ΰ� �ִϸ��̼�
#define T_CONTACT	20	// �ڽ� Ż���� üũ�ϴ� Ÿ�̸�
#define T_SKILL		21	// ��ų �Է� Ÿ�̸�
#define T_SPEED		22 // �ð� ������ ���ǵ� ����
#define T_QW		23 // T_SPEED�� ���۵Ǵ� Ÿ�̸�
#define T_FAIL		-1	// ��� ����
#define T_SUCCESS	24 //  ��� ����
#define T_CRUSH		25 // �浹
#define T_COMBO		26 // �޺� Ÿ�̸�
#define T_GO		27 // '��' Ÿ�̸�
#define T_SKILL_ANI 28 // ��ų �ִϸ��̼�


// �ִϸ��̼� ����
#define A_MOVE 0	   // �̵� ��
#define	A_FAIL -1		// ���� ��

// ���ΰ� ����
#define S_FAIL -1		// ���, �ڽ� ����
#define S_MOVE 0		// �̵���
#define S_SKILL 1		// ��� �����
#define S_SUCCESS 2		// ��� ����
#define S_CRUSH 3		// �浹 ����

// �����̵��� ���� ���� ����� ����

#define SKILL_1 1  // �̱� ��� 1 ��ġ�� �ʿ� �ӵ�
#define SKILL_2 3  // �̱� ��� 2
#define SKILL_3 5  // �̱� ��� 3

#define C1		1	// �ڽ� ���� 1
#define C2		2	// �ڽ� ���� 2
#define C3		3	// �ڽ� ���� 3
#define S1		4	// ��� ���� 1
#define S2		5	// ��� ���� 2
#define S3		6	// ��� ���� 3

#define SUCCESS 0  // ��� ����
#define FAIL -1  // ��� ����

#define COURSE_COUNT 5 //�ڽ� ����
#define ARROW_MAX 5 // ȭ��ǥ ����

/**********************
    ���� ���� ����
**********************/
// ���� ���� ���
#define M_MENU_MOVE		 _T("res/sound/Menu_Move.mp3")
#define M_MENU_THEME	 _T("res/sound/Menu_Theme.mp3")
#define M_READY			 _T("res/sound/Ready.mp3")
#define M_GO			 _T("res/sound/Go.mp3")
#define M_MAIN_THEME	 _T("res/sound/Main_Theme.mp3")
#define M_CRUSH			 _T("res/sound/Crush.mp3")
#define M_FAIL			 _T("res/sound/Fail.mp3")
#define M_SUCCESS		 _T("res/sound/Success.mp3")
#define M_GAMEOVER		 _T("res/sound/GameOver.mp3")

