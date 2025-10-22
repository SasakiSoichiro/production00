//**********************************
//
// ���p�[�e�B�N������ [smokeParticle.cpp]
// Author:Sasaki Soichiro
//
//**********************************

//*******************
// �C���N���[�h
//*******************
#include "smokeParticle.h"
#include "manager.h"
#include "effect.h"
#include <time.h>
#include "smoke.h"

//=================
// �R���X�g���N�^
//=================
CSmokeParticle::CSmokeParticle(int nPriority) :CObject(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR2(0.0f, 0.0f);
	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	m_fLength = 0.0f;	// �ړ�����
	m_nRad = 0;			// ���a
	m_nAngle = 0;		// ����
	m_nLife = 0;		// ����
}

//=================
// �f�X�g���N�^
//=================
CSmokeParticle::~CSmokeParticle()
{
}

//=================
// ����������
//=================
HRESULT CSmokeParticle::Init(D3DXVECTOR3 pos)
{
	m_pos = pos;
	m_fLength = 200.0f;	// �ړ�����
	m_nRad = 10;		// ���a
	m_nAngle = 629;		// ����
	m_nLife = 20;		// ����

	return S_OK;
}

//=================
// �I������
//=================
void CSmokeParticle::Uninit(void)
{
	CObject::Release();
}

//=================
// �X�V����
//=================
void CSmokeParticle::Update(void)
{

	for (int nCnt = 0; nCnt < 5; nCnt++)
	{

		//for (int nCntS = 0; nCntS < 2; nCntS++)
		//{
		float fAngle = (float)(rand() % m_nAngle - 314) / 100.0f;
		float fLength = (float)(rand() % m_nRad) /*/ m_fLength + 10.0f*/;

		D3DXVECTOR3 rot = NONE;
		D3DXVECTOR3 pos = m_pos;
		pos.x = m_pos.x + sinf(fAngle) * fLength;
		pos.z = m_pos.z + cosf(fAngle) * fLength;
		rot.z = (float)(rand() % m_nAngle - 314) / 100.0f;
		CSmoke::Create(pos, D3DXVECTOR3(0.0f,2.0f,0.0f), rot, m_size, m_nLife, m_col);
		m_nAmount--;
		if (m_nAmount <= 0)
		{
			break;
		}
	}
	m_nTime--;
	if (m_nTime <= 0)
	{
		Uninit();
	}
}

//=================
// �`�揈��
//=================
void CSmokeParticle::Draw(void)
{

}
CSmokeParticle* CSmokeParticle::Create(D3DXVECTOR3 pos, int radius, D3DXVECTOR2 size, int nAmount, int nLife, int nTime, D3DXCOLOR col)
{
	CSmokeParticle* pParticle;
	int nNum = GetNumAll();
	if (nNum < MAX_OBJ - 1)
	{
		pParticle = new CSmokeParticle;
		pParticle->Init(pos);
		pParticle->SetCol(col);
		pParticle->SetRadius(radius);
		pParticle->SetSize(size);
		pParticle->SetAmount(nAmount);
		pParticle->m_nLife = nLife;
		pParticle->SetTime(nTime);
		return pParticle;
	}
	return NULL;
}

void CSmokeParticle::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}
void CSmokeParticle::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}
void CSmokeParticle::SetCol(D3DXCOLOR col)
{
	m_col = col;
}