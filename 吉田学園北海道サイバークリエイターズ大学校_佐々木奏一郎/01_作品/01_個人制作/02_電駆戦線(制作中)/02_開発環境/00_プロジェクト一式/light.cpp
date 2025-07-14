//**********************************
//
// ライト処理 [light.cpp]
// Author:Sasaki Soichiro
//
//**********************************

//*******************
// インクルード
//*******************
#include "light.h"
#include "manager.h"

//*****************
// コンストラクタ
//*****************
CLight::CLight()
{
	for(int nCnt = 0; nCnt < MAX_LIGHT; nCnt++)
	{
		m_aLight[nCnt] = {};
		m_aVec[nCnt] = {};
	}
}

//*****************
// デストラクタ
//*****************
CLight::~CLight()
{
}

//**********
//  初期化
//**********
void CLight::Init(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	CRenderer* renderer = CManager::GetCRenderer();
	pDevice = renderer->GetDevice();

	//ライトをクリアする
	ZeroMemory(&m_aLight, sizeof(m_aLight));

	// ライト設定
	for (int nCnt = 0; nCnt < 3; nCnt++)
	{
		m_aVec[nCnt];

		//ライトの種類を設定
		m_aLight[nCnt].Type = D3DLIGHT_DIRECTIONAL;

		//ライトの拡散光を設定
		m_aLight[nCnt].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	}

	//ライトの方向を設定(個別)
	m_aVec[0] = D3DXVECTOR3(0.0f, -1.0f, -0.0f);
	m_aVec[1] = D3DXVECTOR3(0.3f, -0.8f, 0.8f);
	m_aVec[2] = D3DXVECTOR3(-0.4f, 0.8f, -0.9f);

	for (int nCnt = 0; nCnt < 3; nCnt++)
	{
		//正規化する(大きさ１のベクトルにする)
		D3DXVec3Normalize(&m_aVec[nCnt], &m_aVec[nCnt]);
		m_aLight[nCnt].Direction = m_aVec[nCnt];

		//ライトを設定する
		pDevice->SetLight(nCnt, &m_aLight[nCnt]);

		//ライトを有効にする
		pDevice->LightEnable(nCnt, TRUE);

	}
}

//************
// 終了処理
//************
void CLight::Uninit(void)
{

}

//************
// 更新処理
//************
void CLight::Update(void)
{

}