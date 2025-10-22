//**********************************
//
// タイトルUI処理 [titleUI.cpp]
// Author:Sasaki Soichiro
//
//**********************************

//*******************
// インクルード
//*******************
#include "resultUI.h"
#include "manager.h"
#include "texture.h"
#include "renderer.h"

//*****************
// コンストラクタ
//*****************
CResultUI::CResultUI(int nPriority) :CObject2D(nPriority)
{
	m_nIdxTexture = 0;	// インデックス
}

//*****************
// デストラクタ
//*****************
CResultUI::~CResultUI()
{
}

//*****************
// 初期化処理
//*****************
HRESULT CResultUI::Init(D3DXVECTOR3 pos)
{
	CTexture* pTexture = CManager::GetCTexture();
	CObject2D::BindTexture(pTexture->GetAddres(m_nIdxTexture));

	CObject2D::Init(pos);						// 2Dの初期化

	// UVの設定
	CObject2D::SetTex(D3DXVECTOR2(0.0f, 0.0f),
		D3DXVECTOR2(1.0f, 0.0f),
		D3DXVECTOR2(0.0f, 1.0f),
		D3DXVECTOR2(1.0f, 1.0f));
	// 大きさの設定
	CObject2D::SetSize(D3DXVECTOR2(200.0f, 80.0f));
	return S_OK;
}

//*****************
// 終了処理
//*****************
void CResultUI::Uninit(void)
{
	// 終了処理
	CObject2D::Uninit();
}

//*****************
// 更新処理
//*****************
void CResultUI::Update(void)
{

}

//*****************
// 描画処理
//*****************
void CResultUI::Draw(void)
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
CResultUI* CResultUI::Create(D3DXVECTOR3 pos)
{
	CResultUI* TitleUI;								// ライフのポインタ
	CTexture* pTexture = CManager::GetCTexture();	// テクスチャのポインタ

	int nNum = CObject::GetNumAll();// 現在のオブジェクト総数取得
	if (nNum < MAX_OBJ - 1)
	{// 最大オブジェクト数を超えていなかったら

		TitleUI = new CResultUI;// インスタンス生成
		// テクスチャ
		TitleUI->m_nIdxTexture = pTexture->Register("data\\TEXTURE\\result.png");

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
void CResultUI::SetPos(D3DXVECTOR3 pos)
{
	// 位置設定
	CObject2D::SetPos(pos);
}

//*****************
// 向き設定
//*****************
void CResultUI::SetRot(D3DXVECTOR3 rot)
{
	// 位置設定
	CObject2D::SetRot(rot);
}

//*****************
// 位置情報取得
//*****************
D3DXVECTOR3 CResultUI::GetPos(void)
{
	// 位置情報取得
	return CObject2D::GetPos();
}