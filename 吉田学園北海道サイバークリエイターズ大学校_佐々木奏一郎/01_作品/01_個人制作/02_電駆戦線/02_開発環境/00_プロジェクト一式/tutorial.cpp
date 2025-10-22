//**********************************
//
// タイトル処理 [title.cpp]
// Author:Sasaki Soichiro
//
//**********************************

//*******************
// インクルード
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
// コンストラクタ
//*******************
CTutorial::CTutorial() :CScene(CScene::MODE_TUTORIAL)
{
	m_State = STATE_FLONTBACK;
	m_Machine = NULL;
	m_pTutorialCheck = NULL;
}

//*******************
// デストラクタ
//*******************
CTutorial::~CTutorial()
{
}

//*************
// 初期化処理
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

	// 壁
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
	{// レールの制御点設定
		float fAngle = D3DX_PI * 2.0f * 1 / 8;
		Railpos[nCnt].x = cosf(fAngle * (nCnt % 8)) * 400.0f;
		Railpos[nCnt].y = 13.0f;
		Railpos[nCnt].z = sinf(fAngle * (nCnt % 8)) * 400.0f;
	}

	// レール 充電タイプ
	m_pRail = CTutorialRail::Create(Railpos[0], Railpos[1], Railpos[2], Railpos[3], 0);

	for (int nCnt = 4; nCnt < 11; nCnt++)
	{// レールの制御点追加
		m_pRail->AddPoint(Railpos[nCnt]);
	}


	return S_OK;
}

//*************
// 終了処理
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
// 更新処理
//*************
void CTutorial::Update(void)
{
	// キーボードの取得
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
// 描画処理
//**************
void CTutorial::Draw(void)
{

}

//****************
// タスクのクリア
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
// コンストラクタ
//****************
CTutorialStateBase::CTutorialStateBase()
{
	m_pTutorial = NULL;
}

//****************
// デストラクタ
//****************
CTutorialStateBase::~CTutorialStateBase()
{

}
//******************************
// チュートリアルのポインタ設定
//******************************
void CTutorialStateBase::SetOwner(CTutorial* pTutorial)
{
	m_pTutorial = pTutorial;
}

//*********************************
//           前後の操作
//*********************************

//****************
// コンストラクタ
//****************
CFlontBackState::CFlontBackState()
{
	m_nClear = false;
	m_nCnt = 0;
}

//****************
// デストラクタ
//****************
CFlontBackState::~CFlontBackState()
{

}

//***************
// 初期化処理
//***************
void CFlontBackState::Init(void)
{

}

//***************
// 更新処理
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
// 終了処理
//***************
void CFlontBackState::Uninit(void)
{

}

//*********************************
//           左右の操作
//*********************************

//****************
// コンストラクタ
//****************
CRightLeftState::CRightLeftState()
{

}

//****************
// デストラクタ
//****************
CRightLeftState::~CRightLeftState()
{

}

//***************
// 初期化処理
//***************
void CRightLeftState::Init(void)
{
}

//***************
// 更新処理
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
// 終了処理
//***************
void CRightLeftState::Uninit(void)
{

}

//*********************************
//           回転の操作
//*********************************

//****************
// コンストラクタ
//****************
CRollState::CRollState()
{

}

//****************
// デストラクタ
//****************
CRollState::~CRollState()
{

}

//***************
// 初期化処理
//***************
void CRollState::Init(void)
{
}

//***************
// 更新処理
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
// 終了処理
//***************
void CRollState::Uninit(void)
{

}

//*********************************
//        ジャンプの操作
//*********************************

//****************
// コンストラクタ
//****************
CJumpCState::CJumpCState()
{

}

//****************
// デストラクタ
//****************
CJumpCState::~CJumpCState()
{

}

//***************
// 初期化処理
//***************
void CJumpCState::Init(void)
{
}

//***************
// 更新処理
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
// 終了処理
//***************
void CJumpCState::Uninit(void)
{

}

//*********************************
//    ジャンプキャンセルの操作
//*********************************

//****************
// コンストラクタ
//****************
CJumpCancelState::CJumpCancelState()
{

}

//****************
// デストラクタ
//****************
CJumpCancelState::~CJumpCancelState()
{

}

//***************
// 初期化処理
//***************
void CJumpCancelState::Init(void)
{
}

//***************
// 更新処理
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
// 終了処理
//***************
void CJumpCancelState::Uninit(void)
{

}

//*********************************
//    レールの操作
//*********************************

//****************
// コンストラクタ
//****************
CRailCState::CRailCState()
{

}

//****************
// デストラクタ
//****************
CRailCState::~CRailCState()
{

}

//***************
// 初期化処理
//***************
void CRailCState::Init(void)
{
}

//***************
// 更新処理
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
// 終了処理
//***************
void CRailCState::Uninit(void)
{

}

//*********************************
//    レールの操作
//*********************************

//****************
// コンストラクタ
//****************
CAttackCState::CAttackCState()
{

}

//****************
// デストラクタ
//****************
CAttackCState::~CAttackCState()
{

}

//***************
// 初期化処理
//***************
void CAttackCState::Init(void)
{
	CTutorialEnemy::Create(D3DXVECTOR3(0.2f,0.2f,0.2f));
}

//***************
// 更新処理
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
// 終了処理
//***************
void CAttackCState::Uninit(void)
{

}


//*********************************
//    フリーの操作
//*********************************

//****************
// コンストラクタ
//****************
CFreeState::CFreeState()
{

}

//****************
// デストラクタ
//****************
CFreeState::~CFreeState()
{

}

//***************
// 初期化処理
//***************
void CFreeState::Init(void)
{
}

//***************
// 更新処理
//***************
void CFreeState::Update(void)
{
	// 入力取得
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
// 終了処理
//***************
void CFreeState::Uninit(void)
{

}