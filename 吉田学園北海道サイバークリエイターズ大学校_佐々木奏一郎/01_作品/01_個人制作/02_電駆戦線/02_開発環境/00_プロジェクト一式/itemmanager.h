//***************************************
// 
// �A�C�e���}�l�[�W���[���� [itemmanager.h]
// Author:Sasaki Soichiro
//
//***************************************
#ifndef _ITEMMANAGER_H_ // ���̃}�N����`������Ă��Ȃ�������
#define _ITEMMANAGER_H_ // ��d�C���N���[�h�h�~�̃}�N����`

//******************
// �C���N���[�h
//******************
#include "main.h"

class CItemSkill;

//*****************************
// �A�C�e���}�l�[�W���[�N���X
//*****************************
class CItemManager
{
public:
	CItemManager();	// �R���X�g���N�^
	~CItemManager();// �f�X�g���N�^
	HRESULT Init(void);	// ������
	void Uninit(void);	// �I��
	void Update(void);	// �X�V
	void SetItem(CItemSkill* pItemSkill) { m_pItemSkill = pItemSkill; }
private:
	CItemSkill* m_pItemSkill;
};
#endif