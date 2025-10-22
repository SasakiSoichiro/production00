//**********************************
//
// �^�C�g������ [title.cpp]
// Author:Sasaki Soichiro
//
//**********************************

//*******************
// �C���N���[�h
//*******************
#include "scene.h"
#include "reslut.h"
#include "resultUI.h"
#include "manager.h"
#include "resultScore.h"
#include "rank.h"
#include "camera.h"
#include "input.h"
#include "fade.h"

//*******************
// �R���X�g���N�^
//*******************
CResult::CResult() :CScene(CScene::MODE_RESULT)
{
}

//*******************
// �f�X�g���N�^
//*******************
CResult::~CResult()
{
}

//*************
// ����������
//*************
HRESULT CResult::Init(D3DXVECTOR3 pos)
{
	CResultUI::Create(D3DXVECTOR3(150.0f, 100.0f, 0.0f));
	CResultScore::Create(D3DXVECTOR3(900.0f, 400.0f, 0.0f));
	CRank::Create(NONE);

	return S_OK;
}

//*************
// �I������
//*************
void CResult::Uninit(void)
{
	CObject::Release();
}

//*************
// �X�V����
//*************
void CResult::Update(void)
{
	CCamera* pCamera = CManager::GetCCamera();
	pCamera->Target(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	// �L�[�{�[�h�̎擾
	CInputKeyboard* pInputKeyboard = CManager::GetCInputKeyboard();
	CInputJoypad* pInputJoypad = CManager::GetCInputJoypad();
	if (pInputKeyboard->Trigger(DIK_RETURN)|| pInputJoypad->GetTrigger(CInputJoypad::JOYKEY_A))
	{
		CFade::Set(CScene::MODE_TITLE);
	}

}

//**************
// �`�揈��
//**************
void CResult::Draw(void)
{

}