//====================================================
//
// �A�C�e���\���̏��� [KeyUI.h]
// Author : chikada shouya
//
//====================================================
#ifndef _KEYUI_H_
#define _KEYUI_H_

#include "main.h"

//++++++++++++++++++++++++++++++++++++++++++++++++++++
//�}�N����`
//++++++++++++++++++++++++++++++++++++++++++++++++++++
#define MAX_WIDTH (150)  //UI�̉���
#define MAX_HEIGHT (100) //UI�̍���
#define MAX_ITEMUI (20)   //�A�C�e���̐�

//++++++++++++++++++++++++++++++++++++++++++++++++++++
//�A�C�e��UI�̃e�N�X�`�����
//++++++++++++++++++++++++++++++++++++++++++++++++++++
typedef enum
{
	ITEMKEYUITYPE_NO5,			//	��(0/2)				0
	ITEMKEYUITYPE_YESNO5,		//	��(1/2)				1
	ITEMKEYUITYPE_5,			//	��(����)			2
	ITEMKEYUITYPE_MAX,
}ITEMKEYUITYPE;

static const char* ITEMKEYUI_TEXTURE[ITEMKEYUITYPE_MAX] =
{
	"data\\texture\\NOkagi.png",		// ��(0/2)			0
	"data\\texture\\YesNoKagi.png",		// ��(1/2)			1
	"data\\texture\\Perfectkagi.png",	// ��(����)			2

};

//++++++++++++++++++++++++++++++++++++++++++++++++++++
//�A�C�e��UI�̍\����
//++++++++++++++++++++++++++++++++++++++++++++++++++++
typedef struct
{
	D3DXVECTOR3 pos;
	ITEMKEYUITYPE aType;
	bool bUse;
	float fWidth; // ����
	float fHeight;// ����
}ITEMKEYUI;

//++++++++++++++++++++++++++++++++++++++++++++++++++++
//�v���g�^�C�v�錾
//++++++++++++++++++++++++++++++++++++++++++++++++++++
void InitKeyUI();
void UninitKeyUI();
void UpdateKeyUI();
void DrawKeyUI();
void SetKeyUI(D3DXVECTOR3 pos, ITEMKEYUITYPE aType, float fWidth, float fHeight);
#endif