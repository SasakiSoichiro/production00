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

//=================
// コンストラクタ
//=================
CParticle::CParticle(int nPriority) :CObject(nPriority)
{
	m_pTexture = NULL;
	m_pVtxBuff = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR2(0.0f, 0.0f);
	m_col = D3DXCOLOR(0.0f,0.0f,0.0f,0.0f);
	m_fLength=0.0f;		// 移動距離
	m_fRad=0.0f;		// 半径
	m_nAngle=0;			// 向き
	m_nLife = 0;		// 寿命
}

//=================
// デストラクタ
//=================
CParticle::~CParticle()
{
}

//=================
// 初期化処理
//=================
HRESULT CParticle::Init(D3DXVECTOR3 pos)
{
	m_pos = pos;
	m_fLength = 20.0f;	// 移動距離
	m_fRad = 10.0f;		// 半径
	m_nAngle = 629;		// 向き
	m_nLife = 20;		// 寿命

	return S_OK;
}

//=================
// 終了処理
//=================
void CParticle::Uninit(void)
{
	CObject::Release();
}

//=================
// 更新処理
//=================
void CParticle::Update(void)
{
	for (int nCnt = 0; nCnt < 128; nCnt++)
	{
		for (int nCnt = 0; nCnt < 2; nCnt++)
		{
			float fAngle = (float)(rand() % m_nAngle - 314) / 100.0f;
			float fLength = (float)(rand() % 10) / m_fLength + 10.0f;
			D3DXVECTOR3 move;
			move.x = sinf(fAngle) * fLength;
			move.y = cosf(fAngle) * fLength;
			m_nLife--;

		}
		if (m_nLife <= 0)
		{
			Uninit();
			break;
		}

	}
}

//=================
// 描画処理
//=================
void CParticle::Draw(void)
{

}
CParticle* CParticle::Create(D3DXVECTOR3 pos,D3DXCOLOR col)
{
	CParticle* pParticle;
	int nNum = GetNumAll();
	if (nNum < MAX_OBJ - 1)
	{
		pParticle = new CParticle;
		pParticle->Init(pos);
		pParticle->SetCol(col);
		return pParticle;
	}
	return NULL;
}

void CParticle::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}
void CParticle::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}
void CParticle::SetCol(D3DXCOLOR col)
{
	m_col = col;
}