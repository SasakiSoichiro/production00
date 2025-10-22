//***************************************
// 
// �X�^�[�gUI���� [startUI.h]
// Author:Sasaki Soichiro
//
//***************************************
#ifndef _STARTUI_H_ // ���̃}�N����`������Ă��Ȃ�������
#define _STARTUI_H_ // ��d�C���N���[�h�h�~�̃}�N����`

//******************
// �C���N���[�h
//******************
#include "main.h"
#include "object2D.h"

//************************
// �X�^�[�gUI�N���X
//************************
class CStartUI :public CObject2D
{
public:
	CStartUI(int nPriority = 5);	// �R���X�g���N�^
	~CStartUI();					// �f�X�g���N�^
	static CStartUI* Create(D3DXVECTOR3 pos);// �C���X�^���X����
	HRESULT Init(D3DXVECTOR3 pos);	// ������
	void Uninit(void);				// �I��
	void Update(void);				// �X�V
	void Draw(void);				// �`��
	void SetPos(D3DXVECTOR3 pos);	// �ʒu�ݒ�
	void SetRot(D3DXVECTOR3 rot);	// �����ݒ�
	D3DXVECTOR3 GetPos(void);		// �ʒu���擾
private:
	int  m_nIdxTexture;			// �g���Ă���e�N�X�`���̔ԍ�
};
#endif