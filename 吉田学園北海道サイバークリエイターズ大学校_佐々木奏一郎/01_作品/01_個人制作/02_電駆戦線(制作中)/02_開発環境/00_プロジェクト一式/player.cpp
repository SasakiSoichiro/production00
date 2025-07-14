//*****************************************
//
// �v���C���[���� [player.cpp]
// Author:Sasaki Soichiro
//
//*****************************************

//*******************
// �C���N���[�h
//*******************
#include "player.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "texture.h"
#include "camera.h"
#include "object3D.h"

//*******************
// �}�N����`
//*******************
#define SPEED (8.0f)	// �v���C���[�̈ړ����x
#define DEST (0.3f)

//*****************
// �ÓI�����o�ϐ�
//*****************
int CPlayer::m_nLife = NULL;

//*****************
// �R���X�g���N�^
//*****************
CPlayer::CPlayer(int nPriority) :CObject(nPriority)
{
	// �ϐ��̃N���A
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_oldPos= D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	m_vecF = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	m_vecR = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fAngle = 0.0f;
	m_nIdxXFile = -1;
	m_nLife = 0;
	m_State = STATE_NONE;
	m_pMotion = NULL;
}

//*****************
// �f�X�g���N�^
//*****************
CPlayer::~CPlayer()
{
}

//******************
// �C���X�^���X����
//*******************
CPlayer* CPlayer::Create(D3DXVECTOR3 pos)
{
	CPlayer* pPlayer;// �v���C���[�̃|�C���^
	// �e�N�X�`�����̎擾
	CTexture* pTexture = CManager::GetCTexture();
	// ���݂̃I�u�W�F�N�g�̑����擾
	int nNum = CObject::GetNumAll();
	if (nNum < MAX_OBJ - 1)
	{// �I�u�W�F�N�g���ő吔�ɒB���Ă��Ȃ��ꍇ

		pPlayer = new CPlayer;		// �C���X�^���X����
		pPlayer->Init(pos);			// ������
		CCamera::SetPlayer(pPlayer);// �J�����̃^�[�Q�b�g�ɐݒ�

		// ����n��
		return pPlayer;				
	}

	// �I�u�W�F�N�g���ő吔�ɒB���Ă����ꍇ
	// NULL��Ԃ�
	return NULL;	
}

//*****************
// ����������
//*****************
HRESULT CPlayer::Init(D3DXVECTOR3 pos)
{
	m_pos = pos;// �ʒu�����ݒ�
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);// ���������ݒ�
	// ���f���̐���(�p�[�c��)
	if (m_pMotion == NULL)
	{// NULL��������
		// �C���X�^���X����
		m_pMotion = CMotion::Create("data\\MOTION\\segway.txt");
	}
	m_nLife = 3;// ���C�t�����ݒ�

	// ����������
	return S_OK;		
}

//*****************
// �I������
//*****************
void CPlayer::Uninit(void)
{
	m_pMotion->Uninit();
	delete m_pMotion;
	m_pMotion = NULL;
	CObject::Release();
}

//*****************
// �X�V����
//*****************
void CPlayer::Update(void)
{
	D3DXVECTOR3 pos = m_pos;// ���݂̈ʒu����
	m_oldPos = m_pos;
	CDebugProc::Print("\n�v���C���[�̈ʒu X:%f Y:%f Z:%f\n",pos.x,pos.y,pos.z);
	// �L�[�{�[�h�̎擾
	CInputKeyboard* pInputKeyboard;
	CInputJoypad* pInputJoypad;
	pInputKeyboard = CManager::GetCInputKeyboard();
	pInputJoypad = CManager::GetCInputJoypad();
	float RightSpeed=0.0f, LeftSpeed=0.0f;
	bool bLeftback = pInputKeyboard->GetPress(DIK_A) == true || pInputJoypad->GetPress(CInputJoypad::JOYKEY_DOWN) == true;	// ��:��
	bool bRightback = pInputKeyboard->GetPress(DIK_D) == true || pInputJoypad->GetPress(CInputJoypad::JOYKEY_A) == true;	// �E:��
	bool bLeftflont = pInputKeyboard->GetPress(DIK_Q) == true || pInputJoypad->GetPress(CInputJoypad::JOYKEY_UP) == true;	// ��:�O
	bool bRightflont = pInputKeyboard->GetPress(DIK_E) == true || pInputJoypad->GetPress(CInputJoypad::JOYKEY_Y) == true;	// �E:�O
	switch (m_State)
	{
	case CPlayer::STATE_NONE:

		if (bLeftback == true)
		{// �������������ɐi�ނƂ�
			if (bRightback == true)
			{// �E�����������̂Ƃ�
				RightSpeed = SPEED;
				m_pMotion->SetMotion(MOTION_BACK);
			}
			else if (bRightflont == true)
			{// �E�����O�����̂Ƃ�
				RightSpeed = -SPEED;
				m_pMotion->SetMotion(MOTION_BF);
			}
			else
			{
				m_pMotion->SetMotion(MOTION_LB);
			}
			LeftSpeed = SPEED;
		}
		else if (bLeftflont == true)
		{// �������O�����ɐi�ނƂ�
			if (bRightback == true)
			{// �E�����������̂Ƃ�
				RightSpeed = SPEED;
				m_pMotion->SetMotion(MOTION_FB);

			}
			else if (bRightflont == true)
			{// �E�����O�����̂Ƃ�
				RightSpeed = -SPEED;
				m_pMotion->SetMotion(MOTION_FLONT);
			}
			else
			{
				m_pMotion->SetMotion(MOTION_LF);
			}
			LeftSpeed = -SPEED;
		}
		else if (bRightback == true)
		{// �E�����������̂Ƃ�
			RightSpeed = SPEED;
			m_pMotion->SetMotion(MOTION_RB);
		}
		else if (bRightflont == true)
		{// �E�����O�����̂Ƃ�
			RightSpeed = -SPEED;
			m_pMotion->SetMotion(MOTION_RF);
		}
		else
		{
			m_pMotion->SetMotion(MOTION_NUETORAL);
		}
		if (pInputKeyboard->GetPress(DIK_W) == true
			|| pInputJoypad->GetPress(CInputJoypad::JOYKEY_UP) == true)
		{// D�܂��͉E�{�^��
			pos.y += SPEED;
		}
		if (pInputKeyboard->GetPress(DIK_S) == true
			|| pInputJoypad->GetPress(CInputJoypad::JOYKEY_Y) == true)
		{// D�܂��͉E�{�^��
			pos.y += -SPEED;
		}

		float speed = (RightSpeed + LeftSpeed) / 2.0f;
		float omega = (RightSpeed - LeftSpeed) / 50.0f; // ��]�����i�p���x�j
		m_move.x = sinf(m_fAngle) * speed;
		m_move.z = cosf(m_fAngle) * speed;
		m_fAngle += omega;
		// ���X�Ɏ~�܂�
		m_move.x += (0.0f - m_move.x) * 0.5f;
		m_move.z += (0.0f - m_move.z) * 0.5f;

		pos += m_move;	// ���݂̈ʒu��move�l�𑫂�

		CMesh* pMesh = CManager::GetCMesh();
		if (pInputKeyboard->GetPress(DIK_N) == true)
		{
			pMesh->MoveY(pos);
		}

		if (pInputKeyboard->Trigger(DIK_K) == true)
		{
			std::vector<int> p = { 19 };
			pMesh->Save(p, "data\\JSON\\j.json");
		}

		pos.y = pMesh->GetHeight(pos);
	}
	SetPos(pos);	// �ʒu��ݒ�
	SetRot(D3DXVECTOR3(0.0f, m_fAngle, 0.0f));
	m_pMotion->Update();
}

//*****************
// �`�揈��
//*****************
void CPlayer::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	CRenderer* renderer = CManager::GetCRenderer();
	pDevice = renderer->GetDevice();

	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;
	//���[���h�}�g���b�N�X�̏�����
	//D3DXMatrixIdentity(&m_mtxWorld);
	////�����𔽉f
	//D3DXMatrixRotationYawPitchRoll(&mtxRot, m_fAngle, m_rot.x, m_rot.z);
	//D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	//D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	//D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	Posture();

	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	m_pMotion->Draw();
}

//******************
// �ʒu�̐ݒ�
//*******************
void CPlayer::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}
//******************
// �����̐ݒ�
//*******************
void CPlayer::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//***************
// �̐��̐ݒ�
//***************
void CPlayer::Posture(void)
{
	CMesh* pMesh = CManager::GetCMesh();

	// �v���C���[�̏�x�N�g��
	D3DXVECTOR3 vecU = pMesh->GetNormal(m_pos);

	m_vecU += (vecU - m_vecU) * DEST;

	D3DXVECTOR3 vecF =-( m_pos - m_oldPos);

	D3DXVec3Normalize(&vecF, &vecF);

	if (D3DXVec3LengthSq(&vecF) > 0.001f)
	{
		m_vecF = vecF;
	}

	D3DXVECTOR3 baseForward = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	D3DXMATRIX rotMtx;
	D3DXMatrixRotationAxis(&rotMtx, &vecU, m_fAngle);

	D3DXVec3TransformNormal(&m_vecF, &baseForward, &rotMtx);


	D3DXVECTOR3 vecR,vecFa;
	D3DXVec3Cross(&vecR, &vecU, &m_vecF);
	D3DXVec3Normalize(&vecR, &vecR);
	m_vecR += (vecR-m_vecR) * DEST;
	D3DXVec3Cross(&m_vecF, &vecR, &vecU);
	D3DXVec3Normalize(&vecFa, &m_vecF);
	m_vecF += (vecFa- m_vecF) * DEST;
	D3DXMatrixIdentity(&m_mtxWorld); 

	// ���[���h�}�g���b�N�X�̍X�V
	m_mtxWorld._11 = m_vecR.x;
	m_mtxWorld._12 = m_vecR.y;
	m_mtxWorld._13 = m_vecR.z;
	m_mtxWorld._14 = 0;
	m_mtxWorld._21 = m_vecU.x;
	m_mtxWorld._22 = m_vecU.y;
	m_mtxWorld._23 = m_vecU.z;
	m_mtxWorld._24 = 0;
	m_mtxWorld._31 = m_vecF.x;
	m_mtxWorld._32 = m_vecF.y;
	m_mtxWorld._33 = m_vecF.z;
	m_mtxWorld._34 = 0;
	m_mtxWorld._41 = m_pos.x;
	m_mtxWorld._42 = m_pos.y;
	m_mtxWorld._43 = m_pos.z;
	m_mtxWorld._44 = 1;
}