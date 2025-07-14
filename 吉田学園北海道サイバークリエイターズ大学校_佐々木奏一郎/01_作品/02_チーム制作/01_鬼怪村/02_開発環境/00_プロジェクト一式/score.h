//=============================================================================
//
//    スコア処理 [score.h]
//    Author : ryuu HRT
//
//=============================================================================
#ifndef _SCORE_H_
#define _SCORE_H_

#include "main.h"

// マクロ定義
#define MAX_SCORE_COOKEI_NOMAL (156)	// 通常クッキーのスコア
#define MAX_SCORE_COOKEI_HARD (236)		// 硬いクッキーのスコア

//=====================
// 構造体
//====================
//スコア情報の構造体
typedef struct
{
	bool bUse;				// 使用しているか
	int nCountScoreCounter;	// 0のカウント
	int SCORE;				// 最終スコア
}Score;

// プロトタイプ
void InitScore(void);
void UninitScore(void);
void UpdateScore(void);
void DrawScore(void);
void SetScore(int nScore);
void AddScore(int nValue);
int  ScoreCounter(int nScore);
int GetScore(void);

#endif // !_SCORE_H_
