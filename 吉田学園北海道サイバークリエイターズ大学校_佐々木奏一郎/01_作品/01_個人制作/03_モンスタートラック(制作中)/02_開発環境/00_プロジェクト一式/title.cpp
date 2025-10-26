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
#include "title.h"
#include "titleUI.h"
#include "manager.h"
#include "sound.h"
#include "input.h"
#include "camera.h"
#include "fade.h"

//*******************
// �R���X�g���N�^
//*******************
CTitle::CTitle() :CScene(CScene::MODE_TITLE)
{
}

//*******************
// �f�X�g���N�^
//*******************
CTitle::~CTitle()
{
}

//*************
// ����������
//*************
HRESULT CTitle::Init(D3DXVECTOR3 pos)
{
	CSound* pSound = CManager::GetCSound();
	CTitleUI::Create(D3DXVECTOR3(300.0f, 150.0f, 0.0f));
	pSound->Play(CSound::LABEL_BGM00);
	CCamera* pCamera = CManager::GetCCamera();
	pCamera->InitTarget(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	return S_OK;
}

//*************
// �I������
//*************
void CTitle::Uninit(void)
{
	CObject::Release();
}

//*************
// �X�V����
//*************
void CTitle::Update(void)
{
	// �L�[�{�[�h�̎擾
	CInputKeyboard* pInputKeyboard = CManager::GetCInputKeyboard();
	CInputJoypad* pInputJoypad = CManager::GetCInputJoypad();
	if (pInputKeyboard->Trigger(DIK_RETURN)==true||pInputJoypad->GetTrigger(CInputJoypad::JOYKEY_START)==true)
	{
		CFade::Set(CScene::MODE_GAME);
	}
}

//**************
// �`�揈��
//**************
void CTitle::Draw(void)
{

}