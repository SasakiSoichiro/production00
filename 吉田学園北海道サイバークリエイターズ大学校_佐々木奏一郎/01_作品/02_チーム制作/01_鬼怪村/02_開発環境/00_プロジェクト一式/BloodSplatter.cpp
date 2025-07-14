//=============================================================================
//
// 血しぶきの処理 [BloodSplatter.cpp]
// Author : Hirata ryuusei
//
//=============================================================================

#include "BloodSplatter.h"
#include "ui.h"
#include "player.h"
#include "item.h"

// グローバル変数

// テクスチャへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureUI[BLOODTYPE_MAX] = {};

// 頂点バッファへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffUI = NULL;

UI g_ui[BLOODTYPE_MAX] = {};

//====================
//	初期化処理
//====================
void InitBloodSplatter(void)
{
	for (int nCnt = 0; nCnt < BLOODTYPE_MAX; nCnt++)
	{//グローバル変数初期化
		g_ui[nCnt].ui = UI_NONE;
		g_ui[nCnt].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.1f);
		g_ui[nCnt].count = 0;
		g_ui[nCnt].bUse = false;
	}

	// デバイス情報の取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	for (int nCnt = 0; nCnt < BLOODTYPE_MAX; nCnt++)
	{// テクスチャバッファ生成
		D3DXCreateTextureFromFile(pDevice,
			UI_TEXTURE[nCnt],
			&g_pTextureUI[nCnt]);
	}

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * BLOODTYPE_MAX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffUI,
		NULL);

	VERTEX_2D* pVtx;

	// ロック
	g_pVtxBuffUI->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < BLOODTYPE_MAX; nCnt++)
	{
		// 頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);

		// rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// tex座標
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		// 頂点カラー
		pVtx[0].col = D3DXCOLOR(g_ui[nCnt].col);
		pVtx[1].col = D3DXCOLOR(g_ui[nCnt].col);
		pVtx[2].col = D3DXCOLOR(g_ui[nCnt].col);
		pVtx[3].col = D3DXCOLOR(g_ui[nCnt].col);

		pVtx += 4;
	}

	// アンロック
	g_pVtxBuffUI->Unlock();
}

//====================
//	終了処理
//====================
void UinitBloodSplatter(void)
{
	// テクスチャの破棄
	for (int nCnt = 0; nCnt < BLOODTYPE_MAX; nCnt++)
	{
		if (g_pTextureUI[nCnt] != NULL)
		{
			g_pTextureUI[nCnt]->Release();
			g_pTextureUI[nCnt] = NULL;
		}
	}

	// 頂点バッファの解放
	if (g_pVtxBuffUI != NULL)
	{
		g_pVtxBuffUI->Release();
		g_pVtxBuffUI = NULL;
	}
}

//====================
//	更新処理
//====================
void UpdateBloodSplatter(void)
{
	// ローカル変数宣言
	Player* pPlayer = GetPlayer();
	ITEM* pItem = Getitem();
	VERTEX_2D* pVtx;


	// ロック
	g_pVtxBuffUI->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < BLOODTYPE_MAX; nCnt++)
	{
		if (g_ui[nCnt].ui != UI_NONE)
		{// NONEでない場合

			if (g_ui[nCnt].ui == UI_IN)
			{// INの場合

				// フェードイン
				g_ui[nCnt].col.a -= 0.01f;			// ポリゴンが透明になる速さ

				if (g_ui[nCnt].col.a <= 0.0f)
				{// α値が0.0f以下になった場合

					g_ui[nCnt].col.a = 0.0f;		// α値を0.0fに設定
					g_ui[nCnt].ui = UI_NONE;		// 何もしていない状態
					g_ui[nCnt].bUse = false;		//使っていない状態に設定
					
				}
			}

			else if (g_ui[nCnt].ui == UI_OUT)
			{// OUTの場合

				// フェードアウト
				g_ui[nCnt].col.a += 0.05f;			// ポリゴンが不透明になる速さ

				if (g_ui[nCnt].col.a >= 0.7f)
				{// α値が0.7f以下になった場合

					g_ui[nCnt].col.a = 0.7f;		// α値を0.7fに設定
					g_ui[nCnt].ui = UI_NONE;		// 何もしていない状態

				}
			}


		}



		// 頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(g_ui[nCnt].col);
		pVtx[1].col = D3DXCOLOR(g_ui[nCnt].col);
		pVtx[2].col = D3DXCOLOR(g_ui[nCnt].col);
		pVtx[3].col = D3DXCOLOR(g_ui[nCnt].col);

		// pVtxを4足す
		pVtx += 4;



		if (g_ui[nCnt].bUse == true)
		{// 使っている場合

			g_ui[nCnt].count--;	// デクリメント

		}


		if (g_ui[nCnt].count <= 0 && pPlayer->nLife >= 2 && g_ui[nCnt].bUse == true)
		{// countが0以下かつlifeが2以上かつtrueの場合

			g_ui[nCnt].ui = UI_NONE;	// 何もしていない状態
			g_ui[nCnt].count = 0;		// count初期化

		}

		else if (g_ui[nCnt].count <= 0 && pPlayer->nLife <= 1 && g_ui[nCnt].bUse == true)
		{// countが0以下かつlifeが1以上かつtrueの場合

			g_ui[nCnt].ui = UI_NONE;	// 何もしていない状態
			g_ui[nCnt].count = 0;		// count初期化

		}


		if (pPlayer->nLife >= 3)
		{// lifeが3以上の場合

			g_ui[nCnt].bUse = false;	// 表示されていないとき
			g_ui[nCnt].ui = UI_IN;		// フェードイン状態
			g_ui[nCnt].count = 0;		// count初期化

		}
	}
	// アンロック
	g_pVtxBuffUI->Unlock();
}

//====================
//	描画処理
//====================
void DrawBloodSplatter(void)
{
	// デバイスへのポインタ、状態取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	Player* pPlayer = GetPlayer();

	// 頂点フォーマットの設定
	pDevice->SetStreamSource(0, g_pVtxBuffUI, 0, sizeof(VERTEX_2D));

	// 頂点フォーマット設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCnt = 0; nCnt < BLOODTYPE_MAX; nCnt++)
	{
		if (g_ui[nCnt].bUse == true)
		{// 使われている場合

				// テクスチャの設定
				pDevice->SetTexture(BLOODTYPE_RED, g_pTextureUI[g_ui[nCnt].nType]);
				// テクスチャの設定
				pDevice->SetTexture(BLOODTYPE_SMALL, g_pTextureUI[g_ui[nCnt].nType]);
				// テクスチャの設定
				pDevice->SetTexture(BLOODTYPE_BIG, g_pTextureUI[g_ui[nCnt].nType]);

				// ポリゴンの描画
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4*nCnt, 2);
		}
	}


}

//====================
//	設定処理
//====================
void SetBloodSplatter(int count, int nType,UI_MODE uiType)
{
	for (int nCnt = 0; nCnt < BLOODTYPE_MAX; nCnt++)
	{
		if (g_ui[nCnt].bUse == false)
		{
			g_ui[nCnt].ui = uiType;		// フェードアウト状態
			if (uiType == UI_IN|| uiType == UI_NONE)
			{
				g_ui[nCnt].col.a = 0.5f;
			}
			g_ui[nCnt].count = count;
			g_ui[nCnt].nType = nType;
			g_ui[nCnt].bUse = true;		// 表示されているとき
			break;
		}
	}
}