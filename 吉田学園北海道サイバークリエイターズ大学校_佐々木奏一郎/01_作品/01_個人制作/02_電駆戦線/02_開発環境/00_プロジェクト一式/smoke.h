//**********************************
//
//	������ [smoke.h]
// Author Sasaki Soichiro
//
//**********************************
#ifndef _SMOKE_H_//���̃}�N����`������Ă��Ȃ�������
#define _SMOKE_H_//2�d�C���N���[�h�h�~�̃}�N����`
//*******************
// �C���N���[�h
//*******************
#include "main.h"
#include "objectBillboard.h"

//************************
// ���N���X
//************************
class CSmoke :public CObjectBillboard
{
public:
	CSmoke(int nPriority = 4);	// �R���X�g���N�^
	~CSmoke();					// �f�X�g���N�^

	static CSmoke* Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, D3DXVECTOR2 size, int nLife, D3DXCOLOR col);// �C���X�^���X����

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