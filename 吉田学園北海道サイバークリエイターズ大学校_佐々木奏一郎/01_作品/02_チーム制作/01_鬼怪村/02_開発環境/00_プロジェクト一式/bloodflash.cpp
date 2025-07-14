//=============================================================================
//
// 画面点滅の処理 [BloodSplatter.cpp]
// Author : Sasaki Soichiro
//
//=============================================================================

#include "BloodFlash.h"
#include "player.h"

// グローバル変数

// 頂点バッファへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBloodFlash = NULL;

BLOODFLASH g_BloodFlash;

int g_nCntBloodState;

//====================
//	初期化処理
//====================
void InitBloodFlash(void)
{
	//グローバル変数初期化
	g_BloodFlash.col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.3f);
	g_BloodFlash.bPlus = false;
	g_BloodFlash.bUse = false;
	g_nCntBloodState = 0;

	// デバイス情報の取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBloodFlash,
		NULL);

	VERTEX_2D* pVtx;

	// ロック
	g_pVtxBuffBloodFlash->Lock(0, 0, (void**)&pVtx, 0);

		// 頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);

		// rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// tex座標
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		// 頂点カラー
		pVtx[0].col = D3DXCOLOR(g_BloodFlash.col);
		pVtx[1].col = D3DXCOLOR(g_BloodFlash.col);
		pVtx[2].col = D3DXCOLOR(g_BloodFlash.col);
		pVtx[3].col = D3DXCOLOR(g_BloodFlash.col);

	// アンロック
	g_pVtxBuffBloodFlash->Unlock();
}

//====================
//	終了処理
//====================
void UninitBloodFlash(void)
{

	// 頂点バッファの解放
	if (g_pVtxBuffBloodFlash != NULL)
	{
		g_pVtxBuffBloodFlash->Release();
		g_pVtxBuffBloodFlash = NULL;
	}
}

//====================
//	更新処理
//====================
void UpdateBloodFlash(void)
{
	// ローカル変数宣言
	Player* pPlayer = GetPlayer();
	VERTEX_2D* pVtx;
	if (pPlayer->nLife == 1)
	{
		g_BloodFlash.bUse = true;
		if (g_BloodFlash.bPlus == true)
		{
			g_BloodFlash.col.a += DELTA;
			if (g_BloodFlash.col.a >= MAX_BLOODALPHA)
			{
				g_BloodFlash.bPlus = false;
			}
		}
		else
		{
			g_BloodFlash.col.a -= DELTA;
			if (g_BloodFlash.col.a <= 0.0f)
			{
				g_BloodFlash.bPlus = true;
			}
		}

		// ロック
		g_pVtxBuffBloodFlash->Lock(0, 0, (void**)&pVtx, 0);

		// 頂点カラー
		pVtx[0].col = D3DXCOLOR(g_BloodFlash.col);
		pVtx[1].col = D3DXCOLOR(g_BloodFlash.col);
		pVtx[2].col = D3DXCOLOR(g_BloodFlash.col);
		pVtx[3].col = D3DXCOLOR(g_BloodFlash.col);

		// アンロック
		g_pVtxBuffBloodFlash->Unlock();
	}
	else
	{
		g_BloodFlash.bUse = false;
	}

}

//====================
//	描画処理
//====================
void DrawBloodFlash(void)
{
	// デバイスへのポインタ、状態取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	Player* pPlayer = GetPlayer();

	// 頂点フォーマットの設定
	pDevice->SetStreamSource(0, g_pVtxBuffBloodFlash, 0, sizeof(VERTEX_2D));

	// 頂点フォーマット設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	if (g_BloodFlash.bUse == true)
	{// 使われている場合

		// ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}


}