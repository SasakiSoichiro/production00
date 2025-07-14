//=============================================================================
//
//	タイム処理 [time.h]
// Author : 佐々木奏一郎
//
//=============================================================================
#ifndef _TIME_H_
#define _TIME_H_
#include "main.h"
#define MAX_TIME (3)
//プロトタイプ宣言
void InitTime(void);
void UninitTime(void);
void UpdateTime(void);
void DrawTime(void);
int TimeCnt(int nTime);
int GetTime(void);
#endif