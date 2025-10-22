//***************************************
// 
// �ҏW���̃J�������� [editcamera.h]
// Author:Sasaki Soichiro
//
//***************************************
#ifndef _EDITCAMERA_H_ // ���̃}�N����`������Ă��Ȃ�������
#define _EDITCAMERA_H_ // ��d�C���N���[�h�h�~�̃}�N����`

//******************
// �C���N���[�h
//******************
#include "main.h"

//************************
// �G�f�B�b�g�J�����N���X
//************************
class CEditCamera
{
public:
	typedef enum
	{
		STATE_NONE=0,
		STATE_R,
		STATE_V,
		STATE_MAX
	}STATE;
	CEditCamera();	// �R���X�g���N�^
	~CEditCamera();	// �f�X�g���N�^
	HRESULT Init(void);	// ������
	void Uninit(void);	// �I��
	void Update(void);	// �X�V
private:
	STATE m_state;
};
#endif