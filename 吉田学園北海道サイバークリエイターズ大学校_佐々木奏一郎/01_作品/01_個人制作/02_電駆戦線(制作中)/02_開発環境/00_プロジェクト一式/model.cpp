//***************************************
// 
// メッシュフィールド処理[mesh.cpp]
// Author:Sasaki Soichiro
// 
//***************************************

//******************
// インクルード
//******************
#include "model.h"
#include "manager.h"


//*****************
// コンストラクタ
//*****************
CModel::CModel()
{
	m_pos = D3DXVECTOR3{ 0.0f,0.0f,0.0f };
	m_rot = D3DXVECTOR3{ 0.0f,0.0f,0.0f };
	m_nIdxXFile = 0;
	m_pParent = NULL;
	m_mtxWorld = {};
	m_pXModel = {};
	
}

//=================
// デストラクタ
//=================
CModel::~CModel()
{
}

//=================
// 初期化処理
//=================
void CModel::Init(D3DXVECTOR3 pos)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	CRenderer* renderer = CManager::GetCRenderer();
	CXModel* pXModel = CManager::GetCXModel();
	pDevice = renderer->GetDevice();

	//xファイルの読み込み
	m_pXModel = pXModel->GetAddres(m_nIdxXFile);
	m_pos = pos;
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//=================
// 終了処理
//=================
void CModel::Uninit(void)
{
}

//=================
// 更新処理
//=================
void CModel::Update(void)
{

}

//=================
// 描画処理
//=================
void CModel::Draw(void)
{
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

	D3DXMATRIX mtxParent;// 親のマトリックス
	if (m_pParent != NULL)
	{// 親が存在する
		// 親のマトリックスを取得する
		mtxParent = m_pParent->GetMtxWorld();
	}
	else
	{// 親が存在しない
		// 現在(最新)のマトリックスを取得する[=プレイヤーのマトリックス]
		pDevice->GetTransform(D3DTS_WORLD, &mtxParent);
	}
	// 親のマトリックスと掛け合わせる
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxParent);
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);
	pDevice->GetMaterial(&matDef);
	//マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)m_pXModel.pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_pXModel.dwNumMat; nCntMat++)
	{
		//マテリアルの設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		////テクスチャの設定
		pDevice->SetTexture(0, NULL);

		//モデル（パーツ）の描画
		m_pXModel.pMesh->DrawSubset(nCntMat);
	}
	pDevice->SetMaterial(&matDef);

}

CModel* CModel::Create(D3DXVECTOR3 pos,const char*pFileName)
{
	CModel* pModel;
	CXModel* pXModel = CManager::GetCXModel();
	int nNum = CObject::GetNumAll();
	if (nNum < MAX_OBJ - 1)
	{
		pModel = new CModel;
		pModel->m_nIdxXFile = pXModel->Register(pFileName);
		pModel->Init(pos);
		return pModel;
	}
	return NULL;
}
//****************
// 親の設定
//****************
void CModel::SetParent(CModel* pModel)
{
	m_pParent = pModel;
}

//************************
// マトリックス情報の取得
//************************
D3DXMATRIX CModel::GetMtxWorld()
{
	return m_mtxWorld;
}