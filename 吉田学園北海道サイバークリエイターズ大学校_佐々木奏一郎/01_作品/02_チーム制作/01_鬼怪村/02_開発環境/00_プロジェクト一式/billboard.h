//====================================================
//
// 木の処理 [billboard.h]
// Author : yabuki yukito
//
//====================================================

#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

#include "main.h"

//++++++++++++++++++++++++++++++++++++++++++++++++++++
// マクロ定義
//++++++++++++++++++++++++++++++++++++++++++++++++++++
#define MAX_BILLBOARD (15)

//++++++++++++++++++++++++++++++++++++++++++++++++++++
// アイテムの種類
//++++++++++++++++++++++++++++++++++++++++++++++++++++
typedef enum
{
	BILLBOARDTYPE_0,	// 木
	BILLBOARDTYPE_1,	// 拾う
	BILLBOARDTYPE_2,	// 鍵を持っていない(0/2)
	BILLBOARDTYPE_3,	// 鍵を持っているが1つのみ(1/2)
	BILLBOARDTYPE_4,	// 脱出可能
	BILLBOARDTYPE_5,	// 脱出する溜めゲージ
	BILLBOARDTYPE_MAX	
}TYPE;

static const char* ITEM_TEXTURE[BILLBOARDTYPE_MAX] =
{
	"data\\texture\\Wood.png",			// 木の画像
	"data\\texture\\itembilbord.jpg",	// 拾う画像
	"data\\texture\\no2.png",			// 鍵を持っていない(0/2)
	"data\\texture\\no1.png",			// 鍵を持っているが1つのみ(1/2)
	"data\\texture\\ok.png",			// 脱出可能
	"data\\texture\\hold.jpg",			// 脱出の溜めゲージ
};

//++++++++++++++++++++++++++++++++++++++++++++++++++++
//アイテムの構造体
//++++++++++++++++++++++++++++++++++++++++++++++++++++
typedef struct
{
	D3DXVECTOR3 pos;				// 位置
	D3DXVECTOR3 rot;				// 向き(角度)
	D3DXVECTOR3 VtxMaxBillboard;	// 最大数
	D3DXVECTOR3 VtxMinBillboard;	// 最小数
	D3DXMATRIX mtxWorld;			// ワールドマトリックス
	TYPE nType;						// 種類
	bool bDisplay;					// 
	bool bTest;						//
	bool bUse;						// 使用しているかどうか
	D3DXVECTOR3 size;				// 大きさ
}Billboard;

//++++++++++++++++++++++++++++++++++++++++++++++++++++
//プロトタイプ宣言
//++++++++++++++++++++++++++++++++++++++++++++++++++++
void InitBillboard();
void UninitBillboard();
void UpdateBillboard();
void DrawBillboard();
void SetBillboard(D3DXVECTOR3 pos, D3DXVECTOR3 dir, TYPE nType, D3DXVECTOR3 size);

#endif