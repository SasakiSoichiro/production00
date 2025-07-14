//**********************************
//
// �I�u�W�F�N�g���� [object.cpp]
// Author:Sasaki Soichiro
//
//**********************************

//*******************
// �C���N���[�h
//*******************
#include "object.h"
#include "renderer.h"
#include "debugproc.h"
#include "camera.h"
#include "manager.h"

//***********************
// �ÓI�����o�ϐ�������
//***********************
int CObject::m_nNumAll = 0;
CObject* CObject::m_apObject[MAX_PRI][MAX_OBJ] = {};
int CObject::m_nNumPriority[MAX_PRI] = {};

//******************
// �R���X�g���N�^
//******************
CObject::CObject(int nPriority)
{

	for (int nCntObject = 0; nCntObject < MAX_OBJ; nCntObject++)
	{
		if (m_apObject[nPriority][nCntObject] == NULL)
		{// NULL��������
			m_apObject[nPriority][nCntObject] = this;	// �������g����
			m_nID = nCntObject;							// �������g��ID��ۑ�
			m_nNumAll++;								// �������J�E���g�A�b�v
			m_nNumPriority[nPriority]++;				// �`�揇���Ƃ̑����𑫂�
			break;
		}
	}
	m_nPriority = nPriority;// �`�揇���蓖��
	m_type = TYPE_NONE;		// �^�C�v�ݒ�
}
//******************
// �f�X�g���N�^
//******************
CObject::~CObject()
{
}

//******************
// �S�Ă̍X�V
//******************
void CObject::UpdateAll(void)
{
	for (int nCntPriority = 0; nCntPriority < MAX_PRI; nCntPriority++)
	{
		for (int nCntObject = 0; nCntObject < MAX_OBJ; nCntObject++)
		{
			if (m_apObject[nCntPriority][nCntObject] != NULL)
			{// NULL����Ȃ�������
				m_apObject[nCntPriority][nCntObject]->Update();// �X�V
			}
		}

	}
}

//******************
// �S�Ă̕`��
//******************
void CObject::DrawAll(void)
{
	CCamera* pCamera = CManager::GetCCamera();	// �J�������擾
	pCamera->SetCamera();						// �J������ݒ�

	for (int nCntPriority = 0; nCntPriority < MAX_PRI; nCntPriority++)
	{
		for (int nCntObject = 0; nCntObject < MAX_OBJ; nCntObject++)
		{
			if (m_apObject[nCntPriority][nCntObject] != NULL)
			{// NULL����Ȃ�������
				m_apObject[nCntPriority][nCntObject]->Draw();// �`��
			}
		}
	}
}

//******************
// �S�Ă̏I��
//******************
void CObject::ReleaseAll(void)
{
	for (int nCntPriority = 0; nCntPriority < MAX_PRI; nCntPriority++)
	{
		for (int nCntObject = 0; nCntObject < MAX_OBJ; nCntObject++)
		{
			if (m_apObject[nCntPriority][nCntObject] != NULL)
			{// NULL����Ȃ�������
				m_apObject[nCntPriority][nCntObject]->Uninit();// �I��
			}
		}
	}
}

//******************
// �I��
//******************
void CObject::Release(void)
{
	int nID = this->m_nID;				// ������ID����
	int nPriority = this->m_nPriority;	// �����̕`�揇�����蓖��

	if (m_apObject[nPriority][nID] != NULL)
	{// �I�u�W�F�N�g��NULL����Ȃ�������

		delete m_apObject[nPriority][nID];	// �f���[�g
		m_apObject[nPriority][nID] = NULL;	// NULL����
		m_nNumAll--;						// �������J�E���g�_�E��
		m_nNumPriority[nPriority]--;		// �`�揇���Ƃ̑��������炷
	}
}

//******************
// �^�C�v�̊��蓖��
//******************
void CObject::SetType(CObject::TYPE type)
{
	m_type = type;// �^�C�v��ݒ�
}