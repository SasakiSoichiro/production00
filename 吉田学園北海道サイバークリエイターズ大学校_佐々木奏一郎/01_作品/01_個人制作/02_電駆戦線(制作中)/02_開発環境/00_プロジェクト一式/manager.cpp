//**********************************
//
// マネージャ処理 [manager.cpp]
// Author:Sasaki Soichiro
//
//**********************************

//*******************
// インクルード
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

//*******************
// 静的メンバ変数
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
CObject3D* CManager::m_pObject3D = NULL;
CMesh* CManager::m_pMesh = NULL;
CPlayer* CManager::m_pPlayer = NULL;


//*******************
// コンストラクタ
//*******************
CManager::CManager()
{
}

//*******************
// デストラクタ
//*******************
CManager::~CManager()
{
}

//*************
// 初期化処理
//*************
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	// インスタンス生成
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
	;

	// 初期化処理
	if (FAILED(m_pRenderer->Init(hWnd, TRUE)))
	{//初期化処理が失敗した場合
		return-1;
	}
	// 初期化処理
	if (FAILED(m_pInputKeyboard->Init(hInstance, hWnd)))
	{//初期化処理が失敗した場合
		return-1;
	}
	// 初期化処理
	if (FAILED(m_pInputMouse->Init(hInstance, hWnd)))
	{//初期化処理が失敗した場合
		return-1;
	}
	// 初期化処理
	if (FAILED(m_pInputJoypad->Init(hInstance, hWnd)))
	{//初期化処理が失敗した場合
		return-1;
	}
	// 初期化処理
	if (FAILED(m_pSound->Init(hWnd)))
	{//初期化処理が失敗した場合
		return-1;
	}
	// 初期化処理
	if (FAILED(m_pTexture->Load()))
	{//初期化処理が失敗した場合
		return-1;
	}
	// 初期化処理
	if (FAILED(m_pXModel->Load()))
	{//初期化処理が失敗した場合
		return-1;
	}
	// 初期化処理
	m_pCamera->Init();
	m_pLight->Init();
	m_pDebugProc->Init();

	CScore::Create(D3DXVECTOR3(600.0f, 300.0f, 0.0f));
	CTimer::Create(D3DXVECTOR3(600.0f, 50.0f, 0.0f),120);
	CPause::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT/2, 0.0f));
	CLifeUI::Create(D3DXVECTOR3(170.0f, 80.0f, 0.0f));
	m_pPlayer=CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pMesh=CMesh::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	
	int nNumPoint = 8;
	D3DXVECTOR3 pos[8];
	for (int nCnt = 0; nCnt < nNumPoint; nCnt++)
	{
		float fAngle = D3DX_PI * 2.0f * nCnt / nNumPoint;
		pos[nCnt].x = cosf(fAngle) * 410.0f;
		pos[nCnt].y = 5.0f;
		pos[nCnt].z = sinf(fAngle) * 410.0f;
	}

	CRail*pRail=CRail::Create(pos[0], pos[1], pos[2], pos[3]);
	return S_OK;
}

//*************
// 終了処理
//*************
void CManager::Uninit(void)
{
	//終了処理
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

}

//*************
// 更新処理
//*************
void CManager::Update(void)
{
	if (CPause::GetPause() == false)
	{
		m_pRenderer->Update();
	}
	m_pInputKeyboard->Update();
	m_pInputMouse->Update();
	m_pInputJoypad->Update();
	m_pCamera->Update();
	if (m_pInputKeyboard->Trigger(DIK_F1) == true)
	{
		CDebugProc::SwitchDebug();
	}
	if (m_pInputKeyboard->Trigger(DIK_P) == true)
	{
		CPause::SwitchPause();
	}
	//if (0 >= CPlayer::GetNumAll())
	//{
	//	CPlayer::Create(D3DXVECTOR3(SCREEN_WIDTH/2, 500.0f, 0.0f));
	//}

	for (int nCntPriority = 0; nCntPriority < MAX_PRI; nCntPriority++)
	{
		int nNum = CObject::GetNumPriority(nCntPriority);
		CDebugProc::Print("描画%d番目の数:%d\n", nCntPriority, nNum);
	}
	 //デバッグ用
	{
		srand((unsigned int)time(NULL));
		if (m_pInputKeyboard->Trigger(DIK_F) == true)
		{
			for (int nCnt = 0; nCnt < 8; nCnt++)
			{
				float X = (float)(rand() % 100) - 50.0f;
				float Y = (float)(rand() % 100) - 50.0f;

				CPlayer::Create(D3DXVECTOR3(X, 50.0f, Y));
			}
		}
	}
}

//**************
// 描画処理
//**************
void CManager::Draw(void)
{
	m_pRenderer->Draw();
}