//***************************************
//
//	�I�u�W�F�N�g3D���� [object3D.h]
// Author:Sasaki Soichiro
//
//***************************************
#ifndef _OBJECT3D_H_// ���̃}�N����`������Ă��Ȃ�������
#define _OBJECT3D_H_// ��d�C���N���[�h�h�~�̃}�N����`
//******************
// �C���N���[�h
//******************
#include "main.h"
#include "object.h"

//**********************
// �I�u�W�F�N�g3D�N���X
//**********************
class CObject3D :public CObject
{
public:
	CObject3D(int nPriority = 4);	// �R���X�g���N�^
	~CObject3D();					// �f�X�g���N�^
	static CObject3D* Create(D3DXVECTOR3 pos);// �C���X�^���X����
	HRESULT Init(D3DXVECTOR3 pos);	// ������
	void Uninit(void);				// �I��
	void Update(void);				// �X�V
	void Draw(void);				// �`��
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; };	// �ʒu
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; };	// ����
	D3DXVECTOR3 GetPos(void) { return m_pos; };		// �ʒu���
	D3DXVECTOR2 GetSize(void) { return D3DXVECTOR2{ 0.0f,0.0f }; }		// �傫�����
	float GetHeight(D3DXVECTOR3 pos);
private:
	LPDIRECT3DTEXTURE9 m_pTexture;		// �e�N�X�`���̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// ���_���̃|�C���^
	D3DXVECTOR3 m_pos;		// �ʒu
	D3DXVECTOR3 m_rot;		// ����
	D3DXMATRIX m_mtxWorld;	// �}�g���b�N�X
};

#endif