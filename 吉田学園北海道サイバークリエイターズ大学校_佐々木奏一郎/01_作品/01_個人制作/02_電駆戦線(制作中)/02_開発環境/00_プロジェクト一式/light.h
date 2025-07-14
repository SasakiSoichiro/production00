//************************************
//
// ���C�g���� [light.h]
// Author:Sasaki Soichiro
//
//************************************
#ifndef _LIGHT_H_//���̃}�N����`������Ă��Ȃ�������
#define _LIGHT_H_//��d�C���N���[�h�h�~�̃}�N����`

//*****************
//	�C���N���[�h
//*****************
#include "main.h"

//******************
// �}�N����`
//******************
#define MAX_LIGHT (3)

//******************
// ���C�g�N���X
//******************
class CLight
{
public:
	CLight();	// �R���X�g���N�^
	~CLight();	// �f�X�g���N�^
	void Init(void);	// ������
	void Uninit(void);	// �I��
	void Update(void);	// �X�V
private:
	D3DLIGHT9 m_aLight[MAX_LIGHT];// ���C�g
	D3DXVECTOR3 m_aVec[MAX_LIGHT];// �x�N�g��
};

#endif