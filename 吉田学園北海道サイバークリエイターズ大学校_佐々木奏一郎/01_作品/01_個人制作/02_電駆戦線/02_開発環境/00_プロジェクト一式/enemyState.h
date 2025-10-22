//**************************************
//
// �G�l�~�[��ԏ��� [enemyState.h]
// Author:Sasaki Soichiro
//
//**************************************
#ifndef _ENEMYSTATE_H_ // ���̃}�N����`������Ă��Ȃ�������
#define _ENEMYSTATE_H_ // ��d�C���N���[�h�h�~�̃}�N����`

//******************
// �C���N���[�h
//******************
#include "main.h"
#include "state.h"

class CEnemy;

//**************************************
// �G�l�~�[��p�̃X�e�[�g�̊��N���X
//**************************************
class CEnemyStateBase :public CStateBase
{
public:
	CEnemyStateBase();	// �R���X�g���N�^
	~CEnemyStateBase();	// �f�X�g���N�^
	void SetOwner(CEnemy* pEnemy);// �|�C���^�̐ݒ�
protected:
	CEnemy* m_pEnemy;// �G�l�~�[�ւ̃|�C���^
};

//****************
// �ҋ@���
//****************
class CNuetoralState :public CEnemyStateBase
{
public:
	CNuetoralState();// �R���X�g���N�^
	~CNuetoralState();// �f�X�g���N�^
	void Init(void);// ������
	void Update(void);// �X�V
	void Uninit(void);// �I��
};

//******************
// �Ǐ]���
//******************
class CChaseState :public CEnemyStateBase
{
public:
	CChaseState();		// �R���X�g���N�^
	~CChaseState();		// �f�X�g���N�^
	void Init(void);	// ������
	void Update(void);	// �X�V
	void Uninit(void);	// �I��
};

//******************
// �U�����
//******************
class CAttackState :public CEnemyStateBase
{
public:
	CAttackState();		// �R���X�g���N�^
	~CAttackState();	// �f�X�g���N�^
	void Init(void);	// ������
	void Update(void);	// �X�V
	void Uninit(void);	// �I��
};

//******************
// ������
//******************
class CHitState :public CEnemyStateBase
{
public:
	CHitState();		// �R���X�g���N�^
	~CHitState();		// �f�X�g���N�^
	void Init(void);	// ������
	void Update(void);	// �X�V
	void Uninit(void);	// �I��
private:
};

//******************
// ���񂾏��
//******************
class CDownState :public CEnemyStateBase
{
public:
	CDownState();		// �R���X�g���N�^
	~CDownState();		// �f�X�g���N�^
	void Init(void);	// ������
	void Update(void);	// �X�V
	void Uninit(void);	// �I��
private:
};


#endif