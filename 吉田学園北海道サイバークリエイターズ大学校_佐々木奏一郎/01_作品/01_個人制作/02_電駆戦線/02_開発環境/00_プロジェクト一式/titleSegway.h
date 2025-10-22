//*******************************************
//
// �^�C�g���̃Z�O�E�F�C���� [titleSegway.h]
// Author:Sasaki Soichiro
//
//*******************************************
#ifndef _TITLESEGWAY_H_ // ���̃}�N����`������Ă��Ȃ�������
#define _TITLESEGWAY_H_ // ��d�C���N���[�h�h�~�̃}�N����`

//******************
// �C���N���[�h
//******************
#include "main.h"
#include "objectX.h"

//********************
// �v���C���[�N���X
//********************
class CTitleSegway :public CObjectX
{
public:
	CTitleSegway(int nPriority = 4);	// �R���X�g���N�^
	~CTitleSegway();					// �f�X�g���N�^
	static CTitleSegway* Create(D3DXVECTOR3 pos);// �C���X�^���X����
	HRESULT Init(D3DXVECTOR3 pos);	// ������
	void Uninit(void);				// �I��
	void Update(void);				// �X�V
	void Draw(void);				// �`��
	void SetPos(D3DXVECTOR3 pos);	// �ʒu
	void SetRot(D3DXVECTOR3 rot);	// ����
	D3DXVECTOR3 GetPos(void);		// �ʒu���̎擾
	D3DXVECTOR3 GetRot(void);
private:
	int m_nIdxXFile;		// �g���Ă���X�t�@�C���̔ԍ�
};
#endif