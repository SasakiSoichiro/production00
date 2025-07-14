//=============================================================================
//
//	ランキング処理 [ranking.h]
// Author : 佐々木奏一郎
//
//=============================================================================
#ifndef _RANKING__H_
#define _RANKING_H_
#include "main.h"
#define MAX_RANK (5)//表示順位数
//プロトタイプ宣言
void InitRanking(void);
void UninitRanking(void);
void UpdateRanking(void);
void DrawRanking(void);
void ResetRanking(void);
#endif
