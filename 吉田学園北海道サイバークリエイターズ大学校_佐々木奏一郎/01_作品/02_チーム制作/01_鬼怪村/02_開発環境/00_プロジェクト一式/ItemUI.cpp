//=============================================================================
//
//　アイテムUI処理 [itemUI.cpp]
// 　Author : SasakiSoichiro
//
//=============================================================================
#include "itemUI.h"
#include "player.h"
#include "input.h"
#include "item.h"

// マクロ定義
#define MAX_ITEMUI (3)
#define ITEMUI_SIZE (60)

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureItemUI[ITEM_MAX] = {};		// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffItemUI = NULL;		// 頂点バッファへのポインタ
ItemUI g_aItemUI[MAX_ITEMUI];							// ブロックの情報
int g_nSelect;

//=============================================================================
//アイテムUIの初期化処理
//=============================================================================
void InitItemUI(void)
{
	// ローカル変数
	LPDIRECT3DDEVICE9 pDevice;	// デバイスへのポインタ
	VERTEX_2D* pVtx = 0;		// 頂点情報へのポインタ

	// デバイスの取得
	pDevice = GetDevice();
	for (int nCnt = 0; nCnt < ITEM_MAX; nCnt++)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,
			ITEMUI_TEXTURE[nCnt],
			&g_pTextureItemUI[nCnt]);
	}

	// ループ処理
	for (int nCntBlock = 0; nCntBlock < MAX_ITEMUI; nCntBlock++)
	{// ブロックの数分ループする

		g_aItemUI[nCntBlock].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 位置を初期化する
		g_aItemUI[nCntBlock].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 移動値を初期化する
		g_aItemUI[nCntBlock].fWidth = 0.0f;							// 幅を初期化する
		g_aItemUI[nCntBlock].fHeight = 0.0f;						// 高さを初期化する
		g_aItemUI[nCntBlock].nType = ITEM_FLAME;					// 種類を初期化する
		g_aItemUI[nCntBlock].bUse = false;							// 使われていない状態にする	
	}

	g_nSelect = 0;

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_ITEMUI,	// (sizeof(VERTEX_2D)*必要な頂点数
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffItemUI,
		NULL);

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffItemUI->Lock(0, 0, (void**)&pVtx, 0);

	// ループ処理
	for (int nCntBlock = 0; nCntBlock < MAX_ITEMUI; nCntBlock++)
	{// ブロックの数分ループする

		// 頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(1000.0f + nCntBlock * ITEMUI_SIZE, 50.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(1000.0f + nCntBlock * ITEMUI_SIZE + ITEMUI_SIZE, 50.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(1000.0f + nCntBlock * ITEMUI_SIZE, 50.0f + ITEMUI_SIZE, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(1000.0f + nCntBlock * ITEMUI_SIZE + ITEMUI_SIZE, 50.0f + ITEMUI_SIZE, 0.0f);

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

		pVtx += 4;		// 頂点データのポインタを4つ分集める
	}

	// 頂点バッファをアンロックする
	g_pVtxBuffItemUI->Unlock();
}

//=============================================================================
//アイテムUIの終了処理
//=============================================================================
void UninitItemUI(void)
{
	for (int nCnt = 0; nCnt < ITEM_MAX; nCnt++)
	{
		// テクスチャの破棄
		if (g_pTextureItemUI[nCnt] != NULL)
		{
			g_pTextureItemUI[nCnt]->Release();
			g_pTextureItemUI[nCnt] = NULL;
		}
	}

	// 頂点バッファの破棄
	if (g_pVtxBuffItemUI != NULL)
	{
		g_pVtxBuffItemUI->Release();
		g_pVtxBuffItemUI = NULL;
	}
}

//=============================================================================
//アイテムUIの更新処理
//=============================================================================
void UpdateItemUI()
{

	VERTEX_2D* pVtx = 0;		// 頂点情報へのポインタ

	if (KeybordTrigger(DIK_1) == true||JoyPadTrigger(JOYKEY_Y)==true)
	{// 1またはYボタンを押した場合

		if (g_nSelect == MAX_ITEMUI-1)
		{// 端までいったら
			g_nSelect = 0;
		}
		else
		{// 端以外
			g_nSelect++;
		}
	}

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffItemUI->Lock(0, 0, (void**)&pVtx, 0);

	// ループ処理
	for (int nCntBlock = 0; nCntBlock < MAX_ITEMUI; nCntBlock++)
	{// ブロックの数分ループする

		if(nCntBlock == g_nSelect)
		{
			// 頂点カラーの設定　　　　
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}
		else
		{
			// 頂点カラーの設定　　　　
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.4f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.4f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.4f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.4f);
		}


		pVtx += 4;			//頂点データのポインタを4つ分集める
	}

	// 頂点バッファをアンロックする
	g_pVtxBuffItemUI->Unlock();
}

//=============================================================================
//アイテムUIの描画処理
//=============================================================================
void DrawItemUI(void)
{
	// デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスの取得
	pDevice = GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffItemUI, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// ループ処理
	for (int nCntItemUI = 0; nCntItemUI < MAX_ITEMUI; nCntItemUI++)
	{// ブロックの数分ループする

		// テクスチャの設定
		pDevice->SetTexture(ITEM_FLAME, g_pTextureItemUI[g_aItemUI[nCntItemUI].nType]);
		pDevice->SetTexture(ITEM_NAGINATA, g_pTextureItemUI[g_aItemUI[nCntItemUI].nType]);
		pDevice->SetTexture(ITEM_HEAL, g_pTextureItemUI[g_aItemUI[nCntItemUI].nType]);
		pDevice->SetTexture(ITEM_POCKETWATCH, g_pTextureItemUI[g_aItemUI[nCntItemUI].nType]);
		pDevice->SetTexture(ITEM_USEDNAGINATA, g_pTextureItemUI[g_aItemUI[nCntItemUI].nType]);
		pDevice->SetTexture(ITEM_USEDHEAL, g_pTextureItemUI[g_aItemUI[nCntItemUI].nType]);
		pDevice->SetTexture(ITEM_USEDPOCKETWATCH, g_pTextureItemUI[g_aItemUI[nCntItemUI].nType]);

		// ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntItemUI, 2);
	}
}

//=============================================================================
// アイテムUIの設定処理
//=============================================================================
void SetItemUI(int nType)
{
	for (int nCntUI = 0; nCntUI < MAX_ITEMUI; nCntUI++)
	{
		if (g_aItemUI[nCntUI].nType == ITEM_FLAME)
		{
			switch (nType)
			{
			case ITEMTYPE_THREE:	// 懐中時計
				g_aItemUI[nCntUI].nType = ITEM_POCKETWATCH;
				break;
			case ITEMTYPE_FOUR:		// 薙刀
				g_aItemUI[nCntUI].nType = ITEM_NAGINATA;
				break;
			case ITEMTYPE_FIVE:		// 回復
				g_aItemUI[nCntUI].nType = ITEM_HEAL;
				break;
			case ITEMTYPE_SIX:		// 懐中電灯
				g_aItemUI[nCntUI].nType = ITEM_FLASHLIGHT;
				break;
			}

			break;
		}
	}
}

//=============================================================================
// 使い終わったアイテムを×表示する処理
//=============================================================================
void SetUsedItemUI(int nType)
{
	ITEM* pItem = Getitem();

	for (int nCntUI = 0; nCntUI < MAX_ITEMUI; nCntUI++)
	{
		switch (nType)
		{
		case ITEMTYPE_THREE:	// 懐中時計
			if(g_aItemUI[nCntUI].nType == ITEM_POCKETWATCH)g_aItemUI[nCntUI].nType = ITEM_USEDPOCKETWATCH;
			break;
		case ITEMTYPE_FOUR:		// 薙刀
			if (g_aItemUI[nCntUI].nType == ITEM_NAGINATA)g_aItemUI[nCntUI].nType = ITEM_USEDNAGINATA;
			break;
		case ITEMTYPE_FIVE:		// 回復
			if (g_aItemUI[nCntUI].nType == ITEM_HEAL)g_aItemUI[nCntUI].nType = ITEM_USEDHEAL;
			break;
		}
	}
}

//=============================================================================
//選択した情報を渡す処理
//=============================================================================
ItemUI *GetItemUI()
{
	return &g_aItemUI[0];
}

//=============================================================================
// 選んだ情報を渡す処理
//=============================================================================
int GetSelect()
{
	return g_nSelect;
}