//=============================================================================
//
// 粒子の処理 [Particle.cpp]
// Author : yabuki yukito
//
//=============================================================================

#include "Particle.h"
#include "effect.h"

//マクロ定義
#define MAX_PARTICLE (128)																//パーティクルの最大数

//グローバル変数
Particle g_aParticle[MAX_PARTICLE];														//パーティクルの情報
LPDIRECT3DTEXTURE9 g_pTextureParticle = NULL;											//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffParticle = NULL;										//頂点バッファへのポインタ

//=============================================================================
//粒子の初期化処理
//=============================================================================
void InitParticle(void)
{
	//全パーティクル分初期化
	for (int nCnt = 0; nCnt < MAX_PARTICLE; nCnt++)
	{
		g_aParticle[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aParticle[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aParticle[nCnt].col = D3DXCOLOR(1.0f, 1.0, 1.0f, 1.0f);
		g_aParticle[nCnt].nLife = 0;
		g_aParticle[nCnt].bUse = false;
	}

}

//=============================================================================
//粒子の終了処理
//=============================================================================
void UninitParticle(void)
{

}

//=============================================================================
//粒子の更新処理
//=============================================================================
void UpdateParticle(void)
{
	for (int nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{

		if (g_aParticle[nCntParticle].bUse == true)
		{
			for (int nCntApper = 0; nCntApper < 3; nCntApper++)
			{
				//位置更新
				g_aParticle[nCntParticle].pos += g_aParticle[nCntParticle].move;

				D3DXVECTOR3 pos = g_aParticle[nCntParticle].pos;



				D3DXVECTOR3 move = g_aParticle[nCntParticle].move;

				D3DXCOLOR col = g_aParticle[nCntParticle].col;

				int nLife = rand() % g_aParticle[nCntParticle].nLife + 60;

				//ライフの減少
				g_aParticle[nCntParticle].nLife--;

				if (g_aParticle[nCntParticle].nLife <= 0)
				{
					g_aParticle[nCntParticle].bUse = false;
				}

				SetEffect(pos, move, nLife, col);
			}
		}
	}
}

//=============================================================================
//粒子の描画処理
//=============================================================================
void DrawParticle(void)
{

}

//=============================================================================
//粒子の設定処理
//=============================================================================
void SetParticle(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, int nLife)
{
	for (int nCnt = 0; nCnt < MAX_PARTICLE; nCnt++)
	{
		if (g_aParticle[nCnt].bUse == false)
		{
			g_aParticle[nCnt].pos = pos;
			g_aParticle[nCnt].move = move;
			g_aParticle[nCnt].col = col;
			g_aParticle[nCnt].nLife = nLife;
			g_aParticle[nCnt].bUse = true;
			break;
		}
	}
}
