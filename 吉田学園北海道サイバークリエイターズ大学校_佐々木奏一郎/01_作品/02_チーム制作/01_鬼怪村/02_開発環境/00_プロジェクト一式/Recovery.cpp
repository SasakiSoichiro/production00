//=============================================================================
//
// 回復の処理 [Recovery.cpp]
// Author : Hirata ryuusei
//
//=============================================================================
#include "Recovery.h"
#include "ui.h"
#include "player.h"
#include "sound.h"

// グローバル
Recovery g_Recovery = {};

// テクスチャへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureRecovery = NULL;

// 頂点バッファへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRecovery = NULL;

//====================
//	初期化処理
//====================
void InitRecovery(void)
{
	// 各変数の初期化
	g_Recovery.ui = Recovery_IN;							// フェードイン状態
	g_Recovery.col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 0.2f);		// カラーの設定
	g_Recovery.count = 0;
	g_Recovery.bUse = false;

	// デバイス情報の取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRecovery,
		NULL);

	VERTEX_2D* pVtx;

	// ロック
	g_pVtxBuffRecovery->Lock(0, 0, (void**)&pVtx, 0);

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

	// 頂点カラー
	pVtx[0].col = D3DXCOLOR(g_Recovery.col);
	pVtx[1].col = D3DXCOLOR(g_Recovery.col);
	pVtx[2].col = D3DXCOLOR(g_Recovery.col);
	pVtx[3].col = D3DXCOLOR(g_Recovery.col);

	// アンロック
	g_pVtxBuffRecovery->Unlock();
}

//====================
//	終了処理
//====================
void UinitRecovery(void)
{
	// SEを止める
	StopSound(SOUND_LABEL_SE2);

	// 頂点バッファの解放
	if (g_pVtxBuffRecovery != NULL)
	{
		g_pVtxBuffRecovery->Release();
		g_pVtxBuffRecovery = NULL;
	}
}

//====================
//	更新処理
//====================
void UpdateRecovery(void)
{
	if (g_Recovery.bUse == true)
	{
		// デクリメント
		g_Recovery.count--;

		if (g_Recovery.count <= 0 && g_Recovery.ui == Recovery_NONE)
		{
			g_Recovery.ui = Recovery_IN;	// フェードイン状態
			g_Recovery.bUse = false;		// 表示されていなかったら
			g_Recovery.count = 0;			// 0にする
		}
	}

	if (g_Recovery.ui != Recovery_NONE)
	{
		if (g_Recovery.ui == Recovery_IN)
		{
			// フェードイン
			g_Recovery.col.a -= 0.01f;				// ポリゴンが透明になる速さ
			if (g_Recovery.col.a <= 0.0f)
			{
				g_Recovery.col.a = 0.0f;
				g_Recovery.ui = Recovery_NONE;		// 何もしていない状態
			}
		}
		else if (g_Recovery.ui == Recovery_OUT)
		{
			// フェードアウト
			g_Recovery.col.a += 0.02f;

			if (g_Recovery.col.a >= 0.3f)
			{
				g_Recovery.col.a = 0.3f;
				g_Recovery.ui = Recovery_IN;		// フェードイン状態
			}
		}

		VERTEX_2D* pVtx;

		// ロック
		g_pVtxBuffRecovery->Lock(0, 0, (void**)&pVtx, 0);

		// 頂点カラー
		pVtx[0].col = D3DXCOLOR(g_Recovery.col);
		pVtx[1].col = D3DXCOLOR(g_Recovery.col);
		pVtx[2].col = D3DXCOLOR(g_Recovery.col);
		pVtx[3].col = D3DXCOLOR(g_Recovery.col);

		// アンロック
		g_pVtxBuffRecovery->Unlock();
	}
}

//====================
//	描画処理
//====================
void DrawRecovery(void)
{
	// デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスの取得
	pDevice = GetDevice();

	// 頂点フォーマットの設定
	pDevice->SetStreamSource(0, g_pVtxBuffRecovery, 0, sizeof(VERTEX_2D));

	// 頂点フォーマット設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	if (g_Recovery.bUse == true)
	{
		// ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}
}

//====================
//	配置処理
//====================
void SetRecovery(int count)
{
	g_Recovery.ui = Recovery_OUT;	// フェードアウト状態
	g_Recovery.count = count;		// カウント
	g_Recovery.bUse = true;			// 表示されているなら
}