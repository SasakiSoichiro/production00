//=============================================================================
//
//	アイテム持つの処理 [itemUI.h]
// Author : 佐々木奏一郎
//
//=============================================================================
#ifndef _ITEMUI_H_//このマクロ定義がされていなかったら
#define _ITEMUI_H_//2重インクルード防止のマクロ定義

#include "main.h"

// アイテムUIの種類
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

// アイテムUI構造体
typedef struct
{
	D3DXVECTOR3 pos;	// 位置
	D3DXVECTOR3 move;	// 動き
	float fWidth;		// 幅
	float fHeight;		// 高さ
	int nType;			// ブロックのタイプ
	bool bUse;			// 使用しているかどうか
}ItemUI;

// アイテムのテクスチャ
static const char* ITEMUI_TEXTURE[ITEM_MAX] =
{
	"data\\texture\\waku.png",			// 枠
	"data\\texture\\naginata.png",		// 薙刀
	"data\\texture\\heal.png",			// 回復
	"data\\texture\\time.png",			// 懐中時計
	"data\\texture\\Nonaginata.png",	// 薙刀(使用済)
	"data\\texture\\Noheal.png",		// 回復(使用済)
	"data\\texture\\Notime.png",		// 懐中時計(使用済)
	"data\\texture\\flashPicture.png",	// 懐中電灯(使用済)
};

// プロトタイプ宣言
void InitItemUI(void);
void UninitItemUI(void);
void UpdateItemUI();
void DrawItemUI(void);
void SetItemUI(int nType);
void SetUsedItemUI(int nType);
ItemUI *GetItemUI();
int GetSelect();
#endif