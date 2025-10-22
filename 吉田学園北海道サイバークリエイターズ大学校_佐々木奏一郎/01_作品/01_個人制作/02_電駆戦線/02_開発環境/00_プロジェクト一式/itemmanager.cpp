//**********************************
//
// アイテム管理処理 [blurManager.cpp]
// Author:Sasaki Soichiro
//
//**********************************

//*******************
// インクルード
//*******************
#include "itemmanager.h"
#include "itemskill.h"

//*****************
// コンストラクタ
//*****************
CItemManager::CItemManager()
{
	m_pItemSkill = NULL;
}

//*****************
// デストラクタ
//*****************
CItemManager::~CItemManager()
{

}

//*****************
// 初期化処理
//*****************
HRESULT CItemManager::Init(void)
{
	m_pItemSkill = NULL;

	return S_OK;
}

//*****************
// 終了処理
//*****************
void CItemManager::Uninit(void)
{
	if (m_pItemSkill != NULL)
	{
		m_pItemSkill->Uninit();
		delete m_pItemSkill;
		m_pItemSkill = NULL;
	}

}

//*****************
// 更新処理
//*****************
void CItemManager::Update(void)
{
	if (m_pItemSkill != NULL)
	{// 更新
		m_pItemSkill->Update();
	}
	else
	{

	}
}