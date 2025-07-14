//=============================================================================
//
// ��ʓ_�ł̏��� [bloodflash.h]
// Author : Sasaki Soichiro
//
//=============================================================================

#ifndef _BLOODSFLASH_H_
#define _BLOODSFLASH_H_

#include "main.h"
#define DELTA (0.005f) //�ω���
#define MAX_BLOODALPHA (0.2f) // �����x�̍ő�

// ��ʓ_�ł̍\���̒�`
typedef struct
{
	D3DXCOLOR col;
	bool bPlus;
	bool bUse;
}BLOODFLASH;

// �v���g�^�C�v�錾
void InitBloodFlash(void);
void UninitBloodFlash(void);
void UpdateBloodFlash(void);
void DrawBloodFlash(void);

#endif 