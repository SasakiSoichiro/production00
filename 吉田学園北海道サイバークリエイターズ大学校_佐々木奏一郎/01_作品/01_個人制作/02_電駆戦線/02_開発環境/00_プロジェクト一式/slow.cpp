//**********************************
//
// �R���{���� [combo.cpp]
// Author:Sasaki Soichiro
//
//**********************************

//*******************
// �C���N���[�h
//*******************
#include "slow.h"

//****************
// �}�N����`
//****************
#define SLOW (4)

//*****************
// �ÓI�����o�ϐ�
//*****************
float CSlow::m_fMulti=0.0f;
float CSlow::m_fDivi=0.0f;
int CSlow::m_nMulti=0;
int CSlow::m_nDivi=0;
int CSlow::m_nTime=0;



//*****************
// �R���X�g���N�^
//*****************
CSlow::CSlow()
{
}

//*****************
// �f�X�g���N�^
//*****************
CSlow::~CSlow()
{
}

//*****************
// ����������
//*****************
HRESULT CSlow::Init(void)
{
	m_fMulti = 1.0f;
	m_fDivi = 1.0f;
	m_nMulti = 1;
	m_nDivi = 1;
	m_nTime = 0;

	return S_OK;
}

//*****************
// �I������
//*****************
void CSlow::Uninit(void)
{
}

//*****************
// �X�V����
//*****************
void CSlow::Update(void)
{
	if (m_nTime > 0)
	{
		m_fMulti = (int)SLOW;
		m_fDivi = 1.0 / SLOW;
		m_nMulti = SLOW;
	}
	else
	{
		m_fMulti = 1.0f;
		m_fDivi = 1.0f;
		m_nMulti = 1;
	}
	m_nTime--;
}

//*****************
// �X���[��������
//*****************
void CSlow::Set(int nTime)
{
	m_nTime = nTime;
}