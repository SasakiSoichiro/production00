//*****************************************
//
// �{���g���� [bolt.cpp]
// Author:Sasaki Soichiro
//
//*****************************************

//*******************
// �C���N���[�h
//*******************
#include "bolt.h"
#include "renderer.h"
#include "manager.h"
#include "player.h"
#include "game.h"
#include "particle.h"
#include "attackbolt.h"
#include "sound.h"
#include "mesh.h"

//*****************
// �R���X�g���N�^
//*****************
CBolt::CBolt(int nPriority) :CObjectX(nPriority)
{
	m_nIdxXFile = -1;
	m_nBreak = 0;
	m_nLife = 0;
	m_fAngle = 0.0f;
	m_fAngleSum = 0.0f;
}

//*****************
// �f�X�g���N�^
//*****************
CBolt::~CBolt()
{
}

//******************
// �C���X�^���X����
//*******************
CBolt* CBolt::Create(D3DXVECTOR3 pos)
{
	CBolt* pBlock;
	int nNum = CObject::GetNumAll();

	if (nNum < MAX_OBJ - 1)
	{// �I�u�W�F�N�g���ő吔�ɒB���Ă��Ȃ��ꍇ

		// �C���X�^���X����
		pBlock = new CBolt;	
		// ������
		pBlock->Init(pos);

		return pBlock;			
	}

	return NULL;
}

//*****************
// ����������
//*****************
HRESULT CBolt::Init(D3DXVECTOR3 pos)
{
	// CXModel�̃|�C���^�ɏ�������
	CXModel* pXModel = CManager::GetCXModel();
	// �g�����f���̃C���f�b�N�X������
	m_nIdxXFile = pXModel->Register("data\\MODEL\\bolts.x");
	// X�t�@�C�������蓖�Ă�
	BindXFile(pXModel->GetAddres(m_nIdxXFile));

	// ������
	CObjectX::Init(pos);
	m_nBreak = 0;
	m_nLife = maxLife;

	return S_OK;
}

//*****************
// �I������
//*****************
void CBolt::Uninit(void)
{
	CObjectX::Uninit();
}

//*****************
// �X�V����
//*****************
void CBolt::Update(void)
{
	// �T�E���h�ƃ��b�V�����擾
	CSound* pSound = CManager::GetCSound();
	CMesh* pMesh = CGame::GetCMesh();
	// �ʒu���擾
	D3DXVECTOR3 pos = GetPos();
	// �v���C���[�ƃv���C���[�̈ʒu���擾
	CPlayer* pPlayer = CGame::GetCPlayer();
	D3DXVECTOR3 playerPos = pPlayer->GetPos();
	D3DXVECTOR3 playerOldPos = pPlayer->GetOldPos();

	float DistX, DistY, DistZ;
	// ���݂̃v���C���[�Ƃ̋��������߂�
	DistX = playerPos.x - pos.x;
	DistY = playerPos.y - pos.y;
	DistZ = playerPos.z - pos.z;
	float Dist = sqrtf((DistX * DistX) + (DistY * DistY) + (DistZ * DistZ));

	// �O�t���[���̃v���C���[�Ƃ̋��������߂�
	DistX = playerOldPos.x - pos.x;
	DistY = playerOldPos.y - pos.y;
	DistZ = playerOldPos.z - pos.z;
	float OldDist = sqrtf((DistX * DistX) + (DistY * DistY) + (DistZ * DistZ));
	
	// �v���C���[�Ƃ̓����蔻��
	if (Dist < maxRange && OldDist>= maxRange)
	{
		// ��]�̍��v��������
		m_fAngle = pPlayer->GetAngle();
		m_fAngleSum = 0.0f;
	}

	// �{���g���΂��鏈��
	if (Dist < maxRange && m_nLife>0)
	{
		// �v���C���[����]�������v�����߂�
		float OldAngle = m_fAngle;
		m_fAngle = pPlayer->GetAngle();
		m_fAngleSum += fabs(OldAngle - m_fAngle);


		if (m_fAngleSum > D3DX_PI*2.0f)
		{// 1��]������

			// �{���g��360�x�����ɔ�΂�
			for (int nCnt = 0; nCnt < 18; nCnt++)
			{
				float fAngle = D3DX_PI * 2.0f * nCnt / 18;
				CAttackBolt::Create(playerPos, fAngle);
			}

			// SE�Đ�
			pSound->Play(CSound::LABEL_SE01);

			// ������
			m_nLife = 0;
			m_nBreak = 0;
			m_fAngleSum = 0.0f;
		}
		
	}

	// �x�e���Ԃ��߂����������
	m_nBreak++;
	if (m_nBreak > maxBreakTime)
	{
		m_nLife = maxLife;
	}

	// �n�ʂ̍����ɍ��킹��&�ʒu���f
	pos.y = pMesh->GetHeight(pos);
	SetPos(pos);

}

//*****************
// �`�揈��
//*****************
void CBolt::Draw(void)
{
	CObjectX::Draw();
}

//******************
// �ʒu�̐ݒ�
//******************
void CBolt::SetPos(D3DXVECTOR3 pos)
{
	CObjectX::SetPos(pos);
}

//******************
// �����̐ݒ�
//******************
void CBolt::SetRot(D3DXVECTOR3 rot)
{
	CObjectX::SetRot(rot);
}

//******************
// �ʒu���̎擾
//******************
D3DXVECTOR3 CBolt::GetPos(void)
{
	return CObjectX::GetPos();
}

//******************
// �������̎擾
//******************
D3DXVECTOR3 CBolt::GetRot(void)
{
	return CObjectX::GetRot();
}