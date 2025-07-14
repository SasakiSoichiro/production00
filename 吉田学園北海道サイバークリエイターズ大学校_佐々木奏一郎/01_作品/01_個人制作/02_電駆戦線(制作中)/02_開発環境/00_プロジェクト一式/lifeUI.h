//***************************************
// 
// ���C�tUI���� [lifeUI.h]
// Author:Sasaki Soichiro
//
//***************************************
#ifndef _LIFEUI_H_ // ���̃}�N����`������Ă��Ȃ�������
#define _LIFEUI_H_ // ��d�C���N���[�h�h�~�̃}�N����`

//******************
// �C���N���[�h
//******************
#include "main.h"
#include "object.h"
#include "number.h"
#include "object2DMulti.h"

//********************
// ���C�t�N���X
//********************
class CLifeUI :public CObject2DMulti
{
public:
	CLifeUI(int nPriority = 5);	// �R���X�g���N�^
	~CLifeUI();					// �f�X�g���N�^
	static CLifeUI* Create(D3DXVECTOR3 pos);
	HRESULT Init(D3DXVECTOR3 pos);	// ������
	void Uninit(void);				// �I��
	void Update(void);				// �X�V
	void Draw(void);				// �`��
	void SetPos(D3DXVECTOR3 pos);	// �ʒu�ݒ�
	void SetRot(D3DXVECTOR3 rot);	// �����ݒ�
	void SetLife(float fLife) { m_fLife = fLife; }		// ���C�t�̐ݒ�
	int Digit(int nScore);
	D3DXVECTOR3 GetPos(void);		// �ʒu���擾
private:
	int  m_nIdxTexture[4];			// �e�N�X�`���̃C���f�b�N�X
	static CNumber* m_apNumber[3];	// �i���o�[�ւ̃|�C���^
	static CSymbol* m_pSymbol;		// �p�[�Z���g�ւ̃|�C���^
	D3DXVECTOR2 m_size;				// �傫��
	float m_fLife;					// ���C�t
	int m_nDigit;					// ���݂̌�
};

#endif