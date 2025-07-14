//******************************************
//	�I�u�W�F�N�gX���� [objectX.h]
// Author:Sasaki Soichiro
//
//******************************************
#ifndef _OBJECTX_H_//���̃}�N����`������Ă��Ȃ�������
#define _OBJECTX_H_//2�d�C���N���[�h�h�~�̃}�N����`
//******************
// �C���N���[�h
//******************
#include "main.h"
#include "object.h"
#include "Xmodel.h"

//***********************
// X�t�@�C���̕\���N���X
//***********************
class CObjectX :public CObject
{
public:
	CObjectX(int nPriority = 4);	// �R���X�g���N�^;
	~CObjectX();					// �f�X�g���N�^
	static CObjectX* Create(D3DXVECTOR3 pos);// �C���X�^���X����
	HRESULT Init(D3DXVECTOR3 pos);	// ������
	void Uninit(void);				// �I��
	void Update(void);				// �X�V
	void Draw(void);				// �`��
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }					// �ʒu�̐ݒ�
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }					// �����̐ݒ�
	void SetMatrix(D3DMATRIX mtxWorld) { m_mtxWorld = mtxWorld; }
	D3DXVECTOR3 GetPos(void) { return m_pos; };						// �ʒu���
	D3DXVECTOR3 GetRot(void) { return m_rot; };						// �������
	D3DXVECTOR2 GetSize(void) { return D3DXVECTOR2{ 0.0f,0.0f }; }	// �傫�����
	void BindXFile(CXModel::XMODEL pXFile);
private:
	CXModel::XMODEL m_XModel;
	D3DXMATRIX m_mtxWorld;		// �}�g���b�N�X
	LPDIRECT3DTEXTURE9 m_apTextureModel;		// �e�N�X�`���̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;			// ���_���̃|�C���^
	D3DXVECTOR3 m_pos;			// �ʒu
	D3DXVECTOR3 m_rot;			// ����
	int  m_nIdxTexture[128];	// �e�N�X�`���̃C���f�b�N�X
};

#endif