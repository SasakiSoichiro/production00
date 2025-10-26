//***************************************
//
// �u���b�N�Ǘ����� [blockManager.cpp]
// Author:Sasaki Soichiro
//
//***************************************

//*******************
// �C���N���[�h
//*******************
#include "blockManager.h"

//*******************
// �R���X�g���N�^
//*******************
CBlockManager::CBlockManager()
{
}

//*******************
// �f�X�g���N�^
//*******************
CBlockManager::~CBlockManager()
{
}

//*************
// ����������
//*************
HRESULT CBlockManager::Init(void)
{

	return S_OK;
}

//*************
// �I������
//*************
void CBlockManager::Uninit(void)
{
}

//*************
// �X�V����
//*************
void CBlockManager::Update(void)
{
}

//**************
// �o�^
//**************
void CBlockManager::Set(CBlock*block)
{
	m_Block.push_back(block);
}

//**********************
// �ʒu��Ԃ������蔻��
//**********************
D3DXVECTOR3 CBlockManager::Collision(D3DXVECTOR3 pos, D3DXVECTOR3 posOld)
{
	for (const auto& block : m_Block)
	{
		// �u���b�N�̈ʒu�ƃ��f�������擾
		D3DXVECTOR3 blockPos = block->GetPos();
		CXModel::XMODEL XModel = block->GetXModel();

		//���E��O���̂߂荞�ݔ���
		if (pos.y< blockPos.y + XModel.vtxMax.y && pos.y + (25.0f * 2.0f) > blockPos.y + XModel.vtxMin.y)
		{
			//���E�̂߂荞�ݔ���
			if (pos.z - 25.0f< blockPos.z + XModel.vtxMax.z && pos.z + 25.0f > blockPos.z + XModel.vtxMin.z)//�v���C���[�̂��͈̔͂��u���b�N�ɏd�Ȃ��Ă���
			{

				if (posOld.x + 25.0f< blockPos.x + XModel.vtxMin.x && pos.x + 25.0f > blockPos.x + XModel.vtxMin.x)//�w��������E�ɂ߂荞��
				{
					//pPlayer->pos�����f���̍����ɂ�������
					pos.x = blockPos.x + XModel.vtxMin.x - 25.0f - 0.1f;
				}
				if (posOld.x - 25.0f > blockPos.x + XModel.vtxMax.x && pos.x - 25.0f < blockPos.x + XModel.vtxMax.x)//�w��������E�ɂ߂荞��
				{
					//pPlayer->pos�����f���̉E���ɂ�������
					pos.x = blockPos.x + XModel.vtxMax.x + 25.0f + 0.1f;
				}
			}

			//��O���̂߂荞�ݔ���
			if (pos.x - 25.0f< blockPos.x + XModel.vtxMax.x && pos.x + 25.0f > blockPos.x + XModel.vtxMin.x)//�v���C���[x�͈̔͂��u���b�N�ɏd�Ȃ��Ă���
			{

				if (posOld.z + 25.0f< blockPos.z + XModel.vtxMin.z && pos.z + 25.0f > blockPos.z + XModel.vtxMin.z)//Z���������ɂ߂荞��
				{
					//pPlayer->pos�����f���̎�O���ɂ�������
					pos.z = blockPos.z + XModel.vtxMin.z - 25.0f - 0.1f;
					//return pos;
					
				}
				if (posOld.z - 25.0f > blockPos.z + XModel.vtxMax.z && pos.z - 25.0f < blockPos.z + XModel.vtxMax.z)//Z���ォ�牺�ɂ߂荞��
				{
					//pPlayer->pos�����f���̉����ɂ�������
					pos.z = blockPos.z + XModel.vtxMax.z + 25.0f + 0.1f;
					
				}
			}

		}
		if (pos.z - 25.0f< blockPos.z + XModel.vtxMax.z && pos.z + 25.0f > blockPos.z + XModel.vtxMin.z
			&& pos.x - 25.0f< blockPos.x + XModel.vtxMax.x && pos.x + 25.0f > blockPos.x + XModel.vtxMin.x)
		{
			if (posOld.y + (25.0f * 2.0f) < blockPos.y + XModel.vtxMin.y && pos.y + (25.0f * 2.0f) > blockPos.y + XModel.vtxMin.y)//�w��������E�ɂ߂荞��
			{
				//pPlayer->pos�����f���̉����ɂ�������
				pos.y = blockPos.y + XModel.vtxMin.y - (25.0f * 2.0f) - 0.1f;
				
			}
			if (posOld.y > blockPos.y + XModel.vtxMax.y && pos.y < blockPos.y + XModel.vtxMax.y)//�w��������E�ɂ߂荞��
			{
				//pPlayer->pos�����f���̏㑤�ɂ�������
				pos.y = blockPos.y + XModel.vtxMax.y + 0.1f;
				
			}

		}
		
	}

	return pos;
}

//**********************
// bool�^�̂����蔻��
//**********************
bool CBlockManager::bCollision(D3DXVECTOR3 pos)
{
	for (const auto& block : m_Block)
	{
		D3DXVECTOR3 blockPos = block->GetPos();
		CXModel::XMODEL XModel = block->GetXModel();
		//���E��O���̂߂荞�ݔ���
		if (pos.y< blockPos.y + XModel.vtxMax.y && pos.y + (25.0f * 2.0f) > blockPos.y + XModel.vtxMin.y)
		{
			//���E�̂߂荞�ݔ���
			if (pos.z - 25.0f < blockPos.z + XModel.vtxMax.z && pos.z + 25.0f > blockPos.z + XModel.vtxMin.z)//�v���C���[�̂��͈̔͂��u���b�N�ɏd�Ȃ��Ă���
			{

				if (pos.x + 25.0f > blockPos.x + XModel.vtxMin.x)//�w��������E�ɂ߂荞��
				{
					//pPlayer->pos�����f���̍����ɂ�������
					pos.x = blockPos.x + XModel.vtxMin.x - 25.0f - 0.1f;
					return true;
				}
				if (pos.x - 25.0f < blockPos.x + XModel.vtxMax.x)//�w��������E�ɂ߂荞��
				{
					//pPlayer->pos�����f���̉E���ɂ�������
					pos.x = blockPos.x + XModel.vtxMax.x + 25.0f + 0.1f;
					return true;
				}
			}

			//��O���̂߂荞�ݔ���
			if (pos.x - 25.0f < blockPos.x + XModel.vtxMax.x && pos.x + 25.0f > blockPos.x + XModel.vtxMin.x)//�v���C���[x�͈̔͂��u���b�N�ɏd�Ȃ��Ă���
			{

				if ( pos.z + 25.0f > blockPos.z + XModel.vtxMin.z)//Z���������ɂ߂荞��
				{
					//pPlayer->pos�����f���̎�O���ɂ�������
					pos.z = blockPos.z + XModel.vtxMin.z - 25.0f - 0.1f;
					return true;

				}
				if ( pos.z - 25.0f < blockPos.z + XModel.vtxMax.z)//Z���ォ�牺�ɂ߂荞��
				{
					//pPlayer->pos�����f���̉����ɂ�������
					pos.z = blockPos.z + XModel.vtxMax.z + 25.0f + 0.1f;
					return true;

				}
			}

		}
		if (pos.z - 25.0f < blockPos.z + XModel.vtxMax.z && pos.z + 25.0f > blockPos.z + XModel.vtxMin.z
			&& pos.x - 25.0f < blockPos.x + XModel.vtxMax.x && pos.x + 25.0f > blockPos.x + XModel.vtxMin.x)
		{
			if ( pos.y + (25.0f * 2.0f) > blockPos.y + XModel.vtxMin.y)//�w��������E�ɂ߂荞��
			{
				//pPlayer->pos�����f���̉����ɂ�������
				pos.y = blockPos.y + XModel.vtxMin.y - (25.0f * 2.0f) - 0.1f;
				return true;

			}
			if ( pos.y < blockPos.y + XModel.vtxMax.y)//�w��������E�ɂ߂荞��
			{
				//pPlayer->pos�����f���̏㑤�ɂ�������
				pos.y = blockPos.y + XModel.vtxMax.y + 0.1f;
				return true;

			}

		}

	}
	return false;
}