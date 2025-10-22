//**********************************
//
// 体力UI処理 [lifeUI.cpp]
// Author:Sasaki Soichiro
//
//**********************************

//*******************
// インクルード
//*******************
#include "adjustUI.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"

//*****************
// コンストラクタ
//*****************
CAdjustUI::CAdjustUI(int nPriority) :CObject2DMulti(nPriority)
{
	// テクスチャ枚数分
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		m_nIdxTexture[nCnt] = 0;	
	}
	m_size = D3DXVECTOR2(0.0f, 0.0f);	
	m_fLife = 0.0f;					
}

//*****************
// デストラクタ
//*****************
CAdjustUI::~CAdjustUI()
{
}

//*****************
// 初期化処理
//*****************
HRESULT CAdjustUI::Init(D3DXVECTOR3 pos)
{
	// テクスチャ情報取得
	CTexture* pTexture = CManager::GetCTexture();	

	// 2Dの初期化
	CObject2DMulti::Init(pos);						

	// テクスチャを割り当てる
	CObject2DMulti::BindTexture(pTexture->GetAddres(m_nIdxTexture[TYPE_SHAPE]),
								pTexture->GetAddres(m_nIdxTexture[TYPE_COLOR]));

	// UVの設定
	CObject2DMulti::SetTex(D3DXVECTOR2(0.0f, 0.0f),
		D3DXVECTOR2(1.0f, 0.0f),
		D3DXVECTOR2(0.0f, 1.0f),
		D3DXVECTOR2(1.0f, 1.0f));

	// テクスチャの緑部分が移るように設定
	CObject2DMulti::SetTex2(D3DXVECTOR2(0.0f, 0.0f),
		D3DXVECTOR2(texOffset, 0.0f),
		D3DXVECTOR2(0.0f, 1.0f),
		D3DXVECTOR2(texOffset, 1.0f));

	// 大きさの設定
	CObject2DMulti::SetSize(D3DXVECTOR2(150.0f, 500.0f));

	return S_OK;
}

//*****************
// 終了処理
//*****************
void CAdjustUI::Uninit(void)
{
	CObject2DMulti::Uninit();
}

//*****************
// 更新処理
//*****************
void CAdjustUI::Update(void)
{
	// 割合を計算
	float fLife = maxLife - m_fLife;
	float p = fLife / maxLife;

	// テクスチャ座標を反映
	if (m_fLife >= 0.0f && m_fLife <= maxLife)
	{
		// UV座標(割合に応じて色が変わるように計算)
		CObject2DMulti::SetTex2(D3DXVECTOR2(0.0f,p * texOffset),
								D3DXVECTOR2(1.0f, p * texOffset),
								D3DXVECTOR2(0.0f, texOffset + p * texOffset),
								D3DXVECTOR2(1.0f, texOffset + p * texOffset));
	}

	// 寿命で終了
	if (m_fLife <= 0.0f)
	{
		Uninit();
	}
}

//*****************
// 描画処理
//*****************
void CAdjustUI::Draw(void)
{
	CObject2DMulti::Draw();
}

//******************
// インスタンス生成
//******************
CAdjustUI* CAdjustUI::Create(D3DXVECTOR3 pos)
{
	CAdjustUI* pAdjustUI;							// のポインタ
	CTexture* pTexture = CManager::GetCTexture();	// テクスチャのポインタ

	int nNum = CObject::GetNumAll();// 現在のオブジェクト総数取得
	if (nNum < MAX_OBJ - 1)
	{// 最大オブジェクト数を超えていなかったら

		pAdjustUI = new CAdjustUI;// インスタンス生成
		// マルチテクスチャ1枚目(電池の画像)
		pAdjustUI->m_nIdxTexture[TYPE_SHAPE] = pTexture->Register("data\\TEXTURE\\adjust.png");
		// マルチテクスチャ2枚目(緑・白の二色の画像)
		pAdjustUI->m_nIdxTexture[TYPE_COLOR] = pTexture->Register("data\\TEXTURE\\purple.png");

		// 初期化
		pAdjustUI->Init(pos);

		return pAdjustUI;
	}

	return NULL;
}

//*****************
// 位置設定
//*****************
void CAdjustUI::SetPos(D3DXVECTOR3 pos)
{
	CObject2DMulti::SetPos(pos);
}

//*****************
// 向き設定
//*****************
void CAdjustUI::SetRot(D3DXVECTOR3 rot)
{
	CObject2DMulti::SetRot(rot);
}

//*****************
// 位置情報取得
//*****************
D3DXVECTOR3 CAdjustUI::GetPos(void)
{
	return CObject2DMulti::GetPos();
}