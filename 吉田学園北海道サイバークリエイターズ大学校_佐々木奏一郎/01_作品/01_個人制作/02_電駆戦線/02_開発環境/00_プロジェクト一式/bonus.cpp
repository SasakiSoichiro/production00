//**********************************
//
// ボーナス処理 [bonus.cpp]
// Author:Sasaki Soichiro
//
//**********************************

//*******************
// インクルード
//*******************
#include "bonus.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"


//*****************
// コンストラクタ
//*****************
CBonus::CBonus(int nPriority) :CObject2D(nPriority)
{
	m_nIdxTexture = 0;	// インデックス
}

//*****************
// デストラクタ
//*****************
CBonus::~CBonus()
{
}

//*****************
// 初期化処理
//*****************
HRESULT CBonus::Init(D3DXVECTOR3 pos)
{
	// テクスチャ取得
	CTexture* pTexture = CManager::GetCTexture();
	// テクスチャ割り当て
	CObject2D::BindTexture(pTexture->GetAddres(m_nIdxTexture));

	CObject2D::Init(pos);

	// UVの設定
	CObject2D::SetTex(D3DXVECTOR2(0.0f, 0.0f),
		D3DXVECTOR2(1.0f, 0.0f),
		D3DXVECTOR2(0.0f, 1.0f),
		D3DXVECTOR2(1.0f, 1.0f));

	return S_OK;
}

//*****************
// 終了処理
//*****************
void CBonus::Uninit(void)
{
	CObject2D::Uninit();
}

//*****************
// 更新処理
//*****************
void CBonus::Update(void)
{

}

//*****************
// 描画処理
//*****************
void CBonus::Draw(void)
{
	// 描画処理
	CObject2D::Draw();
}

//*****************
// 位置設定
//*****************
void CBonus::SetPos(D3DXVECTOR3 pos)
{
	CObject2D::SetPos(pos);
}

//*****************
// 向き設定
//*****************
void CBonus::SetRot(D3DXVECTOR3 rot)
{
	CObject2D::SetRot(rot);
}

//******************
// 大きさの設定
//******************
void CBonus::SetSize(D3DXVECTOR2 size)
{
	CObject2D::SetSize(size);
}

//***********************
// 使うテクスチャの設定
//***********************
void CBonus::SetTexture(const char* pFileName)
{
	CTexture* pTexture=CManager::GetCTexture();
	// テクスチャ
	m_nIdxTexture = pTexture->Register(pFileName);
}

//*****************
// 位置情報取得
//*****************
D3DXVECTOR3 CBonus::GetPos(void)
{
	// 位置情報取得
	return CObject2D::GetPos();
}
