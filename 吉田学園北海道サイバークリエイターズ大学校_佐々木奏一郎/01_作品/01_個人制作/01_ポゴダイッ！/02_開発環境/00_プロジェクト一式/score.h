//=============================================================================
//
//	�X�R�A���� [score.h]
// Author : ���X�ؑt��Y
//
//=============================================================================
#ifndef _SCORE_H_
#define _SCORE_H_
#include "main.h"
#define MAX_SCORE (8)
//�v���g�^�C�v�錾
void InitScore(void);
void UninitScore(void);
void UpdateScore(void);
void DrawScore(void);
void SetScore(int nScore);
void AddScore(int nValue);
int ScoreCnt(int nScore);
int GetScore(void);
#endif