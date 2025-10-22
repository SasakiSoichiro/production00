//**************************************
//
// �[�d�ʒ��ߏ��� [adjust.h]
// Author:Sasaki Soichiro
//
//**************************************
#ifndef _ADJUST_H_ // ���̃}�N����`������Ă��Ȃ�������
#define _ADJUST_H_ // ��d�C���N���[�h�h�~�̃}�N����`

//******************
// �C���N���[�h
//******************
#include "main.h"
#include "itemskill.h"

class CAdjustUI;

//********************
// �[�d�ʒ��߃N���X
//********************
class CAdjust :public CItemSkill
{
public:
	CAdjust();	// �R���X�g���N�^
	~CAdjust();	// �f�X�g���N�^
	HRESULT Init(void);			// ������
	void Uninit(void);			// �I��
	void Update(void);			// �X�V
private:
	float m_fSum;			// ���v�ω���
	CAdjustUI* m_pAdjustUI;	// UI�ւ̃|�C���^
	static constexpr int thereshold = 10000;// �X�e�B�b�N�̃f�b�h�]�[��
	static constexpr float maxSum = 150.0f;	// �ω��ʂ̍ő�l
	static constexpr float frameLife = 0.5f;// 1�t���[���̕ω���
	static const D3DXVECTOR3 POS_UI;		// UI�̈ʒu
};
#endif