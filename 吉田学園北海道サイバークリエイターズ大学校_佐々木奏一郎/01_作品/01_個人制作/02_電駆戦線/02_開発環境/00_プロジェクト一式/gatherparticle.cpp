//************************************************
//
// �W�܂�p�[�e�B�N������ [gatherParticle.cpp]
// Author:Sasaki Soichiro
//
//************************************************

//*******************
// �C���N���[�h
//*******************
#include "gatherparticle.h"
#include "manager.h"
#include "effect.h"
#include <time.h>
#include "gatherEffect.h"

//*****************
// �R���X�g���N�^
//*****************
CGatherParticle::CGatherParticle(int nPriority) :CObject(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR2(0.0f, 0.0f);
	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	m_fLength = 0.0f;	// �ړ�����
	m_nRad = 0;			// ���a
	m_nAngle = 0;		// ����
	m_nLife = 0;		// ����
	m_nAmount = 0;		// ��
	m_nTime = 0;		// ����
}

//*****************
// �f�X�g���N�^
//*****************
CGatherParticle::~CGatherParticle()
{
}

//*****************
// ����������
//*****************
HRESULT CGatherParticle::Init(D3DXVECTOR3 pos)
{
	m_pos = pos;
	m_fLength = 200.0f;	// �ړ�����
	m_nRad = 10;		// ���a
	m_nAngle = 629;		// ����
	m_nLife = 20;		// ����

	return S_OK;
}

//*****************
// �I������
//*****************
void CGatherParticle::Uninit(void)
{
	CObject::Release();
}

//*****************
// �X�V����
//*****************
void CGatherParticle::Update(void)
{

	for (int nCnt = 0; nCnt < 5; nCnt++)
	{
		// �����������ӂɃ����_���Ő���
		m_pos.x = m_pos.x + (float)(rand() % 50 - 25);
		m_pos.y = m_pos.y +20.0f+ (float)(rand() % 50 - 25);
		m_pos.z = m_pos.z + (float)(rand() % 50 - 25);

		// �G�t�F�N�g����
		CGatherEffect::Create(m_pos, m_size, m_nLife, m_col);
		// �J�E���g�����炷
		m_nAmount--;
		if (m_nAmount <= 0)
		{
			break;
		}
	}

	// ���ԂŏI��
	m_nTime--;
	if (m_nTime <= 0)
	{
		Uninit();
	}
}

//*****************
// �`�揈��
//*****************
void CGatherParticle::Draw(void)
{

}

//*******************
// �C���X�^���X����
//*******************
CGatherParticle* CGatherParticle::Create(D3DXVECTOR3 pos, int radius, D3DXVECTOR2 size, int nAmount, int nLife, int nTime, D3DXCOLOR col)
{
	// ���g�̃|�C���^
	CGatherParticle* pParticle;
	int nNum = GetNumAll();
	if (nNum < MAX_OBJ - 1)
	{
		// �C���X�^���X����
		pParticle = new CGatherParticle;
		// ������
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

//*****************
// �ʒu�ݒ�
//*****************
void CGatherParticle::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//*****************
// �����ݒ�
//*****************
void CGatherParticle::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//*****************
// �F�ݒ�
//*****************
void CGatherParticle::SetCol(D3DXCOLOR col)
{
	m_col = col;
}