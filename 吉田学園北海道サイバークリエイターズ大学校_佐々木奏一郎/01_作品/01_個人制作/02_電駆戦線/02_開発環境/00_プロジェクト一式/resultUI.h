//***************************************
// 
// ���U���gUI���� [resultUI.h]
// Author:Sasaki Soichiro
//
//***************************************
#ifndef _RESULTUI_H_ // ���̃}�N����`������Ă��Ȃ�������
#define _RESULTUI_H_ // ��d�C���N���[�h�h�~�̃}�N����`

//******************
// �C���N���[�h
//******************
#include "main.h"
#include "object2D.h"

//************************
// ���U���gUI�N���X
//************************
class CResultUI :public CObject2D
{
public:
	CResultUI(int nPriority = 5);	// �R���X�g���N�^
	~CResultUI();					// �f�X�g���N�^
	static CResultUI* Create(D3DXVECTOR3 pos);// �C���X�^���X����
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