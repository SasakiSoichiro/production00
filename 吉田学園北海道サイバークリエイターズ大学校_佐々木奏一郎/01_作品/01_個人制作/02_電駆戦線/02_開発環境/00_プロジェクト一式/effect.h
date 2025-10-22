//****************************************
//
//	�G�t�F�N�g���� [effect.h]
// Author Sasaki Soichiro
//
//****************************************
#ifndef _EFFECT_H_//���̃}�N����`������Ă��Ȃ�������
#define _EFFECT_H_//2�d�C���N���[�h�h�~�̃}�N����`
#include "main.h"
#include "objectBillboard.h"

//********************
// �G�t�F�N�g�N���X
//********************
class CEffect :public CObjectBillboard
{
public:
	CEffect(int nPriority = 4);	// �R���X�g���N�^
	~CEffect();					// �f�X�g���N�^

	static CEffect* Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, D3DXVECTOR2 size, int nLife, D3DXCOLOR col);// �C���X�^���X����
	HRESULT Init(D3DXVECTOR3 pos);	// ������
	void Uninit(void);				// �I��
	void Update(void);				// �X�V
	void Draw(void);				// �`��
	void SetPos(D3DXVECTOR3 pos);	// �ʒu�̐ݒ�
	void SetRot(D3DXVECTOR3 rot);	// �����̐ݒ�
	void SetMove(D3DXVECTOR3 move) { m_move = move; }	// ���[�u�l�̐ݒ�
	void SetCol(D3DXCOLOR col);							// �F�̐ݒ�
	void SetSize(D3DXVECTOR2 size);						// �傫���̐ݒ�
	void SetTexture(int nTexture) { m_nIdxTexture = nTexture; }	// �e�N�X�`���̐ݒ�
	void SetLife(int nLife) { m_nLife = nLife; }// �����̐ݒ�
	D3DXVECTOR3 GetPos(void);					// �ʒu���̎擾
	D3DXVECTOR3 GetMove(void) { return m_move; }// ���[�u�l�̎擾
	D3DXVECTOR2 GetSize(void);					// �傫�����̎擾
private:
	int  m_nIdxTexture;			// �g���e�N�X�`���̔ԍ�
	D3DXVECTOR3 m_move;			// �ړ���
	int m_nPatternAnim;			// �p�^�[���J�E���g
	int m_nCntAnim;				// �A�j���[�V�����J�E���g
	int m_nLife;				// ����
	bool m_bLife;				// �c���Ă��邩
	static constexpr int maxLife = 60;		// �����̎���
	static constexpr int anim = 3;			// �X�V����t���[��
	static constexpr int patternAnim = 4;	// �A�j���[�V�����̃p�^�[����
	static constexpr float texOffset = 0.25f;	// �e�N�X�`�����W�̃I�t�Z�b�g
};
#endif