//***************************************
// 
// �X���[���� [slow.h]
// Author:Sasaki Soichiro
//
//***************************************
#ifndef _SLOW_H_ // ���̃}�N����`������Ă��Ȃ�������
#define _SLOW_H_ // ��d�C���N���[�h�h�~�̃}�N����`

//******************
// �C���N���[�h
//******************
#include "main.h"

//************************
// �X���[�Ǘ��N���X
//************************
class CSlow
{
public:
	CSlow();	// �R���X�g���N�^
	~CSlow();	// �f�X�g���N�^
	HRESULT Init(void);			// ������
	void Uninit(void);			// �I��
	void Update(void);			// �X�V
	static void Set(int nTime);	// ���Ԃ̐ݒ�
	float GetfMulti(void) { return m_fMulti; }	// �|����l���擾
	int GetnMulti(void) { return m_nMulti; }	// �|����l���擾
	float GetfDivi(void) { return m_fDivi; }	// ����l���擾
	int GetnDivi(void) { return m_nDivi; }		// ����l���擾
private:
	static float m_fMulti;	// �|����l
	static float m_fDivi;	// ����l
	static int m_nMulti;	// �|����l
	static int m_nDivi;		// ����l
	static int m_nTime;		// ����
};
#endif