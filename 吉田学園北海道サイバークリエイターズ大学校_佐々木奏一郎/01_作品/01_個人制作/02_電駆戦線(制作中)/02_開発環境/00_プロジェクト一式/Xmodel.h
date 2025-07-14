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
class CXModel
{
public:
	//*******************
	// X�t�@�C���̍\����
	//*******************
	typedef struct
	{
		LPD3DXMESH pMesh;
		LPD3DXBUFFER pBuffMat;
		DWORD dwNumMat;
	}XMODEL;
	typedef enum
	{
		TYPE_PLAYER = 0,
		TYPE_MAX
	}TYPE;
	CXModel();	// �R���X�g���N�^
	~CXModel();	// �f�X�g���N�^
	HRESULT Load(void);	// ���[�h
	void Unload(void);	// �A�����[�h
	int Register(const char* pFilename);	// X�t�@�C���̓o�^
	XMODEL GetAddres(int nIdx);				// X�t�@�C���̃C���f�b�N�X
private:
	XMODEL m_apXModel[256];
	static int m_nNumAll;
	const char* XFILE[256] =
	{
		"data\\MODEL\\aa.x",
	};
};



#endif