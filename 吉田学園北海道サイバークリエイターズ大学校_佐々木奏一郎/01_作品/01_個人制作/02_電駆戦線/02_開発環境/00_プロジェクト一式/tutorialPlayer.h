//**************************************************
//
// �`���[�g���A���v���C���[���� [tutorialPlayer.h]
// Author:Sasaki Soichiro
//
//***************************************************
#ifndef _TUTORIALPLAYER_H_ // ���̃}�N����`������Ă��Ȃ�������
#define _TUTORIALPLAYER_H_ // ��d�C���N���[�h�h�~�̃}�N����`

//******************
// �C���N���[�h
//******************
#include "main.h"
#include "object.h"
#include "state.h"


class CTutorialPlayerStateBase;
class COrbit;
class CLifeUI;
class CShadowS;
class CMotion;
class CModel;
class CItemManager;

//********************
// �v���C���[�N���X
//********************
class CTutorialPlayer :public CObject
{
public:
	// ���
	typedef enum
	{
		STATE_NONE = 0,		// �����Ȃ�
		STATE_JUMP,			// �W�����v
		STATE_RAIL,			// ���[��
		STATE_RAILCHANGE,	// ���[����芷��
		STATE_LANDING,		// ���n
		STATE_INOPERABLE,	// ����s�\���
	}STATE;

	// ���[�V����
	typedef enum
	{
		MOTION_NUETORAL = 0,	// �ʏ�
		MOTION_FLONT,		// �O
		MOTION_BACK,		// ���
		MOTION_LF,			// ���O
		MOTION_LB,			// �����
		MOTION_RF,			// �E�O
		MOTION_RB,			// �E���
		MOTION_FB,			// ����]
		MOTION_BF,			// �E��]
		MOTION_DIE,			// ��
		MOTION_RAILL,		// ���[�����̃��[�V����(��)
		MOTION_RAILR,		// ���[�����̃��[�V����(�E)
		MOTION_RAILJUMP,	// ���[�����̃W�����v
		MOTION_JUMP,		// ���[�����̃W�����v
		MOTION_ELECJUMP		// �������̃W�����v
	}MOTION;
	CTutorialPlayer(int nPriority = 4);	// �R���X�g���N�^
	~CTutorialPlayer();					// �f�X�g���N�^
	static CTutorialPlayer* Create(D3DXVECTOR3 pos);// �C���X�^���X����
	HRESULT Init(D3DXVECTOR3 pos);	// ������
	void Uninit(void);				// �I��
	void Update(void);				// �X�V
	void Draw(void);				// �`��
	void SetPos(D3DXVECTOR3 pos);	// �ʒu
	void SetRot(D3DXVECTOR3 rot);	// ����
	void SetMove(D3DXVECTOR3 move);	// ���x
	void SetState(STATE state) { m_State = state; }		// ��Ԃ̐ݒ�
	void SetLife(float fLife) { m_fLife = fLife; }		// ���C�t�̐ݒ�
	void SetAngle(float fAngle) { m_fAngle = fAngle; }	// �����̐ݒ�
	void SetStan(int nStan) { m_nStanTime = nStan; }	// �X�^�����鎞�Ԃ̐ݒ�
	void SetElec(bool bElec) { m_bElec = bElec; }			// ������Ԃ̐ݒ�
	D3DXVECTOR3 GetPos(void) { return m_pos; }			// �ʒu���擾
	D3DXVECTOR3 GetOldPos(void) { return m_oldPos; }	// �O�t���[���̈ʒu���擾
	D3DXVECTOR3 GetRot(void) { return m_rot; }			// �������擾
	D3DXVECTOR3 GetMove(void) { return m_move; }		// �������擾
	D3DXVECTOR3 GetVecU(void) { return m_vecU; }		// ��x�N�g�����擾
	STATE GetState(void) { return m_State; }			// ��ԏ��擾
	CMotion* GetMotion(void) { return m_pMotion; }		// ���[�V�����̃|�C���^�擾
	CItemManager* GetItemManager(void) { return m_pItemManager; }// ���[�V�����̃|�C���^�擾
	static float GetLife(void) { return m_fLife; }		// ���C�t���̎擾
	float GetAngle(void) { return m_fAngle; }			// �������擾
	int GetStan(void) { return m_nStanTime; }			// �X�^�����ԏ��擾
	int GetStanCnt(void) { return m_nStanCnt; }			// �X�^���J�E���g���擾
	bool GetReverse(void) { return m_bReverse; }		// ���씽�]���擾
	bool GetElec(void) { return m_bElec; }				// �������擾
	float GetSpeed(void) { return m_fSpeed; }			// �������擾
	void Posture(void);									// �p������
	void JumpPosture(void);								// �W�����v���p������
	void LoadMotion(const char* pMotionScript);			// ���[�V�����̓ǂݍ���
	void AngleVelocity(float speed, float omega);		// �i�ޕ����̐���
	void Decay(void);									// ���X�Ɏ~�܂点��
	void SpeedUp(void);									// ���X�ɉ�������
	void SpeedDown(void);									// ���X�ɉ�������
	void ChangeState(CTutorialPlayerStateBase* pState);			// ��Ԃ�ς���
	void SetBoostTime(int nBoost) { m_nBoostTime = nBoost; }// �u�[�X�g���Ԑݒ�
	int GetBoostTime(void) { return m_nBoostTime; }		// �u�[�X�g���ԏ��擾
	void PutOutRail(void);								// ���[�����o��
	void AddStanCnt(void) { m_nStanCnt++; }				// �X�^�����Ԃ�ǉ�
	void SetATK(int nATK) { m_nATK = nATK; }			// �U���͐ݒ�
	int GetATK(void);									// �U���͏��擾
	void SetJumpCancel(bool bCancel) { m_bJumpCancel = bCancel; }
	bool GetJumpCancel(void) { return m_bJumpCancel; }	// �W�����v�L�����Z���擾
	void SwitchReverse(void) { m_bReverse = !m_bReverse; }// ���씽�]�ؑ�
private:
	D3DXVECTOR3 m_pos;		// �ʒu
	D3DXVECTOR3 m_oldPos;	// �O�t���[���̈ʒu
	D3DXVECTOR3 m_move;		// ����
	D3DXVECTOR3 m_rot;		// ����
	D3DXVECTOR3 m_rotDest;	// �ڕW�̌���
	D3DXVECTOR3 m_vecF;		// �O�x�N�g��
	D3DXVECTOR3 m_vecR;		// �E�x�N�g��
	D3DXVECTOR3 m_vecU;		// ��x�N�g��
	D3DXMATRIX m_mtxWorld;	// ���[���h�}�g���b�N�X
	float m_fAngle;			// ����
	static float m_fLife;	// ���C�t
	int m_nIdxXFile;		// �g��X�t�@�C���̔ԍ�
	STATE m_State;			// ���
	CMotion* m_pMotion;		// ���[�V�����ւ̃|�C���^
	CModel* m_apModel[18];	// �p�[�c�ւ̃|�C���^
	int m_nNumModel;		// �p�[�c��
	CStateMachine* m_Machine;// �X�e�[�g�}�V���ւ̃|�C���^
	CShadowS* m_pShadow;	// �e�̃|�C���^
	CLifeUI* m_pLifeUI;		// ���C�tUI�ւ̃|�C���^
	COrbit* m_pOrbit[2];	// �O�Ղւ̃|�C���^
	CItemManager* m_pItemManager;// �A�C�e���}�l�[�W���[�ւ̃|�C���^
	int m_nBoostTime;		// �u�[�X�g����
	int m_nStanTime;		// �X�^������
	int m_nStanCnt;			// �X�^���J�E���g
	float m_fSpeed;			// ���݂̑��x
	int m_nATK;				// �U����
	bool m_bReverse;		// ���씽�]
	bool m_bElec;			// ������
	bool m_bJumpCancel;		// �W�����v�L�����Z��
	static constexpr float Acceleration = 0.08f;// �����x
};

//**************************************
// �v���C���[��p�̃X�e�[�g�̊��N���X
//**************************************
class CTutorialPlayerStateBase :public CStateBase
{
public:
	CTutorialPlayerStateBase();				// �R���X�g���N�^
	~CTutorialPlayerStateBase();			// �f�X�g���N�^
	void SetOwner(CTutorialPlayer* pPlayer);// �v���C���[�̃|�C���^�ݒ�
protected:
	CTutorialPlayer* m_pPlayer;				// �v���C���[�ւ̃|�C���^
};

//****************
// �n�ʂɂ���Ƃ�
//****************
class CTutorialRandState :public CTutorialPlayerStateBase
{
public:
	CTutorialRandState();		// �R���X�g���N�^
	~CTutorialRandState();		// �f�X�g���N�^
	void Init(void);	// ������
	void Update(void);	// �X�V
	void Uninit(void);	// �I��
	void Controll(void);// ����
private:
	static constexpr float backSpeed = 0.5f;// �����x
};

//****************
// �󒆂ɂ���Ƃ�
//****************
class CTutorialJumpState :public CTutorialPlayerStateBase
{
public:
	CTutorialJumpState();		// �R���X�g���N�^
	~CTutorialJumpState();		// �f�X�g���N�^
	void Init(void);	// ������
	void Update(void);	// �X�V
	void Uninit(void);	// �I��
	void Rotation(void);// ��]�ŏ[�d
	void Controll(void);// ����
private:
	float m_fAngleSum;	// ��]�������v
	float m_fAngle;		// ����
};


//******************
// ���[���ɂ���Ƃ�
//******************
class CTutorialRailState :public CTutorialPlayerStateBase
{
public:
	CTutorialRailState();		// �R���X�g���N�^
	~CTutorialRailState();		// �f�X�g���N�^
	void Init(void);	// ������
	void Update(void);	// �X�V
	void Uninit(void);	// �I��
private:
};


//************************
// ���[���`�F���W����Ƃ�
//************************
class CTutorialRailChangeState :public CTutorialPlayerStateBase
{
public:
	CTutorialRailChangeState();		// �R���X�g���N�^
	~CTutorialRailChangeState();	// �f�X�g���N�^
	void Init(void);	// ������
	void Update(void);	// �X�V
	void Uninit(void);	// �I��
private:
};

//************************
// ���n����Ƃ�
//************************
class CTutorialLandingState :public CTutorialPlayerStateBase
{
public:
	CTutorialLandingState();	// �R���X�g���N�^
	~CTutorialLandingState();	// �f�X�g���N�^
	void Init(void);	// ������
	void Update(void);	// �X�V
	void Uninit(void);	// �I��
private:
	int m_nCnt;			// ���n�̃J�E���g
	int m_nDirectionType;// �i�ޕ���
	static constexpr float speedDivision = 2.0f;	// ��]���a 
	static constexpr float omegaRadius = 200.0f;	// ��]���a 
	static constexpr float  maxSpeed = -10.0f;	// �ő�X�s�[�h
	static constexpr float  minSpeed = -3.0f;	// �ŏ��X�s�[�h
};

//*********************
// ����s�\�̂Ƃ�
//*********************
class CTutorialInoperableState :public CTutorialPlayerStateBase
{
public:
	CTutorialInoperableState();		// �R���X�g���N�^
	~CTutorialInoperableState();	// �f�X�g���N�^
	void Init(void);	// ������
	void Update(void);	// �X�V
	void Uninit(void);	// �I��
private:
	int m_nCnt;		// ���ԃJ�E���g
	static constexpr int Cool = 30;// ����s�\�����܂ł̎���
};

#endif