//**************************************
//
// �u���b�N���� [block.h]
// Author:Sasaki Soichiro
//
//**************************************
#ifndef _BLOCK_H_ // ���̃}�N����`������Ă��Ȃ�������
#define _BLOCK_H_ // ��d�C���N���[�h�h�~�̃}�N����`

//******************
// �C���N���[�h
//******************
#include "main.h"
#include "objectX.h"

//********************
// �v���C���[�N���X
//********************
class CBlock :public CObjectX
{
public:
	CBlock(int nPriority = 4);	// �R���X�g���N�^
	~CBlock();					// �f�X�g���N�^
	static CBlock* Create(D3DXVECTOR3 pos,const char*pFileName,int nType);// �C���X�^���X����
	HRESULT Init(D3DXVECTOR3 pos);	// ������
	void Uninit(void);				// �I��
	void Update(void);				// �X�V
	void Draw(void);				// �`��
	void SetPos(D3DXVECTOR3 pos);	// �ʒu
	void SetRot(D3DXVECTOR3 rot);	// ����
	void SetXModel(const char*fileName);// �g�����f���̐ݒ�
	D3DXVECTOR3 GetPos(void);			// �ʒu���̎擾
	D3DXVECTOR3 GetRot(void);			// �������̎擾
	CXModel::XMODEL GetXModel(void);	// ���f�����̎擾
private:
	int m_nIdxXFile;	// �g�����f���̔ԍ�
};
#endif