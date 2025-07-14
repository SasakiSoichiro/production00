//====================================================
//
// �A�C�e�������̏��� [explain.h]
// Author : chikada shouya
//
//====================================================
#ifndef _EXPLAIN_H_
#define _EXPLAIN_H_

#include "main.h"

//++++++++++++++++++++++++++++++++++++++++++++++++++++
//�}�N����`
//++++++++++++++++++++++++++++++++++++++++++++++++++++
#define MAX_ITEMUI (20)		//�A�C�e���̐�

//++++++++++++++++++++++++++++++++++++++++++++++++++++
//�A�C�e��UI�̃e�N�X�`�����
//++++++++++++++++++++++++++++++++++++++++++++++++++++
typedef enum
{
	EXPLAINTYPE_WATCH,		//	�������v	0
	EXPLAINTYPE_HEAL,		//	��ÃL�b�g	1
	EXPLAINTYPE_LIGHT,		//	�����d��	2
	EXPLAINTYPE_MAX,
}EXPLAINTYPE;

static const char* EXPLAIN_TEXTURE[EXPLAINTYPE_MAX] =
{
	"data\\texture\\explanation1.png",	//	�������v	0
	"data\\texture\\life.png",			//	��ÃL�b�g	1
	"data\\texture\\light.png",			//	�����d��	2
};

//++++++++++++++++++++++++++++++++++++++++++++++++++++
//�A�C�e��UI�̍\����
//++++++++++++++++++++++++++++++++++++++++++++++++++++
typedef struct
{
	D3DXVECTOR3 pos;
	EXPLAINTYPE aType;
	bool bUse;
	bool bLook;
	float fWidth;			// ����
	float fHeight;			// ����
}EXPLAIN;

//++++++++++++++++++++++++++++++++++++++++++++++++++++
//�v���g�^�C�v�錾
//++++++++++++++++++++++++++++++++++++++++++++++++++++
void InitExplain();
void UninitExplain();
void UpdateExplain();
void DrawExplain();
void SetExplain(D3DXVECTOR3 pos, EXPLAINTYPE aType, float fWidth, float fHeight);
EXPLAIN* GetExplain();
#endif
