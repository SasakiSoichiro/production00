//=============================================================================
//
//		懐中電灯  flashlight.cpp
//		Auther:Sasaki Soichiro
//
//=============================================================================

#ifndef _FLASHLIGHT_H_
#define _FLASHLIGHT_H_

#include "main.h"

// マクロ定義
#define MAX_FLASH (1)

// 懐中電灯の構造体
typedef struct
{
	D3DLIGHT9 light;	//	ライト情報
	bool bLight;
}FLASHLIGHT;

// プロトタイプ宣言
void InitFlashLight(void);
void UninitFlashLight(void);
void UpdateFlashLight(void);
FLASHLIGHT* GetFlashLight(void);
void InitFlashGlobal(int nCnt);
void bFlashTRUE(int nCnt);
void bFlashFALSE(int nCnt);

#endif // !_LIGHT_H_