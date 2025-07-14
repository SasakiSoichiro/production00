//=============================================================================
//
//	スコア処理 [score.h]
// Author : 佐々木奏一郎
//
//=============================================================================
#ifndef _SCORE_H_
#define _SCORE_H_
#include "main.h"
#define MAX_SCORE (8)
//プロトタイプ宣言
void InitScore(void);
void UninitScore(void);
void UpdateScore(void);
void DrawScore(void);
void SetScore(int nScore);
void AddScore(int nValue);
int ScoreCnt(int nScore);
int GetScore(void);
#endif