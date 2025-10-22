//**********************************
//
// スタンUI処理 [stanUI.cpp]
// Author:Sasaki Soichiro
//
//**********************************

//*******************
// インクルード
//*******************
#include "stanUI.h"
#include "manager.h"
#include "game.h"
#include "player.h"
#include "renderer.h"
#include "texture.h"

//*****************
// コンストラクタ
//*****************
CStanUI::CStanUI(int nPriority) :CObject2D(nPriority)
{
	m_nIdxTexture = 0;	// インデックス
}

//*****************
// デストラクタ
//*****************
CStanUI::~CStanUI()
{
}

//*****************
// 初期化処理
//*****************
HRESULT CStanUI::Init(D3DXVECTOR3 pos)
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
	CObject2D::SetSize(D3DXVECTOR2(250.0f, 80.0f));
	return S_OK;
}

//*****************
// 終了処理
//*****************
void CStanUI::Uninit(void)
{
	// 終了処理
	CObject2D::Uninit();
}

//*****************
// 更新処理
//*****************
void CStanUI::Update(void)
{
	CPlayer* pPlayer = CGame::GetCPlayer();
	int nStan=pPlayer->GetStan();
	if (nStan > 0)
	{
		// 位置の設定
		SetPos(D3DXVECTOR3(SCREEN_WIDTH / 2, 150.0f, 0.0f));

		// 色の設定
		CObject2D::SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
	else
	{
		// 位置の設定
		SetPos(D3DXVECTOR3(SCREEN_WIDTH / 2, -150.0f, 0.0f));

		// 色の設定
		CObject2D::SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	}
}

//*****************
// 描画処理
//*****************
void CStanUI::Draw(void)
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
CStanUI* CStanUI::Create(D3DXVECTOR3 pos)
{
	CStanUI* TitleUI;								// ライフのポインタ
	CTexture* pTexture = CManager::GetCTexture();	// テクスチャのポインタ

	int nNum = CObject::GetNumAll();// 現在のオブジェクト総数取得
	if (nNum < MAX_OBJ - 1)
	{// 最大オブジェクト数を超えていなかったら

		TitleUI = new CStanUI;// インスタンス生成
		// テクスチャ
		TitleUI->m_nIdxTexture = pTexture->Register("data\\TEXTURE\\stan.png");

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
void CStanUI::SetPos(D3DXVECTOR3 pos)
{
	// 位置設定
	CObject2D::SetPos(pos);
}

//*****************
// 向き設定
//*****************
void CStanUI::SetRot(D3DXVECTOR3 rot)
{
	// 位置設定
	CObject2D::SetRot(rot);
}

//*****************
// 位置情報取得
//*****************
D3DXVECTOR3 CStanUI::GetPos(void)
{
	// 位置情報取得
	return CObject2D::GetPos();
}