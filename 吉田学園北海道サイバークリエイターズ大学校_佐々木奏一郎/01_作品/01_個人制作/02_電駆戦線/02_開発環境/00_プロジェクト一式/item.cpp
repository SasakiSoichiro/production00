//*****************************************
//
// �A�C�e������ [item.cpp]
// Author:Sasaki Soichiro
//
//*****************************************

//*******************
// �C���N���[�h
//*******************
#include "item.h"
#include "renderer.h"
#include "manager.h"
#include "player.h"
#include "game.h"
#include "itemskill.h"
#include "itemmanager.h"

//*****************
// �R���X�g���N�^
//*****************
CItem::CItem(int nPriority) :CObjectX(nPriority)
{
	m_nIdxXFile = -1;
}

//*****************
// �f�X�g���N�^
//*****************
CItem::~CItem()
{
}

//******************
// �C���X�^���X����
//*******************
CItem* CItem::Create(D3DXVECTOR3 pos,int nType)
{
	// ���g�̃|�C���^�擾
	CItem* pItem;
	// XModel�̎擾
	CXModel* pXModel = CManager::GetCXModel();

	int nNum = CObject::GetNumAll();
	if (nNum < MAX_OBJ - 1)
	{// �I�u�W�F�N�g���ő吔�ɒB���Ă��Ȃ��ꍇ
		// �C���X�^���X����
		pItem = new CItem;	
		// �g�����f���̃C���f�b�N�X������
		pItem->m_nIdxXFile = pXModel->Register("data\\MODEL\\adjust.x");
		pItem->Init(pos);

		return pItem;			
	}

	return NULL;
}

//*****************
// ����������
//*****************
HRESULT CItem::Init(D3DXVECTOR3 pos)
{
	// CXModel�̃|�C���^�ɏ�������
	CXModel* pXModel = CManager::GetCXModel();

	// X�t�@�C�������蓖�Ă�
	BindXFile(pXModel->GetAddres(m_nIdxXFile));

	// ������
	CObjectX::Init(pos);

	return S_OK;
}

//*****************
// �I������
//*****************
void CItem::Uninit(void)
{
	CObjectX::Uninit();
}

//*****************
// �X�V����
//*****************
void CItem::Update(void)
{
	// �v���C���[�̃A�C�e�����擾	
	CPlayer* pPlayer = CGame::GetCPlayer();
	CItemManager* pItemManager=pPlayer->GetItemManager();
	// �v���C���[���͈͓��ɓ�������擾
	pItemManager->SetItem(Collision(pPlayer->GetPos()));

	// ��]������
	D3DXVECTOR3 rot = GetRot();
	rot.y += 0.01f;
	SetRot(rot);
}

//*****************
// �`�揈��
//*****************
void CItem::Draw(void)
{
	CObjectX::Draw();
}

//******************
// �ʒu�̐ݒ�
//******************
void CItem::SetPos(D3DXVECTOR3 pos)
{
	CObjectX::SetPos(pos);
}

//******************
// �����̐ݒ�
//******************
void CItem::SetRot(D3DXVECTOR3 rot)
{
	CObjectX::SetRot(rot);
}

//******************
// �ʒu���̎擾
//******************
D3DXVECTOR3 CItem::GetPos(void)
{
	return CObjectX::GetPos();
}

//******************
// �������̎擾
//******************
D3DXVECTOR3 CItem::GetRot(void)
{
	return CObjectX::GetRot();
}

//******************
// �����蔻��
//******************
CItemSkill* CItem::Collision(D3DXVECTOR3 pos)
{
	// �A�C�e���̎����4�_�ݒu
	D3DXVECTOR3 itemPos[4];
	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		itemPos[nCnt] = GetPos();
	}
	itemPos[0].x -= size;
	itemPos[0].z -= size;

	itemPos[1].x += size;
	itemPos[1].z -= size;

	itemPos[2].x += size;
	itemPos[2].z += size;

	itemPos[3].x -= size;
	itemPos[3].z += size;

	D3DXVECTOR3 Vec[4];
	D3DXVECTOR3 VecP[4];
	D3DXVECTOR3 nor[4];

	// �v���C���[�Ƃ̋���
	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		Vec[nCnt] = itemPos[(nCnt+1)%4] - itemPos[nCnt];
		VecP[nCnt] = pos - itemPos[nCnt];
		D3DXVec3Cross(&nor[nCnt], &VecP[nCnt], &Vec[nCnt]);
	}

	if (nor[0].y > 0.0f&&nor[1].y > 0.0f && nor[2].y > 0.0f && nor[3].y > 0.0f)
	{// �v���C���[���͈͓���������I��
		Uninit();
		return CItemSkill::Create(0);
	}
	else
	{
		return NULL;
	}
}