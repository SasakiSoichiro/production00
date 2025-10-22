//***************************************
// 
// �X�^��UI���� [titleUI.h]
// Author:Sasaki Soichiro
//
//***************************************
#ifndef _STANUI_H_ // ���̃}�N����`������Ă��Ȃ�������
#define _STANUI_H_ // ��d�C���N���[�h�h�~�̃}�N����`

//******************
// �C���N���[�h
//******************
#include "main.h"
#include "object2D.h"

//************************
// �X�^��UI�N���X
//************************
class CStanUI :public CObject2D
{
public:
	CStanUI(int nPriority = 5);	// �R���X�g���N�^
	~CStanUI();					// �f�X�g���N�^
	static CStanUI* Create(D3DXVECTOR3 pos);// �C���X�^���X����
	HRESULT Init(D3DXVECTOR3 pos);	// ������
	void Uninit(void);				// �I��
	void Update(void);				// �X�V
	void Draw(void);				// �`��
	void SetPos(D3DXVECTOR3 pos);	// �ʒu�ݒ�
	void SetRot(D3DXVECTOR3 rot);	// �����ݒ�
	D3DXVECTOR3 GetPos(void);		// �ʒu���擾
private:
	int  m_nIdxTexture;			// �e�N�X�`���̃C���f�b�N�X
};
#endif