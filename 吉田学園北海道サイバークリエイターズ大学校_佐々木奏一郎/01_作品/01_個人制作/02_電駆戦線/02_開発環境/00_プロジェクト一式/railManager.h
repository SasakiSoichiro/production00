//***************************************
// 
// ���[���}�l�[�W���[���� [railManager.h]
// Author:Sasaki Soichiro
//
//***************************************
#ifndef _RAILMANAGER_H_ // ���̃}�N����`������Ă��Ȃ�������
#define _RAILMANAGER_H_ // ��d�C���N���[�h�h�~�̃}�N����`

//******************
// �C���N���[�h
//******************
#include "main.h"

class CRail;

//**************************
// ���[���}�l�[�W���[�N���X
//**************************
class CRailManager
{
public:
	CRailManager();	// �R���X�g���N�^
	~CRailManager();	// �f�X�g���N�^
	HRESULT Init(void);	// ������
	void Uninit(void);	// �I��
	void Update(void);	// �X�V
private:
	static CRail* m_pRail[2];	// ���[���ւ̃|�C���^
};
#endif