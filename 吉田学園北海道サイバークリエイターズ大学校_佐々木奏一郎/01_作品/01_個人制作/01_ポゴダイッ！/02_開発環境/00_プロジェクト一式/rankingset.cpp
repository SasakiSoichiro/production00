//=============================================================================
//
//	ランキングセット処理 [rankingset.cpp]
// Author : 佐々木奏一郎
//
//=============================================================================
#include "rankingset.h"
#include "input.h"
#include "fade.h"
//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureRank = {};//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRank = NULL;//頂点バッファへのポインタ
int g_RankTimeCnt;
void InitRankingSet(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCnt;
	//デバイスの取得
	pDevice = GetDevice();
	//テクスチャの読み込み
		//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\irekae.png",
		&g_pTextureRank);
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,//(sizeof(VERTEX_2D)*必要な頂点数
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRank,
		NULL);
	VERTEX_2D* pVtx;
	g_RankTimeCnt=0;
	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffRank->Lock(0, 0, (void**)&pVtx, 0);
	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(250.0f, 90.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(400.0f, 90.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(250.0f, 560.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(400.0f, 560.0f, 0.0f);
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
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	/*	pVtx += 4;*/
	//頂点バッファをアンロックする
	g_pVtxBuffRank->Unlock();
}
//タイトル画面の終了処理
void UninitRankingSet(void)
{
	//テクスチャの破棄
	if (g_pTextureRank != NULL)
	{
		g_pTextureRank->Release();
		g_pTextureRank = NULL;
	}
	//頂点バッファの破棄
	if (g_pVtxBuffRank != NULL)
	{
		g_pVtxBuffRank->Release();
		g_pVtxBuffRank = NULL;
	}
}
//タイトル画面の更新処理
void UpdateRankingSet(void)
{
	g_RankTimeCnt++;
	if (g_RankTimeCnt>=300 ||KeyboardTrigger(DIK_RETURN) == true|| JoyPadTrigger(JOYKEY_A) == true)
	{//エンターキーが押された
		//モード設定
		SetFade(MODE_TITLE);
	}

}
void DrawRankingSet(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ
	int nCntBG;
	//デバイスの取得
	pDevice = GetDevice();
	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffRank, 0, sizeof(VERTEX_2D));
	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureRank);
	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}