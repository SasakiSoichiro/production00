//=============================================================================
//
//	�̗͂̏��� [stamina.h]
// Author : ���X�ؑt��Y
//
//=============================================================================
#ifndef _STAMINA_H_//���̃}�N����`������Ă��Ȃ�������
#define _STAMINA_H_//2�e�C���N���[�h�h�~�̃}�N����`
#include "main.h"

typedef enum
{
	STAMINA_GAUGE=0,
	STAMINA_FRAME,
	STAMINA_MAX
}STAMINA;

//�v���g�^�C�v�錾
void InitStamina(void);
void UninitStamina(void);
void UpdateStamina(void);
void DrawStamina(void);
bool GetStamina(void);

#endif