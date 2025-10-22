//*****************************************
//
// �A�C�e�����ʏ��� [itemskill.cpp]
// Author:Sasaki Soichiro
//
//*****************************************

//*******************
// �C���N���[�h
//*******************
#include "itemskill.h"
#include "item.h"
#include "adjust.h"

//*****************
// �R���X�g���N�^
//*****************
CItemSkill::CItemSkill() 
{
}

//*****************
// �f�X�g���N�^
//*****************
CItemSkill::~CItemSkill()
{
}

//******************
// �C���X�^���X����
//*******************
CItemSkill* CItemSkill::Create(int nType)
{
	CItemSkill* pItemSkill;
	int nNum = CObject::GetNumAll();
	if (nNum < MAX_OBJ - 1)
	{// �I�u�W�F�N�g���ő吔�ɒB���Ă��Ȃ��ꍇ
		switch (nType)
		{
		case CItem::ITEM_ADJUST:
			// �C���X�^���X����
			pItemSkill = new CAdjust;
			// ������
			pItemSkill->Init();		
			return pItemSkill;
			break;
		}
	}

	return NULL;
}
