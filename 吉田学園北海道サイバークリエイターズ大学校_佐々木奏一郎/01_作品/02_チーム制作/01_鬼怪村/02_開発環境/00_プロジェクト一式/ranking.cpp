//=============================================================
//
// Athor: HRT ryuusei  ランキング
// 
//=============================================================
#include "ranking.h"
#include "input.h"
#include "fade.h"
#include "game.h"
#include "stdio.h"
#include "time.h"
#include "player.h"

//ランキングスコアの構造体
typedef struct
{
	D3DXVECTOR3 pos;	//位置
	int nRank;			//順位
	int nTime;          //タイマー
	int nNs;			//秒
	int nMin;           //分
}RankTime;

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_pTextureBKG = NULL;			    //テクスチャへのポインタ(背景)
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBKG = NULL;			//頂点バッファへのポインタ(背景)

LPDIRECT3DTEXTURE9 g_pTextureRank = NULL;				//テクスチャへのポインタ(順位)
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRank = NULL;			//頂点バッファへのポインタ(順位)

LPDIRECT3DTEXTURE9 g_pTextureRankTime = NULL;			//テクスチャへのポインタ(秒・分)
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRankNs = NULL;		//頂点バッファへのポインタ(秒)
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRankMin = NULL;		//頂点バッファへのポインタ(分)

LPDIRECT3DTEXTURE9 g_pTextureRankColon = NULL;			//テクスチャへのポインタ(:)
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRankColon = NULL;		//頂点バッファへのポインタ(:)

RankTime g_aRankTime[MAX_RANK] = {};					//ランキングタイマー(5位分)表示
int g_nRankUpdate = -1;									//更新ランクNo.
int g_nTimerRanking;									//ランキング画面表示タイマー

//----------------------------
//ランキングの初期化処理
//----------------------------
void InitRanking(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	int nCntRank;
	int nRankTime;

	g_nRankUpdate = -1;//更新No.を初期化
	g_nTimerRanking = 0;
	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み(順位)
	D3DXCreateTextureFromFile(pDevice,
		"data\\texture\\number006.png",
		&g_pTextureRank);

	//テクスチャの読み込み(秒・分)
	D3DXCreateTextureFromFile(pDevice,
		"data\\texture\\number005.png",
		&g_pTextureRankTime);

	//テクスチャの読み込み(背景)
	D3DXCreateTextureFromFile(pDevice,
		"data\\texture\\BloodSplatter.png",
		&g_pTextureBKG);

	//テクスチャの読み込み(:)
	D3DXCreateTextureFromFile(pDevice,
		"data\\texture\\colon000.png",
		&g_pTextureRankColon);

	//頂点バッファの生成(順位)
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_RANK, //必要な頂点数
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRank,
		NULL);

	//頂点バッファの生成(秒)
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_RANK * MAX_RANKNS_NUM, //必要な頂点数
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRankNs,
		NULL);

	//頂点バッファの生成(分)
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_RANK * MAX_RANKMIN_NUM, //必要な頂点数
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRankMin,
		NULL);

	//頂点バッファの生成(:)
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_RANK, //必要な頂点数
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRankColon,
		NULL);

	//頂点バッファの生成(背景)
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, //必要な頂点数
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBKG,
		NULL);

	VERTEX_2D* pVtx;

	//秒
	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffRankNs->Lock(0, 0, (void**)&pVtx, 0);

	//ランキングの情報の初期化
	for (nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
	{//ランキングの順位分回す
		g_aRankTime[nCntRank].pos = D3DXVECTOR3(750.0f, 150.0f + MAX_RANKTIME_HEIGHT * nCntRank, 0.0f);
		g_aRankTime[nCntRank].nTime = 0;
		g_aRankTime[nCntRank].nRank = nCntRank + 1;

		for (nRankTime = 0; nRankTime < MAX_RANKNS_NUM; nRankTime++)
		{//秒の桁数分回す

			//頂点座標の設定
			pVtx[0].pos.x = g_aRankTime[nCntRank].pos.x - MAX_RANKTIME_WIDTH / 2 + MAX_RANKTIME_WIDTH * nRankTime;
			pVtx[0].pos.y = g_aRankTime[nCntRank].pos.y - MAX_RANKTIME_HEIGHT / 2;
			pVtx[0].pos.z = 0.0f;

			pVtx[1].pos.x = g_aRankTime[nCntRank].pos.x + MAX_RANKTIME_WIDTH / 2 + MAX_RANKTIME_WIDTH * nRankTime;
			pVtx[1].pos.y = g_aRankTime[nCntRank].pos.y - MAX_RANKTIME_HEIGHT / 2;
			pVtx[1].pos.z = 0.0f;

			pVtx[2].pos.x = g_aRankTime[nCntRank].pos.x - MAX_RANKTIME_WIDTH / 2 + MAX_RANKTIME_WIDTH * nRankTime;
			pVtx[2].pos.y = g_aRankTime[nCntRank].pos.y + MAX_RANKTIME_HEIGHT / 2;
			pVtx[2].pos.z = 0.0f;

			pVtx[3].pos.x = g_aRankTime[nCntRank].pos.x + MAX_RANKTIME_WIDTH / 2 + MAX_RANKTIME_WIDTH * nRankTime;
			pVtx[3].pos.y = g_aRankTime[nCntRank].pos.y + MAX_RANKTIME_HEIGHT / 2;
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

			pVtx += 4;//頂点データのポインタを四つ分進める
		}
	}
	//頂点バッファをアンロックする
	g_pVtxBuffRankNs->Unlock();

	//分
	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffRankMin->Lock(0, 0, (void**)&pVtx, 0);

	//ランキングの情報の初期化
	for (nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
	{//ランキングの順位分回す
		g_aRankTime[nCntRank].pos = D3DXVECTOR3(550.0f, 150.0f + MAX_RANKTIME_HEIGHT * nCntRank, 0.0f);
		g_aRankTime[nCntRank].nMin = 0;
		g_aRankTime[nCntRank].nRank = nCntRank + 1;

		for (nRankTime = 0; nRankTime < MAX_RANKMIN_NUM; nRankTime++)
		{//分の桁数分回す

			//頂点座標の設定
			pVtx[0].pos.x = g_aRankTime[nCntRank].pos.x - MAX_RANKTIME_WIDTH / 2 + MAX_RANKTIME_WIDTH * nRankTime;
			pVtx[0].pos.y = g_aRankTime[nCntRank].pos.y - MAX_RANKTIME_HEIGHT / 2;
			pVtx[0].pos.z = 0.0f;

			pVtx[1].pos.x = g_aRankTime[nCntRank].pos.x + MAX_RANKTIME_WIDTH / 2 + MAX_RANKTIME_WIDTH * nRankTime;
			pVtx[1].pos.y = g_aRankTime[nCntRank].pos.y - MAX_RANKTIME_HEIGHT / 2;
			pVtx[1].pos.z = 0.0f;

			pVtx[2].pos.x = g_aRankTime[nCntRank].pos.x - MAX_RANKTIME_WIDTH / 2 + MAX_RANKTIME_WIDTH * nRankTime;
			pVtx[2].pos.y = g_aRankTime[nCntRank].pos.y + MAX_RANKTIME_HEIGHT / 2;
			pVtx[2].pos.z = 0.0f;

			pVtx[3].pos.x = g_aRankTime[nCntRank].pos.x + MAX_RANKTIME_WIDTH / 2 + MAX_RANKTIME_WIDTH * nRankTime;
			pVtx[3].pos.y = g_aRankTime[nCntRank].pos.y + MAX_RANKTIME_HEIGHT / 2;
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

			pVtx += 4;//頂点データのポインタを四つ分進める
		}
	}
	//頂点バッファをアンロックする
	g_pVtxBuffRankNs->Unlock();

	//順位
	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffRank->Lock(0, 0, (void**)&pVtx, 0);

	//ランキングの情報の初期化
	for (nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
	{
		g_aRankTime[nCntRank].pos = D3DXVECTOR3(500.0f - MAX_RANK_WIDTH, 150.0f + MAX_RANKTIME_HEIGHT * nCntRank, 0.0f);

		//頂点座標の設定
		pVtx[0].pos.x = g_aRankTime[nCntRank].pos.x - MAX_RANK_WIDTH / 2;
		pVtx[0].pos.y = g_aRankTime[nCntRank].pos.y - MAX_RANKTIME_HEIGHT / 2;
		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = g_aRankTime[nCntRank].pos.x + MAX_RANK_WIDTH / 2;
		pVtx[1].pos.y = g_aRankTime[nCntRank].pos.y - MAX_RANKTIME_HEIGHT / 2;
		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = g_aRankTime[nCntRank].pos.x - MAX_RANK_WIDTH / 2;
		pVtx[2].pos.y = g_aRankTime[nCntRank].pos.y + MAX_RANKTIME_HEIGHT / 2;
		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = g_aRankTime[nCntRank].pos.x + MAX_RANK_WIDTH / 2;
		pVtx[3].pos.y = g_aRankTime[nCntRank].pos.y + MAX_RANKTIME_HEIGHT / 2;
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
		pVtx[0].tex = D3DXVECTOR2(0.1f + 0.1f * nCntRank, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.2f + 0.1f * nCntRank, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.1f + 0.1f * nCntRank, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.2f + 0.1f * nCntRank, 1.0f);

		pVtx += 4;//頂点データのポインタを四つ分進める
	}
	//頂点バッファをアンロックする
	g_pVtxBuffRank->Unlock();

	//背景
	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBKG->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);

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
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffBKG->Unlock();

	//:
	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffRankColon->Lock(0, 0, (void**)&pVtx, 0);

	//ランキングの情報の初期化
	for (nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
	{//ランキングの順位分回す
		g_aRankTime[nCntRank].pos = D3DXVECTOR3(730.0f - MAX_RANK_WIDTH, 150.0f + MAX_RANKTIME_HEIGHT * nCntRank, 0.0f);

		//頂点座標の設定
		pVtx[0].pos.x = g_aRankTime[nCntRank].pos.x - MAX_RANK_WIDTH / 2;
		pVtx[0].pos.y = g_aRankTime[nCntRank].pos.y - MAX_RANKTIME_HEIGHT / 2;
		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = g_aRankTime[nCntRank].pos.x + MAX_RANK_WIDTH / 2;
		pVtx[1].pos.y = g_aRankTime[nCntRank].pos.y - MAX_RANKTIME_HEIGHT / 2;
		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = g_aRankTime[nCntRank].pos.x - MAX_RANK_WIDTH / 2;
		pVtx[2].pos.y = g_aRankTime[nCntRank].pos.y + MAX_RANKTIME_HEIGHT / 2;
		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = g_aRankTime[nCntRank].pos.x + MAX_RANK_WIDTH / 2;
		pVtx[3].pos.y = g_aRankTime[nCntRank].pos.y + MAX_RANKTIME_HEIGHT / 2;
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
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;//頂点データのポインタを四つ分進める
	}
	//頂点バッファをアンロックする
	g_pVtxBuffRankColon->Unlock();

	//ランキングリセット
	ResetRanking(FILE_TXT_NS);

	ResetRanking(FILE_TXT_MIN);

	Player* pPlayer = GetPlayer();	//　プレイヤー情報取得

	

	//プレイヤーが死んだとき
	if (pPlayer->nLife <= 0)
	{

		//モード設定
		SetGameState(GAMESTATE_END);// ゲームを終了させる
		//タイマーの秒・分
		SetRanking(GetNs(), GetMin());
	}
	else
	{

		//タイマーの秒・分
		SetRanking(GetNs(), GetMin());

	}
}
//----------------------------
//ランキングの終了処理
//----------------------------
void UninitRanking(void)
{
	//テクスチャの破棄(順位)
	if (g_pTextureRank != NULL)
	{
		g_pTextureRank->Release();
		g_pTextureRank = NULL;
	}

	//テクスチャの破棄(タイマー)
	if (g_pTextureRankTime != NULL)
	{
		g_pTextureRankTime->Release();
		g_pTextureRankTime = NULL;
	}

	//テクスチャの破棄(背景)
	if (g_pTextureBKG != NULL)
	{
		g_pTextureBKG->Release();
		g_pTextureBKG = NULL;
	}

	//テクスチャの破棄(:)
	if (g_pTextureRankColon != NULL)
	{
		g_pTextureRankColon->Release();
		g_pTextureRankColon = NULL;
	}

	//頂点バッファの破棄(順位)
	if (g_pVtxBuffRank != NULL)
	{
		g_pVtxBuffRank->Release();
		g_pVtxBuffRank = NULL;
	}

	//頂点バッファの破棄(秒)
	if (g_pVtxBuffRankNs != NULL)
	{
		g_pVtxBuffRankNs->Release();
		g_pVtxBuffRankNs = NULL;
	}

	//頂点バッファの破棄(分)
	if (g_pVtxBuffRankMin != NULL)
	{
		g_pVtxBuffRankMin->Release();
		g_pVtxBuffRankMin = NULL;
	}

	//頂点バッファの破棄(背景)
	if (g_pVtxBuffBKG != NULL)
	{
		g_pVtxBuffBKG->Release();
		g_pVtxBuffBKG = NULL;
	}

	//頂点バッファの破棄(:)
	if (g_pVtxBuffRankColon != NULL)
	{
		g_pVtxBuffRankColon->Release();
		g_pVtxBuffRankColon = NULL;
	}

}
//----------------------------
//ランキングの更新処理
//----------------------------
void UpdateRanking(void)
{
	int nRankTime;

	g_nTimerRanking += 1;
	//頂点情報へのポインタ
	VERTEX_2D* pVtx;

	//秒
	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffRankNs->Lock(0, 0, (void**)&pVtx, 0);

	for (nRankTime = 0; nRankTime < MAX_RANKNS_NUM * MAX_RANK; nRankTime++)
	{//秒の桁数分回す
		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		pVtx += 4;
	}

	pVtx -= 4 * MAX_RANKNS_NUM * MAX_RANK;

	//該当タイマーランキング(秒)を点滅
	if (g_nRankUpdate != -1 && g_nTimerRanking >= 0)
	{//ランクインしてて、かつ、タイマーがゼロ以上だったら
		pVtx += 4 * MAX_RANKNS_NUM * g_nRankUpdate;

		for (nRankTime = 0; nRankTime < MAX_RANKNS_NUM; nRankTime++)
		{//秒の桁数分回す
			//頂点カラーの設定
			pVtx[0].col = D3DXCOLOR(0.3f, 1.0f, 0.3f, 1.0f);
			pVtx[1].col = D3DXCOLOR(0.3f, 1.0f, 0.3f, 1.0f);
			pVtx[2].col = D3DXCOLOR(0.3f, 1.0f, 0.3f, 1.0f);
			pVtx[3].col = D3DXCOLOR(0.3f, 1.0f, 0.3f, 1.0f);

			pVtx += 4;
		}
	}

	//頂点バッファをアンロックする
	g_pVtxBuffRankNs->Unlock();

	//分
	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffRankMin->Lock(0, 0, (void**)&pVtx, 0);

	for (nRankTime = 0; nRankTime < MAX_RANKMIN_NUM * MAX_RANK; nRankTime++)
	{//分の桁数分回す
		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		pVtx += 4;
	}

	pVtx -= 4 * MAX_RANKMIN_NUM * MAX_RANK;

	//該当タイマーランキング(分)を点滅
	if (g_nRankUpdate != -1 && g_nTimerRanking >= 0)
	{//ランクインしてて、かつ、タイマーがゼロ以上だったら
		pVtx += 4 * MAX_RANKMIN_NUM * g_nRankUpdate;

		for (nRankTime = 0; nRankTime < MAX_RANKMIN_NUM; nRankTime++)
		{//分の桁数分回す
			//頂点カラーの設定
			pVtx[0].col = D3DXCOLOR(0.3f, 1.0f, 0.3f, 1.0f);
			pVtx[1].col = D3DXCOLOR(0.3f, 1.0f, 0.3f, 1.0f);
			pVtx[2].col = D3DXCOLOR(0.3f, 1.0f, 0.3f, 1.0f);
			pVtx[3].col = D3DXCOLOR(0.3f, 1.0f, 0.3f, 1.0f);

			pVtx += 4;
		}
	}

	//頂点バッファをアンロックする
	g_pVtxBuffRankMin->Unlock();

	//:
	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffRankColon->Lock(0, 0, (void**)&pVtx, 0);

	for (nRankTime = 0; nRankTime < MAX_RANK; nRankTime++)
	{//:の順位分回す
		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		pVtx += 4;
	}

	pVtx -= 4 * MAX_RANK;

	//該当タイマーランキング(:)を点滅
	if (g_nRankUpdate != -1 && g_nTimerRanking >= 0)
	{//ランクインしてて、かつ、タイマーがゼロ以上だったら
		pVtx += 4 * g_nRankUpdate;

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(0.3f, 1.0f, 0.3f, 1.0f);
		pVtx[1].col = D3DXCOLOR(0.3f, 1.0f, 0.3f, 1.0f);
		pVtx[2].col = D3DXCOLOR(0.3f, 1.0f, 0.3f, 1.0f);
		pVtx[3].col = D3DXCOLOR(0.3f, 1.0f, 0.3f, 1.0f);

	}

	//頂点バッファをアンロックする
	g_pVtxBuffRankColon->Unlock();

	//タイマーをマイナスにする
	if (g_nTimerRanking >= 5)
	{
		g_nTimerRanking *= -1;
	}

	if (KeybordTrigger(DIK_RETURN) == true || JoyPadTrigger(JOYKEY_A) == true || OnMouseDown(MOUSE_L) == true)
	{
		//モード設定(ゲーム画面に移行)
		SetFade(MODE_TITLE);
	}
}
//----------------------------
//ランキングの描画処理
//----------------------------
void DrawRanking(void)
{
	int nCntTime;

	LPDIRECT3DDEVICE9 pDevice; //デバイスへのポインタ
	//デバイスの取得
	pDevice = GetDevice();

	//背景
	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffBKG, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureBKG);

	//ポリゴン描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//プリミティブの種類
		0,							//描画する最初の頂点インデックス
		2);

	//秒
	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffRankNs, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//ランキングスコアの描画
	for (nCntTime = 0; nCntTime < MAX_RANK * MAX_RANKNS_NUM; nCntTime++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureRankTime);
		//ポリゴン描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//プリミティブの種類
			4 * nCntTime,							//描画する最初の頂点インデックス
			2);
	}

	//分
	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffRankMin, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//ランキングスコアの描画
	for (nCntTime = 0; nCntTime < MAX_RANK * MAX_RANKMIN_NUM; nCntTime++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureRankTime);
		//ポリゴン描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//プリミティブの種類
			4 * nCntTime,							//描画する最初の頂点インデックス
			2);
	}

	//順位
	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffRank, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//エフェクトの描画
	for (nCntTime = 0; nCntTime < MAX_RANK; nCntTime++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureRank);
		//ポリゴン描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//プリミティブの種類
			4 * nCntTime,						   //描画する最初の頂点インデックス
			2);
	}

	//:
	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffRankColon, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//エフェクトの描画
	for (nCntTime = 0; nCntTime < MAX_RANK; nCntTime++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureRankColon);
		//ポリゴン描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//プリミティブの種類
			4 * nCntTime,						   //描画する最初の頂点インデックス
			2);
	}

}
//----------------------------
//ランキングのリセット
//----------------------------
void ResetRanking(const char* DateScore)
{
	int nCnt = 0;
	int foge = NULL;

	//ランキングスコア情報の初期設定
	FILE* pFile = fopen(FILE_TXT_NS, "r");

	if (pFile == NULL)
	{

	}
	else
	{

		//読み込む
		for (nCnt = 0; nCnt < MAX_RANK; nCnt++)
		{
			foge = fscanf(pFile, "%d\n", &g_aRankTime[nCnt].nTime);
		}

		fclose(pFile);
	}

	//ランキングスコア情報の初期設定
	pFile = fopen(FILE_TXT_MIN, "r");

	if (pFile == NULL)
	{

	}
	else
	{

		//読み込む
		for (nCnt = 0; nCnt < MAX_RANK; nCnt++)
		{
			foge = fscanf(pFile, "%d\n", &g_aRankTime[nCnt].nMin);
		}

		fclose(pFile);
	}

}
//----------------------------
//ランキングの設定
//----------------------------
void SetRanking(int ntime,int nmin)
{
	Player* pPlayer = GetPlayer();
	int nCntRank;
	int nSelect;
	int nTemp;
	int aPosTexU[MAX_RANKNS_NUM] = {};//格桁の数字を格納(秒)
	int aPosTexu[MAX_RANKMIN_NUM] = {};//格桁の数字を格納(分)
	int nData1,nData2,nData3,nData4;
	int nCnt;

	//---ランキングタイマーの並び替え
	//-----指定タイマーがランクインしたら g_nRankUpdate を更新
	if (pPlayer->nLife > 0)
	{
		if (ntime >= g_aRankTime[MAX_RANK - 1].nTime)//ソート処理
		{
			g_aRankTime[MAX_RANK - 1].nTime = ntime;

			for (nCntRank = 0; nCntRank < MAX_RANK - 1; nCntRank++)
			{
				for (nSelect = nCntRank + 1; nSelect < MAX_RANK; nSelect++)
				{
					if (g_aRankTime[nCntRank].nTime <= g_aRankTime[nSelect].nTime)
					{
						nTemp = g_aRankTime[nCntRank].nTime;
						g_aRankTime[nCntRank].nTime = g_aRankTime[nSelect].nTime;
						g_aRankTime[nSelect].nTime = nTemp;
					}
				}
			}
			//順位をぶち込む
			for (nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
			{
				if (g_aRankTime[nCntRank].nTime == ntime)
				{
					g_nRankUpdate = g_aRankTime[nCntRank].nRank - 1;
				}
			}
		}

		if (nmin >= g_aRankTime[MAX_RANK - 1].nMin)//ソート処理
		{
			g_aRankTime[MAX_RANK - 1].nMin = nmin;

			for (nCntRank = 0; nCntRank < MAX_RANK - 1; nCntRank++)
			{
				for (nSelect = nCntRank + 1; nSelect < MAX_RANK; nSelect++)
				{
					if (g_aRankTime[nCntRank].nMin <= g_aRankTime[nSelect].nMin)
					{
						nTemp = g_aRankTime[nCntRank].nMin;
						g_aRankTime[nCntRank].nMin = g_aRankTime[nSelect].nMin;
						g_aRankTime[nSelect].nMin = nTemp;
					}
				}
			}
			//順位をぶち込む
			for (nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
			{
				if (g_aRankTime[nCntRank].nMin == nmin)
				{
					g_nRankUpdate = g_aRankTime[nCntRank].nRank - 1;
				}
			}
		}
	}
	//頂点情報へのポインタ
	VERTEX_2D* pVtx;

	//秒
	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffRankNs->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
	{
		nData1 = 100;
		nData2 = 10;

		//桁ごとに分割する(秒)
		for (nCnt = 0; nCnt < MAX_RANKNS_NUM; nCnt++)
		{
			aPosTexU[nCnt] = (g_aRankTime[nCntRank].nTime % nData1 / nData2);
			nData1 = nData1 / 10;
			nData2 = nData2 / 10;

			//-----テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(0.0f + (0.1f * aPosTexU[nCnt]), 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.1f + (0.1f * aPosTexU[nCnt]), 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f + (0.1f * aPosTexU[nCnt]), 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.1f + (0.1f * aPosTexU[nCnt]), 1.0f);

			pVtx += 4;
		}
	}

	//頂点バッファをアンロックする
	g_pVtxBuffRankNs->Unlock();

	//分
	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffRankMin->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
	{
		nData3 = 100;
		nData4 = 10;

		//桁ごとに分割する(分)
		for (nCnt = 0; nCnt < MAX_RANKMIN_NUM; nCnt++)
		{
			aPosTexu[nCnt] = (g_aRankTime[nCntRank].nMin % nData3 / nData4);
			nData3 /= 10;
			nData4 /= 10;

			//-----テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(0.1f * aPosTexu[nCnt], 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.1f + (0.1f * aPosTexu[nCnt]), 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.1f * aPosTexu[nCnt], 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.1f + (0.1f * aPosTexu[nCnt]), 1.0f);

			pVtx += 4;
		}
	}

	//頂点バッファをアンロックする
	g_pVtxBuffRankMin->Unlock();

	//順位を書き込む
	//ランキングタイマー情報の初期設定
	FILE* pFile = fopen(FILE_TXT_NS, "w");

	if (pFile == NULL)
	{

	}
	else
	{

		//書き込む
		for (int nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
		{
			fprintf(pFile, "%d\n", g_aRankTime[nCntRank].nTime);
		}

		fclose(pFile);
	}

	//ランキングタイマー情報の初期設定
	pFile = fopen(FILE_TXT_MIN, "w");

	if (pFile == NULL)
	{

	}
	else
	{

		//書き込む
		for (int nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
		{
			fprintf(pFile, "%d\n", g_aRankTime[nCntRank].nMin);
		}

		fclose(pFile);
	}

}