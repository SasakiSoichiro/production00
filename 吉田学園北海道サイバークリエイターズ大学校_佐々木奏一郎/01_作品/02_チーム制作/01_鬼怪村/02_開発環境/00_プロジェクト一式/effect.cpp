//=============================================================================
//
// エフェクト処理 [effect.cpp]
// Author :Marina Harada
//
//=============================================================================
#include"effect.h"
#include"player.h"

// グローバル宣言
LPDIRECT3DTEXTURE9 g_pTextureeffect = NULL;			// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffeffect = NULL;	// 頂点バッファへのポインタ
Effect g_effect[MAX_EFFECT];

//=============================================================================
// エフェクトの初期化処理
//=============================================================================
void InitEffect(void)
{
	// デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスの取得
	pDevice = GetDevice();

	// 初期化
	for (int nCnt = 0; nCnt < MAX_EFFECT; nCnt++)
	{
		g_effect[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		g_effect[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		g_effect[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		g_effect[nCnt].col = D3DXCOLOR(1.0f, 1.0, 1.0f, 1.0f);

		g_effect[nCnt].nLife = 0;

		g_effect[nCnt].buse = false;
	}

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * 4 * MAX_EFFECT,		// 確保するバッファのサイズ、*数は必要な頂点数
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,							//頂点フォーマット
		D3DPOOL_MANAGED,
		&g_pVtxBuffeffect,
		NULL
	);

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\effect000.jpg",
		&g_pTextureeffect
	);

	// 頂点情報へのポインタ
	VERTEX_3D* pVtx = NULL;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffeffect->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_EFFECT; nCnt++)
	{
		// 頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_effect[nCnt].pos.x - 1.0f, g_effect[nCnt].pos.y + 1.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_effect[nCnt].pos.x + 1.0f, g_effect[nCnt].pos.y + 1.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_effect[nCnt].pos.x - 1.0f, g_effect[nCnt].pos.y - 1.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_effect[nCnt].pos.x + 1.0f, g_effect[nCnt].pos.y - 1.0f, 0.0f);

		// 各頂点の法線の設定(※ベクトルの大きさは１にする必要がある)
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		// 頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(0.5f, 0.5, 0.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(0.5f, 0.5, 0.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(0.5f, 0.5, 0.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(0.5f, 0.5, 0.0f, 1.0f);

		// テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}

	// 頂点バッファをアンロックする
	g_pVtxBuffeffect->Unlock();
}

//=============================================================================
//エフェクトの終了処理
//=============================================================================
void UninitEffect(void)
{
	// 頂点バッファの解放
	if (g_pVtxBuffeffect != NULL)
	{
		g_pVtxBuffeffect->Release();

		g_pVtxBuffeffect = NULL;
	}

	// テクスチャの破棄
	if (g_pTextureeffect != NULL)
	{
		g_pTextureeffect->Release();

		g_pTextureeffect = NULL;
	}
}

//=============================================================================
//エフェクトの更新処理
//=============================================================================
void UpdateEffect(void)
{
	Player* pPlayer = GetPlayer();

	for (int nCnt = 0; nCnt < MAX_EFFECT; nCnt++)
	{
		if (g_effect[nCnt].buse == true)
		{
			g_effect[nCnt].pos += g_effect[nCnt].move;

			g_effect[nCnt].nLife--;

			if (g_effect[nCnt].nLife <= 0)
			{
				g_effect[nCnt].buse = false;
			}
		}
	}
}

//=============================================================================
//エフェクトの描画処理
//=============================================================================
void DrawEffect(void)
{
	// デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスの取得
	pDevice = GetDevice();

	////αテストを有効
	//pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	//pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	//pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	// 減算合成の設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);	// Zの比較
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);		// Zバッファに書き込まない

	for (int nCnt = 0; nCnt < MAX_EFFECT; nCnt++)
	{
		if (g_effect[nCnt].buse == true)
		{
			// ライトを無効にする
			pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

			// 計算用マトリックス
			D3DXMATRIX mtxRot, mtxTrans;

			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_effect[nCnt].mtxWorld);

			D3DMATRIX mtxView;
			// ビューマトリックス取得
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			// カメラの逆行列を設定
			g_effect[nCnt].mtxWorld._11 = mtxView._11;
			g_effect[nCnt].mtxWorld._12 = mtxView._21;
			g_effect[nCnt].mtxWorld._13 = mtxView._31;
			g_effect[nCnt].mtxWorld._21 = mtxView._12;
			g_effect[nCnt].mtxWorld._22 = mtxView._22;
			g_effect[nCnt].mtxWorld._23 = mtxView._32;
			g_effect[nCnt].mtxWorld._31 = mtxView._13;
			g_effect[nCnt].mtxWorld._32 = mtxView._23;
			g_effect[nCnt].mtxWorld._33 = mtxView._33;

			// 位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_effect[nCnt].pos.x, g_effect[nCnt].pos.y, g_effect[nCnt].pos.z);
			D3DXMatrixMultiply(&g_effect[nCnt].mtxWorld, &g_effect[nCnt].mtxWorld, &mtxTrans);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_effect[nCnt].mtxWorld);

			// 頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(
				0,
				g_pVtxBuffeffect,
				0,
				sizeof(VERTEX_3D)
			);

			// テクスチャの設定
			pDevice->SetTexture(0, g_pTextureeffect);

			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			// エフェクトの描画
			pDevice->DrawPrimitive(
				D3DPT_TRIANGLESTRIP,	// プリミティブの種類
				nCnt * 4,				// 描画する最初の頂点インデックス
				2						// プリミティブ（背景）の数
			);

			// ライトを有効に戻す
			pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
		}
	}

	////αテストを無効に戻す
	//pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);

	// 設定を元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);	// Zの比較方法変更
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);		// Zバッファに書き込む
}

//=============================================================================
//エフェクトの設定
//=============================================================================
void SetEffect(D3DXVECTOR3 pos, D3DXVECTOR3 dir, int nLife, D3DXCOLOR col)
{
	for (int nCnt = 0; nCnt < MAX_EFFECT; nCnt++)
	{
		if (g_effect[nCnt].buse == false)
		{
			g_effect[nCnt].pos = pos;
			g_effect[nCnt].move = dir;
			g_effect[nCnt].nLife = nLife;
			g_effect[nCnt].col = col;
			g_effect[nCnt].buse = true;
			break;
		}
	}

}