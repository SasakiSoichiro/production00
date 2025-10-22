//**********************************************
// 
// �`���[�g���A���̃`�F�b�N���� [tutorialCheck.h]
// Author:Sasaki Soichiro
//
//**********************************************
#ifndef _TUTORIALCHECK_H_ // ���̃}�N����`������Ă��Ȃ�������
#define _TUTORIALCHECK_H_ // ��d�C���N���[�h�h�~�̃}�N����`

//******************
// �C���N���[�h
//******************
#include "main.h"
#include "object2D.h"
#include "tutorial.h"

//********************************
// �`���[�g���A���̃`�F�b�N�N���X
//********************************
class CTutorialCheck :public CObject2D
{
public:
	CTutorialCheck(int nPriority = 5);	// �R���X�g���N�^
	~CTutorialCheck();					// �f�X�g���N�^
	static CTutorialCheck* Create(D3DXVECTOR3 pos);// �C���X�^���X����
	HRESULT Init(D3DXVECTOR3 pos);	// ������
	void Uninit(void);				// �I��
	void Update(void);				// �X�V
	void Draw(void);				// �`��
	void SetPos(D3DXVECTOR3 pos);	// �ʒu�ݒ�
	void SetRot(D3DXVECTOR3 rot);	// �����ݒ�
	D3DXVECTOR3 GetPos(void);		// �ʒu���擾
	void Clear(void);					// ���ڂ̐ݒ�
private:
	CObject2D* m_pCheckBox;					// �`�F�b�N���ڕ\���̃|�C���^
	int  m_nIdxTextureCheck[2];				// �e�N�X�`���̃C���f�b�N�X
	int  m_nIdxTextureCheckBox[CTutorial::STATE_MAX];	// �e�N�X�`���̃C���f�b�N�X
	static const D3DXVECTOR2 SIZE_CHECK;	// �傫��
	static const D3DXVECTOR2 SIZE_CHECKBOX;	// �傫��
	static constexpr float boxOffset = 300.0f;
	bool m_bCheck;							// �`�F�b�N
	int m_nCheckBox;						// �`�F�b�N����
	int m_nCnt;								// �J�E���g
};
#endif