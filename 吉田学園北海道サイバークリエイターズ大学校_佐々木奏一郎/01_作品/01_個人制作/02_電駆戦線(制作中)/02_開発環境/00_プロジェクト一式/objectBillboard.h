//*************************************************
//
//	�r���{�[�h���� [objectBillboard.h]
// Author:Sasaki Soichiro
//
//*************************************************
#ifndef _OBJECTBILLBOARD_H_//���̃}�N����`������Ă��Ȃ�������
#define _OBJECTBILLBOARD_H_//��d�C���N���[�h�h�~�̃}�N����`

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
	static CObjectBillboard* Create(D3DXVECTOR3 pos);// �C���X�^���X����
	HRESULT Init(D3DXVECTOR3 pos);	// ������
	void Uninit(void);				// �I��
	void Update(void);				// �X�V
	void Draw(void);				// �`��
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; };	// �ʒu
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; };	// ����
	D3DXVECTOR3 GetPos(void) { return m_pos; };		// �ʒu���
	D3DXVECTOR2 GetSize(void) { return m_size; }	// �傫�����
private:
	LPDIRECT3DTEXTURE9 m_pTexture;		// �e�N�X�`���̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// ���_���̃|�C���^
	D3DXVECTOR3 m_pos;		// �ʒu
	D3DXVECTOR3 m_rot;		// ����
	D3DXVECTOR2 m_size;		// �傫��
	D3DXMATRIX m_mtxWorld;	// �}�g���b�N�X
	int m_nIdxTexture;		// �e�N�X�`���̃C���f�b�N�X
};

#endif