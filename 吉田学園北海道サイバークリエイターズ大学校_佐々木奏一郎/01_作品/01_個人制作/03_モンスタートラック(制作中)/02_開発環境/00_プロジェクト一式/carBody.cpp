//*****************************************
//
// �v���C���[���� [player.cpp]
// Author:Sasaki Soichiro
//
//*****************************************

//*******************
// �C���N���[�h
//*******************
#include "carBody.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "texture.h"
#include "camera.h"
#include "object3D.h"
#include "game.h"
#include "blurManager.h"
#include "blockManager.h"
#include "motion.h"
#include "state.h"
#include "mesh.h"
#include "sound.h"
#include "debugproc.h"
#include "wheel.h"

//*****************
// �R���X�g���N�^
//*****************
CCarBody::CCarBody(int nPriority)
{
	// �ϐ��̃N���A
	m_oldPos = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	m_vecF = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	m_vecR = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fAngle = 0.0f;
	m_nIdxXFile = -1;
	m_fSpeed = 0.0f;
	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		m_pWheel[nCnt] = nullptr;
	}
}

//*****************
// �f�X�g���N�^
//*****************
CCarBody::~CCarBody()
{
}

//******************
// �C���X�^���X����
//*******************
CCarBody* CCarBody::Create(D3DXVECTOR3 pos, const char* pFileName)
{
	// ���g�̃|�C���^
	CCarBody* pCarBody;
	// XModel�擾
	CXModel* pXModel = CManager::GetCXModel();
	// ���݂̃I�u�W�F�N�g�̑����擾
	int nNum = CObject::GetNumAll();
	if (nNum < MAX_OBJ - 1)
	{// �I�u�W�F�N�g���ő吔�ɒB���Ă��Ȃ��ꍇ

		// �C���X�^���X����
		pCarBody = new CCarBody;

		pCarBody->SetIdxXFile(pXModel->Register(pFileName));
		// ������
		pCarBody->Init(pos);

		return pCarBody;
	}

	return NULL;
}

//*****************
// ����������
//*****************
HRESULT CCarBody::Init(D3DXVECTOR3 pos)
{

	CModel::Init(pos);

	m_pWheel[0] = CWheel::Create(D3DXVECTOR3(fWheelOffsetLeft, -fWheelOffsetY, fWheelOffsetFlont), "data\\MODEL\\03_tire.x");
	m_pWheel[1] = CWheel::Create(D3DXVECTOR3(fWheelOffsetRight, -fWheelOffsetY, fWheelOffsetFlont), "data\\MODEL\\01_tire.x");
	m_pWheel[2] = CWheel::Create(D3DXVECTOR3(fWheelOffsetLeft, -fWheelOffsetY, fWheelOffsetRear), "data\\MODEL\\02_tire.x");
	m_pWheel[3] = CWheel::Create(D3DXVECTOR3(fWheelOffsetRight, -fWheelOffsetY, fWheelOffsetRear), "data\\MODEL\\00_tire.x");

	SetWheel();

	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		m_pWheel[nCnt]->SetOffsetY(20.0f);
	}

	SetPos(D3DXVECTOR3(pos.x, fWheelOffsetY * 2, pos.z));

	return S_OK;
}

//*****************
// �I������
//*****************
void CCarBody::Uninit(void)
{
	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		m_pWheel[nCnt]->Uninit();
		delete m_pWheel[nCnt];
		m_pWheel[nCnt] = nullptr;
	}

	CModel::Uninit();
}

//*****************
// �X�V����
//*****************
void CCarBody::Update(void)
{
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();
	float fDeltaHeight[4];
	CInputKeyboard* pKeyboard = CManager::GetCInputKeyboard();
	CCamera* pCamera = CManager::GetCCamera();

	if (pKeyboard->GetPress(DIK_W))
	{
		m_fSpeed += 0.1f;

	}
	else if (pKeyboard->GetPress(DIK_S))
	{
		m_fSpeed -= 0.1f;

	}
	else
	{
		m_fSpeed += (0.0f - m_fSpeed) * 0.05f;
	}

	if (pKeyboard->GetPress(DIK_A))
	{
		m_fAngle -= fDeltaAngle;
	}
	else if (pKeyboard->GetPress(DIK_D))
	{
		m_fAngle += fDeltaAngle;
	}
	else
	{
		m_fAngle += (0.0f - m_fAngle) * 0.05f;
	}


	if (m_fSpeed > fMaxSpeed)
	{
		m_fSpeed = fMaxSpeed;
	}
	else if (m_fSpeed < -fMaxSpeed)
	{
		m_fSpeed = -fMaxSpeed;
	}

	if (m_fAngle > fMaxAngle)
	{
		m_fAngle = fMaxAngle;
	}
	else if (m_fAngle < -fMaxAngle)
	{
		m_fAngle = -fMaxAngle;
	}


	// �^�C���̍X�V
	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		m_pWheel[nCnt]->Update();
	}

	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		fDeltaHeight[nCnt] = m_pWheel[nCnt]->GetDeltaHeight();
	}

	// �e�z�C�[������̗͂̕��ς����߂�
	float fHeight = (fDeltaHeight[0] + fDeltaHeight[1] + fDeltaHeight[2] + fDeltaHeight[3]) / 4;

	// �O��ƍ��E�̍����̍����Ō��������߂�
	float LR = atanf((fDeltaHeight[0] - fDeltaHeight[1]) / 40.0f) + atanf((fDeltaHeight[2] - fDeltaHeight[3]) / 40.0f);
	LR = LR / 2;
	float FR = atanf((fDeltaHeight[0] - fDeltaHeight[2]) / 40.0f) + atanf((fDeltaHeight[1] - fDeltaHeight[3]) / 40.0f);
	FR = FR / 2;

	m_pWheel[0]->SetRot(D3DXVECTOR3(0.0f,m_fAngle,0.0f));
	m_pWheel[2]->SetRot(D3DXVECTOR3(0.0f,m_fAngle,0.0f));

	
	// �ω��ʂ𑫂��Ă΂˂̗h������
	pos.y += fHeight;

	pos.x -= cosf(-rot.y) * m_fSpeed;
	pos.z -= sinf(-rot.y) * m_fSpeed;

	pCamera->Target(pos, rot);

	SetPos(D3DXVECTOR3(pos.x, pos.y, pos.z));

	rot.y += m_fAngle * (m_fSpeed / fMaxSpeed) * 0.04f;

	SetRot(D3DXVECTOR3(-FR, rot.y, -LR));


	// �ڑ������̍����X�V
	WheelAttachY();
}

//*****************
// �`�揈��
//*****************
void CCarBody::Draw(void)
{
	CModel::Draw();

	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		m_pWheel[nCnt]->Draw();
	}
}

//********************
// �z�C�[���̈ʒu�ݒ�
//********************
void CCarBody::SetWheel(void)
{
	// �z�C�[���̈ʒu�ݒ�
	//m_pWheel[0]->SetPos(D3DXVECTOR3(fWheelOffsetLeft, -fWheelOffsetY * 2, fWheelOffsetFlont));
	//m_pWheel[1]->SetPos(D3DXVECTOR3(fWheelOffsetRight, -fWheelOffsetY * 2, fWheelOffsetFlont));
	//m_pWheel[2]->SetPos(D3DXVECTOR3(fWheelOffsetLeft, -fWheelOffsetY * 2, fWheelOffsetRear));
	//m_pWheel[3]->SetPos(D3DXVECTOR3(fWheelOffsetRight,-fWheelOffsetY * 2, fWheelOffsetRear));

	// �z�C�[���̌����Ɛe�ݒ�
	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		m_pWheel[nCnt]->SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		m_pWheel[nCnt]->SetParent(this);
		m_pWheel[nCnt]->SetCarBody(this);
	}
}

//**************************
// �z�C�[���̐ڑ������̍���
//**************************
void CCarBody::WheelAttachY(void)
{
	D3DXVECTOR3 offset[4];
	offset[0]=D3DXVECTOR3(fWheelOffsetLeft, -fWheelOffsetY, fWheelOffsetFlont);
	offset[1]=D3DXVECTOR3(fWheelOffsetRight, -fWheelOffsetY, fWheelOffsetFlont);
	offset[2]=D3DXVECTOR3(fWheelOffsetLeft, -fWheelOffsetY, fWheelOffsetRear);
	offset[3]=D3DXVECTOR3(fWheelOffsetRight, -fWheelOffsetY, fWheelOffsetRear);

	D3DXMATRIX mtx = GetMtxWorld();

	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		D3DXVECTOR3 wldPos;
		D3DXVec3TransformCoord(&wldPos, &offset[nCnt], &mtx);

		m_pWheel[nCnt]->SetAttachY(wldPos.y);
	}

}

//******************
// �ʒu�̐ݒ�
//*******************
void CCarBody::SetPos(D3DXVECTOR3 pos)
{
	CModel::SetPos(pos);
}
//******************
// �����̐ݒ�
//*******************
void CCarBody::SetRot(D3DXVECTOR3 rot)
{
	CModel::SetRot(rot);
}

//******************
// ���x�̐ݒ�
//*******************
void CCarBody::SetMove(D3DXVECTOR3 move)
{
	m_move = move;
}