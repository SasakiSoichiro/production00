//=============================================================================
//
//    解除ゲージ処理 [gauge.cpp]
//    Author : Chikada
//
//=============================================================================
#include "gauge.h"
#include "input.h"
#include "player.h"
#include "gimmick.h"
#include "item.h"

// グローバル
Gauge g_gauge = {};
LPDIRECT3DTEXTURE9 g_GaugeTexture =  NULL ;			// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffGauge = NULL;		// バッファへのポインタ

//===================
// 初期化処理
//===================
void InitGauge(void)
{
	VERTEX_2D* pVtx{};

	LPDIRECT3DDEVICE9 pDevice;					// デバイスへのポインタ
	pDevice = GetDevice();						// デバイスの取得

		// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\texture\\hold.jpg",
		&g_GaugeTexture);

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffGauge, NULL);

	// 頂点バッファのロック、頂点データへのポインタ取得
	g_pVtxBuffGauge->Lock(0, 0, (void**)&pVtx, 0);

	// 各変数の初期化
	g_gauge.bKeyhave = false;
	g_gauge.bUse = false;
	g_gauge.fCnt = 0.0f;
	g_gauge.fCnt1 = 0.0f;
	g_gauge.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// 頂点情報の設定
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

	// 頂点バッファをアンロック
	g_pVtxBuffGauge->Unlock();
}

//===================
//	終了処理
//===================
void UinitGauge(void)
{

	// テクスチャの破棄
	if (g_GaugeTexture != NULL)
	{
		g_GaugeTexture->Release();
		g_GaugeTexture = NULL;
	}
	
	// 頂点バッファの破棄
	if (g_pVtxBuffGauge != NULL)
	{
		g_pVtxBuffGauge->Release();
		g_pVtxBuffGauge = NULL;
	}
}

//===================
//	更新処理
//===================
void UpdateGauge(void)
{
	Player* pPlayer = GetPlayer();
	bool isbill = IsBill();			// 範囲取得
	ITEM* pItem = Getitem();

	VERTEX_2D* pVtx{};

	// 頂点バッファのロック、頂点データへのポインタ取得
	g_pVtxBuffGauge->Lock(0, 0, (void**)&pVtx, 0);

	// プレイヤーがアイテムの範囲に入ったら
	if (isbill == true)
	{
		g_gauge.bUse = true;

		if (pItem[0].bHold == true && pItem[1].bHold == true)
		{
			if (g_gauge.fCnt < 3.0f)
			{
				if (GetKeyboardPress(DIK_F) || GetJoypadPress(JOYKEY_B) == true)
				{
					g_gauge.fCnt += 0.01f;
				}
				else if (g_gauge.fCnt >= 0)
				{
					g_gauge.fCnt -= 0.01f;
				}
			}
			if (g_gauge.fCnt >= 3.0f)
			{
				g_gauge.fCnt = 3.0f;
			}
			if (g_gauge.fCnt < 0)
			{
				g_gauge.fCnt1 = 321.5f;
			}

			// 頂点情報の設定
			pVtx[0].pos.x = g_gauge.fCnt1;
			pVtx[0].pos.y = 399.5f;
			pVtx[0].pos.z = 0.0f;

			pVtx[1].pos.x = g_gauge.fCnt1 * g_gauge.fCnt;
			pVtx[1].pos.y = 399.5f;
			pVtx[1].pos.z = 0.0f;

			pVtx[2].pos.x = g_gauge.fCnt1;
			pVtx[2].pos.y = 450.5f;
			pVtx[2].pos.z = 0.0f;

			pVtx[3].pos.x = g_gauge.fCnt1 * g_gauge.fCnt;
			pVtx[3].pos.y = 450.5f;
			pVtx[3].pos.z = 0.0f;
		}
	}
	else
	{
		g_gauge.bUse = false;

		if (g_gauge.fCnt >= 0)
		{
			g_gauge.fCnt -= 0.01f;
		}
	}
	
	// 頂点バッファをアンロック
	g_pVtxBuffGauge->Unlock();
}

//===================
//	描画処理
//===================
void DrawGauge(void)
{
	// デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスの取得
	pDevice = GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffGauge, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	if (g_gauge.bUse == true)
	{
		// テクスチャの設定
		pDevice->SetTexture(0, g_GaugeTexture);
		
		// ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}
}

//===================
//	配置処理
//===================
void SetGauge(D3DXVECTOR3 pos)
{
	if (g_gauge.bUse == false)
	{
		g_gauge.pos = pos;
		
		g_gauge.bUse = true;
	}
}