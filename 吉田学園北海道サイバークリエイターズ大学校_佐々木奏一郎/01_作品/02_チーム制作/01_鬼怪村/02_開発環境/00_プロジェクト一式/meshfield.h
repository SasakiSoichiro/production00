//=============================================================================
//
//	���b�V���t�B�[���h���� [Meshfield.h]
// Author : ���X�ؑt��Y
//
//=============================================================================
#ifndef _MESHFIELD_H_//���̃}�N����`������Ă��Ȃ�������
#define _MESHFIELD_H_//2�e�C���N���[�h�h�~�̃}�N����`

#include "main.h"

#define OBJ_X (1850.0f)
#define OBJ_Z (850.0f)
#define XMESH (20)
#define ZMESH (20)
//#define VTXCNT ((XMESH+1)*(ZMESH+1))
//#define POLYCNT ((2*XMESH*ZMESH)+4*(ZMESH-1))
//#define IDXCNT (((XMESH+1)*2*ZMESH)+(ZMESH-1)*4)

//�v���g�^�C�v�錾
void InitMeshfield(void);
void UninitMeshfield(void);
void UpdateMeshfield(void);
void DrawMeshfield(void);

#endif