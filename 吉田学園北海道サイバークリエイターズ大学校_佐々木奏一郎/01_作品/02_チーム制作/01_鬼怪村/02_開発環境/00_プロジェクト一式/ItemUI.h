//=============================================================================
//
//	�A�C�e�����̏��� [itemUI.h]
// Author : ���X�ؑt��Y
//
//=============================================================================
#ifndef _ITEMUI_H_//���̃}�N����`������Ă��Ȃ�������
#define _ITEMUI_H_//2�d�C���N���[�h�h�~�̃}�N����`

#include "main.h"

// �A�C�e��UI�̎��
typedef enum
{
	ITEM_FLAME = 0,
	ITEM_NAGINATA,
	ITEM_HEAL,
	ITEM_POCKETWATCH,
	ITEM_USEDNAGINATA,
	ITEM_USEDHEAL,
	ITEM_USEDPOCKETWATCH,
	ITEM_FLASHLIGHT,
	ITEM_MAX
}ITEMUI;

// �A�C�e��UI�\����
typedef struct
{
	D3DXVECTOR3 pos;	// �ʒu
	D3DXVECTOR3 move;	// ����
	float fWidth;		// ��
	float fHeight;		// ����
	int nType;			// �u���b�N�̃^�C�v
	bool bUse;			// �g�p���Ă��邩�ǂ���
}ItemUI;

// �A�C�e���̃e�N�X�`��
static const char* ITEMUI_TEXTURE[ITEM_MAX] =
{
	"data\\texture\\waku.png",			// �g
	"data\\texture\\naginata.png",		// �㓁
	"data\\texture\\heal.png",			// ��
	"data\\texture\\time.png",			// �������v
	"data\\texture\\Nonaginata.png",	// �㓁(�g�p��)
	"data\\texture\\Noheal.png",		// ��(�g�p��)
	"data\\texture\\Notime.png",		// �������v(�g�p��)
	"data\\texture\\flashPicture.png",	// �����d��(�g�p��)
};

// �v���g�^�C�v�錾
void InitItemUI(void);
void UninitItemUI(void);
void UpdateItemUI();
void DrawItemUI(void);
void SetItemUI(int nType);
void SetUsedItemUI(int nType);
ItemUI *GetItemUI();
int GetSelect();
#endif