//=============================================================================
//
//	�m�C�Y���� [noise.h]
// Author : ���X�ؑt��Y
//
//=============================================================================
#ifndef _NOIZ_H_//���̃}�N����`������Ă��Ȃ�������
#define _NOIZ_H_//2�e�C���N���[�h�h�~�̃}�N����`
#include "main.h"

typedef enum
{
	NOISE_A = 0,
	NOISE_B,
	NOISE_C,
	NOISE_MAX
}NOIZ;

typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	float fWidth;		//��
	float fHeight;		//����
	int nType;			//�u���b�N�̃^�C�v
	bool bUse;			//�g�p���Ă��邩�ǂ���
}Noise;

static const char* NOISE_TEXTURE[NOISE_MAX] =
{
	"data\\texture\\noise00.png",			//�u���b�N
	"data\\texture\\noise01.png",			//�{�^��
	"data\\texture\\noise02.png",			//�{�^��
};

//�v���g�^�C�v�錾
void InitNoise(void);
void UninitNoise(void);
void UpdateNoise(void);
void DrawNoise(void);
void RandNoise(float *U, float *V,int nCnt);
#endif