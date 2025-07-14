//=============================================================================
//
//	�u���b�N���� [block.h]
// Author : ���X�ؑt��Y
//
//=============================================================================

#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"

// �}�N����`
#define MAX_CAMERA (2)

// �\����
typedef struct
{
	D3DXVECTOR3 posV;			// ���_
	D3DXVECTOR3 posR;			// �����_
	D3DXVECTOR3 vecU;			// ������x�N�g��
	D3DXMATRIX mtxProjection;	// �v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX mtxView;			// �r���[�}�g���b�N�X
	D3DXVECTOR3 rot;			// ����
	D3DXVECTOR3 rotDest;		// �ړI�̌���
	D3DXVECTOR3 posRDest;		// �ړI�̈ʒu(�E)
	D3DXVECTOR3 posVDest;		// �ړI�̈ʒu(��)
	D3DVIEWPORT9 viewport;		// �r���[�|�[�g
	float fDistance;			// ���_���璍���_�̋���
	float deltaX;				// �f���^X
	float deltaY;				// �f���^Y
	POINT cursorPos;			// �}�E�X�J�[�\���̈ʒu
	POINT prevCursorPos;		// �J�[�\���̌�����ʒu
}Camera;

// �Ղ�Ƃ�����
void InitCamera(void);
void UninitCamera(void);
void UpdateCamera(void);
void SetCamera(int nIdx);
void MouseWheel(int zDelta);
Camera* GetCamera(void);

#endif // !_CAMERA_H_
