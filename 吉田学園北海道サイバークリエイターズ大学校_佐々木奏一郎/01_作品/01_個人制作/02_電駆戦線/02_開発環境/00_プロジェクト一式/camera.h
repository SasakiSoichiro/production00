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
	void Target(D3DXVECTOR3 pos,D3DXVECTOR3 rot);	// �f���^�[�Q�b�g�̐ݒ�
	void BackTarget(D3DXVECTOR3 pos, D3DXVECTOR3 rot);// ���ɐi�ޏꍇ�̐ݒ�
	void InitTarget(D3DXVECTOR3 pos, D3DXVECTOR3 rot);// �J�����̏�����
	void JumpTarget(D3DXVECTOR3 pos,float fAngle);	// �󒆂ɂ���ꍇ�̐ݒ�
	void SetVandR(void);							// ���_�ƒ����_�̐ݒ�
	void MoveMouseR(void);							// �}�E�X�Œ����_�𓮂���
	void MoveMouseV(void);							// �}�E�X�Ŏ��_�𓮂���
	void Shake(void);								// �J������h�炷
	void SetShake(int nTime);						// �J������h�炷���Ԃ�ݒ肷��
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
	int m_nShakeTime;			// �J�������h��Ă��鎞��
	static constexpr float ofsetV = 60.0f;	// �v���C���[���王�_�܂ł̋���
	static constexpr float ofsetBackV = 90.0f;	// �v���C���[���王�_�܂ł̋���(�������ɐi��ł���Ƃ�)
	static constexpr float ofsetR = 50.0f;	// �v���C���[���王�_�܂ł̋���
	static constexpr float dest = 0.08f;	// �ڕW�ɓ��B����܂ł̒x��
	static constexpr float speed = 2.0f;	// �J�������쎞�̃X�s�[�h
	static constexpr float sensitivity = 0.009f;	// �}�E�X���x
	static constexpr float shakeDistance = 1.5f;	// �J�����h��̓�������
	static constexpr float FOV = 100.0f;			// ����p
	static constexpr float nearScreen = 10.0f;		// �`�拗��(�߂�)
	static constexpr float farScreen = 10000.0f;	// �`�拗��(����)
};
#endif