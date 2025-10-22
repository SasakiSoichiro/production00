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
#include "renderer.h"

//********************
// �R���X�g���N�^
//********************
CCamera::CCamera()
{
	m_posV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	
	m_vecU = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	
	m_mtxProjection = {};					
	m_mtxView = {};							
	m_fDistance = 0.0f;						
	m_posVDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	
	m_posRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	
	m_nShakeTime = 0;
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
	m_posV = D3DXVECTOR3(0.0f, ofsetV, 0.0f);
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
	// �����_�̃X���[�W���O�Ǐ]�v�Z(DEST�Œx������)
	m_posR.x += (m_posRDest.x - m_posR.x) * dest;
	m_posR.y += (m_posRDest.y - m_posR.y) * dest;
	m_posR.z += (m_posRDest.z - m_posR.z) * dest;

	// ���_�̃X���[�W���O�Ǐ]�v�Z(DEST�Œx������)
	m_posV.x += (m_posVDest.x - m_posV.x) * dest;
	m_posV.y += (m_posVDest.y - m_posV.y) * dest;
	m_posV.z += (m_posVDest.z - m_posV.z) * dest;

	// �J������h�炷
	Shake();
	// �^�C�}�[�����炷
	m_nShakeTime--;
}

//**************
// �`�揈��
//**************
void CCamera::SetCamera(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	CRenderer* renderer = CManager::GetCRenderer();
	pDevice = renderer->GetDevice();

	//�r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxView);

	//�r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&m_mtxView,
		&m_posV,	// ���_
		&m_posR,	// �����_
		&m_vecU);	// ������x�N�g��

	//�r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);

	//�v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxProjection);

	//�v���W�F�N�V�����}�g���b�N�X�̍쐬
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
		D3DXToRadian(FOV),							// ����p
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,	// �A�X�y�N�g��
		nearScreen,									// �j�A(�ǂ��܂ŋ߂����f����)
		farScreen);									// �t�@�[(�ǂ��܂ŉ������f����)

	//�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);
}

//****************
// �v���C���[�Ǐ]
//****************
void CCamera::Target(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// �v���C���[���擾
	D3DXVECTOR3 Ppos = pos;
	D3DXVECTOR3 Prot = rot;

	// �����_���v���C���[�̈ʒu�ɐݒ�
	m_posRDest.x = Ppos.x;
	m_posRDest.y = Ppos.y + ofsetR;
	m_posRDest.z = Ppos.z;

	// ���_���v���C���[�̌�둤�ɐݒ�(�����ݒ�̋����ɗ����)
	m_posVDest.x = Ppos.x + sinf(Prot.y) * m_fDistance;
	m_posVDest.y = Ppos.y + ofsetV;
	m_posVDest.z = Ppos.z + cosf(Prot.y) * m_fDistance;
}

//************************
// �������v���C���[�Ǐ]
//************************
void CCamera::BackTarget(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// �����_���v���C���[�̈ʒu�ɐݒ�
	m_posRDest.x = pos.x + sinf(rot.y) * ofsetR;
	m_posRDest.y = pos.y + ofsetR;
	m_posRDest.z = pos.z + cosf(rot.y) * ofsetR;

	// ���_���v���C���[�̌�둤�ɐݒ�(�����ݒ�̋����ɗ����)
	m_posVDest.x = pos.x + sinf(rot.y) * m_fDistance;
	m_posVDest.y = pos.y + ofsetBackV;
	m_posVDest.z = pos.z + cosf(rot.y) * m_fDistance;

}

//**********************
// �J�����̈ʒu�̏�����
//**********************
void CCamera::InitTarget(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// �����_���v���C���[�̈ʒu�ɐݒ�
	m_posR.x = pos.x;
	m_posR.y = pos.y + ofsetR;
	m_posR.z = pos.z;

	// ���_���v���C���[�̌�둤�ɐݒ�(�����ݒ�̋����ɗ����)
	m_posV.x = pos.x + sinf(rot.y) * m_fDistance;
	m_posV.y = pos.y + ofsetV;
	m_posV.z = pos.z + cosf(rot.y) * m_fDistance;

	// �x�����Ȃ���
	m_posVDest = m_posV;
	m_posRDest = m_posR;
}

//****************
// �W�����v�̒Ǐ]
//****************
void CCamera::JumpTarget(D3DXVECTOR3 pos, float fAngle)
{
	// �v���C���[���擾
	D3DXVECTOR3 Ppos = pos;

	// �����_���v���C���[�̈ʒu�ɐݒ�
	m_posRDest.x = Ppos.x;
	m_posRDest.y = Ppos.y;
	m_posRDest.z = Ppos.z;

	// ���_���v���C���[�̌�둤�ɐݒ�(�����ݒ�̋����ɗ����)
	m_posVDest.x = Ppos.x + sinf(fAngle);
	m_posVDest.y = Ppos.y + ofsetBackV;
	m_posVDest.z = Ppos.z + cosf(fAngle);
}

//********************
// ���_�ƒ����_�̐ݒ�
//********************
void CCamera::SetVandR(void)
{
	// ���͎擾
	CInputKeyboard* pInputKeyboard = CManager::GetCInputKeyboard();

	// �J�����𓮂���(���_�ƒ����_����)
	if (pInputKeyboard->GetPress(DIK_UP) == true)
	{// �O
		m_posR.x += sinf(m_rot.y + D3DX_PI) * speed;
		m_posR.z += cosf(m_rot.y + D3DX_PI) * speed;
		m_posV.x += sinf(m_rot.y + D3DX_PI) * speed;
		m_posV.z += cosf(m_rot.y + D3DX_PI) * speed;
	}
	else if (pInputKeyboard->GetPress(DIK_DOWN) == true)
	{// ��
		m_posR.x += sinf(m_rot.y) * speed;
		m_posR.z += cosf(m_rot.y) * speed;
		m_posV.x += sinf(m_rot.y) * speed;
		m_posV.z += cosf(m_rot.y) * speed;
	}
	if (pInputKeyboard->GetPress(DIK_LEFT) == true)
	{// ��
		m_posR.x += sinf(m_rot.y + D3DX_PI * 0.5f) * speed;
		m_posR.z += cosf(m_rot.y + D3DX_PI * 0.5f) * speed;
		m_posV.x += sinf(m_rot.y + D3DX_PI * 0.5f) * speed;
		m_posV.z += cosf(m_rot.y + D3DX_PI * 0.5f) * speed;
	}
	else if (pInputKeyboard->GetPress(DIK_RIGHT) == true)
	{// �E
		m_posR.x += sinf(m_rot.y - D3DX_PI * 0.5f) * speed;
		m_posR.z += cosf(m_rot.y - D3DX_PI * 0.5f) * speed;
		m_posV.x += sinf(m_rot.y - D3DX_PI * 0.5f) * speed;
		m_posV.z += cosf(m_rot.y - D3DX_PI * 0.5f) * speed;
	}

	// �x�����Ȃ���
	m_posRDest = m_posR;	
	m_posVDest = m_posV;	
}

//************************
// �}�E�X�Œ����_�𓮂���
//************************
void CCamera::MoveMouseR(void)
{
	// �}�E�X���擾
	CInputMouse* pInputMouse = CManager::GetCInputMouse();

	// �J�[�\���ʒu�擾
	D3DXVECTOR2 cursorPos, cursorPosOld;
	cursorPos = pInputMouse->GetVelocity();
	cursorPosOld = pInputMouse->GetVelocityOld();

	// �}�E�X�������Ă�����������߂�
	float DeltaX = (float)(cursorPos.x - cursorPosOld.x);
	float DeltaY = (float)(cursorPos.y - cursorPosOld.y);

	// �}�E�X���x�v�Z
	DeltaX *= sensitivity;
	DeltaY *= sensitivity;

	// �����v�Z
	m_rot.x += DeltaY;
	m_rot.y += DeltaX;

	// �����_�𓮂���
	m_posR.x = m_posV.x - sinf(m_rot.y) * cosf(m_rot.x) * m_fDistance;
	m_posR.y = m_posV.y - sinf(m_rot.x) * m_fDistance;
	m_posR.z = m_posV.z - cosf(m_rot.y) * cosf(m_rot.x) * m_fDistance;

	// �x�����Ȃ���
	m_posRDest = m_posR;
}

void CCamera::MoveMouseV(void)
{
	// �}�E�X���擾
	CInputMouse* pInputMouse = CManager::GetCInputMouse();

	// �J�[�\���ʒu�擾
	D3DXVECTOR2 cursorPos, cursorPosOld;
	cursorPos = pInputMouse->GetVelocity();
	cursorPosOld = pInputMouse->GetVelocityOld();

	// �}�E�X�������Ă�����������߂�
	float DeltaX = (float)(cursorPos.x - cursorPosOld.x);
	float DeltaY = (float)(cursorPos.y - cursorPosOld.y);

	// �}�E�X���x�v�Z
	DeltaX *= sensitivity;
	DeltaY *= sensitivity;

	// �����v�Z
	m_rot.x += DeltaY;
	m_rot.y += DeltaX;

	// �����_�𓮂���
	m_posV.x = m_posR.x + sinf(m_rot.y) * cosf(m_rot.x) * m_fDistance;
	m_posV.y = m_posR.y + sinf(m_rot.x) * m_fDistance;
	m_posV.z = m_posR.z + cosf(m_rot.y) * cosf(m_rot.x) * m_fDistance;

	// �x�����Ȃ���
	m_posVDest = m_posV;
}

//***************
// �U��
//***************
void CCamera::Shake(void)
{
	float fShakeX, fShakeY;

	// �h����v�Z
	fShakeX = sinf((float)m_nShakeTime) * shakeDistance;
	fShakeY = cosf((float)m_nShakeTime) * shakeDistance;

	// ���_�ƒ����_��h�炷
	if (m_nShakeTime > 0)
	{
		m_posR.x += fShakeX;
		m_posR.y += fShakeY;
		m_posV.x += fShakeX;
		m_posV.y += fShakeY;
	}
}

//******************
// �h�炷���Ԃ�ݒ�
//******************
void CCamera::SetShake(int nTime)
{
	if (m_nShakeTime <= 0)
	{// ���Ԃ�0�ȉ���������ݒ�
		m_nShakeTime = nTime;
	}
}