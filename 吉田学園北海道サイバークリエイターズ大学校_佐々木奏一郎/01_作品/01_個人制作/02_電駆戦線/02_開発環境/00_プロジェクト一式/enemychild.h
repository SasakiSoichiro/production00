//**************************************
//
// �q�G�l�~�[���� [enemychild.h]
// Author:Sasaki Soichiro
//
//**************************************
#ifndef _ENEMYCHILD_H_ // ���̃}�N����`������Ă��Ȃ�������
#define _ENEMYCHILD_H_ // ��d�C���N���[�h�h�~�̃}�N����`

//******************
// �C���N���[�h
//******************
#include "main.h"
#include "enemy.h"

//********************
// �w偌^�̓G�N���X
//********************
class CSpiderEnemy :public CEnemy
{
public:
	CSpiderEnemy();		// �R���X�g���N�^
	~CSpiderEnemy();	// �f�X�g���N�^
	HRESULT Init(D3DXVECTOR3 pos);	// ������
	void Uninit(void);				// �I��
	void Update(void);				// �X�V
	void Draw(void);				// �`��
	bool Chase(void);				// �ǂ����������
	bool Attack(void);				// �U���������
	bool Nuetoral(void);			// �ҋ@�������
	bool Hit(void);					// �U������
	bool AttackUpdate(void);		// �U���̍X�V
private:
	int m_fAttackFps;				// �U�����鎞��
	bool m_bAttackSound;			// �T�E���h�����̂ݖ炷
	bool m_bAngle;					// ���������
	int m_nHitCool;					// �U���N�[���^�C��

	static constexpr float SPEED = 1.0f;
	static constexpr int hitCool = 30;
	static constexpr float Range = 55.0f;
};

//********************
// ��@�^�̓G�N���X
//********************
class CFanmotorEnemy :public CEnemy
{
public:
	CFanmotorEnemy();	// �R���X�g���N�^
	~CFanmotorEnemy();	// �f�X�g���N�^
	HRESULT Init(D3DXVECTOR3 pos);	// ������
	void Uninit(void);				// �I��
	void Update(void);				// �X�V
	void Draw(void);				// �`��
	bool Chase(void);		// �ǂ����������
	bool Attack(void);		// �U���������
	bool Nuetoral(void);	// �ҋ@�������
	bool Hit(void);			// �U������
	bool AttackUpdate(void);// �U���̍X�V
private:
	int m_fAttackFps;		// �U�����鎞��
	bool m_bAttackSound;	// �T�E���h�����̂ݖ炷
	int m_nHitCool;			// �U���N�[���^�C��
	
	static constexpr float SPEED = 1.2f;
	static constexpr int hitCool = 30;
	static constexpr float Range = 30.0f;
};
#endif