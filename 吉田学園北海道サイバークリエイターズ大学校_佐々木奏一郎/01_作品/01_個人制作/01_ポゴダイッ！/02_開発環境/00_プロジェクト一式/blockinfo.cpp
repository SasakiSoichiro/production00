//=============================================================================
//
//	ブロックの説明処理 [blockinfo.cpp]
// Author : 佐々木奏一郎
//
//=============================================================================
#include "blockinfo.h"
#include "main.h"
#include "input.h"
#include "fade.h"
#include "player.h"
#include "sound.h"
//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureBlockInfo = NULL;//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBlockInfo = NULL;//頂点バッファへのポインタ
int g_nStateCnt;
//タイトル画面の初期化処理
void InitBlockInfo(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ
	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\blockInfo.png",
		&g_pTextureBlockInfo);
	//頂点バッファの生成。頂点情報の設定
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,//(sizeof(VERTEX_2D)*必要な頂点数
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBlockInfo,
		NULL);

	g_nStateCnt = 0;

	VERTEX_2D* pVtx;//頂点情報へのポインタ
	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBlockInfo->Lock(0, 0, (void**)&pVtx, 0);
	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
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
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	//頂点バッファをアンロックする
	g_pVtxBuffBlockInfo->Unlock();
}
//タイトル画面の終了処理
void UninitBlockInfo(void)
{
	//サウンドを停止
	StopSound();
	//テクスチャの破棄
	if (g_pTextureBlockInfo != NULL)
	{
		g_pTextureBlockInfo->Release();
		g_pTextureBlockInfo = NULL;
	}
	//頂点バッファの破棄
	if (g_pVtxBuffBlockInfo != NULL)
	{
		g_pVtxBuffBlockInfo->Release();
		g_pVtxBuffBlockInfo = NULL;
	}
}
//タイトル画面の更新処理
void UpdateBlockInfo(void)
{
	if (KeyboardTrigger(DIK_RETURN) == true)
	{//エンターキーが押された
		//モード設定
		SetFade(MODE_TUTORIAL);
	}
	if (JoyPadTrigger(JOYKEY_A) == true)
	{//エンターキーが押された
		//モード設定
		SetFade(MODE_TUTORIAL);
	}
	g_nStateCnt++;
	if (g_nStateCnt >= 1800)
	{
		//モード設定(ランキング画面に移動)
		SetFade(MODE_TITLE);
	}

}
//タイトル画面の描画処理
void DrawBlockInfo(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ
	int nCntBG;
	//デバイスの取得
	pDevice = GetDevice();
	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffBlockInfo, 0, sizeof(VERTEX_2D));
	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureBlockInfo);
	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}