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

using json = nlohmann::json;

//*****************
// マクロ定義
//*****************
#define CALDERA_SIZE (400.0f)
#define ONEFLAME_SIZE (0.012f)

int g_nTime;
float f;

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

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\field.jpg",
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
			pVtx[nCntPOS].pos = D3DXVECTOR3(((OBJ_X * 2) / Xmesh) * nCntX - OBJ_X, 1.0f, (-1 * ((OBJ_Z * 2) / Zmesh) * nCntZ + OBJ_Z));
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
			pVtx[nCntTEX].tex = D3DXVECTOR2((1.0f / Xmesh) * nCntX, ((1.0f / Zmesh) * nCntZ));
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
	f = CALDERA_SIZE;
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
	{
		//VERTEX_3D* pVtx = 0;//頂点情報へのポインタ

		//D3DXVECTOR2 uv;
		//D3DXVECTOR2 uv2;
		//float distance;
		//D3DXVECTOR2 s;
		//s.x = 12.0f;
		//s.y = 13.0f;
		//D3DXVECTOR2 ss;
		//ss.x = 23.0f;
		//ss.y = 21.0f;
		//float f = sqrtf((s.x * ss.x) + (s.y * ss.y));
		//D3DXVec2Scale(&ss, &ss, 5);
		//D3DXVec2Scale(&s, &s, 5);
		//float ff = sqrtf((s.x * ss.x) + (s.y * ss.y));


		////頂点バッファをロックし、頂点情報へのポインタを取得
		//m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		//int nCntPOS = 0;

		//float Xmesh = (float)(XMESH);
		//float Zmesh = (float)(ZMESH);
		//for (int nCntZ = 0; nCntZ < ZMESH + 1; nCntZ++)
		//{
		//	//uvの値Y座標が大きくなるにつれて0.0f～1.0fになる
		//	uv.y = 1.0f / ZMESH * nCntZ;

		//	for (int nCntX = 0; nCntX < XMESH + 1; nCntX++, nCntPOS++)
		//	{
		//		//uvの値X座標が大きくなるにつれて0.0f～1.0fになる
		//		uv.x = 1.0f / XMESH * nCntX;
		//		uv2.x = (uv.x - 0.5f) * 2.0f;
		//		uv2.y = (uv.y - 0.5f) * 2.0f;
		//		//uv2.x *= 2.0f;
		//		//uv2.y *= 2.0f;

		//		//uv2.x = uv2.x-float(floor(uv2.x));
		//		//uv2.y = uv2.y-float(floor(uv2.y));

		//		//uv2.x -= 0.5f;
		//		//uv2.y -= 0.5f;
		//		uv2.x = fabsf(uv2.x);
		//		uv2.y = fabsf(uv2.y);
		//		distance = sqrtf(((uv2.x) * (uv2.x)) + ((uv2.y) * (uv2.y)));

		//		distance = sinf(distance * 10.0f - float(g_nTime) * 0.05f) * (1.0f - distance) * 0.5f;

		//		distance = fabsf(distance);

		//		if (distance > 1.0f)
		//		{
		//			distance = 1.0f;
		//		}

		//		pVtx[nCntPOS].pos = D3DXVECTOR3(((OBJ_X * 2) / Xmesh) * nCntX - OBJ_X, distance * 200.0f, (-1 * ((OBJ_Z * 2) / Zmesh) * nCntZ + OBJ_Z));
		//		pVtx[nCntPOS].col = D3DXCOLOR(0.8f, 0.8f, distance + 0.1f, 1.0f);
		//	}
		//}
		////頂点バッファをアンロックする
		//m_pVtxBuff->Unlock();

		//g_nTime++;
	}
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
	// プレイヤー情報取得
	CPlayer* pPlayer = CManager::GetCPlayer();

	// 計算用変数
	float sizeX, sizeZ;
	float posX,posZ;
	int nCount,a, b;
	D3DXVECTOR3 nor, vtx0, norP[6], vec1, vec2;
	float fHeight = 0.0f;

	sizeX = (OBJ_X*2) / XMESH;
	sizeZ = (OBJ_Z*2) / ZMESH;
	posX = pos.x + OBJ_X;
	posZ = pos.z - OBJ_Z;
	b = (int)(posZ / -sizeZ);
	a = (int)((posX +b*OBJ_X*2) / sizeX);
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
			D3DXVec3Cross(&nor, &vec1, &vec2);
			D3DXVec3Normalize(&nor, &nor);
			
			vtx0 = pVtx[nCount + 1].pos;
			fHeight = vtx0.y - ((pos.x - vtx0.x) * nor.x + (pos.z - vtx0.z) * nor.z) / nor.y;
		}
		else if (0.0f > norP[3].y
			&& 0.0f > norP[4].y
			&& 0.0f > norP[5].y)
		{
			if (pInputKeyboard->GetPress(DIK_SPACE) == true)
			{
				pVtx[nCount].pos.y -= 0.4f;
				pVtx[nCount + XMESH + 1].pos.y -= 0.4f;
				pVtx[nCount + XMESH + 2].pos.y -= 0.4f;
			}
			vec1 = pVtx[nCount].pos - pVtx[nCount + XMESH + 1].pos;
			vec2 = pVtx[nCount + XMESH + 2].pos - pVtx[nCount + XMESH + 1].pos;
			D3DXVec3Cross(&nor, &vec1, &vec2);
			D3DXVec3Normalize(&nor, &nor);
			vtx0 = pVtx[nCount + XMESH + 1].pos;
			fHeight = vtx0.y - ((pos.x - vtx0.x) * nor.x + (pos.z - vtx0.z) * nor.z) / nor.y;
		}
		else
		{
			fHeight = 0.0f;
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
	// プレイヤー情報取得
	CPlayer* pPlayer = CManager::GetCPlayer();

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
	if (0.0f < f)
	{
		f -= ONEFLAME_SIZE * g_nTime;
	}
	g_nTime++;

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
			if (f > distance)
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
void CMesh::Save(const std::vector<int>& nNum, const std::string& FileName)
{
	// 保存するファイルを開く
	std::ofstream outFile("data\\output.txt");
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