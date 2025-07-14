//=============================================================================
//
//	2D�\��������UI���� [etcUI.h]
// Author : ���X�ؑt��Y
//
//=============================================================================
#ifndef _ETCUI_H_//���̃}�N����`������Ă��Ȃ�������
#define _ETCUI_H_//2�d�C���N���[�h�h�~�̃}�N����`
#include "main.h"

// UI�̎��
typedef enum
{
	ETCUI_DASH=0,
	ETCUI_KEY,
	ETCUI_MASTER,
	ETCUI_MAX
}ETCUI;

// UI�̍\����
typedef struct
{
	D3DXVECTOR3 pos;	// �ʒu
	D3DXVECTOR3 move;	// ����
	float fWidth;		// ��
	float fHeight;		// ����
	int nType;			// �u���b�N�̃^�C�v
	bool bUse;			// �g�p���Ă��邩�ǂ���
}EtcUI;

// �e�N�X�`���̎��
static const char* ETCUI_TEXTURE[ETCUI_MAX] =
{
	"data\\texture\\dash00.png",		// �g
	"data\\texture\\naginata.png",		// �㓁
	"data\\texture\\heal.png",			// ��
};

// �v���g�^�C�v�錾
void InitEtcUI(void);
void UninitEtcUI(void);
void UpdateEtcUI();
void DrawEtcUI(void);
void SetEtcUI(int nType, D3DXVECTOR3 pos, float fHeight, float fWidth);
#endif