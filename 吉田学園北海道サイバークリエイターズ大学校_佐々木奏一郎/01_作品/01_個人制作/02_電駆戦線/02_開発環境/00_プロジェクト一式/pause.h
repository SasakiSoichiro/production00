//**********************************
//
// �|�[�Y���� [pause.h]
// Author:Sasaki Soichiro
//
//**********************************
#ifndef _PAUSE_H_ // ���̃}�N����`������Ă��Ȃ�������
#define _PAUSE_H_ // ��d�C���N���[�h�h�~�̃}�N����`

//******************
// �C���N���[�h
//******************
#include "main.h"
#include "object2D.h"
#include "state.h"

//*********************
// �}�N����`
//*********************
#define MAX_SELECT (4)

class CPauseStateBase;

//********************
// �|�[�Y�N���X
//********************
class CPause:public CObject2D
{
public:
	typedef enum
	{
		TYPE_BACKGAME=0,
		TYPE_STARTGAME,
		TYPE_BACKTITLE,
		TYPE_REVERSE,
		TYPE_MAX
	}TYPE;
	CPause(int nPriority = 7);	// �R���X�g���N�^
	~CPause();					// �f�X�g���N�^
	static CPause* Create(D3DXVECTOR3 pos,int nType);
	HRESULT Init(D3DXVECTOR3 pos);	// ������
	void Uninit(void);				// �I��
	void Update(void);				// �X�V
	void Draw(void);				// �`��
	void SetPos(D3DXVECTOR3 pos);	// �ʒu�̐ݒ�
	void SetRot(D3DXVECTOR3 rot);	// �����̐ݒ�
	D3DXVECTOR3 GetPos(void);		// �ʒu���擾
	D3DXVECTOR2 GetSize(void);		// �傫�����擾
	void AnimSize(void);			// �|�[�Y���̃A�j���[�V����
	static bool GetPause(void) { return m_bPause; }			// �|�[�Y���̎擾
	static void SwitchPause(void) { m_bPause = !m_bPause; }	// �|�[�Y�؂�ւ�
	static int GetSelect(void) { return m_nSelect; }		// �I��
	static void SetSelect(int nSelect) { m_nSelect = nSelect; }	// �I���̐ݒ�

private:
	int  m_nIdxTexture;			// �e�N�X�`���̃C���f�b�N�X
	float m_nAnim;				// �A�j���[�V�����p�J�E���g
	static bool m_bPause;		// �|�[�Y�ؑ֗p
	CObject2D* m_apObject2D[MAX_SELECT];	// CObject2D�ւ̃|�C���^
	static int m_nSelect;
};

//**********************
// �Q�[���ɖ߂�
//**********************
class CBackGame :public CPause
{
public:
	CBackGame();
	~CBackGame();
	HRESULT Init(D3DXVECTOR3 pos);	// ������
	void Uninit(void);				// �I��
	void Update(void);				// �X�V
	void Draw(void);				// �`��
};

//**********************
// �n�߂���
//**********************
class CStartGame :public CPause
{
public:

	CStartGame();
	~CStartGame();
	HRESULT Init(D3DXVECTOR3 pos);	// ������
	void Uninit(void);				// �I��
	void Update(void);				// �X�V
	void Draw(void);				// �`��
};

//**********************
// �^�C�g���ɖ߂�
//**********************
class CBackTitle :public CPause
{
public:

	CBackTitle();
	~CBackTitle();
	HRESULT Init(D3DXVECTOR3 pos);	// ������
	void Uninit(void);				// �I��
	void Update(void);				// �X�V
	void Draw(void);				// �`��
};

//**********************
// ������@
//**********************
class CReverse :public CPause
{
public:
	CReverse();
	~CReverse();
	HRESULT Init(D3DXVECTOR3 pos);	// ������
	void Uninit(void);				// �I��
	void Update(void);				// �X�V
	void Draw(void);				// �`��
};




#endif