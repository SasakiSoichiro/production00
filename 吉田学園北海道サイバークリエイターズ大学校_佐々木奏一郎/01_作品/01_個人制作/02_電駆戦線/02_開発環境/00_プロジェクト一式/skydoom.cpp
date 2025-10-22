//*****************************************
//
// ��̏��� [skydoom.cpp]
// Author:Sasaki Soichiro
//
//*****************************************

//*******************
// �C���N���[�h
//*******************
#include "skydoom.h"
#include "renderer.h"
#include "manager.h"
#include "camera.h"

//******************
// �}�N����`
//******************
#define SPEED (0.0015f)

//*****************
// �R���X�g���N�^
//*****************
CSkyDoom::CSkyDoom(int nPriority) :CObjectX(nPriority)
{
	m_nIdxXFile = -1;
}

//*****************
// �f�X�g���N�^
//*****************
CSkyDoom::~CSkyDoom()
{
}

//******************
// �C���X�^���X����
//*******************
CSkyDoom* CSkyDoom::Create(D3DXVECTOR3 pos)
{
	CSkyDoom* pBlock;
	int nNum = CObject::GetNumAll();
	if (nNum < MAX_OBJ - 1)
	{// �I�u�W�F�N�g���ő吔�ɒB���Ă��Ȃ��ꍇ

		pBlock = new CSkyDoom;	// �C���X�^���X����
		pBlock->Init(pos);		// ������
		return pBlock;			// ����n��
	}

	// �I�u�W�F�N�g���ő吔�ɒB���Ă����ꍇ
	return NULL;	// NULL��Ԃ�
}

//*****************
// ����������
//*****************
HRESULT CSkyDoom::Init(D3DXVECTOR3 pos)
{
	// CXModel�̃|�C���^�ɏ�������
	CXModel* pXModel = CManager::GetCXModel();
	// �g�����f���̃C���f�b�N�X������
	m_nIdxXFile = pXModel->Register("data\\MODEL\\skydoom.x");
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
void CSkyDoom::Uninit(void)
{
	// �I������
	CObjectX::Uninit();
}

//*****************
// �X�V����
//*****************
void CSkyDoom::Update(void)
{
	D3DXVECTOR3 rot = GetRot();

	rot.y += SPEED;

	SetRot(rot);
}

//*****************
// �`�揈��
//*****************
void CSkyDoom::Draw(void)
{
	CObjectX::Draw();// �`��
}

//******************
// �ʒu�̐ݒ�
//******************
void CSkyDoom::SetPos(D3DXVECTOR3 pos)
{
	CObjectX::SetPos(pos);// �ʒu�ݒ�
}

//******************
// �����̐ݒ�
//******************
void CSkyDoom::SetRot(D3DXVECTOR3 rot)
{
	CObjectX::SetRot(rot);// �����ݒ�
}

//******************
// �ʒu���̎擾
//******************
D3DXVECTOR3 CSkyDoom::GetPos(void)
{
	return CObjectX::GetPos();// �ʒu���擾
}
D3DXVECTOR3 CSkyDoom::GetRot(void)
{
	return CObjectX::GetRot();// �ʒu���擾
}