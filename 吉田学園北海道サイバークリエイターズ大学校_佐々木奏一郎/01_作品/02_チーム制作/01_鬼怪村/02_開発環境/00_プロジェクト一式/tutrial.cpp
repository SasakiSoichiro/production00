//=========================================
//
//		チュートリアル		tutrial.cpp
//
//			hirata ryuusei
//
//=========================================
#include "tutrial.h"
#include "input.h"
#include "fade.h"

// グローバル
LPDIRECT3DTEXTURE9 g_apTextureTutrial = NULL;			// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTutrial = NULL;		// 頂点バッファへのポインタ

// 初期化処理
void InitTutrial(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	// テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\texture\\tutrial000.png",
		&g_apTextureTutrial);

	// 頂点バッファ
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTutrial,
		NULL);

	VERTEX_2D* pVtx;
	
	// ロック
	g_pVtxBuffTutrial->Lock(0, 0, (void**)&pVtx, 0);

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
	g_pVtxBuffTutrial->Unlock();
}

// 終了処理
void UninitTutrial(void)
{
	// テクスチャの破棄
	if (g_apTextureTutrial != NULL)
	{
		g_apTextureTutrial->Release();
		g_apTextureTutrial = NULL;
	}

	//頂点バッファの解放
	if (g_pVtxBuffTutrial != NULL)
	{
		g_pVtxBuffTutrial->Release();
		g_pVtxBuffTutrial = NULL;
	}
}

// 更新処理
void UpdateTutrial(void)
{
	if (KeybordTrigger(DIK_RETURN) || GetJoypadPress(JOYKEY_A) == true || OnMouseDown(MOUSE_L) == true)
	{// エンターが押されたら
		SetFade(MODE_GAME);
	}
}

// 描画処理
void DrawTutrial(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	// 頂点フォーマットの設定
	pDevice->SetStreamSource(0, g_pVtxBuffTutrial, 0, sizeof(VERTEX_2D));

	// 頂点フォーマット設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_apTextureTutrial);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}