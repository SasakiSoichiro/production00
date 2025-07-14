//=============================================================================
//
//	�M�~�b�N���� [gimmick.h]
// author chikada shouya
//
//=============================================================================

#ifndef _GIMMICK_H_
#define _GIMMICK_H_


#include "main.h"
#include "player.h"

#define MAX_DOOR (2)				//�h�A�̍ő吔

//�u���b�N�̍\����
typedef struct
{
	D3DXVECTOR3 pos;				// �ʒu
	D3DXVECTOR3 rot;				// ����
	D3DXVECTOR3 move;				// �ړ�
	D3DXVECTOR3 size;				// �T�C�Y
	D3DXVECTOR3 vtxMin, vtxMax;		// ���_�̍ŏ��ő�
	D3DXMATRIX mtxWorld;			// �}�g���b�N�X
	LPD3DXMESH pMesh;				   
	LPD3DXBUFFER pBuffMat;
	DWORD dwNumMat;
	bool bLanding;
	bool bUse;
	//bool bGoal;
	bool bMove;
}GIMMICK;

// �\����
typedef struct
{
	int nHoldCount;
	int NoTouch;
	int HolTime;
	int count;
	bool bClear;
	bool bPush;
	bool bNoPush;
}HOLD;

// �v���g�^�C�v�錾
void InitGimmick(void);
void UninitGimmick(void);
void UpdateGimmick(void);
void DrawGimmick(void);
void CollisionGimmick(D3DXVECTOR3* pPos,D3DXVECTOR3* pPosOld);
void SetGimmick(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
GIMMICK* GetGimmick(void);
bool IsGoal();
bool IsBill();
void IsHold(void);
HOLD* GetHold(void);

#endif