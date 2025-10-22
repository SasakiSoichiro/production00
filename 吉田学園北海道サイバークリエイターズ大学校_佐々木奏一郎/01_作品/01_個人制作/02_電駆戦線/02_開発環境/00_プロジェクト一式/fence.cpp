//*****************************************
//
// �d�C�򏈗� [fence.cpp]
// Author:Sasaki Soichiro
//
//*****************************************

//*******************
// �C���N���[�h
//*******************
#include "fence.h"
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

//******************
// �}�N����`
//******************
#define DISTANCE (150.0f)	// �x���̋���
#define RADIUS (90.0f)		// �U���̔��a

//*****************
// �R���X�g���N�^
//*****************
CFence::CFence(int nPriority) :CObjectX(nPriority)
{
	for (int nCnt = 0; nCnt < 3; nCnt++)
	{
		m_nIdxXFile[nCnt] = -1;
	}
	m_nBreak = 0;
	m_nBreakAttack = 0;
	m_nLife = 0;
}

//*****************
// �f�X�g���N�^
//*****************
CFence::~CFence()
{
}

//******************
// �C���X�^���X����
//*******************
CFence* CFence::Create(D3DXVECTOR3 pos)
{
	CFence* pBlock;
	int nNum = CObject::GetNumAll();
	if (nNum < MAX_OBJ - 1)
	{// �I�u�W�F�N�g���ő吔�ɒB���Ă��Ȃ��ꍇ

		// �C���X�^���X����
		pBlock = new CFence;
		// ������
		pBlock->Init(pos);	

		return pBlock;			
	}

	return NULL;	
}

//*****************
// ����������
//*****************
HRESULT CFence::Init(D3DXVECTOR3 pos)
{
	// CXModel�̃|�C���^�ɏ�������
	CXModel* pXModel = CManager::GetCXModel();
	// �g�����f���̃C���f�b�N�X������
	m_nIdxXFile[0] = pXModel->Register("data\\MODEL\\fencebreak01.x");
	m_nIdxXFile[1] = pXModel->Register("data\\MODEL\\fencebreak00.x");
	m_nIdxXFile[2] = pXModel->Register("data\\MODEL\\fence.x");
	// X�t�@�C�������蓖�Ă�
	BindXFile(pXModel->GetAddres(m_nIdxXFile[2]));

	CObjectX::Init(pos);
	m_nLife = 3;

	return S_OK;
}

//*****************
// �I������
//*****************
void CFence::Uninit(void)
{
	CObjectX::Uninit();
}

//*****************
// �X�V����
//*****************
void CFence::Update(void)
{
	// �ʒu�ƌ����擾
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();
	// �v���C���[�̈ʒu�ƑO�t���[���̈ʒu�擾
	CPlayer* pPlayer = CGame::GetCPlayer();
	D3DXVECTOR3 playerPos = pPlayer->GetPos();
	D3DXVECTOR3 playerOldPos = pPlayer->GetOldPos();
	// �T�E���h�ƃ��b�V����Xmodel�擾
	CSound* pSound = CManager::GetCSound();
	CMesh* pMesh = CGame::GetCMesh();
	CXModel* pXModel = CManager::GetCXModel();
	// �R���{���擾
	int nCombo = CCombo::GetCombo();

	D3DXVECTOR3 postPos[2] = {};

	// �ʒu�����b�V���̍����ɍ��킹��
	pos.y = pMesh->GetHeight(pos);
	postPos[0].y = pos.y;
	postPos[1].y = pos.y;

	// �v���C���[�̗͎̑擾
	float fLife = pPlayer->GetLife();

	// ��̗��[�̈ʒu�ݒ�
	postPos[0].x = pos.x + sinf(rot.y) * DISTANCE;
	postPos[0].z = pos.z + cosf(rot.y) * DISTANCE;
	postPos[1].x = pos.x + sinf(rot.y + D3DX_PI) * DISTANCE;
	postPos[1].z = pos.z + cosf(rot.y + D3DX_PI) * DISTANCE;

	// �v���C���[�Ƃ̋����v�Z
	float fDistance = RADIUS;
	float radXF = playerPos.x - postPos[0].x;
	float radYF = playerPos.y - postPos[0].y;
	float radZF = playerPos.z - postPos[0].z;
	float radXS = playerPos.x - postPos[1].x;
	float radYS = playerPos.y - postPos[1].y;
	float radZS = playerPos.z - postPos[1].z;
	float fRadiusF = sqrtf((radXF * radXF)+(radYF * radYF)+ (radZF * radZF));
	float fRadiusS = sqrtf((radXS * radXS)+(radYS * radYS)+ (radZS * radZS));


	if (fDistance > fRadiusF && m_nBreak<0 || fDistance > fRadiusS && m_nBreak < 0)
	{// �v���C���[���͈͂ɓ�������
		// �̗͂𑝂₷
		fLife += 10.0f;
		// ���f
		pPlayer->SetLife(fLife);
		// �T�E���h�Đ�
		pSound->Play(CSound::LABEL_SE10);
		// �N�[���^�C���ݒ�
		m_nBreak = 180;
	}

	// �J�E���g�����炷
	m_nBreak--;
	m_nBreakAttack--;

	for (int nCnt = 0; nCnt < 2; nCnt++)
	{// �d�C�p�[�e�B�N���𐶐�
		CParticle::Create(postPos[nCnt], 90, D3DXVECTOR2(30.0f, 30.0f), 2, 10, 1, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
	}
	// ���f
	SetPos(pos);

	// �t�F���X�̊ԂƂ̓����蔻��
	bool collision = Collision(playerPos, postPos[0], postPos[1]);

	if(collision==true)
	{// ����������
		m_nLife--;
		// �T�E���h��炷
		pSound->Play(CSound::LABEL_SE11);
		// X�t�@�C�������蓖�Ă�
		BindXFile(pXModel->GetAddres(m_nIdxXFile[m_nLife-1]));
	}
	// �U��
	Shake();

	if (m_nLife <= 0|| nCombo>4)
	{// ����
		// �X�R�A���Z
		CScore::Add(1000);

		Uninit();
	}
}

//*****************
// �`�揈��
//*****************
void CFence::Draw(void)
{
	CObjectX::Draw();
}

//******************
// �ʒu�̐ݒ�
//******************
void CFence::SetPos(D3DXVECTOR3 pos)
{
	CObjectX::SetPos(pos);
}

//******************
// �����̐ݒ�
//******************
void CFence::SetRot(D3DXVECTOR3 rot)
{
	CObjectX::SetRot(rot);
}

//******************
// �ʒu���̎擾
//******************
D3DXVECTOR3 CFence::GetPos(void)
{
	return CObjectX::GetPos();
}

//******************
// �������̎擾
//******************
D3DXVECTOR3 CFence::GetRot(void)
{
	return CObjectX::GetRot();
}

//**************************
// �v���C���[�Ƃ̓����蔻��
//**************************
bool CFence::Collision(D3DXVECTOR3 playerPos, D3DXVECTOR3 postPos0, D3DXVECTOR3 postPos1)
{
	float fTime = 0.0f;
	float threshold = 15.0f;

	// �t�F���X�̊Ԃ�10����
	for (int nCnt = 0; nCnt < 10; nCnt++)
	{
		// �v���C���[�Ƃ̋����v�Z
		D3DXVECTOR3 Rpos;
		Rpos.x = postPos1.x + (postPos0.x - postPos1.x) * fTime;
		Rpos.y = postPos1.y + (postPos0.y - postPos1.y) * fTime;
		Rpos.z = postPos1.z + (postPos0.z - postPos1.z) * fTime;
		D3DXVECTOR3 Dist = Rpos - playerPos;

		float fDistance = D3DXVec3Length(&Dist);
		if (fDistance < threshold&&m_nBreakAttack<0)
		{// �͈͓���������
			// �N�[���^�C���ݒ�
			m_nBreakAttack = 30;
			return true;
		}
		fTime += 0.1f;
	}
	return false;
}

//****************
// �k�킹�鏈��
//****************
void CFence::Shake(void)
{
	// �ʒu�擾
	D3DXVECTOR3 pos = GetPos();
	if (m_nBreakAttack > 0)
	{// �N�[���^�C����
		// �U�����鏈��
		pos.x += sinf((float)m_nBreakAttack);
		pos.y += sinf((float)m_nBreakAttack);
		pos.z += sinf((float)m_nBreakAttack);
	}
	// ���f
	SetPos(pos);
}