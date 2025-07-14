//=============================================================================
//
//	タイム処理 [time.cpp]
// Author : 佐々木奏一郎
//
//=============================================================================
#include "time.h"
#include "score.h"
#include "player.h"
#include "block.h"
#include "fade.h"
typedef struct
{
	bool bUse;

}Time;
//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureTime = NULL;//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTime = NULL;//頂点バッファへのポインタ
D3DXVECTOR3 g_posTime;//スコアの位置
int g_nTime;//スコアの値
Time g_aTime[MAX_TIME];
int g_nTimeSecond;
//====================
//スコアの初期化処理
//====================
void InitTime(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCnt;
	//デバイスの取得
	pDevice = GetDevice();
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\number002.png",
		&g_pTextureTime);
	g_posTime = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//位置を初期化する
	g_nTime = 120;//値を初期化する

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TIME,//(sizeof(VERTEX_2D)*必要な頂点数
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTime,
		NULL);
	VERTEX_2D* pVtx;
	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffTime->Lock(0, 0, (void**)&pVtx, 0);
	for (nCnt = 0; nCnt < MAX_TIME; nCnt++)
	{
		g_aTime[nCnt].bUse = true;
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(600.0f + nCnt * 30.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(600.0f + nCnt * 30.0f + 30.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(600.0f + nCnt * 30.0f, 50.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(600.0f + nCnt * 30.0f + 30.0f, 50.0f, 0.0f);
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
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);//←右回りで設定する
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);
		pVtx += 4;//頂点データのポインタを4つ分集める
	}
	//頂点バッファをアンロックする
	g_pVtxBuffTime->Unlock();
}
//====================
//スコアの終了処理
//====================
void UninitTime(void)
{
	//テクスチャの破棄
	if (g_pTextureTime != NULL)
	{
		g_pTextureTime->Release();
		g_pTextureTime = NULL;
	}
	//頂点バッファの破棄
	if (g_pVtxBuffTime != NULL)
	{
		g_pVtxBuffTime->Release();
		g_pVtxBuffTime = NULL;
	}
}
//===================
//スコアの更新処理
//===================
void UpdateTime(void)
{
	int nData1, nData2, aPosTexU[MAX_TIME] = {},nCnt;

	VERTEX_2D* pVtx;

	bool goal = GetGoal();

	nData1 = 100;//求めたスコアの桁数保存
	nData2 = 10;
	g_nTimeSecond++;
	if (goal == false)
	{
		if (g_nTimeSecond >= 60)
		{
			g_nTimeSecond = 0;
			if (g_nTime != 0)
			{
				g_nTime--;
				AddScore(-5);
			}
			else if (g_nTime <= 0)
			{
				SetFade(MODE_GAME);
			}
		}
	}

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffTime->Lock(0, 0, (void**)&pVtx, 0);
	for (nCnt = 0; nCnt < MAX_TIME; nCnt++)
	{
		if (nCnt == 0)
		{
			aPosTexU[0] = g_nTime / nData1;
		}
		else
		{
			aPosTexU[nCnt] = g_nTime % nData1 / nData2;
			nData1 = nData1 / 10;
			nData2 = nData2 / 10;
		}
		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f + (0.1f * aPosTexU[nCnt]), 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f + (0.1f * aPosTexU[nCnt]), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + (0.1f * aPosTexU[nCnt]), 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f + (0.1f * aPosTexU[nCnt]), 1.0f);
		pVtx += 4;//頂点データのポインタを4つ分集める
	}
	//頂点バッファをアンロックする
	g_pVtxBuffTime->Unlock();
}
//==================
// スコアの描画処理
//==================
void DrawTime(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ
	int nCnt;
	//デバイスの取得
	pDevice = GetDevice();
	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTime, 0, sizeof(VERTEX_2D));
	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	VERTEX_2D* pVtx;
	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffTime->Lock(0, 0, (void**)&pVtx, 0);
	for (nCnt = 0; nCnt < MAX_TIME; nCnt++)
	{
		if (g_aTime[nCnt].bUse == true)
		{
			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureTime);
			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCnt, 2);
		}
	}
	//頂点バッファをアンロックする
	g_pVtxBuffTime->Unlock();
}
//===================
// スコアの加算処理
//===================
int TimeCnt(int nTime)
{
	int nNum = nTime;//スコアの０の部分をカウント
	int nKeepNum = 0;//スコアの桁数
	for (int nCnt = 0; nCnt < MAX_TIME; nCnt++)
	{
		if (nNum == 0)
		{
			for (int nCnt2 = 0; nCnt < nKeepNum; nCnt2++)
			{
				g_aTime[nCnt2].bUse = true;
			}
		}
		else
		{
			nNum /= 10;//10で割る
			nKeepNum++;//桁数を加算
		}
	}
	//while (nNum != 0)//割り切れなくなるまで繰り返す
	//{
	//	nNum /= 10;//10で割る
	//	nKeepNum++;//桁数を加算
	//}

	return nKeepNum;
}
//==================
//スコアの取得
//==================
int GetTime(void)
{
	return g_nTime;
}