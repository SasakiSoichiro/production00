//====================================================
//
// アイテム表示の処理 [KeyUI.h]
// Author : chikada shouya
//
//====================================================
#ifndef _KEYUI_H_
#define _KEYUI_H_

#include "main.h"

//++++++++++++++++++++++++++++++++++++++++++++++++++++
//マクロ定義
//++++++++++++++++++++++++++++++++++++++++++++++++++++
#define MAX_WIDTH (150)  //UIの横幅
#define MAX_HEIGHT (100) //UIの高さ
#define MAX_ITEMUI (20)   //アイテムの数

//++++++++++++++++++++++++++++++++++++++++++++++++++++
//アイテムUIのテクスチャ状態
//++++++++++++++++++++++++++++++++++++++++++++++++++++
typedef enum
{
	ITEMKEYUITYPE_NO5,			//	鍵(0/2)				0
	ITEMKEYUITYPE_YESNO5,		//	鍵(1/2)				1
	ITEMKEYUITYPE_5,			//	鍵(完成)			2
	ITEMKEYUITYPE_MAX,
}ITEMKEYUITYPE;

static const char* ITEMKEYUI_TEXTURE[ITEMKEYUITYPE_MAX] =
{
	"data\\texture\\NOkagi.png",		// 鍵(0/2)			0
	"data\\texture\\YesNoKagi.png",		// 鍵(1/2)			1
	"data\\texture\\Perfectkagi.png",	// 鍵(完成)			2

};

//++++++++++++++++++++++++++++++++++++++++++++++++++++
//アイテムUIの構造体
//++++++++++++++++++++++++++++++++++++++++++++++++++++
typedef struct
{
	D3DXVECTOR3 pos;
	ITEMKEYUITYPE aType;
	bool bUse;
	float fWidth; // 横幅
	float fHeight;// 高さ
}ITEMKEYUI;

//++++++++++++++++++++++++++++++++++++++++++++++++++++
//プロトタイプ宣言
//++++++++++++++++++++++++++++++++++++++++++++++++++++
void InitKeyUI();
void UninitKeyUI();
void UpdateKeyUI();
void DrawKeyUI();
void SetKeyUI(D3DXVECTOR3 pos, ITEMKEYUITYPE aType, float fWidth, float fHeight);
#endif