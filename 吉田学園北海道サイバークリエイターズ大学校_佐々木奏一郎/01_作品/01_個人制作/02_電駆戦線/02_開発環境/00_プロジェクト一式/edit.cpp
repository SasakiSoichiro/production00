//**********************************
//
// �G�f�B�b�g���� [title.cpp]
// Author:Sasaki Soichiro
//
//**********************************

//*******************
// �C���N���[�h
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
// �ÓI�����o�ϐ�������
//**********************
CEditCamera* CEdit::m_pEditCamera=NULL;
CMesh* CEdit::m_pMesh = NULL;
CEditMesh* CEdit::m_pEditMesh;

//*******************
// �R���X�g���N�^
//*******************
CEdit::CEdit() :CScene(CScene::MODE_EDIT)
{
}

//*******************
// �f�X�g���N�^
//*******************
CEdit::~CEdit()
{
}

//*************
// ����������
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
// �I������
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
// �X�V����
//*************
void CEdit::Update(void)
{
	m_pEditCamera->Update();
}

//**************
// �`�揈��
//**************
void CEdit::Draw(void)
{

}