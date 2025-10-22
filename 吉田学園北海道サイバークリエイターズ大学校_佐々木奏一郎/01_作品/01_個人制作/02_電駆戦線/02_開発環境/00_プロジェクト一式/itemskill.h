//**************************************
//
// �A�C�e�����ʏ��� [itemskill.h]
// Author:Sasaki Soichiro
//
//**************************************
#ifndef _ITEMSKILL_H_ // ���̃}�N����`������Ă��Ȃ�������
#define _ITEMSKILL_H_ // ��d�C���N���[�h�h�~�̃}�N����`

//******************
// �C���N���[�h
//******************
#include "main.h"
#include "objectX.h"

//********************
// �A�C�e�����ʃN���X
//********************
class CItemSkill
{
public:
	CItemSkill();			// �R���X�g���N�^
	virtual ~CItemSkill();	// �f�X�g���N�^
	static CItemSkill* Create(int nType);	// �C���X�^���X����
	virtual HRESULT Init(void)=0;			// ������
	virtual void Uninit(void)=0;			// �I��
	virtual void Update(void)=0;			// �X�V
private:
};
#endif