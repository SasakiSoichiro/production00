//=============================================================================
//
//	���b�V���t�B�[���h���� [Meshfield.h]
// Author:Sasaki Soichiro
//
//=============================================================================
#ifndef _MESHFIELD_H_// ���̃}�N����`������Ă��Ȃ�������
#define _MESHFIELD_H_// 2�d�C���N���[�h�h�~�̃}�N����`
#include "main.h"
#include "object.h"
#include <fstream>
#include <vector>
#define OBJ_X (600.0f)
#define OBJ_Z (600.0f)
#define XMESH (100)
#define ZMESH (100)
#define VTXCNT ((XMESH+1)*(ZMESH+1))
#define POLYCNT ((2*XMESH*ZMESH)+4*(ZMESH-1))
#define IDXCNT (((XMESH+1)*2*ZMESH)+(ZMESH-1)*4)

class CMesh :public CObject
{
public:
	CMesh(int nPriority=3);	// �R���X�g���N�^
	~CMesh();
	static CMesh* Create(D3DXVECTOR3 pos);
	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; };	// �ʒu
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; };	// ����
	D3DXVECTOR3 GetPos(void) { return m_pos; };		// �ʒu���
	float GetHeight(D3DXVECTOR3 pos);
	D3DXVECTOR3 GetNormal(D3DXVECTOR3 pos);
	void MoveY(D3DXVECTOR3 pos);
	void Save(const std::vector<int>& nNum,const std::string& FileName);
	void Load(void);
private:
	static D3DXVECTOR3 VtxNor(D3DXVECTOR3 pos0, D3DXVECTOR3 pos1, D3DXVECTOR3 pos2);// �@���v�Z�p
	LPDIRECT3DTEXTURE9 m_pTexture = NULL;		// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff = NULL;	// �C���f�b�N�X�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 m_pos;		// �ʒu
	D3DXVECTOR3 m_rot;		// ����
	D3DXMATRIX m_mtxWorld;	// ���[���h�}�g���b�N�X
};

#endif