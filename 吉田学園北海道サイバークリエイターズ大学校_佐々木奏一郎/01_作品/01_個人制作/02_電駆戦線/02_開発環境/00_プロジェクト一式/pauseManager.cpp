//**********************************
//
// ポーズ管理処理 [pauseManager.cpp]
// Author:Sasaki Soichiro
//
//**********************************

//*******************
// インクルード
//*******************
#include "pauseManager.h"
#include "pause.h"
#include "input.h"
#include "manager.h"

//*****************
// 静的メンバ変数
//*****************
CPause* CPauseManager::m_pBackGame = NULL;
CPause* CPauseManager::m_pStartGame = NULL;
CPause* CPauseManager::m_pBackTitle = NULL;
CPause* CPauseManager::m_pReverse = NULL;

//*****************
// コンストラクタ
//*****************
CPauseManager::CPauseManager()
{
}

//*****************
// デストラクタ
//*****************
CPauseManager::~CPauseManager()
{
}

//*****************
// 初期化処理
//*****************
HRESULT CPauseManager::Init(void)
{
	m_pBackGame = CPause::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2-150.0f, 0.0f), CPause::TYPE_BACKGAME);
	m_pStartGame = CPause::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), CPause::TYPE_STARTGAME);
	m_pBackTitle = CPause::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2+150.0f, 0.0f), CPause::TYPE_BACKTITLE);
	m_pReverse = CPause::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 300.0f, 0.0f), CPause::TYPE_REVERSE);
	
	return S_OK;
}

//*****************
// 終了処理
//*****************
void CPauseManager::Uninit(void)
{
}

//*****************
// 更新処理
//*****************
void CPauseManager::Update(void)
{
	int nSelect = CPause::GetSelect();
	CInputKeyboard* pKeyboard = CManager::GetCInputKeyboard();
	CInputJoypad* pJoypad = CManager::GetCInputJoypad();
	bool bUp = pKeyboard->Trigger(DIK_UP)||pJoypad->GetTrigger(CInputJoypad::JOYKEY_UP)|| pKeyboard->Trigger(DIK_W);
	bool bDown = pKeyboard->Trigger(DIK_DOWN) || pJoypad->GetTrigger(CInputJoypad::JOYKEY_DOWN) || pKeyboard->Trigger(DIK_S);

	if (bUp)
	{
		nSelect--;
		if (nSelect == -1)
		{
			nSelect = 3;
		}
	}
	else if (bDown)
	{
		nSelect++;
		nSelect = nSelect % 4;
	}
	if (pKeyboard->Trigger(DIK_RETURN)||pJoypad->GetTrigger(CInputJoypad::JOYKEY_A))
	{
		switch (nSelect)
		{
		case CPause::TYPE_STARTGAME:
			CPause::SwitchPause();
			CManager::SetMode(CScene::MODE_GAME);
			break;
		}
	}


	CPause::SetSelect(nSelect);
}