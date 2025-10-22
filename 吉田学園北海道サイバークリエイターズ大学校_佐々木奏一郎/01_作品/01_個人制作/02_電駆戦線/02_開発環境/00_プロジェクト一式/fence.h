//**************************************
//
// �d�C�򏈗� [fence.h]
// Author:Sasaki Soichiro
//
//**************************************
#ifndef _FENCE_H_ // ���̃}�N����`������Ă��Ȃ�������
#define _FENCE_H_ // ��d�C���N���[�h�h�~�̃}�N����`

//******************
// �C���N���[�h
//******************
#include "main.h"
#include "objectX.h"

//********************
// �t�F���X�N���X
//********************
class CFence :public CObjectX
{
public:
	CFence(int nPriority = 4);	// �R���X�g���N�^
	~CFence();					// �f�X�g���N�^
	static CFence* Create(D3DXVECTOR3 pos);// �C���X�^���X����
	HRESULT Init(D3DXVECTOR3 pos);	// ������
	void Uninit(void);				// �I��
	void Update(void);				// �X�V
	void Draw(void);				// �`��
	void SetPos(D3DXVECTOR3 pos);	// �ʒu
	void SetRot(D3DXVECTOR3 rot);	// ����
	D3DXVECTOR3 GetPos(void);		// �ʒu���̎擾
	D3DXVECTOR3 GetRot(void);		// �������̎擾
	bool Collision(D3DXVECTOR3 playerPos, D3DXVECTOR3 postPos0, D3DXVECTOR3 postPos1);
	void Shake(void);				// �h�炷
private:
	int m_nIdxXFile[3];	// �g�����f���̔ԍ�
	int m_nBreak;		// �N�[���_�E������
	int m_nBreakAttack;	// �N�[���_�E������
	int m_nLife;		// ���C�t
};
#endif