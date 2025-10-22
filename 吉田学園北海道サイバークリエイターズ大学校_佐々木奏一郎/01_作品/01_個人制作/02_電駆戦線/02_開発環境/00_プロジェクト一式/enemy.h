//**************************************
//
// �G�l�~�[���� [enemy.h]
// Author:Sasaki Soichiro
//
//**************************************
#ifndef _ENEMY_H_ // ���̃}�N����`������Ă��Ȃ�������
#define _ENEMY_H_ // ��d�C���N���[�h�h�~�̃}�N����`

//******************
// �C���N���[�h
//******************
#include "main.h"
#include "objectX.h"
#include "motion.h"
#include "enemyState.h"
#include "state.h"

class CEnemyLifeManager;

//********************
// �G�l�~�[�N���X
//********************
class CEnemy :public CObject
{
public:
	// �G�̎��
	typedef enum
	{
		TYPE_SPIDER=0,	// �w偌^
		TYPE_FANMOTOR,	// ��@�^
		TYPE_CRAWLER,	// �N���[���[�^
		TYPE_MAX
	}TYPE;

	// ���
	typedef enum
	{
		STATE_NONE=0,	// �����Ȃ�
		STATE_MAX
	}STATE;

	// ���[�V����
	typedef enum
	{
		MOTION_NUETORAL = 0,// �ʏ���
		MOTION_MOVE,		// �����Ă�����
		MOTION_ACTION1,		// �U�����1
		MOTION_ACTION2,		// �U�����2
		MOTION_DIE,			// ���ʏ��
		MOTION_MAX
	}MOTION;

	CEnemy(int nPriority = 4);				// �R���X�g���N�^
	~CEnemy();								// �f�X�g���N�^
	static CEnemy* Create(D3DXVECTOR3 pos,int nType);	// �C���X�^���X����
	HRESULT Init(D3DXVECTOR3 pos);	// ������
	void Uninit(void);				// �I��
	void Update(void);				// �X�V
	void Draw(void);				// �`��
	void SetPos(D3DXVECTOR3 pos);	// �ʒu
	void SetRot(D3DXVECTOR3 rot);	// ����
	void SetSpeed(float speed) { m_speed = speed; }		// ���x
	void SetState(STATE state) { m_State = state; }		// ��Ԃ̐ݒ�
	void SetLife(int nLife) { m_nLife = nLife; }		// ���C�t�̐ݒ�
	D3DXVECTOR3 GetPos(void) { return m_pos; }			// �ʒu���̎擾
	D3DXVECTOR3 GetRot(void) { return m_rot; }			// �������̎擾
	float GetSpeed(void) { return m_speed; }			// ���x���̎擾
	STATE GetState(void) { return m_State; }			// ��ԏ��̎擾
	CMotion*GetMotion(void) { return m_pMotion; }		// ���[�V�������̎擾
	CModel* GetModel(int nIdx) { return m_apModel[nIdx]; }// ���f�����̎擾
	int GetLife(void) { return m_nLife; }				// ���C�t���̎擾
	static int GetNumAll(void) { return m_nNumAll; }	// ���݂̑����̎擾
	void LoadMotion(const char* pMotionScript);			// ���[�V�����e�L�X�g��ǂݍ���
	void ChangeState(CEnemyStateBase* pState);			// ��Ԃ����ւ���
	void SetMotion(int nType) { m_pMotion->SetMotion(nType); }// ���[�V�����̐ݒ�
	bool Distance(float fDistance);// �v���C���[�Ƃ̋���
	virtual bool Chase(void) = 0;		// �`�F�C�X��Ԃւ̏���
	virtual bool Attack(void) = 0;		// �U����Ԃւ̏���
	virtual bool Nuetoral(void) = 0;	// �ʏ��Ԃւ̏���
	virtual bool Hit(void) = 0;			// �����Ԃւ̏���
	virtual bool AttackUpdate(void) = 0;// �U���̍X�V�ւ̏���
private:
	D3DXVECTOR3 m_pos;		// �ʒu
	D3DXVECTOR3 m_oldPos;	// �O�t���[���̈ʒu
	D3DXVECTOR3 m_move;		// ��������
	D3DXVECTOR3 m_rot;		// ����
	D3DXVECTOR3 m_rotDest;	// �ڕW�̌���
	D3DXMATRIX m_mtxWorld;	// ���[���h�}�g���b�N�X
	D3DXVECTOR3 m_vecF;		// �O�x�N�g��
	D3DXVECTOR3 m_vecR;		// �E�x�N�g��
	D3DXVECTOR3 m_vecU;		// ��x�N�g��
	float m_speed;			// ���x
	float m_fAngle;			// ����
	int m_nLife;			// ���C�t
	int m_nIdxXFile;		// �g�����f���̔ԍ�
	STATE m_State;			// ���
	CMotion* m_pMotion;		// ���[�V�����ւ̃|�C���^
	CModel* m_apModel[15];	// ���f��(�p�[�c)�ւ̃|�C���^
	int m_nNumModel;		// �g���Ă��郂�f����
	CStateMachine* m_Machine;// �X�e�[�g�}�V���ւ̃|�C���^
	static int m_nNumAll;	// ���݂̑���
	int m_nType;			// ���
	CEnemyLifeManager* m_pLifeManager;// ���C�t�̃}�l�[�W���[
	static constexpr int initLife = 4;// �̗͂̏�����
};

#endif