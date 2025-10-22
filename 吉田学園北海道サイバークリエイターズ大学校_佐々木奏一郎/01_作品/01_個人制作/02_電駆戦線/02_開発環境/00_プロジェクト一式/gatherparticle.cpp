//************************************************
//
// 集まるパーティクル処理 [gatherParticle.cpp]
// Author:Sasaki Soichiro
//
//************************************************

//*******************
// インクルード
//*******************
#include "gatherparticle.h"
#include "manager.h"
#include "effect.h"
#include <time.h>
#include "gatherEffect.h"

//*****************
// コンストラクタ
//*****************
CGatherParticle::CGatherParticle(int nPriority) :CObject(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR2(0.0f, 0.0f);
	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	m_fLength = 0.0f;	// 移動距離
	m_nRad = 0;			// 半径
	m_nAngle = 0;		// 向き
	m_nLife = 0;		// 寿命
	m_nAmount = 0;		// 量
	m_nTime = 0;		// 時間
}

//*****************
// デストラクタ
//*****************
CGatherParticle::~CGatherParticle()
{
}

//*****************
// 初期化処理
//*****************
HRESULT CGatherParticle::Init(D3DXVECTOR3 pos)
{
	m_pos = pos;
	m_fLength = 200.0f;	// 移動距離
	m_nRad = 10;		// 半径
	m_nAngle = 629;		// 向き
	m_nLife = 20;		// 寿命

	return S_OK;
}

//*****************
// 終了処理
//*****************
void CGatherParticle::Uninit(void)
{
	CObject::Release();
}

//*****************
// 更新処理
//*****************
void CGatherParticle::Update(void)
{

	for (int nCnt = 0; nCnt < 5; nCnt++)
	{
		// 生成した周辺にランダムで生成
		m_pos.x = m_pos.x + (float)(rand() % 50 - 25);
		m_pos.y = m_pos.y +20.0f+ (float)(rand() % 50 - 25);
		m_pos.z = m_pos.z + (float)(rand() % 50 - 25);

		// エフェクト生成
		CGatherEffect::Create(m_pos, m_size, m_nLife, m_col);
		// カウントを減らす
		m_nAmount--;
		if (m_nAmount <= 0)
		{
			break;
		}
	}

	// 時間で終了
	m_nTime--;
	if (m_nTime <= 0)
	{
		Uninit();
	}
}

//*****************
// 描画処理
//*****************
void CGatherParticle::Draw(void)
{

}

//*******************
// インスタンス生成
//*******************
CGatherParticle* CGatherParticle::Create(D3DXVECTOR3 pos, int radius, D3DXVECTOR2 size, int nAmount, int nLife, int nTime, D3DXCOLOR col)
{
	// 自身のポインタ
	CGatherParticle* pParticle;
	int nNum = GetNumAll();
	if (nNum < MAX_OBJ - 1)
	{
		// インスタンス生成
		pParticle = new CGatherParticle;
		// 初期化
		pParticle->Init(pos);
		pParticle->SetCol(col);
		pParticle->SetRadius(radius);
		pParticle->SetSize(size);
		pParticle->SetAmount(nAmount);
		pParticle->m_nLife = nLife;
		pParticle->SetTime(nTime);

		return pParticle;
	}

	return NULL;
}

//*****************
// 位置設定
//*****************
void CGatherParticle::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//*****************
// 向き設定
//*****************
void CGatherParticle::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//*****************
// 色設定
//*****************
void CGatherParticle::SetCol(D3DXCOLOR col)
{
	m_col = col;
}