//*********************************
//
// エフェクト処理 [effect.cpp]
// Author Sasaki Soichiro
//
//*********************************

//*******************
// インクルード
//*******************
#include "chargeEffect.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "debugproc.h"
#include "texture.h"
#include "game.h"
#include "player.h"

//****************
// コンストラクタ
//****************
CChargeEffect::CChargeEffect(int nPriority) :CEffect(nPriority)
{

}

//**************
// デストラクタ
//**************
CChargeEffect::~CChargeEffect()
{
}

//**************
// 初期化処理
//**************
HRESULT CChargeEffect::Init(D3DXVECTOR3 pos)
{
	CEffect::Init(pos);

	return S_OK;
}

//**************
// 終了処理
//**************
void CChargeEffect::Uninit(void)
{
	CEffect::Uninit();
}

//**************
// 更新処理
//**************
void CChargeEffect::Update(void)
{
	// プレイヤーとプレイヤーの位置情報取得
	CPlayer* pPlayer = CGame::GetCPlayer();
	D3DXVECTOR3 playerPos = pPlayer->GetPos();
	// 位置と向きとムーブ値情報取得
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();
	D3DXVECTOR3 move = GetMove();

	D3DXVECTOR3 moveDest;

	// 遅延をつけながらプレイヤーの位置に動かす
	playerPos.y += offsetY;
	moveDest = playerPos - pos;
	move += (moveDest - move) * dest;
	pos += move;

	// 反映
	SetPos(pos);
	SetMove(move);

	CEffect::Update();
}

//**************
// 描画処理
//**************
void CChargeEffect::Draw(void)
{
	CEffect::Draw();
}

//*******************
// インスタンス生成 
//*******************
CChargeEffect* CChargeEffect::Create(D3DXVECTOR3 pos, float fAngle, D3DXVECTOR2 size, int nLife, D3DXCOLOR col)
{
	CChargeEffect* pExplosion;
	// テクスチャ情報取得
	CTexture* pTexture = CManager::GetCTexture();
	int nNum = GetNumAll();
	if (nNum < MAX_OBJ - 1)
	{
		// インスタンス生成
		pExplosion = new CChargeEffect;
		// テクスチャ割り当て
		pExplosion->SetTexture(pTexture->Register("data\\TEXTURE\\electricity000.jpg"));
		// 初期化
		pExplosion->Init(pos);
		pExplosion->SetRot(D3DXVECTOR3(0.0f, fAngle, (float)(rand() % 314) / 100.0f));
		pExplosion->SetMove(D3DXVECTOR3(sinf(fAngle) * speed, 0.0f, cosf(fAngle) * speed));
		pExplosion->SetSize(size);
		pExplosion->SetCol(col);
		pExplosion->SetLife(nLife);

		return pExplosion;
	}
	return NULL;
}