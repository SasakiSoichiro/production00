//************************************
//
// �^�C�g������ [title.h]
// Author:Sasaki Soichiro
//
//************************************
#ifndef _TITLE_H_ // ���̃}�N����`������Ă��Ȃ�������
#define _TITLE_H_ // ��d�C���N���[�h�h�~�̃}�N����`

//******************
// �C���N���[�h
//******************
#include "main.h"
#include "scene.h"

//********************
// �^�C�g���N���X
//********************
class CTitle :public CScene
{
public:
	CTitle();	// �R���X�g���N�^
	~CTitle();	// �f�X�g���N�^
	HRESULT Init(D3DXVECTOR3 pos);		// ������
	void Uninit(void);					// �I��
	void Update(void);					// �X�V
	void Draw(void);					// �`��
	void SetPos(D3DXVECTOR3 pos) {};	// �ʒu
	void SetRot(D3DXVECTOR3 rot) {};	// ����
	D3DXVECTOR3 GetPos(void) { return NONE; }	// �ʒu���
private:
};
#endif