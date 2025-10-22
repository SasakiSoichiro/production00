//**********************************
//
//	�U��G�t�F�N�g���� [sparkEffect.h]
// Author Sasaki Soichiro
//
//**********************************
#ifndef _SPARKEFFECT_H_//���̃}�N����`������Ă��Ȃ�������
#define _SPARKEFFECT_H_//2�d�C���N���[�h�h�~�̃}�N����`
//*******************
// �C���N���[�h
//*******************
#include "main.h"
#include "objectBillboard.h"

//************************
// �W�܂�G�t�F�N�g�N���X
//************************
class CSparkEffect :public CObjectBillboard
{
public:
	CSparkEffect(int nPriority = 4);	// �R���X�g���N�^
	~CSparkEffect();					// �f�X�g���N�^

	static CSparkEffect* Create(D3DXVECTOR3 pos, D3DXVECTOR3 move,D3DXVECTOR2 size, int nLife, D3DXCOLOR col);// �C���X�^���X����

	HRESULT Init(D3DXVECTOR3 pos);	// ������
	void Uninit(void);				// �I��
	void Update(void);				// �X�V
	void Draw(void);				// �`��
	void SetPos(D3DXVECTOR3 pos);	// �ʒu
	void SetCol(D3DXCOLOR col);		// �F�̐ݒ�
	void SetSize(D3DXVECTOR2 size);	// �傫���̐ݒ�
	D3DXVECTOR3 GetPos(void);		// �ʒu���擾
	D3DXVECTOR2 GetSize(void);		// �傫�����擾
private:
	int  m_nIdxTexture;			// �g���Ă���e�N�X�`���̔ԍ�
	D3DXVECTOR3 m_move;			// �ړ���
	int m_nLife;				// ����
};
#endif