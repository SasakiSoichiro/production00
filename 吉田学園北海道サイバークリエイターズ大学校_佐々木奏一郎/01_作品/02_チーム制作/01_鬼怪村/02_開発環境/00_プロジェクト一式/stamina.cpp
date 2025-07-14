//====================================================
//
// スタミナの処理 [stamina.cpp]
// Author : Sasaki Soichiro
//
//====================================================

#include "stamina.h"
#include "player.h"
#include "enemy.h"

//マクロ定義
#define MAX_TIMEWIDTH (1000)
#define MAX_TIMEHEIGHT (10)

//グローバル変数
D3DXVECTOR3 StaminaPos;								// スタミナの位置
LPDIRECT3DTEXTURE9 g_StaminaTexture;				// スタミナテクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffStamina = NULL;	// バッファへのポインタ
int g_nCntState;
bool bStamina;
bool bScreen;
int g_nStamina;

//====================================================
//表示の初期化処理
//====================================================
void InitStamina()
{
	VERTEX_2D* pVtx=NULL;

	LPDIRECT3DDEVICE9 pDevice;					//デバイスへのポインタ

	pDevice = GetDevice();						//デバイスの取得

	StaminaPos = D3DXVECTOR3(150.0f, 700.0f, 0.0f);

	bStamina = true;
	bScreen = false;

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\texture\\staminaFrame.png",
		&g_StaminaTexture);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4*STAMINA_MAX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffStamina, NULL);

	//頂点バッファのロック、頂点データへのポインタ取得
	g_pVtxBuffStamina->Lock(0, 0, (void**)&pVtx, 0);

	// ループ処理
	for (int nCntStamina = 0; nCntStamina <STAMINA_MAX; nCntStamina++)
	{// ブロックの数分ループする

		//頂点情報の設定
		pVtx[0].pos.x = StaminaPos.x - 0.0f;
		pVtx[0].pos.y = StaminaPos.y - MAX_TIMEHEIGHT;
		pVtx[0].pos.z = StaminaPos.z;
						
		pVtx[1].pos.x = StaminaPos.x + MAX_TIMEWIDTH;
		pVtx[1].pos.y = StaminaPos.y - MAX_TIMEHEIGHT;
		pVtx[1].pos.z = StaminaPos.z;
						
		pVtx[2].pos.x = StaminaPos.x - 0.0f;
		pVtx[2].pos.y = StaminaPos.y + MAX_TIMEHEIGHT;
		pVtx[2].pos.z = StaminaPos.z;
						
		pVtx[3].pos.x = StaminaPos.x + MAX_TIMEWIDTH;
		pVtx[3].pos.y = StaminaPos.y + MAX_TIMEHEIGHT;
		pVtx[3].pos.z = StaminaPos.z;

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		switch (nCntStamina)
		{
		case STAMINA_GAUGE:
			//頂点カラーの設定
			pVtx[0].col = D3DXCOLOR(0.5f, 0.5f, 0.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(0.5f, 0.5f, 0.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(0.5f, 0.5f, 0.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(0.5f, 0.5f, 0.0f, 1.0f);
			break;
		case STAMINA_FRAME:
			//頂点カラーの設定
			pVtx[0].col = D3DXCOLOR(0.6f, 0.6f, 0.6f, 1.0f);
			pVtx[1].col = D3DXCOLOR(0.6f, 0.6f, 0.6f, 1.0f);
			pVtx[2].col = D3DXCOLOR(0.6f, 0.6f, 0.6f, 1.0f);
			pVtx[3].col = D3DXCOLOR(0.6f, 0.6f, 0.6f, 1.0f);
			break;
		}

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}

	//頂点バッファをアンロック
	g_pVtxBuffStamina->Unlock();
}

//====================================================
//表示の終了処理
//====================================================
void UninitStamina()
{

	// テクスチャの破棄
	if (g_StaminaTexture != NULL)
	{
		g_StaminaTexture->Release();
		g_StaminaTexture = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffStamina != NULL)
	{
		g_pVtxBuffStamina->Release();
		g_pVtxBuffStamina = NULL;
	}

}

//====================================================
//表示の更新処理
//====================================================
void UpdateStamina()
{
	Player* pPlayer = GetPlayer();
	bool pRange = IsRange();

	int nDate = 2;
	int aDate = 1;

	VERTEX_2D* pVtx=0;

	g_nStamina = pPlayer->nStamina;
	if (pPlayer->pState == PLAYERSTATE_DASH)
	{//プレイヤーが走っているとき

		if (pRange == false)
		{
			//スタミナ値を減らす
			pPlayer->nStamina--;

			if (pPlayer->nStamina <= 0)
			{//スタミナが0になったとき
				bStamina = false;
			}
		}
		else if (pRange == true)
		{
			//スタミナ値を減らす
			pPlayer->nStamina = pPlayer->nStamina - nDate;

			if (pPlayer->nStamina <= 0)
			{//スタミナが0になったとき
				bStamina = false;
			}
		}
	}
	else
	{
		if (pPlayer->nStamina <= 0)
		{//スタミナが0になったとき

			//カウントする
			g_nCntState++;

			if (g_nCntState >= 120)
			{//120Fたったら
				pPlayer->nStamina = 1;

				//カウントを初期化する
				g_nCntState = 0;

				//スタミナを使えるようにする
				bStamina = true;
			}

		}
		else if (pPlayer->nStamina < 400)
		{//スタミナが100未満で走っていないとき

			if (pRange == false)
			{
				pPlayer->nStamina++;
			}
			else if (pRange == true)
			{
				pPlayer->nStamina = pPlayer->nStamina + aDate;
			}
		}

	}

	float fStamina = (float(MAX_TIMEWIDTH)/400)*pPlayer->nStamina;
	//頂点バッファのロック、頂点データへのポインタ取得
	g_pVtxBuffStamina->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < STAMINA_MAX; nCnt++)
	{
		switch (nCnt)
		{
		case STAMINA_GAUGE:
			pVtx[0].pos.x = StaminaPos.x;
			pVtx[1].pos.x = StaminaPos.x + fStamina;
			pVtx[2].pos.x = StaminaPos.x;
			pVtx[3].pos.x = StaminaPos.x + fStamina;
			break;
		case STAMINA_FRAME:
			pVtx[0].pos.x = StaminaPos.x;
			pVtx[1].pos.x = StaminaPos.x + MAX_TIMEWIDTH;
			pVtx[2].pos.x = StaminaPos.x;
			pVtx[3].pos.x = StaminaPos.x + MAX_TIMEWIDTH;

			break;
		}
		pVtx += 4;
	}

	//頂点バッファをアンロック
	g_pVtxBuffStamina->Unlock();

	if (g_nStamina == pPlayer->nStamina)
	{
		bScreen = false;
	}
	else
	{
		bScreen = true;
	}

}

//====================================================
//表示の描画処理
//====================================================
void DrawStamina()
{
	LPDIRECT3DDEVICE9 pDevice;					//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffStamina, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCnt = 0; nCnt < STAMINA_MAX; nCnt++)
	{
		if (bScreen == true)
		{
			switch (nCnt)
			{
			case STAMINA_GAUGE:
				//ポリゴンの描画
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4*nCnt, 2);
				break;
			case STAMINA_FRAME:

				//// テクスチャの設定
				//pDevice->SetTexture(0, g_StaminaTexture);

				////ポリゴンの描画
				//pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4, 2);
				break;

			}

		}

	}


}
bool GetStamina(void)
{
	return bStamina;
}