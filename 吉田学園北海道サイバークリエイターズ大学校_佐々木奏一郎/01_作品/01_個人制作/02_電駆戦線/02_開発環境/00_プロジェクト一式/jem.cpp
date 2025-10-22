//*****************************************
//
// 宝石処理 [jem.cpp]
// Author:Sasaki Soichiro
//
//*****************************************

//*******************
// インクルード
//*******************
#include "jem.h"
#include "renderer.h"
#include "manager.h"
#include "player.h"
#include "game.h"
#include "particle.h"
#include "attackbolt.h"
#include "sound.h"
#include "mesh.h"
#include "combo.h"
#include "score.h"
#include "pieceparticle.h"

//****************
// マクロ定義
//****************
#define RANGE (50.0f)

//*****************
// コンストラクタ
//*****************
CJem::CJem(int nPriority) :CObjectX(nPriority)
{
	for (int nCnt = 0; nCnt < 3; nCnt++)
	{
		m_nIdxXFile[nCnt] = -1;
	}
	m_nLife = 0;
	m_nShake = 0;
	m_OffsetPos = NONE;
}

//*****************
// デストラクタ
//*****************
CJem::~CJem()
{
}

//******************
// インスタンス生成
//*******************
CJem* CJem::Create(D3DXVECTOR3 pos)
{
	CJem* pBlock;
	int nNum = CObject::GetNumAll();
	if (nNum < MAX_OBJ - 1)
	{// オブジェクトが最大数に達していない場合

		pBlock = new CJem;	// インスタンス生成
		pBlock->Init(pos);		// 初期化
		return pBlock;			// 情報を渡す
	}

	// オブジェクトが最大数に達していた場合
	return NULL;	// NULLを返す
}

//*****************
// 初期化処理
//*****************
HRESULT CJem::Init(D3DXVECTOR3 pos)
{
	// CXModelのポインタに情報を入れる
	CXModel* pXModel = CManager::GetCXModel();
	// 使うモデルのインデックスを入れる
	m_nIdxXFile[0] = pXModel->Register("data\\MODEL\\jembreak01.x");
	m_nIdxXFile[1] = pXModel->Register("data\\MODEL\\jembreak00.x");
	m_nIdxXFile[2] = pXModel->Register("data\\MODEL\\jem.x");

	// Xファイルを割り当てる
	BindXFile(pXModel->GetAddres(m_nIdxXFile[2]));

	// 初期化
	CObjectX::Init(pos);
	m_nLife = 3;
	m_OffsetPos = pos;

	// 初期化成功
	return S_OK;
}

//*****************
// 終了処理
//*****************
void CJem::Uninit(void)
{
	CObjectX::Uninit();
}

//*****************
// 更新処理
//*****************
void CJem::Update(void)
{
	// 位置取得
	D3DXVECTOR3 pos = GetPos();
	// プレイヤーの位置と前フレームの位置取得
	CPlayer* pPlayer = CGame::GetCPlayer();
	D3DXVECTOR3 playerPos = pPlayer->GetPos();
	D3DXVECTOR3 playerOldPos = pPlayer->GetOldPos();
	// モデルとサウンド取得
	CXModel* pXModel = CManager::GetCXModel();
	CSound* pSound = CManager::GetCSound();

	// 現在の距離計算
	float DistX, DistY, DistZ;
	DistX = playerPos.x - pos.x;
	DistY = playerPos.y - pos.y;
	DistZ = playerPos.z - pos.z;
	float Dist = sqrtf((DistX * DistX) + (DistY * DistY) + (DistZ * DistZ));

	// 前フレームの距離計算
	DistX = playerOldPos.x - pos.x;
	DistY = playerOldPos.y - pos.y;
	DistZ = playerOldPos.z - pos.z;
	float OldDist = sqrtf((DistX * DistX) + (DistY * DistY) + (DistZ * DistZ));

	// コンボ取得
	int nCombo = CCombo::GetCombo();

	if (Dist < RANGE)
	{
		m_nLife--;
		// Xファイルを割り当てる
		BindXFile(pXModel->GetAddres(m_nIdxXFile[m_nLife-1]));
		// サウンド再生
		pSound->Play(CSound::LABEL_SE09);
		m_nShake = 20;
		if (m_nLife <= 0|| nCombo>=5)
		{
			CScore::Add(300);
			int nAngle = (int)(atan2f(DistX, DistY)) * 100;
			nAngle -= 314;
			CPieceParticle::Create(pos, nAngle);
			Uninit();
		}
		else
		{
			pPlayer->SetState(CPlayer::STATE_NONE);
			pPlayer->SetPos(D3DXVECTOR3(playerPos.x + (DistX * 1.2f), playerPos.y + (DistY * 1.2f), playerPos.z + (DistZ * 1.2f)));
			CRandState* pRandState = new CRandState;
			pPlayer->ChangeState(pRandState);
		}
	}
	if (m_nShake > 0)
	{
		Shake();
		m_nShake--;
	}
	else
	{
		SetPos(m_OffsetPos);
	}
}

//*****************
// 描画処理
//*****************
void CJem::Draw(void)
{
	CObjectX::Draw();// 描画
}

//******************
// 位置の設定
//******************
void CJem::SetPos(D3DXVECTOR3 pos)
{
	CObjectX::SetPos(pos);// 位置設定
}

//******************
// 向きの設定
//******************
void CJem::SetRot(D3DXVECTOR3 rot)
{
	CObjectX::SetRot(rot);// 向き設定
}

//******************
// 位置情報の取得
//******************
D3DXVECTOR3 CJem::GetPos(void)
{
	return CObjectX::GetPos();// 位置情報取得
}
D3DXVECTOR3 CJem::GetRot(void)
{
	return CObjectX::GetRot();// 位置情報取得
}

void CJem::Shake(void)
{
	D3DXVECTOR3 pos = GetPos();
	pos.x += sinf((float)m_nShake)*1.4f;
	pos.y += sinf((float)m_nShake)*1.4f;
	pos.z += sinf((float)m_nShake)*1.4f;

	SetPos(pos);
}