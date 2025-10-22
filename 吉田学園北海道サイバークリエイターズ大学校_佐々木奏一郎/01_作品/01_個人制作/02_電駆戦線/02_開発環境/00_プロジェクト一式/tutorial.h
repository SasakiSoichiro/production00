//************************************
//
// �`���[�g���A������ [tutorial.h]
// Author:Sasaki Soichiro
//
//************************************
#ifndef _TUTORIAL_H_ // ���̃}�N����`������Ă��Ȃ�������
#define _TUTORIAL_H_ // ��d�C���N���[�h�h�~�̃}�N����`

//******************
// �C���N���[�h
//******************
#include "main.h"
#include "scene.h"
#include "state.h"

class CTutorialCheck;
class CTutorialStateBase;
class CMesh;
class CBlockManager;
class CTutorialPlayer;
class CTutorialRail;

//**********************
// �`���[�g���A���N���X
//**********************
class CTutorial :public CScene
{
public:
	typedef enum
	{
		STATE_FLONTBACK=0,
		STATE_RIGHTLEFT,
		STATE_ROLL,
		STATE_JUMP,
		STATE_JUMPCANCEL,
		STATE_RAIL,
		STATE_ATTACK,
		STATE_FREE,
		STATE_MAX,
	}STATE;
	CTutorial();	// �R���X�g���N�^
	~CTutorial();	// �f�X�g���N�^
	HRESULT Init(D3DXVECTOR3 pos);		// ������
	void Uninit(void);					// �I��
	void Update(void);					// �X�V
	void Draw(void);					// �`��
	void SetPos(D3DXVECTOR3 pos) {};	// �ʒu
	void SetRot(D3DXVECTOR3 rot) {};	// ����
	D3DXVECTOR3 GetPos(void) { return NONE; }	// �ʒu���
	void TaskClear(void);				// �N���A
	void ChangeState(CTutorialStateBase* pState);
	static CMesh*GetCMesh(void) { return m_pMesh; }
	static CBlockManager* GetCBlockManager(void) { return m_pBlockManager; }
	static CTutorialPlayer* GetCPlayer(void) { return m_pPlayer; }


private:
	STATE m_State;				// ���
	CStateMachine* m_Machine;	// �X�e�[�g�}�V���ւ̃|�C���^
	CTutorialCheck* m_pTutorialCheck;
	static CMesh* m_pMesh;					// ���b�V���ւ̃|�C���^
	static CBlockManager* m_pBlockManager;	// �u���b�N�}�l�[�W���[�ւ̃|�C���^
	static CTutorialPlayer* m_pPlayer;		// �u���b�N�}�l�[�W���[�ւ̃|�C���^
	static CTutorialRail* m_pRail;			// ���[���ւ̃|�C���^
};

//******************************************
// �`���[�g���A����p�̃X�e�[�g�̊��N���X
//******************************************
class CTutorialStateBase :public CStateBase
{
public:
	CTutorialStateBase();				// �R���X�g���N�^
	~CTutorialStateBase();				// �f�X�g���N�^
	void SetOwner(CTutorial* pTutorial);// �`���[�g���A���̃|�C���^�ݒ�
protected:
	CTutorial* m_pTutorial;				// �`���[�g���A���ւ̃|�C���^
};

//****************
// �O��̑���
//****************
class CFlontBackState :public CTutorialStateBase
{
public:
	CFlontBackState();		// �R���X�g���N�^
	~CFlontBackState();		// �f�X�g���N�^
	void Init(void);	// ������
	void Update(void);	// �X�V
	void Uninit(void);	// �I��
private:
	int m_nCnt;
	bool m_nClear;
	static constexpr int clearTime = 180;
	
};

//****************
// ���E�̑���
//****************
class CRightLeftState :public CTutorialStateBase
{
public:
	CRightLeftState();		// �R���X�g���N�^
	~CRightLeftState();		// �f�X�g���N�^
	void Init(void);	// ������
	void Update(void);	// �X�V
	void Uninit(void);	// �I��
private:
	int m_nCnt;
	bool m_nClear;
	static constexpr int clearTime = 60;
};

//****************
// ��]�̑���
//****************
class CRollState :public CTutorialStateBase
{
public:
	CRollState();		// �R���X�g���N�^
	~CRollState();		// �f�X�g���N�^
	void Init(void);	// ������
	void Update(void);	// �X�V
	void Uninit(void);	// �I��
private:
	int m_nCnt;
	bool m_nClear;
	static constexpr int clearTime = 60;
};


//****************
// �W�����v�̑���
//****************
class CJumpCState :public CTutorialStateBase
{
public:
	CJumpCState();		// �R���X�g���N�^
	~CJumpCState();		// �f�X�g���N�^
	void Init(void);	// ������
	void Update(void);	// �X�V
	void Uninit(void);	// �I��
private:
	int m_nCnt;
	bool m_nClear;
	static constexpr int clearCnt = 1;
};

//****************
// �W�����v�̑���
//****************
class CJumpCancelState :public CTutorialStateBase
{
public:
	CJumpCancelState();		// �R���X�g���N�^
	~CJumpCancelState();	// �f�X�g���N�^
	void Init(void);	// ������
	void Update(void);	// �X�V
	void Uninit(void);	// �I��
private:
	int m_nCnt;
	bool m_nClear;
	static constexpr int clearCnt = 1;
};

//********************
// ���[���ɏ��̑���
//********************
class CRailCState :public CTutorialStateBase
{
public:
	CRailCState();		// �R���X�g���N�^
	~CRailCState();		// �f�X�g���N�^
	void Init(void);	// ������
	void Update(void);	// �X�V
	void Uninit(void);	// �I��
private:
	int m_nCnt;
	bool m_nClear;
};

//********************
// �A�^�b�N����
//********************
class CAttackCState :public CTutorialStateBase
{
public:
	CAttackCState();		// �R���X�g���N�^
	~CAttackCState();		// �f�X�g���N�^
	void Init(void);	// ������
	void Update(void);	// �X�V
	void Uninit(void);	// �I��
private:
	int m_nCnt;
	bool m_nClear;
	static constexpr int clearCnt = 180;
};

//********************
// �t���[����
//********************
class CFreeState :public CTutorialStateBase
{
public:
	CFreeState();		// �R���X�g���N�^
	~CFreeState();		// �f�X�g���N�^
	void Init(void);	// ������
	void Update(void);	// �X�V
	void Uninit(void);	// �I��
private:
	int m_nCnt;
	bool m_nClear;
};





#endif