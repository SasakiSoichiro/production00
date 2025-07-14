//=============================================================================
//
//	�E��UI���� [pickupUI.h]
// Author : ���X�ؑt��Y
//
//=============================================================================
#ifndef _PICKUPUI_H_//���̃}�N����`������Ă��Ȃ�������
#define _PICKUPUI_H_//2�d�C���N���[�h�h�~�̃}�N����`
#include "main.h"
#define PICKBILL (7.0f)
#define MAX_BLB (16)

typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXMATRIX mtxWorld;
	bool bDisplay;
	bool bUse;
}PickUpUI;


//�v���g�^�C�v�錾
void InitPickUpUI(void);
void UninitPickUpUI(void);
void UpdatePickUpUI(void);
void DrawPickUpUI(void);
int SetPickUpUI(D3DXVECTOR3 pos, D3DXVECTOR3 dir);

#endif