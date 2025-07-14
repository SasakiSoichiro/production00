//=============================================================================
//
//    タイトル処理 [title.h]
//    Author : ryuusei.hirata
//
//=============================================================================
#ifndef _TITLE_H_
#define _TITLE_H_

#include "main.h"
#include "input.h"
#include "game.h"

typedef enum
{
	TITLE_ONE = 0,
	TITLE_TWO,
	TITLE_THREE,
	TITLE_MAX
}TITLE;

// 列挙
typedef enum
{
	TITLEMODE_NONE = 0,
	TITLEMODE_FLASH,
	TITLEMODE_MAX
}TITLEMODE;

// 構造体
typedef struct
{
	D3DXVECTOR3 pos;	// 座標
	D3DXVECTOR3 col;	// カラー
	int nType;			// 種類
	bool bUse;			// 使われてるか
	float fHeight;		// 高さ
	float fWidth;		// 幅
	TITLEMODE state;	// 状態
}Title;

// プロトタイプ
void InitTitle(void);
void UninitTitle(void);
void UpdateTitle(void);
void DrawTitle(void);
void SetTitle(int nType, D3DXVECTOR3 pos);

#endif // !_TITLE_H_
