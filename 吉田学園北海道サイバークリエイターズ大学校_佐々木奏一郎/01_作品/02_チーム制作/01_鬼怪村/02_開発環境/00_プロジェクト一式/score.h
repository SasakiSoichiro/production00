//=============================================================================
//
//    �X�R�A���� [score.h]
//    Author : ryuu HRT
//
//=============================================================================
#ifndef _SCORE_H_
#define _SCORE_H_

#include "main.h"

// �}�N����`
#define MAX_SCORE_COOKEI_NOMAL (156)	// �ʏ�N�b�L�[�̃X�R�A
#define MAX_SCORE_COOKEI_HARD (236)		// �d���N�b�L�[�̃X�R�A

//=====================
// �\����
//====================
//�X�R�A���̍\����
typedef struct
{
	bool bUse;				// �g�p���Ă��邩
	int nCountScoreCounter;	// 0�̃J�E���g
	int SCORE;				// �ŏI�X�R�A
}Score;

// �v���g�^�C�v
void InitScore(void);
void UninitScore(void);
void UpdateScore(void);
void DrawScore(void);
void SetScore(int nScore);
void AddScore(int nValue);
int  ScoreCounter(int nScore);
int GetScore(void);

#endif // !_SCORE_H_
