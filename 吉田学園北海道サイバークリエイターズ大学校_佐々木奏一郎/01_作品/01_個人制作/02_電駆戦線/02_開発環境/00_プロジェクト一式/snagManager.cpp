//**********************************
//
// ��Q���Ǘ����� [blurManager.cpp]
// Author:Sasaki Soichiro
//
//**********************************

//*******************
// �C���N���[�h
//*******************
#include "snagManager.h"
#include "fence.h"
#include "jem.h"


//*****************
// �R���X�g���N�^
//*****************
CSnagManager::CSnagManager()
{
	m_nFenceTime = 0;
	m_nJemTime = 0;
}

//*****************
// �f�X�g���N�^
//*****************
CSnagManager::~CSnagManager()
{
}

//*****************
// ����������
//*****************
HRESULT CSnagManager::Init(void)
{
	m_nFenceTime = FenceCool;
	m_nJemTime = JemCool;

	return S_OK;
}

//*****************
// �I������
//*****************
void CSnagManager::Uninit(void)
{
}

//*****************
// �X�V����
//*****************
void CSnagManager::Update(void)
{
	D3DXVECTOR3 pos=D3DXVECTOR3(0.1f,0.0f,0.1f);
	if (m_nFenceTime<0)
	{
		CFence::Create(pos);
		m_nFenceTime = FenceCool;
	}
	if (m_nJemTime<0)
	{
		float random = rand() % 100 * 0.1f;
		pos.x= sinf(random) * 350.0f;
		pos.y = 40.0f;
		pos.z= cosf(random) * 350.0f;
		CJem::Create(pos);
		m_nJemTime = JemCool;
	}
	m_nFenceTime--;
	m_nJemTime--;
}