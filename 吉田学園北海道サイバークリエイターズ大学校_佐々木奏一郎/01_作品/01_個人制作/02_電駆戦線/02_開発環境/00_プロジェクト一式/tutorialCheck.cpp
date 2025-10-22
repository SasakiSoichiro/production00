//**********************************
//
// 体力UI処理 [lifeUI.cpp]
// Author:Sasaki Soichiro
//
//**********************************

//*******************
// インクルード
//*******************
#include "tutorialcheck.h"
#include "manager.h"
#include "game.h"
#include "player.h"
#include "renderer.h"
#include "texture.h"

//************************
// 静的メンバ変数初期化
//************************
const D3DXVECTOR2 CTutorialCheck::SIZE_CHECK = D3DXVECTOR2(80.0f, 80.0f);
const D3DXVECTOR2 CTutorialCheck::SIZE_CHECKBOX = D3DXVECTOR2(500.0f, 70.0f);

//*****************
// コンストラクタ
//*****************
CTutorialCheck::CTutorialCheck(int nPriority) :CObject2D(nPriority)
{
	m_pCheckBox = NULL;
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		m_nIdxTextureCheck[nCnt] = 0;		// インデックス
	}
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		m_nIdxTextureCheckBox[nCnt] = 0;	// インデックス
	}
	m_bCheck = false;
	m_nCheckBox = 0;

}

//*****************
// デストラクタ
//*****************
CTutorialCheck::~CTutorialCheck()
{
}

//*****************
// 初期化処理
//*****************
HRESULT CTutorialCheck::Init(D3DXVECTOR3 pos)
{
	// テクスチャ情報取得とテクスチャの割り当て
	CTexture* pTexture = CManager::GetCTexture();

	// テクスチャ登録
	m_nIdxTextureCheck[0] = pTexture->Register("data\\TEXTURE\\check00.png");
	m_nIdxTextureCheck[1] = pTexture->Register("data\\TEXTURE\\check01.png");

	// チェック項目のテクスチャ登録
	m_nIdxTextureCheckBox[0] = pTexture->Register("data\\TEXTURE\\FlontBack.png");
	m_nIdxTextureCheckBox[1] = pTexture->Register("data\\TEXTURE\\RightLeft.png");
	m_nIdxTextureCheckBox[2] = pTexture->Register("data\\TEXTURE\\roll.png");
	m_nIdxTextureCheckBox[3] = pTexture->Register("data\\TEXTURE\\jump.png");
	m_nIdxTextureCheckBox[4] = pTexture->Register("data\\TEXTURE\\jumpCancel.png");
	m_nIdxTextureCheckBox[5] = pTexture->Register("data\\TEXTURE\\rail.png");
	m_nIdxTextureCheckBox[6] = pTexture->Register("data\\TEXTURE\\attack.png");
	m_nIdxTextureCheckBox[7] = pTexture->Register("data\\TEXTURE\\free.png");


	CObject2D::BindTexture(pTexture->GetAddres(m_nIdxTextureCheck[0]));
	m_pCheckBox->BindTexture(pTexture->GetAddres(m_nIdxTextureCheckBox[m_nCheckBox]));

	// 初期化
	CObject2D::Init(pos);
	D3DXVECTOR3 boxPos = D3DXVECTOR3(pos.x + boxOffset, pos.y, pos.z);
	m_pCheckBox->Init(boxPos);

	// UVの設定
	CObject2D::SetTex(D3DXVECTOR2(0.0f, 0.0f),
		D3DXVECTOR2(1.0f, 0.0f),
		D3DXVECTOR2(0.0f, 1.0f),
		D3DXVECTOR2(1.0f, 1.0f));
	m_pCheckBox->SetTex(D3DXVECTOR2(0.0f, 0.0f),
		D3DXVECTOR2(1.0f, 0.0f),
		D3DXVECTOR2(0.0f, 1.0f),
		D3DXVECTOR2(1.0f, 1.0f));

	// 大きさの設定
	CObject2D::SetSize(SIZE_CHECK);
	m_pCheckBox->SetSize(SIZE_CHECKBOX);

	return S_OK;
}

//*****************
// 終了処理
//*****************
void CTutorialCheck::Uninit(void)
{
	m_pCheckBox->Uninit();
	CObject2D::Uninit();
}

//*****************
// 更新処理
//*****************
void CTutorialCheck::Update(void)
{
	// テクスチャ情報取得とテクスチャの割り当て
	CTexture* pTexture = CManager::GetCTexture();

	if (m_bCheck==true&&m_nCnt>60)
	{
		m_nCheckBox++;
		m_bCheck = false;
		CObject2D::BindTexture(pTexture->GetAddres(m_nIdxTextureCheck[0]));
		m_pCheckBox->BindTexture(pTexture->GetAddres(m_nIdxTextureCheckBox[m_nCheckBox]));
	}
	m_nCnt++;
}

//*****************
// 描画処理
//*****************
void CTutorialCheck::Draw(void)
{
	CObject2D::Draw();
	m_pCheckBox->Draw();
}

//******************
// インスタンス生成
//******************
CTutorialCheck* CTutorialCheck::Create(D3DXVECTOR3 pos)
{
	// ライフのポインタ
	CTutorialCheck* pCheck;

	// 現在のオブジェクト総数取得
	int nNum = CObject::GetNumAll();
	if (nNum < MAX_OBJ - 1)
	{// 最大オブジェクト数を超えていなかったら

		// インスタンス生成
		pCheck = new CTutorialCheck;
		pCheck->m_pCheckBox = new CObject2D(5);
		// 初期化
		pCheck->Init(pos);

		return pCheck;
	}

	return NULL;
}

//*****************
// 位置設定
//*****************
void CTutorialCheck::SetPos(D3DXVECTOR3 pos)
{
	CObject2D::SetPos(pos);
}

//*****************
// 向き設定
//*****************
void CTutorialCheck::SetRot(D3DXVECTOR3 rot)
{
	CObject2D::SetRot(rot);
}

//*****************
// 位置情報取得
//*****************
D3DXVECTOR3 CTutorialCheck::GetPos(void)
{
	return CObject2D::GetPos();
}

void CTutorialCheck::Clear(void)
{
	// テクスチャ情報取得とテクスチャの割り当て
	CTexture* pTexture = CManager::GetCTexture();
	CObject2D::BindTexture(pTexture->GetAddres(m_nIdxTextureCheck[1]));

	m_bCheck = true;
	m_nCnt = 0;
}