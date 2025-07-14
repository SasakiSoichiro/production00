//=============================================================================
//
//	ノイズ処理 [noise.h]
// Author : 佐々木奏一郎
//
//=============================================================================
#ifndef _NOIZ_H_//このマクロ定義がされていなかったら
#define _NOIZ_H_//2銃インクルード防止のマクロ定義
#include "main.h"

typedef enum
{
	NOISE_A = 0,
	NOISE_B,
	NOISE_C,
	NOISE_MAX
}NOIZ;

typedef struct
{
	D3DXVECTOR3 pos;	//位置
	float fWidth;		//幅
	float fHeight;		//高さ
	int nType;			//ブロックのタイプ
	bool bUse;			//使用しているかどうか
}Noise;

static const char* NOISE_TEXTURE[NOISE_MAX] =
{
	"data\\texture\\noise00.png",			//ブロック
	"data\\texture\\noise01.png",			//ボタン
	"data\\texture\\noise02.png",			//ボタン
};

//プロトタイプ宣言
void InitNoise(void);
void UninitNoise(void);
void UpdateNoise(void);
void DrawNoise(void);
void RandNoise(float *U, float *V,int nCnt);
#endif