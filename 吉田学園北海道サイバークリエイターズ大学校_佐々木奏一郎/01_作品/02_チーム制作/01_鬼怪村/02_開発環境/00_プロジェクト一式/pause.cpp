//--------------------------
//
// ポーズ
//
//--------------------------
#include "pause.h"
#include "input.h"
#include "main.h"
#include "game.h"
#include "fade.h"
#include "result.h"

//===============
// マクロ
//===============
#define MAX_PAUSE (3)
#define MAX_MENU_HIGHT (100)
#define MAX_MENU_WID (300)

//===============
// グローバル
//===============
//テクスチャへのポインタ
LPDIRECT3DTEXTURE9 g_pTexturePause[MAX_PAUSE] = { NULL };
//頂点バッファへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPause = NULL;

//テクスチャへのポインタ
LPDIRECT3DTEXTURE9 g_pTexturePause2 = NULL;
// 薄皮
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPause2 = NULL;

Pause g_aPause[MAX_PAUSE];
int nSelect;

//===============================
// 初期化処理
//===============================
void InitPause(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\texture\\contene1.png",
		&g_pTexturePause[0]);

	//	テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\texture\\retry1.png",
		&g_pTexturePause[1]);

	//	テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\texture\\quit1.png",
		&g_pTexturePause[2]);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\texture\\usukawa.png",
		&g_pTexturePause2);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_PAUSE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPause,
		NULL);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPause2,
		NULL);

	VERTEX_2D* pVtx;
	//ロック
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

	nSelect = PAUSEMENYU_COTINUE;

	for (int nCnt = 0; nCnt < MAX_PAUSE; nCnt++)
	{
		g_aPause[nCnt].pos = D3DXVECTOR3(650.0f, 250.0f + nCnt * MAX_MENU_HIGHT, 0.0f);

		//頂点座標の設定
		pVtx[0].pos.x = g_aPause[nCnt].pos.x - MAX_MENU_WID / 2;
		pVtx[0].pos.y = g_aPause[nCnt].pos.y - MAX_MENU_HIGHT / 2;
		pVtx[0].pos.z = 0.0f;
		pVtx[1].pos.x = g_aPause[nCnt].pos.x + MAX_MENU_WID / 2;
		pVtx[1].pos.y = g_aPause[nCnt].pos.y - MAX_MENU_HIGHT / 2;
		pVtx[1].pos.z = 0.0f;
		pVtx[2].pos.x = g_aPause[nCnt].pos.x - MAX_MENU_WID / 2;
		pVtx[2].pos.y = g_aPause[nCnt].pos.y + MAX_MENU_HIGHT / 2;
		pVtx[2].pos.z = 0.0f;
		pVtx[3].pos.x = g_aPause[nCnt].pos.x + MAX_MENU_WID / 2;
		pVtx[3].pos.y = g_aPause[nCnt].pos.y + MAX_MENU_HIGHT / 2;
		pVtx[3].pos.z = 0.0f;

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラー
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//テクスチャ座標の設定　　１２５
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		// 大事
		pVtx += 4;
	}

	//アンロック
	g_pVtxBuffPause->Unlock();

	// ロック
	g_pVtxBuffPause2->Lock(0, 0, (void**)&pVtx, 0);

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

	//頂点カラー
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//テクスチャ座標の設定　　１２５
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//アンロック
	g_pVtxBuffPause2->Unlock();

}
//=============
// 終了
//============
void UninitPause(void)
{
	for (int nCnt = 0; nCnt < MAX_PAUSE; nCnt++)
	{
		if (g_pTexturePause[nCnt] != NULL)
		{
			g_pTexturePause[nCnt]->Release();
			g_pTexturePause[nCnt] = NULL;
		}
	}

	if (g_pVtxBuffPause != NULL)
	{
		g_pVtxBuffPause->Release();
		g_pVtxBuffPause = NULL;
	}

	if (g_pTexturePause2 != NULL)
	{
		g_pTexturePause2->Release();
		g_pTexturePause2 = NULL;
	}

	if (g_pVtxBuffPause2 != NULL)
	{
		g_pVtxBuffPause2->Release();
		g_pVtxBuffPause2 = NULL;
	}

}
//==========================
// 更新
//=========================
void UpdatePause(void)
{
	int nCntPause;

	//スティック状態の取得
	VERTEX_2D* pVtx;

	// ロック
	g_pVtxBuffPause2->Lock(0, 0, (void**)&pVtx, 0);

	//頂点カラー
	pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.8f);
	pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.8f);
	pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.8f);
	pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.8f);

	//アンロック
	g_pVtxBuffPause2->Unlock();

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntPause = 0; nCntPause < MAX_PAUSE; nCntPause++)
	{//一度すべてを半透明に
		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);

		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffPause->Unlock();

	if (KeybordTrigger(DIK_W) || KeybordTrigger(DIK_UP) || JoyPadTrigger(JOYKEY_UP) == true)//W&↑
	{//Wキーが押された
		nSelect--;
	}
	else if (KeybordTrigger(DIK_S) || KeybordTrigger(DIK_DOWN) || JoyPadTrigger(JOYKEY_DOWN) == true)//S&↓
	{//Sキーが押された
		nSelect++;
	}

	//範囲を超えないようにする
	if (nSelect < 0)
	{//ゼロより小さい
		nSelect = PAUSEMENYU_COTINUE;
	}
	else if (nSelect >= PAUSEMENYU_MAX)
	{//最大値以上
		nSelect = PAUSEMENYU_QUIT;
	}

	//頂点バッファをロックし、ちょうてん情報へのポインタを取得
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

	//g_nSelectを基準にポリゴンを不透明にする
	pVtx += 4 * nSelect;

	//頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffPause->Unlock();

	if (KeybordTrigger(DIK_RETURN) || JoyPadTrigger(JOYKEY_A) == true || OnMouseDown(MOUSE_L) == true)
	{//決定キーが押された
		//メニューに合わせてモードの切り替え
		switch (nSelect)
		{
		case PAUSEMENYU_COTINUE:
			SetEnablePause(false);
			break;

		case PAUSEMENYU_RETRY:
			SetEnablePause(false);
			SetFade(MODE_GAME);
			break;

		case PAUSEMENYU_QUIT:
			SetEnablePause(false);
			SetFade(MODE_TITLE);
			break;
		}
	}
}
//================
// 描画
//===============
void DrawPause(void)
{
	//デヴァイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//頂点フォーマットの設定
	pDevice->SetStreamSource(0, g_pVtxBuffPause2, 0, sizeof(VERTEX_2D));

	//頂点フォーマット設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTexturePause2);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//頂点フォーマットの設定
	pDevice->SetStreamSource(0, g_pVtxBuffPause, 0, sizeof(VERTEX_2D));

	//頂点フォーマット設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCnt = 0; nCnt < MAX_PAUSE; nCnt++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTexturePause[nCnt]);

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);
	}
}
