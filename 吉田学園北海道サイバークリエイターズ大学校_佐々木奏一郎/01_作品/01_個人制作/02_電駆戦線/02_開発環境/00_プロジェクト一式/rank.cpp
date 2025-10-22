//*****************************************
//
// �����N���� [rank.cpp]
// Author:Sasaki Soichiro
//
//*****************************************

//*******************
// �C���N���[�h
//*******************
#include "rank.h"
#include "renderer.h"
#include "manager.h"
#include "camera.h"
#include "score.h"

//*****************
// �R���X�g���N�^
//*****************
CRank::CRank(int nPriority) :CObjectX(nPriority)
{
	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		m_nIdxXFile[nCnt] = -1;
	}
}

//*****************
// �f�X�g���N�^
//*****************
CRank::~CRank()
{
}

//******************
// �C���X�^���X����
//*******************
CRank* CRank::Create(D3DXVECTOR3 pos)
{
	CRank* pBlock;
	int nNum = CObject::GetNumAll();
	if (nNum < MAX_OBJ - 1)
	{// �I�u�W�F�N�g���ő吔�ɒB���Ă��Ȃ��ꍇ

		pBlock = new CRank;	// �C���X�^���X����
		pBlock->Init(pos);		// ������
		return pBlock;			// ����n��
	}

	// �I�u�W�F�N�g���ő吔�ɒB���Ă����ꍇ
	return NULL;	// NULL��Ԃ�
}

//*****************
// ����������
//*****************
HRESULT CRank::Init(D3DXVECTOR3 pos)
{
	// CXModel�̃|�C���^�ɏ�������
	CXModel* pXModel = CManager::GetCXModel();
	// �g�����f���̃C���f�b�N�X������
	m_nIdxXFile[0] = pXModel->Register("data\\MODEL\\s.x");
	m_nIdxXFile[1] = pXModel->Register("data\\MODEL\\a.x");
	m_nIdxXFile[2] = pXModel->Register("data\\MODEL\\B.x");
	m_nIdxXFile[3] = pXModel->Register("data\\MODEL\\C.x");
	SetRank();
	// ������
	CObjectX::Init(pos);

	// ����������
	return S_OK;
}

//*****************
// �I������
//*****************
void CRank::Uninit(void)
{
	// �I������
	CObjectX::Uninit();
}

//*****************
// �X�V����
//*****************
void CRank::Update(void)
{
	CCamera* pCamera = CManager::GetCCamera();
	D3DXVECTOR3 rot = GetRot();
	rot.y += 0.01f;
	SetRot(rot);
	pCamera->Target(D3DXVECTOR3(0.0f, -30.0f, -30.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
}

//*****************
// �`�揈��
//*****************
void CRank::Draw(void)
{
	CObjectX::Draw();// �`��
}

void CRank::SetRank(void)
{
	// CXModel�̃|�C���^�ɏ�������
	CXModel* pXModel = CManager::GetCXModel();
	if (CScore::GetScore() > 45000)
	{
		// X�t�@�C�������蓖�Ă�
		BindXFile(pXModel->GetAddres(m_nIdxXFile[0]));
	}
	else if (CScore::GetScore() > 20000)
	{
		// X�t�@�C�������蓖�Ă�
		BindXFile(pXModel->GetAddres(m_nIdxXFile[1]));
	}
	else if (CScore::GetScore() > 3000)
	{
		// X�t�@�C�������蓖�Ă�
		BindXFile(pXModel->GetAddres(m_nIdxXFile[2]));
	}
	else
	{
		// X�t�@�C�������蓖�Ă�
		BindXFile(pXModel->GetAddres(m_nIdxXFile[3]));
	}
}

//******************
// �ʒu�̐ݒ�
//******************
void CRank::SetPos(D3DXVECTOR3 pos)
{
	CObjectX::SetPos(pos);// �ʒu�ݒ�
}

//******************
// �����̐ݒ�
//******************
void CRank::SetRot(D3DXVECTOR3 rot)
{
	CObjectX::SetRot(rot);// �����ݒ�
}

//******************
// �ʒu���̎擾
//******************
D3DXVECTOR3 CRank::GetPos(void)
{
	return CObjectX::GetPos();// �ʒu���擾
}
D3DXVECTOR3 CRank::GetRot(void)
{
	return CObjectX::GetRot();// �ʒu���擾
}