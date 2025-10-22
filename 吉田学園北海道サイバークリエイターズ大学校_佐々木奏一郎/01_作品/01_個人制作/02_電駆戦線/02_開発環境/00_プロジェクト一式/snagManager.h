//***************************************
// 
// ��Q���}�l�[�W���[���� [snagManager.h]
// Author:Sasaki Soichiro
//
//***************************************
#ifndef _SNAGMANAGER_H_ // ���̃}�N����`������Ă��Ȃ�������
#define _SNAGMANAGER_H_ // ��d�C���N���[�h�h�~�̃}�N����`

//******************
// �C���N���[�h
//******************
#include "main.h"

//************************
// ��Q���}�l�[�W���[�N���X
//************************
class CSnagManager
{
public:
	CSnagManager();	// �R���X�g���N�^
	~CSnagManager();// �f�X�g���N�^
	HRESULT Init(void);	// ������
	void Uninit(void);	// �I��
	void Update(void);	// �X�V
private:
	int m_nFenceTime;	// ��̏o������
	int m_nJemTime;		// ��΂̏o������
	static constexpr int FenceCool = 1600;	// �N�[���^�C��
	static constexpr int JemCool = 500;		// �N�[���^�C��
};
#endif