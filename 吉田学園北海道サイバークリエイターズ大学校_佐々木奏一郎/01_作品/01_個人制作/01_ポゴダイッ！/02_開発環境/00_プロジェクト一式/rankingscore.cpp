//=============================================================================
//
//	ランキングスコア処理 [rankingscore.cpp]
// Author : 佐々木奏一郎
//
//=============================================================================
#include "rankingscore.h"
#include "score.h"
#include "edit.h"
//#define MAX_POLYGON (40)
#define MAX_DIGIT (8)

#define TXTRANK0 ("data\\RANKING\\ranking000.txt")
#define TXTRANK1 ("data\\RANKING\\ranking001.txt")
#define TXTRANK2 ("data\\RANKING\\ranking002.txt")
#define TXTRANK3 ("data\\RANKING\\ranking003.txt")
#define TXTRANK4 ("data\\RANKING\\ranking004.txt")
#define TXTRANK5 ("data\\RANKING\\ranking005.txt")
#define TXTRANK6 ("data\\RANKING\\ranking006.txt")
#define TXTRANK7 ("data\\RANKING\\ranking007.txt")
#define TXTRANK8 ("data\\RANKING\\ranking008.txt")
#define TXTRANK9 ("data\\RANKING\\ranking009.txt")

typedef struct
{
	D3DXVECTOR3 pos;	//位置
	int nScore;			//スコア
	bool bUse;			//使われいるかどうか
}RankScore;
LPDIRECT3DTEXTURE9 g_pTextureRankScore = {};//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRankScore = NULL;//頂点バッファへのポインタ
RankScore g_aRankScore[MAX_RANK];//ランキングスコア情報
int g_nRankUpdate = -1;//更新ランクNo.
int g_nRankScore[MAX_RANK];

void InitRankingscore(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCnt;
	//デバイスの取得
	pDevice = GetDevice();
	//テクスチャの読み込み
		//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\number002.png",
		&g_pTextureRankScore);
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * (MAX_RANK * MAX_SCORE),//(sizeof(VERTEX_2D)*必要な頂点数
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRankScore,
		NULL);
	VERTEX_2D* pVtx;
	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffRankScore->Lock(0, 0, (void**)&pVtx, 0);
	for (nCnt = 0; nCnt < MAX_RANK; nCnt++)
	{
		g_aRankScore[nCnt].pos = D3DXVECTOR3(700.0f, 350.0f + (MAX_HEIGHT * nCnt) + (20.0f * nCnt), 0.0f);
		g_aRankScore[nCnt].nScore = 0;
		g_aRankScore[nCnt].bUse = true;
		g_nRankScore[nCnt] = 0;
		g_nRankUpdate = -1;
		for (int nCNT = 0; nCNT < MAX_DIGIT; nCNT++)
		{
			//頂点座標の設定
			pVtx[0].pos.x = g_aRankScore[nCnt].pos.x - MAX_WIDTH / 2 + (MAX_WIDTH * nCNT);
			pVtx[0].pos.y = g_aRankScore[nCnt].pos.y - MAX_WIDTH / 2;
			pVtx[0].pos.z = 0.0f;

			pVtx[1].pos.x = g_aRankScore[nCnt].pos.x + MAX_WIDTH / 2 + (MAX_WIDTH * nCNT);
			pVtx[1].pos.y = g_aRankScore[nCnt].pos.y - MAX_WIDTH / 2;
			pVtx[1].pos.z = 0.0f;

			pVtx[2].pos.x = g_aRankScore[nCnt].pos.x - MAX_WIDTH / 2 + (MAX_WIDTH * nCNT);
			pVtx[2].pos.y = g_aRankScore[nCnt].pos.y + MAX_WIDTH / 2;
			pVtx[2].pos.z = 0.0f;

			pVtx[3].pos.x = g_aRankScore[nCnt].pos.x + MAX_WIDTH / 2 + (MAX_WIDTH * nCNT);
			pVtx[3].pos.y = g_aRankScore[nCnt].pos.y + MAX_WIDTH / 2;
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
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);//←右回りで設定する
			pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);
			pVtx += 4;//頂点データのポインタを4つ分集める
		}
	}
	//頂点バッファをアンロックする
	g_pVtxBuffRankScore->Unlock();
}
//スコアの終了処理
void UninitRankingscore(void)
{
	//テクスチャの破棄
	if (g_pTextureRankScore != NULL)
	{
		g_pTextureRankScore->Release();
		g_pTextureRankScore = NULL;
	}
	//頂点バッファの破棄
	if (g_pVtxBuffRankScore != NULL)
	{
		g_pVtxBuffRankScore->Release();
		g_pVtxBuffRankScore = NULL;
	}
}
//スコアの更新処理
void UpdateRankingscore(void)
{
	static int nCnt = {};
	if (g_nRankUpdate != -1)
	{
		nCnt++;
		if (nCnt == 10)
		{
			VERTEX_2D* pVtx{};
			//頂点バッファをロックし、頂点情報へのポインタを取得
			g_pVtxBuffRankScore->Lock(0, 0, (void**)&pVtx, 0);
			pVtx += (32 * g_nRankUpdate);
			for (int nCnt = 0; nCnt < MAX_DIGIT; nCnt++)
			{
				//頂点カラーの設定　　　　
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
				pVtx += 4;
			}
			//頂点バッファをアンロックする
			g_pVtxBuffRankScore->Unlock();
		}
		else if (nCnt == 20)
		{
			VERTEX_2D* pVtx{};
			//頂点バッファをロックし、頂点情報へのポインタを取得
			g_pVtxBuffRankScore->Lock(0, 0, (void**)&pVtx, 0);
			pVtx += (32 * g_nRankUpdate);
			for (int nCnt = 0; nCnt < MAX_DIGIT; nCnt++)
			{
				//頂点カラーの設定　　　　
				pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
				pVtx += 4;
			}
			//頂点バッファをアンロックする
			g_pVtxBuffRankScore->Unlock();
			nCnt = 0;
		}
	}

}
void DrawRankingscore(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ
	int nCnt;
	//デバイスの取得
	pDevice = GetDevice();
	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffRankScore, 0, sizeof(VERTEX_2D));
	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	VERTEX_2D* pVtx;
	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffRankScore->Lock(0, 0, (void**)&pVtx, 0);
	for (nCnt = 0; nCnt < MAX_RANK*MAX_SCORE; nCnt++)
	{
		//if (g_aRankScore[nCnt].bUse == true)
		//{
			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureRankScore);
			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCnt, 2);
		//}
		
	}
	//頂点バッファをアンロックする
	g_pVtxBuffRankScore->Unlock();
}

void ResetRanking(void)
{
	FILE *pFile;
	int nStage=GetStage();
	switch (nStage)
	{
	case 0:
		pFile = fopen(TXTRANK0, "r");
		break;
	case 1:

		pFile = fopen(TXTRANK1, "r");
		break;
	case 2:
		pFile = fopen(TXTRANK2, "r");
		break;
	case 3:
		pFile = fopen(TXTRANK3, "r");
		break;
	case 4:
		pFile = fopen(TXTRANK4, "r");
		break;
	case 5:
		pFile = fopen(TXTRANK5, "r");
		break;
	case 6:
		pFile = fopen(TXTRANK6, "r");
		break;
	case 7:
		pFile = fopen(TXTRANK7, "r");
		break;
	case 8:
		pFile = fopen(TXTRANK8, "r");
		break;
	case 9:
		pFile = fopen(TXTRANK9, "r");
		break;
	default:
		pFile = NULL;
		break;
	}
	
	if (pFile != NULL)
	{
		for (int nCnt = 0; nCnt < MAX_RANK; nCnt++)
		{
			fscanf(pFile, "%d", &g_aRankScore[nCnt].nScore);
		}
	}
	else
	{
		MessageBox(NULL, "ファイルを開けません", "エラー", MB_OK);
		return;
	}
	fclose(pFile);
}
void Writescore(void)
{
	FILE* pFile;
	int nStage = GetStage();
	switch (nStage)
	{
	case 0:
		pFile = fopen(TXTRANK0, "w");
		break;
	case 1:
		pFile = fopen(TXTRANK1, "w");
		break;
	case 2:
		pFile = fopen(TXTRANK2, "w");
		break;
	case 3:
		pFile = fopen(TXTRANK3, "w");
		break;
	case 4:
		pFile = fopen(TXTRANK4, "w");
		break;
	case 5:
		pFile = fopen(TXTRANK5, "w");
		break;
	case 6:
		pFile = fopen(TXTRANK6, "w");
		break;
	case 7:
		pFile = fopen(TXTRANK7, "w");
		break;
	case 8:
		pFile = fopen(TXTRANK8, "w");
		break;
	case 9:
		pFile = fopen(TXTRANK9, "w");
		break;
	default:
		pFile = NULL;
		break;
	}

	if (pFile != NULL)
	{
		for (int nCnt = 0; nCnt < MAX_RANK; nCnt++)
		{
			fprintf(pFile, "%d\n", g_aRankScore[nCnt].nScore);
		}
	}
	else
	{
		MessageBox(NULL, "ファイルを開けません", "エラー", MB_OK);
		return;
	}
	fclose(pFile);
}
void SetRanking(int nScore)
{
	int nCntRank, nData{}, nCntScore;
	if (g_aRankScore[MAX_RANK - 1].nScore < nScore)
	{
		g_aRankScore[MAX_RANK - 1].nScore = nScore;
		g_nRankUpdate = MAX_RANK - 1;
	}
	for (nCntRank = 0; nCntRank < MAX_DIGIT; nCntRank++)
	{
		for (nCntScore = nCntRank + 1; nCntScore < MAX_RANK; nCntScore++)
		{
			if (g_aRankScore[nCntRank].nScore <= g_aRankScore[nCntScore].nScore)
			{
				nData = g_aRankScore[nCntRank].nScore;
				g_aRankScore[nCntRank].nScore = g_aRankScore[nCntScore].nScore;
				g_aRankScore[nCntScore].nScore = nData;
			}
		}
	}
	for (nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
	{
		if (nScore == g_aRankScore[nCntRank].nScore)
		{
			g_nRankUpdate = nCntRank;
			break;
		}
	}
	Writescore();
}
void SetRankingTexure(void)
{
	int aPosTexU[MAX_DIGIT] = {}, nData[2], nCnt;
	nData[0] = 10000000; nData[1] = 1000000;
	VERTEX_2D* pVtx;
	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffRankScore->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCNT = 0; nCNT < MAX_RANK; nCNT++)
	{
		g_nRankScore[nCNT] = g_aRankScore[nCNT].nScore;
		for (nCnt = 0; nCnt < MAX_DIGIT; nCnt++)
		{
			
			if (nCnt == 0)
			{
				aPosTexU[0] = g_nRankScore[nCNT] / nData[0];
			}
			else
			{
				aPosTexU[nCnt] = g_nRankScore[nCNT] % nData[0] / nData[1];
				nData[0] = nData[0] / 10;
				nData[1] = nData[1] / 10;
			}
			//テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(0.0f + (0.1f * aPosTexU[nCnt]), 0.0f);//←右回りで設定する
			pVtx[1].tex = D3DXVECTOR2(0.1f + (0.1f * aPosTexU[nCnt]), 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f + (0.1f * aPosTexU[nCnt]), 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.1f + (0.1f * aPosTexU[nCnt]), 1.0f);
			pVtx += 4;//頂点データのポインタを4つ分集める
		}
		nData[0] = 10000000; nData[1] = 1000000;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffRankScore->Unlock();
}
int GetRankScore(void)
{
	for (int nCnt = 0; nCnt < MAX_RANK; nCnt++)
	{
		return g_nRankScore[nCnt];
	}
}