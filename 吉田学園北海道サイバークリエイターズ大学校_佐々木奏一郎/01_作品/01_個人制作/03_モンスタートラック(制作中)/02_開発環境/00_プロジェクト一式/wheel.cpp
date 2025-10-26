//*****************************************
//
// �d�C�򏈗� [fence.cpp]
// Author:Sasaki Soichiro
//
//*****************************************

//*******************
// �C���N���[�h
//*******************
#include "wheel.h"
#include "renderer.h"
#include "manager.h"
#include "game.h"
#include "sound.h"
#include "mesh.h"
#include "carBody.h"

//******************
// �}�N����`
//******************
#define DISTANCE (150.0f)	// �x���̋���
#define RADIUS (90.0f)		// �U���̔��a

//*****************
// �R���X�g���N�^
//*****************
CWheel::CWheel(int nPriority)
{
	m_fOffset = 0.0f;
	m_fSuspension = 0.0f;
	m_fSuspensionOld = 0.0f;
	m_fDeltaHeight = 0.0f;
	m_fAttachY = 0.0f;
	m_pCarBody = nullptr;
}

//*****************
// �f�X�g���N�^
//*****************
CWheel::~CWheel()
{
}

//******************
// �C���X�^���X����
//*******************
CWheel* CWheel::Create(D3DXVECTOR3 pos, const char* pFileName)
{
	// ���g�̃|�C���^
	CWheel* pWheel;
	// XModel�擾
	CXModel* pXModel = CManager::GetCXModel();

	int nNum = CObject::GetNumAll();
	if (nNum < MAX_OBJ - 1)
	{// �I�u�W�F�N�g���ő吔�ɒB���Ă��Ȃ��ꍇ

		// �C���X�^���X����
		pWheel = new CWheel;

		pWheel->SetIdxXFile(pXModel->Register(pFileName));
		// ������
		pWheel->Init(pos);

		return pWheel;
	}

	return NULL;
}

//*****************
// ����������
//*****************
HRESULT CWheel::Init(D3DXVECTOR3 pos)
{
	CModel::Init(pos);
	m_fSuspension = fSusRest;
	return S_OK;
}

//*****************
// �I������
//*****************
void CWheel::Uninit(void)
{
	CModel::Uninit();
}

//*****************
// �X�V����
//*****************
void CWheel::Update(void)
{
	// ���b�V���Ƃ̓����蔻��
	CollisionMesh();
}

//*****************
// �`�揈��
//*****************
void CWheel::Draw(void)
{
	CModel ::Draw();
}

//*****************
// �ʒu�̐ݒ�
//*****************
void CWheel::SetPosion(D3DXVECTOR3 pos)
{

}

//******************
// �ʒu�̐ݒ�
//******************
void CWheel::SetPos(D3DXVECTOR3 pos)
{
	CModel::SetPos(pos);
}

//******************
// �����̐ݒ�
//******************
void CWheel::SetRot(D3DXVECTOR3 rot)
{
	CModel::SetRot(rot);
}

//******************
// �ʒu���̎擾
//******************
D3DXVECTOR3 CWheel::GetPos(void)
{
	return CModel::GetPos();
}

//******************
// �������̎擾
//******************
D3DXVECTOR3 CWheel::GetRot(void)
{
	return CModel::GetRot();
}

//************************
// ���b�V���Ƃ̂����蔻��
//************************
void CWheel::CollisionMesh(void)
{
	D3DXMATRIX mtx = GetMtxWorld();

	if (m_pCarBody == nullptr)
	{
		return;
	}
	D3DXMATRIX carMtx = m_pCarBody->GetMtxWorld();
	// �t�s��쐬
	D3DXMATRIX invCarMtx;

	D3DXMatrixInverse(&invCarMtx,nullptr,&carMtx);

	// �ʒu�擾
	D3DXVECTOR3 pos = GetPos();
	// ���b�V�����擾
	CMesh* pMesh = CGame::GetCMesh();

	// �n�ʂ̍���
	float meshHeight = pMesh->GetHeight(D3DXVECTOR3(mtx._41, mtx._42, mtx._43));

	// �^�C���̍���
	mtx._42 = meshHeight + fRadius;

	m_fSuspensionOld = m_fSuspension;
	// �T�X�y���V�����̒���
	m_fSuspension = m_fAttachY - mtx._42;

	float Spring = (fSusRest - m_fSuspension)* fSpringK;

	float Danper = -(m_fSuspension - m_fSuspensionOld)* fDanperC;

	m_fDeltaHeight = Spring + Danper;
	m_fDeltaHeight = m_fDeltaHeight*0.04f;

	//if (m_fSuspension > fSusMax)
	//{// �ő�̒����𒴂�����
	//	m_fDeltaHeight = m_fSuspension - fSusMax;
	//}
	//else if (m_fSuspension < fSusMin)
	//{// �ŏ��̒����𒴂�����
	//	m_fDeltaHeight = m_fSuspension - fSusMin;
	//}
	//else
	//{
	//	m_fDeltaHeight = 0.0f;
	//}

	pos.y = meshHeight - fRadius;

	D3DXVECTOR3 wldPos = D3DXVECTOR3(mtx._41, mtx._42, mtx._43);
	D3DXVECTOR3 lclPos;

	D3DXVec3TransformCoord(&lclPos, &wldPos, &invCarMtx);

	// �ʒu�𔽉f
	SetPos(D3DXVECTOR3(pos.x,lclPos.y,pos.z));
}