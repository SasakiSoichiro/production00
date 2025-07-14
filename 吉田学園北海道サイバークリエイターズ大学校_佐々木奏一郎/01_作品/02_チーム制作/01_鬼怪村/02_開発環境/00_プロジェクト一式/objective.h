//=============================================================================
//
//	�A�C�e�����̏��� [objective.h]
// Author : ���X�ؑt��Y
//
//=============================================================================
#ifndef _OBJECTIVE_H_//���̃}�N����`������Ă��Ȃ�������
#define _OBJECTIVE_H_//2�d�C���N���[�h�h�~�̃}�N����`
#include "main.h"

typedef enum
{
	OBJECTIVETYPE_OBJECTIVE = 0,	//�ړI
	OBJECTIVETYPE_WAKU1,			//�g
	OBJECTIVETYPE_WAKU2,			//�g
	OBJECTIVETYPE_CHECK,			//�`�F�b�N
	OBJECTIVETYPE_TEXT1,			//�~�b�V����1
	OBJECTIVETYPE_TEXT2,			//�~�b�V����2
	OBJECTIVETYPE_MAX
}OBJECTIVETYPE;

typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu
	D3DXVECTOR3 move;		//����
	float fWidth;			//��
	float fHeight;			//����
	OBJECTIVETYPE nType;	//�u���b�N�̃^�C�v
	bool bUse;				//�g�p���Ă��邩�ǂ���
	bool bText;				//�e�L�X�g�̎g�p�m�F
}OBJECTIVE;

static const char* OBJECTIVE_TEXTURE[OBJECTIVETYPE_MAX] =
{
	"data\\texture\\objective1.png",		//�ړI
	"data\\texture\\waku3.png",			//�g
	"data\\texture\\waku3.png",			//�g
	"data\\texture\\check.png",			//�`�F�b�N
	"data\\texture\\text1.png",			//�~�b�V����1
	"data\\texture\\text2.png",			//�~�b�V����2
};

//�v���g�^�C�v�錾
void InitObjective(void);
void UninitObjective(void);
void UpdateObjective(void);
void DrawObjective(void);
void SetObjective(D3DXVECTOR3 pos,float fWidth,float fHeight,OBJECTIVETYPE nType);
OBJECTIVE* GetObjective();
#endif