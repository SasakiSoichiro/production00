//=============================================================================
//
//    解除ゲージ処理 [gauge.h]
//    Author : Chikada
//
//=============================================================================
#ifndef _GAUGE_H_
#define _GAUGE_H_

#include "main.h"

// ゲージの構造体
typedef struct
{
	D3DXVECTOR3 pos;	// 位置
	bool bUse;			// 使用しているかどうか
	float fCnt;
	float fCnt1;
	bool bKeyhave;
}Gauge;

// プロトタイプ宣言
void InitGauge(void);
void UinitGauge(void);
void UpdateGauge(void);
void DrawGauge(void);
void SetGauge(D3DXVECTOR3 pos);

#endif // !_GAUGE_H_
