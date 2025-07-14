//******************************************
//
// �^�C�}�[���� [timer.h]
// AuthorSasaki Soichiro
//
//******************************************
#ifndef _TIMER_H_ // ���̃}�N����`������Ă��Ȃ�������
#define _TIMER_H_ // ��d�C���N���[�h�h�~�̃}�N����`

//******************
// �C���N���[�h
//******************
#include "main.h"
#include "object.h"
#include "number.h"

//********************
// �^�C�}�[�N���X
//********************
class CTimer :public CObject
{
public:
	CTimer(int nPriority = 5);	// �R���X�g���N�^
	~CTimer();					// �f�X�g���N�^
	static CTimer* Create(D3DXVECTOR3 pos,int nTime);// �C���X�^���X����
	HRESULT Init(D3DXVECTOR3 pos);	// ������
	void Uninit(void);				// �I��
	void Update(void);				// �X�V
	void Draw(void);				// �`��
	void SetPos(D3DXVECTOR3 pos);// �ʒu�̐ݒ�
	void SetRot(D3DXVECTOR3 rot);// �����̐ݒ�
	D3DXVECTOR3 GetPos(void) { return m_pos; };		// �ʒu�̐ݒ�
	D3DXVECTOR2 GetSize(void) { return m_size; };	// �傫���̐ݒ�
	static void SetTime(int nTime);				// �^�C�}�[�̐ݒ�
	static void Add(int nTime);					// �^�C�����Z
	static int GetTime(void) { return m_nTime; }// �^�C�����̎擾

private:
	int  m_nIdxTexture[2];		// �e�N�X�`���̃C���f�b�N�X
	static CNumber* m_apMin[2];	// �i���o�[�ւ̃|�C���^
	static CNumber* m_apSec[2];	// �i���o�[�ւ̃|�C���^
	static CSymbol* m_pSymbol;	// �R�����ւ̃|�C���^
	D3DXVECTOR3 m_pos;	// �ʒu
	D3DXVECTOR3 m_rot;	// ����
	D3DXVECTOR2 m_size;	// �傫��
	static int m_nTime;	// �^�C��
	static int m_nFps;	// FPS�J�E���g
};
#endif