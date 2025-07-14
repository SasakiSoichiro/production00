//=============================================================================
//
//　ムーブブロック処理 [moveblock.cpp]
// 　Author : 佐々木奏一郎
//
//=============================================================================
#include "moveblock.h"
#include "main.h"
#include "input.h"
#include "player.h"
#include "particle.h"

//マクロ定義
#define MAX_MOVEBLOCK (128)		//ブロックの最大数
#define MAX_NUMMOVEBLOCK (3)	//ブロックの種類

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureMoveBlock[MAX_NUMMOVEBLOCK] = {};	//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMoveBlock = NULL;			//頂点バッファへのポインタ
MoveBlock g_aMoveBlock[MAX_MOVEBLOCK];								//ブロックの情報


//==================
//ブロックの初期化処理
//==================
void InitMoveBlock(void)
{
	//ローカル変数
	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ
	VERTEX_2D* pVtx = 0;		//頂点情報へのポインタ

	//デバイスの取得
	pDevice = GetDevice();
	for (int nCnt = 0; nCnt < BLOCK_MOVEMAX; nCnt++)
	{
		//テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,
			MOVEBLOCK_TEXTURE[nCnt],
			&g_pTextureMoveBlock[nCnt]);
	}
	//ループ処理
	for (int nCntBlock = 0; nCntBlock < MAX_MOVEBLOCK; nCntBlock++)
	{//ブロックの数分ループする

		g_aMoveBlock[nCntBlock].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//位置を初期化する
		g_aMoveBlock[nCntBlock].fWidth = 0.0f;						//幅を初期化する
		g_aMoveBlock[nCntBlock].fHeight = 0.0f;						//高さを初期化する
		g_aMoveBlock[nCntBlock].nType = BLOCK_BEFORE;				//種類を初期化する
		g_aMoveBlock[nCntBlock].bUse = false;						//使われていない状態にする	
	}

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_MOVEBLOCK,//(sizeof(VERTEX_2D)*必要な頂点数
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMoveBlock,
		NULL);


	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffMoveBlock->Lock(0, 0, (void**)&pVtx, 0);

	//ループ処理
	for (int nCntBlock = 0; nCntBlock < MAX_MOVEBLOCK; nCntBlock++)
	{//ブロックの数分ループする

		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_aMoveBlock[nCntBlock].pos.x - 40, g_aMoveBlock[nCntBlock].pos.y - 40, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aMoveBlock[nCntBlock].pos.x + 40, g_aMoveBlock[nCntBlock].pos.y - 40, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aMoveBlock[nCntBlock].pos.x - 40, g_aMoveBlock[nCntBlock].pos.y + 40, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aMoveBlock[nCntBlock].pos.x + 40, g_aMoveBlock[nCntBlock].pos.y + 40, 0.0f);

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
		pVtx[0].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx += 4;//頂点データのポインタを4つ分集める
	}
	//頂点バッファをアンロックする
	g_pVtxBuffMoveBlock->Unlock();
}

//==================
//ブロックの終了処理
//==================
void UninitMoveBlock(void)
{
	for (int nCnt = 0; nCnt < MAX_NUMMOVEBLOCK; nCnt++)
	{
		//テクスチャの破棄
		if (g_pTextureMoveBlock[nCnt] != NULL)
		{
			g_pTextureMoveBlock[nCnt]->Release();
			g_pTextureMoveBlock[nCnt] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuffMoveBlock != NULL)
	{
		g_pVtxBuffMoveBlock->Release();
		g_pVtxBuffMoveBlock = NULL;
	}

}

//==================
//ブロックの更新処理
//==================
void UpdateMoveBlock(void)
{
	VERTEX_2D* pVtx = 0;	//頂点情報へのポインタ

	Player* pPlayer = GetPlayer();

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffMoveBlock->Lock(0, 0, (void**)&pVtx, 0);

	//ループ処理
	for (int nCnt = 0; nCnt < MAX_MOVEBLOCK; nCnt++)
	{//ブロックの最大数分ぶん回す


		if (g_aMoveBlock[nCnt].bUse == true)
		{//ブロックを使用している場合


			switch (g_aMoveBlock[nCnt].nType)
			{
			case BLOCK_BEFORE:
				break;
			case BLOCK_MOVE:
				g_aMoveBlock[nCnt].pos.x = pPlayer->pos.x;
				g_aMoveBlock[nCnt].pos.y = pPlayer->pos.y-80.0f;
				if (GetKeyboardPress(DIK_RETURN) == true || GetJoypadPress(JOYKEY_X) == true)
				{//Fキーが押されたとき
					g_aMoveBlock[nCnt].nType = BLOCK_AFTER;
				}
				break;
			case BLOCK_AFTER:
				break;
			}
			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_aMoveBlock[nCnt].pos.x - g_aMoveBlock[nCnt].fWidth, g_aMoveBlock[nCnt].pos.y - g_aMoveBlock[nCnt].fHeight, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aMoveBlock[nCnt].pos.x + g_aMoveBlock[nCnt].fWidth, g_aMoveBlock[nCnt].pos.y - g_aMoveBlock[nCnt].fHeight, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aMoveBlock[nCnt].pos.x - g_aMoveBlock[nCnt].fWidth, g_aMoveBlock[nCnt].pos.y + g_aMoveBlock[nCnt].fHeight, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aMoveBlock[nCnt].pos.x + g_aMoveBlock[nCnt].fWidth, g_aMoveBlock[nCnt].pos.y + g_aMoveBlock[nCnt].fHeight, 0.0f);

			break;
		}
		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffMoveBlock->Unlock();

}

//==================
//ブロックの描画処理
//==================
void DrawMoveBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();
	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffMoveBlock, 0, sizeof(VERTEX_2D));
	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//ループ処理
	for (int nCntBlock = 0; nCntBlock < MAX_MOVEBLOCK; nCntBlock++)
	{//ブロックの数分ループする

		if (g_aMoveBlock[nCntBlock].bUse == true)
		{//弾が使用されている


			//テクスチャの設定
			pDevice->SetTexture(BLOCK_BEFORE, g_pTextureMoveBlock[g_aMoveBlock[nCntBlock].nType]);
			pDevice->SetTexture(BLOCK_MOVE, g_pTextureMoveBlock[g_aMoveBlock[nCntBlock].nType]);
			pDevice->SetTexture(BLOCK_AFTER, g_pTextureMoveBlock[g_aMoveBlock[nCntBlock].nType]);
			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntBlock, 2);
		}
	}
}

//===================
//ブロックの設定処理
//===================
void SetMoveBlock(D3DXVECTOR3 pos,	//位置の設定
	float fWidth,					//幅の設定
	float fHeight,					//高さの設定
	int nType)						//種類	

{
	VERTEX_2D* pVtx = 0;	//頂点情報へのポインタ
	float fU = 0;			//テクスチャの枚数
	Player* pPlayer = GetPlayer();

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffMoveBlock->Lock(0, 0, (void**)&pVtx, 0);

	//ループ処理
	for (int nCntBlock = 0; nCntBlock < MAX_MOVEBLOCK; nCntBlock++)
	{//ブロックの最大数分ループする
		if (g_aMoveBlock[nCntBlock].bUse == false)
		{//ブロックが使用されていない


			g_aMoveBlock[nCntBlock].pos = pos;			//ブロックの頂点座標を代入
			g_aMoveBlock[nCntBlock].fWidth = fWidth;	//ブロックの幅を代入
			g_aMoveBlock[nCntBlock].fHeight = fHeight;	//ブロックの高さを代入
			g_aMoveBlock[nCntBlock].nType = nType;		//ブロックの種類を代入
			g_aMoveBlock[nCntBlock].bUse = true;		//使用している状態にする

			switch (g_aMoveBlock[nCntBlock].nType)
			{
			case BLOCK_BEFORE://ノーマル

				//頂点座標の設定
				pVtx[0].pos = D3DXVECTOR3(g_aMoveBlock[nCntBlock].pos.x - fWidth, g_aMoveBlock[nCntBlock].pos.y - fHeight, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_aMoveBlock[nCntBlock].pos.x + fWidth, g_aMoveBlock[nCntBlock].pos.y - fHeight, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aMoveBlock[nCntBlock].pos.x - fWidth, g_aMoveBlock[nCntBlock].pos.y + fHeight, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aMoveBlock[nCntBlock].pos.x + fWidth, g_aMoveBlock[nCntBlock].pos.y + fHeight, 0.0f);

				break;

			case BLOCK_MOVE://ボタン

				//頂点座標の設定
				pVtx[0].pos = D3DXVECTOR3(g_aMoveBlock[nCntBlock].pos.x - fWidth, g_aMoveBlock[nCntBlock].pos.y - fHeight, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_aMoveBlock[nCntBlock].pos.x + fWidth, g_aMoveBlock[nCntBlock].pos.y - fHeight, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aMoveBlock[nCntBlock].pos.x - fWidth, g_aMoveBlock[nCntBlock].pos.y + fHeight, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aMoveBlock[nCntBlock].pos.x + fWidth, g_aMoveBlock[nCntBlock].pos.y + fHeight, 0.0f);

				break;

			case BLOCK_AFTER://ボタン

				//頂点座標の設定
				pVtx[0].pos = D3DXVECTOR3(g_aMoveBlock[nCntBlock].pos.x - fWidth, g_aMoveBlock[nCntBlock].pos.y - fHeight, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_aMoveBlock[nCntBlock].pos.x + fWidth, g_aMoveBlock[nCntBlock].pos.y - fHeight, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aMoveBlock[nCntBlock].pos.x - fWidth, g_aMoveBlock[nCntBlock].pos.y + fHeight, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aMoveBlock[nCntBlock].pos.x + fWidth, g_aMoveBlock[nCntBlock].pos.y + fHeight, 0.0f);

				break;
			}

			break;
		}
		pVtx += 4;//頂点データのポインタを4つ分集める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffMoveBlock->Unlock();
}


//===========================
//ブロックの当たり判定処理
//===========================
bool CollisionMoveBlock(D3DXVECTOR3* pPos,		//現在のポゴ位置
	D3DXVECTOR3* pPosOld,	//前回のポゴ位置
	D3DXVECTOR3* pPYPos,	//現在のプレイヤー位置
	D3DXVECTOR3* pPYPosOld,	//前回のプレイヤー位置
	D3DXVECTOR3* pMove,		//移動量
	float fWidth,			//幅
	float fHeight)			//高さ
{
	//ローカル変数
	bool bLanding = false;					//着地しているかどうか
	float Width = fWidth;					//プレイヤーの幅
	float Height = fHeight;					//プレイヤーの高さ
	float fX[4];
	float fY[4];
	D3DXVECTOR3* PosOld = pPosOld;			//前フレームのポゴの位置
	D3DXVECTOR3* Pos = pPos;				//現フレームのポゴの位置
	D3DXVECTOR3* PYPosOld = pPYPosOld;		//前フレームのプレイヤーの位置
	D3DXVECTOR3* PYPos = pPYPos;			//現フレームのプレイヤーの位置
	Player* pPlayer = GetPlayer();


	//ループ処理
	for (int nCntBlock = 0; nCntBlock < MAX_MOVEBLOCK; nCntBlock++)
	{//ブロックの最大数分ループする


		if (g_aMoveBlock[nCntBlock].bUse == true)
		{//ブロックを使用している場合

			switch (g_aMoveBlock[nCntBlock].nType)
			{
			case BLOCK_BEFORE://取る前

				fX[0] = (g_aMoveBlock[nCntBlock].pos.x - g_aMoveBlock[nCntBlock].fWidth - pPos->x) * (g_aMoveBlock[nCntBlock].pos.x - g_aMoveBlock[nCntBlock].fWidth - pPos->x);
				fY[0] = (g_aMoveBlock[nCntBlock].pos.y - g_aMoveBlock[nCntBlock].fHeight - pPos->y) * (g_aMoveBlock[nCntBlock].pos.y - g_aMoveBlock[nCntBlock].fHeight - pPos->y);
				fX[1] = (g_aMoveBlock[nCntBlock].pos.x + g_aMoveBlock[nCntBlock].fWidth - pPos->x) * (g_aMoveBlock[nCntBlock].pos.x + g_aMoveBlock[nCntBlock].fWidth - pPos->x);
				fY[1] = (g_aMoveBlock[nCntBlock].pos.y + g_aMoveBlock[nCntBlock].fHeight - pPos->y) * (g_aMoveBlock[nCntBlock].pos.y + g_aMoveBlock[nCntBlock].fHeight - pPos->y);
				fX[2] = (g_aMoveBlock[nCntBlock].pos.x - g_aMoveBlock[nCntBlock].fWidth - pPYPos->x) * (g_aMoveBlock[nCntBlock].pos.x - g_aMoveBlock[nCntBlock].fWidth - pPYPos->x);
				fY[2] = (g_aMoveBlock[nCntBlock].pos.y - g_aMoveBlock[nCntBlock].fHeight - pPYPos->y) * (g_aMoveBlock[nCntBlock].pos.y - g_aMoveBlock[nCntBlock].fHeight - pPYPos->y);
				fX[3] = (g_aMoveBlock[nCntBlock].pos.x + g_aMoveBlock[nCntBlock].fWidth - pPYPos->x) * (g_aMoveBlock[nCntBlock].pos.x + g_aMoveBlock[nCntBlock].fWidth - pPYPos->x);
				fY[3] = (g_aMoveBlock[nCntBlock].pos.y + g_aMoveBlock[nCntBlock].fHeight - pPYPos->y) * (g_aMoveBlock[nCntBlock].pos.y + g_aMoveBlock[nCntBlock].fHeight - pPYPos->y);

				break;

			case BLOCK_MOVE://動かしてるとき

				fX[0] = (g_aMoveBlock[nCntBlock].pos.x - g_aMoveBlock[nCntBlock].fWidth - pPos->x) * (g_aMoveBlock[nCntBlock].pos.x - g_aMoveBlock[nCntBlock].fWidth - pPos->x);
				fY[0] = (g_aMoveBlock[nCntBlock].pos.y - g_aMoveBlock[nCntBlock].fHeight - pPos->y) * (g_aMoveBlock[nCntBlock].pos.y - g_aMoveBlock[nCntBlock].fHeight - pPos->y);
				fX[1] = (g_aMoveBlock[nCntBlock].pos.x + g_aMoveBlock[nCntBlock].fWidth - pPos->x) * (g_aMoveBlock[nCntBlock].pos.x + g_aMoveBlock[nCntBlock].fWidth - pPos->x);
				fY[1] = (g_aMoveBlock[nCntBlock].pos.y + g_aMoveBlock[nCntBlock].fHeight - pPos->y) * (g_aMoveBlock[nCntBlock].pos.y + g_aMoveBlock[nCntBlock].fHeight - pPos->y);
				fX[2] = (g_aMoveBlock[nCntBlock].pos.x - g_aMoveBlock[nCntBlock].fWidth - pPYPos->x) * (g_aMoveBlock[nCntBlock].pos.x - g_aMoveBlock[nCntBlock].fWidth - pPYPos->x);
				fY[2] = (g_aMoveBlock[nCntBlock].pos.y - g_aMoveBlock[nCntBlock].fHeight - pPYPos->y) * (g_aMoveBlock[nCntBlock].pos.y - g_aMoveBlock[nCntBlock].fHeight - pPYPos->y);
				fX[3] = (g_aMoveBlock[nCntBlock].pos.x + g_aMoveBlock[nCntBlock].fWidth - pPYPos->x) * (g_aMoveBlock[nCntBlock].pos.x + g_aMoveBlock[nCntBlock].fWidth - pPYPos->x);
				fY[3] = (g_aMoveBlock[nCntBlock].pos.y + g_aMoveBlock[nCntBlock].fHeight - pPYPos->y) * (g_aMoveBlock[nCntBlock].pos.y + g_aMoveBlock[nCntBlock].fHeight - pPYPos->y);

				break;

			case BLOCK_AFTER://使ったあと

				fX[0] = (g_aMoveBlock[nCntBlock].pos.x - g_aMoveBlock[nCntBlock].fWidth - pPos->x) * (g_aMoveBlock[nCntBlock].pos.x - g_aMoveBlock[nCntBlock].fWidth - pPos->x);
				fY[0] = (g_aMoveBlock[nCntBlock].pos.y - g_aMoveBlock[nCntBlock].fHeight - pPos->y) * (g_aMoveBlock[nCntBlock].pos.y - g_aMoveBlock[nCntBlock].fHeight - pPos->y);
				fX[1] = (g_aMoveBlock[nCntBlock].pos.x + g_aMoveBlock[nCntBlock].fWidth - pPos->x) * (g_aMoveBlock[nCntBlock].pos.x + g_aMoveBlock[nCntBlock].fWidth - pPos->x);
				fY[1] = (g_aMoveBlock[nCntBlock].pos.y + g_aMoveBlock[nCntBlock].fHeight - pPos->y) * (g_aMoveBlock[nCntBlock].pos.y + g_aMoveBlock[nCntBlock].fHeight - pPos->y);
				fX[2] = (g_aMoveBlock[nCntBlock].pos.x - g_aMoveBlock[nCntBlock].fWidth - pPYPos->x) * (g_aMoveBlock[nCntBlock].pos.x - g_aMoveBlock[nCntBlock].fWidth - pPYPos->x);
				fY[2] = (g_aMoveBlock[nCntBlock].pos.y - g_aMoveBlock[nCntBlock].fHeight - pPYPos->y) * (g_aMoveBlock[nCntBlock].pos.y - g_aMoveBlock[nCntBlock].fHeight - pPYPos->y);
				fX[3] = (g_aMoveBlock[nCntBlock].pos.x + g_aMoveBlock[nCntBlock].fWidth - pPYPos->x) * (g_aMoveBlock[nCntBlock].pos.x + g_aMoveBlock[nCntBlock].fWidth - pPYPos->x);
				fY[3] = (g_aMoveBlock[nCntBlock].pos.y + g_aMoveBlock[nCntBlock].fHeight - pPYPos->y) * (g_aMoveBlock[nCntBlock].pos.y + g_aMoveBlock[nCntBlock].fHeight - pPYPos->y);

				break;
			}

			switch (g_aMoveBlock[nCntBlock].nType)
			{
			case BLOCK_BEFORE:

				if ((pPos->x > g_aMoveBlock[nCntBlock].pos.x - g_aMoveBlock[nCntBlock].fWidth) && (pPos->x < g_aMoveBlock[nCntBlock].pos.x + g_aMoveBlock[nCntBlock].fWidth) && (pPos->y > g_aMoveBlock[nCntBlock].pos.y - g_aMoveBlock[nCntBlock].fHeight - MAX_POSCIRCLE) && (pPos->y < g_aMoveBlock[nCntBlock].pos.y + g_aMoveBlock[nCntBlock].fHeight + MAX_POSCIRCLE))
				{//上下のポゴ当たり判定

			
					//着地の判定をtrueにする
					bLanding = true;

					SetParticle(pPlayer->pos, 50.0f, 30.0f, 629, 40, PARTICLETYPE_1);

					//y方向のmove初期化
					pMove->y = 0.0f;

					pPlayer->move.x = -sinf(pPlayer->rot.z) * JUMP;	//ジャンプ力加算
					pPlayer->move.y = -cosf(pPlayer->rot.z) * JUMP;	//ジャンプ力加算
					pPlayer->bJump = true;

				}


				if ((pPos->x > g_aMoveBlock[nCntBlock].pos.x - g_aMoveBlock[nCntBlock].fWidth - MAX_POSCIRCLE) && (pPos->x < g_aMoveBlock[nCntBlock].pos.x + g_aMoveBlock[nCntBlock].fWidth + MAX_POSCIRCLE) && (pPos->y > g_aMoveBlock[nCntBlock].pos.y - g_aMoveBlock[nCntBlock].fHeight) && (pPos->y < g_aMoveBlock[nCntBlock].pos.y + g_aMoveBlock[nCntBlock].fHeight))
				{//左右のポゴ当たり判定


					//着地の判定をtrueにする
					bLanding = true;

					SetParticle(pPlayer->pos, 50.0f, 30.0f, 629, 40, PARTICLETYPE_1);

					//ジャンプしている

					//x方向のmove初期化
					pMove->x = 0.0f;
					pPlayer->move.x = -sinf(pPlayer->rot.z) * JUMP;	//ジャンプ力加算
					pPlayer->move.y = -cosf(pPlayer->rot.z) * JUMP;	//ジャンプ力加算
					pPlayer->bJump = true;

				}


				if (fX[0] + fY[0] < MAX_POSCIRCLE * MAX_POSCIRCLE)
				{//右上のポゴ当たり判定


					//着地の判定をtrueにする
					bLanding = true;

					SetParticle(pPlayer->pos, 50.0f, 30.0f, 629, 40, PARTICLETYPE_1);

					//ジャンプしている

					//x方向のmove初期化
					pMove->x = 0.0f;

					pPlayer->move.x = -sinf(pPlayer->rot.z) * JUMP;	//ジャンプ力加算
					pPlayer->move.y = -cosf(pPlayer->rot.z) * JUMP;	//ジャンプ力加算
					pPlayer->bJump = true;
				}


				if (fX[1] + fY[0] < MAX_POSCIRCLE * MAX_POSCIRCLE)
				{//左上のポゴ当たり判定


					//着地の判定をtrueにする
					bLanding = true;

					SetParticle(pPlayer->pos, 50.0f, 30.0f, 629, 40, PARTICLETYPE_1);

					//ジャンプしている

					//x方向のmove初期化
					pMove->x = 0.0f;
					pPlayer->move.x = -sinf(pPlayer->rot.z) * JUMP;	//ジャンプ力加算
					pPlayer->move.y = -cosf(pPlayer->rot.z) * JUMP;	//ジャンプ力加算
					pPlayer->bJump = true;
				}


				if (fX[0] + fY[1] < MAX_POSCIRCLE * MAX_POSCIRCLE)
				{//右下のポゴ当たり判定


					//着地の判定をtrueにする
					bLanding = true;

					SetParticle(pPlayer->pos, 50.0f, 30.0f, 629, 40, PARTICLETYPE_1);

					//ジャンプしている

					//x方向のmove初期化
					pMove->x = 0.0f;
					pPlayer->move.x = -sinf(pPlayer->rot.z) * JUMP;	//ジャンプ力加算
					pPlayer->move.y = -cosf(pPlayer->rot.z) * JUMP;	//ジャンプ力加算
					pPlayer->bJump = true;
				}


				if (fX[1] + fY[1] < MAX_POSCIRCLE * MAX_POSCIRCLE)
				{//左下のポゴ当たり判定


					//着地の判定をtrueにする
					bLanding = true;

					SetParticle(pPlayer->pos, 50.0f, 30.0f, 629, 40, PARTICLETYPE_1);

					//ジャンプしている

					//x方向のmove初期化
					pMove->x = 0.0f;
					pPlayer->move.x = -sinf(pPlayer->rot.z) * JUMP;	//ジャンプ力加算
					pPlayer->move.y = -cosf(pPlayer->rot.z) * JUMP;	//ジャンプ力加算
					pPlayer->bJump = true;
				}

				if ((pPYPos->x > g_aMoveBlock[nCntBlock].pos.x - g_aMoveBlock[nCntBlock].fWidth) && (pPYPos->x < g_aMoveBlock[nCntBlock].pos.x + g_aMoveBlock[nCntBlock].fWidth) && (pPYPos->y > g_aMoveBlock[nCntBlock].pos.y - g_aMoveBlock[nCntBlock].fHeight - MAX_POSCIRCLE) && (pPYPos->y < g_aMoveBlock[nCntBlock].pos.y + g_aMoveBlock[nCntBlock].fHeight + MAX_POSCIRCLE))
				{//上下のプレイヤー当たり判定

					if (pPosOld->y >= g_aMoveBlock[nCntBlock].pos.y + g_aMoveBlock[nCntBlock].fHeight + MAX_POSCIRCLE)
					{
						g_aMoveBlock[nCntBlock].nType = BLOCK_MOVE;
					}
					else
					{
						//プレイヤーのライフを1減らす
						pPlayer->nLife--;
					}

					//y方向のmove初期化
					pMove->y = 0.0f;

				}


				if ((pPYPos->x > g_aMoveBlock[nCntBlock].pos.x - g_aMoveBlock[nCntBlock].fWidth - MAX_POSCIRCLE) && (pPYPos->x < g_aMoveBlock[nCntBlock].pos.x + g_aMoveBlock[nCntBlock].fWidth + MAX_POSCIRCLE) && (pPYPos->y > g_aMoveBlock[nCntBlock].pos.y - g_aMoveBlock[nCntBlock].fHeight) && (pPYPos->y < g_aMoveBlock[nCntBlock].pos.y + g_aMoveBlock[nCntBlock].fHeight))
				{//左右のプレイヤー当たり判定


					if (pPosOld->y >= g_aMoveBlock[nCntBlock].pos.y + g_aMoveBlock[nCntBlock].fHeight + MAX_POSCIRCLE)
					{
						g_aMoveBlock[nCntBlock].nType = BLOCK_MOVE;
					}

					//x方向のmove初期化
					pMove->x = 0.0f;
					//x方向のmove初期化
					pMove->y = 0.0f;

				}


				if (fX[2] + fY[2] < MAX_POSCIRCLE * MAX_POSCIRCLE)
				{//右上のプレイヤー当たり判定


					//プレイヤーのライフを1減らす
					pPlayer->nLife--;


					//x方向のmove初期化
					pMove->x = 0.0f;
					//x方向のmove初期化
					pMove->y = 0.0f;
				}


				if (fX[3] + fY[2] < MAX_POSCIRCLE * MAX_POSCIRCLE)
				{//左上のプレイヤー当たり判定


					//プレイヤーのライフを1減らす
					pPlayer->nLife--;

					//x方向のmove初期化
					pMove->x = 0.0f;
					//x方向のmove初期化
					pMove->y = 0.0f;
				}


				if (fX[2] + fY[3] < MAX_POSCIRCLE * MAX_POSCIRCLE)
				{//右下のプレイヤー当たり判定


					if (pPosOld->y >= g_aMoveBlock[nCntBlock].pos.y + g_aMoveBlock[nCntBlock].fHeight + MAX_POSCIRCLE)
					{
						g_aMoveBlock[nCntBlock].nType = BLOCK_MOVE;
					}

					//x方向のmove初期化
					pMove->x = 0.0f;
					//x方向のmove初期化
					pMove->y = 0.0f;
				}


				if (fX[3] + fY[3] < MAX_POSCIRCLE * MAX_POSCIRCLE)
				{//左下のプレイヤー当たり判定


					if (pPosOld->y >= g_aMoveBlock[nCntBlock].pos.y + g_aMoveBlock[nCntBlock].fHeight + MAX_POSCIRCLE)
					{
						g_aMoveBlock[nCntBlock].nType = BLOCK_MOVE;
					}


					//x方向のmove初期化
					pMove->x = 0.0f;
					//x方向のmove初期化
					pMove->y = 0.0f;
				}

				break;
			case BLOCK_AFTER:
				if ((pPos->x > g_aMoveBlock[nCntBlock].pos.x - g_aMoveBlock[nCntBlock].fWidth) && (pPos->x < g_aMoveBlock[nCntBlock].pos.x + g_aMoveBlock[nCntBlock].fWidth) && (pPos->y > g_aMoveBlock[nCntBlock].pos.y - g_aMoveBlock[nCntBlock].fHeight - MAX_POSCIRCLE)&& (pPosOld->y + MAX_POSCIRCLE < g_aMoveBlock[nCntBlock].pos.y - g_aMoveBlock[nCntBlock].fHeight) && (pPos->y < g_aMoveBlock[nCntBlock].pos.y + g_aMoveBlock[nCntBlock].fHeight + MAX_POSCIRCLE))
				{//上下のポゴ当たり判定


					//着地の判定をtrueにする
					bLanding = true;

					//y方向のmove初期化
					pMove->y = 0.0f;

					pPlayer->move.x = -sinf(pPlayer->rot.z) * JUMP;	//ジャンプ力加算
					pPlayer->move.y = -cosf(pPlayer->rot.z) * JUMP;	//ジャンプ力加算
					pPlayer->bJump = true;

				}


				if ((pPos->x > g_aMoveBlock[nCntBlock].pos.x - g_aMoveBlock[nCntBlock].fWidth - MAX_POSCIRCLE) && (pPos->x < g_aMoveBlock[nCntBlock].pos.x + g_aMoveBlock[nCntBlock].fWidth + MAX_POSCIRCLE) && (pPos->y > g_aMoveBlock[nCntBlock].pos.y - g_aMoveBlock[nCntBlock].fHeight) && (pPos->y < g_aMoveBlock[nCntBlock].pos.y + g_aMoveBlock[nCntBlock].fHeight) && (pPosOld->y + MAX_POSCIRCLE < g_aMoveBlock[nCntBlock].pos.y - g_aMoveBlock[nCntBlock].fHeight))
				{//左右のポゴ当たり判定


					//着地の判定をtrueにする
					bLanding = true;

					//ジャンプしている

					//x方向のmove初期化
					pMove->x = 0.0f;
					pPlayer->move.x = -sinf(pPlayer->rot.z) * JUMP;	//ジャンプ力加算
					pPlayer->move.y = -cosf(pPlayer->rot.z) * JUMP;	//ジャンプ力加算
					pPlayer->bJump = true;

				}


				if (fX[0] + fY[0] < MAX_POSCIRCLE * MAX_POSCIRCLE && (pPosOld->y + MAX_POSCIRCLE < g_aMoveBlock[nCntBlock].pos.y - g_aMoveBlock[nCntBlock].fHeight))
				{//右上のポゴ当たり判定


					//着地の判定をtrueにする
					bLanding = true;

					//ジャンプしている

					//x方向のmove初期化
					pMove->x = 0.0f;

					pPlayer->move.x = -sinf(pPlayer->rot.z) * JUMP;	//ジャンプ力加算
					pPlayer->move.y = -cosf(pPlayer->rot.z) * JUMP;	//ジャンプ力加算
					pPlayer->bJump = true;
				}


				if (fX[1] + fY[0] < MAX_POSCIRCLE * MAX_POSCIRCLE && (pPosOld->y + MAX_POSCIRCLE < g_aMoveBlock[nCntBlock].pos.y - g_aMoveBlock[nCntBlock].fHeight))
				{//左上のポゴ当たり判定


					//着地の判定をtrueにする
					bLanding = true;

					//ジャンプしている

					//x方向のmove初期化
					pMove->x = 0.0f;
					pPlayer->move.x = -sinf(pPlayer->rot.z) * JUMP;	//ジャンプ力加算
					pPlayer->move.y = -cosf(pPlayer->rot.z) * JUMP;	//ジャンプ力加算
					pPlayer->bJump = true;
				}


				if (fX[0] + fY[1] < MAX_POSCIRCLE * MAX_POSCIRCLE && (pPosOld->y + MAX_POSCIRCLE < g_aMoveBlock[nCntBlock].pos.y - g_aMoveBlock[nCntBlock].fHeight))
				{//右下のポゴ当たり判定


					//着地の判定をtrueにする
					bLanding = true;

					//ジャンプしている

					//x方向のmove初期化
					pMove->x = 0.0f;
					pPlayer->move.x = -sinf(pPlayer->rot.z) * JUMP;	//ジャンプ力加算
					pPlayer->move.y = -cosf(pPlayer->rot.z) * JUMP;	//ジャンプ力加算
					pPlayer->bJump = true;
				}


				if (fX[1] + fY[1] < MAX_POSCIRCLE * MAX_POSCIRCLE && (pPosOld->y + MAX_POSCIRCLE < g_aMoveBlock[nCntBlock].pos.y - g_aMoveBlock[nCntBlock].fHeight))
				{//左下のポゴ当たり判定


					//着地の判定をtrueにする
					bLanding = true;

					//ジャンプしている

					//x方向のmove初期化
					pMove->x = 0.0f;
					pPlayer->move.x = -sinf(pPlayer->rot.z) * JUMP;	//ジャンプ力加算
					pPlayer->move.y = -cosf(pPlayer->rot.z) * JUMP;	//ジャンプ力加算
					pPlayer->bJump = true;
				}

				if ((pPYPos->x > g_aMoveBlock[nCntBlock].pos.x - g_aMoveBlock[nCntBlock].fWidth) && (pPYPos->x < g_aMoveBlock[nCntBlock].pos.x + g_aMoveBlock[nCntBlock].fWidth) && (pPYPos->y > g_aMoveBlock[nCntBlock].pos.y - g_aMoveBlock[nCntBlock].fHeight - MAX_POSCIRCLE) && (pPosOld->y + MAX_POSCIRCLE < g_aMoveBlock[nCntBlock].pos.y - g_aMoveBlock[nCntBlock].fHeight ))
				{//上下のプレイヤー当たり判定


					//プレイヤーのライフを1減らす
					pPlayer->nLife--;

					//y方向のmove初期化
					pMove->y = 0.0f;

				}


				if ((pPYPos->x > g_aMoveBlock[nCntBlock].pos.x - g_aMoveBlock[nCntBlock].fWidth - MAX_POSCIRCLE) && (pPYPos->x < g_aMoveBlock[nCntBlock].pos.x + g_aMoveBlock[nCntBlock].fWidth + MAX_POSCIRCLE) && (pPYPos->y > g_aMoveBlock[nCntBlock].pos.y - g_aMoveBlock[nCntBlock].fHeight) && (pPYPos->y < g_aMoveBlock[nCntBlock].pos.y + g_aMoveBlock[nCntBlock].fHeight) && (pPosOld->y + MAX_POSCIRCLE < g_aMoveBlock[nCntBlock].pos.y - g_aMoveBlock[nCntBlock].fHeight))
				{//左右のプレイヤー当たり判定


					//プレイヤーのライフを1減らす
					pPlayer->nLife--;

					//x方向のmove初期化
					pMove->x = 0.0f;
					//x方向のmove初期化
					pMove->y = 0.0f;

				}


				if (fX[2] + fY[2] < MAX_POSCIRCLE * MAX_POSCIRCLE && (pPosOld->y + MAX_POSCIRCLE < g_aMoveBlock[nCntBlock].pos.y - g_aMoveBlock[nCntBlock].fHeight))
				{//右上のプレイヤー当たり判定


					//プレイヤーのライフを1減らす
					pPlayer->nLife--;

					//x方向のmove初期化
					pMove->x = 0.0f;
					//x方向のmove初期化
					pMove->y = 0.0f;
				}


				if (fX[3] + fY[2] < MAX_POSCIRCLE * MAX_POSCIRCLE && (pPosOld->y + MAX_POSCIRCLE < g_aMoveBlock[nCntBlock].pos.y - g_aMoveBlock[nCntBlock].fHeight))
				{//左上のプレイヤー当たり判定


					//プレイヤーのライフを1減らす
					pPlayer->nLife--;

					//x方向のmove初期化
					pMove->x = 0.0f;
					//x方向のmove初期化
					pMove->y = 0.0f;
				}


				if (fX[2] + fY[3] < MAX_POSCIRCLE * MAX_POSCIRCLE && (pPosOld->y + MAX_POSCIRCLE < g_aMoveBlock[nCntBlock].pos.y - g_aMoveBlock[nCntBlock].fHeight))
				{//右下のプレイヤー当たり判定


					//プレイヤーのライフを1減らす
					pPlayer->nLife--;

					//x方向のmove初期化
					pMove->x = 0.0f;
					//x方向のmove初期化
					pMove->y = 0.0f;
				}


				if (fX[3] + fY[3] < MAX_POSCIRCLE * MAX_POSCIRCLE && (pPosOld->y + MAX_POSCIRCLE < g_aMoveBlock[nCntBlock].pos.y - g_aMoveBlock[nCntBlock].fHeight))
				{//左下のプレイヤー当たり判定


					//プレイヤーのライフを1減らす
					pPlayer->nLife--;

					//x方向のmove初期化
					pMove->x = 0.0f;
					//x方向のmove初期化
					pMove->y = 0.0f;
				}
				break;
			}

		}
	}

	//bLandingの値を返す
	return bLanding;
}