//=============================================================================
//
//	ポーズ処理 [pause.cpp]
// Author : 佐々木奏一郎
//
//=============================================================================
#include "pause.h"
#include "input.h"
#include "fade.h"
#include "game.h"
#include "main.h"
#include "sound.h"
#define MAX_PAUSE (3)
//グローバル変数
LPDIRECT3DTEXTURE9 g_pTexturePause[MAX_PAUSE] = {};//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPause = NULL;//頂点バッファへのポインタ
PAUSE_MENU g_pauseMenu;//ポーズメニュー
int PauseState=0;
void InitPause(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ
	PauseState = 0;
	//デバイスの取得
	pDevice = GetDevice();
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\continue000.png",
		&g_pTexturePause[PAUSE_MENU_CONTINUE]);
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\stageselect000.png",
		&g_pTexturePause[PAUSE_MENU_RETRY]);
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\title001.png",
		&g_pTexturePause[PAUSE_MENU_QUIT]);
	//頂点バッファの生成。頂点情報の設定
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_PAUSE,//(sizeof(VERTEX_2D)*必要な頂点数
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPause,
		NULL);
	VERTEX_2D* pVtx;//頂点情報へのポインタ
	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCnt = 0; nCnt < MAX_PAUSE; nCnt++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(500.0f, 120.0f + nCnt * 150.0f, 0.0f);//←右回りで設定する
		pVtx[1].pos = D3DXVECTOR3(800.0f, 120.0f + nCnt * 150.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(500.0f, 250.0f + nCnt * 150.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(800.0f, 250.0f + nCnt * 150.0f, 0.0f);
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
		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffPause->Unlock();
}
void UninitPause(void)
{
	int nCntPause;
	for (nCntPause = 0; nCntPause < MAX_PAUSE; nCntPause++)
	{
		//テクスチャの破棄
		if (g_pTexturePause[nCntPause] != NULL)
		{
			g_pTexturePause[nCntPause]->Release();
			g_pTexturePause[nCntPause] = NULL;
		}
	}
	//頂点バッファの破棄
	if (g_pVtxBuffPause != NULL)
	{
		g_pVtxBuffPause->Release();
		g_pVtxBuffPause = NULL;
	}
}
void UpdatePause(void)
{
	if (KeyboardTrigger(DIK_UP) == true|| JoyPadTrigger(JOYKEY_UP) == true)
	{

		if (PauseState == 0)
		{
			PauseState += 2;
		}
		else
		{
			PauseState -= 1;
		}
	}
	else if (KeyboardTrigger(DIK_DOWN) == true|| JoyPadTrigger(JOYKEY_DOWN) == true)
	{


		if (PauseState == 2)
		{
			PauseState -= 2;
		}
		else
		{
			PauseState += 1;
		}
	}
	VERTEX_2D* pVtx;//頂点情報へのポインタ
//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);
	//メニューの選択→頂点カラーの設定
	switch (PauseState)
	{
	case PAUSE_MENU_CONTINUE:
		//頂点カラーの設定　　　　
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx += 4 ;
		//頂点カラーの設定　　　　
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx += 4;
		//頂点カラーの設定　　　　
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		break;
	case PAUSE_MENU_RETRY:
		//頂点カラーの設定　　　　
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx += 4;
		//頂点カラーの設定　　　　
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx += 4;
		//頂点カラーの設定　　　　
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		break;
	case PAUSE_MENU_QUIT:
		//頂点カラーの設定　　　　
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx += 4;
		//頂点カラーの設定　　　　
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx += 4;
		//頂点カラーの設定　　　　
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		break;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffPause->Unlock();
	if (KeyboardTrigger(DIK_RETURN) == true|| JoyPadTrigger(JOYKEY_A) == true)
	{

		//メニューモードに合わせて切り替え
		switch (PauseState)
		{
		case PAUSE_MENU_CONTINUE:
			SetEnblePause(false);
			break;
		case PAUSE_MENU_RETRY:
			SetFade(MODE_STAGESELECT);
			break;
		case PAUSE_MENU_QUIT:
			SetFade(MODE_TITLE);
			break;
		}
	}
}
void DrawPause(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ
	int nCntPause;
	//デバイスの取得
	pDevice = GetDevice();
	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffPause, 0, sizeof(VERTEX_2D));
	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	for (nCntPause = 0; nCntPause < MAX_PAUSE; nCntPause++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTexturePause[nCntPause]);
		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntPause * 4, 2);
	}
}