//=============================================================================
//
//　敵視点のビューポートの枠の処理 [viewportwaku.cpp]
// 　Author : 近田尚也
//
//=============================================================================
#include "unlock.h"
#include "gimmick.h"
#include "item.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureUnlock = {};			//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffUnlock = NULL;	//頂点バッファへのポインタ
bool bUse;
//====================================
//敵視点のビューポートの枠の初期化処理
//====================================
void InitUnlock(void)
{
	//ローカル変数
	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ
	VERTEX_2D* pVtx;		//頂点情報へのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\texture\\waku2.png",
		&g_pTextureUnlock);

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,//(sizeof(VERTEX_2D)*必要な頂点数
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffUnlock,
		NULL);

	bUse = false;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffUnlock->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(307.5f, 397.5f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(972.5f, 397.5f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(307.5f, 452.5f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(972.5f, 452.5f, 0.0f);

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
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffUnlock->Unlock();
}

//====================================
//敵視点のビューポートの枠の終了処理
//====================================
void UninitUnlock(void)
{

	//テクスチャの破棄
	if (g_pTextureUnlock != NULL)
	{
		g_pTextureUnlock->Release();
		g_pTextureUnlock = NULL;
	}


	//頂点バッファの破棄
	if (g_pVtxBuffUnlock != NULL)
	{
		g_pVtxBuffUnlock->Release();
		g_pVtxBuffUnlock = NULL;
	}

}

//====================================
//敵視点のビューポートの枠の更新処理
//====================================
void UpdateUnlock(void)
{
	bool isBill = IsBill();
	ITEM* pItem = Getitem();

	if (isBill == true)
	{
		if (pItem[0].bHold == true && pItem[1].bHold == true)
		{
			bUse = true;
		}

	}
	else
	{
		bUse = false;
	}
}

//====================================
//敵視点のビューポートの枠の描画処理
//====================================
void DrawUnlock(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//頂点フォーマットの設定
	pDevice->SetStreamSource(0, g_pVtxBuffUnlock, 0, sizeof(VERTEX_2D));

	//頂点フォーマット設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	if (bUse == true)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureUnlock);

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}
}
