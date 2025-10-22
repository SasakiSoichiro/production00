//***************************************
// 
// �^�C���{�[�i�X���� [timeBonus.h]
// Author:Sasaki Soichiro
//
//***************************************
#ifndef _TIMEBONUS_H_ // ���̃}�N����`������Ă��Ȃ�������
#define _TIMEBONUS_H_ // ��d�C���N���[�h�h�~�̃}�N����`

//******************
// �C���N���[�h
//******************
#include "main.h"
#include "bonus.h"

class CNumber;

//************************
// �{�[�i�X�N���X
//************************
class CTimeBonus :public CBonus
{
public:
	CTimeBonus(int nPriority = 5);	// �R���X�g���N�^
	~CTimeBonus();					// �f�X�g���N�^
	static CTimeBonus* Create(D3DXVECTOR3 pos);// �C���X�^���X����
	HRESULT Init(D3DXVECTOR3 pos);	// ������
	void Uninit(void);				// �I��
	void Update(void);				// �X�V
	void Draw(void);				// �`��
	void SetPos(D3DXVECTOR3 pos);	// �ʒu�ݒ�
	void SetRot(D3DXVECTOR3 rot);	// �����ݒ�
	D3DXVECTOR3 GetPos(void);		// �ʒu���擾
	void SetTime(int nTime) { m_nTime = nTime; }// ���Ԃ̐ݒ�
private:
	CNumber* m_pNumber[5];	// �i���o�[�ւ̃|�C���^
	static int m_nTime;		// ����
};
#endif