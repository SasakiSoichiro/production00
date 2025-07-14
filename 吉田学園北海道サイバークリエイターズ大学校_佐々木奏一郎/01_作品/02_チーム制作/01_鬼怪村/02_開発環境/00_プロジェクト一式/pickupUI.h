//=============================================================================
//
//	拾うUI処理 [pickupUI.h]
// Author : 佐々木奏一郎
//
//=============================================================================
#ifndef _PICKUPUI_H_//このマクロ定義がされていなかったら
#define _PICKUPUI_H_//2重インクルード防止のマクロ定義
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


//プロトタイプ宣言
void InitPickUpUI(void);
void UninitPickUpUI(void);
void UpdatePickUpUI(void);
void DrawPickUpUI(void);
int SetPickUpUI(D3DXVECTOR3 pos, D3DXVECTOR3 dir);

#endif