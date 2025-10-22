//**********************************
//
// パーティクル処理 [particle.cpp]
// Author:Sasaki Soichiro
//
//**********************************

//*******************
// インクルード
//*******************
#include "particle.h"
#include "manager.h"
#include "effect.h"
#include <time.h>

//*****************
// コンストラクタ
//*****************
CParticle::CParticle(int nPriority) :CObject(nPriority)
{
	m_pTexture = NULL;
	m_pVtxBuff = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR2(0.0f, 0.0f);
	m_col = D3DXCOLOR(0.0f,0.0f,0.0f,0.0f);
	m_fLength=0.0f;		// 移動距離
	m_nRad=0;			// 半径
	m_nAngle=0;			// 向き
	m_nLife = 0;		// 寿命
}

//****************
// デストラクタ
//****************
CParticle::~CParticle()
{
}

//***************
// 初期化処理
//***************
HRESULT CParticle::Init(D3DXVECTOR3 pos)
{
	m_pos = pos;
	m_fLength = 200.0f;	// 移動距離
	m_nRad = 10;		// 半径
	m_nAngle = 629;		// 向き
	m_nLife = 20;		// 寿命

	return S_OK;
}

//***************
// 終了処理
//***************
void CParticle::Uninit(void)
{
	CObject::Release();
}

//***************
// 更新処理
//***************
void CParticle::Update(void)
{

	for (int nCnt = 0; nCnt < 5; nCnt++)
	{
		float fAngle = (float)(rand() % m_nAngle - 314) / 100.0f;
		float fLength = (float)(rand() % m_nRad) /*/ m_fLength + 10.0f*/;
		
		D3DXVECTOR3 rot = NONE;
		D3DXVECTOR3 pos=m_pos;
		pos.x =m_pos.x+ sinf(fAngle) * fLength;
		pos.z =m_pos.z+ cosf(fAngle) * fLength;
		rot.z = (float)(rand() % m_nAngle - 314) / 100.0f;
		CEffect::Create(pos, NONE, rot, m_size,m_nLife,m_col);
		m_nAmount--;
		if (m_nAmount <= 0)
		{
			break;
		}
	}
	if (m_bLife == true)
	{
		m_nTime--;
		if (m_nTime <= 0)
		{
			Uninit();
		}
	}
}

//***************
// 描画処理
//***************
void CParticle::Draw(void)
{

}

//******************
// インスタンス生成
//******************
CParticle* CParticle::Create(D3DXVECTOR3 pos, int radius, D3DXVECTOR2 size, int nAmount, int nLife, int nTime, D3DXCOLOR col, bool bLife)
{
	CParticle* pParticle;
	int nNum = GetNumAll();
	if (nNum < MAX_OBJ - 1)
	{
		pParticle = new CParticle;
		pParticle->Init(pos);
		pParticle->SetCol(col);
		pParticle->SetRadius(radius);
		pParticle->SetSize(size);
		pParticle->SetAmount(nAmount);
		pParticle->m_nLife = nLife;
		pParticle->SetTime(nTime);
		pParticle->SetbLife(bLife);
		return pParticle;
	}
	return NULL;
}

//***************
// 位置設定
//***************
void CParticle::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//***************
// 向き設定
//***************
void CParticle::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//***************
// 色設定
//***************
void CParticle::SetCol(D3DXCOLOR col)
{
	m_col = col;
}