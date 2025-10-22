//***********************************
//
// レール処理 [rail.cpp]
// Author:Sasaki Soichiro
//
//***********************************

//*******************
// インクルード
//*******************
#include "tutorialRail.h"
#include "input.h"
#include "camera.h"
#include <stdio.h>
#include "debugproc.h"
#include "player.h"
#include "manager.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include < iomanip >
#include "tutorial.h"
#include "particle.h"
#include "railblock.h"
#include "object.h"
#include "blockManager.h"
#include "railmesh.h"
#include "gatherparticle.h"
#include "sparkParticle.h"
#include "railEffect.h"
#include "chargeEffect.h"
#include "motion.h"
#include "tutorialPlayer.h"

//*******************
// マクロ定義
//*******************
#define MAX_RAIL (10)
#define NUM_BLOCK (MAX_RAIL*RAILBLOCK_NUM)	//ブロックの最大数
#define ANGLE_OFFSET (0.8f)
#define RAILEFFECT_SIZE (D3DXVECTOR2(150.0f,45.0f))

//**********************
// 静的メンバ変数初期化
//**********************
int CTutorialRail::m_nCntAll = 0;
int CTutorialRail::m_nUse = 0;
int CTutorialRail::m_nOldUse = 0;
int CTutorialRail::m_nPlayerCurrentIdx = 0;
float  CTutorialRail::m_fPlayerCurrentT = 0.0f;


//******************
// コンストラクタ
//******************
CTutorialRail::CTutorialRail()
{
	for (int nCnt = 0; nCnt < MAX_POINT; nCnt++)
	{
		m_pBlock[nCnt] = NULL;
	}
	m_pPrev = NULL;
	m_nNumPoint = 0;
	m_fTime = 0.0f;
	m_fTension = 0.0f;
	m_nCurrentIdx = 0;
	m_nCnt = 0;
	m_nUse = 0;
	m_nOldUse = 0;
	m_nIdx = m_nCntAll;
	m_nType = 0;
	m_pMesh = NULL;
	m_nEffectCnt = 0;

	m_nCntAll++;
}

//******************
// コンストラクタ
//******************
CTutorialRail::~CTutorialRail()
{

}

//*******************
// インスタンス生成
//*******************
CTutorialRail* CTutorialRail::Create(D3DXVECTOR3 point0, D3DXVECTOR3 point1, D3DXVECTOR3 point2, D3DXVECTOR3 point3, int nType)
{
	CTutorialRail* pRail;
	pRail = new CTutorialRail;
	pRail->m_pBlock[0] = CRailBlock::Create(point0);
	pRail->m_pBlock[1] = CRailBlock::Create(point1);
	pRail->m_pBlock[2] = CRailBlock::Create(point2);
	pRail->m_pBlock[3] = CRailBlock::Create(point3);
	pRail->m_pPrev = CRailBlock::Create(point1);
	pRail->m_pMesh = CRailMesh::Create(point1, nType);
	pRail->m_nNumPoint = 4;
	pRail->m_nType = nType;
	pRail->Init(point1);
	return pRail;
}

//=====================
// レールの初期化処理
//=====================
HRESULT CTutorialRail::Init(D3DXVECTOR3 pos)
{
	m_fTension = 0.5f;
	m_nCurrentIdx = 1;
	m_nEffectCnt = 0;
	float fEffectT = 0.0f;
	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		m_pMesh->SetVtxPos(m_pBlock[m_nNumPoint - 3]->GetPos(), nCnt);
	}

	for (int nCnt = 0; nCnt < 5; nCnt++)
	{
		fEffectT += 0.2f;

		D3DXVECTOR3 pos0 = Curve(m_pBlock[m_nNumPoint - 4]->GetPos(),
			m_pBlock[m_nNumPoint - 3]->GetPos(),
			m_pBlock[m_nNumPoint - 2]->GetPos(),
			m_pBlock[m_nNumPoint - 1]->GetPos(), fEffectT - 0.2f);

		D3DXVECTOR3 pos1 = Curve(m_pBlock[m_nNumPoint - 4]->GetPos(),
			m_pBlock[m_nNumPoint - 3]->GetPos(),
			m_pBlock[m_nNumPoint - 2]->GetPos(),
			m_pBlock[m_nNumPoint - 1]->GetPos(), fEffectT);

		SetMesh(pos0, pos1);

	}

	//Load();
	return S_OK;
}

//=====================
// レールの終了処理
//=====================
void CTutorialRail::Uninit(void)
{
	CObject::Release();
}

//=====================
// レールの更新処理
//=====================
void CTutorialRail::Update(void)
{
	CTutorialPlayer* pPlayer = CTutorial::GetCPlayer();
	CBlockManager* pBlockManager = CTutorial::GetCBlockManager();
	CInputKeyboard* pInputKeyboard = CManager::GetCInputKeyboard();
	CInputJoypad* pInputJoypad = CManager::GetCInputJoypad();

	CTutorialPlayer::STATE state = pPlayer->GetState();

	m_fTime += 0.01f;

	D3DXVECTOR3 pos = Curve(m_pBlock[m_nCurrentIdx - 1]->GetPos(),
		m_pBlock[m_nCurrentIdx]->GetPos(),
		m_pBlock[m_nCurrentIdx + 1]->GetPos(),
		m_pBlock[m_nCurrentIdx + 2]->GetPos(), m_fTime);

	float fAngle = pPlayer->GetAngle();

	m_pPrev->SetPos(pos);
	if (m_fTime >= 1.0f)
	{
		m_fTime = 0.0f;
		m_nCurrentIdx++;
	}
	if (m_nCurrentIdx > m_nNumPoint - 3)
	{
		m_nCurrentIdx = 1;
	}
	bool t = false;


	switch (state)
	{
	case CPlayer::STATE_NONE:
		t = Collision(pPlayer->GetPos());
		if (t == true && pInputKeyboard->Trigger(DIK_SPACE) == true || t == true && pInputJoypad->GetTrigger(CInputJoypad::JOYKEY_Y))
		{
			pPlayer->SetState(CTutorialPlayer::STATE_RAIL);
			CTutorialRailState* pRailState = new CTutorialRailState;
			pPlayer->ChangeState(pRailState);

		}
		break;
	case CPlayer::STATE_RAIL:

		if (m_nUse == m_nIdx)
		{
			m_fPlayerCurrentT += 0.01f;
			m_nOldUse = m_nUse;

			D3DXVECTOR3 pos = Curve(m_pBlock[m_nPlayerCurrentIdx - 1]->GetPos(),
				m_pBlock[m_nPlayerCurrentIdx]->GetPos(),
				m_pBlock[m_nPlayerCurrentIdx + 1]->GetPos(),
				m_pBlock[m_nPlayerCurrentIdx + 2]->GetPos(), m_fPlayerCurrentT);
			D3DXVECTOR3 posS = Curve(m_pBlock[m_nPlayerCurrentIdx - 1]->GetPos(),
				m_pBlock[m_nPlayerCurrentIdx]->GetPos(),
				m_pBlock[m_nPlayerCurrentIdx + 1]->GetPos(),
				m_pBlock[m_nPlayerCurrentIdx + 2]->GetPos(), m_fPlayerCurrentT - 0.01f);


			fAngle = GetAngle(pos, posS);
			pPlayer->SetAngle(fAngle);

			pos = pBlockManager->Collision(pos, pPlayer->GetOldPos());
			pPlayer->SetPos(pos);
			float fLife = pPlayer->GetLife();

			if (m_fPlayerCurrentT >= 1.0f)
			{
				m_fPlayerCurrentT = 0.0f;
				m_nPlayerCurrentIdx++;
			}
			if (m_nPlayerCurrentIdx > m_nNumPoint - 3)
			{
				m_nPlayerCurrentIdx = 1;
			}
			if (pInputKeyboard->Trigger(DIK_SPACE) == true || pInputJoypad->GetTrigger(CInputJoypad::JOYKEY_Y))
			{
				pPlayer->SetState(CTutorialPlayer::STATE_RAILCHANGE);
				CTutorialRailChangeState* pRailChangeState = new CTutorialRailChangeState;
				pPlayer->ChangeState(pRailChangeState);
			}
			else if (pInputKeyboard->Trigger(DIK_S) == true || pInputJoypad->GetTrigger(CInputJoypad::JOYKEY_B))
			{
				pPlayer->SetState(CTutorialPlayer::STATE_NONE);
				CTutorialRandState* pRandState = new CTutorialRandState;
				pPlayer->ChangeState(pRandState);
			}
		}
		break;
	case CPlayer::STATE_RAILCHANGE:
		if (Collision(pPlayer->GetPos()) && m_nOldUse != m_nUse)
		{
			pPlayer->SetState(CTutorialPlayer::STATE_RAIL);
			CTutorialRailState* pRailState = new CTutorialRailState;
			pPlayer->ChangeState(pRailState);
		}
		break;
	}

	m_nCnt++;
}

//************
// 描画処理
//************
void CTutorialRail::Draw(void)
{

}

//**************************
// 曲線処理 (Catmull-Rom)
//**************************
D3DXVECTOR3 CTutorialRail::Curve(D3DXVECTOR3 P0, D3DXVECTOR3 P1, D3DXVECTOR3 P2, D3DXVECTOR3 P3, float t)
{
	float t2 = t * t;
	float t3 = t2 * t;

	D3DXVECTOR3 point;
	point.x = m_fTension * ((2.0f * P1.x) + (-P0.x + P2.x) * t + (2.0f * P0.x - 5.0f * P1.x + 4.0f * P2.x - P3.x) * t2 + (-P0.x + 3.0f * P1.x - 3.0f * P2.x + P3.x) * t3);
	point.y = m_fTension * ((2.0f * P1.y) + (-P0.y + P2.y) * t + (2.0f * P0.y - 5.0f * P1.y + 4.0f * P2.y - P3.y) * t2 + (-P0.y + 3.0f * P1.y - 3.0f * P2.y + P3.y) * t3);
	point.z = m_fTension * ((2.0f * P1.z) + (-P0.z + P2.z) * t + (2.0f * P0.z - 5.0f * P1.z + 4.0f * P2.z - P3.z) * t2 + (-P0.z + 3.0f * P1.z - 3.0f * P2.z + P3.z) * t3);

	return point;

}

//************
// 制御点追加
//************
void CTutorialRail::AddPoint(D3DXVECTOR3 pos)
{
	float fEffectT = 0.0f;
	if (m_pBlock[m_nNumPoint] == NULL)
	{
		m_pBlock[m_nNumPoint] = CRailBlock::Create(pos);
		for (int nCnt = 0; nCnt < 5; nCnt++)
		{
			D3DXVECTOR3 pos0 = Curve(m_pBlock[m_nNumPoint - 3]->GetPos(),
				m_pBlock[m_nNumPoint - 2]->GetPos(),
				m_pBlock[m_nNumPoint - 1]->GetPos(),
				m_pBlock[m_nNumPoint]->GetPos(), fEffectT);

			D3DXVECTOR3 pos1 = Curve(m_pBlock[m_nNumPoint - 3]->GetPos(),
				m_pBlock[m_nNumPoint - 2]->GetPos(),
				m_pBlock[m_nNumPoint - 1]->GetPos(),
				m_pBlock[m_nNumPoint]->GetPos(), fEffectT + 0.2f);

			SetMesh(pos0, pos1);

			//CParticle::Create(pos, 10, D3DXVECTOR2(10.0f, 10.0f), 1, 5, 1, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), false);
			fEffectT += 0.2f;
		}

	}
	m_nNumPoint++;
}

//**************************
// プレイヤーとの当たり判定
//**************************
bool CTutorialRail::Collision(D3DXVECTOR3 pos)
{
	float fTime = 0.0f;
	float threshold = 30.0f;
	for (int nCnt = 0; nCnt < 10; nCnt++)
	{
		for (int nCntIndex = 1; nCntIndex < m_nNumPoint - 2; nCntIndex++)
		{
			D3DXVECTOR3 Rpos = Curve(m_pBlock[nCntIndex - 1]->GetPos(),
				m_pBlock[nCntIndex]->GetPos(),
				m_pBlock[nCntIndex + 1]->GetPos(),
				m_pBlock[nCntIndex + 2]->GetPos(), fTime);
			D3DXVECTOR3 Dist = Rpos - pos;

			float fDistance = D3DXVec3Length(&Dist);
			if (fDistance < threshold)
			{
				m_nPlayerCurrentIdx = nCntIndex;
				m_fPlayerCurrentT = fTime;
				m_nUse = m_nIdx;
				return true;
			}
		}
		fTime += 0.1f;
	}
	return false;
}

//******************
// メッシュの設定
//******************
void CTutorialRail::SetMesh(D3DXVECTOR3 pos0, D3DXVECTOR3 pos1)
{
	D3DXVECTOR3 pos[2];
	D3DXVECTOR3 dir;
	D3DXVECTOR3 width;
	D3DXVECTOR3 up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	dir = pos1 - pos0;

	D3DXVec3Normalize(&dir, &dir);

	D3DXVec3Cross(&width, &up, &dir);

	D3DXVec3Normalize(&width, &width);

	pos[0] = pos0 - width * 2.0f;
	pos[1] = pos0 + width * 2.0f;

	m_pMesh->Add(pos[0], pos[1]);
}


float CTutorialRail::GetAngle(D3DXVECTOR3 pos0, D3DXVECTOR3 pos1)
{
	float DistX = pos1.x - pos0.x;
	float DistZ = pos1.z - pos0.z;

	float fAngle = atan2f(DistX, DistZ);
	return fAngle;
}

void CTutorialRail::Change(void)
{
	switch (m_nUse)
	{
	case 0:
		m_nUse = 1;
		break;

	case 1:
		m_nUse = 0;
		break;
	}
}
