//=============================================================================
//
//　2D表示させるUI処理 [etcUI.cpp]
// 　Author : 佐々木奏一郎
//
//=============================================================================
#include "etcUI.h"

// グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureEtcUI[ETCUI_MAX] = {};		// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEtcUI = NULL;			// 頂点バッファへのポインタ
EtcUI g_aEtcUI[ETCUI_MAX];								// ブロックの情報

//=============================================================================
// アイテムUIの初期化処理
//=============================================================================
void InitEtcUI(void)
{
	// ローカル変数
	LPDIRECT3DDEVICE9 pDevice;	// デバイスへのポインタ
	VERTEX_2D* pVtx = 0;		// 頂点情報へのポインタ

	// デバイスの取得
	pDevice = GetDevice();

	for (int nCnt = 0; nCnt < ETCUI_MAX; nCnt++)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,
			ETCUI_TEXTURE[nCnt],
			&g_pTextureEtcUI[nCnt]);
	}

	// ループ処理
	for (int nCntBlock = 0; nCntBlock < ETCUI_MAX; nCntBlock++)
	{// ブロックの数分ループする

		g_aEtcUI[nCntBlock].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 位置を初期化する
		g_aEtcUI[nCntBlock].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 移動値を初期化する
		g_aEtcUI[nCntBlock].fWidth = 0.0f;							// 幅を初期化する
		g_aEtcUI[nCntBlock].fHeight = 0.0f;							// 高さを初期化する
		g_aEtcUI[nCntBlock].nType = ETCUI_MAX;						// 種類を初期化する
		g_aEtcUI[nCntBlock].bUse = false;							// 使われていない状態にする	
	}

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * ETCUI_MAX,	// (sizeof(VERTEX_2D)*必要な頂点数
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEtcUI,
		NULL);

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffEtcUI->Lock(0, 0, (void**)&pVtx, 0);

	// ループ処理
	for (int nCntBlock = 0; nCntBlock < ETCUI_MAX; nCntBlock++)
	{// ブロックの数分ループする

		// 頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		// rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// 頂点カラーの設定　　　　
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.4f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.4f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.4f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.4f);

		// テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;			// 頂点データのポインタを4つ分集める
	}

	// 頂点バッファをアンロックする
	g_pVtxBuffEtcUI->Unlock();
}

//=============================================================================
// アイテムUIの終了処理
//=============================================================================
void UninitEtcUI(void)
{
	for (int nCnt = 0; nCnt < ETCUI_MAX; nCnt++)
	{
		// テクスチャの破棄
		if (g_pTextureEtcUI[nCnt] != NULL)
		{
			g_pTextureEtcUI[nCnt]->Release();
			g_pTextureEtcUI[nCnt] = NULL;
		}
	}

	// 頂点バッファの破棄
	if (g_pVtxBuffEtcUI != NULL)
	{
		g_pVtxBuffEtcUI->Release();
		g_pVtxBuffEtcUI = NULL;
	}
}

//=============================================================================
// アイテムUIの更新処理
//=============================================================================
void UpdateEtcUI()
{

}

//=============================================================================
// アイテムUIの描画処理
//=============================================================================
void DrawEtcUI(void)
{
	LPDIRECT3DDEVICE9 pDevice;		// デバイスへのポインタ

	// デバイスの取得
	pDevice = GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffEtcUI, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// ループ処理
	for (int nCntItemUI = 0; nCntItemUI < ETCUI_MAX; nCntItemUI++)
	{// ブロックの数分ループする
		// テクスチャの設定
		pDevice->SetTexture(ETCUI_DASH, g_pTextureEtcUI[g_aEtcUI[nCntItemUI].nType]);
		pDevice->SetTexture(ETCUI_KEY, g_pTextureEtcUI[g_aEtcUI[nCntItemUI].nType]);
		pDevice->SetTexture(ETCUI_MASTER, g_pTextureEtcUI[g_aEtcUI[nCntItemUI].nType]);

		// ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntItemUI, 2);
	}
}

//=============================================================================
// アイテムUIの設定処理
//=============================================================================
void SetEtcUI(int nType,D3DXVECTOR3 pos,float fHeight,float fWidth)
{
	// 頂点情報のポインタ
	VERTEX_2D* pVtx;

	// 頂点バッファのロック、頂点データへのポインタ取得
	g_pVtxBuffEtcUI->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < ETCUI_MAX; nCnt++)
	{
		if (g_aEtcUI[nCnt].bUse == false)
		{// 未使用状態だったら
			g_aEtcUI[nCnt].pos = pos;
			g_aEtcUI[nCnt].nType = nType;
			g_aEtcUI[nCnt].fHeight = fHeight;
			g_aEtcUI[nCnt].fWidth = fWidth;
			g_aEtcUI[nCnt].bUse = true;

			// 頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_aEtcUI[nCnt].pos.x - fWidth, g_aEtcUI[nCnt].pos.y - fHeight, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aEtcUI[nCnt].pos.x + fWidth, g_aEtcUI[nCnt].pos.y - fHeight, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aEtcUI[nCnt].pos.x - fWidth, g_aEtcUI[nCnt].pos.y + fHeight, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEtcUI[nCnt].pos.x + fWidth, g_aEtcUI[nCnt].pos.y + fHeight, 0.0f);

			break;
		}
		pVtx += 4;
	}

	// 頂点バッファをアンロック
	g_pVtxBuffEtcUI->Unlock();
}