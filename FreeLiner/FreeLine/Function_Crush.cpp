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

		 충돌과 관련된 함수

************************************/



void CFreeLineView::CheckVirtual(void)
{
	CRect rect;
	GetClientRect(&rect);
	if(Hero.virtual_point.x-8>rect.Width()/2 && Hero.virtual_point.x+25<=BG_WIDTH-rect.Width()/2)
		Flag_Virtual.x=FALSE;
	else
		Flag_Virtual.x=TRUE;

	if(Hero.virtual_point.y-20>=rect.Height()/2 && Hero.virtual_point.y+20<=BG_HEIGHT-rect.Height()/2)
		Flag_Virtual.y=FALSE;
	else
		Flag_Virtual.y=TRUE;
}

void CFreeLineView::Invert_Direction(void)
{
	if(mode==MODE_EASY)
	{
		switch(Hero.Flag_move)
		{
		case NORTH:
			Hero.Flag_move=SOUTH;
			break;
		case SOUTH:
			Hero.Flag_move=NORTH;
			break;
		case EAST:
			Hero.Flag_move=WEST;
			break;
		case WEST:
			Hero.Flag_move=EAST;
			break;
		}
	}
}

void CFreeLineView::Crush(void)
{
	SetTimer(T_CRUSH,SECOND/2,NULL);
	Invert_Direction();
	A_speed=0;
	Count_speed=0;
	Hero.Flag_stat=S_CRUSH;
	SetSkillData();
	PlayMusic(M_CRUSH);
	KillTimer(T_SKILL);
}

void CFreeLineView::CrushCheck(CRect Hurdle)
{
	CRect Hero_Rect(Hero.point.x-Hero.size.x,Hero.point.y-Hero.size.y,
				Hero.point.x+Hero.size.x,Hero.point.y+Hero.size.y);
	if(Hurdle.IntersectRect(Hero_Rect,Hurdle))
		Crush();
}

void CFreeLineView::SetOutLine(void)
{
	// 고정 벽
	CRect rect;
	GetClientRect(rect);
	OutLine[0] = CRect(-50,-50,0,rect.Height());
	OutLine[1] = CRect(-50,rect.Height(),rect.Width()+50,rect.Height()+50);
	OutLine[2] = CRect(rect.Width(),-50,rect.Width()+50,rect.Height()+50);
	OutLine[3] = CRect(-50,-50,rect.Width()+50,-20);
}

void CFreeLineView::ContactHurdle(void)	// 장애물 검사
{
	
	for(int i=0;i<4;i++)	
	{
		CrushCheck(OutLine[i]);		// 바깥 라인
		VirtualCrushCheck(Wall[i]); // 안쪽 벽 가상좌표
	}
	if(Hero.Flag_stat==S_MOVE)
	{
		for(int i=4;i<16;i++)
		{
			VirtualCrushCheck(Wall[i]);
		}
	}
	if(Hero.virtual_point.y<=1441)		// for문에 너무 오래잡히는걸 방지하기 위해 나눔
	{
		for(int i=16;i<44;i++)
		{
			VirtualCrushCheck(Wall[i]);
		}
	}
	else
	{
		for(int i=44;i<MAX_HURDLE;i++)
		{
			VirtualCrushCheck(Wall[i]);
		}
	}
}

void CFreeLineView::SetWall(void)	// 가상좌표 기준
{
	// 초보 -> 중급 지형 벽
	Wall[0] = CRect(0,660,3520,720);
	Wall[1] = CRect(3720,660,BG_WIDTH,720);
	// 중급 -> 고급 지형 벽
	Wall[2] = CRect(0,1400,2080,1560);
	Wall[3] = CRect(2389,1400,BG_WIDTH,1560);
	
	// 코스 장애물 4~15
	Wall[4] = CRect(1292,385,1504,393);	// 코스 1
	Wall[5] = CRect(2739,426,2951,434);	// 코스 2
	//코스3
	Wall[6] = CRect(801,1257,1331,1262);
	Wall[7] = CRect(965,1213,1178,1221);
	Wall[8] = CRect(922,1235,1225,1237);
	//코스4
	Wall[9] = CRect(2792,839,3322,843);
	Wall[10] = CRect(2953,802,3165,810);
	Wall[11] = CRect(2928,815,3185,819);
	//코스 5
	Wall[12] = CRect(2791,2251,3122,2253);
	Wall[13] = CRect(2988,2222,3180,2224);
	Wall[14] = CRect(3054,2192,3105,2193);
	Wall[15] = CRect(3116,2184,3129,2186);

	// 초보지형 장애물
	Wall[16] = CRect(245,43,290,46);
	Wall[17] = CRect(134,520,179,523);
	Wall[18] = CRect(742,231,787,234);
	Wall[19] = CRect(1210,103,1267,105);
	Wall[20] = CRect(1325,548,1370,551);
	Wall[21] = CRect(1636,256,1693,258);
	Wall[22] = CRect(2087,459,2144,461);
	Wall[23] = CRect(2358,81,2415,83);
	Wall[24] = CRect(2488,469,2524,472);
	Wall[25] = CRect(2808,159,2844,162);
	Wall[26] = CRect(2999,521,3044,524);
	Wall[27] = CRect(3256,247,3313,249);
	Wall[28] = CRect(3510,138,3546,141);
	Wall[29] = CRect(3590,411,3647,413);
	// 중급지형 장애물
	Wall[30] = CRect(3,803,20,1389);  // 울타리 시작
	Wall[31] = CRect(21,798,49,1338);
	Wall[32] = CRect(57,793,71,915);
	Wall[33] = CRect(73,797,105,838); // 울타리 끝
	Wall[34] = CRect(617,1167,675,1170);
	Wall[35] = CRect(906,1053,964,1056);
	Wall[36] = CRect(1377,906,1435,909);
	Wall[37] = CRect(1145,814,1181,817);
	Wall[38] = CRect(1376,904,1434,907);
	Wall[39] = CRect(1980,1063,2016,1066);
	Wall[40] = CRect(2172,847,2208,850);
	Wall[41] = CRect(2534,1250,2570,1253);
	Wall[42] = CRect(2588,984,2646,987);
	Wall[43] = CRect(2953,1041,3011,1044);

	// 고급지형 장애물
	Wall[44] = CRect(110,1702,166,1705);
	Wall[45] = CRect(175,2161,231,2164);
	Wall[46] = CRect(1434,1837,1490,1840);
	Wall[47] = CRect(1488,1682,1544,1685);
	Wall[48] = CRect(1780,1748,1836,1751);
	Wall[49] = CRect(1959,2132,2015,2135);
	Wall[50] = CRect(2223,1872,2279,1875);
	Wall[51] = CRect(2285,2350,2341,2353);
	Wall[52] = CRect(3163,1721,3219,1724);
	Wall[53] = CRect(3515,2201,3571,2204);
	Wall[54] = CRect(45,2025,79,2058);
	Wall[55] = CRect(398,1724,433,1759);
	Wall[56] = CRect(598,2039,631,2074);
	Wall[57] = CRect(933,1812,968,1847);
	Wall[58] = CRect(1212,2029,1246,2065);
	Wall[59] = CRect(1535,1917,1569,1952);
	Wall[60] = CRect(3288,2039,3324,2075);
	Wall[61] = CRect(642,2233,687,2236);
	Wall[62] = CRect(964,2111,1009,2114);
	Wall[63] = CRect(1693,2070,1739,2073);
	Wall[64] = CRect(3346,1643,3391,1646);
	Wall[65] = CRect(3572,2021,3617,2024);
	Wall[66] = CRect(386,1831,441,1834);
	Wall[67] = CRect(1508,2217,1563,2220);
	Wall[68] = CRect(2436,1865,2491,1868);
	Wall[69] = CRect(2618,2102,2673,2105);
	Wall[70] = CRect(2764,1718,2819,1721);
	Wall[71] = CRect(3446,1856,3501,1859);

}

void CFreeLineView::VirtualCrushCheck(CRect Hurdle)
{
	CRect Hero_Rect(Hero.virtual_point.x-Hero.size.x,Hero.virtual_point.y-Hero.size.y,
				Hero.virtual_point.x+Hero.size.x,Hero.virtual_point.y+Hero.size.y);
	if(Hurdle.IntersectRect(Hero_Rect,Hurdle))
		Crush();
}

