//=============================================================================
//
//	フェード処理 [fade.cpp]
// Author : 佐々木奏一郎
//
//=============================================================================
#include "fade.h"
//グローバル変数
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffFade = NULL;//頂点バッファへのポインタ
FADE g_fade;
MODE g_modeNext;
D3DXCOLOR g_colorFade;
void InitFade(MODE modeNext)
{
	LPDIRECT3DDEVICE9 pDevice;

	g_fade = FADE_IN;
	g_modeNext = modeNext;
	g_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

	//デバイスの取得
	pDevice = GetDevice();

	VERTEX_2D* pVtx;

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,//(sizeof(VERTEX_2D)*必要な頂点数
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffFade,
		NULL);
	//
	g_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);

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
	pVtx[0].col = D3DXCOLOR(g_colorFade);
	pVtx[1].col = D3DXCOLOR(g_colorFade);
	pVtx[2].col = D3DXCOLOR(g_colorFade);
	pVtx[3].col = D3DXCOLOR(g_colorFade);
	//頂点バッファをアンロックする
	g_pVtxBuffFade->Unlock();
	//モードを設定
	SetMode(g_modeNext);
}
void UninitFade(void)
{
	//頂点バッファの破棄
	if (g_pVtxBuffFade != NULL)
	{
		g_pVtxBuffFade->Release();
		g_pVtxBuffFade = NULL;
	}
}
void UpdateFade(void)
{
	VERTEX_2D* pVtx;
	if (g_fade != FADE_NONE)
	{
		if (g_fade == FADE_IN)
		{//フェードイン状態
			g_colorFade.a -= 0.03f;//ポリゴンを透明にしておく
			if (g_colorFade.a <= 0.0f)
			{
				g_colorFade.a = 0.0f;
				g_fade = FADE_NONE;
			}
		}
		else if (g_fade == FADE_OUT)
		{//フェードアウト状態
			g_colorFade.a += 0.03f;
			if (g_colorFade.a >= 1.0f)
			{
				g_colorFade.a = 1.0f;
				g_fade = FADE_IN;
				//次の画面の移行
				SetMode(g_modeNext);
			}
		}
		//頂点バッファをロックする
		g_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(g_colorFade);
		pVtx[1].col = D3DXCOLOR(g_colorFade);
		pVtx[2].col = D3DXCOLOR(g_colorFade);
		pVtx[3].col = D3DXCOLOR(g_colorFade);

		//頂点バッファをアンロックする
		g_pVtxBuffFade->Unlock();
	}
}
void DrawFade(void)
{
	VERTEX_2D* pVtx;
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ
	int nCntBullet;
	//デバイスの取得
	pDevice = GetDevice();
	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffFade, 0, sizeof(VERTEX_2D));
	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	//テクスチャの設定
	pDevice->SetTexture(0, NULL);
	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}
void SetFade(MODE modeNext)
{
	g_fade = FADE_OUT;//フェードアウト状態に
	g_modeNext = modeNext;//次の画面を設定
}
FADE GetFade(void)
{
	return g_fade;
}