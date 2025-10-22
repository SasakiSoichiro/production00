//*****************************************
//
// �[�d�ʒ��ߏ��� [adjust.cpp]
// Author:Sasaki Soichiro
//
//*****************************************

//*******************
// �C���N���[�h
//*******************
#include "adjust.h"
#include "player.h"
#include "game.h"
#include "input.h"
#include "manager.h"
#include "adjustUI.h"

//**********************
// �ÓI�����o�ϐ�������
//**********************
const D3DXVECTOR3 CAdjust::POS_UI = D3DXVECTOR3(100.0f, 380.0f, 0.0f);

//*****************
// �R���X�g���N�^
//*****************
CAdjust::CAdjust()
{
	m_fSum = 0;
	m_pAdjustUI = NULL;
}

//*****************
// �f�X�g���N�^
//*****************
CAdjust::~CAdjust()
{
}

//*****************
// ������
//*****************
HRESULT CAdjust::Init(void)
{
	m_fSum = maxSum;
	m_pAdjustUI = CAdjustUI::Create(POS_UI);

	return S_OK;
}

//*****************
// �I������
//*****************
void CAdjust::Uninit(void)
{

}

//*****************
// �X�V����
//*****************
void CAdjust::Update(void)
{
	// ���͎擾
	CInputJoypad* pJoypad = CManager::GetCInputJoypad();
	CInputKeyboard* pKeyboard = CManager::GetCInputKeyboard();
	CInputMouse* pMouse = CManager::GetCInputMouse();
	XINPUT_STATE* pInputJoyStick = pJoypad->GetState();

	// �v���C���[�Ƒ̗͏��擾
	CPlayer* pPlayer = CGame::GetCPlayer();
	float fLife = pPlayer->GetLife();

	// �̗͏���
	bool bSum = m_fSum > 0.0f;
	// ����
	bool bUp = pInputJoyStick->Gamepad.sThumbRY >= thereshold|| pKeyboard->GetPress(DIK_UP);
	bool bDown = pInputJoyStick->Gamepad.sThumbRY <= -thereshold || pKeyboard->GetPress(DIK_DOWN);

	
	// �̗͂�ς���
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

	// �l�𔽉f
	pPlayer->SetLife(fLife);
	m_pAdjustUI->SetLife(m_fSum);
}

