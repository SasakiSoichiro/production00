//=============================================================================
//
// スローモーション処理 [slow.h]
// Author : 佐々木奏一郎
//
//=============================================================================
#ifndef _SLOW_H_
#define _SLOW_H_
#include "main.h"

#define SLOW (4);


//	フェードの状態
typedef enum
{
	SLOWFADE_NONE = 0,	//	何もしていない状態
	SLOWFADE_IN,		//	フェードイン状態
	SLOWFADE_OUT,		//	フェードアウト状態
	SLOWFADE_MAX
}SLOWFADE;

//構造体
typedef struct
{
	float fMulti;
	float fDivi;
	int nMulti;
	int nDivi;
	bool bUse;
	D3DXCOLOR color;
	SLOWFADE fade;
}Slow;

//プロトタイプ宣言
void InitSlow(void);
void UninitSlow(void);
void UpdateSlow(void);
void DrawSlow(void);
void SetSlow(void);
Slow*GetSlow(void);

#endif