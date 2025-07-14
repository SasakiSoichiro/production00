//====================================================
//
// 木の処理 [billboard.cpp]
// Author : yabuki yukito
//
//====================================================

#include "billboard.h"
#include "player.h"
#include "item.h"
#include "input.h"
#include "gimmick.h"

//++++++++++++++++++++++++++++++++++++++++++++++++++++
// グローバル変数宣言
//++++++++++++++++++++++++++++++++++++++++++++++++++++
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBillboard = NULL;					// 頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureBillboard[BILLBOARDTYPE_MAX] = {};		// テクスチャへのポインタ
Billboard g_Billboard[MAX_BILLBOARD];								// 構造体変数
bool bExchange;		// 脱出可能か否か
bool bNext;			// 溜めゲージが使用されているか否か
bool bChange;		// 鍵を持っていない(1 / 2)
bool bGive;			// 鍵を持っていない(0/2)

//====================================================
//アイテムの初期化処理
//====================================================
void InitBillboard()
{
	LPDIRECT3DDEVICE9 pDevice;			// デバイスへのポインタ

	pDevice = GetDevice();				// デバイスの取得

	// テクスチャの読み込み
	for (int nCnt = 0; nCnt < BILLBOARDTYPE_MAX; nCnt++)
	{
		D3DXCreateTextureFromFile(pDevice,
			ITEM_TEXTURE[nCnt],
			&g_pTextureBillboard[nCnt]);
	}

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_BILLBOARD,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBillboard, NULL);

	// 頂点情報のポインタ
	VERTEX_3D* pVtx = NULL;

	// 頂点バッファをロック
	g_pVtxBuffBillboard->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_BILLBOARD; nCnt++)
	{
		// 各変数の初期化
		g_Billboard[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Billboard[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Billboard[nCnt].bTest = false;
		g_Billboard[nCnt].bDisplay = true;
		g_Billboard[nCnt].bUse = false;

		bExchange = false;
		bNext = false;
		bChange = false;
		bGive = false;

		// 頂点情報の設定
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		// 各頂点の法線の設定(ベクトルの大きさは1にする)
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

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

	// 頂点バッファのアンロック
	g_pVtxBuffBillboard->Unlock();
}

//====================================================
//アイテムの終了処理
//====================================================
void UninitBillboard()
{
	// 頂点バッファの解放
	if (g_pVtxBuffBillboard != NULL)
	{
		g_pVtxBuffBillboard->Release();
		g_pVtxBuffBillboard = NULL;
	}

	for (int nCnt = 0; nCnt < BILLBOARDTYPE_MAX; nCnt++)
	{
		// テクスチャの破棄
		if (g_pTextureBillboard[nCnt] != NULL)
		{
			g_pTextureBillboard[nCnt]->Release();
			g_pTextureBillboard[nCnt] = NULL;
		}
	}
}

//====================================================
//アイテムの更新処理
//====================================================
void UpdateBillboard()
{
	// 頂点情報のポインタ
	VERTEX_3D* pVtx = NULL;

	Player* pPlayer = GetPlayer();		// プレイヤーの取得
	ITEM* pItem = Getitem();			// アイテムの取得
	bool isbill = IsBill();				// 範囲取得
	GIMMICK* pGimick = GetGimmick();	// ギミックの取得
	HOLD* pHold = GetHold();			// アイテムの取得判定変数

	// 頂点バッファをロック
	g_pVtxBuffBillboard->Lock(0, 0, (void**)&pVtx, 0);

	for (int count = 0; count < ITEMTYPE_MAX; count++,pItem++)
	{
		for (int nCnt = 0; nCnt < MAX_BILLBOARD; nCnt++)
		{

			if (pItem[count].bUse == true)
			{
				// プレイヤーの半径の算出用変数
				float fPRadPos = 28.0f;

				// アイテムの半径の算出用変数
				float fIRadPos = 28.0f;

				// プレイヤーの位置を取得
				D3DXVECTOR3 PlayerPos = GetPlayer()->pos;

				// アイテムのプレイヤーの距離の差
				D3DXVECTOR3 diff = PlayerPos - pItem->pos;

				// 範囲計算
				float fDisX = PlayerPos.x - pItem->pos.x;
				float fDisY = PlayerPos.y - pItem->pos.y;
				float fDisZ = PlayerPos.z - pItem->pos.z;

				// 二つの半径を求める
				float fRadX = fPRadPos + fIRadPos;

				// 回答格納用
				float fDistance = (fDisX * fDisX) + (fDisY * fDisY) + (fDisZ * fDisZ);
				float fRadius = (fRadX * fRadX);

				// プレイヤーがアイテムの範囲に入ったら
				if (fDistance < fRadius)
				{

					//拾うビルボードが使われてるとき
					//if (g_Billboard[nCnt].nType == BILLBOARDTYPE_1)
					//{

						g_Billboard[nCnt].bUse = true;
						g_Billboard[nCnt].bDisplay = true;
						g_Billboard[nCnt].pos.x = pItem->pos.x;
						g_Billboard[nCnt].pos.y = pItem->pos.y + 10.0f;
						g_Billboard[nCnt].pos.z = pItem->pos.z;

						// Fを押されたとき
						if (KeybordTrigger(DIK_F) == true)
						{
							g_Billboard[nCnt].bUse = false;
						}
					//}
				}

				// プレイヤーがアイテムの範囲外にいったら
				else if (fDistance > fRadius)
				{
					g_Billboard[nCnt].bDisplay = false;
				}
			}

			// 鍵を持った時
			if (pItem[0].bHold == true && pItem[1].bHold == true)
			{
				// プレイヤーの半径の算出用変数
				float fPRadPos = 50.0f;

				// アイテムの半径の算出用変数
				float fIRadPos = 50.0f;

				// プレイヤーの位置を取得
				D3DXVECTOR3 PlayerPos = GetPlayer()->pos;

				// アイテムのプレイヤーの距離の差
				D3DXVECTOR3 diff = PlayerPos - pGimick->pos;

				// 範囲計算
				float fDisX = PlayerPos.x - pGimick->pos.x;
				float fDisY = PlayerPos.y - pGimick->pos.y;
				float fDisZ = PlayerPos.z - pGimick->pos.z;

				// 二つの半径を求める
				float fRadX = fPRadPos + fIRadPos;

				// プレイヤーがアイテムの範囲に入ったら
				if ((fDisX * fDisX) + (fDisY * fDisY) + (fDisZ * fDisZ) <= (fRadX * fRadX))
				{

					if (g_Billboard[nCnt].nType == BILLBOARDTYPE_4)
					{
						bExchange = true;						// 脱出可能の条件文
						g_Billboard[nCnt].bUse = true;			// 使用
						g_Billboard[nCnt].bDisplay = true;		// 見る
					}			
				}

				// プレイヤーがアイテムの範囲外にいったら
				if ((fDisX * fDisX) + (fDisY * fDisY) + (fDisZ * fDisZ) > (fRadX * fRadX))
				{
					g_Billboard[nCnt].bDisplay = false;
				}
			}

			// (1/2)鍵を持った時
			else if (pItem[1].bHold == false && pItem[0].bHold == true)
			{
				// プレイヤーの半径の算出用変数
				float fPRadPos = 50.0f;

				// アイテムの半径の算出用変数
				float fIRadPos = 50.0f;

				// プレイヤーの位置を取得
				D3DXVECTOR3 PlayerPos = GetPlayer()->pos;

				// アイテムのプレイヤーの距離の差
				D3DXVECTOR3 diff = PlayerPos - pGimick->pos;

				// 範囲計算
				float fDisX = PlayerPos.x - pGimick->pos.x;
				float fDisY = PlayerPos.y - pGimick->pos.y;
				float fDisZ = PlayerPos.z - pGimick->pos.z;

				// 二つの半径を求める
				float fRadX = fPRadPos + fIRadPos;

				// プレイヤーがアイテムの範囲に入ったら
				if ((fDisX * fDisX) + (fDisY * fDisY) + (fDisZ * fDisZ) <= (fRadX * fRadX))
				{

					// 1/2鍵
					if (g_Billboard[nCnt].nType == BILLBOARDTYPE_3)
					{
						bChange = true;						// 脱出可能の条件文
						bGive = false;
						g_Billboard[nCnt].bUse = true;		// 使用
						g_Billboard[nCnt].bDisplay = true;	// 見る
					}
				}

				// プレイヤーがアイテムの範囲外にいったら
				if ((fDisX * fDisX) + (fDisY * fDisY) + (fDisZ * fDisZ) > (fRadX * fRadX))
				{
					g_Billboard[nCnt].bDisplay = false;
				}
			}

			// (1/2)鍵を持った時
			else if (pItem[0].bHold == false && pItem[1].bHold == true)
			{
				// プレイヤーの半径の算出用変数
				float fPRadPos = 50.0f;

				// アイテムの半径の算出用変数
				float fIRadPos = 50.0f;

				// プレイヤーの位置を取得
				D3DXVECTOR3 PlayerPos = GetPlayer()->pos;

				// アイテムのプレイヤーの距離の差
				D3DXVECTOR3 diff = PlayerPos - pGimick->pos;

				// 範囲計算
				float fDisX = PlayerPos.x - pGimick->pos.x;
				float fDisY = PlayerPos.y - pGimick->pos.y;
				float fDisZ = PlayerPos.z - pGimick->pos.z;

				// 二つの半径を求める
				float fRadX = fPRadPos + fIRadPos;

				// プレイヤーがアイテムの範囲に入ったら
				if ((fDisX * fDisX) + (fDisY * fDisY) + (fDisZ * fDisZ) <= (fRadX * fRadX))
				{
					// 1/2鍵
					if (g_Billboard[nCnt].nType == BILLBOARDTYPE_3)
					{
						bChange = true;						// 脱出可能の条件文
						bGive = false;
						g_Billboard[nCnt].bUse = true;		// 使用
						g_Billboard[nCnt].bDisplay = true;	// 見る
					}
				}

				// プレイヤーがアイテムの範囲外にいったら
				if ((fDisX * fDisX) + (fDisY * fDisY) + (fDisZ * fDisZ) > (fRadX * fRadX))
				{
					g_Billboard[nCnt].bDisplay = false;
				}
			}

			// (0/2)鍵を持ってない時
			else if (pItem[0].bHold == false && pItem[1].bHold == false)
			{
				// プレイヤーの半径の算出用変数
				float fPRadPos = 50.0f;

				// アイテムの半径の算出用変数
				float fIRadPos = 50.0f;

				// プレイヤーの位置を取得
				D3DXVECTOR3 PlayerPos = GetPlayer()->pos;

				// アイテムのプレイヤーの距離の差
				D3DXVECTOR3 diff = PlayerPos - pGimick->pos;

				// 範囲計算
				float fDisX = PlayerPos.x - pGimick->pos.x;
				float fDisY = PlayerPos.y - pGimick->pos.y;
				float fDisZ = PlayerPos.z - pGimick->pos.z;

				// 二つの半径を求める
				float fRadX = fPRadPos + fIRadPos;

				// プレイヤーがアイテムの範囲に入ったら
				if ((fDisX * fDisX) + (fDisY * fDisY) + (fDisZ * fDisZ) <= (fRadX * fRadX))
				{
					// 0/2鍵
					if (g_Billboard[nCnt].nType == BILLBOARDTYPE_2)
					{
						bGive = true;						// 脱出可能の条件文
						g_Billboard[nCnt].bUse = true;		// 使用
						g_Billboard[nCnt].bDisplay = true;	// 見る
					}
				}

				// プレイヤーがアイテムの範囲外にいったら
				if ((fDisX * fDisX) + (fDisY * fDisY) + (fDisZ * fDisZ) > (fRadX * fRadX))
				{
					g_Billboard[nCnt].bDisplay = false;
				}
			}
		}
	}

	// 頂点バッファのアンロック
	g_pVtxBuffBillboard->Unlock();
}

//====================================================
//アイテムの描画処理
//====================================================
void DrawBillboard()
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	ITEM* pItem = Getitem();

	// 計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;

	// ライトを無効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	for (int nCnt = 0; nCnt < MAX_BILLBOARD; nCnt++)
	{
		if (g_Billboard[nCnt].bUse == true && g_Billboard[nCnt].bDisplay == true)
		{
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_Billboard[nCnt].mtxWorld);

			D3DXMATRIX mtxView;
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			// カメラの逆行列を指定
			g_Billboard[nCnt].mtxWorld._11 = mtxView._11;
			g_Billboard[nCnt].mtxWorld._12 = mtxView._21;
			g_Billboard[nCnt].mtxWorld._13 = mtxView._31;
			g_Billboard[nCnt].mtxWorld._21 = mtxView._12;
			g_Billboard[nCnt].mtxWorld._22 = mtxView._22;
			g_Billboard[nCnt].mtxWorld._23 = mtxView._32;
			g_Billboard[nCnt].mtxWorld._31 = mtxView._13;
			g_Billboard[nCnt].mtxWorld._32 = mtxView._23;
			g_Billboard[nCnt].mtxWorld._33 = mtxView._33;

			// 位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_Billboard[nCnt].pos.x, g_Billboard[nCnt].pos.y, g_Billboard[nCnt].pos.z);
			D3DXMatrixMultiply(&g_Billboard[nCnt].mtxWorld, &g_Billboard[nCnt].mtxWorld, &mtxTrans);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_Billboard[nCnt].mtxWorld);

			// 頂点バッファをデバイスのデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffBillboard, 0, sizeof(VERTEX_3D));

			// 脱出可能の条件文
			if (bExchange == true && g_Billboard[nCnt].nType == BILLBOARDTYPE_4)
			{
				// テクスチャの設定
				pDevice->SetTexture(0, g_pTextureBillboard[4]);
			}
			// 溜めゲージの条件文
			else if (bNext == true && g_Billboard[nCnt].nType == BILLBOARDTYPE_5)
			{
				// テクスチャの設定
				pDevice->SetTexture(0, g_pTextureBillboard[5]);
			}
			// 鍵を持っていない(1/2)ときの条件文
			else if (bChange == true && g_Billboard[nCnt].nType == BILLBOARDTYPE_3)
			{
				// テクスチャの設定
				pDevice->SetTexture(0, g_pTextureBillboard[2]);
			}
			// 鍵を持っていない(0/2)ときの条件文
			else if (bGive == true && g_Billboard[nCnt].nType == BILLBOARDTYPE_2)
			{
				// テクスチャの設定
				pDevice->SetTexture(0, g_pTextureBillboard[3]);
			}
			// 全部の条件文以外
			else if (bExchange == false && bChange == false && bGive == false)
			{
				// テクスチャの設定
				pDevice->SetTexture(0, g_pTextureBillboard[g_Billboard[nCnt].nType]);
			}

			// 頂点フォーマット
			pDevice->SetFVF(FVF_VERTEX_3D);

			// アイテムの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);
		}
	}

	// ライトを有効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//====================================================
//アイテムの設定処理
//====================================================
void SetBillboard(D3DXVECTOR3 pos, D3DXVECTOR3 dir, TYPE nType, D3DXVECTOR3 size)
{
	VERTEX_3D* pVtx = NULL;		// 頂点情報のポインタ

	LPDIRECT3DDEVICE9 pDevice;	// デバイスへのポインタ

	pDevice = GetDevice();		// デバイスの取得

	// 頂点バッファをロック
	g_pVtxBuffBillboard->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_BILLBOARD; nCnt++)
	{
		if (g_Billboard[nCnt].bUse == false)
		{
			g_Billboard[nCnt].pos = pos;		// 位置
			g_Billboard[nCnt].nType = nType;	// 種類
			g_Billboard[nCnt].size = size;		// 大きさ
			g_Billboard[nCnt].bUse = true;		// 使用しているとき

			// 頂点情報の設定
			pVtx[0].pos = D3DXVECTOR3(-size.x, size.y, size.z);
			pVtx[1].pos = D3DXVECTOR3(size.x, size.y, size.z);
			pVtx[2].pos = D3DXVECTOR3(-size.x, -size.y, size.z);
			pVtx[3].pos = D3DXVECTOR3(size.x, -size.y, size.z);

			break;
		}

		pVtx += 4;
	}

	// 頂点バッファのアンロック
	g_pVtxBuffBillboard->Unlock();
}
