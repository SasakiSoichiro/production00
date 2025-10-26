//**********************************
//
// 体力UI処理 [lifeUI.cpp]
// Author:Sasaki Soichiro
//
//**********************************

//*******************
// インクルード
//*******************
#include "numbermulti.h"
#include "manager.h"
#include "texture.h"

//*****************
// コンストラクタ
//*****************
CNumberMulti::CNumberMulti(int nPriority) :CObject2DMulti(nPriority)
{
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		m_nIdxTexture[nCnt]=0;	// インデックス
	}
	m_nNum=0;
}

//*****************
// デストラクタ
//*****************
CNumberMulti::~CNumberMulti()
{
}

//*****************
// 初期化処理
//*****************
HRESULT CNumberMulti::Init(D3DXVECTOR3 pos)
{
	CTexture* pTexture = CManager::GetCTexture();	// テクスチャのポインタ取得
	CObject2DMulti::Init(pos);						// 2Dの初期化
	// テクスチャを割り当てる
	CObject2DMulti::BindTexture(pTexture->GetAddres(m_nIdxTexture[0]), pTexture->GetAddres(m_nIdxTexture[1]));

	// UVの設定
	CObject2DMulti::SetTex(D3DXVECTOR2(0.0f, 0.0f),
		D3DXVECTOR2(1.0f, 0.0f),
		D3DXVECTOR2(0.0f, 1.0f),
		D3DXVECTOR2(1.0f, 1.0f));
	// テクスチャの緑部分が移るように設定
	CObject2DMulti::SetTex2(D3DXVECTOR2(0.0f, 0.0f),
		D3DXVECTOR2(0.5f, 0.0f),
		D3DXVECTOR2(0.0f, 1.0f),
		D3DXVECTOR2(0.5f, 1.0f));

	// 大きさの設定
	CObject2DMulti::SetSize(D3DXVECTOR2(120.0f, 150.0f));
	SetNumber(m_nNum);
	SetGauge(50);

	return S_OK;
}

//*****************
// 終了処理
//*****************
void CNumberMulti::Uninit(void)
{
	// 終了処理
	CObject2DMulti::Uninit();
}

//*****************
// 更新処理
//*****************
void CNumberMulti::Update(void)
{

}

//*****************
// 描画処理
//*****************
void CNumberMulti::Draw(void)
{
	// 描画処理
	CObject2DMulti::Draw();
}

//******************
// インスタンス生成
//******************
CNumberMulti* CNumberMulti::Create(D3DXVECTOR3 pos)
{
	CNumberMulti* pLifeUI;								// ライフのポインタ
	CTexture* pTexture = CManager::GetCTexture();	// テクスチャのポインタ

	int nNum = CObject::GetNumAll();// 現在のオブジェクト総数取得
	if (nNum < MAX_OBJ - 1)
	{// 最大オブジェクト数を超えていなかったら

		pLifeUI = new CNumberMulti;// インスタンス生成
		// マルチテクスチャ1枚目(電池の画像)
		pLifeUI->m_nIdxTexture[0] = pTexture->Register("data\\TEXTURE\\number005.png");
		// マルチテクスチャ2枚目(緑・白の二色の画像)
		pLifeUI->m_nIdxTexture[1] = pTexture->Register("data\\TEXTURE\\orange.jpg");

		// 初期化
		pLifeUI->Init(pos);

		// 情報を渡す
		return pLifeUI;
	}

	// (失敗したら)NULLを返す
	return NULL;
}

//*****************
// 位置設定
//*****************
void CNumberMulti::SetPos(D3DXVECTOR3 pos)
{
	// 位置設定
	CObject2DMulti::SetPos(pos);
}

//*****************
// 向き設定
//*****************
void CNumberMulti::SetRot(D3DXVECTOR3 rot)
{
	// 位置設定
	CObject2DMulti::SetRot(rot);
}
void CNumberMulti::SetCol(D3DXCOLOR col)
{
	CObject2DMulti::SetCol(col);
}
//*****************
// 位置情報取得
//*****************
D3DXVECTOR3 CNumberMulti::GetPos(void)
{
	// 位置情報取得
	return CObject2DMulti::GetPos();
}

void CNumberMulti::SetNumber(int nNum)
{
	float fData = 0.1f;

	// UVの設定
	CObject2DMulti::SetTex(D3DXVECTOR2(nNum * fData, 0.0f),
		D3DXVECTOR2(fData + nNum * fData, 0.0f),
		D3DXVECTOR2(nNum * fData, 1.0f),
		D3DXVECTOR2(fData + nNum * fData, 1.0f));
}
void CNumberMulti::SetGauge(int nGauge)
{
	float p = (float)nGauge / 100;		// 1から100の値に直す

	if (nGauge >= 0.0f && nGauge <= 100.0f)
	{
		// UV座標(割合に応じて色が変わるように計算)
		CObject2DMulti::SetTex2(D3DXVECTOR2(0.0f, p * 0.5f),
			D3DXVECTOR2(1.0f, p * 0.5f),
			D3DXVECTOR2(0.0f, 0.5f + p * 0.5f),
			D3DXVECTOR2(1.0f, 0.5f + p * 0.5f));
	}
}