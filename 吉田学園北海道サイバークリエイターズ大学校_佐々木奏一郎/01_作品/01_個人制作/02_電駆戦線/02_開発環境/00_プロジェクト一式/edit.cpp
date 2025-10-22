//**********************************
//
// エディット処理 [title.cpp]
// Author:Sasaki Soichiro
//
//**********************************

//*******************
// インクルード
//*******************
#include "scene.h"
#include "edit.h"
#include "input.h"
#include "camera.h"
#include "manager.h"
#include "stand.h"
#include "editcamera.h"
#include "mesh.h"
#include "editmesh.h"
#include "block.h"

//**********************
// 静的メンバ変数初期化
//**********************
CEditCamera* CEdit::m_pEditCamera=NULL;
CMesh* CEdit::m_pMesh = NULL;
CEditMesh* CEdit::m_pEditMesh;

//*******************
// コンストラクタ
//*******************
CEdit::CEdit() :CScene(CScene::MODE_EDIT)
{
}

//*******************
// デストラクタ
//*******************
CEdit::~CEdit()
{
}

//*************
// 初期化処理
//*************
HRESULT CEdit::Init(D3DXVECTOR3 pos)
{
	m_pEditCamera = new CEditCamera;
	CEditMesh::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pEditCamera->Init();
	m_pMesh = CMesh::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	CStand::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	return S_OK;
}

//*************
// 終了処理
//*************
void CEdit::Uninit(void)
{
	if (m_pEditCamera != NULL)
	{
		m_pEditCamera->Uninit();
		delete m_pEditCamera;
		m_pEditCamera = NULL;
	}

	CObject::Release();
}

//*************
// 更新処理
//*************
void CEdit::Update(void)
{
	m_pEditCamera->Update();
}

//**************
// 描画処理
//**************
void CEdit::Draw(void)
{

}