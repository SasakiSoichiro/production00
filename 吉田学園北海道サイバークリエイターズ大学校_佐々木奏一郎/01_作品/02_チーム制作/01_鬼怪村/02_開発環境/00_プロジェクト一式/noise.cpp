//=============================================================================
//
//　ノイズ処理 [noise.cpp]
// 　Author : 佐々木奏一郎
//
//=============================================================================
#include "noise.h"
#define MAX_NOISE (3)
//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureNoise[NOISE_MAX] = {};		//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffNoise = NULL;			//頂点バッファへのポインタ
Noise g_Noise[MAX_NOISE];
int g_nCnt;
float g_aPosTexU[3];//テクスチャの開始位置(U値)
float g_aPosTexV[3];//テクスチャの開始位置(U値)


//=============================================================================
//ノイズの初期化処理
//=============================================================================
void InitNoise(void)
{
	//ローカル変数
	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ
	VERTEX_2D* pVtx = 0;		//頂点情報へのポインタ

	//デバイスの取得
	pDevice = GetDevice();
	for (int nCnt = 0; nCnt < NOISE_MAX; nCnt++)
	{
		//テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,
			NOISE_TEXTURE[nCnt],
			&g_pTextureNoise[nCnt]);
	}


	//ループ処理
	for (int nCntNoise = 0; nCntNoise < MAX_NOISE; nCntNoise++)
	{
		g_Noise[nCntNoise].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//位置を初期化する
		g_Noise[nCntNoise].fWidth = 0.0f;							//幅を初期化する
		g_Noise[nCntNoise].fHeight = 0.0f;							//高さを初期化する
		g_Noise[nCntNoise].nType = nCntNoise;						//種類を初期化する
		g_Noise[nCntNoise].bUse = false;							//使われていない状態にする
		g_aPosTexU[nCntNoise] = 0.0f;
		g_aPosTexV[nCntNoise] = 0.0f;

	}



	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4*MAX_NOISE,//(sizeof(VERTEX_2D)*必要な頂点数
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffNoise,
		NULL);



	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffNoise->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCnt = 0; nCnt < MAX_NOISE; nCnt++)
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

		// 頂点カラーの設定　　　　
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);

		// テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(g_aPosTexU[nCnt], g_aPosTexV[nCnt]);
		pVtx[1].tex = D3DXVECTOR2(g_aPosTexU[nCnt]+1.0f, g_aPosTexV[nCnt]);
		pVtx[2].tex = D3DXVECTOR2(g_aPosTexU[nCnt], g_aPosTexV[nCnt]+1.0f);
		pVtx[3].tex = D3DXVECTOR2(g_aPosTexU[nCnt]+1.0f, g_aPosTexV[nCnt]+1.0f);

		pVtx += 4;
	}

	// 頂点バッファをアンロックする
	g_pVtxBuffNoise->Unlock();
}

//=============================================================================
//ノイズの終了処理
//=============================================================================
void UninitNoise(void)
{
	for (int nCnt = 0; nCnt < NOISE_MAX; nCnt++)
	{
		//テクスチャの破棄
		if (g_pTextureNoise[nCnt] != NULL)
		{
			g_pTextureNoise[nCnt]->Release();
			g_pTextureNoise[nCnt] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuffNoise != NULL)
	{
		g_pVtxBuffNoise->Release();
		g_pVtxBuffNoise = NULL;
	}

}

//=============================================================================
//ノイズの更新処理
//=============================================================================
void UpdateNoise(void)
{

	VERTEX_2D* pVtx = 0;		//頂点情報へのポインタ



	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffNoise->Lock(0, 0, (void**)&pVtx, 0);

	RandNoise(&g_aPosTexU[0], &g_aPosTexV[0],0);

	// テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(g_aPosTexU[0], g_aPosTexV[0]);
	pVtx[1].tex = D3DXVECTOR2(g_aPosTexU[0] + 1.0f, g_aPosTexV[0]);
	pVtx[2].tex = D3DXVECTOR2(g_aPosTexU[0], g_aPosTexV[0] + 1.0f);
	pVtx[3].tex = D3DXVECTOR2(g_aPosTexU[0] + 1.0f, g_aPosTexV[0] + 1.0f);

	pVtx += 4;

	RandNoise(&g_aPosTexU[1], &g_aPosTexV[1],1);
	// テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(g_aPosTexU[1], g_aPosTexV[1]);
	pVtx[1].tex = D3DXVECTOR2(g_aPosTexU[1] + 1.0f, g_aPosTexV[1]);
	pVtx[2].tex = D3DXVECTOR2(g_aPosTexU[1], g_aPosTexV[1] + 1.0f);
	pVtx[3].tex = D3DXVECTOR2(g_aPosTexU[1] + 1.0f, g_aPosTexV[1] + 1.0f);

	pVtx += 4;

	RandNoise(&g_aPosTexU[2], &g_aPosTexV[2],2);
	// テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(g_aPosTexU[2], g_aPosTexV[2]);
	pVtx[1].tex = D3DXVECTOR2(g_aPosTexU[2] + 1.0f, g_aPosTexV[2]);
	pVtx[2].tex = D3DXVECTOR2(g_aPosTexU[2], g_aPosTexV[2] + 1.0f);
	pVtx[3].tex = D3DXVECTOR2(g_aPosTexU[2] + 1.0f, g_aPosTexV[2] + 1.0f);

	// 頂点バッファをアンロックする
	g_pVtxBuffNoise->Unlock();

	g_nCnt++;
}

//=============================================================================
//ノイズの描画処理
//=============================================================================
void DrawNoise(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ

	// デバイスの取得
	pDevice = GetDevice();
	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffNoise, 0, sizeof(VERTEX_2D));
	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntNoise = 0; nCntNoise < MAX_NOISE; nCntNoise++)
	{
		// テクスチャの設定
		pDevice->SetTexture(NOISE_A, g_pTextureNoise[g_Noise[nCntNoise].nType]);
		pDevice->SetTexture(NOISE_B, g_pTextureNoise[g_Noise[nCntNoise].nType]);
		pDevice->SetTexture(NOISE_C, g_pTextureNoise[g_Noise[nCntNoise].nType]);

		// ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,4*nCntNoise , 2);

	}

}

//=============================================================================
//ランダムな動きをさせる処理
//=============================================================================
void RandNoise(float *U, float *V ,int nCnt)
{
	int nRand[MAX_NOISE] = {};

	nRand[nCnt] = rand() % 6;
	g_nCnt = 0;

	
	switch (nRand[nCnt])
	{
	case 0:
		*U += 0.025f;
		*V += 0.025f;
		break;
	case 1:
		*U += 0.0025f;
		break;
	case 2:
		*U += 0.0065f;
		*V -= 0.0025f;
		break;
	case 3:
		*U += 0.05f;
		*V -= 0.0025f;
		break;
	case 4:
		*U -= 0.0025f;
		break;
	case 5:
		*U -= 0.0025f;
		*V -= 0.085f;
		break;
	}

}