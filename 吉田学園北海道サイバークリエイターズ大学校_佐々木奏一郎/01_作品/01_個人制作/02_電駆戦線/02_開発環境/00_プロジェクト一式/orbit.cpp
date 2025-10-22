//***************************************
// 
// 軌跡処理[orbit.cpp]
// Author:Sasaki Soichiro
// 
//***************************************

//******************
// インクルード
//******************
#include "orbit.h"
#include "manager.h"
#include <string>
#include <iostream>
#include "json.hpp"
#include "game.h"
#include "renderer.h"
#include "mesh.h"

//****************
// コンストラクタ
//****************
COrbit::COrbit(int nPriority) : CObject(nPriority)
{
	m_pTexture = NULL;						// テクスチャのポインタ
	m_pVtxBuff = NULL;						// 頂点バッファ
	m_pIdxBuff = NULL;						// インデックスバッファ
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 位置
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 向き
	m_FPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 位置
	m_SPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 位置;
	m_mtxWorld = {};						// ワールドマトリックス
	m_Frame = 0;
	for (int nCnt = 0; nCnt < MAX_ORBITVTX / 2 - 1; nCnt++)
	{
		m_oldFPos[nCnt]=D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_oldSPos[nCnt]=D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
	m_Time = 0;
}

//****************
// デストラクタ
//****************
COrbit::~COrbit()
{

}

//*******************
// インスタンス生成
//*******************
COrbit* COrbit::Create(D3DXVECTOR3 pos)
{
	COrbit* pOrbit;
	// テクスチャ情報の取得
	CTexture* pTexture = CManager::GetCTexture();

	// 現在のオブジェクト総数取得
	int nNum = CObject::GetNumAll();
	if (nNum < MAX_OBJ - 1)
	{// 最大オブジェクト数に達していなかったら

		// インスタンス生成
		pOrbit = new COrbit;
		// 初期化
		pOrbit->Init(pos);

		return pOrbit;
	}

	return NULL;
}

//**************
// 初期化
//**************
HRESULT COrbit::Init(D3DXVECTOR3 pos)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	CRenderer* renderer = CManager::GetCRenderer();
	pDevice = renderer->GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\orbit.jpg",
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

	int nCC = MAX_ORBITVTX;
	for (int nCnt = 0; nCnt < MAX_ORBITVTX; nCnt++, nCC--)
	{
		pVtx[nCnt].pos = D3DXVECTOR3(408.0f, 1.0f, -3.5f);
		//各頂点の法線の設定
		pVtx[nCnt].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f-(0.07f*nCnt));
	}
	int nCntTEX = 0;
	for (int nCnt = 0; nCnt < MAX_ORBITVTX; nCnt += 2, nCntTEX++)
	{
		pVtx[nCnt + 1].tex = D3DXVECTOR2((1.0f / (MAX_ORBITVTX / 2) * nCntTEX), 0.0f);
		pVtx[nCnt].tex = D3DXVECTOR2((1.0f / (MAX_ORBITVTX / 2) * nCntTEX), 1.0f);
	}

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();


	//インデックスバッファをロック
	WORD* pIdx;
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);


	for (int nCnt = 0; nCnt < MAX_ORBITVTX; nCnt++)
	{
		pIdx[nCnt] = nCnt;
	}
	for (int nCnt = 0; nCnt < MAX_ORBITVTX / 2 - 1; nCnt++)
	{
		m_oldFPos[nCnt] = D3DXVECTOR3(408.0f, 1.0f, -3.5f);
		m_oldSPos[nCnt] = D3DXVECTOR3(408.0f, 1.0f, -3.5f);
	}
	//頂点バッファをアンロックする
	m_pIdxBuff->Unlock();
	return S_OK;
}

//**************
// 終了処理
//**************
void COrbit::Uninit(void)
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
void COrbit::Update(void)
{
	VERTEX_3D* pVtx = 0;//頂点情報へのポインタ
	//D3DXVECTOR3 posOld[2];
	int nCnt = 0;
	int nCntEX = 0;
	m_Time++;
	m_Frame++;


	if (m_Time >= (MAX_ORBITVTX / 2) - 1)
	{
		m_Time = 0;
	}
	nCntEX = m_Time;
	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	m_oldFPos[m_Time] = pVtx[0].pos;
	m_oldSPos[m_Time] = pVtx[1].pos;

	pVtx[0].pos = m_FPos;
	pVtx[1].pos = m_SPos;

	for (int nCntOrbit = 2; nCntOrbit < MAX_ORBITVTX; nCntOrbit += 2, nCnt += 2)
	{

		pVtx[nCntOrbit].pos.x = m_oldFPos[nCntEX].x;
		pVtx[nCntOrbit].pos.y = m_oldFPos[nCntEX].y;
		pVtx[nCntOrbit].pos.z = m_oldFPos[nCntEX].z;

		pVtx[nCntOrbit + 1].pos.x = m_oldSPos[nCntEX].x;
		pVtx[nCntOrbit + 1].pos.y = m_oldSPos[nCntEX].y;
		pVtx[nCntOrbit + 1].pos.z = m_oldSPos[nCntEX].z;

		if (nCntEX <= 0)
		{
			nCntEX = (MAX_ORBITVTX / 2) - 2;
		}
		else
		{
			nCntEX--;
		}
	}


	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//**************
// 描画
//**************
void COrbit::Draw(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	CRenderer* renderer = CManager::GetCRenderer();
	pDevice = renderer->GetDevice();

	// 計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;
	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	// αブレンディングを加算合成に設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// 向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);
	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));
	// インデックスバッファをデータストリームに設定
	pDevice->SetIndices(m_pIdxBuff);
	// テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);
	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);
	// ポリゴンの描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, MAX_ORBITVTX, 0, 14);

	//αブレンディングを元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

}

//**************
// 位置の設定
//**************
void COrbit::SetPosS(D3DXVECTOR3 pos0, D3DXVECTOR3 pos1)
{
	m_FPos = pos0;
	m_SPos = pos1;
}