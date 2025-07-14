//=============================================================================
//
//	エフェクト処理 [effect.cpp]
// Author : 佐々木奏一郎
//
//=============================================================================
#include "effect.h"
#include "main.h"
#include "input.h"
#include "player.h"
//マクロ定義
#define MAX_EFFECT (4096)//エフェクトの最大数
#define MAX_SPEED (5)//弾の速さ
//弾構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;//位置
	D3DXVECTOR3 move;
	D3DXCOLOR col;//色
	float fRadius;//半径
	int nLife;//寿命
	EFFECTTYPE type;//種類
	float fAlpha;
	bool bUse;//使用しているかどうか
}Effect;
//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureEffect = NULL;//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEffect = NULL;//頂点バッファへのポインタ
Effect g_aEffect[MAX_EFFECT];//エフェクトの情報

//弾の初期化処理
void InitEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntEffect;
	//デバイスの取得
	pDevice = GetDevice();
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\effect000.jpg",
		&g_pTextureEffect);
	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		g_aEffect[nCntEffect].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEffect[nCntEffect].col = D3DXCOLOR(0.0f,0.0f, 0.0f, 0.0f);
		g_aEffect[nCntEffect].fRadius = 0.0f;
		g_aEffect[nCntEffect].nLife = NULL;
		g_aEffect[nCntEffect].move= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEffect[nCntEffect].fAlpha = 1.0f;
		g_aEffect[nCntEffect].type = EFFECTTYPE_PLAYER;
		g_aEffect[nCntEffect].bUse = false;
	}
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_EFFECT,//(sizeof(VERTEX_2D)*必要な頂点数
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEffect,
		NULL);
	VERTEX_2D* pVtx =0;
	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x - 40, g_aEffect[nCntEffect].pos.y - 40, 0.0f);//←右回りで設定する
		pVtx[1].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x + 40, g_aEffect[nCntEffect].pos.y - 40, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x - 40, g_aEffect[nCntEffect].pos.y + 40, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x + 40, g_aEffect[nCntEffect].pos.y + 40, 0.0f);
		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		//頂点カラーの設定　　　　
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f,0.0f);//←右回りで設定する
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx += 4;//頂点データのポインタを4つ分集める
	}
	//頂点バッファをアンロックする
	g_pVtxBuffEffect->Unlock();
}
void UninitEffect(void)
{
	//テクスチャの破棄
	if (g_pTextureEffect != NULL)
	{
		g_pTextureEffect->Release();
		g_pTextureEffect = NULL;
	}
	//頂点バッファの破棄
	if (g_pVtxBuffEffect != NULL)
	{
		g_pVtxBuffEffect->Release();
		g_pVtxBuffEffect = NULL;
	}
}
void UpdateEffect(void)
{
	VERTEX_2D* pVtx = 0;
	int nCntEffect;
	int nSize=40;
	float fAlpha[MAX_EFFECT] = {};
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_aEffect[nCntEffect].bUse == true)
		{//弾が使用されている
			switch (g_aEffect[nCntEffect].type)
			{
			case EFFECTTYPE_PLAYER:
				//頂点カラーの設定
				pVtx[0].col = D3DXCOLOR(g_aEffect[nCntEffect].col.r, g_aEffect[nCntEffect].col.g,g_aEffect[nCntEffect].fAlpha, g_aEffect[nCntEffect].fAlpha);
				pVtx[1].col = D3DXCOLOR(g_aEffect[nCntEffect].col.r, g_aEffect[nCntEffect].col.g,g_aEffect[nCntEffect].fAlpha, g_aEffect[nCntEffect].fAlpha);
				pVtx[2].col = D3DXCOLOR(g_aEffect[nCntEffect].col.r, g_aEffect[nCntEffect].col.g,g_aEffect[nCntEffect].fAlpha, g_aEffect[nCntEffect].fAlpha);
				pVtx[3].col = D3DXCOLOR(g_aEffect[nCntEffect].col.r, g_aEffect[nCntEffect].col.g,g_aEffect[nCntEffect].fAlpha, g_aEffect[nCntEffect].fAlpha);
				break;
			case EFFECTTYPE_ENEMY:
				//頂点カラーの設定
				pVtx[0].col = D3DXCOLOR(g_aEffect[nCntEffect].col.r, g_aEffect[nCntEffect].fAlpha, g_aEffect[nCntEffect].col.b, g_aEffect[nCntEffect].fAlpha);
				pVtx[1].col = D3DXCOLOR(g_aEffect[nCntEffect].col.r, g_aEffect[nCntEffect].fAlpha, g_aEffect[nCntEffect].col.b, g_aEffect[nCntEffect].fAlpha);
				pVtx[2].col = D3DXCOLOR(g_aEffect[nCntEffect].col.r, g_aEffect[nCntEffect].fAlpha, g_aEffect[nCntEffect].col.b, g_aEffect[nCntEffect].fAlpha);
				pVtx[3].col = D3DXCOLOR(g_aEffect[nCntEffect].col.r, g_aEffect[nCntEffect].fAlpha, g_aEffect[nCntEffect].col.b, g_aEffect[nCntEffect].fAlpha);
				break;
			case EFFECTTYPE_PARTICLE1:
				//頂点カラーの設定
				pVtx[0].col = D3DXCOLOR(g_aEffect[nCntEffect].nLife* g_aEffect[nCntEffect].col.r/30.0f, g_aEffect[nCntEffect].col.g, g_aEffect[nCntEffect].col.b, g_aEffect[nCntEffect].fAlpha);
				pVtx[1].col = D3DXCOLOR(g_aEffect[nCntEffect].nLife* g_aEffect[nCntEffect].col.r/30.0f, g_aEffect[nCntEffect].col.g, g_aEffect[nCntEffect].col.b, g_aEffect[nCntEffect].fAlpha);
				pVtx[2].col = D3DXCOLOR(g_aEffect[nCntEffect].nLife* g_aEffect[nCntEffect].col.r/30.0f, g_aEffect[nCntEffect].col.g, g_aEffect[nCntEffect].col.b, g_aEffect[nCntEffect].fAlpha);
				pVtx[3].col = D3DXCOLOR(g_aEffect[nCntEffect].nLife* g_aEffect[nCntEffect].col.r/30.0f, g_aEffect[nCntEffect].col.g, g_aEffect[nCntEffect].col.b, g_aEffect[nCntEffect].fAlpha);
				break;
			case EFFECTTYPE_PARTICLE2:
				//頂点カラーの設定
				pVtx[0].col = D3DXCOLOR(g_aEffect[nCntEffect].col.r, g_aEffect[nCntEffect].fAlpha,g_aEffect[nCntEffect].fAlpha, g_aEffect[nCntEffect].fAlpha);
				pVtx[1].col = D3DXCOLOR(g_aEffect[nCntEffect].col.r, g_aEffect[nCntEffect].fAlpha,g_aEffect[nCntEffect].fAlpha, g_aEffect[nCntEffect].fAlpha);
				pVtx[2].col = D3DXCOLOR(g_aEffect[nCntEffect].col.r, g_aEffect[nCntEffect].fAlpha,g_aEffect[nCntEffect].fAlpha, g_aEffect[nCntEffect].fAlpha);
				pVtx[3].col = D3DXCOLOR(g_aEffect[nCntEffect].col.r, g_aEffect[nCntEffect].fAlpha,g_aEffect[nCntEffect].fAlpha, g_aEffect[nCntEffect].fAlpha);
				break;
			}
			//位置の更新
			g_aEffect[nCntEffect].pos.x+= g_aEffect[nCntEffect].move.x;
			g_aEffect[nCntEffect].pos.y+= g_aEffect[nCntEffect].move.y;
			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x - g_aEffect[nCntEffect].fRadius, g_aEffect[nCntEffect].pos.y - g_aEffect[nCntEffect].fRadius, 0.0f);//←右回りで設定する
			pVtx[1].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x + g_aEffect[nCntEffect].fRadius, g_aEffect[nCntEffect].pos.y - g_aEffect[nCntEffect].fRadius, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x - g_aEffect[nCntEffect].fRadius, g_aEffect[nCntEffect].pos.y + g_aEffect[nCntEffect].fRadius, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x + g_aEffect[nCntEffect].fRadius, g_aEffect[nCntEffect].pos.y + g_aEffect[nCntEffect].fRadius, 0.0f);
	
			g_aEffect[nCntEffect].nLife--;
			g_aEffect[nCntEffect].fAlpha -= 0.025;
			g_aEffect[nCntEffect].fRadius -= 0.3;
			if (g_aEffect[nCntEffect].pos.x >=SCREEN_WIDTH|| g_aEffect[nCntEffect].pos.x<=0|| g_aEffect[nCntEffect].pos.y>=SCREEN_HEIGHT|| g_aEffect[nCntEffect].pos.y<=0)
			{
				g_aEffect[nCntEffect].bUse = false;
			}
			if (g_aEffect[nCntEffect].nLife<=0)
			{
				g_aEffect[nCntEffect].bUse = false;
			}
			
		}
		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffEffect->Unlock();
}
void DrawEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ
	int nCntEffect;
	//デバイスの取得
	pDevice = GetDevice();
	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffEffect, 0, sizeof(VERTEX_2D));
	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	//αブレンディングを加算合成に設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_aEffect[nCntEffect].bUse == true)
		{//弾が使用されている
				//ポリゴンの描画
			pDevice->SetTexture(0, g_pTextureEffect);
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4*nCntEffect, 2);
		}
	}
	//αブレンディングを元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

void SetEffect(D3DXVECTOR3 pos, D3DXVECTOR3 move,D3DXCOLOR col, float fRadius, int nLife,EFFECTTYPE type)
{
	VERTEX_2D* pVtx=0;
	int nCntEffect;
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_aEffect[nCntEffect].bUse == false)
		{//弾が使用されていない
			g_aEffect[nCntEffect].pos = pos;
			g_aEffect[nCntEffect].col = col;
			g_aEffect[nCntEffect].fRadius = fRadius;
			g_aEffect[nCntEffect].nLife =nLife;
			g_aEffect[nCntEffect].move = move;
			g_aEffect[nCntEffect].type = type;
			g_aEffect[nCntEffect].fAlpha = 1.0f;
			g_aEffect[nCntEffect].bUse = true;//使用している状態にする
		
			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x - 40, g_aEffect[nCntEffect].pos.y - 40, 0.0f);//←右回りで設定する
			pVtx[1].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x + 40, g_aEffect[nCntEffect].pos.y - 40, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x - 40, g_aEffect[nCntEffect].pos.y + 40, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x + 40, g_aEffect[nCntEffect].pos.y + 40, 0.0f);
	
			break;
		}
		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffEffect->Unlock();
}