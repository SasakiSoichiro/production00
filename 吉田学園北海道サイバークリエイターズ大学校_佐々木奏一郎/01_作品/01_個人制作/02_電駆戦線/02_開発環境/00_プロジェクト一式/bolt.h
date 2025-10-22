//**************************************
//
// �{���g���� [bolt.h]
// Author:Sasaki Soichiro
//
//**************************************
#ifndef _BOLT_H_ // ���̃}�N����`������Ă��Ȃ�������
#define _BOLT_H_ // ��d�C���N���[�h�h�~�̃}�N����`

//******************
// �C���N���[�h
//******************
#include "main.h"
#include "objectX.h"

//********************
// �{���g�N���X
//********************
class CBolt :public CObjectX
{
public:
	CBolt(int nPriority = 4);	// �R���X�g���N�^
	~CBolt();					// �f�X�g���N�^
	static CBolt* Create(D3DXVECTOR3 pos);// �C���X�^���X����
	HRESULT Init(D3DXVECTOR3 pos);	// ������
	void Uninit(void);				// �I��
	void Update(void);				// �X�V
	void Draw(void);				// �`��
	void SetPos(D3DXVECTOR3 pos);	// �ʒu
	void SetRot(D3DXVECTOR3 rot);	// ����
	D3DXVECTOR3 GetPos(void);		// �ʒu���̎擾
	D3DXVECTOR3 GetRot(void);		// �������̎擾
private:
	int m_nIdxXFile;	// �g�����f���̔ԍ�
	int m_nBreak;		// �N�[���_�E������
	int m_nLife;		// ����
	float m_fAngle;		// ����
	float m_fAngleSum;	// ��]�����p�x�̍��v
	static constexpr int maxBreakTime = 60;		// �x�e�̎���
	static constexpr int maxLife = 30;			// �����̎���
	static constexpr float maxRange = 100.0f;	// ���肷�鋗��
};
#endif