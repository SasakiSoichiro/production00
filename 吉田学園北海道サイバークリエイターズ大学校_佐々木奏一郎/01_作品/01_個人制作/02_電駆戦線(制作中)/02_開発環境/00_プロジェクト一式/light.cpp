//**********************************
//
// ���C�g���� [light.cpp]
// Author:Sasaki Soichiro
//
//**********************************

//*******************
// �C���N���[�h
//*******************
#include "light.h"
#include "manager.h"

//*****************
// �R���X�g���N�^
//*****************
CLight::CLight()
{
	for(int nCnt = 0; nCnt < MAX_LIGHT; nCnt++)
	{
		m_aLight[nCnt] = {};
		m_aVec[nCnt] = {};
	}
}

//*****************
// �f�X�g���N�^
//*****************
CLight::~CLight()
{
}

//**********
//  ������
//**********
void CLight::Init(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	CRenderer* renderer = CManager::GetCRenderer();
	pDevice = renderer->GetDevice();

	//���C�g���N���A����
	ZeroMemory(&m_aLight, sizeof(m_aLight));

	// ���C�g�ݒ�
	for (int nCnt = 0; nCnt < 3; nCnt++)
	{
		m_aVec[nCnt];

		//���C�g�̎�ނ�ݒ�
		m_aLight[nCnt].Type = D3DLIGHT_DIRECTIONAL;

		//���C�g�̊g�U����ݒ�
		m_aLight[nCnt].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	}

	//���C�g�̕�����ݒ�(��)
	m_aVec[0] = D3DXVECTOR3(0.0f, -1.0f, -0.0f);
	m_aVec[1] = D3DXVECTOR3(0.3f, -0.8f, 0.8f);
	m_aVec[2] = D3DXVECTOR3(-0.4f, 0.8f, -0.9f);

	for (int nCnt = 0; nCnt < 3; nCnt++)
	{
		//���K������(�傫���P�̃x�N�g���ɂ���)
		D3DXVec3Normalize(&m_aVec[nCnt], &m_aVec[nCnt]);
		m_aLight[nCnt].Direction = m_aVec[nCnt];

		//���C�g��ݒ肷��
		pDevice->SetLight(nCnt, &m_aLight[nCnt]);

		//���C�g��L���ɂ���
		pDevice->LightEnable(nCnt, TRUE);

	}
}

//************
// �I������
//************
void CLight::Uninit(void)
{

}

//************
// �X�V����
//************
void CLight::Update(void)
{

}