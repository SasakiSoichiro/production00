//=============================================================================
//
//	�G�t�F�N�g���� [effect.h]
// Author : ���X�ؑt��Y
//
//=============================================================================
#ifndef _EFFECT_H_//���̃}�N����`������Ă��Ȃ�������
#define _EFFECT_H_//2�e�C���N���[�h�h�~�̃}�N����`
#include "main.h"
//�G�t�F�N�g�̎��
typedef enum
{
	EFFECTTYPE_PLAYER=0,
	EFFECTTYPE_ENEMY,
	EFFECTTYPE_PARTICLE1,
	EFFECTTYPE_PARTICLE2,
	EFFECTTYPE_MAX
}EFFECTTYPE;
//�v���g�^�C�v�錾
void InitEffect(void);
void UninitEffect(void);
void UpdateEffect(void);
void DrawEffect(void);
void SetEffect(D3DXVECTOR3 pos, D3DXVECTOR3 move,D3DXCOLOR col,float fRadius,int nLife,	EFFECTTYPE type);
#endif