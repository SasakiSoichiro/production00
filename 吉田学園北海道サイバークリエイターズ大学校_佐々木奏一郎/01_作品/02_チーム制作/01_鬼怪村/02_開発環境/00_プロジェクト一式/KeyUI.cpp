//=============================================================================
//
// アイテム表示の処理 [KeyUI.cpp]
// Author : chikada shouya
//
//=============================================================================

#include "KeyUI.h"
#include "item.h"

// グローバル変数
LPDIRECT3DTEXTURE9 g_ItemKeyUiTexture[ITEMKEYUITYPE_MAX] = { };		// Uiテクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffItemKeyUi = NULL;					// Uiバッファへのポインタ
ITEMKEYUI g_ItemKeyUI[ITEMKEYUITYPE_MAX];
bool bHave;
bool bHave1;

//=============================================================================
// アイテムUI表示の初期化処理
//=============================================================================
void InitKeyUI()
{
	LPDIRECT3DDEVICE9 pDevice;				// デバイスへのポインタ
	pDevice = GetDevice();					// デバイスの取得

	for (int nCnt = 0; nCnt < ITEMKEYUITYPE_MAX; nCnt++)
	{
		// テクスチャの読込
		D3DXCreateTextureFromFile(pDevice,
			ITEMKEYUI_TEXTURE[nCnt],
			&g_ItemKeyUiTexture[nCnt]);
	}

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * ITEMKEYUITYPE_MAX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffItemKeyUi, NULL);

	// 頂点情報へのポインタ
	VERTEX_2D* pVtx;

	// 頂点バッファのロック、頂点データへのポインタ取得
	g_pVtxBuffItemKeyUi->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt1 = 0; nCnt1 < ITEMKEYUITYPE_MAX; nCnt1++)
	{
		// 構造体変数の初期化
		g_ItemKeyUI[nCnt1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_ItemKeyUI[nCnt1].fHeight = 0.0f;
		g_ItemKeyUI[nCnt1].fWidth = 0.0f;
		g_ItemKeyUI[nCnt1].bUse = false;
		bHave = false;
		bHave1 = false;

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
	g_pVtxBuffItemKeyUi->Unlock();
}

//=============================================================================
// アイテムUI表示の終了処理
//=============================================================================
void UninitKeyUI()
{
	for (int nCnt = 0; nCnt < ITEMKEYUITYPE_MAX; nCnt++)
	{
		// テクスチャの破棄
		if (g_ItemKeyUiTexture[nCnt] != NULL)
		{
			g_ItemKeyUiTexture[nCnt]->Release();
			g_ItemKeyUiTexture[nCnt] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuffItemKeyUi != NULL)
	{
		g_pVtxBuffItemKeyUi->Release();
		g_pVtxBuffItemKeyUi = NULL;
	}
}

//=============================================================================
//アイテムUI表示の更新処理
//=============================================================================
void UpdateKeyUI()
{
	// アイテムの取得処理
	ITEM* pItem = Getitem();

	// 鍵の上部のみ取った場合
	if (pItem[0].bHold == true && pItem[1].bHold == false)
	{
		bHave = true;
	}

	// 鍵の下部のみ取った場合
	if (pItem[1].bHold == true && pItem[0].bHold == false)
	{
		bHave = true;
	}

	// 鍵の上部と下部の両方をとった場合
	if (pItem[0].bHold == true && pItem[1].bHold == true)
	{
		bHave = false;
		bHave1 = true;
	}
}
//=============================================================================
// アイテムUI表示の描画処理
//=============================================================================
void DrawKeyUI()
{
	// デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスの取得
	pDevice = GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffItemKeyUi, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCnt = 0; nCnt < ITEMKEYUITYPE_MAX; nCnt++)
	{

		if (g_ItemKeyUI[nCnt].bUse == true)
		{

			if (bHave == true)
			{
				// テクスチャの設定
				pDevice->SetTexture(0, g_ItemKeyUiTexture[1]);
			}
			else if (bHave1 == true)
			{
				// テクスチャの設定
				pDevice->SetTexture(0, g_ItemKeyUiTexture[2]);
			}
			else
			{
				// テクスチャの設定
				pDevice->SetTexture(0, g_ItemKeyUiTexture[g_ItemKeyUI[nCnt].aType]);

			}

			// アイテムUIの描画
			pDevice->DrawPrimitive(
				D3DPT_TRIANGLESTRIP,	// プリミティブの種類
				nCnt * 4,				// 描画する最初の頂点インデックス
				2						// プリミティブ（アイテムUI）の数
			);
		}
	}
}
//=============================================================================
// 鍵のUIの設定処理
//=============================================================================
void SetKeyUI(D3DXVECTOR3 pos, ITEMKEYUITYPE aType, float fWidth, float fHeight)
{
	// 頂点情報のポインタ
	VERTEX_2D* pVtx;

	// 頂点バッファのロック、頂点データへのポインタ取得
	g_pVtxBuffItemKeyUi->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < ITEMKEYUITYPE_MAX; nCnt++)
	{
		if (g_ItemKeyUI[nCnt].bUse == false)
		{// 未使用状態だったら
			g_ItemKeyUI[nCnt].pos = pos;
			g_ItemKeyUI[nCnt].aType = aType;
			g_ItemKeyUI[nCnt].fHeight = fHeight;
			g_ItemKeyUI[nCnt].fWidth = fWidth;
			g_ItemKeyUI[nCnt].bUse = true;

			// 頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_ItemKeyUI[nCnt].pos.x - fWidth, g_ItemKeyUI[nCnt].pos.y - fHeight, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_ItemKeyUI[nCnt].pos.x + fWidth, g_ItemKeyUI[nCnt].pos.y - fHeight, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_ItemKeyUI[nCnt].pos.x - fWidth, g_ItemKeyUI[nCnt].pos.y + fHeight, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_ItemKeyUI[nCnt].pos.x + fWidth, g_ItemKeyUI[nCnt].pos.y + fHeight, 0.0f);
			break;
		}
		pVtx += 4;
	}

	// 頂点バッファをアンロック
	g_pVtxBuffItemKeyUi->Unlock();
}
