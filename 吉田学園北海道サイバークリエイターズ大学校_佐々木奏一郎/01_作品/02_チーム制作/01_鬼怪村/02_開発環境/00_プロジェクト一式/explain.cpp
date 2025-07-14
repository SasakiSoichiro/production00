//=============================================================================
//
// アイテム表示の処理 [KeyUI.cpp]
// Author : chikada shouya
//
//=============================================================================
#include "explain.h"
#include "item.h"
#include "input.h"

// グローバル変数
LPDIRECT3DTEXTURE9 g_ExplainTexture[EXPLAINTYPE_MAX] = { };	// Uiテクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffExplain = NULL;			// Uiバッファへのポインタ

LPDIRECT3DTEXTURE9 g_ExplainTexture2 = NULL;				// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffExplain2 = NULL;			// バッファ

EXPLAIN g_Explain[EXPLAINTYPE_MAX];

bool bCount,bCount1,bCount2;

//=============================================================================
//アイテムUI表示の初期化処理
//=============================================================================
void InitExplain()
{
	LPDIRECT3DDEVICE9 pDevice;					// デバイスへのポインタ
	pDevice = GetDevice();						// デバイスの取得

	for (int nCnt = 0; nCnt < EXPLAINTYPE_MAX; nCnt++)
	{
			// テクスチャの読込
		D3DXCreateTextureFromFile(pDevice,
			EXPLAIN_TEXTURE[nCnt],
			&g_ExplainTexture[nCnt]);
	}

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\texture\\usukawa.png",
		&g_ExplainTexture2);

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * EXPLAINTYPE_MAX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffExplain, NULL);

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffExplain2,NULL);

	// 頂点情報へのポインタ
	VERTEX_2D* pVtx;

	bCount = false;
	bCount1 = false;
	bCount2 = false;

	// 頂点バッファのロック、頂点データへのポインタ取得
	g_pVtxBuffExplain->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt1 = 0; nCnt1 < EXPLAINTYPE_MAX; nCnt1++)
	{
		// 構造体変数の初期化
		g_Explain[nCnt1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Explain[nCnt1].fHeight = 0.0f;
		g_Explain[nCnt1].fWidth = 0.0f;
		g_Explain[nCnt1].bLook = false;
		g_Explain[nCnt1].bUse = false;

		// 頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(240.0f, 85.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(1040.0f, 85.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(240.0f, 635.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(1040.0f, 635.0f, 0.0f);

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
	g_pVtxBuffExplain->Unlock();

	// ロック
	g_pVtxBuffExplain2->Lock(0, 0, (void**)&pVtx, 0);

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
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// テクスチャ座標の設定　　１２５
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// アンロック
	g_pVtxBuffExplain2->Unlock();
}

//=============================================================================
// アイテムUI表示の終了処理
//=============================================================================
void UninitExplain()
{
	for (int nCnt = 0; nCnt < EXPLAINTYPE_MAX; nCnt++)
	{
		if (g_ExplainTexture[nCnt] != NULL)
		{
			g_ExplainTexture[nCnt]->Release();
			g_ExplainTexture[nCnt] = NULL;
		}
	}

	// 頂点バッファの破棄
	if (g_pVtxBuffExplain != NULL)
	{
		g_pVtxBuffExplain->Release();
		g_pVtxBuffExplain = NULL;
	}

	if (g_ExplainTexture2 != NULL)
	{
		g_ExplainTexture2->Release();
		g_ExplainTexture2 = NULL;
	}

	// 頂点バッファの破棄
	if (g_pVtxBuffExplain2 != NULL)
	{
		g_pVtxBuffExplain2->Release();
		g_pVtxBuffExplain2 = NULL;
	}
}

//=============================================================================
// アイテムUI表示の更新処理
//=============================================================================
void UpdateExplain()
{
	// アイテムの取得処理
	ITEM* pItem = Getitem();
	VERTEX_2D* pVtx;

	if (g_Explain[0].bLook == true || g_Explain[1].bLook == true || g_Explain[2].bLook == true)
	{
		// ロック
		g_pVtxBuffExplain2->Lock(0, 0, (void**)&pVtx, 0);

		// 頂点カラー
		pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.8f);
		pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.8f);
		pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.8f);
		pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.8f);

		// アンロック
		g_pVtxBuffExplain2->Unlock();
	}

	// 鍵の上部のみ取った場合
	if (pItem[2].bHold == true && bCount == false)
	{
		g_Explain[0].bLook = true;
	}

	// 鍵の下部のみ取った場合
	if (pItem[3].bHold == true && bCount1 == false)
	{
		g_Explain[1].bLook = true;
	}

	if (pItem[4].bHold == true && bCount2 == false)
	{
		g_Explain[2].bLook = true;
	}

	if (g_Explain[0].bLook == true && (GetJoypadPress(JOYKEY_A) == true || KeybordTrigger(DIK_RETURN) == true))
	{
		g_Explain[0].bLook = false;
		bCount = true;
	}

	if (g_Explain[1].bLook == true && (GetJoypadPress(JOYKEY_A) == true || KeybordTrigger(DIK_RETURN) == true))
	{
		g_Explain[1].bLook = false;
		bCount1 = true;
	}

	if (g_Explain[2].bLook == true && (GetJoypadPress(JOYKEY_A) == true || KeybordTrigger(DIK_RETURN) == true))
	{
		g_Explain[2].bLook = false;
		bCount2 = true;
	}
}

//=============================================================================
// アイテムUI表示の描画処理
//=============================================================================
void DrawExplain()
{
	// デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスの取得
	pDevice = GetDevice();

	//=====================================================================//
	// 頂点フォーマットの設定
	pDevice->SetStreamSource(0, g_pVtxBuffExplain2, 0, sizeof(VERTEX_2D));

	// 頂点フォーマット設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_ExplainTexture2);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	//=====================================================================//

	//=====================================================================//
	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffExplain, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCnt = 0; nCnt < EXPLAINTYPE_MAX; nCnt++)
	{

		if (g_Explain[0].bLook == true)
		{
			// テクスチャの設定
			pDevice->SetTexture(0, g_ExplainTexture[0]);
		}

		if (g_Explain[1].bLook == true)
		{
			// テクスチャの設定
			pDevice->SetTexture(0, g_ExplainTexture[1]);
		}
		if (g_Explain[2].bLook == true)
		{
			// テクスチャの設定
			pDevice->SetTexture(0, g_ExplainTexture[2]);
		}

		// アイテムUIの描画
		pDevice->DrawPrimitive(
			D3DPT_TRIANGLESTRIP,	//プリミティブの種類
			nCnt * 4,				//描画する最初の頂点インデックス
			2						//プリミティブ（アイテムUI）の数
		);
		
	}
	//=====================================================================//
}
//=============================================================================
// 鍵のUIの設定処理
//=============================================================================
void SetExplain(D3DXVECTOR3 pos, EXPLAINTYPE aType, float fWidth, float fHeight)
{
	// 頂点情報のポインタ
	VERTEX_2D* pVtx;

	// 頂点バッファのロック、頂点データへのポインタ取得
	g_pVtxBuffExplain->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < EXPLAINTYPE_MAX; nCnt++)
	{
		if (g_Explain[nCnt].bUse == false)
		{// 未使用状態だったら
			g_Explain[nCnt].pos = pos;
			g_Explain[nCnt].aType = aType;
			g_Explain[nCnt].fHeight = fHeight;
			g_Explain[nCnt].fWidth = fWidth;
			g_Explain[nCnt].bLook = false;
			g_Explain[nCnt].bUse = true;

			// 頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_Explain[nCnt].pos.x - fWidth, g_Explain[nCnt].pos.y - fHeight, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_Explain[nCnt].pos.x + fWidth, g_Explain[nCnt].pos.y - fHeight, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_Explain[nCnt].pos.x - fWidth, g_Explain[nCnt].pos.y + fHeight, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_Explain[nCnt].pos.x + fWidth, g_Explain[nCnt].pos.y + fHeight, 0.0f);
			break;
		}
		pVtx += 4;
	}
	// 頂点バッファをアンロック
	g_pVtxBuffExplain->Unlock();
}

//=============================================================================
// 取得(値を渡す)処理
//=============================================================================
EXPLAIN* GetExplain()
{
	return &g_Explain[0];
}
