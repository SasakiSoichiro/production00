//***************************************************
//
// 敵の体力マネージャー処理 [enemyLifeManager.cpp]
// Author:Sasaki Soichiro
//
//***************************************************

//*******************
// インクルード
//*******************
#include "enemyLifeManager.h"
#include "enemyLifeUI.h"
#include "input.h"
#include "manager.h"


//*****************
// コンストラクタ
//*****************
CEnemyLifeManager::CEnemyLifeManager(int nPriority) :CObject(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	for (int nCnt = 0; nCnt < 5; nCnt++)
	{
		m_pLifeUI[nCnt] = NULL;
	}

	m_nLife = 0;
	m_nOffsetLife = 0;
}

//*****************
// デストラクタ
//*****************
CEnemyLifeManager::~CEnemyLifeManager()
{
}

//******************
// インスタンス生成
//*******************
CEnemyLifeManager* CEnemyLifeManager::Create(D3DXVECTOR3 pos, int nLife)
{
	CEnemyLifeManager* pLifeManager;

	// 現在のオブジェクトの総数取得
	int nNum = CObject::GetNumAll();
	if (nNum < MAX_OBJ - 1)
	{// オブジェクトが最大数に達していない場合

		// インスタンス生成
		pLifeManager = new CEnemyLifeManager;
		pLifeManager->m_nLife = nLife;
		pLifeManager->m_nOffsetLife = nLife;
		// 初期化
		pLifeManager->Init(pos);

		return pLifeManager;
	}

	return NULL;
}


//*****************
// 初期化処理
//*****************
HRESULT CEnemyLifeManager::Init(D3DXVECTOR3 pos)
{
	// HPメモリのサイズ計算
	float fullSize = size * m_nLife;
	float halfSize = fullSize * 0.5f;

	for (int nCnt = 0; nCnt < m_nLife; nCnt++)
	{// インスタンス生成
		m_pLifeUI[nCnt] = CEnemyLifeUI::Create(D3DXVECTOR3(pos.x, pos.y, pos.z),
			D3DXVECTOR2((size * nCnt) - halfSize, 0.0f), nCnt + 1);
	}
	return S_OK;
}

//*****************
// 終了処理
//*****************
void CEnemyLifeManager::Uninit(void)
{
	for (int nCnt = 0; nCnt < m_nOffsetLife; nCnt++)
	{
		if (m_pLifeUI[nCnt] != NULL)
		{
			m_pLifeUI[nCnt]->Uninit();
		}
	}
	CObject::Release();
}

//*****************
// 更新処理
//*****************
void CEnemyLifeManager::Update(void)
{
	// UIの場所と体力の設定
	for (int nCnt = 0; nCnt < m_nOffsetLife; nCnt++)
	{
		if (m_nLife > 0)
		{
			m_pLifeUI[nCnt]->SetPos(m_pos);
			m_pLifeUI[nCnt]->SetLife(m_nLife);
		}
	}
}

//*****************
// 描画処理
//*****************
void CEnemyLifeManager::Draw(void)
{

}

//*****************
// HPの設定
//*****************
void CEnemyLifeManager::SetLife(int nLife)
{
	m_nLife = nLife;
}