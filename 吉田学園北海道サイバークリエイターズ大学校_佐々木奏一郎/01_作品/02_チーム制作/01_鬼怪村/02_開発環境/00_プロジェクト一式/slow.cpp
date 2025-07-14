//=============================================================================
//
// スローモーション処理 [slow.h]
// Author : 佐々木奏一郎
//
//=============================================================================

#include "slow.h"
#include "sound.h"

//グローバル変数宣言
//	グローバル
//	頂点バッファへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffSlow = NULL;
D3DXCOLOR g_colorSlow;
Slow g_Slow;
int g_nCntSlowState;

//----------------
// スローの初期化処理
//----------------
void InitSlow(void)
{
	g_Slow.fMulti = 1.0f;
	g_Slow.fDivi = 1.0f;
	g_Slow.nMulti = 1;
	g_Slow.nDivi = 1;
	g_Slow.fade = SLOWFADE_IN;
	g_Slow.color = D3DXCOLOR(0.0f, 0.0f, 0.3f, 1.0f);
	g_Slow.bUse = false;
	g_nCntSlowState = 0;

	

	//	デバイス情報の取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//	頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffSlow,
		NULL);

	VERTEX_2D* pVtx;
	//	ロック
	g_pVtxBuffSlow->Lock(0, 0, (void**)&pVtx, 0);

	//	頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);

	//	rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//	頂点カラー
	pVtx[0].col = D3DXCOLOR(g_Slow.color);
	pVtx[1].col = D3DXCOLOR(g_Slow.color);
	pVtx[2].col = D3DXCOLOR(g_Slow.color);
	pVtx[3].col = D3DXCOLOR(g_Slow.color);

	//	アンロック
	g_pVtxBuffSlow->Unlock();

}

//-------------------
//スローの終了処理
//-------------------
void UninitSlow(void)
{
	// SEを止める
	StopSound(SOUND_LABEL_SE3);

	//	頂点バッファの破棄
	if (g_pVtxBuffSlow != NULL)
	{
		g_pVtxBuffSlow->Release();
		g_pVtxBuffSlow = NULL;
	}
}

//-------------------
// スローの更新処理
//-------------------
void UpdateSlow(void)
{
	if (g_Slow.bUse == true)
	{
		g_Slow.fade = SLOWFADE_OUT;
		g_nCntSlowState++;
		if (g_nCntSlowState > 600)
		{
			g_nCntSlowState = 0;
			g_Slow.fade = SLOWFADE_IN;
			g_Slow.bUse = false;
			SetSlow();
		}
	}
	if (g_Slow.fade!= SLOWFADE_NONE)
	{
		if (g_Slow.fade == SLOWFADE_IN)
		{
			//	フェードイン
			g_Slow.color.a -= 0.01f;		//ポリゴンが透明になる速さ
			if (g_Slow.color.a <= 0.0f)
			{
				g_Slow.color.a = 0.0f;
				g_Slow.fade = SLOWFADE_NONE;		//何もしていない状態
			}
		}
		else if (g_Slow.fade == SLOWFADE_OUT)
		{
			//	フェードアウト
			g_Slow.color.a += 0.02f;

			if (g_Slow.color.a >= 0.3f)
			{
				g_Slow.color.a = 0.3f;
			}
		}

		VERTEX_2D* pVtx;
		//	ロック
		g_pVtxBuffSlow->Lock(0, 0, (void**)&pVtx, 0);

		//	頂点カラー
		pVtx[0].col = D3DXCOLOR(g_Slow.color);
		pVtx[1].col = D3DXCOLOR(g_Slow.color);
		pVtx[2].col = D3DXCOLOR(g_Slow.color);
		pVtx[3].col = D3DXCOLOR(g_Slow.color);

		//	アンロック
		g_pVtxBuffSlow->Unlock();
	}
}

//-------------------
// スローの描画処理
//-------------------
void DrawSlow(void)
{
	//	デバイス情報の取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//	テクスチャの設定
	pDevice->SetTexture(0, NULL);

	//	頂点フォーマットの設定
	pDevice->SetStreamSource(0, g_pVtxBuffSlow, 0, sizeof(VERTEX_2D));

	//	頂点フォーマット設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//	ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

void SetSlow()
{
	if (g_Slow.bUse == true)
	{
		g_Slow.fMulti = (int)SLOW;
		g_Slow.fDivi = 1.0 / SLOW;
		g_Slow.nMulti = SLOW;
	}
	else if (g_Slow.bUse == false)
	{
		g_Slow.fMulti = 1.0f;
		g_Slow.fDivi = 1.0f;
		g_Slow.nMulti = 1;
	}
}

Slow*GetSlow(void)
{
	return &g_Slow;
}