//*****************************************
//
// �G�l�~�[���� [enemychild.cpp]
// Author:Sasaki Soichiro
//
//*****************************************

//*******************
// �C���N���[�h
//*******************
#include "enemychild.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "texture.h"
#include "camera.h"
#include "object3D.h"
#include "player.h"
#include "game.h"
#include "particle.h"
#include "score.h"
#include "combo.h"
#include "slow.h"
#include "blurManager.h"
#include "sound.h"
#include "motion.h"

//****************
// �R���X�g���N�^
//****************
CSpiderEnemy::CSpiderEnemy()
{
	m_fAttackFps = 0;
	m_bAttackSound = false;
	m_bAngle = false;
	m_nHitCool = 0;
}

//****************
// �f�X�g���N�^
//****************
CSpiderEnemy::~CSpiderEnemy()
{

}

//****************
// ����������
//****************
HRESULT CSpiderEnemy::Init(D3DXVECTOR3 pos)
{
	CEnemy::LoadMotion("data\\MOTION\\spider.txt");
	CEnemy::Init(pos);
	CEnemy::SetSpeed(SPEED);
	
	return S_OK;
}

//****************
// �I������
//****************
void CSpiderEnemy::Uninit(void)
{
	CEnemy::Uninit();
}

//****************
// �X�V����
//****************
void CSpiderEnemy::Update(void)
{
	CEnemy::Update();
}

//****************
// �`�揈��
//****************
void CSpiderEnemy::Draw(void)
{
	CEnemy::Draw();
}

//****************
// �ǂ����������
//****************
bool CSpiderEnemy::Chase(void)
{
	return CEnemy::Distance(200.0f);
}

//****************
// �U���������
//****************
bool CSpiderEnemy::Attack(void)
{
	return CEnemy::Distance(70.0f);
}

//****************
// �~�܂����
//****************
bool CSpiderEnemy::Nuetoral(void)
{
	return !CEnemy::Distance(200.0f);
}

//****************
// ��������
//****************
bool CSpiderEnemy::Hit(void)
{
	// �v���C���[�̈ʒu�擾
	CPlayer* pPlayer = CGame::GetCPlayer();
	D3DXVECTOR3 playerPos = pPlayer->GetPos();
	// �T�E���h�擾
	CSound* pSound = CManager::GetCSound();
	// �ʒu�擾
	D3DXVECTOR3 pos = GetPos();

	// �����蔻��v�Z
	float DistX, DistY, DistZ;
	// ���̋���
	DistX = playerPos.x - pos.x;
	DistY = playerPos.y - pos.y;
	DistZ = playerPos.z - pos.z;
	float Dist = sqrtf((DistX * DistX) + (DistY * DistY) + (DistZ * DistZ));

	m_nHitCool++;
	// �q�b�g�̏���
	bool bHit = Dist < Range
		&& pPlayer->GetState() != CPlayer::STATE_RAIL
		&&m_nHitCool>hitCool;

	if (bHit)
	{// �q�b�g������

		if (pPlayer->GetState() == CPlayer::STATE_NONE)
		{
			pPlayer->SetMove(D3DXVECTOR3(DistX * 0.05f, 0.0f, DistZ * 0.05f));
			// �v���C���[�̏�Ԃ�ύX
			pPlayer->SetState(CPlayer::STATE_INOPERABLE);
			CInoperableState* pInoperableState = new CInoperableState;
			pPlayer->ChangeState(pInoperableState);

		}

		m_nHitCool = 0;
		return true;
	}
	return false;
}

//******************
// �U���̍X�V
//******************
bool CSpiderEnemy::AttackUpdate(void)
{
	m_fAttackFps++;
	// �v���C���[�擾
	CPlayer* pPlayer = CGame::GetCPlayer();
	D3DXVECTOR3 playerPos = pPlayer->GetPos();
	float fLife = pPlayer->GetLife();

	// �T�E���h�ƃX���[�擾
	CSound* pSound = CManager::GetCSound();
	CSlow* pSlow = CGame::GetCSlow();

	// �ʒu���擾
	D3DXVECTOR3 pos = CEnemy::GetPos();
	// �����v�Z
	float fDistance = 80.0f;
	float radX = playerPos.x - pos.x;
	float radY = playerPos.y - pos.y;
	float radZ = playerPos.z - pos.z;
	float fRadius = sqrtf((radX * radX) + (radY * radY) + (radZ * radZ));

	// �p���B��t����
	bool bParryTime = m_fAttackFps > 20*pSlow->GetnMulti() && m_fAttackFps <= 40 * pSlow->GetnMulti();	
	// ���d����
	bool bDisChargeTime = m_fAttackFps > 70 * pSlow->GetnMulti() && m_fAttackFps < 180 * pSlow->GetnMulti();
	bool bParry = false;
	if (bParryTime == true)
	{// �p���B��t��
		int nBoost = pPlayer->GetBoostTime();
		if (nBoost > 0)
		{
			bParry = true;
			CSlow::Set(180);
		}
	}
	if (bDisChargeTime==true)
	{// ���d���Ԓ�
		if (fDistance > fRadius && bParry == false)
		{// �͈͓���������
			// �v���C���[�̗̑͂𑝂₷�U��
			fLife+=0.2f;
			pPlayer->SetLife(fLife);
		}
		// ���d���[�V����
		SetMotion(MOTION_ACTION2);

		// �d�C�p�[�e�B�N������
		CParticle::Create(D3DXVECTOR3(CEnemy::GetPos()),// �ʒu
			80,											// ���a
			D3DXVECTOR2(30.0f,30.0f),					// �T�C�Y
			2,											// ��
			10,											// ����
			1,											// ����
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));			// �F
		
		if (m_bAttackSound == false)
		{// �T�E���h���d�h�~
			pSound->Play(CSound::LABEL_SE05);
			m_bAttackSound = true;
		}
	}
	if (m_fAttackFps > 120 * pSlow->GetnMulti())
	{// �U�����Ԃ��I�������
		m_fAttackFps = 0;
		// �T�E���h��~
		pSound->Stop(CSound::LABEL_SE05);
		m_bAttackSound = false;

		return true;
	}
	return false;
}

//*****************
// �R���X�g���N�^
//*****************
CFanmotorEnemy::CFanmotorEnemy()
{
	m_fAttackFps = 0;
	m_bAttackSound = false;
	m_nHitCool = 0;
}

//*****************
// �f�X�g���N�^
//*****************
CFanmotorEnemy::~CFanmotorEnemy()
{

}

//*****************
// ����������
//*****************
HRESULT CFanmotorEnemy::Init(D3DXVECTOR3 pos)
{
	// ���[�V�����ǂݍ���
	CEnemy::LoadMotion("data\\MOTION\\fanmotor.txt");
	CEnemy::Init(pos);
	CEnemy::SetSpeed(SPEED);
	
	return S_OK;
}

//*****************
// �I������
//*****************
void CFanmotorEnemy::Uninit(void)
{
	CEnemy::Uninit();
}

//*****************
// �X�V����
//*****************
void CFanmotorEnemy::Update(void)
{
	CEnemy::Update();
}

//*****************
// �`�揈��
//*****************
void CFanmotorEnemy::Draw(void)
{
	CEnemy::Draw();
}

//*****************
// �ǂ����������
//*****************
bool CFanmotorEnemy::Chase(void)
{
	return CEnemy::Distance(200.0f);
}

//*****************
// �U���������
//*****************
bool CFanmotorEnemy::Attack(void)
{
	// �v���C���[�̈ʒu�擾
	CPlayer* pPlayer = CGame::GetCPlayer();
	D3DXVECTOR3 playerPos = pPlayer->GetPos();

	// ���[�^�[�V���t�g�̃��[���h�}�g���b�N�X�擾
	CModel* pModelShaft = GetModel(10);
	D3DXMATRIX mtxShaft = pModelShaft->GetMtxWorld();

	// �ʒu�擾
	D3DXVECTOR3 pos = CEnemy::GetPos();

	// �v���C���[�Ƃ̋����擾
	float fDistance = 35.0f;
	float radX = playerPos.x - pos.x;
	float radY = playerPos.y - pos.y;
	float radZ = playerPos.z - pos.z;
	float fRadius = sqrtf((radX * radX) + (radY * radY) + (radZ * radZ));

	// �p�[�e�B�N������
	CParticle::Create(D3DXVECTOR3(mtxShaft._41, 
		mtxShaft._42, 
		mtxShaft._43), 
		30, 
		D3DXVECTOR2(20.0f, 20.0f),
		2, 
		2, 
		1, 
		D3DXCOLOR(0.4f, 0.4f, 1.0f, 1.0f));

	if (fDistance > fRadius)
	{// �͈͓�
		m_bAttackSound = false;
		return true;
	}
	return false;
}

//*****************
// �~�܂����
//*****************
bool CFanmotorEnemy::Nuetoral(void)
{
	return !CEnemy::Distance(200.0f);
}

//*****************
// ��������
//*****************
bool CFanmotorEnemy::Hit(void)
{
	// �ʒu�擾
	D3DXVECTOR3 pos = GetPos();
	// �v���C���[�̈ʒu�擾
	CPlayer* pPlayer = CGame::GetCPlayer();
	D3DXVECTOR3 playerPos = pPlayer->GetPos();
	// �J�����ƃT�E���h�擾
	CCamera* pCamera = CManager::GetCCamera();
	CSound* pSound = CManager::GetCSound();

	// �����蔻��v�Z
	float DistX, DistY, DistZ;
	// ���̋���
	DistX = playerPos.x - pos.x;
	DistY = playerPos.y - pos.y;
	DistZ = playerPos.z - pos.z;
	float Dist = sqrtf((DistX * DistX) + (DistY * DistY) + (DistZ * DistZ));

	m_nHitCool++;
	// �q�b�g�̏���
	bool bHit = Dist < Range
		&& pPlayer->GetState() != CPlayer::STATE_RAIL
		&& m_nHitCool>hitCool;
	if (bHit)
	{// �q�b�g������
		pSound->Play(CSound::LABEL_SE05);

		if (pPlayer->GetState() == CPlayer::STATE_NONE)
		{
			pPlayer->SetMove(D3DXVECTOR3(DistX * 0.05f, 0.0f, DistZ * 0.05f));
			// �v���C���[�̏�Ԃ�ύX
			pPlayer->SetState(CPlayer::STATE_INOPERABLE);
			CInoperableState* pInoperableState = new CInoperableState;
			pPlayer->ChangeState(pInoperableState);
		}

		m_nHitCool = 0;
		return true;
	}


	// �{���g�Ƃ̓����蔻��
	for (int nCntPriority = 0; nCntPriority < MAX_PRI; nCntPriority++)
	{
		CObject* pObject = GetTop(nCntPriority);
		while (pObject != NULL)
		{
			CObject* pObjectNext = pObject->GetNext();
			if (pObject->GetType() == CObject::TYPE_BOLT)
			{// �I�u�W�F�N�g�̖��O���{���g��������
				D3DXVECTOR3 posBolt=pObject->GetPos();
				D3DXVECTOR3 pos = CEnemy::GetPos();
				// �������v�Z
				float fDistance = 35.0f;
				float radX = posBolt.x - pos.x;
				float radY = posBolt.y - pos.y;
				float radZ = posBolt.z - pos.z;
				float fRadius = sqrtf((radX * radX) + (radY * radY) + (radZ * radZ));
				if (fDistance > fRadius)
				{// �͈͓���������
					pCamera->SetShake(10);
					return true;
				}

			}
			pObject = pObjectNext;
		}
	}
	return false;
}

//*****************
// �U���̍X�V
//*****************
bool CFanmotorEnemy::AttackUpdate(void)
{
	// �X���[�ƃT�E���h�擾
	CSlow* pSlow = CGame::GetCSlow();
	CSound* pSound = CManager::GetCSound();
	m_fAttackFps++;
	// �r�����̃��[���h�}�g���b�N�X���擾
	CModel* pModelArm = GetModel(4);
	CModel* pModelHand = GetModel(5);
	D3DXMATRIX mtxArm = pModelArm->GetMtxWorld();
	D3DXMATRIX mtxHand = pModelHand->GetMtxWorld();
	// �v���C���[�ʒu�Ƒ̗͎擾
	CPlayer* pPlayer = CGame::GetCPlayer();
	D3DXVECTOR3 playerPos = pPlayer->GetPos();
	float fLife = pPlayer->GetLife();

	// ���[���h�}�g���b�N�X�v�Z
	float mtxX = (mtxHand._41 - mtxArm._41);
	float mtxY = (mtxHand._42 - mtxArm._42);
	float mtxZ = (mtxHand._43 - mtxArm._43);
	// ���d����
	bool bParryTime = 20<m_fAttackFps&& m_fAttackFps < 40 * pSlow->GetnMulti();
	bool bParry = false;
	if (bParryTime == true)
	{// �p���B��t��
		// �v���C���[�̃J�E���^�[�擾
		int nBoost = pPlayer->GetBoostTime();
		if (nBoost > 0)
		{// �p���B����
			bParry = true;
			CSlow::Set(180);
			CBlurManager::Set(180);
		}
	}

	for (int nCnt = 0; nCnt < 4; nCnt++)
	{// �肩��r�̐�[�܂ł�4��������
		D3DXVECTOR3 pos;
		pos.x = mtxArm._41 + mtxX * 0.25f * nCnt;
		pos.y = mtxArm._42 + mtxY * 0.25f * nCnt;
		pos.z = mtxArm._43 + mtxZ * 0.25f * nCnt;
		CParticle::Create(pos, 40, D3DXVECTOR2(10.0f, 10.0f), 2, 4, 1, D3DXCOLOR(0.4f, 0.4f, 1.0f, 1.0f));
	}

	// �ʒu�擾
	D3DXVECTOR3 pos=GetPos();

	// �v���C���[�Ƃ̋����v�Z
	float DistanceX = playerPos.x - pos.x;
	float DistanceY = playerPos.y - pos.y;
	float DistanceZ = playerPos.z - pos.z;
	float fDistance = (DistanceX * DistanceX) + (DistanceY * DistanceY) + (DistanceZ * DistanceZ);

	float fPlayerRad = 30.0f;
	float fEnemyRad = 40.0f;
	// �����蔻��
	float fRad = fEnemyRad + fPlayerRad;
	fRad = fRad * fRad;
	bool bAttack = fDistance < fRad && m_fAttackFps >30&& m_fAttackFps < 45&& bParry == false;

	if (bAttack == true)
	{// �U����������������
		fLife -= 1.0f;
		pPlayer->SetLife(fLife);
	}

	if (m_fAttackFps > 30&&m_bAttackSound==false)
	{// ���d�T�E���h�h�~
		pSound->Play(CSound::LABEL_SE06);
		m_bAttackSound = true;
	}
	if (m_fAttackFps > 120 * pSlow->GetnMulti())
	{// �J�E���g���߂�����
		m_fAttackFps = 0;
		return true;
	}
	return false;
}