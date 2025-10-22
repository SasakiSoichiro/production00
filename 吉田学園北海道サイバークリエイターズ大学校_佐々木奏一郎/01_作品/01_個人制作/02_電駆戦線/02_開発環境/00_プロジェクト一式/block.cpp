//*****************************************
//
// �u���b�N���� [block.cpp]
// Author:Sasaki Soichiro
//
//*****************************************

//*******************
// �C���N���[�h
//*******************
#include "block.h"
#include "renderer.h"
#include "manager.h"
#include "player.h"
#include "game.h"
#include "particle.h"
#include "blockManager.h"
#include "tutorial.h"

//*****************
// �R���X�g���N�^
//*****************
CBlock::CBlock(int nPriority) :CObjectX(nPriority)
{
	m_nIdxXFile = -1;
}

//*****************
// �f�X�g���N�^
//*****************
CBlock::~CBlock()
{
}

//******************
// �C���X�^���X����
//*******************
CBlock* CBlock::Create(D3DXVECTOR3 pos, const char* pFileName,int nType)
{
	CBlock* pBlock;
	CBlockManager* pBlockManager=NULL;

	switch (nType)
	{
	case 0:
		// �Q�[���p
		pBlockManager = CGame::GetCBlockManager();
		break;
	case 1:
		// �`���[�g���A���p
		pBlockManager = CTutorial::GetCBlockManager();
		break;
	}

	int nNum = CObject::GetNumAll();
	if (nNum < MAX_OBJ - 1)
	{// �I�u�W�F�N�g���ő吔�ɒB���Ă��Ȃ��ꍇ

		// �C���X�^���X����
		pBlock = new CBlock;	
		// ���f���̐ݒ�
		pBlock->SetXModel(pFileName);
		// ������
		pBlock->Init(pos);
		// �u���b�N�}�l�[�W���[�̃��X�g�ɐݒ�
		pBlockManager->Set(pBlock);

		return pBlock;
	}

	return NULL;
}

//*****************
// ����������
//*****************
HRESULT CBlock::Init(D3DXVECTOR3 pos)
{
	CObjectX::Init(pos);

	return S_OK;
}

//*****************
// �I������
//*****************
void CBlock::Uninit(void)
{
	CObjectX::Uninit();
}

//*****************
// �X�V����
//*****************
void CBlock::Update(void)
{

}

//*****************
// �`�揈��
//*****************
void CBlock::Draw(void)
{
	CObjectX::Draw();
}

//******************
// �ʒu�̐ݒ�
//******************
void CBlock::SetPos(D3DXVECTOR3 pos)
{
	CObjectX::SetPos(pos);
}

//******************
// �����̐ݒ�
//******************
void CBlock::SetRot(D3DXVECTOR3 rot)
{
	CObjectX::SetRot(rot);
}

//******************
// �g�����f���̐ݒ�
//******************
void CBlock::SetXModel(const char*fileName)
{
	// CXModel�̃|�C���^�ɏ�������
	CXModel* pXModel = CManager::GetCXModel();
	// �g�����f���̃C���f�b�N�X������
	m_nIdxXFile = pXModel->Register(fileName);
	// X�t�@�C�������蓖�Ă�
	BindXFile(pXModel->GetAddres(m_nIdxXFile));
}

//******************
// �ʒu���̎擾
//******************
D3DXVECTOR3 CBlock::GetPos(void)
{
	return CObjectX::GetPos();
}

//******************
// �������擾
//******************
D3DXVECTOR3 CBlock::GetRot(void)
{
	return CObjectX::GetRot();
}

//******************
// ���f�����擾
//******************
CXModel::XMODEL CBlock::GetXModel(void)
{
	return CObjectX::GetXModel();
}