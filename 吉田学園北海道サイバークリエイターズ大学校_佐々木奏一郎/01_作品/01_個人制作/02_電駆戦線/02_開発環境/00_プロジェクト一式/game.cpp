//**********************************
//
// �}�l�[�W������ [manager.cpp]
// Author:Sasaki Soichiro
//
//**********************************

//*******************
// �C���N���[�h
//*******************
#include "scene.h"
#include "game.h"
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
#include "effect.h"
#include "particle.h"
#include "manager.h"
#include "bolt.h"
#include "block.h"
#include "attackbolt.h"
#include "batterydown.h"
#include "stanUI.h"
#include "numbermulti.h"
#include "combo.h"
#include "smoke.h"
#include "sound.h"
#include "blockManager.h"
#include "defenceResult.h"
#include "wave.h"
#include "slow.h"
#include "blurManager.h"
#include "input.h"
#include "skydoom.h"
#include "humansatellite.h"
#include "jem.h"
#include "fence.h"
#include "snagManager.h"
#include "item.h"
#include "pauseManager.h"
#include "fade.h"
#include "railmesh.h"
#include "pieceparticle.h"
#include "railManager.h"
#include "railEffect.h"
#include "chargeEffect.h"
#include "enemyLifeManager.h"
#include "controllerUI.h"
#include "target.h"

//*******************
// �ÓI�����o�ϐ�
//*******************
CObject3D* CGame::m_pObject3D = NULL;
CMesh* CGame::m_pMesh = NULL;
CPlayer* CGame::m_pPlayer = NULL;
CWave* CGame::m_pWave = NULL;
CSlow* CGame::m_pSlow = NULL;
CBlockManager* CGame::m_pBlockManager = NULL;
CSnagManager* CGame::m_pSnagManager = NULL;
CPauseManager* CGame::m_pPauseManager = NULL;
CRailManager* CGame::m_pRailManager = NULL;
CGame::STATE CGame::m_State = STATE_NONE;


//*******************
// �R���X�g���N�^
//*******************
CGame::CGame():CScene(CScene::MODE_GAME)
{
	m_nCnt = 0;
}

//*******************
// �f�X�g���N�^
//*******************
CGame::~CGame()
{
}

//*************
// ����������
//*************
HRESULT CGame::Init(D3DXVECTOR3 pos)
{
	m_State = STATE_NONE;
	m_nCnt = 0;

	// �X���[
	m_pSlow = new CSlow;

	// �u���b�N�}�l�[�W���[
	m_pBlockManager = new CBlockManager;

	// ��Q���}�l�[�W���[
	m_pSnagManager = new CSnagManager;
	m_pSnagManager->Init();

	// �|�[�Y�}�l�[�W���[
	m_pPauseManager = new CPauseManager;
	m_pPauseManager->Init();

	// �E�F�[�u�Ǘ�
	m_pWave = CWave::Create(D3DXVECTOR3(-150.0f, 150.0f, 0.0f));

	// �n��
	m_pMesh = CMesh::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	// �{���g
	CBolt::Create(D3DXVECTOR3(150.1f,0.0f,0.1f));
	CBolt::Create(D3DXVECTOR3(-150.1f, 0.0f, 0.1f));

	// ��
	CBlock::Create(D3DXVECTOR3(0.0f, 0.0f, 500.0f),"data\\MODEL\\honeycomb01.x",0);
	CBlock::Create(D3DXVECTOR3(0.0f, 0.0f, -500.0f), "data\\MODEL\\honeycomb01.x", 0);
	CBlock::Create(D3DXVECTOR3(500.0f, 0.0f, 0.0f), "data\\MODEL\\honeycomb00.x", 0);
	CBlock::Create(D3DXVECTOR3(-500.0f, 0.0f, 0.0f), "data\\MODEL\\honeycomb00.x", 0);

	// ���C�g
	CBlock::Create(D3DXVECTOR3(-700.0f, 0.0f, 0.0f), "data\\MODEL\\light.x", 0);
	CBlock::Create(D3DXVECTOR3(750.0f, 0.0f, 750.0f), "data\\MODEL\\light01.x", 0);
	CBlock::Create(D3DXVECTOR3(0.0f, 0.0f, -700.0f), "data\\MODEL\\controller.x", 0);

	// �O��
	CBlock::Create(D3DXVECTOR3(0.0f, 0.0f, 900.0f), "data\\MODEL\\wall00.x", 0);
	CBlock::Create(D3DXVECTOR3(0.0f, 0.0f, -900.0f), "data\\MODEL\\wall00.x", 0);
	CBlock::Create(D3DXVECTOR3(900.0f, 0.0f, 0.0f), "data\\MODEL\\wall01.x", 0);
	CBlock::Create(D3DXVECTOR3(-900.0f, 0.0f, 0.0f), "data\\MODEL\\wall01.x", 0);

	// ����
	CSkyDoom::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	CHumanSatellite::Create(D3DXVECTOR3(0.0f, 200.0f, 0.0f));

	// UI
	CScore::Create(D3DXVECTOR3(600.0f, 300.0f, 0.0f));
	CTimer::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 50.0f, 0.0f), 120);
	CBatteryDown::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 150.0f, 0.0f));
	CStanUI::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 150.0f, 0.0f));
	CCombo::Create(D3DXVECTOR3(1180.0f, 350.0f, 0.0f));
	CControllerUI::Create(D3DXVECTOR3(100.0f, SCREEN_WIDTH / 2, 0.0f));
	CTarget::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 600.0f, 0.0f));

	CRailEffect::Create(D3DXVECTOR3(0.0f, -100.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(200.0f,200.0f));

	// �v���C���[
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(408.0f, 1.0f, -3.5f));

	// ���[���}�l�[�W���[
	m_pRailManager = new CRailManager;
	m_pRailManager->Init();

	// �T�E���h
	CSound* pSound = CManager::GetCSound();
	pSound->Play(CSound::LABEL_BGM01);

	// �X�R�A������
	CScore::SetScore(0);
	
	return S_OK;
}

//*************
// �I������
//*************
void CGame::Uninit(void)
{
	if (m_pSlow != NULL)
	{
		m_pSlow->Uninit();
		delete m_pSlow;
		m_pSlow = NULL;
	}
	if (m_pBlockManager != NULL)
	{
		m_pBlockManager->Uninit();
		delete m_pBlockManager;
		m_pBlockManager = NULL;
	}
	if (m_pSnagManager != NULL)
	{
		m_pSnagManager->Uninit();
		delete m_pSnagManager;
		m_pSnagManager = NULL;
	}
	if (m_pPauseManager != NULL)
	{
		m_pPauseManager->Uninit();
		delete m_pPauseManager;
		m_pPauseManager = NULL;
	}
	if (m_pRailManager != NULL)
	{
		m_pRailManager->Uninit();
		delete m_pRailManager;
		m_pRailManager = NULL;
	}


	CObject::Release();
}

//*************
// �X�V����
//*************
void CGame::Update(void)
{
	// ���͎擾
	CInputKeyboard* pKeyboard = CManager::GetCInputKeyboard();
	CInputJoypad* pJoypad = CManager::GetCInputJoypad();

	// �|�[�Y����
	bool bPause = pKeyboard->Trigger(DIK_P) || pJoypad->GetTrigger(CInputJoypad::JOYKEY_START);
	if (bPause)
	{
		CPause::SwitchPause();
	}

	if (CPause::GetPause())
	{// �|�[�Y��
		m_pPauseManager->Update();
	}
	else
	{// �|�[�Y�ȊO
		// �X�V
		m_pSlow->Update();
		m_pSnagManager->Update();
		m_pRailManager->Update();

		// ��ԕύX
		switch (m_State)
		{
		case STATE_NORMAL:
			break;
		case STATE_END:
			if (m_nCnt <= 0)
			{
				// �Q�[�����ʕ\��
				CDefenceResult::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f));
			}
			m_nCnt++;
			if (m_nCnt > 120)
			{
				m_nCnt = 0;
				// ���U���g�ֈڍs
				CFade::Set(CScene::MODE_RESULT);
			}
			break;
		}
	}
	
}

//**************
// �`�揈��
//**************
void CGame::Draw(void)
{
	
}