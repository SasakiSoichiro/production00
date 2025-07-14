//==============================================
//
//
//			解除の処理
//
//			Yabuki
//
//===============================================

#include "Cancellation.h"
#include "input.h"
#include "player.h"
#include "gimmick.h"
#include "item.h"

// グローバル
Cance g_Cancellation = {};
LPDIRECT3DTEXTURE9 g_CancellationTexture[TEX_MAX] = {};		// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffCancellation = NULL;		// バッファへのポインタ

//===================
//	初期化処理
//===================
void InitCancellation(void)
{
	VERTEX_2D* pVtx{};

	LPDIRECT3DDEVICE9 pDevice;		// デバイスへのポインタ
	pDevice = GetDevice();			// デバイスの取得

	// 各変数の初期化
	g_Cancellation.bKeyhave = false;
	g_Cancellation.bUse = false;
	g_Cancellation.fCnt = 0.0f;
	g_Cancellation.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	for (int nCntLoad = 0; nCntLoad < TEX_MAX; nCntLoad++)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,
			X_TEX[nCntLoad],
			&g_CancellationTexture[nCntLoad]);
	}

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffCancellation, NULL);

	// 頂点バッファのロック、頂点データへのポインタ取得
	g_pVtxBuffCancellation->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点情報の設定
	pVtx[0].pos = D3DXVECTOR3(320.0f, 340.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(640.0f, 340.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(320.0f, 400.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(640.0f, 400.0f, 0.0f);

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
	g_pVtxBuffCancellation->Unlock();
}

//===================
//	終了処理
//===================
void UinitCancellation(void)
{
	for (int nCnt = 0; nCnt < TEX_MAX; nCnt++)
	{
		// テクスチャの破棄
		if (g_CancellationTexture != NULL)
		{
			g_CancellationTexture[nCnt]->Release();
			g_CancellationTexture[nCnt] = NULL;
		}
	}

	// 頂点バッファの破棄
	if (g_pVtxBuffCancellation != NULL)
	{
		g_pVtxBuffCancellation->Release();
		g_pVtxBuffCancellation = NULL;
	}
}

//===================
//	更新処理
//===================
void UpdateCancellation(void)
{
	Player* pPlayer = GetPlayer();
	GIMMICK* pGimmick = GetGimmick();
	ITEM* pItem = Getitem();

	//if (g_Cancellation.bUse)
	//{
		// プレイヤーの半径の算出用変数
		float fPRadPos = 50.0f;

		// アイテムの半径の算出用変数
		float fIRadPos = 50.0f;

		// アイテムのプレイヤーの距離の差
		D3DXVECTOR3 diff = pPlayer->pos - pGimmick->pos;

		// 範囲計算
		float fDisX = pPlayer->pos.x - pGimmick->pos.x;
		float fDisY = pPlayer->pos.y - pGimmick->pos.y;
		float fDisZ = pPlayer->pos.z - pGimmick->pos.z;

		// 二つの半径を求める
		float fRadX = fPRadPos + fIRadPos;

		// プレイヤーがアイテムの範囲に入ったら
		if ((fDisX * fDisX) + (fDisY * fDisY) + (fDisZ * fDisZ) <= (fRadX * fRadX))
		{
			if (pItem[0].bHold == true && pItem[1].bHold == true)
			{
				g_Cancellation.bUse = true;
				if (GetKeyboardPress(DIK_F) || GetJoypadPress(JOYKEY_B) == true)
				{// Fが押されていたら
					g_Cancellation.nType = TEX_0;
				}
				else
				{
					g_Cancellation.nType = TEX_1;
				}
			}
		}
		else
		{
			g_Cancellation.bUse = false;
		}
	//}
}

//===================
//	描画処理
//===================
void DrawCancellation(void)
{
	// デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスの取得
	pDevice = GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffCancellation, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	for (int nCntTex = 0; nCntTex < TEX_MAX; nCntTex++)
	{
		if (g_Cancellation.bUse == true)
		{
			// テクスチャの設定
			pDevice->SetTexture(0, g_CancellationTexture[g_Cancellation.nType]);
			// テクスチャの設定
			pDevice->SetTexture(1, g_CancellationTexture[g_Cancellation.nType]);

			// ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

		}
	}
}
