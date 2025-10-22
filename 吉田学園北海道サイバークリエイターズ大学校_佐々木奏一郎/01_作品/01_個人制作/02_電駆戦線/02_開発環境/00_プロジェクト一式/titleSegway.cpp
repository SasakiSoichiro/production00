//*****************************************
//
// �^�C�g���̃Z�O�E�F�C���� [titleSegway.cpp]
// Author:Sasaki Soichiro
//
//*****************************************

//*******************
// �C���N���[�h
//*******************
#include "titleSegway.h"
#include "renderer.h"
#include "manager.h"
#include "camera.h"

//*****************
// �R���X�g���N�^
//*****************
CTitleSegway::CTitleSegway(int nPriority) :CObjectX(nPriority)
{
	m_nIdxXFile = -1;
}

//*****************
// �f�X�g���N�^
//*****************
CTitleSegway::~CTitleSegway()
{
}

//******************
// �C���X�^���X����
//*******************
CTitleSegway* CTitleSegway::Create(D3DXVECTOR3 pos)
{
	CTitleSegway* pBlock;
	int nNum = CObject::GetNumAll();
	if (nNum < MAX_OBJ - 1)
	{// �I�u�W�F�N�g���ő吔�ɒB���Ă��Ȃ��ꍇ

		pBlock = new CTitleSegway;	// �C���X�^���X����
		pBlock->Init(pos);		// ������
		return pBlock;			// ����n��
	}

	// �I�u�W�F�N�g���ő吔�ɒB���Ă����ꍇ
	return NULL;	// NULL��Ԃ�
}

//*****************
// ����������
//*****************
HRESULT CTitleSegway::Init(D3DXVECTOR3 pos)
{
	// CXModel�̃|�C���^�ɏ�������
	CXModel* pXModel = CManager::GetCXModel();
	// �g�����f���̃C���f�b�N�X������
	m_nIdxXFile = pXModel->Register("data\\MODEL\\segwayTitle.x");
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
void CTitleSegway::Uninit(void)
{
	// �I������
	CObjectX::Uninit();
}

//*****************
// �X�V����
//*****************
void CTitleSegway::Update(void)
{
	CCamera* pCamera = CManager::GetCCamera();
	D3DXVECTOR3 rot = GetRot();
	rot.y += 0.01f;
	SetRot(rot);
	pCamera->Target(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
}

//*****************
// �`�揈��
//*****************
void CTitleSegway::Draw(void)
{
	CObjectX::Draw();// �`��
}

//******************
// �ʒu�̐ݒ�
//******************
void CTitleSegway::SetPos(D3DXVECTOR3 pos)
{
	CObjectX::SetPos(pos);// �ʒu�ݒ�
}

//******************
// �����̐ݒ�
//******************
void CTitleSegway::SetRot(D3DXVECTOR3 rot)
{
	CObjectX::SetRot(rot);// �����ݒ�
}

//******************
// �ʒu���̎擾
//******************
D3DXVECTOR3 CTitleSegway::GetPos(void)
{
	return CObjectX::GetPos();// �ʒu���擾
}
D3DXVECTOR3 CTitleSegway::GetRot(void)
{
	return CObjectX::GetRot();// �ʒu���擾
}