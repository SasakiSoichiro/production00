//**********************************
//
// Xファイル処理 [objectX.cpp]
// Author:Sasaki Soichiro
//
//**********************************

//*******************
// インクルード
//*******************
#include "objectX.h"
#include "manager.h"
#include "texture.h"
//=================
// コンストラクタ
//=================
CObjectX::CObjectX(int nPriority) :CObject(nPriority)
{
	m_XModel.pMesh=NULL;
	m_XModel.pBuffMat=NULL;
	m_XModel.dwNumMat = NULL;
	m_mtxWorld = {};
	m_pVtxBuff = NULL;	// 頂点情報のポインタ
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 位置
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 向き
	for (int nCnt = 0; nCnt < 128; nCnt++)
	{
		m_nIdxTexture[nCnt] = -1;
	}
}

//=================
// デストラクタ
//=================
CObjectX::~CObjectX()
{
}

CObjectX* CObjectX::Create(D3DXVECTOR3 pos)
{
	CObjectX* pCObjectX;
	CTexture* pTexture = CManager::GetCTexture();

	int nNum = CObject::GetNumAll();
	if (nNum < MAX_OBJ - 1)
	{
		pCObjectX = new CObjectX;
		pCObjectX->Init(pos);
		return pCObjectX;
	}
	return NULL;
}

//初期化処理
HRESULT CObjectX::Init(D3DXVECTOR3 pos)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	CRenderer* renderer = CManager::GetCRenderer();
	pDevice = renderer->GetDevice();

	//各種変数の初期化
	m_pos = D3DXVECTOR3(pos);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	int nNumVtx;//頂点数
	DWORD sizeFVF;//頂点フォーマットのサイズ
	//BYTE* pVtxBuff;//頂点バッファへのポインタ

	//頂点数の取得

	nNumVtx = m_XModel.pMesh->GetNumVertices();
	sizeFVF = D3DXGetFVFVertexSize(m_XModel.pMesh->GetFVF());
	//頂点バッファのロック
	//m_pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	//for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	//{
	//	//頂点座標の代入
	//	D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

	//	//頂点座標を比較してモデルの最小値最大値を取得
	//	//X============================
	//	if (vtx.x > m_vtxMax.x)
	//	{
	//		m_vtxMax.x = vtx.x;
	//	}

	//	if (vtx.x < m_vtxMin.x)
	//	{
	//		m_vtxMin.x = vtx.x;
	//	}
	//	//Y============================
	//	if (vtx.y > m_vtxMax.y)
	//	{
	//		m_vtxMax.y = vtx.y;
	//	}

	//	if (vtx.y < m_vtxMin.y)
	//	{
	//		m_vtxMin.y = vtx.y;
	//	}
	//	//Z=============================
	//	if (vtx.z > m_vtxMax.z)
	//	{
	//		m_vtxMax.z = vtx.z;
	//	}

	//	if (vtx.z < m_vtxMin.z)
	//	{
	//		m_vtxMin.z = vtx.z;
	//	}

	//	//頂点フォーマットのサイズ分ポインタを進める
	//	pVtxBuff += sizeFVF;
	//}
	////頂点バッファのアンロック
	//m_pMesh->UnlockVertexBuffer();

	D3DXMATERIAL* pMat;//マテリアルへのポインタ

	//マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)m_XModel.pBuffMat->GetBufferPointer();
	CTexture* pTexture = CManager::GetCTexture();

	for (int nCntMat = 0; nCntMat < (int)m_XModel.dwNumMat; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{//テクスチャファイルが存在する
				//テクスチャの読み込み
			m_nIdxTexture[nCntMat] = pTexture->Register(pMat[nCntMat].pTextureFilename);
		}
	}
	return TRUE;
}
void CObjectX::Uninit(void)
{
	//// テクスチャの破棄
	//if (m_pTexture != NULL)
	//{
	//	m_pTexture->Release();
	//	m_pTexture = NULL;
	//}
	//頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	CObject::Release();

}
void CObjectX::Update(void)
{

}
void CObjectX::Draw(void)
{
	CTexture* pTexture = CManager::GetCTexture();

	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	CRenderer* renderer = CManager::GetCRenderer();
	pDevice = renderer->GetDevice();

	//計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;
	//現在のマテリアルの保存用
	D3DMATERIAL9 matDef;//現在のマテリアルの保存用
	D3DXMATERIAL* pMat;//マテリアルデータへのポインタ
	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);
	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	pDevice->GetMaterial(&matDef);
	//マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)m_XModel.pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_XModel.dwNumMat; nCntMat++)
	{
		//マテリアルの設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		if (m_nIdxTexture[nCntMat] != -1)
		{
			//テクスチャの設定
			pDevice->SetTexture(0, pTexture->GetAddres(m_nIdxTexture[nCntMat]));
		}
		else
		{
			//テクスチャの設定
			pDevice->SetTexture(0, NULL);
		}
		//モデル（パーツ）の描画
		m_XModel.pMesh->DrawSubset(nCntMat);
	}
	pDevice->SetMaterial(&matDef);

}

void CObjectX::BindXFile(CXModel::XMODEL pXFile)
{
	m_XModel = pXFile;
}
