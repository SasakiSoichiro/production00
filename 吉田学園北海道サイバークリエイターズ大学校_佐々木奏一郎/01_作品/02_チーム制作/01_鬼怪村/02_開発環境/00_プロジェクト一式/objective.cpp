//=============================================================================
//
//　アイテム持つ処理 [objective.cpp]
// 　Author : 佐々木奏一郎
//
//=============================================================================
#include "objective.h"
#include "player.h"
#include "input.h"
#include "item.h"

#define MAX_OBJECTIVE (10)

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureObjective[OBJECTIVETYPE_MAX] = {};		//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffObjective = NULL;		//頂点バッファへのポインタ
OBJECTIVE g_aObjective[MAX_OBJECTIVE];							//ブロックの情報

//=============================================================================
//アイテムUIの初期化処理
//=============================================================================
void InitObjective(void)
{
	//ローカル変数
	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ
	VERTEX_2D* pVtx = 0;		//頂点情報へのポインタ

	//デバイスの取得
	pDevice = GetDevice();
	for (int nCnt = 0; nCnt < OBJECTIVETYPE_MAX; nCnt++)
	{
		//テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,
			OBJECTIVE_TEXTURE[nCnt],
			&g_pTextureObjective[nCnt]);
	}
	//ループ処理
	for (int nCntBlock = 0; nCntBlock < MAX_OBJECTIVE; nCntBlock++)
	{//ブロックの数分ループする

		g_aObjective[nCntBlock].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//位置を初期化する
		g_aObjective[nCntBlock].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//移動値を初期化する
		g_aObjective[nCntBlock].fWidth = 0.0f;							//幅を初期化する
		g_aObjective[nCntBlock].fHeight = 0.0f;						//高さを初期化する
		g_aObjective[nCntBlock].nType = OBJECTIVETYPE_OBJECTIVE;					//種類を初期化する
		g_aObjective[nCntBlock].bUse = false;							//使われていない状態にする	
		g_aObjective[nCntBlock].bText = false;							//使われていない状態にする	

	}

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_OBJECTIVE,//(sizeof(VERTEX_2D)*必要な頂点数
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffObjective,
		NULL);


	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffObjective->Lock(0, 0, (void**)&pVtx, 0);

	//ループ処理
	for (int nCntBlock = 0; nCntBlock < MAX_OBJECTIVE; nCntBlock++)
	{//ブロックの数分ループする

		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

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

		pVtx += 4;//頂点データのポインタを4つ分集める
	}
	//頂点バッファをアンロックする
	g_pVtxBuffObjective->Unlock();
}

//=============================================================================
//アイテムUIの終了処理
//=============================================================================
void UninitObjective(void)
{
	for (int nCnt = 0; nCnt < OBJECTIVETYPE_MAX; nCnt++)
	{
		//テクスチャの破棄
		if (g_pTextureObjective[nCnt] != NULL)
		{
			g_pTextureObjective[nCnt]->Release();
			g_pTextureObjective[nCnt] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuffObjective != NULL)
	{
		g_pVtxBuffObjective->Release();
		g_pVtxBuffObjective = NULL;
	}

}

//=============================================================================
//アイテムUIの更新処理
//=============================================================================
void UpdateObjective(void)
{
	ITEM* pItem = Getitem();
	VERTEX_2D* pVtx = 0;	//頂点情報へのポインタ

	for (int nCnt = 0; nCnt < MAX_OBJECTIVE; nCnt++)
	{
		if (pItem[0].bHold == true && pItem[1].bHold == true)
		{
			g_aObjective[nCnt].bText = true;
		}
		if (g_aObjective[nCnt].nType == OBJECTIVETYPE_CHECK)
		{
			g_aObjective[nCnt].bUse = false;
		}
		if (g_aObjective[nCnt].bText == true && g_aObjective[nCnt].nType == OBJECTIVETYPE_CHECK)
		{
			g_aObjective[nCnt].bUse = true;
		}
		else if (g_aObjective[nCnt].bText == true && g_aObjective[nCnt].nType == OBJECTIVETYPE_WAKU1)
		{
			g_aObjective[nCnt].bUse = false;
		}
	}

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffObjective->Lock(0, 0, (void**)&pVtx, 0);

	//ループ処理
	for (int nCntBlock = 0; nCntBlock < MAX_OBJECTIVE; nCntBlock++)
	{//ブロックの数分ループする

		if (g_aObjective[nCntBlock].nType == OBJECTIVETYPE_TEXT1)
		{
			if (g_aObjective[nCntBlock].bText == false)
			{
				//頂点カラーの設定　　　　
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			}
			else if (g_aObjective[nCntBlock].bText == true)
			{
				//頂点カラーの設定　　　　
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.4f);
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.4f);
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.4f);
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.4f);

			}
		}

		if (g_aObjective[nCntBlock].nType == OBJECTIVETYPE_TEXT2)
		{
			if (g_aObjective[nCntBlock].bText == true)
			{
				//頂点カラーの設定　　　　
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			}
			else if (g_aObjective[nCntBlock].bText == false)
			{
				//頂点カラーの設定　　　　
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.4f);
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.4f);
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.4f);
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.4f);

			}
		}
		pVtx += 4;//頂点データのポインタを4つ分集める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffObjective->Unlock();

}

//=============================================================================
//アイテムUIの描画処理
//=============================================================================
void DrawObjective(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();
	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffObjective, 0, sizeof(VERTEX_2D));
	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//ループ処理
	for (int nCntItemUI = 0; nCntItemUI < MAX_OBJECTIVE; nCntItemUI++)
	{//ブロックの数分ループする

		if (g_aObjective[nCntItemUI].bUse == true)
		{
			// テクスチャの設定
			pDevice->SetTexture(0, g_pTextureObjective[g_aObjective[nCntItemUI].nType]);

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntItemUI, 2);
		}
	}
}

//=============================================================================
// 設定処理
//=============================================================================
void SetObjective(D3DXVECTOR3 pos, float fWidth, float fHeight, OBJECTIVETYPE nType)
{
	VERTEX_2D* pVtx = 0;		//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffObjective->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntUI = 0; nCntUI < OBJECTIVETYPE_MAX; nCntUI++)
	{
		if (g_aObjective[nCntUI].bUse == false)
		{// 未使用状態だったら
			g_aObjective[nCntUI].pos = pos;
			g_aObjective[nCntUI].nType = nType;
			g_aObjective[nCntUI].fHeight = fHeight;
			g_aObjective[nCntUI].fWidth = fWidth;
			g_aObjective[nCntUI].bText = false;
			g_aObjective[nCntUI].bUse = true;
			

			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_aObjective[nCntUI].pos.x - fWidth, g_aObjective[nCntUI].pos.y - fHeight, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aObjective[nCntUI].pos.x + fWidth, g_aObjective[nCntUI].pos.y - fHeight, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aObjective[nCntUI].pos.x - fWidth, g_aObjective[nCntUI].pos.y + fHeight, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aObjective[nCntUI].pos.x + fWidth, g_aObjective[nCntUI].pos.y + fHeight, 0.0f);
			break;
		}
		pVtx += 4;
	}
	//頂点バッファをアンロック
	g_pVtxBuffObjective->Unlock();
}

//=============================================================================
//選択した情報を渡す処理
//=============================================================================
OBJECTIVE* GetObjective()
{
	return &g_aObjective[0];
}