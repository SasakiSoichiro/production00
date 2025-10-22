//***************************************
// 
// �X�^��UI���� [titleUI.h]
// Author:Sasaki Soichiro
//
//***************************************
#ifndef _CONTROLLERUI_H_ // ���̃}�N����`������Ă��Ȃ�������
#define _CONTROLLERUI_H_ // ��d�C���N���[�h�h�~�̃}�N����`

//******************
// �C���N���[�h
//******************
#include "main.h"
#include "object2D.h"

//************************
// �X�^��UI�N���X
//************************
class CControllerUI :public CObject2D
{
public:
	CControllerUI(int nPriority = 5);	// �R���X�g���N�^
	~CControllerUI();					// �f�X�g���N�^
	static CControllerUI* Create(D3DXVECTOR3 pos);// �C���X�^���X����
	HRESULT Init(D3DXVECTOR3 pos);	// ������
	void Uninit(void);				// �I��
	void Update(void);				// �X�V
	void Draw(void);				// �`��
	void SetPos(D3DXVECTOR3 pos);	// �ʒu�ݒ�
	void SetRot(D3DXVECTOR3 rot);	// �����ݒ�
	D3DXVECTOR3 GetPos(void);		// �ʒu���擾
private:
	int  m_nIdxTexture;			// �e�N�X�`���̃C���f�b�N�X
	bool m_bScreen;
};
#endif