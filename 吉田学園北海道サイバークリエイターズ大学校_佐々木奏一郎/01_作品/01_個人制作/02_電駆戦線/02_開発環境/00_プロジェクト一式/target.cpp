//**********************************
//
// タイトルUI処理 [titleUI.cpp]
// Author:Sasaki Soichiro
//
//**********************************

//*******************
// インクルード
//*******************
#include "target.h"
#include "manager.h"
#include "texture.h"
#include "renderer.h"

//*****************
// コンストラクタ
//*****************
CTarget::CTarget(int nPriority) :CObject2D(nPriority)
{
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		m_nIdxTexture[nCnt] = 0;	// インデックス
	}
	m_nType = 0;
}

//*****************
// デストラクタ
//*****************
CTarget::~CTarget()
{
}

//*****************
// 初期化処理
//*****************
HRESULT CTarget::Init(D3DXVECTOR3 pos)
{
	CTexture* pTexture = CManager::GetCTexture();
	CObject2D::BindTexture(pTexture->GetAddres(m_nIdxTexture[m_nType]));

	CObject2D::Init(pos);						// 2Dの初期化

	// UVの設定
	CObject2D::SetTex(D3DXVECTOR2(0.0f, 0.0f),
		D3DXVECTOR2(1.0f, 0.0f),
		D3DXVECTOR2(0.0f, 1.0f),
		D3DXVECTOR2(1.0f, 1.0f));
	// 大きさの設定
	CObject2D::SetSize(D3DXVECTOR2(500.0f, 40.0f));
	return S_OK;
}

//*****************
// 終了処理
//*****************
void CTarget::Uninit(void)
{
	// 終了処理
	CObject2D::Uninit();
}

//*****************
// 更新処理
//*****************
void CTarget::Update(void)
{
	CTexture* pTexture = CManager::GetCTexture();

	if (m_nCnt > cool)
	{
		switch (m_nType)
		{
		case 0:
			m_nType++;
			CObject2D::BindTexture(pTexture->GetAddres(m_nIdxTexture[m_nType]));
			m_nCnt = 0;
			break;
		case 1:
			m_nType++;
			CObject2D::BindTexture(pTexture->GetAddres(m_nIdxTexture[m_nType]));
			m_nCnt = 0;
			break;

			break;
		case 2:
			CObject2D::SetCol(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
			CObject2D::SetPos(D3DXVECTOR3(SCREEN_WIDTH / 2, -200.0f, 0.0f));
			break;
		}
	}
	m_nCnt++;
}

//*****************
// 描画処理
//*****************
void CTarget::Draw(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	CRenderer* renderer = CManager::GetCRenderer();
	pDevice = renderer->GetDevice();

	// 描画処理
	CObject2D::Draw();
}

//******************
// インスタンス生成
//******************
CTarget* CTarget::Create(D3DXVECTOR3 pos)
{
	CTarget* TitleUI;								// ライフのポインタ
	CTexture* pTexture = CManager::GetCTexture();	// テクスチャのポインタ

	int nNum = CObject::GetNumAll();// 現在のオブジェクト総数取得
	if (nNum < MAX_OBJ - 1)
	{// 最大オブジェクト数を超えていなかったら

		TitleUI = new CTarget;// インスタンス生成
		// テクスチャ
		TitleUI->m_nIdxTexture[0] = pTexture->Register("data\\TEXTURE\\tutorial0.png");
		TitleUI->m_nIdxTexture[1] = pTexture->Register("data\\TEXTURE\\tutorial1.png");
		TitleUI->m_nIdxTexture[2] = pTexture->Register("data\\TEXTURE\\tutorial2.png");

		// 初期化
		TitleUI->Init(pos);

		// 情報を渡す
		return TitleUI;
	}

	// (失敗したら)NULLを返す
	return NULL;
}

//*****************
// 位置設定
//*****************
void CTarget::SetPos(D3DXVECTOR3 pos)
{
	// 位置設定
	CObject2D::SetPos(pos);
}

//*****************
// 向き設定
//*****************
void CTarget::SetRot(D3DXVECTOR3 rot)
{
	// 位置設定
	CObject2D::SetRot(rot);
}

//*****************
// 位置情報取得
//*****************
D3DXVECTOR3 CTarget::GetPos(void)
{
	// 位置情報取得
	return CObject2D::GetPos();
}