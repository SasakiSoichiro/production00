//**************************************
//
// ��ԊǗ����� [state.cpp]
// Author:Sasaki Soichiro
//
//**************************************
//******************
// �C���N���[�h
//******************
#include "state.h"

//****************
// �R���X�g���N�^
//****************
CStateMachine::CStateMachine()
{
	m_pNowState = NULL;
}

//****************
// �f�X�g���N�^
//****************
CStateMachine::~CStateMachine()
{
}

//********************
// �X�e�[�g��ύX����
//********************
void CStateMachine::ChangeState(CStateBase* pNewState)
{
	if (m_pNowState != NULL)
	{// NULL����Ȃ�������
		
		m_pNowState->Uninit();	// �I��
		delete m_pNowState;		// ���
		m_pNowState = NULL;		// NULL����
	}
	// �V�����X�e�[�g���Z�b�g����
	m_pNowState = pNewState;

	// �V�����X�e�[�g���J�n����
	m_pNowState->Init();
}

//********************
// �I������
//********************
void CStateMachine::Uninit(void)
{
	if (m_pNowState != NULL)
	{// NULL����Ȃ�������

		m_pNowState->Uninit();	// �I��
		delete m_pNowState;		// ���
		m_pNowState = NULL;		// NULL����
	}
}

//**************
// �X�V����
//**************
void CStateMachine::Update(void)
{
	if (m_pNowState != NULL)
	{//NULL����Ȃ�������
		m_pNowState->Update();	// �X�V
	}
}