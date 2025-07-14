//**********************************
//
// �J�������� [camera.cpp]
// Author:Sasaki Soichiro
//
//**********************************

//*******************
// �C���N���[�h
//*******************
#include "camera.h"
#include "input.h"
#include "manager.h"

//****************
// �}�N����`
//****************
#define OFFSET (80.0f)	// �v���C���[����J�����̋���
#define DEST (0.09f)	// �ڕW�ɓ��B����܂ł̔{��

//**********************
// �ÓI�����o�ϐ�������
//**********************
CPlayer* CCamera::m_pPlayer = NULL;			// �v���C���[�̃|�C���^


//********************
// �R���X�g���N�^
//********************
CCamera::CCamera()
{
	m_posV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ���_
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �����_
	m_vecU = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ������x�N�g��
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ����
	m_mtxProjection = {};					// �v���W�F�N�V�����}�g���b�N�X
	m_mtxView = {};							// �r���[�}�g���b�N�X
	m_fDistance = 0.0f;						// ���_�ƒ����_�̋���
	m_posVDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ړI�̎��_
	m_posRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ړI�̒����_
}

//********************
// �f�X�g���N�^
//********************
CCamera::~CCamera()
{
	// �����Ȃ�
}

//**************
// ����������
//**************
void CCamera::Init(void)
{
	// �J�����̏����z�u
	m_posV = D3DXVECTOR3(0.0f, OFFSET, 0.0f);
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// ���_�ƒ����_�̋����v�Z
	float fDX = m_posV.x - m_posR.x;
	float fDY = m_posV.y - m_posR.y;
	float fDZ = m_posV.z - m_posR.z;
	m_fDistance = sqrtf((fDX * fDX) + (fDY * fDY) + (fDZ * fDZ));// ���[�N���b�h����

}

//**************
// �I������
//**************
void CCamera::Uninit(void)
{
	// �����Ȃ�
}

//**************
// �X�V����
//**************
void CCamera::Update(void)
{
	// �v���C���[�Ǐ]
	Target();

	// �����_�̃X���[�W���O�Ǐ]�v�Z(DEST�Œx������)
	m_posR.x += (m_posRDest.x - m_posR.x) * DEST;
	m_posR.y += (m_posRDest.y - m_posR.y) * DEST;
	m_posR.z += (m_posRDest.z - m_posR.z) * DEST;

	// ���_�̃X���[�W���O�Ǐ]�v�Z(DEST�Œx������)
	m_posV.x += (m_posVDest.x - m_posV.x) * DEST;
	m_posV.y += (m_posVDest.y - m_posV.y) * DEST;
	m_posV.z += (m_posVDest.z - m_posV.z) * DEST;

}

//**************
// �ݒ菈��
//**************
void CCamera::SetCamera(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	CRenderer* renderer = CManager::GetCRenderer();
	pDevice = renderer->GetDevice();

	//

	//�r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxView);

	//�r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(	&m_mtxView,
						&m_posV,	// ���_
						&m_posR,	// �����_
						&m_vecU);	// ������x�N�g��

	//�r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);

	//�v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxProjection);

	//�v���W�F�N�V�����}�g���b�N�X�̍쐬
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
		D3DXToRadian(100.0f),						// ����p
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,	// �A�X�y�N�g��
		10.0f,										// �j�A(�ǂ��܂ŋ߂����f����)
		1000.0f);									// �t�@�[(�ǂ��܂ŉ������f����)

	//�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);
}

//****************
// �v���C���[�Ǐ]
//****************
void CCamera::Target(void)
{
	if (m_pPlayer != NULL)
	{// �v���C���[��������

		// �v���C���[���擾
		D3DXVECTOR3 Ppos = m_pPlayer->GetPos();
		D3DXVECTOR3 Prot = m_pPlayer->GetRot();

		// �����_���v���C���[�̈ʒu�ɐݒ�
		m_posRDest.x = Ppos.x;
		m_posRDest.y = Ppos.y+20.0f;
		m_posRDest.z = Ppos.z;

		// ���_���v���C���[�̌�둤�ɐݒ�(�����ݒ�̋����ɗ����)
		m_posVDest.x = Ppos.x + sinf(Prot.y) * m_fDistance;
		m_posVDest.y = Ppos.y + OFFSET;
		m_posVDest.z = Ppos.z + cosf(Prot.y) * m_fDistance;
	}
}

//****************
// �Œ�J����
//****************
void CCamera::Fixed(D3DXVECTOR3 pos)
{

}

void CCamera::SetPlayer(CPlayer* pPlayer)
{
	if (m_pPlayer == NULL)
	{
		m_pPlayer = pPlayer;
	}
}