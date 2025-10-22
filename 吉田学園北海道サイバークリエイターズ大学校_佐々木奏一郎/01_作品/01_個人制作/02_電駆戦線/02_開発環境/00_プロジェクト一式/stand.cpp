//*****************************************
//
// �X�^���h���� [stand.cpp]
// Author:Sasaki Soichiro
//
//*****************************************

//*******************
// �C���N���[�h
//*******************
#include "stand.h"
#include "renderer.h"
#include "manager.h"
#include "camera.h"

//*****************
// �R���X�g���N�^
//*****************
CStand::CStand(int nPriority) :CObjectX(nPriority)
{
	m_nIdxXFile = -1;
}

//*****************
// �f�X�g���N�^
//*****************
CStand::~CStand()
{
}

//******************
// �C���X�^���X����
//*******************
CStand* CStand::Create(D3DXVECTOR3 pos)
{
	CStand* pBlock;
	int nNum = CObject::GetNumAll();
	if (nNum < MAX_OBJ - 1)
	{// �I�u�W�F�N�g���ő吔�ɒB���Ă��Ȃ��ꍇ

		pBlock = new CStand;	// �C���X�^���X����
		pBlock->Init(pos);		// ������
		return pBlock;			// ����n��
	}

	// �I�u�W�F�N�g���ő吔�ɒB���Ă����ꍇ
	return NULL;	// NULL��Ԃ�
}

//*****************
// ����������
//*****************
HRESULT CStand::Init(D3DXVECTOR3 pos)
{
	// CXModel�̃|�C���^�ɏ�������
	CXModel* pXModel = CManager::GetCXModel();
	// �g�����f���̃C���f�b�N�X������
	m_nIdxXFile = pXModel->Register("data\\MODEL\\stand.x");
	// X�t�@�C�������蓖�Ă�
	BindXFile(pXModel->GetAddres(m_nIdxXFile));

	// ������
	CObjectX::Init(pos);

	// ����������
	return S_OK;
}

//*****************
// �I������
//*****************
void CStand::Uninit(void)
{
	// �I������
	CObjectX::Uninit();
}

//*****************
// �X�V����
//*****************
void CStand::Update(void)
{
}

//*****************
// �`�揈��
//*****************
void CStand::Draw(void)
{
	CObjectX::Draw();// �`��
}

//******************
// �ʒu�̐ݒ�
//******************
void CStand::SetPos(D3DXVECTOR3 pos)
{
	CObjectX::SetPos(pos);// �ʒu�ݒ�
}

//******************
// �����̐ݒ�
//******************
void CStand::SetRot(D3DXVECTOR3 rot)
{
	CObjectX::SetRot(rot);// �����ݒ�
}

//******************
// �ʒu���̎擾
//******************
D3DXVECTOR3 CStand::GetPos(void)
{
	return CObjectX::GetPos();// �ʒu���擾
}
D3DXVECTOR3 CStand::GetRot(void)
{
	return CObjectX::GetRot();// �ʒu���擾
}