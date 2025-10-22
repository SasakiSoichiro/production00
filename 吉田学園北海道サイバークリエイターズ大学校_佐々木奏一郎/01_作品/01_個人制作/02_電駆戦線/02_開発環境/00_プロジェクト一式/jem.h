//**************************************
//
// ��Ώ��� [jem.h]
// Author:Sasaki Soichiro
//
//**************************************
#ifndef _JEM_H_ // ���̃}�N����`������Ă��Ȃ�������
#define _JEM_H_ // ��d�C���N���[�h�h�~�̃}�N����`

//******************
// �C���N���[�h
//******************
#include "main.h"
#include "objectX.h"

//********************
// ��΃N���X
//********************
class CJem :public CObjectX
{
public:
	CJem(int nPriority = 4);	// �R���X�g���N�^
	~CJem();					// �f�X�g���N�^
	static CJem* Create(D3DXVECTOR3 pos);// �C���X�^���X����
	HRESULT Init(D3DXVECTOR3 pos);	// ������
	void Uninit(void);				// �I��
	void Update(void);				// �X�V
	void Draw(void);				// �`��
	void SetPos(D3DXVECTOR3 pos);	// �ʒu
	void SetRot(D3DXVECTOR3 rot);	// ����
	D3DXVECTOR3 GetPos(void);		// �ʒu���̎擾
	D3DXVECTOR3 GetRot(void);		// �������̎擾
	void Shake(void);				// �h���
private:
	int m_nIdxXFile[3];	// �g�����f���̔ԍ�
	int m_nLife;		// ��΂̗̑�
	int m_nShake;		// �h��鎞��
	D3DXVECTOR3 m_OffsetPos;// �����̈ʒu
};
#endif