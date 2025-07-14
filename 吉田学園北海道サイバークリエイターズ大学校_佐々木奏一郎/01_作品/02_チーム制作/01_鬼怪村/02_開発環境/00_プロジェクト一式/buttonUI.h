//====================================================
//
// �A�C�e���\���̏��� [buttonUI.h]
// Author : chikada shouya
//
//====================================================

#ifndef _BUTTONUI_H_
#define _BUTTONUI_H_

#include "main.h"

//++++++++++++++++++++++++++++++++++++++++++++++++++++
// �}�N����`
//++++++++++++++++++++++++++++++++++++++++++++++++++++
#define MAX_WIDTH (150)		// UI�̉���
#define MAX_HEIGHT (100)	// UI�̍���
#define MAX_BUTTONUI (20)   // �A�C�e���̐�

//++++++++++++++++++++++++++++++++++++++++++++++++++++
// �A�C�e��UI�̃e�N�X�`�����
//++++++++++++++++++++++++++++++++++++++++++++++++++++
typedef enum
{
	BUTTONUITYPE_BUTTON_Y,		// �{�^��(X)				0
	BUTTONUITYPE_BUTTON_X,		// �{�^��(Y)				1
	BUTTONUITYPE_MAX,
}BUTTONUITYPE;

static const char* BUTTONUITYPE__TEXTURE[BUTTONUITYPE_MAX] =
{
	"data\\texture\\button1.png",		// �{�^��(X)			0
	"data\\texture\\buttonX1.png",		// �{�^��(Y)			1
};

//++++++++++++++++++++++++++++++++++++++++++++++++++++
// �A�C�e��UI�̍\����
//++++++++++++++++++++++++++++++++++++++++++++++++++++
typedef struct
{
	D3DXVECTOR3 pos;		// �ʒu
	BUTTONUITYPE aType;		// ���
	bool bUse;				// �g�p���Ă��邩�ǂ���
	float fWidth;			// ����
	float fHeight;			// ����
}BUTTONUI;

//++++++++++++++++++++++++++++++++++++++++++++++++++++
// �v���g�^�C�v�錾
//++++++++++++++++++++++++++++++++++++++++++++++++++++
void InitButtonUI();
void UninitButtonUI();
void UpdateButtonUI();
void DrawButtonUI();
void SetButtonUI(D3DXVECTOR3 pos, BUTTONUITYPE aType, float fWidth, float fHeight);
#endif