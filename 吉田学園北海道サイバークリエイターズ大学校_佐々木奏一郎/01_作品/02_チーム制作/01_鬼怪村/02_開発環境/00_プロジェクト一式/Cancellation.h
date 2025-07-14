//====================================================
//
// �����̏��� [Cancellation.h]
// Author : yabuki yukito
//
//====================================================

#ifndef _CANCELLATION_H_
#define _CANCELLATION_H_

#include "main.h"

// �����e�N�X�`���̎��
typedef enum
{
	TEX_0 = 0,
	TEX_1,
	TEX_MAX
}TEXTYPE;

// �\����
typedef struct
{
	D3DXVECTOR3 pos;	// �ʒu
	bool bUse;			// �g�p���Ă��邩�ǂ���
	float fCnt;			// 
	bool bKeyhave;		// 
	int nType;			// ���
}Cance;

static const char* X_TEX[TEX_MAX] =
{
	"data\\texture\\Cancellation.png",
	"data\\texture\\kaijoB.png",
};

// �v���g�^�C�v�錾
void InitCancellation(void);
void UinitCancellation(void);
void UpdateCancellation(void);
void DrawCancellation(void);

#endif
