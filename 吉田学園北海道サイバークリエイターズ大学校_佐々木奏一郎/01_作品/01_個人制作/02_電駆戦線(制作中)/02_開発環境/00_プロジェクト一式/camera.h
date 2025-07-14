//***************************************
//
// �J�������� [camera.h]
// Author:Sasaki Soichiro
//
//***************************************
#ifndef _CAMERA_H_//���̃}�N����`������Ă��Ȃ�������
#define _CAMERA_H_//�Q�d�C���N���[�h�h�~�̃}�N����`
//**************
// �C���N���[�h
//**************
#include "main.h"
#include "player.h"

//**************
// �J�����N���X
//**************
class CCamera
{
public:
	CCamera();	// �R���X�g���N�^
	~CCamera();	// �f�X�g���N�^
	void Init(void);		// ������
	void Uninit(void);		// �I��
	void Update(void);		// �X�V
	void SetCamera(void);	// �J�����̐ݒ�
	void Target(void);
	void Fixed(D3DXVECTOR3 pos);
	static void SetPlayer(CPlayer* pPlayer);

private:
	D3DXVECTOR3 m_posV;			// ���_
	D3DXVECTOR3 m_posR;			// �����_
	D3DXVECTOR3 m_vecU;			// ������x�N�g��
	D3DXMATRIX m_mtxProjection;	// �v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX m_mtxView;		// �r���[�}�g���b�N�X
	D3DXVECTOR3 m_rot;			// ����
	float m_fDistance;			// ���_���璍���_�̋���
	D3DXVECTOR3 m_posVDest;		// �ړI�̎��_
	D3DXVECTOR3 m_posRDest;		// �ړI�̒����_
	static CPlayer* m_pPlayer;	// �v���C���[�̃|�C���^
};
#endif