//**********************************
//
// マネージャ処理 [manager.cpp]
// Author:Sasaki Soichiro
//
//**********************************

//*******************
// インクルード
//*******************
#include "scene.h"
#include "game.h"
#include "renderer.h"
#include "object2D.h"
#include <time.h>
#include "debugproc.h"
#include "object3D.h"
#include "objectX.h"
#include "objectBillboard.h"
#include "mesh.h"
#include "manager.h"
#include "block.h"
#include "numbermulti.h"
#include "sound.h"
#include "blockManager.h"
#include "blurManager.h"
#include "input.h"
#include "fade.h"
#include "carBody.h"
#include "meshEdit.h"
#include "carManager.h"

//*******************
// 静的メンバ変数
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
// コンストラクタ
//*******************
CGame::CGame():CScene(CScene::MODE_GAME)
{
	m_nCnt = 0;
}

//*******************
// デストラクタ
//*******************
CGame::~CGame()
{
}

//*************
// 初期化処理
//*************
HRESULT CGame::Init(D3DXVECTOR3 pos)
{
	m_State = STATE_NONE;
	m_nCnt = 0;
	m_pBlockManager = new CBlockManager;

	// 地面
	m_pMesh = CMesh::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	CCar::Create(D3DXVECTOR3(0.1f, 50.0f, 0.1f));

	CMeshEdit::Create(D3DXVECTOR3(0.0f, 25.0f, 0.0f));
	
	return S_OK;
}

//*************
// 終了処理
//*************
void CGame::Uninit(void)
{
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
void CGame::Update(void)
{
	switch (m_State)
	{
	case STATE_NORMAL:
		break;
	case STATE_END:
		m_nCnt++;
		if (m_nCnt > 120)
		{
			m_nCnt = 0;
			CFade::Set(CScene::MODE_TITLE);
		}
		break;
	}
}

//**************
// 描画処理
//**************
void CGame::Draw(void)
{
	
}