//***********************************
//
// レール処理 [rail.cpp]
// Author:Sasaki Soichiro
//
//***********************************

//*******************
// インクルード
//*******************
#include "rail.h"
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

//*******************
// マクロ定義
//*******************
#define MAX_RAIL (10)
#define NUM_BLOCK (MAX_RAIL*RAILBLOCK_NUM)	//ブロックの最大数

//******************
// コンストラクタ
//******************
CRail::CRail()
{
	for (int nCnt = 0; nCnt < MAX_POINT; nCnt++)
	{
		m_pBlock[nCnt] = NULL;
	}
	m_pPrev = NULL;
	m_nNumPoint=0;
	m_fTime=0.0f;
	m_fTension = 0.0f;
	m_nCurrentIdx = 0;
	m_nPlayerCurrentIdx = 0;
	m_fPlayerCurrentT = 0.0f;
}

//******************
// コンストラクタ
//******************
CRail::~CRail()
{

}

//*******************
// インスタンス生成
//*******************
CRail* CRail::Create(D3DXVECTOR3 point0, D3DXVECTOR3 point1, D3DXVECTOR3 point2, D3DXVECTOR3 point3)
{
	CRail* pRail;
	pRail = new CRail;
	pRail->m_pBlock[0] = CBlock::Create(point0);
	pRail->m_pBlock[1] = CBlock::Create(point1);
	pRail->m_pBlock[2] = CBlock::Create(point2);
	pRail->m_pBlock[3] = CBlock::Create(point3);
	pRail->m_pPrev = CBlock::Create(point1);
	pRail->m_nNumPoint = 4;
	pRail->Init(point1);
	return pRail;
}

//=====================
// レールの初期化処理
//=====================
HRESULT CRail::Init(D3DXVECTOR3 pos)
{
	m_fTension = 0.5f;
	m_nCurrentIdx = 1;
	Load();
	return S_OK;
}

//=====================
// レールの終了処理
//=====================
void CRail::Uninit(void)
{
	CObject::Release();
}

//=====================
// レールの更新処理
//=====================
void CRail::Update(void)
{
	CPlayer* pPlayer;
	CInputKeyboard* pInputKeyboard;
	pInputKeyboard = CManager::GetCInputKeyboard();
	pPlayer = CManager::GetCPlayer();
	CPlayer::STATE state = pPlayer->GetState();
	m_fTime+=0.01f;
	m_fPlayerCurrentT += 0.01f;
	D3DXVECTOR3 pos=Curve(m_pBlock[m_nCurrentIdx-1]->GetPos(),
		m_pBlock[m_nCurrentIdx]->GetPos(),
		m_pBlock[m_nCurrentIdx+1]->GetPos(),
		m_pBlock[m_nCurrentIdx+2]->GetPos(), m_fTime);
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
	bool t = false;;

	switch (state)
	{
	case CPlayer::STATE_NONE:
		t = Collision(pPlayer->GetPos());
		if (t==true&&pInputKeyboard->Trigger(DIK_SPACE)==true)
		{
			pPlayer->SetState(CPlayer::STATE_RAIL);
		}
		break;
		case CPlayer::STATE_RAIL:
			D3DXVECTOR3 pos = Curve(m_pBlock[m_nPlayerCurrentIdx - 1]->GetPos(),
				m_pBlock[m_nPlayerCurrentIdx]->GetPos(),
				m_pBlock[m_nPlayerCurrentIdx + 1]->GetPos(),
				m_pBlock[m_nPlayerCurrentIdx + 2]->GetPos(), m_fPlayerCurrentT);
			pPlayer->SetPos(pos);
			if (m_fPlayerCurrentT >= 1.0f)
			{
				m_fPlayerCurrentT = 0.0f;
				m_nPlayerCurrentIdx++;
			}
			if (m_nPlayerCurrentIdx > m_nNumPoint - 3|| pInputKeyboard->Trigger(DIK_SPACE) == true)
			{
				pPlayer->SetState(CPlayer::STATE_NONE);
			}
			break;
	}

	if (pInputKeyboard->Trigger(DIK_F3) == true)
	{
		Save();
	}
	else if (pInputKeyboard->Trigger(DIK_F4) == true)
	{
		Load();
	}
	if (pInputKeyboard->Trigger(DIK_G) == true)
	{
		AddPoint(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}
}

//************
// 描画処理
//************
void CRail::Draw(void)
{
	//for (int nCnt = 0; nCnt < m_nNumPoint; nCnt++)
	//{
	//	m_pBlock[nCnt]->Draw();
	//}
}

//**************************
// 曲線処理 (Catmull-Rom)
//**************************
D3DXVECTOR3 CRail::Curve(D3DXVECTOR3 P0, D3DXVECTOR3 P1, D3DXVECTOR3 P2, D3DXVECTOR3 P3, float t)
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
void CRail::AddPoint(D3DXVECTOR3 pos)
{
	if (m_pBlock[m_nNumPoint] == NULL)
	{
		m_pBlock[m_nNumPoint] = CBlock::Create(pos);
	}
	m_nNumPoint++;
}

//**************************
// プレイヤーとの当たり判定
//**************************
bool CRail::Collision(D3DXVECTOR3 pos)
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
				return true;
			}
		}
		fTime += 0.1f;
	}
	return false;
}

//***********
// セーブ
//***********
void CRail::Save(void)
{
	// 保存するファイルを開く
	std::ofstream outFile("data\\rail.txt");
	if (!outFile)
	{// 開けなかった場合
		return;
	}
	// 小数点以下も保存する
	outFile << std::fixed << std::setprecision(2);

	for (int nCnt = 0; nCnt < m_nNumPoint; nCnt++)
	{
		D3DXVECTOR3 pos = m_pBlock[nCnt]->GetPos();
		outFile << "point" << nCnt << " : "
				<<"pos = "<< pos.x <<" " <<pos.y<<" "<<pos.z
				<< std::endl;
	}

	// ファイルを明示的に閉じる
	outFile.close();
}

//***********
// ロード
//***********
void CRail::Load(void)
{
	std::ifstream file("data\\rail.txt");
	int nNumPoint = 0;
	int nCnt = 0;
	D3DXVECTOR3 pos=D3DXVECTOR3(0.0f,0.0f,0.0f);
	if (file.is_open() == false)
	{
		return;
	}
	std::string line;
	while (std::getline(file, line))
	{
		int scan2 = sscanf(line.c_str(),
			"point%d : pos = %f %f %f",
			&nNumPoint,&pos.x, &pos.y, &pos.z);
		if (m_pBlock[nCnt] == NULL)
		{
			AddPoint(pos);
		}
		else
		{
			m_pBlock[nCnt]->SetPos(pos);
		}
		nCnt++;
	}
	// ファイルを明示的に閉じる
	file.close();
}