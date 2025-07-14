//=============================================================================
//
//	ギミック処理 [gimmick.cpp]
// author chikada shouya
//
//=============================================================================

#include "gimmick.h"
#include "camera.h"
#include "Input.h"
#include "enemy.h"
#include "game.h"
#include "item.h"

// グローバル変数宣言
LPDIRECT3DTEXTURE9 g_apTextureDoor[MAX_DOOR] = {};	// テクスチャへのポインタ
GIMMICK g_Door[MAX_DOOR];
HOLD g_hold;
bool isGoal;
bool isBill;

//================================
// 初期化処理
//================================
void InitGimmick(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	g_hold.nHoldCount = 0;
	g_hold.NoTouch = 0;
	g_hold.HolTime = 0;
	g_hold.count = 0;
	g_hold.bPush = false;
	g_hold.bClear = false;
	g_hold.bNoPush = false;

	// 構造体変数の初期化
	for (int nCnt = 0; nCnt < MAX_DOOR; nCnt++)
	{
		// 各種変数の初期化
		g_Door[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Door[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Door[nCnt].size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Door[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Door[nCnt].vtxMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Door[nCnt].vtxMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Door[nCnt].dwNumMat = 0;
		g_Door[nCnt].bUse = false;
		//g_Door[nCnt1][nCnt].bGoal = false;
		//g_Door[nCnt1][nCnt].bMove = false;

		// モデル読み込み
		// Xファイルの読み込み
		D3DXLoadMeshFromX("data\\MODEL\\door.x",
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_Door[nCnt].pBuffMat,
			NULL,
			&g_Door[nCnt].dwNumMat,
			&g_Door[nCnt].pMesh);

		isGoal = false;
		isBill = false;
		// サイズ等の取得
		int nNumVtx;			// 頂点数
		DWORD sizeFVF;			// 頂点フォーマットのサイズ
		BYTE* pVtxBuff;			// 頂点バッファへのポインタ
		D3DXMATERIAL* pMat;		// マテリアルへのポインタ

		// 頂点数の取得
		nNumVtx = g_Door[nCnt].pMesh->GetNumVertices();

		// 頂点フォーマットの取得
		sizeFVF = D3DXGetFVFVertexSize(g_Door[nCnt].pMesh->GetFVF());

		// 頂点バッファのロック
		g_Door[nCnt].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			// 頂点座標の代入
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

			if (vtx.x > g_Door[nCnt].vtxMax.x)
			{// もしXの値が大きかったら
				g_Door[nCnt].vtxMax.x = vtx.x;
			}
			else if (vtx.x < g_Door[nCnt].vtxMin.x)
			{// もしXの値が小さかったら
				g_Door[nCnt].vtxMin.x = vtx.x;
			}

			if (vtx.y > g_Door[nCnt].vtxMax.y)
			{// もしYの値が大きかったら
				g_Door[nCnt].vtxMax.y = vtx.y;
			}
			else if (vtx.y < g_Door[nCnt].vtxMin.y)
			{// もしYの値が小さかったら
				g_Door[nCnt].vtxMin.y = vtx.y;
			}

			if (vtx.z > g_Door[nCnt].vtxMax.z)
			{// もしZの値が大きかったら
				g_Door[nCnt].vtxMax.z = vtx.z;
			}
			else if (vtx.z < g_Door[nCnt].vtxMin.z)
			{// もしZの値が小さかったら
				g_Door[nCnt].vtxMin.z = vtx.z;
			}

			// 頂点フォーマットのサイズ分ポインタを進める
			pVtxBuff += sizeFVF;
		}

		// サイズを代入
		g_Door[nCnt].size.x = g_Door[nCnt].vtxMax.x - g_Door[nCnt].vtxMin.x;
		g_Door[nCnt].size.y = g_Door[nCnt].vtxMax.y - g_Door[nCnt].vtxMin.y;
		g_Door[nCnt].size.z = g_Door[nCnt].vtxMax.z - g_Door[nCnt].vtxMin.z;

		// 頂点バッファのアンロック
		g_Door[nCnt].pMesh->UnlockVertexBuffer();

		// マテリアルデータへのポインタを取得
		pMat = (D3DXMATERIAL*)g_Door[nCnt].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_Door[nCnt].dwNumMat; nCntMat++)
		{
			if (pMat[nCntMat].pTextureFilename != NULL)
			{// テクスチャファイルが存在する
				// テクスチャの読み込み
				D3DXCreateTextureFromFile(pDevice,
					pMat[nCntMat].pTextureFilename,
					&g_apTextureDoor[nCntMat]);
			}
		}
	}
}
//================================
// 終了処理
//================================
void UninitGimmick(void)
{
	for (int nCnt = 0; nCnt < MAX_DOOR; nCnt++)
	{
		// メッシュの破棄
		if (g_Door[nCnt].pMesh != NULL)
		{
			g_Door[nCnt].pMesh->Release();
			g_Door[nCnt].pMesh = NULL;
		}
		// マテリアルの破棄
		if (g_Door[nCnt].pBuffMat != NULL)
		{
			g_Door[nCnt].pBuffMat->Release();
			g_Door[nCnt].pBuffMat = NULL;
		}
		// テクスチャの破棄
		if (g_apTextureDoor[nCnt] != NULL)
		{
			g_apTextureDoor[nCnt]->Release();
			g_apTextureDoor[nCnt] = NULL;
		}
	}
}
//================================
// 更新処理
//================================
void UpdateGimmick(void)
{
	Player* pPlayer = GetPlayer();
	Enemy* pEnemy = GetEnemy();
	ITEM* pItem = Getitem();

	for (int nCnt = 0; nCnt < MAX_DOOR; nCnt++)
	{
		if (g_Door[nCnt].bUse == true)
		{
			// 半径の算出変数
			float PRadiusPos = 50.0f;
			float BRadiusPos = 50.0f;

			// プレイヤーの位置の取得
			D3DXVECTOR3 PlayerPos = GetPlayer()->pos;

			// 敵とプレイヤーの距離の差
			D3DXVECTOR3 diff = PlayerPos - g_Door[nCnt].pos;

			// 範囲計算
			float fDisX = PlayerPos.x - g_Door[nCnt].pos.x;
			float fDisY = PlayerPos.y - g_Door[nCnt].pos.y;
			float fDisZ = PlayerPos.z - g_Door[nCnt].pos.z;

			// 二つの半径を求める
			float fRadX = PRadiusPos + BRadiusPos;

			// プレイヤーが範囲に入ったら
			if ((fDisX * fDisX) + (fDisY * fDisY) + (fDisZ * fDisZ) <= (fRadX * fRadX))
			{
				// ビルボードを表示する
				isBill = true;

				if (pItem[0].bHold == true && pItem[1].bHold == true)
				{

					if (GetKeyboardPress(DIK_F) || GetJoypadPress(JOYKEY_B) == true)
					{

						g_hold.bPush = true;
						g_hold.bNoPush = false;
						g_hold.NoTouch = 0;
					}
					else if (KeybordRelease(DIK_F) || GetJoypadPress(JOYKEY_B) == false)
					{
						g_hold.bNoPush = true;
						g_hold.bPush = false;
					}
				}
			}
			// プレイヤーが範囲の外に出たら
			else if ((fDisX * fDisX) + (fDisY * fDisY) + (fDisZ * fDisZ) >= (fRadX * fRadX))
			{
				// ビルボードを非表示にする
				isBill = false;
				g_hold.bNoPush = true;
				g_hold.bPush = false;
			}
		}
	}

	IsHold();
}
//================================
// 描画処理
//================================
void DrawGimmick(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;	// 計算用マトリックス
	D3DMATERIAL9 matDef;			// 現在のマテリアル保存用
	D3DXMATERIAL* pMat;				// マテリアルデータへのポインタ

	for (int nCnt = 0; nCnt < MAX_DOOR; nCnt++)
	{
		if (g_Door[nCnt].bUse == true)
		{// 未使用だったら下の処理を通さない
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_Door[nCnt].mtxWorld);

			// 向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Door[nCnt].rot.y, g_Door[nCnt].rot.x, g_Door[nCnt].rot.z);
			D3DXMatrixMultiply(&g_Door[nCnt].mtxWorld, &g_Door[nCnt].mtxWorld, &mtxRot);

			// 位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_Door[nCnt].pos.x, g_Door[nCnt].pos.y, g_Door[nCnt].pos.z);
			D3DXMatrixMultiply(&g_Door[nCnt].mtxWorld, &g_Door[nCnt].mtxWorld, &mtxTrans);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_Door[nCnt].mtxWorld);

			// 現在のマテリアルを取得
			pDevice->GetMaterial(&matDef);

			// マテリアルデータへのポインタを取得
			pMat = (D3DXMATERIAL*)g_Door[nCnt].pBuffMat->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_Door[nCnt].dwNumMat; nCntMat++)
			{
				// マテリアルの設定
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				// テクスチャの設定
				pDevice->SetTexture(0, g_apTextureDoor[nCntMat]);

				// モデル(パーツ)の描画
				g_Door[nCnt].pMesh->DrawSubset(nCntMat);
			}

			// 保存していたマテリアルを隠す
			//pDevice->SetMaterial(NULL);
			pDevice->SetMaterial(&matDef);

			// テクスチャの設定
			pDevice->SetTexture(0, NULL);
		}
	}
}
//================================================
// ブロックの設定処理
//================================================
void SetGimmick(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	for (int nCnt = 0; nCnt < MAX_DOOR; nCnt++)
	{
		if (g_Door[nCnt].bUse == false)
		{// 壁が使用されていない
			g_Door[nCnt].pos = pos;		// 位置
			g_Door[nCnt].rot = rot;		// 角度
			g_Door[nCnt].bUse = true;	// 使用している
			break;
		}
	}
}
//================================================
//ブロック当たり判定
//================================================
void CollisionGimmick(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld)
{
	Player* pPlayer = GetPlayer();
	D3DXVECTOR3* posOld = pPosOld;		//前フレームのプレイヤーの位置
	D3DXVECTOR3* pos = pPos;			//現フレームのプレイヤーの位置

	for (int nCnt = 0; nCnt < MAX_DOOR; nCnt++)
	{
		if (g_Door[nCnt].bUse == true)
		{
			//左右手前奥のめり込み判定
			if (pos->y< g_Door[nCnt].pos.y + g_Door[nCnt].vtxMax.y && pos->y + (OBJ_P * 2.0f) > g_Door[nCnt].pos.y + g_Door[nCnt].vtxMin.y)
			{
				//左右のめり込み判定
				if (pos->z - OBJ_P< g_Door[nCnt].pos.z + g_Door[nCnt].vtxMax.z && pos->z + OBJ_P > g_Door[nCnt].pos.z + g_Door[nCnt].vtxMin.z)//プレイヤーのｚの範囲がブロックに重なっている
				{

					if (posOld->x + OBJ_P< g_Door[nCnt].pos.x + g_Door[nCnt].vtxMin.x && pos->x + OBJ_P > g_Door[nCnt].pos.x + g_Door[nCnt].vtxMin.x)//Ｘが左から右にめり込んだ
					{
						//pPlayer->posをモデルの左側にくっつける
						pos->x = g_Door[nCnt].pos.x + g_Door[nCnt].vtxMin.x - OBJ_P - 0.1f;

					}
					if (posOld->x - OBJ_P > g_Door[nCnt].pos.x + g_Door[nCnt].vtxMax.x && pos->x - OBJ_P < g_Door[nCnt].pos.x + g_Door[nCnt].vtxMax.x)//Ｘが左から右にめり込んだ
					{
						//pPlayer->posをモデルの右側にくっつける
						pos->x = g_Door[nCnt].pos.x + g_Door[nCnt].vtxMax.x + OBJ_P + 0.1f;
					}
				}

				//手前奥のめり込み判定
				if (pos->x - OBJ_P< g_Door[nCnt].pos.x + g_Door[nCnt].vtxMax.x && pos->x + OBJ_P > g_Door[nCnt].pos.x + g_Door[nCnt].vtxMin.x)//プレイヤーxの範囲がブロックに重なっている
				{

					if (posOld->z + OBJ_P< g_Door[nCnt].pos.z + g_Door[nCnt].vtxMin.z && pos->z + OBJ_P > g_Door[nCnt].pos.z + g_Door[nCnt].vtxMin.z)//Zが下から上にめり込んだ
					{
						//pPlayer->posをモデルの手前側にくっつける
						pos->z = g_Door[nCnt].pos.z + g_Door[nCnt].vtxMin.z - OBJ_P - 0.1f;
					}
					if (posOld->z - OBJ_P > g_Door[nCnt].pos.z + g_Door[nCnt].vtxMax.z && pos->z - OBJ_P < g_Door[nCnt].pos.z + g_Door[nCnt].vtxMax.z)//Zが上から下にめり込んだ
					{
						//pPlayer->posをモデルの奥側にくっつける
						pos->z = g_Door[nCnt].pos.z + g_Door[nCnt].vtxMax.z + OBJ_P + 0.1f;
					}
				}

			}
			if (pos->z - OBJ_P< g_Door[nCnt].pos.z + g_Door[nCnt].vtxMax.z && pos->z + OBJ_P > g_Door[nCnt].pos.z + g_Door[nCnt].vtxMin.z
				&& pos->x - OBJ_P< g_Door[nCnt].pos.x + g_Door[nCnt].vtxMax.x && pos->x + OBJ_P > g_Door[nCnt].pos.x + g_Door[nCnt].vtxMin.x)
			{
				if (posOld->y + (OBJ_P * 2.0f) < g_Door[nCnt].pos.y + g_Door[nCnt].vtxMin.y && pos->y + (OBJ_P * 2.0f) > g_Door[nCnt].pos.y + g_Door[nCnt].vtxMin.y)//Ｘが左から右にめり込んだ
				{
					//pPlayer->posをモデルの下側にくっつける
					pos->y = g_Door[nCnt].pos.y + g_Door[nCnt].vtxMin.y - (OBJ_P * 2.0f) - 0.1f;
				}
				if (posOld->y > g_Door[nCnt].pos.y + g_Door[nCnt].vtxMax.y && pos->y < g_Door[nCnt].pos.y + g_Door[nCnt].vtxMax.y)//Ｘが左から右にめり込んだ
				{
					//pPlayer->posをモデルの上側にくっつける
					pos->y = g_Door[nCnt].pos.y + g_Door[nCnt].vtxMax.y + 0.1f;
				}

			}

		}

	}
}

GIMMICK* GetGimmick(void)
{
	return &g_Door[0];
}

bool IsGoal()
{
	return isGoal;
}
bool IsBill()
{
	return isBill;
}
void IsHold()
{
	if (g_hold.bPush == true)
	{
		g_hold.nHoldCount++;
	}
	else if (g_hold.bPush == false)
	{
		g_hold.nHoldCount = g_hold.HolTime;
	}

	if (g_hold.bNoPush == true)
	{
		g_hold.count++;
		if (g_hold.count >= 5)
		{
			g_hold.count = 0;
			g_hold.NoTouch++;
		}
	}

	g_hold.HolTime = g_hold.nHoldCount - 1;

	if (g_hold.HolTime <= 0)
	{
		g_hold.HolTime = 0;
	}

	if (g_hold.HolTime >= 300)
	{
		isGoal = true;
	}
}
HOLD* GetHold(void)
{
	return &g_hold;
}