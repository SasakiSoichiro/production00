//**********************************
//
// �u���[�Ǘ����� [blurManager.cpp]
// Author:Sasaki Soichiro
//
//**********************************

//*******************
// �C���N���[�h
//*******************
#include "blurManager.h"

//**********************
// �ÓI�����o�ϐ�������
//**********************
bool CBlurManager::m_bTime=false;
int CBlurManager::m_nTime=0;

//*****************
// �R���X�g���N�^
//*****************
CBlurManager::CBlurManager()
{
}

//*****************
// �f�X�g���N�^
//*****************
CBlurManager::~CBlurManager()
{
}

//*****************
// ����������
//*****************
HRESULT CBlurManager::Init(void)
{

	return S_OK;
}

//*****************
// �I������
//*****************
void CBlurManager::Uninit(void)
{
}

//*****************
// �X�V����
//*****************
void CBlurManager::Update(void)
{
	if (m_nTime > 0)
	{
		m_bTime = true;
	}
	else
	{
		m_bTime = false;
	}
	m_nTime--;
}