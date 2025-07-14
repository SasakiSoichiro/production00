//=============================================================================
//
//	ランキング処理 [ranking.cpp]
// Author : 佐々木奏一郎
//
//=============================================================================
#include "ranking.h"
#include "rankingset.h"
#include "rankingscore.h"
#include "input.h"
#include "fade.h"
#include "sound.h"
//スコアの初期化処理
void InitRanking(void)
{
	InitRankingscore();
	InitRankingSet();
	ResetRanking();
	SetRankingTexure();
}
void UninitRanking(void)
{
	UninitRankingscore();
	UninitRankingSet();
}
void UpdateRanking(void)
{
	UpdateRankingscore();
	UpdateRankingSet();
}
void DrawRanking(void)
{
	DrawRankingscore();
	DrawRankingSet();
}
