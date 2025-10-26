//***************************************
// 
// �u���[�}�l�[�W���[���� [blurManager.h]
// Author:Sasaki Soichiro
//
//***************************************
#ifndef _BLURMANAGER_H_ // ���̃}�N����`������Ă��Ȃ�������
#define _BLURMANAGER_H_ // ��d�C���N���[�h�h�~�̃}�N����`

//******************
// �C���N���[�h
//******************
#include "main.h"

//************************
// �u���[�}�l�[�W���[�N���X
//************************
class CBlurManager
{
public:
	CBlurManager();	// �R���X�g���N�^
	~CBlurManager();// �f�X�g���N�^
	HRESULT Init(void);	// ������
	void Uninit(void);	// �I��
	void Update(void);	// �X�V
	static void Set(int nTime) { m_nTime=nTime; }// ���Ԃ̐ݒ�
	static bool GetBool(void) { return m_bTime; }// �u���[�����H���擾
private:
	static bool m_bTime;	//�u���[�����H
	static int m_nTime;		// ����
};
#endif