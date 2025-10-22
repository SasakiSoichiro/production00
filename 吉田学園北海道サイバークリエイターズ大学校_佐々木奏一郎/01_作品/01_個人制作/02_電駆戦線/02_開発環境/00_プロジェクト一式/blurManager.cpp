//**********************************
//
// ブラー管理処理 [blurManager.cpp]
// Author:Sasaki Soichiro
//
//**********************************

//*******************
// インクルード
//*******************
#include "blurManager.h"

//**********************
// 静的メンバ変数初期化
//**********************
bool CBlurManager::m_bTime=false;
int CBlurManager::m_nTime=0;

//*****************
// コンストラクタ
//*****************
CBlurManager::CBlurManager()
{
}

//*****************
// デストラクタ
//*****************
CBlurManager::~CBlurManager()
{
}

//*****************
// 初期化処理
//*****************
HRESULT CBlurManager::Init(void)
{

	return S_OK;
}

//*****************
// 終了処理
//*****************
void CBlurManager::Uninit(void)
{
}

//*****************
// 更新処理
//*****************
void CBlurManager::Update(void)
{
	if (m_nTime > 0)
	{// ブラーする時間が0秒以上
		m_bTime = true;
	}
	else
	{// ブラーする時間が0秒以下
		m_bTime = false;
	}

	m_nTime--;
}