//====================================================
//
// 解除の処理 [Cancellation.h]
// Author : yabuki yukito
//
//====================================================

#ifndef _CANCELLATION_H_
#define _CANCELLATION_H_

#include "main.h"

// 解除テクスチャの種類
typedef enum
{
	TEX_0 = 0,
	TEX_1,
	TEX_MAX
}TEXTYPE;

// 構造体
typedef struct
{
	D3DXVECTOR3 pos;	// 位置
	bool bUse;			// 使用しているかどうか
	float fCnt;			// 
	bool bKeyhave;		// 
	int nType;			// 種類
}Cance;

static const char* X_TEX[TEX_MAX] =
{
	"data\\texture\\Cancellation.png",
	"data\\texture\\kaijoB.png",
};

// プロトタイプ宣言
void InitCancellation(void);
void UinitCancellation(void);
void UpdateCancellation(void);
void DrawCancellation(void);

#endif
