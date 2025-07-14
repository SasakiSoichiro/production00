//=============================================================================
//
//	2D表示させるUI処理 [etcUI.h]
// Author : 佐々木奏一郎
//
//=============================================================================
#ifndef _ETCUI_H_//このマクロ定義がされていなかったら
#define _ETCUI_H_//2重インクルード防止のマクロ定義
#include "main.h"

// UIの種類
typedef enum
{
	ETCUI_DASH=0,
	ETCUI_KEY,
	ETCUI_MASTER,
	ETCUI_MAX
}ETCUI;

// UIの構造体
typedef struct
{
	D3DXVECTOR3 pos;	// 位置
	D3DXVECTOR3 move;	// 動き
	float fWidth;		// 幅
	float fHeight;		// 高さ
	int nType;			// ブロックのタイプ
	bool bUse;			// 使用しているかどうか
}EtcUI;

// テクスチャの種類
static const char* ETCUI_TEXTURE[ETCUI_MAX] =
{
	"data\\texture\\dash00.png",		// 枠
	"data\\texture\\naginata.png",		// 薙刀
	"data\\texture\\heal.png",			// 回復
};

// プロトタイプ宣言
void InitEtcUI(void);
void UninitEtcUI(void);
void UpdateEtcUI();
void DrawEtcUI(void);
void SetEtcUI(int nType, D3DXVECTOR3 pos, float fHeight, float fWidth);
#endif