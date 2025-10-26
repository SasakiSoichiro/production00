//=============================================================================
//
// �I�u�W�F�N�g2D���� [object2D.h]
// Author : Sasaki Soichiro
//
//=============================================================================
#ifndef _OBJECT2DMULTI_H_ // ���̃}�N����`������Ă��Ȃ�������
#define _OBJECT2DMULTI_H_ // ��d�C���N���[�h�h�~�̃}�N����`

//******************
// �C���N���[�h
//******************
#include "main.h"
#include "object.h"

//****************************
// �I�u�W�F�N�g2D�}���`�N���X
//****************************
class CObject2DMulti :public CObject
{
public:
	CObject2DMulti(int nPriority);	// �R���X�g���N�^
	~CObject2DMulti();				// �f�X�g���N�^
	HRESULT Init(D3DXVECTOR3 pos);	// ������
	void Uninit(void);				// �I��
	void Update(void);				// �X�V
	void Draw(void);				// �`��
	void SetPos(D3DXVECTOR3 pos);// �ʒu
	void SetRot(D3DXVECTOR3 rot);// ����
	void SetTex(D3DXVECTOR2 uv1, D3DXVECTOR2 uv2, D3DXVECTOR2 uv3, D3DXVECTOR2 uv4);	// �e�N�X�`�����W�̐ݒ�1
	void SetTex2(D3DXVECTOR2 uv1, D3DXVECTOR2 uv2, D3DXVECTOR2 uv3, D3DXVECTOR2 uv4);	// �e�N�X�`�����W�̐ݒ�2
	void SetCol(D3DXCOLOR col);					// �F�̐ݒ�
	void SetSize(D3DXVECTOR2 size);				// �傫���̐ݒ�
	D3DXVECTOR3 GetPos(void) { return m_pos; }	// �ʒu�̐ݒ�
	D3DXVECTOR3 GetRot(void) { return m_rot; }	// �����̐ݒ�
	D3DXCOLOR GetCol(void) { return m_col; }	// �F�̐ݒ�
	D3DXVECTOR2 GetSize(void) { return m_size; }// �傫���̐ݒ�
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture0, LPDIRECT3DTEXTURE9 pTexture1);// �e�N�X�`���̊��蓖��
private:
	LPDIRECT3DTEXTURE9 m_pTexture[2];	// �e�N�X�`���̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// ���_���̃|�C���^
	D3DXVECTOR3 m_pos;					// �ʒu
	D3DXVECTOR3 m_rot;					// ����
	D3DXCOLOR m_col;					// �F
	D3DXVECTOR2 m_size;					// �傫��
};
#endif