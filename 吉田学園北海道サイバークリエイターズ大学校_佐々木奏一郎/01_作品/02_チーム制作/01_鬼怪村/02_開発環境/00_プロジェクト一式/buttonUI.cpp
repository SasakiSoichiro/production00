//====================================================
//
// アイテム表示の処理 [KeyUI.cpp]
// Author : chikada shouya
//
//====================================================

#include "buttonUI.h"
#include "itemUI.h"

// グローバル変数
LPDIRECT3DTEXTURE9 g_ButtonUiTexture[BUTTONUITYPE_MAX] = { };	// Uiテクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffButtonUi = NULL;				// Uiバッファへのポインタ
BUTTONUI g_ButtonUI[MAX_BUTTONUI];

//====================================================
// アイテムUI表示の初期化処理
//====================================================
void InitButtonUI()
{
	LPDIRECT3DDEVICE9 pDevice;			// デバイスへのポインタ
	pDevice = GetDevice();				// デバイスの取得

	for (int nCnt = 0; nCnt < BUTTONUITYPE_MAX; nCnt++)
	{
		// テクスチャ読込
		D3DXCreateTextureFromFile(pDevice,
			BUTTONUITYPE__TEXTURE[nCnt],
			&g_ButtonUiTexture[nCnt]);
	}

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BUTTONUI,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffButtonUi, NULL);

	// 頂点情報へのポインタ
	VERTEX_2D* pVtx;

	// 頂点バッファのロック、頂点データへのポインタ取得
	g_pVtxBuffButtonUi->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt1 = 0; nCnt1 < MAX_BUTTONUI; nCnt1++)
	{
		// 構造体変数の初期化
		g_ButtonUI[nCnt1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_ButtonUI[nCnt1].fHeight = 0.0f;
		g_ButtonUI[nCnt1].fWidth = 0.0f;
		g_ButtonUI[nCnt1].bUse = false;

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
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}

	// 頂点バッファをアンロック
	g_pVtxBuffButtonUi->Unlock();
}

//====================================================
// アイテムUI表示の終了処理
//====================================================
void UninitButtonUI()
{
	for (int nCnt = 0; nCnt < BUTTONUITYPE_MAX; nCnt++)
	{
		// テクスチャの破棄
		if (g_ButtonUiTexture[nCnt] != NULL)
		{
			g_ButtonUiTexture[nCnt]->Release();
			g_ButtonUiTexture[nCnt] = NULL;
		}
	}

	// 頂点バッファの破棄
	if (g_pVtxBuffButtonUi != NULL)
	{
		g_pVtxBuffButtonUi->Release();
		g_pVtxBuffButtonUi = NULL;
	}
}

//====================================================
// アイテムUI表示の更新処理
//====================================================
void UpdateButtonUI()
{
	int nSelect = GetSelect();

	for (int nCnt = 0; nCnt < MAX_BUTTONUI; nCnt++)
	{
		if (g_ButtonUI[nCnt].aType == BUTTONUITYPE_BUTTON_Y)
		{
			if (nSelect == 0)
			{
				g_ButtonUI[0].bUse = true;
				g_ButtonUI[1].bUse = false;
				g_ButtonUI[2].bUse = false;
			}
			else if (nSelect == 1)
			{
				g_ButtonUI[1].bUse = true;
				g_ButtonUI[0].bUse = false;
				g_ButtonUI[2].bUse = false;
			}
			else if (nSelect == 2)
			{
				g_ButtonUI[2].bUse = true;
				g_ButtonUI[0].bUse = false;
				g_ButtonUI[1].bUse = false;
			}
		}
		if (g_ButtonUI[nCnt].aType == BUTTONUITYPE_BUTTON_X)
		{
			g_ButtonUI[nCnt].bUse = true;
		}
	}
}

//====================================================
// アイテムUI表示の描画処理
//====================================================
void DrawButtonUI()
{
	// デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;
	// デバイスの取得
	pDevice = GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffButtonUi, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCnt = 0; nCnt < MAX_BUTTONUI; nCnt++)
	{
		if (g_ButtonUI[nCnt].bUse == true)
		{
			// テクスチャの設定
			pDevice->SetTexture(0, g_ButtonUiTexture[g_ButtonUI[nCnt].aType]);

			// アイテムUIの描画
			pDevice->DrawPrimitive(
				D3DPT_TRIANGLESTRIP,	// プリミティブの種類
				nCnt * 4,				// 描画する最初の頂点インデックス
				2						// プリミティブ（アイテムUI）の数
			);
		}
	}
}

//====================================================
// 鍵のUIの設定処理
//====================================================
void SetButtonUI(D3DXVECTOR3 pos, BUTTONUITYPE aType, float fWidth, float fHeight)
{
	// 頂点情報のポインタ
	VERTEX_2D* pVtx;

	// 頂点バッファのロック、頂点データへのポインタ取得
	g_pVtxBuffButtonUi->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_BUTTONUI; nCnt++)
	{
		if (g_ButtonUI[nCnt].bUse == false)
		{// 未使用状態だったら
			g_ButtonUI[nCnt].pos = pos;
			g_ButtonUI[nCnt].aType = aType;
			g_ButtonUI[nCnt].fHeight = fHeight;
			g_ButtonUI[nCnt].fWidth = fWidth;
			g_ButtonUI[nCnt].bUse = true;

			// 頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_ButtonUI[nCnt].pos.x - fWidth, g_ButtonUI[nCnt].pos.y - fHeight, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_ButtonUI[nCnt].pos.x + fWidth, g_ButtonUI[nCnt].pos.y - fHeight, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_ButtonUI[nCnt].pos.x - fWidth, g_ButtonUI[nCnt].pos.y + fHeight, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_ButtonUI[nCnt].pos.x + fWidth, g_ButtonUI[nCnt].pos.y + fHeight, 0.0f);
			break;
		}
		pVtx += 4;
	}

	// 頂点バッファをアンロック
	g_pVtxBuffButtonUi->Unlock();
}
