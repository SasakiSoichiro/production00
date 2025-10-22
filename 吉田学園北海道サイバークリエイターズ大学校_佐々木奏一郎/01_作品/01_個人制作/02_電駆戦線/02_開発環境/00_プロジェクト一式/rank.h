//**************************************
//
// �����N���� [rank.h]
// Author:Sasaki Soichiro
//
//**************************************
#ifndef _RANK_H_ // ���̃}�N����`������Ă��Ȃ�������
#define _RANK_H_ // ��d�C���N���[�h�h�~�̃}�N����`

//******************
// �C���N���[�h
//******************
#include "main.h"
#include "objectX.h"

//********************
// �����N�N���X
//********************
class CRank :public CObjectX
{
public:
	CRank(int nPriority = 4);	// �R���X�g���N�^
	~CRank();					// �f�X�g���N�^
	static CRank* Create(D3DXVECTOR3 pos);// �C���X�^���X����
	HRESULT Init(D3DXVECTOR3 pos);	// ������
	void Uninit(void);				// �I��
	void Update(void);				// �X�V
	void Draw(void);				// �`��
	void SetRank(void);				// Xmodel�̐ݒ�
	void SetPos(D3DXVECTOR3 pos);	// �ʒu
	void SetRot(D3DXVECTOR3 rot);	// ����
	D3DXVECTOR3 GetPos(void);		// �ʒu���擾
	D3DXVECTOR3 GetRot(void);		// �������擾
private:
	int m_nIdxXFile[4];				// �g���Ă���X�t�@�C���̔ԍ�
};
#endif