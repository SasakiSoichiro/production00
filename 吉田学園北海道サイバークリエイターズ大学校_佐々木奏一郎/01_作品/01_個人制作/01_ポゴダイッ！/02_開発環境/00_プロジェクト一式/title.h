//=============================================================================
//
//	�^�C�g������ [title.h]
// Author : ���X�ؑt��Y
//
//=============================================================================
#ifndef _TITLE_H_
#define _TITLE_H_
#include "main.h"
typedef enum
{
	TITLE_1=0,
	TITLE_2,
	TITLE_MAX
}TITLE;
typedef enum
{
	TITLESTATE_NONE=0,
	TITLESTATE_FLASH,
	TITLESTATE_MAX
}TITLESTATE;
//�v���g�^�C�v�錾
void InitTitle(void);
void UninitTitle(void);
void UpdateTitle(void);
void DrawTitle(void);
void SetTitle(int nType ,D3DXVECTOR3 pos);
void TitleFlash(int nType);
#endif