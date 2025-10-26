//***************************************
//
// 車マネージャー処理 [carManager.cpp]
// Author:Sasaki Soichiro
//
//***************************************

//*******************
// インクルード
//*******************
#include "carManager.h"
#include "carBody.h"
#include "manager.h"
#include "renderer.h"

//*******************
// コンストラクタ
//*******************
CCar::CCar()
{
	m_pCarBody=nullptr;
	m_mtxWorld={};
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//*******************
// デストラクタ
//*******************
CCar::~CCar()
{
}

CCar* CCar::Create(D3DXVECTOR3 pos)
{
	// 自身のポインタ
	CCar* pCar;

	int nNum = CObject::GetNumAll();
	if (nNum < MAX_OBJ - 1)
	{// オブジェクトが最大数に達していない場合

		// インスタンス生成
		pCar = new CCar;

		// 初期化
		pCar->Init(pos);

		return pCar;
	}

	return NULL;

}

//*************
// 初期化処理
//*************
HRESULT CCar::Init(D3DXVECTOR3 pos)
{
	m_pCarBody=CCarBody::Create(pos,"data\\MODEL\\truck.x");

	return S_OK;
}

//*************
// 終了処理
//*************
void CCar::Uninit(void)
{
	if (m_pCarBody != nullptr)
	{
		m_pCarBody->Uninit();
		delete m_pCarBody;
		m_pCarBody = nullptr;
	}

	CObject::Release();
}

//*************
// 更新処理
//*************
void CCar::Update(void)
{
	m_pCarBody->Update();
}

//*************
// 描画処理
//*************
void CCar::Draw(void)
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

	m_pCarBody->Draw();
}

