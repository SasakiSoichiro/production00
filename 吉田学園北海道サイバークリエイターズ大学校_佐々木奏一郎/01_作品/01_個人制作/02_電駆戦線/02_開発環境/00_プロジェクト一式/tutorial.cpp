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
#include "tutorial.h"
#include "manager.h"
#include "input.h"
#include "camera.h"
#include "skydoom.h"
#include "fade.h"
#include "tutorialUI.h"
#include "tutorialCheck.h"
#include "mesh.h"
#include "tutorialPlayer.h"
#include "blockManager.h"
#include "block.h"
#include "tutorialRail.h"
#include "skip.h"
#include "tutorialEnemy.h"
#include "controllerUI.h"

CMesh* CTutorial::m_pMesh = NULL;
CTutorialPlayer* CTutorial::m_pPlayer = NULL;
CBlockManager* CTutorial::m_pBlockManager = NULL;
CTutorialRail* CTutorial::m_pRail = NULL;


//*******************
// �R���X�g���N�^
//*******************
CTutorial::CTutorial() :CScene(CScene::MODE_TUTORIAL)
{
	m_State = STATE_FLONTBACK;
	m_Machine = NULL;
	m_pTutorialCheck = NULL;
}

//*******************
// �f�X�g���N�^
//*******************
CTutorial::~CTutorial()
{
}

//*************
// ����������
//*************
HRESULT CTutorial::Init(D3DXVECTOR3 pos)
{
	CCamera* pCamera = CManager::GetCCamera();
	pCamera->InitTarget(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	m_pBlockManager = new CBlockManager;

	m_Machine = new CStateMachine;
	CFlontBackState* pFlontBackState = new CFlontBackState;
	ChangeState(pFlontBackState);


	m_pTutorialCheck =CTutorialCheck::Create(D3DXVECTOR3(450.0f, 200.0f, 0.0f));
	m_pMesh = CMesh::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pPlayer = CTutorialPlayer::Create(D3DXVECTOR3(400.0f, 5.0f, 0.3f));

	// ��
	CBlock::Create(D3DXVECTOR3(0.0f, 0.0f, 500.0f), "data\\MODEL\\honeycomb01.x", 1);
	CBlock::Create(D3DXVECTOR3(0.0f, 0.0f, -500.0f), "data\\MODEL\\honeycomb01.x", 1);
	CBlock::Create(D3DXVECTOR3(500.0f, 0.0f, 0.0f), "data\\MODEL\\honeycomb00.x", 1);
	CBlock::Create(D3DXVECTOR3(-500.0f, 0.0f, 0.0f), "data\\MODEL\\honeycomb00.x", 1);

	// UI
	CSkip::Create(D3DXVECTOR3(1050.0f, 50.0f, 0.0f));
	CControllerUI::Create(D3DXVECTOR3(100.0f, SCREEN_WIDTH / 2, 0.0f));

	CTutorialRail::InitAll();
	D3DXVECTOR3 Railpos[11];
	for (int nCnt = 0; nCnt < 11; nCnt++)
	{// ���[���̐���_�ݒ�
		float fAngle = D3DX_PI * 2.0f * 1 / 8;
		Railpos[nCnt].x = cosf(fAngle * (nCnt % 8)) * 400.0f;
		Railpos[nCnt].y = 13.0f;
		Railpos[nCnt].z = sinf(fAngle * (nCnt % 8)) * 400.0f;
	}

	// ���[�� �[�d�^�C�v
	m_pRail = CTutorialRail::Create(Railpos[0], Railpos[1], Railpos[2], Railpos[3], 0);

	for (int nCnt = 4; nCnt < 11; nCnt++)
	{// ���[���̐���_�ǉ�
		m_pRail->AddPoint(Railpos[nCnt]);
	}


	return S_OK;
}

//*************
// �I������
//*************
void CTutorial::Uninit(void)
{
	if (m_Machine != NULL)
	{
		m_Machine->Uninit();
		delete 	m_Machine;
		m_Machine = NULL;
	}
	if (m_pBlockManager != NULL)
	{
		m_pBlockManager->Uninit();
		delete m_pBlockManager;
		m_pBlockManager = NULL;
	}

	CObject::Release();
}

//*************
// �X�V����
//*************
void CTutorial::Update(void)
{
	// �L�[�{�[�h�̎擾
	CInputKeyboard* pKeyboard = CManager::GetCInputKeyboard();
	CInputJoypad* pJoypad = CManager::GetCInputJoypad();

	if (pKeyboard->Trigger(DIK_RETURN) == true
		|| pJoypad->GetTrigger(CInputJoypad::JOYKEY_START) == true)
	{
		CFade::Set(CScene::MODE_GAME);
	}

	m_Machine->Update();

}

//**************
// �`�揈��
//**************
void CTutorial::Draw(void)
{

}

//****************
// �^�X�N�̃N���A
//****************
void CTutorial::TaskClear(void)
{
	m_pTutorialCheck->Clear();
}

void CTutorial::ChangeState(CTutorialStateBase* pState)
{
	pState->SetOwner(this);
	m_Machine->ChangeState(pState);
}

//****************
// �R���X�g���N�^
//****************
CTutorialStateBase::CTutorialStateBase()
{
	m_pTutorial = NULL;
}

//****************
// �f�X�g���N�^
//****************
CTutorialStateBase::~CTutorialStateBase()
{

}
//******************************
// �`���[�g���A���̃|�C���^�ݒ�
//******************************
void CTutorialStateBase::SetOwner(CTutorial* pTutorial)
{
	m_pTutorial = pTutorial;
}

//*********************************
//           �O��̑���
//*********************************

//****************
// �R���X�g���N�^
//****************
CFlontBackState::CFlontBackState()
{
	m_nClear = false;
	m_nCnt = 0;
}

//****************
// �f�X�g���N�^
//****************
CFlontBackState::~CFlontBackState()
{

}

//***************
// ����������
//***************
void CFlontBackState::Init(void)
{

}

//***************
// �X�V����
//***************
void CFlontBackState::Update(void)
{
	CInputJoypad* pJoypad = CManager::GetCInputJoypad();
	XINPUT_STATE* pJoyStick = pJoypad->GetState();
	bool bFlont = pJoyStick->Gamepad.sThumbLY >= 10000;
	bool bBack = pJoyStick->Gamepad.sThumbLY <= -10000;

	if (bFlont || bBack)
	{
		m_nCnt++;
	}
	if (m_nCnt > clearTime&& m_nClear==false)
	{
		m_pTutorial->TaskClear();
		m_nClear = true;
		CRightLeftState* pRLState = new CRightLeftState;
		m_pTutorial->ChangeState(pRLState);

	}
}

//***************
// �I������
//***************
void CFlontBackState::Uninit(void)
{

}

//*********************************
//           ���E�̑���
//*********************************

//****************
// �R���X�g���N�^
//****************
CRightLeftState::CRightLeftState()
{

}

//****************
// �f�X�g���N�^
//****************
CRightLeftState::~CRightLeftState()
{

}

//***************
// ����������
//***************
void CRightLeftState::Init(void)
{
}

//***************
// �X�V����
//***************
void CRightLeftState::Update(void)
{

	CInputJoypad* pJoypad = CManager::GetCInputJoypad();
	XINPUT_STATE* pJoyStick = pJoypad->GetState();
	bool bFlont = pJoyStick->Gamepad.sThumbLY >= 10000;
	bool bBack = pJoyStick->Gamepad.sThumbLY <= -10000;
	bool bLeft = pJoypad->GetPress(CInputJoypad::JOYKEY_RIGHTS);
	bool bRight = pJoypad->GetPress(CInputJoypad::JOYKEY_LEFTS);


	if (bFlont || bBack)
	{
		if (bLeft || bRight)
		{
			m_nCnt++;
		}
	}
	if (m_nCnt > clearTime && m_nClear == false)
	{
		m_pTutorial->TaskClear();
		m_nClear = true;
		CRollState* pRollState = new CRollState;
		m_pTutorial->ChangeState(pRollState);
	}

}

//***************
// �I������
//***************
void CRightLeftState::Uninit(void)
{

}

//*********************************
//           ��]�̑���
//*********************************

//****************
// �R���X�g���N�^
//****************
CRollState::CRollState()
{

}

//****************
// �f�X�g���N�^
//****************
CRollState::~CRollState()
{

}

//***************
// ����������
//***************
void CRollState::Init(void)
{
}

//***************
// �X�V����
//***************
void CRollState::Update(void)
{

	CInputJoypad* pJoypad = CManager::GetCInputJoypad();
	bool bLeft = pJoypad->GetPress(CInputJoypad::JOYKEY_X);
	bool bRight = pJoypad->GetPress(CInputJoypad::JOYKEY_A);


	if (bLeft || bRight)
	{
		m_nCnt++;
	}
	if (m_nCnt > clearTime && m_nClear == false)
	{
		m_pTutorial->TaskClear();
		m_nClear = true;
		CJumpCState* pJumpState = new CJumpCState;
		m_pTutorial->ChangeState(pJumpState);
	}

}

//***************
// �I������
//***************
void CRollState::Uninit(void)
{

}

//*********************************
//        �W�����v�̑���
//*********************************

//****************
// �R���X�g���N�^
//****************
CJumpCState::CJumpCState()
{

}

//****************
// �f�X�g���N�^
//****************
CJumpCState::~CJumpCState()
{

}

//***************
// ����������
//***************
void CJumpCState::Init(void)
{
}

//***************
// �X�V����
//***************
void CJumpCState::Update(void)
{

	CInputJoypad* pJoypad = CManager::GetCInputJoypad();
	bool bLeft = pJoypad->GetPress(CInputJoypad::JOYKEY_X);
	bool bRight = pJoypad->GetPress(CInputJoypad::JOYKEY_A);
	CTutorialPlayer* pPlayer = CTutorial::GetCPlayer();
	D3DXVECTOR3 playerPos = pPlayer->GetPos();

	if (bLeft || bRight)
	{
		m_nCnt++;
	}
	if (playerPos.y>90.0f&& m_nClear == false)
	{
		m_pTutorial->TaskClear();
		m_nClear = true;
		CJumpCancelState* pJumpCancelState = new CJumpCancelState;
		m_pTutorial->ChangeState(pJumpCancelState);
	}

}

//***************
// �I������
//***************
void CJumpCState::Uninit(void)
{

}

//*********************************
//    �W�����v�L�����Z���̑���
//*********************************

//****************
// �R���X�g���N�^
//****************
CJumpCancelState::CJumpCancelState()
{

}

//****************
// �f�X�g���N�^
//****************
CJumpCancelState::~CJumpCancelState()
{

}

//***************
// ����������
//***************
void CJumpCancelState::Init(void)
{
}

//***************
// �X�V����
//***************
void CJumpCancelState::Update(void)
{

	CInputJoypad* pJoypad = CManager::GetCInputJoypad();
	bool bLeft = pJoypad->GetPress(CInputJoypad::JOYKEY_X);
	bool bRight = pJoypad->GetPress(CInputJoypad::JOYKEY_A);
	CTutorialPlayer* pPlayer = CTutorial::GetCPlayer();
	bool bCancel = pPlayer->GetJumpCancel();

	if (bCancel && m_nClear == false)
	{
		m_pTutorial->TaskClear();
		m_nClear = true;
		CRailCState* pRailState = new CRailCState;
		m_pTutorial->ChangeState(pRailState);
	}

}

//***************
// �I������
//***************
void CJumpCancelState::Uninit(void)
{

}

//*********************************
//    ���[���̑���
//*********************************

//****************
// �R���X�g���N�^
//****************
CRailCState::CRailCState()
{

}

//****************
// �f�X�g���N�^
//****************
CRailCState::~CRailCState()
{

}

//***************
// ����������
//***************
void CRailCState::Init(void)
{
}

//***************
// �X�V����
//***************
void CRailCState::Update(void)
{
	CTutorialPlayer* pPlayer = CTutorial::GetCPlayer();

	if (pPlayer->GetState()==CTutorialPlayer::STATE_RAIL)
	{
		m_pTutorial->TaskClear();
		m_nClear = true;
		CAttackCState* pAttackState = new CAttackCState;
		m_pTutorial->ChangeState(pAttackState);
	}

}

//***************
// �I������
//***************
void CRailCState::Uninit(void)
{

}

//*********************************
//    ���[���̑���
//*********************************

//****************
// �R���X�g���N�^
//****************
CAttackCState::CAttackCState()
{

}

//****************
// �f�X�g���N�^
//****************
CAttackCState::~CAttackCState()
{

}

//***************
// ����������
//***************
void CAttackCState::Init(void)
{
	CTutorialEnemy::Create(D3DXVECTOR3(0.2f,0.2f,0.2f));
}

//***************
// �X�V����
//***************
void CAttackCState::Update(void)
{
	CTutorialPlayer* pPlayer = CTutorial::GetCPlayer();

	if (CTutorialEnemy::GetNumAll()<=0)
	{
		m_pTutorial->TaskClear();
		m_nClear = true;
		CFreeState* pFreeState = new CFreeState;
		m_pTutorial->ChangeState(pFreeState);
	}
}

//***************
// �I������
//***************
void CAttackCState::Uninit(void)
{

}


//*********************************
//    �t���[�̑���
//*********************************

//****************
// �R���X�g���N�^
//****************
CFreeState::CFreeState()
{

}

//****************
// �f�X�g���N�^
//****************
CFreeState::~CFreeState()
{

}

//***************
// ����������
//***************
void CFreeState::Init(void)
{
}

//***************
// �X�V����
//***************
void CFreeState::Update(void)
{
	// ���͎擾
	CInputJoypad* pJoypad = CManager::GetCInputJoypad();

	CTutorialEnemy::EnemyUpdate();

	if (pJoypad->GetTrigger(CInputJoypad::JOYKEY_START))
	{
		m_pTutorial->TaskClear();
		m_nClear = true;
		CFade::Set(CScene::MODE_GAME);
	}

}

//***************
// �I������
//***************
void CFreeState::Uninit(void)
{

}