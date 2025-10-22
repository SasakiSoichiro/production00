//*****************************************
//
// ��Ώ��� [jem.cpp]
// Author:Sasaki Soichiro
//
//*****************************************

//*******************
// �C���N���[�h
//*******************
#include "jem.h"
#include "renderer.h"
#include "manager.h"
#include "player.h"
#include "game.h"
#include "particle.h"
#include "attackbolt.h"
#include "sound.h"
#include "mesh.h"
#include "combo.h"
#include "score.h"
#include "pieceparticle.h"

//****************
// �}�N����`
//****************
#define RANGE (50.0f)

//*****************
// �R���X�g���N�^
//*****************
CJem::CJem(int nPriority) :CObjectX(nPriority)
{
	for (int nCnt = 0; nCnt < 3; nCnt++)
	{
		m_nIdxXFile[nCnt] = -1;
	}
	m_nLife = 0;
	m_nShake = 0;
	m_OffsetPos = NONE;
}

//*****************
// �f�X�g���N�^
//*****************
CJem::~CJem()
{
}

//******************
// �C���X�^���X����
//*******************
CJem* CJem::Create(D3DXVECTOR3 pos)
{
	CJem* pBlock;
	int nNum = CObject::GetNumAll();
	if (nNum < MAX_OBJ - 1)
	{// �I�u�W�F�N�g���ő吔�ɒB���Ă��Ȃ��ꍇ

		pBlock = new CJem;	// �C���X�^���X����
		pBlock->Init(pos);		// ������
		return pBlock;			// ����n��
	}

	// �I�u�W�F�N�g���ő吔�ɒB���Ă����ꍇ
	return NULL;	// NULL��Ԃ�
}

//*****************
// ����������
//*****************
HRESULT CJem::Init(D3DXVECTOR3 pos)
{
	// CXModel�̃|�C���^�ɏ�������
	CXModel* pXModel = CManager::GetCXModel();
	// �g�����f���̃C���f�b�N�X������
	m_nIdxXFile[0] = pXModel->Register("data\\MODEL\\jembreak01.x");
	m_nIdxXFile[1] = pXModel->Register("data\\MODEL\\jembreak00.x");
	m_nIdxXFile[2] = pXModel->Register("data\\MODEL\\jem.x");

	// X�t�@�C�������蓖�Ă�
	BindXFile(pXModel->GetAddres(m_nIdxXFile[2]));

	// ������
	CObjectX::Init(pos);
	m_nLife = 3;
	m_OffsetPos = pos;

	// ����������
	return S_OK;
}

//*****************
// �I������
//*****************
void CJem::Uninit(void)
{
	CObjectX::Uninit();
}

//*****************
// �X�V����
//*****************
void CJem::Update(void)
{
	// �ʒu�擾
	D3DXVECTOR3 pos = GetPos();
	// �v���C���[�̈ʒu�ƑO�t���[���̈ʒu�擾
	CPlayer* pPlayer = CGame::GetCPlayer();
	D3DXVECTOR3 playerPos = pPlayer->GetPos();
	D3DXVECTOR3 playerOldPos = pPlayer->GetOldPos();
	// ���f���ƃT�E���h�擾
	CXModel* pXModel = CManager::GetCXModel();
	CSound* pSound = CManager::GetCSound();

	// ���݂̋����v�Z
	float DistX, DistY, DistZ;
	DistX = playerPos.x - pos.x;
	DistY = playerPos.y - pos.y;
	DistZ = playerPos.z - pos.z;
	float Dist = sqrtf((DistX * DistX) + (DistY * DistY) + (DistZ * DistZ));

	// �O�t���[���̋����v�Z
	DistX = playerOldPos.x - pos.x;
	DistY = playerOldPos.y - pos.y;
	DistZ = playerOldPos.z - pos.z;
	float OldDist = sqrtf((DistX * DistX) + (DistY * DistY) + (DistZ * DistZ));

	// �R���{�擾
	int nCombo = CCombo::GetCombo();

	if (Dist < RANGE)
	{
		m_nLife--;
		// X�t�@�C�������蓖�Ă�
		BindXFile(pXModel->GetAddres(m_nIdxXFile[m_nLife-1]));
		// �T�E���h�Đ�
		pSound->Play(CSound::LABEL_SE09);
		m_nShake = 20;
		if (m_nLife <= 0|| nCombo>=5)
		{
			CScore::Add(300);
			int nAngle = (int)(atan2f(DistX, DistY)) * 100;
			nAngle -= 314;
			CPieceParticle::Create(pos, nAngle);
			Uninit();
		}
		else
		{
			pPlayer->SetState(CPlayer::STATE_NONE);
			pPlayer->SetPos(D3DXVECTOR3(playerPos.x + (DistX * 1.2f), playerPos.y + (DistY * 1.2f), playerPos.z + (DistZ * 1.2f)));
			CRandState* pRandState = new CRandState;
			pPlayer->ChangeState(pRandState);
		}
	}
	if (m_nShake > 0)
	{
		Shake();
		m_nShake--;
	}
	else
	{
		SetPos(m_OffsetPos);
	}
}

//*****************
// �`�揈��
//*****************
void CJem::Draw(void)
{
	CObjectX::Draw();// �`��
}

//******************
// �ʒu�̐ݒ�
//******************
void CJem::SetPos(D3DXVECTOR3 pos)
{
	CObjectX::SetPos(pos);// �ʒu�ݒ�
}

//******************
// �����̐ݒ�
//******************
void CJem::SetRot(D3DXVECTOR3 rot)
{
	CObjectX::SetRot(rot);// �����ݒ�
}

//******************
// �ʒu���̎擾
//******************
D3DXVECTOR3 CJem::GetPos(void)
{
	return CObjectX::GetPos();// �ʒu���擾
}
D3DXVECTOR3 CJem::GetRot(void)
{
	return CObjectX::GetRot();// �ʒu���擾
}

void CJem::Shake(void)
{
	D3DXVECTOR3 pos = GetPos();
	pos.x += sinf((float)m_nShake)*1.4f;
	pos.y += sinf((float)m_nShake)*1.4f;
	pos.z += sinf((float)m_nShake)*1.4f;

	SetPos(pos);
}