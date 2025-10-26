//**************************************
//
// ���b�V���ҏW���� [meshEdit.h]
// Author:Sasaki Soichiro
//
//**************************************
#ifndef _MESHEDIT_H_ // ���̃}�N����`������Ă��Ȃ�������
#define _MESHEDIT_H_ // ��d�C���N���[�h�h�~�̃}�N����`

//******************
// �C���N���[�h
//******************
#include "main.h"
#include "objectX.h"

//********************
// ���b�V���ҏW�N���X
//********************
class CMeshEdit :public CObjectX
{
public:
	CMeshEdit(int nPriority = 4);	// �R���X�g���N�^
	~CMeshEdit();					// �f�X�g���N�^
	static CMeshEdit* Create(D3DXVECTOR3 pos);// �C���X�^���X����
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
	static constexpr float fSpeed = 1.5f;
};
#endif