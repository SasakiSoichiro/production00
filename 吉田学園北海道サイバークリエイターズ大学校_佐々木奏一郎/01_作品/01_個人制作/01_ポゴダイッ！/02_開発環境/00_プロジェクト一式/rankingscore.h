//=============================================================================
//
//	ランキングスコア処理 [rankingscore.h]
// Author : 佐々木奏一郎
//
//=============================================================================
#ifndef _PANKINGSCORE__H_
#define _RANKINGSCORE_H_
#include "main.h"
#define MAX_RANK (1)
#define MAX_HEIGHT (69.0f)
#define MAX_WIDTH (69.0f)
//プロトタイプ宣言
void InitRankingscore(void);
void UninitRankingscore(void);
void UpdateRankingscore(void);
void DrawRankingscore(void);
void Writescore(void);
void ResetRanking(void);
void SetRanking(int nScore);
void SetRankingTexure(void);
int GetRankScore(void);
#endif
