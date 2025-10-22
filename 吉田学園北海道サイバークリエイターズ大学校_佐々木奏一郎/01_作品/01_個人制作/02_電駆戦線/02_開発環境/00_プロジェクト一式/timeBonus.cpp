//**********************************
//
// タイムボーナス処理 [timeBonus.cpp]
// Author:Sasaki Soichiro
//
//**********************************

//*******************
// インクルード
//*******************
#include "timeBonus.h"
#include "manager.h"

int CTimeBonus::m_nTime = 0;

//*****************
// コンストラクタ
//*****************
CTimeBonus::CTimeBonus(int nPriority) :CBonus(nPriority)
{
	for (int nCnt = 0; nCnt < 5; nCnt++)
	{
		m_pNumber[nCnt]=NULL;
	}
}

//*****************
// デストラクタ
//*****************
CTimeBonus::~CTimeBonus()
{
}

//*****************
// 初期化処理
//*****************
HRESULT CTimeBonus::Init(D3DXVECTOR3 pos)
{

	CBonus::Init(pos);						// 2Dの初期化

	return S_OK;
}

//*****************
// 終了処理
//*****************
void CTimeBonus::Uninit(void)
{
	// 終了処理
	CBonus::Uninit();
}

//*****************
// 更新処理
//*****************
void CTimeBonus::Update(void)
{

}

//*****************
// 描画処理
//*****************
void CTimeBonus::Draw(void)
{
	// 描画処理
	CBonus::Draw();
}

//******************
// インスタンス生成
//******************
CTimeBonus* CTimeBonus::Create(D3DXVECTOR3 pos)
{
	CTimeBonus* pTimeBonus;							// ライフのポインタ
	CTexture* pTexture = CManager::GetCTexture();	// テクスチャのポインタ

	int nNum = CObject::GetNumAll();// 現在のオブジェクト総数取得
	if (nNum < MAX_OBJ - 1)
	{// 最大オブジェクト数を超えていなかったら

		pTimeBonus = new CTimeBonus;// インスタンス生成
		// テクスチャ
		pTimeBonus->SetTexture("data\\TEXTURE\\timeBonus.png");
		// 初期化
		pTimeBonus->Init(pos);

		// 情報を渡す
		return pTimeBonus;
	}

	// (失敗したら)NULLを返す
	return NULL;
}

//*****************
// 位置設定
//*****************
void CTimeBonus::SetPos(D3DXVECTOR3 pos)
{
	// 位置設定
	CObject2D::SetPos(pos);
}

//*****************
// 向き設定
//*****************
void CTimeBonus::SetRot(D3DXVECTOR3 rot)
{
	// 位置設定
	CObject2D::SetRot(rot);
}

//*****************
// 位置情報取得
//*****************
D3DXVECTOR3 CTimeBonus::GetPos(void)
{
	// 位置情報取得
	return CObject2D::GetPos();
}