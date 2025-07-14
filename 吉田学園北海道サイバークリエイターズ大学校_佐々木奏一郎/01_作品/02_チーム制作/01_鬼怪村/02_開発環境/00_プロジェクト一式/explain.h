//====================================================
//
// アイテム説明の処理 [explain.h]
// Author : chikada shouya
//
//====================================================
#ifndef _EXPLAIN_H_
#define _EXPLAIN_H_

#include "main.h"

//++++++++++++++++++++++++++++++++++++++++++++++++++++
//マクロ定義
//++++++++++++++++++++++++++++++++++++++++++++++++++++
#define MAX_ITEMUI (20)		//アイテムの数

//++++++++++++++++++++++++++++++++++++++++++++++++++++
//アイテムUIのテクスチャ状態
//++++++++++++++++++++++++++++++++++++++++++++++++++++
typedef enum
{
	EXPLAINTYPE_WATCH,		//	懐中時計	0
	EXPLAINTYPE_HEAL,		//	医療キット	1
	EXPLAINTYPE_LIGHT,		//	懐中電灯	2
	EXPLAINTYPE_MAX,
}EXPLAINTYPE;

static const char* EXPLAIN_TEXTURE[EXPLAINTYPE_MAX] =
{
	"data\\texture\\explanation1.png",	//	懐中時計	0
	"data\\texture\\life.png",			//	医療キット	1
	"data\\texture\\light.png",			//	懐中電灯	2
};

//++++++++++++++++++++++++++++++++++++++++++++++++++++
//アイテムUIの構造体
//++++++++++++++++++++++++++++++++++++++++++++++++++++
typedef struct
{
	D3DXVECTOR3 pos;
	EXPLAINTYPE aType;
	bool bUse;
	bool bLook;
	float fWidth;			// 横幅
	float fHeight;			// 高さ
}EXPLAIN;

//++++++++++++++++++++++++++++++++++++++++++++++++++++
//プロトタイプ宣言
//++++++++++++++++++++++++++++++++++++++++++++++++++++
void InitExplain();
void UninitExplain();
void UpdateExplain();
void DrawExplain();
void SetExplain(D3DXVECTOR3 pos, EXPLAINTYPE aType, float fWidth, float fHeight);
EXPLAIN* GetExplain();
#endif
