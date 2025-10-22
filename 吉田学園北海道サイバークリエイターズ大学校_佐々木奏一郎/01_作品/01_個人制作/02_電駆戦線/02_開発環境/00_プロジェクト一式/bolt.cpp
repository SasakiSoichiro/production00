//*****************************************
//
// ボルト処理 [bolt.cpp]
// Author:Sasaki Soichiro
//
//*****************************************

//*******************
// インクルード
//*******************
#include "bolt.h"
#include "renderer.h"
#include "manager.h"
#include "player.h"
#include "game.h"
#include "particle.h"
#include "attackbolt.h"
#include "sound.h"
#include "mesh.h"

//*****************
// コンストラクタ
//*****************
CBolt::CBolt(int nPriority) :CObjectX(nPriority)
{
	m_nIdxXFile = -1;
	m_nBreak = 0;
	m_nLife = 0;
	m_fAngle = 0.0f;
	m_fAngleSum = 0.0f;
}

//*****************
// デストラクタ
//*****************
CBolt::~CBolt()
{
}

//******************
// インスタンス生成
//*******************
CBolt* CBolt::Create(D3DXVECTOR3 pos)
{
	CBolt* pBlock;
	int nNum = CObject::GetNumAll();

	if (nNum < MAX_OBJ - 1)
	{// オブジェクトが最大数に達していない場合

		// インスタンス生成
		pBlock = new CBolt;	
		// 初期化
		pBlock->Init(pos);

		return pBlock;			
	}

	return NULL;
}

//*****************
// 初期化処理
//*****************
HRESULT CBolt::Init(D3DXVECTOR3 pos)
{
	// CXModelのポインタに情報を入れる
	CXModel* pXModel = CManager::GetCXModel();
	// 使うモデルのインデックスを入れる
	m_nIdxXFile = pXModel->Register("data\\MODEL\\bolts.x");
	// Xファイルを割り当てる
	BindXFile(pXModel->GetAddres(m_nIdxXFile));

	// 初期化
	CObjectX::Init(pos);
	m_nBreak = 0;
	m_nLife = maxLife;

	return S_OK;
}

//*****************
// 終了処理
//*****************
void CBolt::Uninit(void)
{
	CObjectX::Uninit();
}

//*****************
// 更新処理
//*****************
void CBolt::Update(void)
{
	// サウンドとメッシュ情報取得
	CSound* pSound = CManager::GetCSound();
	CMesh* pMesh = CGame::GetCMesh();
	// 位置情報取得
	D3DXVECTOR3 pos = GetPos();
	// プレイヤーとプレイヤーの位置情報取得
	CPlayer* pPlayer = CGame::GetCPlayer();
	D3DXVECTOR3 playerPos = pPlayer->GetPos();
	D3DXVECTOR3 playerOldPos = pPlayer->GetOldPos();

	float DistX, DistY, DistZ;
	// 現在のプレイヤーとの距離を求める
	DistX = playerPos.x - pos.x;
	DistY = playerPos.y - pos.y;
	DistZ = playerPos.z - pos.z;
	float Dist = sqrtf((DistX * DistX) + (DistY * DistY) + (DistZ * DistZ));

	// 前フレームのプレイヤーとの距離を求める
	DistX = playerOldPos.x - pos.x;
	DistY = playerOldPos.y - pos.y;
	DistZ = playerOldPos.z - pos.z;
	float OldDist = sqrtf((DistX * DistX) + (DistY * DistY) + (DistZ * DistZ));
	
	// プレイヤーとの当たり判定
	if (Dist < maxRange && OldDist>= maxRange)
	{
		// 回転の合計を初期化
		m_fAngle = pPlayer->GetAngle();
		m_fAngleSum = 0.0f;
	}

	// ボルトを飛ばせる処理
	if (Dist < maxRange && m_nLife>0)
	{
		// プレイヤーが回転した合計を求める
		float OldAngle = m_fAngle;
		m_fAngle = pPlayer->GetAngle();
		m_fAngleSum += fabs(OldAngle - m_fAngle);


		if (m_fAngleSum > D3DX_PI*2.0f)
		{// 1回転したら

			// ボルトを360度方向に飛ばす
			for (int nCnt = 0; nCnt < 18; nCnt++)
			{
				float fAngle = D3DX_PI * 2.0f * nCnt / 18;
				CAttackBolt::Create(playerPos, fAngle);
			}

			// SE再生
			pSound->Play(CSound::LABEL_SE01);

			// 初期化
			m_nLife = 0;
			m_nBreak = 0;
			m_fAngleSum = 0.0f;
		}
		
	}

	// 休憩時間が過ぎたら寿命回復
	m_nBreak++;
	if (m_nBreak > maxBreakTime)
	{
		m_nLife = maxLife;
	}

	// 地面の高さに合わせる&位置反映
	pos.y = pMesh->GetHeight(pos);
	SetPos(pos);

}

//*****************
// 描画処理
//*****************
void CBolt::Draw(void)
{
	CObjectX::Draw();
}

//******************
// 位置の設定
//******************
void CBolt::SetPos(D3DXVECTOR3 pos)
{
	CObjectX::SetPos(pos);
}

//******************
// 向きの設定
//******************
void CBolt::SetRot(D3DXVECTOR3 rot)
{
	CObjectX::SetRot(rot);
}

//******************
// 位置情報の取得
//******************
D3DXVECTOR3 CBolt::GetPos(void)
{
	return CObjectX::GetPos();
}

//******************
// 向き情報の取得
//******************
D3DXVECTOR3 CBolt::GetRot(void)
{
	return CObjectX::GetRot();
}