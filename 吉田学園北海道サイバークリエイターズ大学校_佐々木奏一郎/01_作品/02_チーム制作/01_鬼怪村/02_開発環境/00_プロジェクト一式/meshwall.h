//=============================================================================
//
//	���b�V���E�H�[������ [meshwall.h]
// Author : ���X�ؑt��Y
//
//=============================================================================
#ifndef _MESHWALL_H_//���̃}�N����`������Ă��Ȃ�������
#define _MESHWALL_H_//2�e�C���N���[�h�h�~�̃}�N����`
#include "main.h"
#define OBJ_V (250.0f)
#define OBJ_H (400.0f)
#define VMESH (30)
#define HMESH (30)
#define VTXCNT ((VMESH+1)*(HMESH+1))
#define POLYCNT ((2*VMESH*HMESH)+4*(VMESH-1))
#define IDXCNT (((VMESH+1)*2*HMESH)+(HMESH-1)*4)
#define RADIUS (1000)
//#define IDXCNT (POLYCNT+2)



typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXVECTOR3 VtxPos[VTXCNT];
	D3DXMATRIX mtxWorld;
}MeshWall;
//�v���g�^�C�v�錾
void InitMeshWall(void);
void UninitMeshWall(void);
void UpdateMeshWall(void);
void DrawMeshWall(void);
void CollisionCyrynder(void);

#endif