//=============================================================================
//
// �G�t�F�N�g���� [effect.h]
// Author :Marina Harada
//
//=============================================================================
#ifndef _EFFECT_H_ //���̃}�N����`������Ă��Ȃ�������
#define _EFFECT_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

#include"main.h"

//�}�N����`
#define MAX_EFFECT (128)
#define EFC_LIFE (20)

//�G�t�F�N�g�̍\����
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 move;
	D3DXVECTOR3 rot;
	D3DXMATRIX mtxWorld;
	D3DXCOLOR col;
	int nLife;
	bool buse;
}Effect;

//�v���g�^�C�v�錾
void InitEffect(void);
void UninitEffect(void);
void UpdateEffect(void);
void DrawEffect(void);
void SetEffect(D3DXVECTOR3 pos, D3DXVECTOR3 dir, int nLife, D3DXCOLOR col);

#endif