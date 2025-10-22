//**********************************
//
// ���[���Ǘ����� [railManager.cpp]
// Author:Sasaki Soichiro
//
//**********************************

//*******************
// �C���N���[�h
//*******************
#include "railManager.h"
#include "pause.h"
#include "input.h"
#include "manager.h"
#include "rail.h"

//*****************
// �ÓI�����o�ϐ�
//*****************
CRail* CRailManager::m_pRail[2] = {};

//*****************
// �R���X�g���N�^
//*****************
CRailManager::CRailManager()
{
}

//*****************
// �f�X�g���N�^
//*****************
CRailManager::~CRailManager()
{
}

//*****************
// ����������
//*****************
HRESULT CRailManager::Init(void)
{
	int nNumPoint = 8;
	CRail::InitAll();
	D3DXVECTOR3 Railpos[11];
	for (int nCnt = 0; nCnt < 11; nCnt++)
	{// ���[���̐���_�ݒ�
		float fAngle = D3DX_PI * 2.0f * 1 / nNumPoint;
		Railpos[nCnt].x = cosf(fAngle * (nCnt % 8)) * 350.0f;
		Railpos[nCnt].y = 10.0f;
		Railpos[nCnt].z = sinf(fAngle * (nCnt % 8)) * 350.0f;
	}

	// ���[�� �[�d�^�C�v
	m_pRail[0] = CRail::Create(Railpos[0], Railpos[1], Railpos[2], Railpos[3], 0);

	for (int nCnt = 4; nCnt < 11; nCnt++)
	{// ���[���̐���_�ǉ�
		m_pRail[0]->AddPoint(Railpos[nCnt]);
	}

	D3DXVECTOR3 RailPosS[11];
	for (int nCnt = 0; nCnt < 11; nCnt++)
	{// ���[���̐���_�ݒ�
		float fAngle = D3DX_PI * 2.0f * 1 / nNumPoint;
		RailPosS[nCnt].x = cosf(fAngle * (nCnt % 8)) * 400.0f;
		RailPosS[nCnt].y = 10.0f;
		RailPosS[nCnt].z = sinf(fAngle * (nCnt % 8)) * 400.0f;
	}

	// ���[�� ���d�^�C�v
	m_pRail[1] = CRail::Create(RailPosS[0], RailPosS[1], RailPosS[2], RailPosS[3], 1);

	for (int nCnt = 4; nCnt < 11; nCnt++)
	{// ���[���̐���_�ǉ�
		m_pRail[1]->AddPoint(RailPosS[nCnt]);
	}

	return S_OK;
}

//*****************
// �I������
//*****************
void CRailManager::Uninit(void)
{

}

//*****************
// �X�V����
//*****************
void CRailManager::Update(void)
{
}