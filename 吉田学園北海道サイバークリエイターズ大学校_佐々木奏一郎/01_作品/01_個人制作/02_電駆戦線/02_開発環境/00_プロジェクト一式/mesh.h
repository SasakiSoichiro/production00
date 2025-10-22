//******************************************
//
//	���b�V���t�B�[���h���� [Meshfield.h]
// Author:Sasaki Soichiro
//
//******************************************
#ifndef _MESHFIELD_H_// ���̃}�N����`������Ă��Ȃ�������
#define _MESHFIELD_H_// 2�d�C���N���[�h�h�~�̃}�N����`

//***********************
// �C���N���[�h
//***********************
#include "main.h"
#include "object.h"
#include <fstream>
#include <vector>

//**********************
// �}�N����`
//**********************
#define OBJ_X (500.0f)	// X�����̑傫��
#define OBJ_Z (500.0f)	// Z�����̑傫��
#define XMESH (100)		// X�����̕�����
#define ZMESH (100)		// Z�����̕�����
#define VTXCNT ((XMESH+1)*(ZMESH+1))				// ���_���̌v�Z
#define POLYCNT ((2*XMESH*ZMESH)+4*(ZMESH-1))		// �|���S�����̌v�Z
#define IDXCNT (((XMESH+1)*2*ZMESH)+(ZMESH-1)*4)	// �C���f�b�N�X���̌v�Z

//**********************
// ���b�V���N���X
//**********************
class CMesh :public CObject
{
public:
	CMesh(int nPriority=2);	// �R���X�g���N�^
	~CMesh();				// �f�X�g���N�^
	static CMesh* Create(D3DXVECTOR3 pos);// �C���X�^���X����
	HRESULT Init(D3DXVECTOR3 pos);	// ������
	void Uninit(void);				// �I��
	void Update(void);				// �X�V
	void Draw(void);				// �`��
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; };	// �ʒu
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; };	// ����
	D3DXVECTOR3 GetPos(void) { return m_pos; };		// �ʒu���
	float GetHeight(D3DXVECTOR3 pos);				// �������擾
	D3DXVECTOR3 GetNormal(D3DXVECTOR3 pos);			// �@�����̎擾
	void MoveY(D3DXVECTOR3 pos);					// ������ς���
	void Save(void);								// �Z�[�u
	void Load(void);								// ���[�h
	void SetCaldera(float size);					// ���ڂ݂̑傫����ݒ�
private:
	static D3DXVECTOR3 VtxNor(D3DXVECTOR3 pos0, D3DXVECTOR3 pos1, D3DXVECTOR3 pos2);// �@���v�Z�p
	LPDIRECT3DTEXTURE9 m_pTexture = NULL;		// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff = NULL;	// �C���f�b�N�X�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 m_pos;		// �ʒu
	D3DXVECTOR3 m_rot;		// ����
	float m_caldera;		// ���ڂ݂̑傫��
	D3DXMATRIX m_mtxWorld;	// ���[���h�}�g���b�N�X
	float m_Sum;			// �v�Z�p
};

#endif