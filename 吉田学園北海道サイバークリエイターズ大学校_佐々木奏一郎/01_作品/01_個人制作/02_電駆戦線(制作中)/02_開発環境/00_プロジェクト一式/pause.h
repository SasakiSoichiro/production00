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
#include "object.h"
#include "object2D.h"

//********************
// �|�[�Y�N���X
//********************
class CPause :public CObject2D
{
public:
	CPause(int nPriority = 7);	// �R���X�g���N�^
	~CPause();					// �f�X�g���N�^
	static CPause* Create(D3DXVECTOR3 pos);
	HRESULT Init(D3DXVECTOR3 pos);	// ������
	void Uninit(void);				// �I��
	void Update(void);				// �X�V
	void Draw(void);				// �`��
	void SetPos(D3DXVECTOR3 pos);// �ʒu
	void SetRot(D3DXVECTOR3 rot);// ����
	D3DXVECTOR3 GetPos(void);// �ʒu���̎擾
	D3DXVECTOR2 GetSize(void);// �傫�����̎擾
	static bool GetPause(void) { return m_bPause; }			// �|�[�Y���̎擾
	static void SwitchPause(void) { m_bPause = !m_bPause; }	// �|�[�Y�؂�ւ�
private:
	int  m_nIdxTexture;		// �e�N�X�`���̃C���f�b�N�X
	static bool m_bPause;	// �|�[�Y�ؑ֗p
};
#endif