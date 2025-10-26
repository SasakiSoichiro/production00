//*****************************************
//
// �{���g���� [bolt.cpp]
// Author:Sasaki Soichiro
//
//*****************************************

//*******************
// �C���N���[�h
//*******************
#include "meshEdit.h"
#include "manager.h"
#include "mesh.h"
#include "game.h"
#include "input.h"

//*****************
// �R���X�g���N�^
//*****************
CMeshEdit::CMeshEdit(int nPriority) :CObjectX(nPriority)
{
	m_nIdxXFile = -1;
}

//*****************
// �f�X�g���N�^
//*****************
CMeshEdit::~CMeshEdit()
{
}

//******************
// �C���X�^���X����
//*******************
CMeshEdit* CMeshEdit::Create(D3DXVECTOR3 pos)
{
	CMeshEdit* pBlock;
	int nNum = CObject::GetNumAll();

	if (nNum < MAX_OBJ - 1)
	{// �I�u�W�F�N�g���ő吔�ɒB���Ă��Ȃ��ꍇ

		// �C���X�^���X����
		pBlock = new CMeshEdit;
		// ������
		pBlock->Init(pos);

		return pBlock;
	}

	return NULL;
}

//*****************
// ����������
//*****************
HRESULT CMeshEdit::Init(D3DXVECTOR3 pos)
{
	// CXModel�̃|�C���^�ɏ�������
	CXModel* pXModel = CManager::GetCXModel();
	// �g�����f���̃C���f�b�N�X������
	m_nIdxXFile = pXModel->Register("data\\MODEL\\tire.x");
	// X�t�@�C�������蓖�Ă�
	BindXFile(pXModel->GetAddres(m_nIdxXFile));

	// ������
	CObjectX::Init(pos);

	return S_OK;
}

//*****************
// �I������
//*****************
void CMeshEdit::Uninit(void)
{
	CObjectX::Uninit();
}

//*****************
// �X�V����
//*****************
void CMeshEdit::Update(void)
{
	// �ʒu�擾
	D3DXVECTOR3 pos = GetPos();
	// ���b�V���擾
	CMesh* pMesh = CGame::GetCMesh();
	// ���͎擾
	CInputKeyboard* pKeyboard = CManager::GetCInputKeyboard();

	if (pKeyboard->GetPress(DIK_0))
	{
		pMesh->MoveY(D3DXVECTOR3(pos));
	}

	if (pKeyboard->GetPress(DIK_UP))
	{
		pos.x += fSpeed;
	}
	if (pKeyboard->GetPress(DIK_DOWN))
	{
		pos.x -= fSpeed;
	}
	if (pKeyboard->GetPress(DIK_RIGHT))
	{
		pos.z += fSpeed;
	}
	if (pKeyboard->GetPress(DIK_LEFT))
	{
		pos.z -= fSpeed;
	}

	// ���f
	SetPos(pos);
}

//*****************
// �`�揈��
//*****************
void CMeshEdit::Draw(void)
{
	CObjectX::Draw();
}

//******************
// �ʒu�̐ݒ�
//******************
void CMeshEdit::SetPos(D3DXVECTOR3 pos)
{
	CObjectX::SetPos(pos);
}

//******************
// �����̐ݒ�
//******************
void CMeshEdit::SetRot(D3DXVECTOR3 rot)
{
	CObjectX::SetRot(rot);
}

//******************
// �ʒu���̎擾
//******************
D3DXVECTOR3 CMeshEdit::GetPos(void)
{
	return CObjectX::GetPos();
}

//******************
// �������̎擾
//******************
D3DXVECTOR3 CMeshEdit::GetRot(void)
{
	return CObjectX::GetRot();
}