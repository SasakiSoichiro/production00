//**********************************
//
// �}�l�[�W������ [manager.cpp]
// Author:Sasaki Soichiro
//
//**********************************

//*******************
// �C���N���[�h
//*******************
#include "manager.h"
#include "renderer.h"
#include "object2D.h"
#include <time.h>
#include "score.h"
#include "timer.h"
#include "debugproc.h"
#include "pause.h"
#include "lifeUI.h"
#include "object3D.h"
#include "objectX.h"
#include "objectBillboard.h"
#include "player.h"
#include "mesh.h"
#include "rail.h"
#include "enemy.h"
#include "object.h"
#include "input.h"
#include "sound.h"
#include "texture.h"
#include "camera.h"
#include "light.h"
#include "Xmodel.h"
#include "scene.h"
#include "blurManager.h"
#include "pauseManager.h"
#include "fade.h"


//*******************
// �ÓI�����o�ϐ�
//*******************
CRenderer *CManager::m_pRenderer=NULL;
CInputKeyboard* CManager::m_pInputKeyboard = NULL;
CInputMouse* CManager::m_pInputMouse = NULL;
CInputJoypad* CManager::m_pInputJoypad = NULL;
CSound* CManager::m_pSound = NULL;
CDebugProc* CManager::m_pDebugProc = NULL;
CTexture* CManager::m_pTexture = NULL;
CCamera* CManager::m_pCamera = NULL;
CLight* CManager::m_pLight = NULL;
CXModel* CManager::m_pXModel = NULL;
CScene* CManager::m_pScene = NULL;
CBlurManager* CManager::m_pBlur = NULL;
CPauseManager* CManager::m_pPauseManager = NULL;
CFade* CManager::m_pFade = NULL;


//*******************
// �R���X�g���N�^
//*******************
CManager::CManager()
{
}

//*******************
// �f�X�g���N�^
//*******************
CManager::~CManager()
{
}

//*************
// ����������
//*************
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	// �C���X�^���X����
	m_pRenderer = new CRenderer;
	m_pInputKeyboard = new CInputKeyboard;
	m_pInputMouse = new CInputMouse;
	m_pInputJoypad = new CInputJoypad;
	m_pSound = new CSound;
	m_pDebugProc = new CDebugProc;
	m_pTexture = new CTexture;
	m_pCamera = new CCamera;
	m_pLight = new CLight;
	m_pXModel = new CXModel;
	m_pBlur = new CBlurManager;
	m_pFade = new CFade;

	// ����������
	if (FAILED(m_pRenderer->Init(hWnd, TRUE)))
	{//���������������s�����ꍇ
		return-1;
	}
	// ����������
	if (FAILED(m_pInputKeyboard->Init(hInstance, hWnd)))
	{//���������������s�����ꍇ
		return-1;
	}
	// ����������
	if (FAILED(m_pInputMouse->Init(hInstance, hWnd)))
	{//���������������s�����ꍇ
		return-1;
	}
	// ����������
	if (FAILED(m_pInputJoypad->Init(hInstance, hWnd)))
	{//���������������s�����ꍇ
		return-1;
	}
	// ����������
	if (FAILED(m_pSound->Init(hWnd)))
	{//���������������s�����ꍇ
		return-1;
	}
	// ����������
	if (FAILED(m_pTexture->Load()))
	{//���������������s�����ꍇ
		return-1;
	}
	// ����������
	if (FAILED(m_pXModel->Load()))
	{//���������������s�����ꍇ
		return-1;
	}
	// ����������
	m_pCamera->Init();
	m_pLight->Init();
	m_pDebugProc->Init();
	m_pFade->Init();

	
	return S_OK;
}

//*************
// �I������
//*************
void CManager::Uninit(void)
{
	//�I������
	CObject::ReleaseAll();
	if (m_pTexture != NULL)
	{
		m_pTexture->Unload();
		delete m_pTexture;
		m_pTexture = NULL;
	}
	if (m_pXModel != NULL)
	{
		m_pXModel->Unload();
		delete m_pXModel;
		m_pXModel = NULL;
	}
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = NULL;
	}
	if (m_pInputKeyboard != NULL)
	{
		m_pInputKeyboard->Uninit();
		delete m_pInputKeyboard;
		m_pInputKeyboard = NULL;
	}
	if (m_pInputMouse != NULL)
	{
		m_pInputMouse->Uninit();
		delete m_pInputMouse;
		m_pInputMouse = NULL;
	}
	if (m_pInputJoypad != NULL)
	{
		m_pInputJoypad->Uninit();
		delete m_pInputJoypad;
		m_pInputJoypad = NULL;
	}
	if (m_pSound != NULL)
	{
		m_pSound->Uninit();
		delete m_pSound;
		m_pSound = NULL;
	}
	if (m_pDebugProc != NULL)
	{
		m_pDebugProc->Uninit();
		delete m_pDebugProc;
		m_pDebugProc = NULL;
	}
	if (m_pCamera != NULL)
	{
		m_pCamera->Uninit();
		delete m_pCamera;
		m_pCamera = NULL;

	}
	if (m_pLight != NULL)
	{
		m_pLight->Uninit();
		delete m_pLight;
		m_pLight = NULL;
	}
	if (m_pBlur != NULL)
	{
		m_pBlur->Uninit();
		delete m_pBlur;
		m_pBlur = NULL;
	}
	if (m_pFade != NULL)
	{
		m_pFade->Uninit();
		delete m_pFade;
		m_pFade = NULL;
	}


}

//*************
// �X�V����
//*************
void CManager::Update(void)
{
	m_pRenderer->Update();
	m_pInputKeyboard->Update();
	m_pInputMouse->Update();
	m_pInputJoypad->Update();
	m_pCamera->Update();
	m_pBlur->Update();
	m_pFade->Update();

	if (m_pInputKeyboard->Trigger(DIK_F1) == true)
	{
		CDebugProc::SwitchDebug();
	}
	if (m_pInputKeyboard->Trigger(DIK_P) == true)
	{
	}
	if (m_pInputKeyboard->Trigger(DIK_1) == true)
	{
		SetMode(CScene::MODE_TITLE);
	}
	if (m_pInputKeyboard->Trigger(DIK_2) == true)
	{
		SetMode(CScene::MODE_GAME);
	}
	if (m_pInputKeyboard->Trigger(DIK_3) == true)
	{
		SetMode(CScene::MODE_RESULT);
	}
	if (m_pInputKeyboard->Trigger(DIK_4) == true)
	{
		SetMode(CScene::MODE_EDIT);
	}

	for (int nCntPriority = 0; nCntPriority < MAX_PRI; nCntPriority++)
	{
		int nNum = CObject::GetNumPriority(nCntPriority);
		CDebugProc::Print("�`��%d�Ԗڂ̐�:%d\n", nCntPriority, nNum);
	}
}

//**************
// �`�揈��
//**************
void CManager::Draw(void)
{
	m_pRenderer->Draw();
}

//**************
// �V�[���ݒ�
//**************
void CManager::SetMode(CScene::MODE mode)
{
	// �T�E���h�̒�~
	m_pSound->Stop();
	// �t�F�[�h�̔j��

	// ���݂̃��[�h�̔j��
	if (m_pScene != NULL)
	{
		m_pScene->Uninit();
		m_pScene = NULL;
	}
	// �S�ẴI�u�W�F�N�g�̔j��
	CObject::ReleaseAll();
	// �V�������[�h�̐���
	m_pScene = CScene::Create(mode);
	// �t�F�[�h��������
}

CScene::MODE CManager::GetMode(void)
{
	CScene::MODE mode = m_pScene->GetMode();
	return mode;
}