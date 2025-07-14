//====================================================
//
// 表示の処理 [UI.cpp]
// Author : yabuki yukito
//
//====================================================

#include "UI.h"
#include "player.h"

//++++++++++++++++++++++++++++++++++++++++++++++++++++
// グローバル変数
//++++++++++++++++++++++++++++++++++++++++++++++++++++
D3DXVECTOR3 pos;								// 時間の位置
LPDIRECT3DTEXTURE9 g_UiTexture[MAX_TEX] = {};			// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffUi = NULL;	// バッファへのポインタ

//====================================================
// 表示の初期化処理
//====================================================
void InitEyeUI()
{
	VERTEX_2D* pVtx{};

	LPDIRECT3DDEVICE9 pDevice;					// デバイスへのポインタ

	pDevice = GetDevice();						// デバイスの取得

	D3DXVECTOR3 pos = D3DXVECTOR3(630.0f, 100.0f, 0.0f);

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\texture\\Eye.png",
		&g_UiTexture[0]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\texture\\Eye1.png",
		&g_UiTexture[1]);

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffUi, NULL);

	// 頂点バッファのロック、頂点データへのポインタ取得
	g_pVtxBuffUi->Lock(0, 0, (void**)&pVtx, 0);

	//頂点情報の設定
	pVtx[0].pos.x = pos.x - MAX_TIMEWIDTH / 2.0f;
	pVtx[0].pos.y = pos.y - MAX_TIMEHEIGHT / 2.0f;
	pVtx[0].pos.z = pos.z;

	pVtx[1].pos.x = pos.x + MAX_TIMEWIDTH / 2.0f;
	pVtx[1].pos.y = pos.y - MAX_TIMEHEIGHT / 2.0f;
	pVtx[1].pos.z = pos.z;

	pVtx[2].pos.x = pos.x - MAX_TIMEWIDTH / 2.0f;
	pVtx[2].pos.y = pos.y + MAX_TIMEHEIGHT / 2.0f;
	pVtx[2].pos.z = pos.z;

	pVtx[3].pos.x = pos.x + MAX_TIMEWIDTH / 2.0f;
	pVtx[3].pos.y = pos.y + MAX_TIMEHEIGHT / 2.0f;
	pVtx[3].pos.z = pos.z;

	// rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// 頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// 頂点バッファをアンロック
	g_pVtxBuffUi->Unlock();
}

//====================================================
// 表示の終了処理
//====================================================
void UninitEyeUI()
{
	// テクスチャの破棄
	for (int nCnt = 0; nCnt < MAX_TEX; nCnt++)
	{
		if (g_UiTexture[nCnt] != NULL)
		{
			g_UiTexture[nCnt]->Release();
			g_UiTexture[nCnt] = NULL;
		}
	}

	// 頂点バッファの破棄
	if (g_pVtxBuffUi != NULL)
	{
		g_pVtxBuffUi->Release();
		g_pVtxBuffUi = NULL;
	}
}

//====================================================
// 表示の更新処理
//====================================================
void UpdateEyeUI()
{
	Player* pPlayer = GetPlayer();

	VERTEX_2D* pVtx{};

	// 頂点バッファのロック、頂点データへのポインタ取得
	g_pVtxBuffUi->Lock(0, 0, (void**)&pVtx, 0);

	if (pPlayer->bEye == true)
	{
		// 頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}
	else if (pPlayer->bEye == false)
	{
		// 頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.4f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.4f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.4f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.4f);
	}

	// 頂点バッファをアンロック
	g_pVtxBuffUi->Unlock();
}

//====================================================
//表示の描画処理
//====================================================
void DrawEyeUI()
{
	Player* pPlayer = GetPlayer();

	LPDIRECT3DDEVICE9 pDevice;					// デバイスへのポインタ

	// デバイスの取得
	pDevice = GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffUi, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCnt = 0; nCnt < MAX_TEX; nCnt++)
	{
		if (pPlayer->bEye == true)
		{
			// テクスチャの設定
			pDevice->SetTexture(0, g_UiTexture[0]);

		}
		else if (pPlayer->bEye == false)
		{
			// テクスチャの設定
			pDevice->SetTexture(0, g_UiTexture[1]);

		}
	}

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}
