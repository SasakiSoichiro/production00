//=============================================================================
//
//    �^�C�g������ [title.h]
//    Author : ryuusei.hirata
//
//=============================================================================
#ifndef _TITLE_H_
#define _TITLE_H_

#include "main.h"
#include "input.h"
#include "game.h"

typedef enum
{
	TITLE_ONE = 0,
	TITLE_TWO,
	TITLE_THREE,
	TITLE_MAX
}TITLE;

// ��
typedef enum
{
	TITLEMODE_NONE = 0,
	TITLEMODE_FLASH,
	TITLEMODE_MAX
}TITLEMODE;

// �\����
typedef struct
{
	D3DXVECTOR3 pos;	// ���W
	D3DXVECTOR3 col;	// �J���[
	int nType;			// ���
	bool bUse;			// �g���Ă邩
	float fHeight;		// ����
	float fWidth;		// ��
	TITLEMODE state;	// ���
}Title;

// �v���g�^�C�v
void InitTitle(void);
void UninitTitle(void);
void UpdateTitle(void);
void DrawTitle(void);
void SetTitle(int nType, D3DXVECTOR3 pos);

#endif // !_TITLE_H_
