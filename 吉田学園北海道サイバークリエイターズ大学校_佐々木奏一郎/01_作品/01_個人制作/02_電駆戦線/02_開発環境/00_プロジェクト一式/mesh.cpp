//***************************************
// 
// メッシュフィールド処理[mesh.cpp]
// Author:Sasaki Soichiro
// 
//***************************************

//******************
// インクルード
//******************
#include "mesh.h"
#include "manager.h"
#include <string>
#include <iostream>
#include "json.hpp"
#include "game.h"
#include "renderer.h"
#include "debugproc.h"


using json = nlohmann::json;

//*****************
// マクロ定義
//*****************
#define CALDERA_SIZE (10.0f)
#define ONEFLAME_SIZE (0.008f)

//****************
// コンストラクタ
//****************
CMesh::CMesh(int nPriority) : CObject(nPriority)
{
	m_pTexture = NULL;						// テクスチャのポインタ
	m_pVtxBuff = NULL;						// 頂点バッファ
	m_pIdxBuff = NULL;						// インデックスバッファ
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 位置
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 向き
	m_mtxWorld = {};						// ワールドマトリックス
	m_caldera = 0.0f;						// くぼみを作る
	m_Sum = 0.0f;							// 計算用
}

//****************
// デストラクタ
//****************
CMesh::~CMesh()
{

}

//*******************
// インスタンス生成
//*******************
CMesh* CMesh::Create(D3DXVECTOR3 pos)
{
	CMesh* pMesh;// メッシュ情報取得
	CTexture* pTexture = CManager::GetCTexture();// テクスチャ情報の取得

	// 現在のオブジェクト総数取得
	int nNum = CObject::GetNumAll();
	if (nNum < MAX_OBJ - 1)
	{// 最大オブジェクト数に達していなかったら

		// インスタンス生成
		pMesh = new CMesh;
		// 初期化
		pMesh->Init(pos);
		// pMeshを渡す
		return pMesh;
	}

	//(失敗したら)NULLを返す
	return NULL;
}

//**************
// 初期化
//**************
HRESULT CMesh::Init(D3DXVECTOR3 pos)
{
	
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	CRenderer* renderer = CManager::GetCRenderer();
	pDevice = renderer->GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\floor.png",
		&m_pTexture);

	// 頂点バッファの作成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * VTXCNT,//(sizeof(VERTEX_3D)*必要な頂点数
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);
	// インデックスバッファの作成
	pDevice->CreateIndexBuffer(sizeof(VERTEX_3D) * IDXCNT,//(sizeof(VERTEX_3D)*必要な頂点数
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIdxBuff,
		NULL);

	VERTEX_3D* pVtx = 0;//頂点情報へのポインタ


	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// カウント用変数
	int nCntPOS = 0;
	float Xmesh = (float)(XMESH);
	float Zmesh = (float)(ZMESH);

	// 頂点バッファの設定
	for (int nCntZ = 0; nCntZ < ZMESH + 1; nCntZ++)
	{
		for (int nCntX = 0; nCntX < XMESH + 1; nCntX++, nCntPOS++)
		{
			float Angle = ((D3DX_PI * 0.5f) / XMESH * nCntX);
			pVtx[nCntPOS].pos = D3DXVECTOR3(pos.x+(((OBJ_X * 2) / Xmesh) * nCntX - OBJ_X), 1.0f, pos.z + (-1 * ((OBJ_Z * 2) / Zmesh) * nCntZ + OBJ_Z));
			//pVtx[nCntPOS].pos = D3DXVECTOR3(((OBJ_X * 2) / Xmesh) * nCntX - OBJ_X, (-sinf(Angle)*radius)+radius, (-1 * ((OBJ_Z * 2) / Zmesh) * nCntZ + OBJ_Z));

		}
	}


	for (int nCnt = 0; nCnt < VTXCNT; nCnt++)
	{//各頂点の法線の設定
		pVtx[nCnt].nor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}

	// カウント用変数
	int nCntTEX = 0;
	for (int nCntZ = 0; nCntZ < ZMESH + 1; nCntZ++)
	{
		for (int nCntX = 0; nCntX < XMESH + 1; nCntX++, nCntTEX++)
		{
			pVtx[nCntTEX].tex = D3DXVECTOR2((1.0f / 4.0f) * nCntX, ((1.0f / 4.0f) * nCntZ));
		}
	}


	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	//インデックスバッファをロック
	WORD* pIdx;
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	// カウント用変数
	int nCntX=0;
	int nCnt = 0;
	std::vector<int> A(IDXCNT, 0);
	std::vector<int> B(IDXCNT, 0);

	for (nCnt = 0; nCnt < IDXCNT; nCnt++, nCntX++)
	{
		if (nCnt == 0)
		{
			A[nCnt] = (2 * XMESH) + 3;
			B[nCnt] = -XMESH - 1;
			pIdx[nCnt] = XMESH + 1;
		}
		else
		{
			A[nCnt] = -1 * (A[nCnt - 1]);

			B[nCnt] = B[nCnt - 1] + A[nCnt - 1];


			if (nCntX == 2 * (XMESH + 1))
			{
				pIdx[nCnt] = pIdx[nCnt - 1];
			}

			else if (nCntX == 2 * (XMESH + 1) + 1)
			{
				pIdx[nCnt] = pIdx[nCnt - 2] + B[nCnt - 2];
			}

			else if (nCntX == 2 * (XMESH + 1) + 2)
			{
				nCntX = 0;

				pIdx[nCnt] = pIdx[nCnt - 1];
			}

			else
			{
				pIdx[nCnt] = pIdx[nCnt - 1] + B[nCnt - 1];
			}

		}
	}

	//頂点バッファをアンロックする
	m_pIdxBuff->Unlock();
	// ロード
	Load();
	m_caldera = 500.0f;
	m_Sum = 1.0f;
	return S_OK;
}

//**************
// 終了処理
//**************
void CMesh::Uninit(void)
{
	//テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}

	//頂点バッファの解放
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	//インデックスバッファの解放
	if (m_pIdxBuff != NULL)
	{
		m_pIdxBuff->Release();
		m_pIdxBuff = NULL;
	}
	CObject::Release();
}

//**************
// 更新
//**************
void CMesh::Update(void)
{
	VERTEX_3D* pVtx = 0;//頂点情報へのポインタ

	// カウント用変数
	int nCntPOS = 0;
	float Xmesh = (float)(XMESH);
	float Zmesh = (float)(ZMESH);
	D3DXVECTOR3 vec1, vec2,norAnswer,nor[4];
	D3DXVECTOR3 NOR = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 法線の更新
	for (int nCntZ = 0; nCntZ < ZMESH + 1; nCntZ++)
	{
		for (int nCntX = 0; nCntX < XMESH + 1; nCntX++, nCntPOS++)
		{
			if (nCntZ == 0)
			{// Zのカウントが0だったら
				if (nCntX == 0)
				{// Xのカウントが0だったら(角の頂点)
					// 法線計算代入
					pVtx[nCntPOS].nor =	VtxNor(	pVtx[nCntPOS].pos,				// 対象の頂点座標
												pVtx[nCntPOS + 1].pos,			// 隣接の頂点座標1
												pVtx[nCntPOS + XMESH + 1].pos);	// 隣接の頂点座標2
				}
				else if (nCntX == XMESH)
				{// Xのカウントが最後だったら(角の頂点)
					// 法線計算代入
					pVtx[nCntPOS].nor = VtxNor(	pVtx[nCntPOS].pos,				// 対象の頂点座標
												pVtx[nCntPOS + XMESH + 1].pos,	// 隣接の頂点座標1
												pVtx[nCntPOS  - 1].pos);		// 隣接の頂点座標2
				}
				else
				{// それ以外(辺の頂点)
					nor[0] = VtxNor(pVtx[nCntPOS].pos,				// 対象の頂点座標
									pVtx[nCntPOS + 1].pos,			// 隣接の頂点座標1
									pVtx[nCntPOS + XMESH + 1].pos);	// 隣接の頂点座標2

					nor[1] = VtxNor(pVtx[nCntPOS].pos,				// 対象の頂点座標
									pVtx[nCntPOS + XMESH + 1].pos,	// 隣接の頂点座標1
									pVtx[nCntPOS - 1].pos);			// 隣接の頂点座標2

					norAnswer = (nor[0] + nor[1]) / 2.0f;
					D3DXVec3Normalize(&norAnswer, &norAnswer);
					pVtx[nCntPOS].nor = norAnswer;
				}
			}
			else if (nCntZ == ZMESH)
			{// Zのカウントが最後だったら
				if (nCntX == 0)
				{// Xのカウントが0だったら
					// 法線計算代入
					pVtx[nCntPOS].nor = VtxNor(	pVtx[nCntPOS].pos,				// 対象の頂点座標
												pVtx[nCntPOS - XMESH - 1].pos,	// 隣接の頂点座標1
												pVtx[nCntPOS + 1].pos);			// 隣接の頂点座標2
				}
				else if (nCntX == XMESH)
				{// Xのカウントが最後だったら
					pVtx[nCntPOS].nor = VtxNor(	pVtx[nCntPOS].pos,				// 対象の頂点座標
												pVtx[nCntPOS - 1].pos,			// 隣接の頂点座標1
												pVtx[nCntPOS - XMESH - 1].pos);	// 隣接の頂点座標2
				}
				else
				{// それ以外
					nor[0] = VtxNor(pVtx[nCntPOS].pos,				// 対象の頂点座標
									pVtx[nCntPOS - XMESH - 1].pos,	// 隣接の頂点座標1
									pVtx[nCntPOS + 1].pos);			// 隣接の頂点座標2
					nor[1] = VtxNor(pVtx[nCntPOS].pos,				// 対象の頂点座標
									pVtx[nCntPOS - 1].pos,			// 隣接の頂点座標1
									pVtx[nCntPOS - XMESH - 1].pos);	// 隣接の頂点座標2
					norAnswer = (nor[0] + nor[1]) / 2.0f;
					D3DXVec3Normalize(&norAnswer, &norAnswer);
					pVtx[nCntPOS].nor = norAnswer;
				}
			}
			else if (nCntX == 0)
			{// Xのカウントが0だったら
				vec1 = pVtx[nCntPOS + 1].pos - pVtx[nCntPOS].pos;
				vec2 = pVtx[nCntPOS + XMESH + 1].pos - pVtx[nCntPOS].pos;
				D3DXVec3Cross(&nor[0], &vec1, &vec2);
				vec1 = pVtx[nCntPOS - XMESH - 1].pos - pVtx[nCntPOS].pos;
				vec2 = pVtx[nCntPOS + 1].pos - pVtx[nCntPOS].pos;
				D3DXVec3Cross(&nor[1], &vec1, &vec2);
				norAnswer = (nor[0] + nor[1]) / 2.0f;
				D3DXVec3Normalize(&norAnswer, &norAnswer);
				pVtx[nCntPOS].nor = norAnswer;
			}
			else if (nCntX == XMESH)
			{// Xのカウントが0だったら
				vec1 = pVtx[nCntPOS - 1].pos - pVtx[nCntPOS].pos;
				vec2 = pVtx[nCntPOS - XMESH - 1].pos - pVtx[nCntPOS].pos;
				D3DXVec3Cross(&nor[0], &vec1, &vec2);
				vec1 = pVtx[nCntPOS + XMESH + 1].pos - pVtx[nCntPOS].pos;
				vec2 = pVtx[nCntPOS - 1].pos - pVtx[nCntPOS].pos;
				D3DXVec3Cross(&nor[1], &vec1, &vec2);
				norAnswer = (nor[0] + nor[1]) / 2.0f;
				D3DXVec3Normalize(&norAnswer, &norAnswer);
				pVtx[nCntPOS].nor = norAnswer;
			}
			else
			{// それ以外
				vec1 = pVtx[nCntPOS + 1].pos - pVtx[nCntPOS].pos;
				vec2 = pVtx[nCntPOS + XMESH + 1].pos - pVtx[nCntPOS].pos;
				D3DXVec3Cross(&nor[0], &vec1, &vec2);
				vec1 = pVtx[nCntPOS - XMESH - 1].pos - pVtx[nCntPOS].pos;
				vec2 = pVtx[nCntPOS + 1].pos - pVtx[nCntPOS].pos;
				D3DXVec3Cross(&nor[1], &vec1, &vec2);
				vec1 = pVtx[nCntPOS - 1].pos - pVtx[nCntPOS].pos;
				vec2 = pVtx[nCntPOS - XMESH - 1].pos - pVtx[nCntPOS].pos;
				D3DXVec3Cross(&nor[2], &vec1, &vec2);
				vec1 = pVtx[nCntPOS + XMESH + 1].pos - pVtx[nCntPOS].pos;
				vec2 = pVtx[nCntPOS - 1].pos - pVtx[nCntPOS].pos;
				D3DXVec3Cross(&nor[3], &vec1, &vec2);
				norAnswer = (nor[0] + nor[1]+nor[2]+nor[3]+ NOR) / 5.0f;
				D3DXVec3Normalize(&norAnswer, &norAnswer);
				pVtx[nCntPOS].nor = norAnswer;
			}
		}
	}
	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//**************
// 描画
//**************
void CMesh::Draw(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	CRenderer* renderer = CManager::GetCRenderer();
	pDevice = renderer->GetDevice();

	//計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;
	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);
	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);
	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));
	//インデックスバッファをデータストリームに設定
	pDevice->SetIndices(m_pIdxBuff);
	//テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);
	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);
	//ポリゴンの描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, VTXCNT, 0, POLYCNT);
}

//**************
// 高さ情報
//**************
float CMesh::GetHeight(D3DXVECTOR3 pos)
{
	// キーボードの取得
	CInputKeyboard* pInputKeyboard;
	pInputKeyboard = CManager::GetCInputKeyboard();

	// ポリゴンの高さを求める変数
	float sizeX, sizeZ;
	float posX,posZ;
	int nCount,a, b;
	D3DXVECTOR3 nor, vtx0, norP[6], vec1, vec2;
	float fHeight = 0.0f;

	// 現在の位置が何番目のメッシュに所属しているか
	sizeX = (OBJ_X * 2) / XMESH;
	sizeZ = (OBJ_Z * 2) / ZMESH;
	posX = pos.x + OBJ_X;
	posZ = pos.z - OBJ_Z;
	b = (int)(posZ / -sizeZ);
	a = (int)((posX + b * OBJ_X * 2) / sizeX);
	nCount = (int)(a + b);
	CDebugProc::Print("\n現在のメッシュ%d\n", nCount);


	VERTEX_3D* pVtx = 0;//頂点情報へのポインタ

	if (nCount >= 0 && nCount <= (XMESH + 1) * (ZMESH + 1))
	{
		//頂点バッファをロックし、頂点情報へのポインタを取得
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
		// 1ポリゴン目
		vec1 = pVtx[nCount + 1].pos - pVtx[nCount].pos;
		vec2 = pos - pVtx[nCount].pos;
		D3DXVec3Cross(&norP[0], &vec1, &vec2);

		vec1 = pVtx[nCount + XMESH + 2].pos - pVtx[nCount + 1].pos;
		vec2 = pos - pVtx[nCount + 1].pos;
		D3DXVec3Cross(&norP[1], &vec1, &vec2);

		vec1 = pVtx[nCount].pos - pVtx[nCount + XMESH + 2].pos;
		vec2 = pos - pVtx[nCount + XMESH + 2].pos;
		D3DXVec3Cross(&norP[2], &vec1, &vec2);

		// 2ポリゴン目
		vec1 = pVtx[nCount + XMESH + 2].pos - pVtx[nCount + XMESH + 1].pos;
		vec2 = pos - pVtx[nCount + XMESH + 1].pos;
		D3DXVec3Cross(&norP[3], &vec1, &vec2);

		vec1 = pVtx[nCount + XMESH + 1].pos - pVtx[nCount].pos;
		vec2 = pos - pVtx[nCount].pos;
		D3DXVec3Cross(&norP[4], &vec1, &vec2);

		vec1 = pVtx[nCount].pos - pVtx[nCount + XMESH + 2].pos;
		vec2 = pos - pVtx[nCount + XMESH + 2].pos;
		D3DXVec3Cross(&norP[5], &vec1, &vec2);

		if (0.0f < norP[0].y
			&& 0.0f < norP[1].y
			&& 0.0f < norP[2].y)
		{// 1ポリゴン目の中にいた場合

			// 法線を求める計算
			vec1 = pVtx[nCount].pos - pVtx[nCount + 1].pos;
			vec2 = pVtx[nCount + XMESH + 2].pos - pVtx[nCount + 1].pos;
			D3DXVec3Cross(&nor, &vec1, &vec2);
			D3DXVec3Normalize(&nor, &nor);
			
			vtx0 = pVtx[nCount + 1].pos;
			// 現在地の高さを計算
			fHeight = vtx0.y - ((pos.x - vtx0.x) * nor.x + (pos.z - vtx0.z) * nor.z) / nor.y;
		}
		else if (0.0f > norP[3].y
			&& 0.0f > norP[4].y
			&& 0.0f > norP[5].y)
		{// 2ポリゴン目の中にいた場合

			// 法線を求める計算
			vec1 = pVtx[nCount].pos - pVtx[nCount + XMESH + 1].pos;
			vec2 = pVtx[nCount + XMESH + 2].pos - pVtx[nCount + XMESH + 1].pos;
			D3DXVec3Cross(&nor, &vec1, &vec2);
			D3DXVec3Normalize(&nor, &nor);

			vtx0 = pVtx[nCount + XMESH + 1].pos;
			// 現在地の高さを計算
			fHeight = vtx0.y - ((pos.x - vtx0.x) * nor.x + (pos.z - vtx0.z) * nor.z) / nor.y;
		}
		else
		{
			fHeight = pos.y;
		}

		//頂点バッファをアンロックする
		m_pVtxBuff->Unlock();
	}
	return fHeight;
}

//***************
// 法線の情報
//***************
D3DXVECTOR3 CMesh::GetNormal(D3DXVECTOR3 pos)
{
	// キーボードの取得
	CInputKeyboard* pInputKeyboard;
	pInputKeyboard = CManager::GetCInputKeyboard();

	// 計算用変数
	float sizeX, sizeZ;
	float posX, posZ;
	int nCount, a, b;
	D3DXVECTOR3 nor, vtx0, norP[6], vec1, vec2;
	float fHeight = 0.0f;

	sizeX = (OBJ_X * 2) / XMESH;
	sizeZ = (OBJ_Z * 2) / ZMESH;
	posX = pos.x + OBJ_X;
	posZ = pos.z - OBJ_Z;
	b = (int)(posZ / -sizeZ);
	a = (int)((posX + b * OBJ_X * 2) / sizeX);
	nCount = (int)(a + b);
	CDebugProc::Print("\n現在のメッシュ%d\n", nCount);


	VERTEX_3D* pVtx = 0;//頂点情報へのポインタ

	if (nCount >= 0 && nCount <= (XMESH + 1) * (ZMESH + 1))
	{
		//頂点バッファをロックし、頂点情報へのポインタを取得
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
		// 1ポリゴン目
		vec1 = pVtx[nCount + 1].pos - pVtx[nCount].pos;
		vec2 = pos - pVtx[nCount].pos;
		D3DXVec3Cross(&norP[0], &vec1, &vec2);

		vec1 = pVtx[nCount + XMESH + 2].pos - pVtx[nCount + 1].pos;
		vec2 = pos - pVtx[nCount + 1].pos;
		D3DXVec3Cross(&norP[1], &vec1, &vec2);

		vec1 = pVtx[nCount].pos - pVtx[nCount + XMESH + 2].pos;
		vec2 = pos - pVtx[nCount + XMESH + 2].pos;
		D3DXVec3Cross(&norP[2], &vec1, &vec2);

		// 2ポリゴン目
		vec1 = pVtx[nCount + XMESH + 2].pos - pVtx[nCount + XMESH + 1].pos;
		vec2 = pos - pVtx[nCount + XMESH + 1].pos;
		D3DXVec3Cross(&norP[3], &vec1, &vec2);

		vec1 = pVtx[nCount + XMESH + 1].pos - pVtx[nCount].pos;
		vec2 = pos - pVtx[nCount].pos;
		D3DXVec3Cross(&norP[4], &vec1, &vec2);

		vec1 = pVtx[nCount].pos - pVtx[nCount + XMESH + 2].pos;
		vec2 = pos - pVtx[nCount + XMESH + 2].pos;
		D3DXVec3Cross(&norP[5], &vec1, &vec2);

		if (0.0f < norP[0].y
			&& 0.0f < norP[1].y
			&& 0.0f < norP[2].y)
		{
			vec1 = pVtx[nCount].pos - pVtx[nCount + 1].pos;
			vec2 = pVtx[nCount + XMESH + 2].pos - pVtx[nCount + 1].pos;
			D3DXVec3Cross(&nor, &vec2, &vec1);
			D3DXVec3Normalize(&nor, &nor);
			return nor;
		}
		else if (0.0f > norP[3].y
			&& 0.0f > norP[4].y
			&& 0.0f > norP[5].y)
		{
			vec1 = pVtx[nCount].pos - pVtx[nCount + XMESH + 1].pos;
			vec2 = pVtx[nCount + XMESH + 2].pos - pVtx[nCount + XMESH + 1].pos;
			D3DXVec3Cross(&nor, &vec1, &vec2);
			D3DXVec3Normalize(&nor, &nor);
			return nor;
		}
		else
		{
			return D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		}

		//頂点バッファをアンロックする
		m_pVtxBuff->Unlock();
	}
	return D3DXVECTOR3(0.0f, 1.0f, 0.0f);
}

void CMesh::MoveY(D3DXVECTOR3 pos)
{
	VERTEX_3D* pVtx = 0;// 頂点情報へのポインタ
	D3DXVECTOR2 pPos = D3DXVECTOR2(pos.x, pos.z);
	int nCntPOS = 0;
	float Xmesh = (float)(XMESH);
	float Zmesh = (float)(ZMESH);
	m_caldera -= 0.8f * m_Sum;
	m_Sum += ONEFLAME_SIZE;
	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntZ = 0; nCntZ < ZMESH + 1; nCntZ++)
	{
		for (int nCntX = 0; nCntX < XMESH + 1; nCntX++, nCntPOS++)
		{
			D3DXVECTOR2 vPos =D3DXVECTOR2(pVtx[nCntPOS].pos.x, pVtx[nCntPOS].pos.z);
			float a = vPos.x - pPos.x;
			float b = vPos.y - pPos.y;
			float distance = sqrtf((a * a) + (b * b));
			if (m_caldera > distance)
			{
				pVtx[nCntPOS].pos.y -= 0.8f;
			}
		}
	}

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//*******************
// 地形セーブ
//*******************
void CMesh::Save(void)
{
	// 保存するファイルを開く
	std::ofstream outFile("data\\output01.txt");
	if (!outFile)
	{// 開けなかった場合
		return;
	}

	// 小数点以下も保存する
	outFile << std::fixed << std::setprecision(2); 

	VERTEX_3D* pVtx = 0;// 頂点情報へのポインタ

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < VTXCNT; nCnt++)
	{// 頂点数分ループする
		// 位置・法線を保存
		float posX = pVtx[nCnt].pos.x, posY = pVtx[nCnt].pos.y, posZ = pVtx[nCnt].pos.z;
		float norX = pVtx[nCnt].nor.x, norY = pVtx[nCnt].nor.y, norZ = pVtx[nCnt].nor.z;

		outFile << "vtx" << nCnt << ":"								// 頂点番号
			<< "pos = " << posX << " " << posY << " " << posZ<<" "	// 位置
			<< "nor = " << norX << " " << norY << " " << norZ		// 法線
			<< std::endl;											// 行終わり
	}

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
	
	// ファイルを明示的に閉じる
	outFile.close();
}

//*************
// 地形ロード
//*************
void CMesh::Load(void)
{
	std::ifstream file("data\\output.txt");
	if (file.is_open() == false)
	{
		return;
	}
	std::string line;
	VERTEX_3D* pVtx;//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	int index = 0;
	int nCnt = 0;
	while (std::getline(file, line))
	{
		int scan=sscanf(line.c_str(),
			"vtx %d:pos = %f %f %f nor = %f %f %f",
			&index, &pVtx[nCnt].pos.x, &pVtx[nCnt].pos.y, &pVtx[nCnt].pos.z,
			&pVtx[nCnt].nor.x, &pVtx[nCnt].nor.y, &pVtx[nCnt].nor.z);
		nCnt++;
	}
	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	// ファイルを明示的に閉じる
	file.close();
}

//*****************
// 頂点の法線計算
//*****************
D3DXVECTOR3 CMesh::VtxNor(D3DXVECTOR3 pos0, D3DXVECTOR3 pos1, D3DXVECTOR3 pos2)
{
	D3DXVECTOR3 vec1, vec2, nor;

	// ベクトル1の計算
	vec1 = pos1 - pos0;
	// ベクトル2の計算
	vec2 = pos2 - pos0;
	// 外積で法線を求める
	D3DXVec3Cross(&nor, &vec1, &vec2);
	// ノーマライズ
	D3DXVec3Normalize(&nor, &nor);

	// 計算結果を渡す
	return nor;
}

void CMesh::SetCaldera(float size)
{
	m_caldera = CALDERA_SIZE * size;
	m_Sum = 1.0f;
}