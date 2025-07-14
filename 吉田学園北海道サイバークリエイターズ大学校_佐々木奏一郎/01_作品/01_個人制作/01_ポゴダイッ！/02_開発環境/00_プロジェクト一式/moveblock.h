//=============================================================================
//
//	���[�u�u���b�N���� [moveblock.h]
// Author : ���X�ؑt��Y
//
//=============================================================================
#ifndef _MOVEBLOCK_H_//���̃}�N����`������Ă��Ȃ�������
#define _MOVEBLOCK_H_//2�d�C���N���[�h�h�~�̃}�N����`
#include "main.h"
#define MAX_BLOCKHEIGHT (20.0f)
#define MAX_BLOCKWIDTH (20.0f)
#define MAX_BUTTONHEIGHT (10.0f)
#define MAX_WALLWIDTH (10.0f)


//���[�u�u���b�N�̏��
typedef enum
{
	BLOCK_BEFORE = 0,
	BLOCK_MOVE,
	BLOCK_AFTER,
	BLOCK_MOVEMAX
}MOVEBLOCK;

typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	float fWidth;		//��
	float fHeight;		//����
	int nType;			//�u���b�N�̃^�C�v
	bool bUse;			//�g�p���Ă��邩�ǂ���
}MoveBlock;

static const char* MOVEBLOCK_TEXTURE[BLOCK_MOVEMAX] =
{
	"data\\TEXTURE\\surinuke000.png",		//���O
	"data\\TEXTURE\\surinuke001.png",		//�����Ă�Ƃ�
	"data\\TEXTURE\\surinuke002.png",		//�g��������
};

//�v���g�^�C�v�錾
void InitMoveBlock(void);
void UninitMoveBlock(void);
void UpdateMoveBlock(void);
void DrawMoveBlock(void);
void SetMoveBlock(D3DXVECTOR3 pos, float fWidth, float fHeight, int nType);
bool CollisionMoveBlock(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3* pPYPos, D3DXVECTOR3* pPYPosOld, D3DXVECTOR3* pMove, float fWidth, float fHeight);
#endif