//=============================================================================
//
//	スコア処理 [score.cpp]
// Author : 佐々木奏一郎
//
//=============================================================================
#include "score.h"
#include "rankingscore.h"
typedef struct
{
	bool bUse;

}Score;
//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureScore = NULL;//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffScore = NULL;//頂点バッファへのポインタ
D3DXVECTOR3 g_posScore;//スコアの位置
int g_nScore;//スコアの値
Score g_aScore[MAX_SCORE];
//====================
//スコアの初期化処理
//====================
void InitScore(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCnt;
	//デバイスの取得
	pDevice = GetDevice();
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\number002.png",
		&g_pTextureScore);
	g_posScore = D3DXVECTOR3(50.0f,350.0f,0.0f);//位置を初期化する
	//g_nScore = 0;
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4*MAX_SCORE,//(sizeof(VERTEX_2D)*必要な頂点数
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffScore,
		NULL);
	VERTEX_2D* pVtx;
	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);
	for (nCnt = 0; nCnt < MAX_SCORE; nCnt++)
	{
		//頂点座標の設定
		pVtx[0].pos.x = g_posScore.x - MAX_WIDTH / 2 + (MAX_WIDTH * nCnt);
		pVtx[0].pos.y = g_posScore.y - MAX_WIDTH / 2;
		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = g_posScore.x + MAX_WIDTH / 2 + (MAX_WIDTH * nCnt);
		pVtx[1].pos.y = g_posScore.y - MAX_WIDTH / 2;
		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = g_posScore.x - MAX_WIDTH / 2 + (MAX_WIDTH * nCnt);
		pVtx[2].pos.y = g_posScore.y + MAX_WIDTH / 2;
		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = g_posScore.x + MAX_WIDTH / 2 + (MAX_WIDTH * nCnt);
		pVtx[3].pos.y = g_posScore.y + MAX_WIDTH / 2;
		pVtx[3].pos.z = 0.0f;
		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		//頂点カラーの設定　　　　
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);
		pVtx += 4;//頂点データのポインタを4つ分集める
	}
	//頂点バッファをアンロックする
	g_pVtxBuffScore->Unlock();
}
//====================
//スコアの終了処理
//====================
void UninitScore(void)
{
	//テクスチャの破棄
	if (g_pTextureScore != NULL)
	{
		g_pTextureScore->Release();
		g_pTextureScore = NULL;
	}
	//頂点バッファの破棄
	if (g_pVtxBuffScore != NULL)
	{
		g_pVtxBuffScore->Release();
		g_pVtxBuffScore = NULL;
	}
}
//===================
//スコアの更新処理
//===================
void UpdateScore(void)
{
	int nData1, nData2;
	nData1 = ScoreCnt(g_nScore);//求めたスコアの桁数保存
	for (nData2 = 0; nData2 < MAX_SCORE; nData2++)
	{
		if (nData2 >= MAX_SCORE - nData1)
		{
			g_aScore[nData2].bUse = true;//0が表示されているとき
		}
		else
		{
			g_aScore[nData2].bUse = false;
		}
	}
}
//==================
// スコアの描画処理
//==================
void DrawScore(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ
	int nCnt;
	//デバイスの取得
	pDevice = GetDevice();
	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffScore, 0, sizeof(VERTEX_2D));
	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	VERTEX_2D* pVtx;
	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);
	for (nCnt = 0; nCnt < MAX_SCORE; nCnt++)
	{
		//if (g_aScore[nCnt].bUse == true)
		//{
			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureScore);
			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCnt, 2);
		//}
	}
	//頂点バッファをアンロックする
	g_pVtxBuffScore->Unlock();
}
//====================
//スコアの設定処理
//====================
void SetScore(int nScore)
{
	int aPosTexU[MAX_SCORE], nData[2], nCnt;
	nData[0] = 10000000; nData[1] = 1000000;;//各桁の数字を格納
	g_nScore = nScore;
	VERTEX_2D* pVtx;
	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);
	for (nCnt = 0; nCnt < MAX_SCORE; nCnt++)
	{
		if (nCnt==0)
		{
			aPosTexU[0] = g_nScore / nData[0];
		}
		else
		{
		aPosTexU[nCnt] = nScore % nData[0] / nData[1];
		nData[0] = nData[0] / 10;
		nData[1] = nData[1] / 10;
		}
		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f+(0.1f*aPosTexU[nCnt]), 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f + (0.1f * aPosTexU[nCnt]), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + (0.1f * aPosTexU[nCnt]), 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f + (0.1f * aPosTexU[nCnt]), 1.0f);
		pVtx += 4;//頂点データのポインタを4つ分集める
	}
	//頂点バッファをアンロックする
	g_pVtxBuffScore->Unlock();
}
//===================
//スコアの加算処理
//===================
void AddScore(int nValue)
{
	int aPosTexU[MAX_SCORE],nData[2], nCnt;
	nData[0] = 10000000; nData[1] = 1000000;
	g_nScore += nValue;
	VERTEX_2D* pVtx;
	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);
	for (nCnt = 0; nCnt < MAX_SCORE; nCnt++)
	{
		if (nCnt==0)
		{
			aPosTexU[0] = g_nScore / nData[0];
		}
		else
		{
			aPosTexU[nCnt] = g_nScore % nData[0] / nData[1];
			nData[0] =nData[0]/ 10;
			nData[1] =nData[1]/ 10;
		}
		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f + (0.1f * aPosTexU[nCnt]), 0.0f);//←右回りで設定する
		pVtx[1].tex = D3DXVECTOR2(0.1f + (0.1f * aPosTexU[nCnt]), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + (0.1f * aPosTexU[nCnt]), 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f + (0.1f * aPosTexU[nCnt]), 1.0f);
		pVtx += 4;//頂点データのポインタを4つ分集める
	}
	//頂点バッファをアンロックする
	g_pVtxBuffScore->Unlock();
}
//===================
// スコアの加算処理
//===================
int ScoreCnt(int nScore)
{
	int nNum = nScore;//スコアの０の部分をカウント
	int nKeepNum = 0;//スコアの桁数
	while (nNum != 0)//割り切れなくなるまで繰り返す
	{
		nNum /= 10;//10で割る
		nKeepNum++;//桁数を加算
	}
	if (nScore == 0)
	{
		nKeepNum = 1;//一桁目が０の時
	}
	return nKeepNum;
}
//==================
//スコアの取得
//==================
int GetScore(void)
{
	return g_nScore;
}