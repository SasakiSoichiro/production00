//*****************************************
//
// �v���C���[���� [player.cpp]
// Author:Sasaki Soichiro
//
//*****************************************

//*******************
// �C���N���[�h
//*******************
#include "enemyState.h"
#include "enemy.h"
#include "manager.h"
#include "game.h"
#include "particle.h"
#include "slow.h"
#include "smokeParticle.h"
#include "sound.h"
#include "player.h"

//******************
// �R���X�g���N�^
//******************
CEnemyStateBase::CEnemyStateBase()
{
	m_pEnemy = NULL;
}

//******************
// �f�X�g���N�^
//******************
CEnemyStateBase::~CEnemyStateBase()
{

}

//************************
// �G�l�~�[�̃|�C���^�ݒ�
//************************
void CEnemyStateBase::SetOwner(CEnemy* pEnemy)
{
	m_pEnemy = pEnemy;
}

//******************
// �R���X�g���N�^
//******************
CNuetoralState::CNuetoralState()
{

}

//******************
// �f�X�g���N�^
//******************
CNuetoralState::~CNuetoralState()
{

}

//**************
// ������
//**************
void CNuetoralState::Init(void)
{
	// �j���[�g�������[�V����
	m_pEnemy->SetMotion(0);
}

//***************
// �X�V����
//***************
void CNuetoralState::Update(void)
{
	// �v���C���[���߂��ɗ�����ǂ�������
	if (m_pEnemy->Chase()==true)
	{
		// ��ԕύX
		CChaseState* pChaseState = new CChaseState;
		m_pEnemy->ChangeState(pChaseState);
	}
}

//*************
// �I������
//*************
void CNuetoralState::Uninit(void)
{

}

//*****************
// �R���X�g���N�^
//*****************
CChaseState::CChaseState()
{

}

//*****************
// �f�X�g���N�^
//*****************
CChaseState::~CChaseState()
{

}

//*************
// ����������
//*************
void CChaseState::Init(void)
{
	
}

//*************
// �X�V����
//*************
void CChaseState::Update(void)
{
	// �ǂ������郂�[�V����
	m_pEnemy->SetMotion(CEnemy::MOTION_MOVE);
	// �v���C���[�̈ʒu�擾
	CPlayer*pPlayer=CGame::GetCPlayer();
	D3DXVECTOR3 playerPos = pPlayer->GetPos();
	// �X���[�擾
	CSlow* pSlow = CGame::GetCSlow();
	// �ʒu�ƌ����擾
	D3DXVECTOR3 pos = m_pEnemy->GetPos();
	D3DXVECTOR3 rot = m_pEnemy->GetRot();

	// �v���C���[��ǂ�������
	float DistanceX = pos.x - playerPos.x;
	float DistanceZ = pos.z - playerPos.z;
	float fAngle = atan2f(DistanceX, DistanceZ);
	float fSpeed = m_pEnemy->GetSpeed() * pSlow->GetfDivi();
	pos.x += -sinf(fAngle) * fSpeed;
	pos.z += -cosf(fAngle) * fSpeed;

	// ���K��
	if (fAngle - rot.y > D3DX_PI)
	{
		rot.y = rot.y + (D3DX_PI * 2);
	}
	else if (rot.y - fAngle > D3DX_PI)
	{
		rot.y = rot.y - (D3DX_PI * 2);
	}

	// ������������ς���
	rot.y += (fAngle - rot.y) * 0.1f;
	// ���f
	m_pEnemy->SetPos(pos);
	m_pEnemy->SetRot(rot);

	// ��ԕύX����
	if (m_pEnemy->Attack() == true)
	{// �U��������true
		CAttackState* pAttackState = new CAttackState;
		m_pEnemy->ChangeState(pAttackState);
	}
	else if (m_pEnemy->Nuetoral() == true)
	{// �ҋ@������true
		CNuetoralState* pNuetoralState = new CNuetoralState;
		m_pEnemy->ChangeState(pNuetoralState);
	}
	else if (m_pEnemy->Hit() == true)
	{// HIT������true
		CHitState* pHitState = new CHitState;
		m_pEnemy->ChangeState(pHitState);
	}

}

//*************
// �I������
//*************
void CChaseState::Uninit(void)
{

}

//****************
// �R���X�g���N�^
//****************
CAttackState::CAttackState()
{

}

//****************
// �f�X�g���N�^
//****************
CAttackState::~CAttackState()
{

}

//*************
// ����������
//*************
void CAttackState::Init(void)
{
	// �U�����[�V����
	m_pEnemy->SetMotion(2);
}

//*************
// �X�V����
//*************
void CAttackState::Update(void)
{
	// �U�������X�V
	if (m_pEnemy->AttackUpdate() == true)
	{// �U���X�V���I�������

		// ��ԕύX����
		if (m_pEnemy->Chase() == true)
		{// �ǂ������������true
			CChaseState* pChaseState = new CChaseState;
			m_pEnemy->ChangeState(pChaseState);
		}
		else if (m_pEnemy->Nuetoral() == true)
		{// �ҋ@������true
			CNuetoralState* pNuetoralState = new CNuetoralState;
			m_pEnemy->ChangeState(pNuetoralState);
		}
	}
	else if (m_pEnemy->Hit() == true)
	{// HIT������true
		CHitState* pHitState = new CHitState;
		m_pEnemy->ChangeState(pHitState);
	}
}

//*************
// �I������
//*************
void CAttackState::Uninit(void)
{
	
}

//*****************
// �R���X�g���N�^
//*****************
CHitState::CHitState()
{

}

//*****************
// �f�X�g���N�^
//*****************
CHitState::~CHitState()
{

}

//*****************
// ����������
//*****************
void CHitState::Init(void)
{
	// �T�E���h�擾
	CSound* pSound = CManager::GetCSound();
	// HIT�T�E���h���Đ�
	pSound->Play(CSound::LABEL_SE02);
	// ���p�[�e�B�N������
	CSmokeParticle::Create(m_pEnemy->GetPos(), 20, D3DXVECTOR2(25.0f, 25.0f), 5, 20, 20, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
}

//*****************
// �X�V����
//*****************
void CHitState::Update(void)
{
	// �v���C���[�ƃT�E���h�擾
	CPlayer* pPlayer = CGame::GetCPlayer();
	CSound* pSound = CManager::GetCSound();

	// �̗͎擾
	int nLife = m_pEnemy->GetLife();
	// �U���͎擾
	nLife-=pPlayer->GetATK();
	if (nLife <= 0)
	{// �̗͂�0�ȉ��ɂȂ�����
		// �T�E���h�Đ�
		pSound->Stop(CSound::LABEL_SE05);
		// ���f
		m_pEnemy->SetLife(nLife);
		// ��ԕύX
		CDownState* pDownState = new CDownState;
		m_pEnemy->ChangeState(pDownState);
		return;
	}
	else
	{// �̗͂��܂���������
		// ���f
		m_pEnemy->SetLife(nLife);
		// ��ԕύX
		CNuetoralState* pNuetoralState = new CNuetoralState;
		m_pEnemy->ChangeState(pNuetoralState);
		return;
	}
}

//*****************
// �I������
//*****************
void CHitState::Uninit(void)
{

}

//********************
// �R���X�g���N�^
//********************
CDownState::CDownState()
{

}
//********************
// �f�X�g���N�^
//********************
CDownState::~CDownState()
{

}

//*************
// ����������
//*************
void CDownState::Init(void)
{
	// �T�E���h�擾
	CSound* pSound = CManager::GetCSound();
	// �T�E���h�Đ�
	pSound->Play(CSound::LABEL_SE02);
	// ���p�[�e�B�N������
	CSmokeParticle::Create(m_pEnemy->GetPos(), 20, D3DXVECTOR2(25.0f, 25.0f), 5, 20, 20, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
}

//*************
// �X�V����
//*************
void CDownState::Update(void)
{
	// ���ʃ��[�V����
	m_pEnemy->SetMotion(CEnemy::MOTION_DIE);
}

//*************
// �I������
//*************
void CDownState::Uninit(void)
{

}