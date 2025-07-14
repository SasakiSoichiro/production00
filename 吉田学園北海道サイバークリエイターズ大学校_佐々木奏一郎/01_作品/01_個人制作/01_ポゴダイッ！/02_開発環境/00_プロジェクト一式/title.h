//=============================================================================
//
//	タイトル処理 [title.h]
// Author : 佐々木奏一郎
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
//プロトタイプ宣言
void InitTitle(void);
void UninitTitle(void);
void UpdateTitle(void);
void DrawTitle(void);
void SetTitle(int nType ,D3DXVECTOR3 pos);
void TitleFlash(int nType);
#endif