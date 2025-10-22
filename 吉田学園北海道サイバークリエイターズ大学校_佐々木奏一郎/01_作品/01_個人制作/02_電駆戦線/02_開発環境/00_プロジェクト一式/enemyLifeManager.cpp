//***************************************************
//
// �G�̗̑̓}�l�[�W���[���� [enemyLifeManager.cpp]
// Author:Sasaki Soichiro
//
//***************************************************

//*******************
// �C���N���[�h
//*******************
#include "enemyLifeManager.h"
#include "enemyLifeUI.h"
#include "input.h"
#include "manager.h"


//*****************
// �R���X�g���N�^
//*****************
CEnemyLifeManager::CEnemyLifeManager(int nPriority) :CObject(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	for (int nCnt = 0; nCnt < 5; nCnt++)
	{
		m_pLifeUI[nCnt] = NULL;
	}

	m_nLife = 0;
	m_nOffsetLife = 0;
}

//*****************
// �f�X�g���N�^
//*****************
CEnemyLifeManager::~CEnemyLifeManager()
{
}

//******************
// �C���X�^���X����
//*******************
CEnemyLifeManager* CEnemyLifeManager::Create(D3DXVECTOR3 pos, int nLife)
{
	CEnemyLifeManager* pLifeManager;

	// ���݂̃I�u�W�F�N�g�̑����擾
	int nNum = CObject::GetNumAll();
	if (nNum < MAX_OBJ - 1)
	{// �I�u�W�F�N�g���ő吔�ɒB���Ă��Ȃ��ꍇ

		// �C���X�^���X����
		pLifeManager = new CEnemyLifeManager;
		pLifeManager->m_nLife = nLife;
		pLifeManager->m_nOffsetLife = nLife;
		// ������
		pLifeManager->Init(pos);

		return pLifeManager;
	}

	return NULL;
}


//*****************
// ����������
//*****************
HRESULT CEnemyLifeManager::Init(D3DXVECTOR3 pos)
{
	// HP�������̃T�C�Y�v�Z
	float fullSize = size * m_nLife;
	float halfSize = fullSize * 0.5f;

	for (int nCnt = 0; nCnt < m_nLife; nCnt++)
	{// �C���X�^���X����
		m_pLifeUI[nCnt] = CEnemyLifeUI::Create(D3DXVECTOR3(pos.x, pos.y, pos.z),
			D3DXVECTOR2((size * nCnt) - halfSize, 0.0f), nCnt + 1);
	}
	return S_OK;
}

//*****************
// �I������
//*****************
void CEnemyLifeManager::Uninit(void)
{
	for (int nCnt = 0; nCnt < m_nOffsetLife; nCnt++)
	{
		if (m_pLifeUI[nCnt] != NULL)
		{
			m_pLifeUI[nCnt]->Uninit();
		}
	}
	CObject::Release();
}

//*****************
// �X�V����
//*****************
void CEnemyLifeManager::Update(void)
{
	// UI�̏ꏊ�Ƒ̗͂̐ݒ�
	for (int nCnt = 0; nCnt < m_nOffsetLife; nCnt++)
	{
		if (m_nLife > 0)
		{
			m_pLifeUI[nCnt]->SetPos(m_pos);
			m_pLifeUI[nCnt]->SetLife(m_nLife);
		}
	}
}

//*****************
// �`�揈��
//*****************
void CEnemyLifeManager::Draw(void)
{

}

//*****************
// HP�̐ݒ�
//*****************
void CEnemyLifeManager::SetLife(int nLife)
{
	m_nLife = nLife;
}