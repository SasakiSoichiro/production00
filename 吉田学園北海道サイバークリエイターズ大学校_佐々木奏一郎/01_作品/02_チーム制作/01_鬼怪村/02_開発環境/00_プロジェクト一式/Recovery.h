//=============================================================================
//
// �񕜂̏��� [Recovery.h]
// Author : Hirata ryuusei
//
//=============================================================================
#ifndef _RECOVERY_H_
#define _RECOVERY_H_

#include "main.h"

// �t�F�[�h�̏��
typedef enum
{
	Recovery_NONE = 0,	// �������Ă��Ȃ����
	Recovery_IN,		// �t�F�[�h�C�����
	Recovery_OUT,		// �t�F�[�h�A�E�g���
	Recovery_DRAW,
	Recovery_MAX
}Recovery_MODE;

// �񕜂̍\����
typedef struct
{
	D3DXCOLOR col;
	Recovery_MODE ui;
	bool bUse;
	int count;
}Recovery;

// �v���g�^�C�v�錾
void InitRecovery(void);
void UinitRecovery(void);
void UpdateRecovery(void);
void DrawRecovery(void);
void SetRecovery(int count);

#endif // !_Recovery_H_
