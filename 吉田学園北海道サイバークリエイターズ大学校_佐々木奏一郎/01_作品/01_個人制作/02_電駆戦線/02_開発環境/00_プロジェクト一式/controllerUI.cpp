//**********************************
//
// スタンUI処理 [stanUI.cpp]
// Author:Sasaki Soichiro
//
//**********************************

//*******************
// インクルード
//*******************
#include "controllerUI.h"
#include "manager.h"
#include "game.h"
#include "player.h"
#include "renderer.h"
#include "texture.h"
#include "input.h"

//*****************
// コンストラクタ
//*****************
CControllerUI::CControllerUI(int nPriority) :CObject2D(nPriority)
{
	m_nIdxTexture = 0;	// インデックス
	m_bScreen = false;
}

//*****************
// デストラクタ
//*****************
CControllerUI::~CControllerUI()
{
}

//*****************
// 初期化処理
//*****************
HRESULT CControllerUI::Init(D3DXVECTOR3 pos)
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
	CObject2D::SetSize(D3DXVECTOR2(150.0f, 300.0f));
	m_bScreen = true;

	return S_OK;
}

//*****************
// 終了処理
//*****************
void CControllerUI::Uninit(void)
{
	CObject2D::Uninit();
}

//*****************
// 更新処理
//*****************
void CControllerUI::Update(void)
{
	// 入力取得
	CInputKeyboard* pKeyboard = CManager::GetCInputKeyboard();
	if (pKeyboard->Trigger(DIK_C))
	{
		m_bScreen = !m_bScreen;
	}

	// 表示・非表示処理
	if(m_bScreen)
	{
		// 位置と色
		SetPos(D3DXVECTOR3(100.0f, SCREEN_HEIGHT / 2, 0.0f));
		CObject2D::SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
	else
	{
		// 位置と色
		SetPos(D3DXVECTOR3(-100.0f, SCREEN_HEIGHT / 2, 0.0f));
		CObject2D::SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	}
}

//*****************
// 描画処理
//*****************
void CControllerUI::Draw(void)
{
	CObject2D::Draw();
}

//******************
// インスタンス生成
//******************
CControllerUI* CControllerUI::Create(D3DXVECTOR3 pos)
{
	// 自身のポインタ
	CControllerUI* pControllerUI;
	// テクスチャ取得
	CTexture* pTexture = CManager::GetCTexture();

	int nNum = CObject::GetNumAll();// 現在のオブジェクト総数取得
	if (nNum < MAX_OBJ - 1)
	{// 最大オブジェクト数を超えていなかったら

		// インスタンス生成
		pControllerUI = new CControllerUI;
		// テクスチャ
		pControllerUI->m_nIdxTexture = pTexture->Register("data\\TEXTURE\\controller.png");
		// 初期化
		pControllerUI->Init(pos);

		return pControllerUI;
	}

	return NULL;
}

//*****************
// 位置設定
//*****************
void CControllerUI::SetPos(D3DXVECTOR3 pos)
{
	CObject2D::SetPos(pos);
}

//*****************
// 向き設定
//*****************
void CControllerUI::SetRot(D3DXVECTOR3 rot)
{
	CObject2D::SetRot(rot);
}

//*****************
// 位置情報取得
//*****************
D3DXVECTOR3 CControllerUI::GetPos(void)
{
	return CObject2D::GetPos();
}