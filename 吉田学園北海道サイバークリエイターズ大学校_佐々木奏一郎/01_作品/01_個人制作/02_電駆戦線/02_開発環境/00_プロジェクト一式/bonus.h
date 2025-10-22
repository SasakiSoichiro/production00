//***************************************
// 
// �{�[�i�X���� [bonus.h]
// Author:Sasaki Soichiro
//
//***************************************
#ifndef _BONUS_H_ // ���̃}�N����`������Ă��Ȃ�������
#define _BONUS_H_ // ��d�C���N���[�h�h�~�̃}�N����`

//******************
// �C���N���[�h
//******************
#include "main.h"
#include "object2D.h"

//************************
// �{�[�i�X�N���X
//************************
class CBonus :public CObject2D
{
public:
	CBonus(int nPriority = 5);	// �R���X�g���N�^
	~CBonus();					// �f�X�g���N�^
	HRESULT Init(D3DXVECTOR3 pos);	// ������
	void Uninit(void);				// �I��
	void Update(void);				// �X�V
	void Draw(void);				// �`��
	void SetPos(D3DXVECTOR3 pos);	// �ʒu�ݒ�
	void SetRot(D3DXVECTOR3 rot);	// �����ݒ�
	void SetSize(D3DXVECTOR2 size);	// �傫���̐ݒ�
	void SetTexture(const char* pFileName);// �g���e�N�X�`���̐ݒ�
	D3DXVECTOR3 GetPos(void);		// �ʒu���擾
private:
	int  m_nIdxTexture;			// �e�N�X�`���̃C���f�b�N�X
};
#endif