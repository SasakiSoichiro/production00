//====================================================
//
// アイテム表示の処理 [buttonUI.h]
// Author : chikada shouya
//
//====================================================

#ifndef _BUTTONUI_H_
#define _BUTTONUI_H_

#include "main.h"

//++++++++++++++++++++++++++++++++++++++++++++++++++++
// マクロ定義
//++++++++++++++++++++++++++++++++++++++++++++++++++++
#define MAX_WIDTH (150)		// UIの横幅
#define MAX_HEIGHT (100)	// UIの高さ
#define MAX_BUTTONUI (20)   // アイテムの数

//++++++++++++++++++++++++++++++++++++++++++++++++++++
// アイテムUIのテクスチャ状態
//++++++++++++++++++++++++++++++++++++++++++++++++++++
typedef enum
{
	BUTTONUITYPE_BUTTON_Y,		// ボタン(X)				0
	BUTTONUITYPE_BUTTON_X,		// ボタン(Y)				1
	BUTTONUITYPE_MAX,
}BUTTONUITYPE;

static const char* BUTTONUITYPE__TEXTURE[BUTTONUITYPE_MAX] =
{
	"data\\texture\\button1.png",		// ボタン(X)			0
	"data\\texture\\buttonX1.png",		// ボタン(Y)			1
};

//++++++++++++++++++++++++++++++++++++++++++++++++++++
// アイテムUIの構造体
//++++++++++++++++++++++++++++++++++++++++++++++++++++
typedef struct
{
	D3DXVECTOR3 pos;		// 位置
	BUTTONUITYPE aType;		// 種類
	bool bUse;				// 使用しているかどうか
	float fWidth;			// 横幅
	float fHeight;			// 高さ
}BUTTONUI;

//++++++++++++++++++++++++++++++++++++++++++++++++++++
// プロトタイプ宣言
//++++++++++++++++++++++++++++++++++++++++++++++++++++
void InitButtonUI();
void UninitButtonUI();
void UpdateButtonUI();
void DrawButtonUI();
void SetButtonUI(D3DXVECTOR3 pos, BUTTONUITYPE aType, float fWidth, float fHeight);
#endif