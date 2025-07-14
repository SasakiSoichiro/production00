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

//********************
// �I�u�W�F�N�g�N���X
//********************
class CObject2DMulti :public CObject
{
public:
	CObject2DMulti(int nPriority);	// �R���X�g���N�^
	~CObject2DMulti();	// �f�X�g���N�^
	HRESULT Init(D3DXVECTOR3 pos);	// ������
	void Uninit(void);	// �I��
	void Update(void);	// �X�V
	void Draw(void);	// �`��
	void SetPos(D3DXVECTOR3 pos);// �ʒu
	void SetRot(D3DXVECTOR3 rot);// ����
	void SetTex(D3DXVECTOR2 uv1, D3DXVECTOR2 uv2, D3DXVECTOR2 uv3, D3DXVECTOR2 uv4);
	void SetTex2(D3DXVECTOR2 uv1, D3DXVECTOR2 uv2, D3DXVECTOR2 uv3, D3DXVECTOR2 uv4);
	void SetCol(D3DXCOLOR col);
	void SetSize(D3DXVECTOR2 size);
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	D3DXCOLOR GetCol(void) { return m_col; }
	D3DXVECTOR2 GetSize(void) { return m_size; }
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture0, LPDIRECT3DTEXTURE9 pTexture1);
private:
	LPDIRECT3DTEXTURE9 m_pTexture[2];		// �e�N�X�`���̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// ���_���̃|�C���^
	D3DXVECTOR3 m_pos;	// �ʒu
	D3DXVECTOR3 m_rot;	// ����
	D3DXCOLOR m_col;
	D3DXVECTOR2 m_size;
};
#endif