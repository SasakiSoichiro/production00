//******************************************
//
// Xファイル処理 [Xmodel.cpp]
// Author:Sasaki Soichiro
//
//******************************************

//*******************
// インクルード
//*******************
#include "Xmodel.h"
#include "manager.h"

// 静的メンバ変数初期化
int CXModel::m_nNumAll = 0;

//*****************
// コンストラクタ
//*****************
CXModel::CXModel()
{
	for (int nCnt = 0; nCnt < 256; nCnt++)
	{
		m_apXModel[nCnt].dwNumMat = NULL;
		m_apXModel[nCnt].pBuffMat = NULL;
		m_apXModel[nCnt].pMesh = NULL;
	}
	m_nNumAll++;
}

//*****************
// デストラクタ
//*****************
CXModel::~CXModel()
{
}

HRESULT CXModel::Load(void)
{

	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	CRenderer* renderer = CManager::GetCRenderer();
	pDevice = renderer->GetDevice();
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		//xファイルの読み込み
		D3DXLoadMeshFromX(XFILE[nCnt],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&m_apXModel[nCnt].pBuffMat,
			NULL,
			&m_apXModel[nCnt].dwNumMat,
			&m_apXModel[nCnt].pMesh);
	}

	return S_OK;
}

void CXModel::Unload(void)
{
	// テクスチャの破棄
	for (int nCnt = 0; nCnt < 256; nCnt++)
	{
		if (m_apXModel[nCnt].pBuffMat != NULL)
		{
			m_apXModel[nCnt].pBuffMat->Release();
			m_apXModel[nCnt].pBuffMat = NULL;
		}
		if (m_apXModel[nCnt].pMesh != NULL)
		{
			m_apXModel[nCnt].pMesh->Release();
			m_apXModel[nCnt].pMesh = NULL;
		}
	}
}

int CXModel::Register(const char* pFilename)
{
	int nCntRegister;
	for (nCntRegister = 0; nCntRegister < 256; nCntRegister++)
	{
		if (XFILE[nCntRegister] == NULL)
		{
			if (m_apXModel[nCntRegister].dwNumMat==NULL
				&& m_apXModel[nCntRegister].pBuffMat == NULL
				&& m_apXModel[nCntRegister].pMesh == NULL)
			{
				// デバイスの取得
				LPDIRECT3DDEVICE9 pDevice;
				CRenderer* renderer = CManager::GetCRenderer();
				pDevice = renderer->GetDevice();
				//xファイルの読み込み
				D3DXLoadMeshFromX(pFilename,
					D3DXMESH_SYSTEMMEM,
					pDevice,
					NULL,
					&m_apXModel[nCntRegister].pBuffMat,
					NULL,
					&m_apXModel[nCntRegister].dwNumMat,
					&m_apXModel[nCntRegister].pMesh);
				XFILE[nCntRegister] = pFilename;
				return nCntRegister;
			}
			else
			{
				return -1;
			}
		}

		else if (strcmp(pFilename, XFILE[nCntRegister]) == 0)
		{
			return nCntRegister;
		}
	}
	return -1;
}

CXModel::XMODEL CXModel::GetAddres(int nIdx)
{
	return m_apXModel[nIdx];
}