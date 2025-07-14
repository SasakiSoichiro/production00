//=============================================================
//
// Athor: HRT ryuusei  �����L���O
// 
//=============================================================
#ifndef _RANKING_H_
#define _RANKING_H_

#include "main.h"

//�}�N����`
#define MAX_RANK (5)					//�\�����ʐ�
#define MAX_RANKNS_NUM (2)			    //�\������(�b)
#define MAX_RANKMIN_NUM (2)			    //�\������(��)
#define MAX_RANKTIME_HEIGHT (100)		//�����L���OUI�̍���
#define MAX_RANKTIME_WIDTH (50)		    //�����L���OUI�̕�
#define MAX_RANK_WIDTH (50)				//�����NUI�̕�
#define MAX_RANK_TIME_ANIM_TIME (30)	//�_�ŃA�j���[�V�����̎���

#define FILE_TXT_NS "data\\ranking\\ranking.txt"	//�b��CSV�f�[�^�t�@�C��

#define FILE_TXT_MIN "data\\ranking\\ranking1.txt"	//����CSV�f�[�^�t�@�C��

//�v���g�^�C�v�錾
void InitRanking(void);
void UninitRanking(void);
void UpdateRanking(void);
void DrawRanking(void);
void ResetRanking(const char* DateScore);
void SetRanking(int ntime,int min);

#endif // !_RANKING_H_
