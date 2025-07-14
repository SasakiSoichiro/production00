//=============================================================================
//
//	�u���b�N���� [Block.h]
// Author : ���X�ؑt��Y
//
//=============================================================================
#ifndef _BLOCK_H_//���̃}�N����`������Ă��Ȃ�������
#define _BLOCK_H_//2�d�C���N���[�h�h�~�̃}�N����`
#include "main.h"

//�}�N����`
#define MAX_BLOCKHEIGHT (40.0f)		//�m�[�}���u���b�N�̃e�N�X�`���̍���
#define MAX_BLOCKWIDTH (40.0f)		//�m�[�}���u���b�N�̃e�N�X�`���̕�
#define MAX_BUTTONHEIGHT (10.0f)	//�{�^���u���b�N�̍���
#define MAX_WALLWIDTH (10.0f)		//�ǃu���b�N�̕�
#define MAX_BLOCK (128)				//�u���b�N�̍ő吔
#define MAX_NUMBLOCK (8)			//�u���b�N�̎��
#define MAX_MOVE (1.0f)				//��������

typedef enum
{
	BLOCK_NORMAL = 0,
	BLOCK_BUTTON,
	BLOCK_MOVEWALL,
	BLOCK_SLIME,
	BLOCK_TRANPORIN,
	BLOCK_GOAL,
	BLOCK_LR,
	BLOCK_UPDOWN,
	BLOCK_MAX
}BLOCK;

typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 move;	//����
	float fWidth;		//��
	float fHeight;		//����
	int nType;			//�u���b�N�̃^�C�v
	bool bUse;			//�g�p���Ă��邩�ǂ���
}Block;

static const char* BLOCK_TEXTURE[BLOCK_MAX] =
{
	"data\\TEXTURE\\block000.png",		//�u���b�N
	"data\\TEXTURE\\button000.png",		//�{�^��
	"data\\TEXTURE\\door001.png",		//������
	"data\\TEXTURE\\suraimu000.png",	//�X���C��
	"data\\TEXTURE\\kinoko000.png",		//�g�����|����
	"data\\TEXTURE\\goal000.png",		//�S�[��
	"data\\TEXTURE\\LR000.png",			//����
	"data\\TEXTURE\\UpDown000.png"		//�g�����|����
};

//�v���g�^�C�v�錾
void InitBlock(void);
void UninitBlock(void);
void UpdateBlock(void);
void DrawBlock(void);
void SetBlock(D3DXVECTOR3 pos,float fWidth,float fHeight,int nType);
bool CollisionBlock(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3* pPYPos, D3DXVECTOR3* pPYPosOld, D3DXVECTOR3* pMove, float fWidth, float fHeight,Block**pBlock);
bool GetGoal(void);
bool GetButton(void);

#endif