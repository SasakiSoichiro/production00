//=============================================================================
//
//    リザルト処理 [result.h]
//    Author : ryuusei.hirata
//
//=============================================================================
#ifndef _RESULT_H_
#define _RESULT_H_

#include "main.h"
#include "game.h"
#include "input.h"

// 構造体
typedef struct
{
	D3DXVECTOR3 pos;	// 位置
	D3DXCOLOR col;		// 色
	bool bUse;			// 使われてるか
	float fHeight;		// 高さ
	float fWidth;		// 幅
}Result;

// プロトタイプ宣言
void InitResult(void);
void UninitResult(void);
void UpdateResult(void);
void DrawResult(void);

#endif // !_RESULT_H_
