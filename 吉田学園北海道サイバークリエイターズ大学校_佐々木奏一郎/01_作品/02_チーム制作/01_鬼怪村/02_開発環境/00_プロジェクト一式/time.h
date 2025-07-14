//=============================================================================
//
// タイマー処理 [time.h]
// Author:Marina Harada
//
//=============================================================================
#ifndef _TIME_H_
#define _TIME_H_

#include"main.h"

//=============================================================================
//マクロ定義
//=============================================================================
#define MAX_TIME (2)
#define MAX_TEX  (4)
#define MAX_MIN (4)

//=============================================================================
//プロトタイプ宣言
//=============================================================================
void InitTime(void);
void UninitTime(void);
void UpdateTime(void);
void DrawTime(void);
void SetTime(int ntime);
void SubNs(int nValue);
void SubMin(int nValue);
int GetNs(void);
int GetMin(void);

#endif