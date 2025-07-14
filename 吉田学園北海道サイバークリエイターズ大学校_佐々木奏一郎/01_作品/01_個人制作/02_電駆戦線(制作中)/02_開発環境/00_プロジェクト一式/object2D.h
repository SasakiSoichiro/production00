//******************************************
//
// �I�u�W�F�N�g2D���� [object2D.h]
// Author:Sasaki Soichiro
//
//******************************************
#ifndef _OBJECT2D_H_ // ���̃}�N����`������Ă��Ȃ�������
#define _OBJECT2D_H_ // ��d�C���N���[�h�h�~�̃}�N����`

//******************
// �C���N���[�h
//******************
#include "main.h"
#include "object.h"

//********************
// �I�u�W�F�N�g�N���X
//********************
class CObject2D:public CObject
{
public:
	CObject2D(int nPriority);	// �R���X�g���N�^
	~CObject2D();				// �f�X�g���N�^
	HRESULT Init(D3DXVECTOR3 pos);	// ������
	void Uninit(void);				// �I��
	void Update(void);				// �X�V
	void Draw(void);				// �`��
	void SetPos(D3DXVECTOR3 pos);	// �ʒu�̐ݒ�
	void SetRot(D3DXVECTOR3 rot);	// �����̐ݒ�
	void SetTex(D3DXVECTOR2 uv1, D3DXVECTOR2 uv2, D3DXVECTOR2 uv3, D3DXVECTOR2 uv4);// UV���W�̐ݒ�
	void SetCol(D3DXCOLOR col);// �F�̐ݒ�
	void SetSize(D3DXVECTOR2 size);// �傫���̐ݒ�
	D3DXVECTOR3 GetPos(void) { return m_pos; }	// �ʒu���̎擾
	D3DXVECTOR3 GetRot(void) { return m_rot; }	// �������̎擾
	D3DXCOLOR GetCol(void) { return m_col; }	// �F���̎擾
	D3DXVECTOR2 GetSize(void){ return m_size; }	// �傫�����̎擾
	//void BindTexture(LPDIRECT3DTEXTURE9 pTexture);
private:
	//LPDIRECT3DTEXTURE9 m_pTexture;		// �e�N�X�`���̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// ���_���̃|�C���^
	D3DXVECTOR3 m_pos;	// �ʒu
	D3DXVECTOR3 m_rot;	// ����
	D3DXCOLOR m_col;	// �F
	D3DXVECTOR2 m_size;	// �傫��
};
#endif