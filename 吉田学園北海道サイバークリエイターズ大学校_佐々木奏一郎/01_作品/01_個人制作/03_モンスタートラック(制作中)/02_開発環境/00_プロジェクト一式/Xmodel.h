//*****************************************
// 
// X�t�@�C������ [Xmodel.h]
// Author:Sasaki Soichiro
//
//*****************************************
#ifndef _XMODEL_H_	// ���̃}�N����`������Ă��Ȃ�������
#define _XMODEL_H_	// ��d�C���N���[�h�h�~�̃}�N����`
//***************
// �C���N���[�h
//***************
#include "main.h"
#include <string>

//***********************
// X�t�@�C���̊Ǘ��N���X
//***********************
class CXModel
{
public:
	// X�t�@�C���̍\����
	typedef struct
	{
		LPD3DXMESH pMesh;		// ���b�V���ւ̃|�C���^
		LPD3DXBUFFER pBuffMat;	// �o�b�t�@�ւ̃|�C���^
		DWORD dwNumMat;
		D3DXVECTOR3 vtxMin, vtxMax;// �傫��
	}XMODEL;
	// ���
	typedef enum
	{
		TYPE_PLAYER = 0,
		TYPE_MAX
	}TYPE;
	CXModel();	// �R���X�g���N�^
	~CXModel();	// �f�X�g���N�^
	HRESULT Load(void);	// �ǂݍ���
	void Unload(void);	// �j��
	int Register(const char* pFilename);	// X�t�@�C���̓o�^
	XMODEL GetAddres(int nIdx);				// X�t�@�C���̃C���f�b�N�X
private:
	XMODEL m_apXModel[256];	// X�t�@�C���ւ̃|�C���^
	static int m_nNumAll;	// �ő吔
	// X�t�@�C���̃t�@�C����
	std::string XFILE[256] =
	{
		"data\\MODEL\\aa.x",
	};
};



#endif