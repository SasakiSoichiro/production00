//=============================================================================
//
//	�����L���O���� [ranking.cpp]
// Author : ���X�ؑt��Y
//
//=============================================================================
#include "ranking.h"
#include "rankingset.h"
#include "rankingscore.h"
#include "input.h"
#include "fade.h"
#include "sound.h"
//�X�R�A�̏���������
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
