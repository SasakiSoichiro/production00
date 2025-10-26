//*************************************************
//
//	�r���{�[�h���� [objectBillboard.h]
// Author:Sasaki Soichiro
//
//*************************************************
#ifndef _OBJECTBILLBOARD_H_// ���̃}�N����`������Ă��Ȃ�������
#define _OBJECTBILLBOARD_H_// ��d�C���N���[�h�h�~�̃}�N����`

//******************
// �C���N���[�h
//******************
#include "main.h"
#include "object.h"

//*******************
// �r���{�[�h�N���X
//*******************
class CObjectBillboard:public CObject
{
public:
	CObjectBillboard(int nPriority = 4);// �R���X�g���N�^;
	~CObjectBillboard();				// �f�X�g���N�^
	HRESULT Init(D3DXVECTOR3 pos);	// ������
	void Uninit(void);				// �I��
	void Update(void);				// �X�V
	void Draw(void);				// �`��
	void SetPos(D3DXVECTOR3 pos);	// �ʒu�̐ݒ�
	void SetRot(D3DXVECTOR3 rot);	// �����̐ݒ�
	void SetTex(D3DXVECTOR2 uv1, D3DXVECTOR2 uv2, D3DXVECTOR2 uv3, D3DXVECTOR2 uv4);// �e�N�X�`�����W�̐ݒ�
	void SetCol(D3DXCOLOR col);					// �F�̐ݒ�
	void SetSize(D3DXVECTOR2 size);				// �傫���̐ݒ�
	void SetOffset(D3DXVECTOR2 offset);			// �I�t�Z�b�g�̐ݒ�
	D3DXVECTOR3 GetPos(void) { return m_pos; }	// �ʒu���擾
	D3DXVECTOR3 GetRot(void) { return m_rot; }	// �������擾
	D3DXCOLOR GetCol(void) { return m_col; }	// �Ӑ}���擾
	D3DXVECTOR2 GetSize(void) { return m_size; }// �傫�����擾
private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// ���_���̃|�C���^
	D3DXVECTOR3 m_pos;					// �ʒu
	D3DXVECTOR3 m_rot;					// ����
	D3DXVECTOR2 m_size;					// �傫��
	D3DXVECTOR2 m_offset;				// �I�t�Z�b�g
	D3DXCOLOR m_col;					// �F
	D3DXMATRIX m_mtxWorld;				// �}�g���b�N�X
};

#endif