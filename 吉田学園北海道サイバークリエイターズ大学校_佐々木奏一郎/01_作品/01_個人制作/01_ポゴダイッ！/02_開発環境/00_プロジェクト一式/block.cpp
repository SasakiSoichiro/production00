//=============================================================================
//
//　ブロック処理 [block.cpp]
// 　Author : 佐々木奏一郎
//
//=============================================================================
#include "block.h"
#include "main.h"
#include "input.h"
#include "player.h"
#include "particle.h"
#include "sound.h"
#include "score.h"



//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureBlock[MAX_NUMBLOCK]= {};	//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBlock = NULL;			//頂点バッファへのポインタ
Block g_aBlock[MAX_BLOCK];								//ブロックの情報
//グローバル宣言
int g_nCntBlockState;
int g_nCntBlockState2;
bool g_bButton = false;
bool g_bUp = false;
bool g_goal = false;
bool g_Right = false;

//==================
//ブロックの初期化処理
//==================
void InitBlock(void)
{
	//ローカル変数
	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ
	VERTEX_2D* pVtx = 0;		//頂点情報へのポインタ

	//デバイスの取得
	pDevice = GetDevice();
	for (int nCnt = 0; nCnt < BLOCK_MAX; nCnt++)
	{
		//テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,
			BLOCK_TEXTURE[nCnt],
			&g_pTextureBlock[nCnt]);
	}
	//ループ処理
	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{//ブロックの数分ループする

		g_aBlock[nCntBlock].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//位置を初期化する
		g_aBlock[nCntBlock].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//移動値を初期化する
		g_aBlock[nCntBlock].fWidth = 0.0f;							//幅を初期化する
		g_aBlock[nCntBlock].fHeight = 0.0f;							//高さを初期化する
		g_aBlock[nCntBlock].nType = BLOCK_NORMAL;					//種類を初期化する
		g_aBlock[nCntBlock].bUse = false;							//使われていない状態にする	
	}

	g_bButton = false;
	g_goal = false;
	g_bUp = false;
	g_Right = false;
	g_nCntBlockState = 0; 
	g_nCntBlockState2 = 0;

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BLOCK,//(sizeof(VERTEX_2D)*必要な頂点数
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBlock,
		NULL);


	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	//ループ処理
	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{//ブロックの数分ループする

		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x - 40, g_aBlock[nCntBlock].pos.y - 40, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + 40, g_aBlock[nCntBlock].pos.y - 40, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x - 40, g_aBlock[nCntBlock].pos.y + 40, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + 40, g_aBlock[nCntBlock].pos.y + 40, 0.0f);

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
		pVtx[0].tex = D3DXVECTOR2(0.0f,0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx += 4;//頂点データのポインタを4つ分集める
	}
	//頂点バッファをアンロックする
	g_pVtxBuffBlock->Unlock();
}

//==================
//ブロックの終了処理
//==================
void UninitBlock(void)
{
	for (int nCnt = 0; nCnt < MAX_NUMBLOCK; nCnt++)
	{
		//テクスチャの破棄
		if (g_pTextureBlock[nCnt] != NULL)
		{
			g_pTextureBlock[nCnt]->Release();
			g_pTextureBlock[nCnt] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuffBlock != NULL)
	{
		g_pVtxBuffBlock->Release();
		g_pVtxBuffBlock = NULL;
	}

}

//==================
//ブロックの更新処理
//==================
void UpdateBlock(void)
{
	VERTEX_2D* pVtx = 0;	//頂点情報へのポインタ
	g_nCntBlockState++;
	g_nCntBlockState2++;
	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	//ループ処理
	for (int nCnt = 0; nCnt < MAX_BLOCK; nCnt++)
	{//ブロックの最大数分ぶん回す


		if (g_aBlock[nCnt].bUse == true)
		{//ブロックを使用している場合

			g_aBlock[nCnt].pos.x += g_aBlock[nCnt].move.x;
			g_aBlock[nCnt].pos.y += g_aBlock[nCnt].move.y;


			switch (g_aBlock[nCnt].nType)
			{
			case BLOCK_BUTTON://ボタン
				if (g_bButton == true)
				{
					if (g_aBlock[nCnt].pos.y < g_aBlock[nCnt].pos.y - g_aBlock[nCnt].fHeight)
					{
						g_aBlock[nCnt].bUse = false;
					}
						g_aBlock[nCnt].fHeight--;
						g_aBlock[nCnt].pos.y++;
				}
				break;

			case BLOCK_MOVEWALL://動く壁
				if (g_bButton == true)
				{
					if (g_aBlock[nCnt].pos.y < g_aBlock[nCnt].pos.y - g_aBlock[nCnt].fHeight)
					{
						g_aBlock[nCnt].bUse = false;
					}
					g_aBlock[nCnt].fHeight --;
					g_aBlock[nCnt].pos.y --;
						
						
				}
				break;
			case BLOCK_LR://左右に動く床
				if (g_Right==true)
				{
					g_aBlock[nCnt].move.x = MAX_MOVE;
				}
				else if(g_Right==false)
				{
					g_aBlock[nCnt].move.x = -MAX_MOVE;
				}
				if (g_nCntBlockState >= 180)
				{
					g_nCntBlockState = 0;
					g_Right = !g_Right;
				}
				break;
			case BLOCK_UPDOWN://左右に動く床

				if (g_bUp == true)
				{
					g_aBlock[nCnt].move.y = MAX_MOVE;
				}
				else if (g_bUp == false)
				{
					g_aBlock[nCnt].move.y = -MAX_MOVE;
				}
				if (g_nCntBlockState2 >= 180)
				{
					g_nCntBlockState2 = 0;
					g_bUp = !g_bUp;
				}
				break;
			}
			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_aBlock[nCnt].pos.x - g_aBlock[nCnt].fWidth, g_aBlock[nCnt].pos.y - g_aBlock[nCnt].fHeight, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aBlock[nCnt].pos.x + g_aBlock[nCnt].fWidth, g_aBlock[nCnt].pos.y - g_aBlock[nCnt].fHeight, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aBlock[nCnt].pos.x - g_aBlock[nCnt].fWidth, g_aBlock[nCnt].pos.y + g_aBlock[nCnt].fHeight, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aBlock[nCnt].pos.x + g_aBlock[nCnt].fWidth, g_aBlock[nCnt].pos.y + g_aBlock[nCnt].fHeight, 0.0f);
		}
		pVtx += 4;//4ずらす
	}


}

//==================
//ブロックの描画処理
//==================
void DrawBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();
	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffBlock, 0, sizeof(VERTEX_2D));
	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//ループ処理
	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{//ブロックの数分ループする

		if (g_aBlock[nCntBlock].bUse == true)
		{//弾が使用されている


			//テクスチャの設定
			pDevice->SetTexture(BLOCK_NORMAL, g_pTextureBlock[g_aBlock[nCntBlock].nType]);
			pDevice->SetTexture(BLOCK_BUTTON, g_pTextureBlock[g_aBlock[nCntBlock].nType]);
			pDevice->SetTexture(BLOCK_MOVEWALL, g_pTextureBlock[g_aBlock[nCntBlock].nType]);
			pDevice->SetTexture(BLOCK_SLIME, g_pTextureBlock[g_aBlock[nCntBlock].nType]);
			pDevice->SetTexture(BLOCK_TRANPORIN, g_pTextureBlock[g_aBlock[nCntBlock].nType]);
			pDevice->SetTexture(BLOCK_GOAL, g_pTextureBlock[g_aBlock[nCntBlock].nType]);
			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4*nCntBlock, 2);
		}
	}
}

//===================
//ブロックの設定処理
//===================
void SetBlock(D3DXVECTOR3 pos,	//位置の設定
				float fWidth,	//幅の設定
				float fHeight,	//高さの設定
				int nType)		//種類	

{	
	VERTEX_2D* pVtx=0;		//頂点情報へのポインタ
	float fU=0;				//テクスチャの枚数
	float fV = 0;			//テクスチャの枚数
	Player* pPlayer = GetPlayer();

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	//ループ処理
	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{//ブロックの最大数分ループする
		if (g_aBlock[nCntBlock].bUse == false)
		{//ブロックが使用されていない


			g_aBlock[nCntBlock].pos = pos;			//ブロックの頂点座標を代入
			g_aBlock[nCntBlock].fWidth=fWidth;		//ブロックの幅を代入
			g_aBlock[nCntBlock].fHeight = fHeight;	//ブロックの高さを代入
			g_aBlock[nCntBlock].nType = nType;		//ブロックの種類を代入
			g_aBlock[nCntBlock].bUse = true;		//使用している状態にする

			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x - fWidth, g_aBlock[nCntBlock].pos.y - fHeight, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + fWidth, g_aBlock[nCntBlock].pos.y - fHeight, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x - fWidth, g_aBlock[nCntBlock].pos.y + fHeight, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + fWidth, g_aBlock[nCntBlock].pos.y + fHeight, 0.0f);
			switch (g_aBlock[nCntBlock].nType)
			{
			case BLOCK_NORMAL://ノーマル

				//頂点座標の設定
				pVtx[0].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x - fWidth, g_aBlock[nCntBlock].pos.y - fHeight, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + fWidth, g_aBlock[nCntBlock].pos.y - fHeight, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x - fWidth, g_aBlock[nCntBlock].pos.y + fHeight, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + fWidth, g_aBlock[nCntBlock].pos.y + fHeight, 0.0f);

				fU = fWidth / MAX_BLOCKWIDTH;
				fV = fHeight / MAX_BLOCKHEIGHT;
				//テクスチャ座標の設定
				pVtx[0].tex = D3DXVECTOR2(fU, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(fU, fV);
				pVtx[3].tex = D3DXVECTOR2(0.0f, fV);
	

				break;

			case BLOCK_SLIME://スライム

				//頂点座標の設定
				pVtx[0].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x - fWidth, g_aBlock[nCntBlock].pos.y - fHeight, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + fWidth, g_aBlock[nCntBlock].pos.y - fHeight, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x - fWidth, g_aBlock[nCntBlock].pos.y + fHeight, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + fWidth, g_aBlock[nCntBlock].pos.y + fHeight, 0.0f);

				fU = fWidth / MAX_BLOCKWIDTH;
				fV = fHeight / MAX_BLOCKHEIGHT;
				//テクスチャ座標の設定
				pVtx[0].tex = D3DXVECTOR2(fU, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(fU, fV);
				pVtx[3].tex = D3DXVECTOR2(0.0f, fV);

				break;
			}
			
			break;
		}
		pVtx += 4;//頂点データのポインタを4つ分集める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffBlock->Unlock();
}


//===========================
//ブロックの当たり判定処理
//===========================
bool CollisionBlock(D3DXVECTOR3* pPos,		//現在のポゴ位置
	                D3DXVECTOR3* pPosOld,	//前回のポゴ位置
					D3DXVECTOR3* pPYPos,	//現在のプレイヤー位置
					D3DXVECTOR3* pPYPosOld,	//前回のプレイヤー位置
	                D3DXVECTOR3* pMove,		//移動量
					float fWidth,			//幅
					float fHeight,			//高さ
					Block**pBlock)			//pBlockのポインタ
{
	//ローカル変数
	bool bLanding = false;					//着地しているかどうか
	float Width = fWidth;					//プレイヤーの幅
	float Height = fHeight;					//プレイヤーの高さ
	float fX[4];
	float fY[4];
	D3DXVECTOR3 *PosOld=pPosOld;			//前フレームのポゴの位置
	D3DXVECTOR3* Pos = pPos;				//現フレームのポゴの位置
	D3DXVECTOR3* PYPosOld = pPYPosOld;		//前フレームのプレイヤーの位置
	D3DXVECTOR3* PYPos = pPYPos;			//現フレームのプレイヤーの位置
	Player*pPlayer= GetPlayer();

	
	//ループ処理
	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{//ブロックの最大数分ループする


		if (g_aBlock[nCntBlock].bUse == true)
		{//ブロックを使用している場合

			fX[0] = (g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].fWidth - pPos->x) * (g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].fWidth - pPos->x);
			fY[0] = (g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].fHeight - pPos->y) * (g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].fHeight - pPos->y);
			fX[1] = (g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth - pPos->x) * (g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth - pPos->x);
			fY[1] = (g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight - pPos->y) * (g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight - pPos->y);
			fX[2] = (g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].fWidth - pPYPos->x) * (g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].fWidth - pPYPos->x);
			fY[2] = (g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].fHeight - pPYPos->y) * (g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].fHeight - pPYPos->y);
			fX[3] = (g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth - pPYPos->x) * (g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth - pPYPos->x);
			fY[3] = (g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight - pPYPos->y) * (g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight - pPYPos->y);
				

				if ((pPos->x > g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].fWidth) && (pPos->x < g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth) && (pPos->y > g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].fHeight - MAX_POSCIRCLE) && (pPos->y < g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight + MAX_POSCIRCLE))
				{//上下のポゴ当たり判定

					
					//着地の判定をtrueにする
					bLanding = true;
					if (g_aBlock[nCntBlock].nType == BLOCK_GOAL)
					{
						g_goal = true;
					}

					//ジャンプしている

					//y方向のmove初期化
					pMove->y = 0.0f;
					if (pBlock != NULL)
					{//ブロックのアドレスを入れる場所がある
						*pBlock = &g_aBlock[nCntBlock];
					}

					if (g_aBlock[nCntBlock].nType == BLOCK_BUTTON)
					{
						g_bButton = true;
					}

				}


				if ((pPos->x > g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].fWidth - MAX_POSCIRCLE) && (pPos->x < g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth + MAX_POSCIRCLE) && (pPos->y > g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].fHeight) && (pPos->y < g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight))
				{//左右のポゴ当たり判定


					//着地の判定をtrueにする
					bLanding = true;
					if (g_aBlock[nCntBlock].nType == BLOCK_GOAL)
					{
						g_goal = true;
					}
					//ジャンプしている

					//x方向のmove初期化
					pMove->x = 0.0f;
					if (pBlock != NULL)
					{//ブロックのアドレスを入れる場所がある
						*pBlock = &g_aBlock[nCntBlock];
					}
					if (g_aBlock[nCntBlock].nType == BLOCK_BUTTON)
					{
						g_bButton = true;
					}

				}


				if (fX[0] + fY[0] < MAX_POSCIRCLE * MAX_POSCIRCLE)
				{//右上のポゴ当たり判定


					//着地の判定をtrueにする
					bLanding = true;
					if (g_aBlock[nCntBlock].nType == BLOCK_GOAL)
					{
						g_goal = true;
					}
					//x方向のmove初期化
					pMove->x = 0.0f;

					if (pBlock != NULL)
					{//ブロックのアドレスを入れる場所がある
						*pBlock = &g_aBlock[nCntBlock];
					}
					if (g_aBlock[nCntBlock].nType == BLOCK_BUTTON)
					{
						g_bButton = true;
					}

				}


				if (fX[1] + fY[0] < MAX_POSCIRCLE * MAX_POSCIRCLE)
				{//左上のポゴ当たり判定


					//着地の判定をtrueにする
					bLanding = true;

					if (g_aBlock[nCntBlock].nType == BLOCK_GOAL)
					{
						g_goal = true;
					}

								//ジャンプしている

					//x方向のmove初期化
					pMove->x = 0.0f;

					if (pBlock != NULL)
					{//ブロックのアドレスを入れる場所がある
						*pBlock = &g_aBlock[nCntBlock];
					}
					if (g_aBlock[nCntBlock].nType == BLOCK_BUTTON)
					{
						g_bButton = true;
					}

				}


				if (fX[0] + fY[1] < MAX_POSCIRCLE * MAX_POSCIRCLE)
				{//右下のポゴ当たり判定


					//着地の判定をtrueにする
					bLanding = true;

					if (g_aBlock[nCntBlock].nType == BLOCK_GOAL)
					{
						g_goal = true;
					}


					//x方向のmove初期化
					pMove->x = 0.0f;

					if (pBlock != NULL)
					{//ブロックのアドレスを入れる場所がある
						*pBlock = &g_aBlock[nCntBlock];
					}
					if (g_aBlock[nCntBlock].nType == BLOCK_BUTTON)
					{
						g_bButton = true;
					}

				}


				if (fX[1] + fY[1] < MAX_POSCIRCLE * MAX_POSCIRCLE)
				{//左下のポゴ当たり判定


					//着地の判定をtrueにする
					bLanding = true;

					if (g_aBlock[nCntBlock].nType == BLOCK_GOAL)
					{
						g_goal = true;
						//AddScore(1000);
					}

					//x方向のmove初期化
					pMove->x = 0.0f;

					if (pBlock != NULL)
					{//ブロックのアドレスを入れる場所がある
						*pBlock = &g_aBlock[nCntBlock];
					}

					if (g_aBlock[nCntBlock].nType == BLOCK_BUTTON)
					{
						g_bButton = true;
					}

				}

				if ((pPYPos->x > g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].fWidth) && (pPYPos->x < g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth) && (pPYPos->y > g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].fHeight - MAX_POSCIRCLE) && (pPYPos->y < g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight + MAX_POSCIRCLE))
				{//上下のプレイヤー当たり判定

					//プレイヤーのライフを1減らす
					pPlayer->nLife--;


					if (g_aBlock[nCntBlock].nType == BLOCK_GOAL)
					{
						g_goal = true;

					}
					//y方向のmove初期化
					pMove->y = 0.0f;

					if (g_aBlock[nCntBlock].nType == BLOCK_BUTTON)
					{
						g_bButton = true;

					}

				}


				if ((pPYPos->x > g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].fWidth - MAX_POSCIRCLE) && (pPYPos->x < g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth + MAX_POSCIRCLE) && (pPYPos->y > g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].fHeight) && (pPYPos->y < g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight))
				{//左右のプレイヤー当たり判定

					//プレイヤーのライフを1減らす
					pPlayer->nLife--;

					//x方向のmove初期化
					pMove->x = 0.0f;
					//x方向のmove初期化
					pMove->y = 0.0f;

					if (g_aBlock[nCntBlock].nType == BLOCK_BUTTON)
					{
						g_bButton = true;
					}
					if (g_aBlock[nCntBlock].nType == BLOCK_GOAL)
					{
						g_goal = true;

					}
				}


				if (fX[2] + fY[2] < MAX_POSCIRCLE * MAX_POSCIRCLE)
				{//右上のプレイヤー当たり判定

					//プレイヤーのライフを1減らす
					pPlayer->nLife--;

					//x方向のmove初期化
					pMove->x = 0.0f;
					//x方向のmove初期化
					pMove->y = 0.0f;

					if (g_aBlock[nCntBlock].nType == BLOCK_BUTTON)
					{
						g_bButton = true;
					}
					if (g_aBlock[nCntBlock].nType == BLOCK_GOAL)
					{
						g_goal = true;


					}
				}

				if (fX[3] + fY[2] < MAX_POSCIRCLE * MAX_POSCIRCLE)
				{//左上のプレイヤー当たり判定

					//プレイヤーのライフを1減らす
					pPlayer->nLife--;

					//x方向のmove初期化
					pMove->x = 0.0f;
					//x方向のmove初期化
					pMove->y = 0.0f;

					if (g_aBlock[nCntBlock].nType == BLOCK_BUTTON)
					{
						g_bButton = true;
					}
					if (g_aBlock[nCntBlock].nType == BLOCK_GOAL)
					{
						g_goal = true;

					}
				}


				if (fX[2] + fY[3] < MAX_POSCIRCLE * MAX_POSCIRCLE)
				{//右下のプレイヤー当たり判定

					//プレイヤーのライフを1減らす
					pPlayer->nLife--;

					//x方向のmove初期化
					pMove->x = 0.0f;
					//x方向のmove初期化
					pMove->y = 0.0f;
					if (g_aBlock[nCntBlock].nType == BLOCK_BUTTON)
					{
						g_bButton = true;
					}
					if (g_aBlock[nCntBlock].nType == BLOCK_GOAL)
					{
						g_goal = true;

					}
				}

				if (fX[3] + fY[3] < MAX_POSCIRCLE * MAX_POSCIRCLE)
				{//左下のプレイヤー当たり判定

					//プレイヤーのライフを1減らす
					pPlayer->nLife--;

					//x方向のmove初期化
					pMove->x = 0.0f;
					//x方向のmove初期化
					pMove->y = 0.0f;
					if (g_aBlock[nCntBlock].nType == BLOCK_BUTTON)
					{
						g_bButton = true;
					}
					if (g_aBlock[nCntBlock].nType == BLOCK_GOAL)
					{
						g_goal = true;

					}
				}

		}
	}

	//bLandingの値を返す
	return bLanding;
}
bool GetGoal(void)
{
	return g_goal;
}
bool GetButton(void)
{
	return &g_bButton;
}