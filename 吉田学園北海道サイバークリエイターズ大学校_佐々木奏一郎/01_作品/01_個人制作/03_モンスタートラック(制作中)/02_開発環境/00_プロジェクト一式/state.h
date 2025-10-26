//**************************************
//
// ��ԊǗ����� [state.h]
// Author:Sasaki Soichiro
//
//**************************************
#ifndef _STATE_H_ // ���̃}�N����`������Ă��Ȃ�������
#define _STATE_H_ // ��d�C���N���[�h�h�~�̃}�N����`

//******************
// �C���N���[�h
//******************
#include "main.h"
#include <iostream>

//********************
// �X�e�[�g���N���X
//********************
class CStateBase
{
public:
	CStateBase(){}			// �R���X�g���N�^
	virtual ~CStateBase(){}	// �f�X�g���N�^
	virtual void Init(){}	// ������
	virtual void Update(){}	// �X�V
	virtual void Uninit(){}	// �I��
};

//*********************
// �X�e�[�g�Ǘ��N���X
//*********************
class CStateMachine
{
public:
	CStateMachine();// �R���X�g���N�^
	~CStateMachine();// �f�X�g���N�^
	void ChangeState(CStateBase* pNewState);// ��Ԑ؂�ւ�
	void Uninit(void);						// �I��
	void Update(void);						// �X�V
private:
	CStateBase* m_pNowState;	// �X�e�[�g�x�[�X�ւ̃|�C���^
};
#endif