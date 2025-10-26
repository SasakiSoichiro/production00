//=============================================================================
//
// �I�u�W�F�N�g���� [object.cpp]
// Author Sasaki Soichiro
//
//=============================================================================

//*******************
// �C���N���[�h
//*******************
#include "object.h"
#include "renderer.h"
#include "debugproc.h"
#include "camera.h"
#include "manager.h"

//**********************
// �ÓI�����o�ϐ�������
//**********************
int CObject::m_nNumAll = 0;
int CObject::m_nNumPriority[MAX_PRI] = {};
CObject* CObject::m_apTop[MAX_PRI] = {};
CObject* CObject::m_apCur[MAX_PRI] = {};

//*****************
// �R���X�g���N�^
//*****************
CObject::CObject(int nPriority)
{

	if (m_apTop[nPriority]== NULL)
	{
		m_apTop[nPriority] = this;		// �������g����
		m_apCur[nPriority] = this;
		m_pPrev = NULL;
		m_pNext = NULL;
	}
	else
	{
		m_pPrev = m_apCur[nPriority];
		m_apCur[nPriority]->m_pNext = this;
		m_pNext = NULL;
		m_apCur[nPriority] = this;
	}
	m_nPriority = nPriority;
	m_type = TYPE_NONE;
	m_nNumAll++;					// �������J�E���g�A�b�v
	m_nNumPriority[nPriority]++;
	m_bDeath = false;
}
//*****************
// �f�X�g���N�^
//*****************
CObject::~CObject()
{

}

//***************
// �S�Ă̍X�V
//***************
void CObject::UpdateAll(void)
{
	for (int nCntPriority = 0; nCntPriority < MAX_PRI; nCntPriority++)
	{
		CObject* pObject = m_apTop[nCntPriority];
		while (pObject != NULL)
		{
			CObject* pObjectNext = pObject->m_pNext;

			// �X�V����
			pObject->Update();

			pObject = pObjectNext;// ���̃I�u�W�F�N�g����
		}

		pObject = m_apTop[nCntPriority];
		while (pObject != NULL)
		{
			CObject* pObjectNext = pObject->m_pNext;
			if (pObject != NULL && pObject->m_bDeath == true)
			{
				Destroy(pObject);
			}
			pObject = pObjectNext;// ���̃I�u�W�F�N�g����
		}
	}
}

//****************
// �S�Ă̕`��
//****************
void CObject::DrawAll(void)
{
	CCamera* pCamera = CManager::GetCCamera();
	pCamera->SetCamera();
	for (int nCntPriority = 0; nCntPriority < MAX_PRI; nCntPriority++)
	{
		CObject* pObject = m_apTop[nCntPriority];
		while (pObject != NULL)
		{
			CObject* pObjectNext = pObject->m_pNext;

			// �X�V����
			pObject->Draw();
			pObject = pObjectNext;// ���̃I�u�W�F�N�g����
		}

	}
}

//***************
// �S�Ă̏I��
//***************
void CObject::ReleaseAll(void)
{
	for (int nCntPriority = 0; nCntPriority < MAX_PRI; nCntPriority++)
	{
		CObject* pObject = m_apTop[nCntPriority];
		while (pObject != NULL)
		{
			CObject* pObjectNext = pObject->m_pNext;

			// �X�V����
			pObject->Uninit();
			pObject = pObjectNext;// ���̃I�u�W�F�N�g����
		}
		pObject = m_apTop[nCntPriority];
		while (pObject != NULL)
		{
			CObject* pObjectNext = pObject->m_pNext;
			if (pObject != NULL && pObject->m_bDeath == true)
			{
				int nPriority = pObject->m_nPriority;
				//CObject* pNext = m_pNext;
				//CObject* pPrev = m_pPrev;
				if (pObject->m_pNext != NULL && pObject->m_pPrev != NULL)
				{
					pObject->m_pPrev->m_pNext = pObject->m_pNext;
					pObject->m_pNext->m_pPrev = pObject->m_pPrev;
				}
				else if (m_apTop[nPriority]->m_pPrev == NULL && pObject->m_pNext != NULL)
				{
					m_apTop[nPriority] = pObject->m_pNext;
					pObject->m_pNext->m_pPrev = NULL;
				}
				else if (m_apCur[nPriority]->m_pNext == NULL && pObject->m_pPrev != NULL)
				{
					m_apCur[nPriority] = pObject->m_pPrev;
					pObject->m_pPrev->m_pNext = NULL;
				}
				if (m_apTop[nPriority] == pObject)
				{
					m_apTop[nPriority] = NULL;
				}
				pObject->m_pNext = NULL;
				pObject->m_pPrev = NULL;
				delete pObject;
				pObject = nullptr;
				m_nNumAll--;		// �������J�E���g�_�E��
				m_nNumPriority[nPriority]--;
			}
			pObject = pObjectNext;// ���̃I�u�W�F�N�g����
		}

	}
}

//**************
// �I��
//**************
void CObject::Release(void)
{
	m_bDeath = true;
}

//**************
// ��ނ�ݒ�
//**************
void CObject::SetType(CObject::TYPE type)
{
	m_type = type;
}

//*******************
// �I�u�W�F�N�g����
//*******************
void CObject::Destroy(CObject* pObject)
{
	int nPriority = pObject->m_nPriority;
	if (pObject->m_pNext != nullptr && pObject->m_pPrev != nullptr)
	{
		pObject->m_pPrev->m_pNext = pObject->m_pNext;
		pObject->m_pNext->m_pPrev = pObject->m_pPrev;
	}
	else if (pObject->m_pPrev == nullptr && pObject->m_pNext != nullptr)
	{
		m_apTop[nPriority] = pObject->m_pNext;
		pObject->m_pNext->m_pPrev = NULL;
	}
	else if (pObject->m_pNext == nullptr && pObject->m_pPrev != nullptr)
	{
		m_apCur[nPriority] = pObject->m_pPrev;
		pObject->m_pPrev->m_pNext = NULL;
	}
	else
	{
		m_apCur[nPriority] = nullptr;
		m_apTop[nPriority] = nullptr;
	}

	//if (m_apTop[nPriority] == pObject)
	//{
	//	m_apTop[nPriority] = NULL;
	//}

	m_nNumAll--;		// �������J�E���g�_�E��
	pObject->m_pNext = NULL;
	pObject->m_pPrev = NULL;
	delete pObject;
	m_nNumPriority[nPriority]--;

}