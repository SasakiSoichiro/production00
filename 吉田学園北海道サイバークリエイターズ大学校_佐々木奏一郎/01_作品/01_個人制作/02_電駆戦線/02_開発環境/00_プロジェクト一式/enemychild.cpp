//*****************************************
//
// エネミー処理 [enemychild.cpp]
// Author:Sasaki Soichiro
//
//*****************************************

//*******************
// インクルード
//*******************
#include "enemychild.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "texture.h"
#include "camera.h"
#include "object3D.h"
#include "player.h"
#include "game.h"
#include "particle.h"
#include "score.h"
#include "combo.h"
#include "slow.h"
#include "blurManager.h"
#include "sound.h"
#include "motion.h"

//****************
// コンストラクタ
//****************
CSpiderEnemy::CSpiderEnemy()
{
	m_fAttackFps = 0;
	m_bAttackSound = false;
	m_bAngle = false;
	m_nHitCool = 0;
}

//****************
// デストラクタ
//****************
CSpiderEnemy::~CSpiderEnemy()
{

}

//****************
// 初期化処理
//****************
HRESULT CSpiderEnemy::Init(D3DXVECTOR3 pos)
{
	CEnemy::LoadMotion("data\\MOTION\\spider.txt");
	CEnemy::Init(pos);
	CEnemy::SetSpeed(SPEED);
	
	return S_OK;
}

//****************
// 終了処理
//****************
void CSpiderEnemy::Uninit(void)
{
	CEnemy::Uninit();
}

//****************
// 更新処理
//****************
void CSpiderEnemy::Update(void)
{
	CEnemy::Update();
}

//****************
// 描画処理
//****************
void CSpiderEnemy::Draw(void)
{
	CEnemy::Draw();
}

//****************
// 追いかける条件
//****************
bool CSpiderEnemy::Chase(void)
{
	return CEnemy::Distance(200.0f);
}

//****************
// 攻撃する条件
//****************
bool CSpiderEnemy::Attack(void)
{
	return CEnemy::Distance(70.0f);
}

//****************
// 止まる条件
//****************
bool CSpiderEnemy::Nuetoral(void)
{
	return !CEnemy::Distance(200.0f);
}

//****************
// やられる条件
//****************
bool CSpiderEnemy::Hit(void)
{
	// プレイヤーの位置取得
	CPlayer* pPlayer = CGame::GetCPlayer();
	D3DXVECTOR3 playerPos = pPlayer->GetPos();
	// サウンド取得
	CSound* pSound = CManager::GetCSound();
	// 位置取得
	D3DXVECTOR3 pos = GetPos();

	// 当たり判定計算
	float DistX, DistY, DistZ;
	// 今の距離
	DistX = playerPos.x - pos.x;
	DistY = playerPos.y - pos.y;
	DistZ = playerPos.z - pos.z;
	float Dist = sqrtf((DistX * DistX) + (DistY * DistY) + (DistZ * DistZ));

	m_nHitCool++;
	// ヒットの条件
	bool bHit = Dist < Range
		&& pPlayer->GetState() != CPlayer::STATE_RAIL
		&&m_nHitCool>hitCool;

	if (bHit)
	{// ヒットしたら

		if (pPlayer->GetState() == CPlayer::STATE_NONE)
		{
			pPlayer->SetMove(D3DXVECTOR3(DistX * 0.05f, 0.0f, DistZ * 0.05f));
			// プレイヤーの状態を変更
			pPlayer->SetState(CPlayer::STATE_INOPERABLE);
			CInoperableState* pInoperableState = new CInoperableState;
			pPlayer->ChangeState(pInoperableState);

		}

		m_nHitCool = 0;
		return true;
	}
	return false;
}

//******************
// 攻撃の更新
//******************
bool CSpiderEnemy::AttackUpdate(void)
{
	m_fAttackFps++;
	// プレイヤー取得
	CPlayer* pPlayer = CGame::GetCPlayer();
	D3DXVECTOR3 playerPos = pPlayer->GetPos();
	float fLife = pPlayer->GetLife();

	// サウンドとスロー取得
	CSound* pSound = CManager::GetCSound();
	CSlow* pSlow = CGame::GetCSlow();

	// 位置情報取得
	D3DXVECTOR3 pos = CEnemy::GetPos();
	// 距離計算
	float fDistance = 80.0f;
	float radX = playerPos.x - pos.x;
	float radY = playerPos.y - pos.y;
	float radZ = playerPos.z - pos.z;
	float fRadius = sqrtf((radX * radX) + (radY * radY) + (radZ * radZ));

	// パリィ受付時間
	bool bParryTime = m_fAttackFps > 20*pSlow->GetnMulti() && m_fAttackFps <= 40 * pSlow->GetnMulti();	
	// 放電時間
	bool bDisChargeTime = m_fAttackFps > 70 * pSlow->GetnMulti() && m_fAttackFps < 180 * pSlow->GetnMulti();
	bool bParry = false;
	if (bParryTime == true)
	{// パリィ受付中
		int nBoost = pPlayer->GetBoostTime();
		if (nBoost > 0)
		{
			bParry = true;
			CSlow::Set(180);
		}
	}
	if (bDisChargeTime==true)
	{// 放電時間中
		if (fDistance > fRadius && bParry == false)
		{// 範囲内だったら
			// プレイヤーの体力を増やす攻撃
			fLife+=0.2f;
			pPlayer->SetLife(fLife);
		}
		// 放電モーション
		SetMotion(MOTION_ACTION2);

		// 電気パーティクル生成
		CParticle::Create(D3DXVECTOR3(CEnemy::GetPos()),// 位置
			80,											// 半径
			D3DXVECTOR2(30.0f,30.0f),					// サイズ
			2,											// 量
			10,											// 寿命
			1,											// 時間
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));			// 色
		
		if (m_bAttackSound == false)
		{// サウンド多重防止
			pSound->Play(CSound::LABEL_SE05);
			m_bAttackSound = true;
		}
	}
	if (m_fAttackFps > 120 * pSlow->GetnMulti())
	{// 攻撃時間が終わったら
		m_fAttackFps = 0;
		// サウンド停止
		pSound->Stop(CSound::LABEL_SE05);
		m_bAttackSound = false;

		return true;
	}
	return false;
}

//*****************
// コンストラクタ
//*****************
CFanmotorEnemy::CFanmotorEnemy()
{
	m_fAttackFps = 0;
	m_bAttackSound = false;
	m_nHitCool = 0;
}

//*****************
// デストラクタ
//*****************
CFanmotorEnemy::~CFanmotorEnemy()
{

}

//*****************
// 初期化処理
//*****************
HRESULT CFanmotorEnemy::Init(D3DXVECTOR3 pos)
{
	// モーション読み込み
	CEnemy::LoadMotion("data\\MOTION\\fanmotor.txt");
	CEnemy::Init(pos);
	CEnemy::SetSpeed(SPEED);
	
	return S_OK;
}

//*****************
// 終了処理
//*****************
void CFanmotorEnemy::Uninit(void)
{
	CEnemy::Uninit();
}

//*****************
// 更新処理
//*****************
void CFanmotorEnemy::Update(void)
{
	CEnemy::Update();
}

//*****************
// 描画処理
//*****************
void CFanmotorEnemy::Draw(void)
{
	CEnemy::Draw();
}

//*****************
// 追いかける条件
//*****************
bool CFanmotorEnemy::Chase(void)
{
	return CEnemy::Distance(200.0f);
}

//*****************
// 攻撃する条件
//*****************
bool CFanmotorEnemy::Attack(void)
{
	// プレイヤーの位置取得
	CPlayer* pPlayer = CGame::GetCPlayer();
	D3DXVECTOR3 playerPos = pPlayer->GetPos();

	// モーターシャフトのワールドマトリックス取得
	CModel* pModelShaft = GetModel(10);
	D3DXMATRIX mtxShaft = pModelShaft->GetMtxWorld();

	// 位置取得
	D3DXVECTOR3 pos = CEnemy::GetPos();

	// プレイヤーとの距離取得
	float fDistance = 35.0f;
	float radX = playerPos.x - pos.x;
	float radY = playerPos.y - pos.y;
	float radZ = playerPos.z - pos.z;
	float fRadius = sqrtf((radX * radX) + (radY * radY) + (radZ * radZ));

	// パーティクル生成
	CParticle::Create(D3DXVECTOR3(mtxShaft._41, 
		mtxShaft._42, 
		mtxShaft._43), 
		30, 
		D3DXVECTOR2(20.0f, 20.0f),
		2, 
		2, 
		1, 
		D3DXCOLOR(0.4f, 0.4f, 1.0f, 1.0f));

	if (fDistance > fRadius)
	{// 範囲内
		m_bAttackSound = false;
		return true;
	}
	return false;
}

//*****************
// 止まる条件
//*****************
bool CFanmotorEnemy::Nuetoral(void)
{
	return !CEnemy::Distance(200.0f);
}

//*****************
// やられる条件
//*****************
bool CFanmotorEnemy::Hit(void)
{
	// 位置取得
	D3DXVECTOR3 pos = GetPos();
	// プレイヤーの位置取得
	CPlayer* pPlayer = CGame::GetCPlayer();
	D3DXVECTOR3 playerPos = pPlayer->GetPos();
	// カメラとサウンド取得
	CCamera* pCamera = CManager::GetCCamera();
	CSound* pSound = CManager::GetCSound();

	// 当たり判定計算
	float DistX, DistY, DistZ;
	// 今の距離
	DistX = playerPos.x - pos.x;
	DistY = playerPos.y - pos.y;
	DistZ = playerPos.z - pos.z;
	float Dist = sqrtf((DistX * DistX) + (DistY * DistY) + (DistZ * DistZ));

	m_nHitCool++;
	// ヒットの条件
	bool bHit = Dist < Range
		&& pPlayer->GetState() != CPlayer::STATE_RAIL
		&& m_nHitCool>hitCool;
	if (bHit)
	{// ヒットしたら
		pSound->Play(CSound::LABEL_SE05);

		if (pPlayer->GetState() == CPlayer::STATE_NONE)
		{
			pPlayer->SetMove(D3DXVECTOR3(DistX * 0.05f, 0.0f, DistZ * 0.05f));
			// プレイヤーの状態を変更
			pPlayer->SetState(CPlayer::STATE_INOPERABLE);
			CInoperableState* pInoperableState = new CInoperableState;
			pPlayer->ChangeState(pInoperableState);
		}

		m_nHitCool = 0;
		return true;
	}


	// ボルトとの当たり判定
	for (int nCntPriority = 0; nCntPriority < MAX_PRI; nCntPriority++)
	{
		CObject* pObject = GetTop(nCntPriority);
		while (pObject != NULL)
		{
			CObject* pObjectNext = pObject->GetNext();
			if (pObject->GetType() == CObject::TYPE_BOLT)
			{// オブジェクトの名前がボルトだったら
				D3DXVECTOR3 posBolt=pObject->GetPos();
				D3DXVECTOR3 pos = CEnemy::GetPos();
				// 距離を計算
				float fDistance = 35.0f;
				float radX = posBolt.x - pos.x;
				float radY = posBolt.y - pos.y;
				float radZ = posBolt.z - pos.z;
				float fRadius = sqrtf((radX * radX) + (radY * radY) + (radZ * radZ));
				if (fDistance > fRadius)
				{// 範囲内だったら
					pCamera->SetShake(10);
					return true;
				}

			}
			pObject = pObjectNext;
		}
	}
	return false;
}

//*****************
// 攻撃の更新
//*****************
bool CFanmotorEnemy::AttackUpdate(void)
{
	// スローとサウンド取得
	CSlow* pSlow = CGame::GetCSlow();
	CSound* pSound = CManager::GetCSound();
	m_fAttackFps++;
	// 腕から手のワールドマトリックスを取得
	CModel* pModelArm = GetModel(4);
	CModel* pModelHand = GetModel(5);
	D3DXMATRIX mtxArm = pModelArm->GetMtxWorld();
	D3DXMATRIX mtxHand = pModelHand->GetMtxWorld();
	// プレイヤー位置と体力取得
	CPlayer* pPlayer = CGame::GetCPlayer();
	D3DXVECTOR3 playerPos = pPlayer->GetPos();
	float fLife = pPlayer->GetLife();

	// ワールドマトリックス計算
	float mtxX = (mtxHand._41 - mtxArm._41);
	float mtxY = (mtxHand._42 - mtxArm._42);
	float mtxZ = (mtxHand._43 - mtxArm._43);
	// 放電時間
	bool bParryTime = 20<m_fAttackFps&& m_fAttackFps < 40 * pSlow->GetnMulti();
	bool bParry = false;
	if (bParryTime == true)
	{// パリィ受付中
		// プレイヤーのカウンター取得
		int nBoost = pPlayer->GetBoostTime();
		if (nBoost > 0)
		{// パリィ成功
			bParry = true;
			CSlow::Set(180);
			CBlurManager::Set(180);
		}
	}

	for (int nCnt = 0; nCnt < 4; nCnt++)
	{// 手から腕の先端までを4分割する
		D3DXVECTOR3 pos;
		pos.x = mtxArm._41 + mtxX * 0.25f * nCnt;
		pos.y = mtxArm._42 + mtxY * 0.25f * nCnt;
		pos.z = mtxArm._43 + mtxZ * 0.25f * nCnt;
		CParticle::Create(pos, 40, D3DXVECTOR2(10.0f, 10.0f), 2, 4, 1, D3DXCOLOR(0.4f, 0.4f, 1.0f, 1.0f));
	}

	// 位置取得
	D3DXVECTOR3 pos=GetPos();

	// プレイヤーとの距離計算
	float DistanceX = playerPos.x - pos.x;
	float DistanceY = playerPos.y - pos.y;
	float DistanceZ = playerPos.z - pos.z;
	float fDistance = (DistanceX * DistanceX) + (DistanceY * DistanceY) + (DistanceZ * DistanceZ);

	float fPlayerRad = 30.0f;
	float fEnemyRad = 40.0f;
	// あたり判定
	float fRad = fEnemyRad + fPlayerRad;
	fRad = fRad * fRad;
	bool bAttack = fDistance < fRad && m_fAttackFps >30&& m_fAttackFps < 45&& bParry == false;

	if (bAttack == true)
	{// 攻撃条件が揃ったら
		fLife -= 1.0f;
		pPlayer->SetLife(fLife);
	}

	if (m_fAttackFps > 30&&m_bAttackSound==false)
	{// 多重サウンド防止
		pSound->Play(CSound::LABEL_SE06);
		m_bAttackSound = true;
	}
	if (m_fAttackFps > 120 * pSlow->GetnMulti())
	{// カウントが過ぎたら
		m_fAttackFps = 0;
		return true;
	}
	return false;
}