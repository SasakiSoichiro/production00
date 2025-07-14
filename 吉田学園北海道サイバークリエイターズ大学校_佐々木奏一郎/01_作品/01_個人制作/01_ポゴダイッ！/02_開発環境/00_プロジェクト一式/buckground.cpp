//=============================================================================
//
//	バックグラウンド処理 [background.cpp]
// Author : 佐々木奏一郎
//
//=============================================================================
#include "main.h"
#include "buckground.h"
#include "stageselect.h"
//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureBuckground = {};//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBuckground = NULL;//頂点バッファへのポインタ
float g_aPosTexU;//テクスチャの開始位置(U値)

//ポリゴンの初期化処理
void InitBuckground(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ
	int nCntBG;

	//デバイスの取得
	pDevice = GetDevice();
	int nStage= GetStageSelect();
	if (nStage == 9)
	{
		//テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,
			"data\\TEXTURE\\back002.png",
			&g_pTextureBuckground);
	}
	else
	{
		//テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,
			"data\\TEXTURE\\back001.png",
			&g_pTextureBuckground);
	}

	//テクスチャ座標の開始位置(U値)の初期化
	g_aPosTexU= 0.0f;

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,//(sizeof(VERTEX_2D)*必要な頂点数
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBuckground,
		NULL);
	VERTEX_2D* pVtx;//頂点情報へのポインタ
	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBuckground->Lock(0, 0, (void**)&pVtx, 0);

		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//←右回りで設定する
		pVtx[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);
		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		//頂点カラーの設定　　　　
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(g_aPosTexU, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(g_aPosTexU + 1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(g_aPosTexU, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(g_aPosTexU + 1.0f, 1.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffBuckground->Unlock();
}
//ポリゴンの終了処理
void UninitBuckground(void)
{
	//テクスチャの破棄
	if (g_pTextureBuckground != NULL)
	{
		g_pTextureBuckground->Release();
		g_pTextureBuckground = NULL;
	}
	//頂点バッファの破棄
	if (g_pVtxBuffBuckground != NULL)
	{
		g_pVtxBuffBuckground->Release();
		g_pVtxBuffBuckground = NULL;
	}
}
//ポリゴンの更新処理
void UpdateBuckground(void)
{
	//int nCntBG;
	//VERTEX_2D*pVtx{};
	////頂点バッファをロックし、頂点情報へのポインタを取得
	//g_pVtxBuffBuckground->Lock(0, 0, (void**)&pVtx, 0);
	////テクスチャ座標の開始位置(U値)の更新
	//g_aPosTexU += 0.00025;
	//	//テクスチャ座標の更新
	//	//rhwの設定
	//	pVtx[0].rhw = 1.0f;
	//	pVtx[1].rhw = 1.0f;
	//	pVtx[2].rhw = 1.0f;
	//	pVtx[3].rhw = 1.0f;
	//	//頂点カラーの設定　　　　
	//	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 190);
	//	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 190);
	//	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 190);
	//	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 190);
	//	//テクスチャ座標の設定
	//	pVtx[0].tex = D3DXVECTOR2(g_aPosTexU, 0.0f);
	//	pVtx[1].tex = D3DXVECTOR2(g_aPosTexU + 1.0f, 0.0f);
	//	pVtx[2].tex = D3DXVECTOR2(g_aPosTexU, 1.0f);
	//	pVtx[3].tex = D3DXVECTOR2(g_aPosTexU + 1.0f, 1.0f);

	////頂点バッファをアンロックする
	//g_pVtxBuffBuckground->Unlock();
}
//ポリゴンの描画処理
void DrawBuckground(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffBuckground, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureBuckground);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

}