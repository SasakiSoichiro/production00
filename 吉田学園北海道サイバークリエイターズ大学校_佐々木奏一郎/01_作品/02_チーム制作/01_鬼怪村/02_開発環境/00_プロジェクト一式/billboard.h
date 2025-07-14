//====================================================
//
// �؂̏��� [billboard.h]
// Author : yabuki yukito
//
//====================================================

#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

#include "main.h"

//++++++++++++++++++++++++++++++++++++++++++++++++++++
// �}�N����`
//++++++++++++++++++++++++++++++++++++++++++++++++++++
#define MAX_BILLBOARD (15)

//++++++++++++++++++++++++++++++++++++++++++++++++++++
// �A�C�e���̎��
//++++++++++++++++++++++++++++++++++++++++++++++++++++
typedef enum
{
	BILLBOARDTYPE_0,	// ��
	BILLBOARDTYPE_1,	// �E��
	BILLBOARDTYPE_2,	// ���������Ă��Ȃ�(0/2)
	BILLBOARDTYPE_3,	// ���������Ă��邪1�̂�(1/2)
	BILLBOARDTYPE_4,	// �E�o�\
	BILLBOARDTYPE_5,	// �E�o���闭�߃Q�[�W
	BILLBOARDTYPE_MAX	
}TYPE;

static const char* ITEM_TEXTURE[BILLBOARDTYPE_MAX] =
{
	"data\\texture\\Wood.png",			// �؂̉摜
	"data\\texture\\itembilbord.jpg",	// �E���摜
	"data\\texture\\no2.png",			// ���������Ă��Ȃ�(0/2)
	"data\\texture\\no1.png",			// ���������Ă��邪1�̂�(1/2)
	"data\\texture\\ok.png",			// �E�o�\
	"data\\texture\\hold.jpg",			// �E�o�̗��߃Q�[�W
};

//++++++++++++++++++++++++++++++++++++++++++++++++++++
//�A�C�e���̍\����
//++++++++++++++++++++++++++++++++++++++++++++++++++++
typedef struct
{
	D3DXVECTOR3 pos;				// �ʒu
	D3DXVECTOR3 rot;				// ����(�p�x)
	D3DXVECTOR3 VtxMaxBillboard;	// �ő吔
	D3DXVECTOR3 VtxMinBillboard;	// �ŏ���
	D3DXMATRIX mtxWorld;			// ���[���h�}�g���b�N�X
	TYPE nType;						// ���
	bool bDisplay;					// 
	bool bTest;						//
	bool bUse;						// �g�p���Ă��邩�ǂ���
	D3DXVECTOR3 size;				// �傫��
}Billboard;

//++++++++++++++++++++++++++++++++++++++++++++++++++++
//�v���g�^�C�v�錾
//++++++++++++++++++++++++++++++++++++++++++++++++++++
void InitBillboard();
void UninitBillboard();
void UpdateBillboard();
void DrawBillboard();
void SetBillboard(D3DXVECTOR3 pos, D3DXVECTOR3 dir, TYPE nType, D3DXVECTOR3 size);

#endif