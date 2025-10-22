//**********************************
//
// 体力UI処理 [lifeUI.cpp]
// Author:Sasaki Soichiro
//
//**********************************

//*******************
// インクルード
//*******************
#include "batterydown.h"
#include "manager.h"
#include "game.h"
#include "player.h"
#include "renderer.h"
#include "texture.h"

//************************
// 静的メンバ変数初期化
//************************
const D3DXVECTOR2 CBatteryDown::SIZE = D3DXVECTOR2(200.0f, 50.0f);

//*****************
// コンストラクタ
//*****************
CBatteryDown::CBatteryDown(int nPriority) :CObject2D(nPriority)
{
	m_nIdxTexture = 0;
}

//*****************
// デストラクタ
//*****************
CBatteryDown::~CBatteryDown()
{
}

//*****************
// 初期化処理
//*****************
HRESULT CBatteryDown::Init(D3DXVECTOR3 pos)
{
	// テクスチャ情報取得とテクスチャの割り当て
	CTexture* pTexture = CManager::GetCTexture();
	CObject2D::BindTexture(pTexture->GetAddres(m_nIdxTexture));

	// 初期化
	CObject2D::Init(pos);						

	// UVの設定
	CObject2D::SetTex(D3DXVECTOR2(0.0f, 0.0f),
		D3DXVECTOR2(1.0f, 0.0f),
		D3DXVECTOR2(0.0f, 1.0f),
		D3DXVECTOR2(1.0f, 1.0f));

	// 大きさの設定
	CObject2D::SetSize(SIZE);

	return S_OK;
}

//*****************
// 終了処理
//*****************
void CBatteryDown::Uninit(void)
{
	CObject2D::Uninit();
}

//*****************
// 更新処理
//*****************
void CBatteryDown::Update(void)
{
	// プレイヤーと体力の情報取得
	CPlayer* pPlayer = CGame::GetCPlayer();
	float fLife = pPlayer->GetLife();

	// 体力低下UI表示
	if (fLife < line && fLife > 0.0f)
	{// 不透明
		CObject2D::SetPos(D3DXVECTOR3(SCREEN_WIDTH / 2, 150.0f, 0.0f));

		CObject2D::SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
	else
	{// 透明
		CObject2D::SetPos(D3DXVECTOR3(SCREEN_WIDTH / 2, -150.0f, 0.0f));

		CObject2D::SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	}

}

//*****************
// 描画処理
//*****************
void CBatteryDown::Draw(void)
{
	CObject2D::Draw();
}

//******************
// インスタンス生成
//******************
CBatteryDown* CBatteryDown::Create(D3DXVECTOR3 pos)
{
	// ライフのポインタ
	CBatteryDown* BatteryDown;
	// テクスチャ情報取得
	CTexture* pTexture = CManager::GetCTexture();

	// 現在のオブジェクト総数取得
	int nNum = CObject::GetNumAll();
	if (nNum < MAX_OBJ - 1)
	{// 最大オブジェクト数を超えていなかったら

		// インスタンス生成
		BatteryDown = new CBatteryDown;
		// テクスチャ
		BatteryDown->m_nIdxTexture = pTexture->Register("data\\TEXTURE\\batteryDown.png");
		// 初期化
		BatteryDown->Init(pos);

		return BatteryDown;
	}

	return NULL;
}

//*****************
// 位置設定
//*****************
void CBatteryDown::SetPos(D3DXVECTOR3 pos)
{
	CObject2D::SetPos(pos);
}

//*****************
// 向き設定
//*****************
void CBatteryDown::SetRot(D3DXVECTOR3 rot)
{
	CObject2D::SetRot(rot);
}

//*****************
// 位置情報取得
//*****************
D3DXVECTOR3 CBatteryDown::GetPos(void)
{
	return CObject2D::GetPos();
}