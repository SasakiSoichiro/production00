//***************************************
// 
// �[�d����UI���� [lifeUI.h]
// Author:Sasaki Soichiro
//
//***************************************
#ifndef _ADJUSTUI_H_ // ���̃}�N����`������Ă��Ȃ�������
#define _ADJUSTUI_H_ // ��d�C���N���[�h�h�~�̃}�N����`

//******************
// �C���N���[�h
//******************
#include "main.h"
#include "object.h"
#include "object2DMulti.h"

//********************
// �[�d�ʒ��߃N���X
//********************
class CAdjustUI :public CObject2DMulti
{
public:
	CAdjustUI(int nPriority = 5);	// �R���X�g���N�^
	~CAdjustUI();					// �f�X�g���N�^
	static CAdjustUI* Create(D3DXVECTOR3 pos);
	HRESULT Init(D3DXVECTOR3 pos);	// ������
	void Uninit(void);				// �I��
	void Update(void);				// �X�V
	void Draw(void);				// �`��
	void SetPos(D3DXVECTOR3 pos);	// �ʒu�ݒ�
	void SetRot(D3DXVECTOR3 rot);	// �����ݒ�
	D3DXVECTOR3 GetPos(void);		// �ʒu���擾
	void SetLife(float fLife) { m_fLife = fLife; }
	float GetLife(void) { return m_fLife; }
private:
	// ���
	typedef enum
	{
		TYPE_SHAPE = 0,	// �`��̃e�N�X�`��
		TYPE_COLOR,		// �F�̃e�N�X�`��
		TYPE_MAX
	}TYPE;
	int  m_nIdxTexture[TYPE_MAX];	// �e�N�X�`���̃C���f�b�N�X
	D3DXVECTOR2 m_size;				// �傫��
	float m_fLife;					// ���C�t
	static constexpr float maxLife = 150.0f;// �ω��ʂ̍ő�l
	static constexpr float texOffset = 0.5f;// �e�N�X�`�����W�̃I�t�Z�b�g
	static const D3DXVECTOR3 SIZE;			// �傫��
};

#endif