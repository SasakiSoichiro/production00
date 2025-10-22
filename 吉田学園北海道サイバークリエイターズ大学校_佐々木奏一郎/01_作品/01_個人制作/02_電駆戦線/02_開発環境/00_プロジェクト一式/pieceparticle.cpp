//**********************************
//
// パーティクル処理 [particle.cpp]
// Author:Sasaki Soichiro
//
//**********************************

//*******************
// インクルード
//*******************
#include "pieceparticle.h"
#include "jempiece.h"
#include "manager.h"
#include <time.h>

//=================
// コンストラクタ
//=================
CPieceParticle::CPieceParticle(int nPriority) :CObject(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nAngle = 0;			// 向き
}

//=================
// デストラクタ
//=================
CPieceParticle::~CPieceParticle()
{
}

//=================
// 初期化処理
//=================
HRESULT CPieceParticle::Init(D3DXVECTOR3 pos)
{
	m_pos = pos;

	return S_OK;
}

//=================
// 終了処理
//=================
void CPieceParticle::Uninit(void)
{
	CObject::Release();
}

//=================
// 更新処理
//=================
void CPieceParticle::Update(void)
{
	for (int nCnt = 0; nCnt < 30; nCnt++)
	{
		int nAngle = rand() % 314 - (314/2);
		int nType = rand() % 3;

		float fAngle = (float)(m_nAngle + nAngle) * 0.01f;

		CJemPiece::Create(m_pos, fAngle, nType);
	}
	Uninit();
}

//=================
// 描画処理
//=================
void CPieceParticle::Draw(void)
{

}
CPieceParticle* CPieceParticle::Create(D3DXVECTOR3 pos, int nAngle)
{
	CPieceParticle* pParticle;
	int nNum = GetNumAll();
	if (nNum < MAX_OBJ - 1)
	{
		pParticle = new CPieceParticle;
		pParticle->Init(pos);
		pParticle->m_nAngle = nAngle;

		return pParticle;
	}
	return NULL;
}

void CPieceParticle::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}
void CPieceParticle::SetRot(D3DXVECTOR3 rot)
{
	
}