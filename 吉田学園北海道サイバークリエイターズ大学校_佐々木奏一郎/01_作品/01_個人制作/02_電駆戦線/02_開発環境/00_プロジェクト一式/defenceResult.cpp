//**********************************
//
// 防衛結果表示処理 [defenceResult.cpp]
// Author:Sasaki Soichiro
//
//**********************************

//*******************
// インクルード
//*******************
#include "defenceResult.h"
#include "manager.h"
#include "game.h"
#include "timer.h"
#include "renderer.h"
#include "texture.h"
#include "player.h"


//*****************
// コンストラクタ
//*****************
CDefenceResult::CDefenceResult(int nPriority) :CObject2D(nPriority)
{
	m_nIdxTexture = 0;	// インデックス
}

//*****************
// デストラクタ
//*****************
CDefenceResult::~CDefenceResult()
{
}

//*****************
// 初期化処理
//*****************
HRESULT CDefenceResult::Init(D3DXVECTOR3 pos)
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
	// 大きさの設定
	CObject2D::SetSize(D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT));

	return S_OK;
}

//*****************
// 終了処理
//*****************
void CDefenceResult::Uninit(void)
{
	CObject2D::Uninit();
}

//*****************
// 更新処理
//*****************
void CDefenceResult::Update(void)
{

}

//*****************
// 描画処理
//*****************
void CDefenceResult::Draw(void)
{
	CObject2D::Draw();
}

//******************
// インスタンス生成
//******************
CDefenceResult* CDefenceResult::Create(D3DXVECTOR3 pos)
{
	CDefenceResult* pDefenceResult;								// ライフのポインタ

	int nNum = CObject::GetNumAll();// 現在のオブジェクト総数取得
	if (nNum < MAX_OBJ - 1)
	{// 最大オブジェクト数を超えていなかったら

		// インスタンス生成
		pDefenceResult = new CDefenceResult;
		// テクスチャ
		pDefenceResult->SetTex();
		// 初期化
		pDefenceResult->Init(pos);

		return pDefenceResult;
	}

	return NULL;
}

//*****************
// 位置設定
//*****************
void CDefenceResult::SetPos(D3DXVECTOR3 pos)
{
	CObject2D::SetPos(pos);
}

//*****************
// 向き設定
//*****************
void CDefenceResult::SetRot(D3DXVECTOR3 rot)
{
	CObject2D::SetRot(rot);
}

//*****************
// 位置情報取得
//*****************
D3DXVECTOR3 CDefenceResult::GetPos(void)
{
	return CObject2D::GetPos();
}

//******************
// テクスチャの設定
//******************
void CDefenceResult::SetTex(void)
{
	// テクスチャとプレイヤー取得
	CTexture* pTexture = CManager::GetCTexture();
	CPlayer* pPlayer = CGame::GetCPlayer();
	// 残り時間取得
	int time = CTimer::GetTime();

	if (pPlayer->GetLife() <= 0.0f || time <= 0)
	{// 負けたとき
		m_nIdxTexture = pTexture->Register("data\\TEXTURE\\gameover.png");
	}
	else
	{// 勝ったとき
		m_nIdxTexture = pTexture->Register("data\\TEXTURE\\gameclear.png");
	}
}