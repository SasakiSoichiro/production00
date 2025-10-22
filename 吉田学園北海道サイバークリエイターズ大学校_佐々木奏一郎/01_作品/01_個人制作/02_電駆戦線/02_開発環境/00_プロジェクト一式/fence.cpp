//*****************************************
//
// 電気柵処理 [fence.cpp]
// Author:Sasaki Soichiro
//
//*****************************************

//*******************
// インクルード
//*******************
#include "fence.h"
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

//******************
// マクロ定義
//******************
#define DISTANCE (150.0f)	// 支柱の距離
#define RADIUS (90.0f)		// 攻撃の半径

//*****************
// コンストラクタ
//*****************
CFence::CFence(int nPriority) :CObjectX(nPriority)
{
	for (int nCnt = 0; nCnt < 3; nCnt++)
	{
		m_nIdxXFile[nCnt] = -1;
	}
	m_nBreak = 0;
	m_nBreakAttack = 0;
	m_nLife = 0;
}

//*****************
// デストラクタ
//*****************
CFence::~CFence()
{
}

//******************
// インスタンス生成
//*******************
CFence* CFence::Create(D3DXVECTOR3 pos)
{
	CFence* pBlock;
	int nNum = CObject::GetNumAll();
	if (nNum < MAX_OBJ - 1)
	{// オブジェクトが最大数に達していない場合

		// インスタンス生成
		pBlock = new CFence;
		// 初期化
		pBlock->Init(pos);	

		return pBlock;			
	}

	return NULL;	
}

//*****************
// 初期化処理
//*****************
HRESULT CFence::Init(D3DXVECTOR3 pos)
{
	// CXModelのポインタに情報を入れる
	CXModel* pXModel = CManager::GetCXModel();
	// 使うモデルのインデックスを入れる
	m_nIdxXFile[0] = pXModel->Register("data\\MODEL\\fencebreak01.x");
	m_nIdxXFile[1] = pXModel->Register("data\\MODEL\\fencebreak00.x");
	m_nIdxXFile[2] = pXModel->Register("data\\MODEL\\fence.x");
	// Xファイルを割り当てる
	BindXFile(pXModel->GetAddres(m_nIdxXFile[2]));

	CObjectX::Init(pos);
	m_nLife = 3;

	return S_OK;
}

//*****************
// 終了処理
//*****************
void CFence::Uninit(void)
{
	CObjectX::Uninit();
}

//*****************
// 更新処理
//*****************
void CFence::Update(void)
{
	// 位置と向き取得
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();
	// プレイヤーの位置と前フレームの位置取得
	CPlayer* pPlayer = CGame::GetCPlayer();
	D3DXVECTOR3 playerPos = pPlayer->GetPos();
	D3DXVECTOR3 playerOldPos = pPlayer->GetOldPos();
	// サウンドとメッシュとXmodel取得
	CSound* pSound = CManager::GetCSound();
	CMesh* pMesh = CGame::GetCMesh();
	CXModel* pXModel = CManager::GetCXModel();
	// コンボ数取得
	int nCombo = CCombo::GetCombo();

	D3DXVECTOR3 postPos[2] = {};

	// 位置をメッシュの高さに合わせる
	pos.y = pMesh->GetHeight(pos);
	postPos[0].y = pos.y;
	postPos[1].y = pos.y;

	// プレイヤーの体力取得
	float fLife = pPlayer->GetLife();

	// 柵の両端の位置設定
	postPos[0].x = pos.x + sinf(rot.y) * DISTANCE;
	postPos[0].z = pos.z + cosf(rot.y) * DISTANCE;
	postPos[1].x = pos.x + sinf(rot.y + D3DX_PI) * DISTANCE;
	postPos[1].z = pos.z + cosf(rot.y + D3DX_PI) * DISTANCE;

	// プレイヤーとの距離計算
	float fDistance = RADIUS;
	float radXF = playerPos.x - postPos[0].x;
	float radYF = playerPos.y - postPos[0].y;
	float radZF = playerPos.z - postPos[0].z;
	float radXS = playerPos.x - postPos[1].x;
	float radYS = playerPos.y - postPos[1].y;
	float radZS = playerPos.z - postPos[1].z;
	float fRadiusF = sqrtf((radXF * radXF)+(radYF * radYF)+ (radZF * radZF));
	float fRadiusS = sqrtf((radXS * radXS)+(radYS * radYS)+ (radZS * radZS));


	if (fDistance > fRadiusF && m_nBreak<0 || fDistance > fRadiusS && m_nBreak < 0)
	{// プレイヤーが範囲に入ったら
		// 体力を増やす
		fLife += 10.0f;
		// 反映
		pPlayer->SetLife(fLife);
		// サウンド再生
		pSound->Play(CSound::LABEL_SE10);
		// クールタイム設定
		m_nBreak = 180;
	}

	// カウントを減らす
	m_nBreak--;
	m_nBreakAttack--;

	for (int nCnt = 0; nCnt < 2; nCnt++)
	{// 電気パーティクルを生成
		CParticle::Create(postPos[nCnt], 90, D3DXVECTOR2(30.0f, 30.0f), 2, 10, 1, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
	}
	// 反映
	SetPos(pos);

	// フェンスの間との当たり判定
	bool collision = Collision(playerPos, postPos[0], postPos[1]);

	if(collision==true)
	{// 当たったら
		m_nLife--;
		// サウンドを鳴らす
		pSound->Play(CSound::LABEL_SE11);
		// Xファイルを割り当てる
		BindXFile(pXModel->GetAddres(m_nIdxXFile[m_nLife-1]));
	}
	// 振動
	Shake();

	if (m_nLife <= 0|| nCombo>4)
	{// 消す
		// スコア加算
		CScore::Add(1000);

		Uninit();
	}
}

//*****************
// 描画処理
//*****************
void CFence::Draw(void)
{
	CObjectX::Draw();
}

//******************
// 位置の設定
//******************
void CFence::SetPos(D3DXVECTOR3 pos)
{
	CObjectX::SetPos(pos);
}

//******************
// 向きの設定
//******************
void CFence::SetRot(D3DXVECTOR3 rot)
{
	CObjectX::SetRot(rot);
}

//******************
// 位置情報の取得
//******************
D3DXVECTOR3 CFence::GetPos(void)
{
	return CObjectX::GetPos();
}

//******************
// 向き情報の取得
//******************
D3DXVECTOR3 CFence::GetRot(void)
{
	return CObjectX::GetRot();
}

//**************************
// プレイヤーとの当たり判定
//**************************
bool CFence::Collision(D3DXVECTOR3 playerPos, D3DXVECTOR3 postPos0, D3DXVECTOR3 postPos1)
{
	float fTime = 0.0f;
	float threshold = 15.0f;

	// フェンスの間を10分割
	for (int nCnt = 0; nCnt < 10; nCnt++)
	{
		// プレイヤーとの距離計算
		D3DXVECTOR3 Rpos;
		Rpos.x = postPos1.x + (postPos0.x - postPos1.x) * fTime;
		Rpos.y = postPos1.y + (postPos0.y - postPos1.y) * fTime;
		Rpos.z = postPos1.z + (postPos0.z - postPos1.z) * fTime;
		D3DXVECTOR3 Dist = Rpos - playerPos;

		float fDistance = D3DXVec3Length(&Dist);
		if (fDistance < threshold&&m_nBreakAttack<0)
		{// 範囲内だったら
			// クールタイム設定
			m_nBreakAttack = 30;
			return true;
		}
		fTime += 0.1f;
	}
	return false;
}

//****************
// 震わせる処理
//****************
void CFence::Shake(void)
{
	// 位置取得
	D3DXVECTOR3 pos = GetPos();
	if (m_nBreakAttack > 0)
	{// クールタイム中
		// 振動する処理
		pos.x += sinf((float)m_nBreakAttack);
		pos.y += sinf((float)m_nBreakAttack);
		pos.z += sinf((float)m_nBreakAttack);
	}
	// 反映
	SetPos(pos);
}