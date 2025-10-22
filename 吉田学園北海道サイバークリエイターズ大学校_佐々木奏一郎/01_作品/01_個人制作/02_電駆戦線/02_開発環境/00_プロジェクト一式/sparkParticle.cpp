//*******************************************
//
// �U��p�[�e�B�N������ [sparkParticle.cpp]
// Author:Sasaki Soichiro
//
//*******************************************

//*******************
// �C���N���[�h
//*******************
#include "sparkParticle.h"
#include "manager.h"
#include "effect.h"
#include <time.h>
#include "sparkEffect.h"

//=================
// �R���X�g���N�^
//=================
CSparkParticle::CSparkParticle(int nPriority) :CObject(nPriority)
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
CSparkParticle::~CSparkParticle()
{
}

//=================
// ����������
//=================
HRESULT CSparkParticle::Init(D3DXVECTOR3 pos)
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
void CSparkParticle::Uninit(void)
{
	CObject::Release();
}

//=================
// �X�V����
//=================
void CSparkParticle::Update(void)
{

	for (int nCnt = 0; nCnt < 5; nCnt++)
	{
		D3DXVECTOR3 move;

		move.x = (float)(rand() % 10 - 5)*0.3f;
		move.y = (float)(rand() % 10 - 5)*0.3f;
		move.z = (float)(rand() % 10 - 5)*0.3f;


		D3DXVECTOR3 rot = NONE;
		CSparkEffect::Create(m_pos, move, m_size, m_nLife, m_col);
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
void CSparkParticle::Draw(void)
{

}
CSparkParticle* CSparkParticle::Create(D3DXVECTOR3 pos, int radius, D3DXVECTOR2 size, int nAmount, int nLife, int nTime, D3DXCOLOR col)
{
	CSparkParticle* pParticle;
	int nNum = GetNumAll();
	if (nNum < MAX_OBJ - 1)
	{
		pParticle = new CSparkParticle;
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

void CSparkParticle::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}
void CSparkParticle::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}
void CSparkParticle::SetCol(D3DXCOLOR col)
{
	m_col = col;
}