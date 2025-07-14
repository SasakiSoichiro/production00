//=============================================================================
//
//	エフェクト処理 [effect.h]
// Author : 佐々木奏一郎
//
//=============================================================================
#ifndef _EFFECT_H_//このマクロ定義がされていなかったら
#define _EFFECT_H_//2銃インクルード防止のマクロ定義
#include "main.h"
//エフェクトの種類
typedef enum
{
	EFFECTTYPE_PLAYER=0,
	EFFECTTYPE_ENEMY,
	EFFECTTYPE_PARTICLE1,
	EFFECTTYPE_PARTICLE2,
	EFFECTTYPE_MAX
}EFFECTTYPE;
//プロトタイプ宣言
void InitEffect(void);
void UninitEffect(void);
void UpdateEffect(void);
void DrawEffect(void);
void SetEffect(D3DXVECTOR3 pos, D3DXVECTOR3 move,D3DXCOLOR col,float fRadius,int nLife,	EFFECTTYPE type);
#endif