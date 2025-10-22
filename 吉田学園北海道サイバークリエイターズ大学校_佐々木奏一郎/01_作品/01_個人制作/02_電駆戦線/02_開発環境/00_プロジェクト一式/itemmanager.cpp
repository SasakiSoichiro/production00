//**********************************
//
// �A�C�e���Ǘ����� [blurManager.cpp]
// Author:Sasaki Soichiro
//
//**********************************

//*******************
// �C���N���[�h
//*******************
#include "itemmanager.h"
#include "itemskill.h"

//*****************
// �R���X�g���N�^
//*****************
CItemManager::CItemManager()
{
	m_pItemSkill = NULL;
}

//*****************
// �f�X�g���N�^
//*****************
CItemManager::~CItemManager()
{

}

//*****************
// ����������
//*****************
HRESULT CItemManager::Init(void)
{
	m_pItemSkill = NULL;

	return S_OK;
}

//*****************
// �I������
//*****************
void CItemManager::Uninit(void)
{
	if (m_pItemSkill != NULL)
	{
		m_pItemSkill->Uninit();
		delete m_pItemSkill;
		m_pItemSkill = NULL;
	}

}

//*****************
// �X�V����
//*****************
void CItemManager::Update(void)
{
	if (m_pItemSkill != NULL)
	{// �X�V
		m_pItemSkill->Update();
	}
	else
	{

	}
}