//*****************************************
//
// プレイヤー処理 [player.cpp]
// Author:Sasaki Soichiro
//
//*****************************************

//*******************
// インクルード
//*******************
#include "enemyState.h"
#include "enemy.h"
#include "manager.h"
#include "game.h"
#include "particle.h"
#include "slow.h"
#include "smokeParticle.h"
#include "sound.h"
#include "player.h"

//******************
// コンストラクタ
//******************
CEnemyStateBase::CEnemyStateBase()
{
	m_pEnemy = NULL;
}

//******************
// デストラクタ
//******************
CEnemyStateBase::~CEnemyStateBase()
{

}

//************************
// エネミーのポインタ設定
//************************
void CEnemyStateBase::SetOwner(CEnemy* pEnemy)
{
	m_pEnemy = pEnemy;
}

//******************
// コンストラクタ
//******************
CNuetoralState::CNuetoralState()
{

}

//******************
// デストラクタ
//******************
CNuetoralState::~CNuetoralState()
{

}

//**************
// 初期化
//**************
void CNuetoralState::Init(void)
{
	// ニュートラルモーション
	m_pEnemy->SetMotion(0);
}

//***************
// 更新処理
//***************
void CNuetoralState::Update(void)
{
	// プレイヤーが近くに来たら追いかける
	if (m_pEnemy->Chase()==true)
	{
		// 状態変更
		CChaseState* pChaseState = new CChaseState;
		m_pEnemy->ChangeState(pChaseState);
	}
}

//*************
// 終了処理
//*************
void CNuetoralState::Uninit(void)
{

}

//*****************
// コンストラクタ
//*****************
CChaseState::CChaseState()
{

}

//*****************
// デストラクタ
//*****************
CChaseState::~CChaseState()
{

}

//*************
// 初期化処理
//*************
void CChaseState::Init(void)
{
	
}

//*************
// 更新処理
//*************
void CChaseState::Update(void)
{
	// 追いかけるモーション
	m_pEnemy->SetMotion(CEnemy::MOTION_MOVE);
	// プレイヤーの位置取得
	CPlayer*pPlayer=CGame::GetCPlayer();
	D3DXVECTOR3 playerPos = pPlayer->GetPos();
	// スロー取得
	CSlow* pSlow = CGame::GetCSlow();
	// 位置と向き取得
	D3DXVECTOR3 pos = m_pEnemy->GetPos();
	D3DXVECTOR3 rot = m_pEnemy->GetRot();

	// プレイヤーを追いかける
	float DistanceX = pos.x - playerPos.x;
	float DistanceZ = pos.z - playerPos.z;
	float fAngle = atan2f(DistanceX, DistanceZ);
	float fSpeed = m_pEnemy->GetSpeed() * pSlow->GetfDivi();
	pos.x += -sinf(fAngle) * fSpeed;
	pos.z += -cosf(fAngle) * fSpeed;

	// 正規化
	if (fAngle - rot.y > D3DX_PI)
	{
		rot.y = rot.y + (D3DX_PI * 2);
	}
	else if (rot.y - fAngle > D3DX_PI)
	{
		rot.y = rot.y - (D3DX_PI * 2);
	}

	// ゆっくり向きを変える
	rot.y += (fAngle - rot.y) * 0.1f;
	// 反映
	m_pEnemy->SetPos(pos);
	m_pEnemy->SetRot(rot);

	// 状態変更処理
	if (m_pEnemy->Attack() == true)
	{// 攻撃条件がtrue
		CAttackState* pAttackState = new CAttackState;
		m_pEnemy->ChangeState(pAttackState);
	}
	else if (m_pEnemy->Nuetoral() == true)
	{// 待機条件がtrue
		CNuetoralState* pNuetoralState = new CNuetoralState;
		m_pEnemy->ChangeState(pNuetoralState);
	}
	else if (m_pEnemy->Hit() == true)
	{// HIT条件がtrue
		CHitState* pHitState = new CHitState;
		m_pEnemy->ChangeState(pHitState);
	}

}

//*************
// 終了処理
//*************
void CChaseState::Uninit(void)
{

}

//****************
// コンストラクタ
//****************
CAttackState::CAttackState()
{

}

//****************
// デストラクタ
//****************
CAttackState::~CAttackState()
{

}

//*************
// 初期化処理
//*************
void CAttackState::Init(void)
{
	// 攻撃モーション
	m_pEnemy->SetMotion(2);
}

//*************
// 更新処理
//*************
void CAttackState::Update(void)
{
	// 攻撃処理更新
	if (m_pEnemy->AttackUpdate() == true)
	{// 攻撃更新が終わったら

		// 状態変更処理
		if (m_pEnemy->Chase() == true)
		{// 追いかける条件がtrue
			CChaseState* pChaseState = new CChaseState;
			m_pEnemy->ChangeState(pChaseState);
		}
		else if (m_pEnemy->Nuetoral() == true)
		{// 待機条件がtrue
			CNuetoralState* pNuetoralState = new CNuetoralState;
			m_pEnemy->ChangeState(pNuetoralState);
		}
	}
	else if (m_pEnemy->Hit() == true)
	{// HIT条件がtrue
		CHitState* pHitState = new CHitState;
		m_pEnemy->ChangeState(pHitState);
	}
}

//*************
// 終了処理
//*************
void CAttackState::Uninit(void)
{
	
}

//*****************
// コンストラクタ
//*****************
CHitState::CHitState()
{

}

//*****************
// デストラクタ
//*****************
CHitState::~CHitState()
{

}

//*****************
// 初期化処理
//*****************
void CHitState::Init(void)
{
	// サウンド取得
	CSound* pSound = CManager::GetCSound();
	// HITサウンドを再生
	pSound->Play(CSound::LABEL_SE02);
	// 煙パーティクル生成
	CSmokeParticle::Create(m_pEnemy->GetPos(), 20, D3DXVECTOR2(25.0f, 25.0f), 5, 20, 20, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
}

//*****************
// 更新処理
//*****************
void CHitState::Update(void)
{
	// プレイヤーとサウンド取得
	CPlayer* pPlayer = CGame::GetCPlayer();
	CSound* pSound = CManager::GetCSound();

	// 体力取得
	int nLife = m_pEnemy->GetLife();
	// 攻撃力取得
	nLife-=pPlayer->GetATK();
	if (nLife <= 0)
	{// 体力が0以下になったら
		// サウンド再生
		pSound->Stop(CSound::LABEL_SE05);
		// 反映
		m_pEnemy->SetLife(nLife);
		// 状態変更
		CDownState* pDownState = new CDownState;
		m_pEnemy->ChangeState(pDownState);
		return;
	}
	else
	{// 体力がまだあったら
		// 反映
		m_pEnemy->SetLife(nLife);
		// 状態変更
		CNuetoralState* pNuetoralState = new CNuetoralState;
		m_pEnemy->ChangeState(pNuetoralState);
		return;
	}
}

//*****************
// 終了処理
//*****************
void CHitState::Uninit(void)
{

}

//********************
// コンストラクタ
//********************
CDownState::CDownState()
{

}
//********************
// デストラクタ
//********************
CDownState::~CDownState()
{

}

//*************
// 初期化処理
//*************
void CDownState::Init(void)
{
	// サウンド取得
	CSound* pSound = CManager::GetCSound();
	// サウンド再生
	pSound->Play(CSound::LABEL_SE02);
	// 煙パーティクル生成
	CSmokeParticle::Create(m_pEnemy->GetPos(), 20, D3DXVECTOR2(25.0f, 25.0f), 5, 20, 20, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
}

//*************
// 更新処理
//*************
void CDownState::Update(void)
{
	// 死ぬモーション
	m_pEnemy->SetMotion(CEnemy::MOTION_DIE);
}

//*************
// 終了処理
//*************
void CDownState::Uninit(void)
{

}