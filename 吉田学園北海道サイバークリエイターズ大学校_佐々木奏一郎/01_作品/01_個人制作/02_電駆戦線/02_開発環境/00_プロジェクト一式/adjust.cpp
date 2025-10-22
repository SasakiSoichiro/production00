//*****************************************
//
// 充電量調節処理 [adjust.cpp]
// Author:Sasaki Soichiro
//
//*****************************************

//*******************
// インクルード
//*******************
#include "adjust.h"
#include "player.h"
#include "game.h"
#include "input.h"
#include "manager.h"
#include "adjustUI.h"

//**********************
// 静的メンバ変数初期化
//**********************
const D3DXVECTOR3 CAdjust::POS_UI = D3DXVECTOR3(100.0f, 380.0f, 0.0f);

//*****************
// コンストラクタ
//*****************
CAdjust::CAdjust()
{
	m_fSum = 0;
	m_pAdjustUI = NULL;
}

//*****************
// デストラクタ
//*****************
CAdjust::~CAdjust()
{
}

//*****************
// 初期化
//*****************
HRESULT CAdjust::Init(void)
{
	m_fSum = maxSum;
	m_pAdjustUI = CAdjustUI::Create(POS_UI);

	return S_OK;
}

//*****************
// 終了処理
//*****************
void CAdjust::Uninit(void)
{

}

//*****************
// 更新処理
//*****************
void CAdjust::Update(void)
{
	// 入力取得
	CInputJoypad* pJoypad = CManager::GetCInputJoypad();
	CInputKeyboard* pKeyboard = CManager::GetCInputKeyboard();
	CInputMouse* pMouse = CManager::GetCInputMouse();
	XINPUT_STATE* pInputJoyStick = pJoypad->GetState();

	// プレイヤーと体力情報取得
	CPlayer* pPlayer = CGame::GetCPlayer();
	float fLife = pPlayer->GetLife();

	// 体力条件
	bool bSum = m_fSum > 0.0f;
	// 入力
	bool bUp = pInputJoyStick->Gamepad.sThumbRY >= thereshold|| pKeyboard->GetPress(DIK_UP);
	bool bDown = pInputJoyStick->Gamepad.sThumbRY <= -thereshold || pKeyboard->GetPress(DIK_DOWN);

	
	// 体力を変える
	if (bSum)
	{
		if (bUp)
		{
			fLife += frameLife;
			m_fSum -= frameLife;
		}
		else if (bDown)
		{
			fLife -= frameLife;
			m_fSum -= frameLife;
		}
	}

	// 値を反映
	pPlayer->SetLife(fLife);
	m_pAdjustUI->SetLife(m_fSum);
}

