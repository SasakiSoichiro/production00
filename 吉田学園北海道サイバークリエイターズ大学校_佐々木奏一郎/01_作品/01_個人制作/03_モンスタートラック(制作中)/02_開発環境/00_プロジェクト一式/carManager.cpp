//***************************************
//
// �ԃ}�l�[�W���[���� [carManager.cpp]
// Author:Sasaki Soichiro
//
//***************************************

//*******************
// �C���N���[�h
//*******************
#include "carManager.h"
#include "carBody.h"
#include "manager.h"
#include "renderer.h"

//*******************
// �R���X�g���N�^
//*******************
CCar::CCar()
{
	m_pCarBody=nullptr;
	m_mtxWorld={};
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//*******************
// �f�X�g���N�^
//*******************
CCar::~CCar()
{
}

CCar* CCar::Create(D3DXVECTOR3 pos)
{
	// ���g�̃|�C���^
	CCar* pCar;

	int nNum = CObject::GetNumAll();
	if (nNum < MAX_OBJ - 1)
	{// �I�u�W�F�N�g���ő吔�ɒB���Ă��Ȃ��ꍇ

		// �C���X�^���X����
		pCar = new CCar;

		// ������
		pCar->Init(pos);

		return pCar;
	}

	return NULL;

}

//*************
// ����������
//*************
HRESULT CCar::Init(D3DXVECTOR3 pos)
{
	m_pCarBody=CCarBody::Create(pos,"data\\MODEL\\truck.x");

	return S_OK;
}

//*************
// �I������
//*************
void CCar::Uninit(void)
{
	if (m_pCarBody != nullptr)
	{
		m_pCarBody->Uninit();
		delete m_pCarBody;
		m_pCarBody = nullptr;
	}

	CObject::Release();
}

//*************
// �X�V����
//*************
void CCar::Update(void)
{
	m_pCarBody->Update();
}

//*************
// �`�揈��
//*************
void CCar::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	CRenderer* renderer = CManager::GetCRenderer();
	pDevice = renderer->GetDevice();

	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;
	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);
	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	m_pCarBody->Draw();
}

