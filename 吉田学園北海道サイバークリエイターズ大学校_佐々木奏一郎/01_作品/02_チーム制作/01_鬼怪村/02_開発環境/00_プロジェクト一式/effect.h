//=============================================================================
//
// エフェクト処理 [effect.h]
// Author :Marina Harada
//
//=============================================================================
#ifndef _EFFECT_H_ //このマクロ定義がされていなかったら
#define _EFFECT_H_ //２重インクルード防止のマクロ定義

#include"main.h"

//マクロ定義
#define MAX_EFFECT (128)
#define EFC_LIFE (20)

//エフェクトの構造体
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 move;
	D3DXVECTOR3 rot;
	D3DXMATRIX mtxWorld;
	D3DXCOLOR col;
	int nLife;
	bool buse;
}Effect;

//プロトタイプ宣言
void InitEffect(void);
void UninitEffect(void);
void UpdateEffect(void);
void DrawEffect(void);
void SetEffect(D3DXVECTOR3 pos, D3DXVECTOR3 dir, int nLife, D3DXCOLOR col);

#endif