//=============================================================================
//
// �X���[���[�V�������� [slow.h]
// Author : ���X�ؑt��Y
//
//=============================================================================
#ifndef _SLOW_H_
#define _SLOW_H_
#include "main.h"

#define SLOW (4);


//	�t�F�[�h�̏��
typedef enum
{
	SLOWFADE_NONE = 0,	//	�������Ă��Ȃ����
	SLOWFADE_IN,		//	�t�F�[�h�C�����
	SLOWFADE_OUT,		//	�t�F�[�h�A�E�g���
	SLOWFADE_MAX
}SLOWFADE;

//�\����
typedef struct
{
	float fMulti;
	float fDivi;
	int nMulti;
	int nDivi;
	bool bUse;
	D3DXCOLOR color;
	SLOWFADE fade;
}Slow;

//�v���g�^�C�v�錾
void InitSlow(void);
void UninitSlow(void);
void UpdateSlow(void);
void DrawSlow(void);
void SetSlow(void);
Slow*GetSlow(void);

#endif