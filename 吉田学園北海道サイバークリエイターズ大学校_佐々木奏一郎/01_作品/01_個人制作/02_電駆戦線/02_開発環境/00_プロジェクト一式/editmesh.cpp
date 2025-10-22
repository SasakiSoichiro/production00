//**********************************
//
// ���b�V���̕ҏW���� [editmesh.cpp]
// Author:Sasaki Soichiro
//
//**********************************

//*******************
// �C���N���[�h
//*******************
#include "editmesh.h"
#include "input.h"
#include "manager.h"
#include "mesh.h"
#include "edit.h"
#include "block.h"
#include "model.h"

//*******************
// �ÓI�����o�ϐ�
//*******************
CModel* CEditMesh::m_pModel = NULL;

//*******************
// �R���X�g���N�^
//*******************
CEditMesh::CEditMesh()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_caldera = 0.0f;
}

//*******************
// �f�X�g���N�^
//*******************
CEditMesh::~CEditMesh()
{
}

CEditMesh* CEditMesh::Create(D3DXVECTOR3 pos)
{
	CEditMesh* pEditMesh;
	int nNum = CObject::GetNumAll();
	if (nNum < MAX_OBJ - 1)
	{// �I�u�W�F�N�g���ő吔�ɒB���Ă��Ȃ��ꍇ

		pEditMesh = new CEditMesh;	// �C���X�^���X����
		pEditMesh->Init(pos);		// ������
		return pEditMesh;			// ����n��
	}

	// �I�u�W�F�N�g���ő吔�ɒB���Ă����ꍇ
	return NULL;	// NULL��Ԃ�
}

//*************
// ����������
//*************
HRESULT CEditMesh::Init(D3DXVECTOR3 pos)
{
	m_pModel = CModel::Create(pos,"data\\MODEL\\circle.x");
	m_pos = pos;
	m_caldera = 1.0f;

	return S_OK;
}

//*************
// �I������
//*************
void CEditMesh::Uninit(void)
{
	if (m_pModel != NULL)
	{
		m_pModel->Uninit();
		delete m_pModel;
		m_pModel = NULL;
	}
	CObject::Release();
}

//*************
// �X�V����
//*************
void CEditMesh::Update(void)
{
	CInputKeyboard* pInputKeyboard = CManager::GetCInputKeyboard();
	CMesh* pMesh = CEdit::GetMesh();
	D3DXVECTOR3 size = m_pModel->GetSize();

	if (pInputKeyboard->GetPress(DIK_W) == true)
	{
		m_pos.z -= 2.0f;
	}
	else if (pInputKeyboard->GetPress(DIK_S) == true)
	{
		m_pos.z += 2.0f;
	}
	else if (pInputKeyboard->GetPress(DIK_A) == true)
	{
		m_pos.x -= 2.0f;
	}
	else if (pInputKeyboard->GetPress(DIK_D) == true)
	{
		m_pos.x += 2.0f;
	}

	if (pInputKeyboard->GetPress(DIK_F6) == true)
	{
		pMesh->SetCaldera(m_caldera);
	}
	if (pInputKeyboard->GetPress(DIK_SPACE) == true)
	{
		pMesh->MoveY(m_pos);
	}
	if (pInputKeyboard->GetPress(DIK_T) == true)
	{
		m_caldera += 0.02f;
		m_caldera += 0.02f;

	}
	else if (pInputKeyboard->GetPress(DIK_G) == true)
	{
		size.x -= 0.02f;
		size.z -= 0.02f;
	}
	if (pInputKeyboard->Trigger(DIK_F9) == true)
	{
		pMesh->Save();
	}


	size.x = m_caldera;
	size.z = m_caldera;

	m_pModel->SetPos(m_pos);
	m_pModel->SetSize(size);
}

//************
// �`�揈��
//************
void CEditMesh::Draw(void)
{
	m_pModel->Draw();
}