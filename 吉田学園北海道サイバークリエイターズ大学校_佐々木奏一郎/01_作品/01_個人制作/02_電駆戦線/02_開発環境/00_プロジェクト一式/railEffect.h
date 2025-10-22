//=============================================================================
//
// ���[�����̃G�t�F�N�g���� [effect.h]
// Author Sasaki Soichiro
//
//=============================================================================
#ifndef _RAILEFFECT_H_//���̃}�N����`������Ă��Ȃ�������
#define _RAILEFFECT_H_//2�d�C���N���[�h�h�~�̃}�N����`
#include "main.h"
#include "object3D.h"

//************************
// ���[���G�t�F�N�g�N���X
//************************
class CRailEffect :public CObject3D
{
public:
	CRailEffect(int nPriority = 4);	// �R���X�g���N�^
	~CRailEffect();					// �f�X�g���N�^

	static CRailEffect* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot,D3DXVECTOR2 size);// �C���X�^���X����

	HRESULT Init(D3DXVECTOR3 pos);	// ������
	void Uninit(void);				// �I��
	void Update(void);				// �X�V
	void Draw(void);				// �`��
	void SetPos(D3DXVECTOR3 pos);	// �ʒu�̐ݒ�
	void SetCol(D3DXCOLOR col);		// �F�̐ݒ�
	void SetSize(D3DXVECTOR2 size);	// �傫���̐ݒ�
	D3DXVECTOR3 GetPos(void);		// �ʒu���̎擾
	D3DXVECTOR2 GetSize(void);		// �傫�����̎擾
private:
	int  m_nIdxTexture;			// �g���e�N�X�`���̔ԍ�
	D3DXVECTOR3 m_move;			// �ړ���
	int m_nPatternAnim;			// �p�^�[���J�E���g
	int m_nCntAnim;				// �A�j���[�V�����J�E���g
	int m_nLife;				// ���C�t
	bool m_bLife;				// �c���Ă��邩
};
#endif