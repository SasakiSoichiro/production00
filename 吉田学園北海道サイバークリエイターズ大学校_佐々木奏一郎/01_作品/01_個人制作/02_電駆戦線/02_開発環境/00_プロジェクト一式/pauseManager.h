//***************************************
// 
// �|�[�Y�}�l�[�W���[���� [pauseManager.h]
// Author:Sasaki Soichiro
//
//***************************************
#ifndef _PAUSEMANAGER_H_ // ���̃}�N����`������Ă��Ȃ�������
#define _PAUSEMANAGER_H_ // ��d�C���N���[�h�h�~�̃}�N����`

//******************
// �C���N���[�h
//******************
#include "main.h"

class CPause;

//**************************
// �|�[�Y�}�l�[�W���[�N���X
//**************************
class CPauseManager
{
public:
	CPauseManager();	// �R���X�g���N�^
	~CPauseManager();	// �f�X�g���N�^
	HRESULT Init(void);	// ������
	void Uninit(void);	// �I��
	void Update(void);	// �X�V
private:
	static CPause* m_pBackGame;	// �Q�[���ɖ߂�
	static CPause* m_pStartGame;// �Q�[���̃X�^�[�g�ɖ߂�
	static CPause* m_pBackTitle;// �^�C�g���ɖ߂�
	static CPause* m_pReverse;	// ���씽�]
};
#endif