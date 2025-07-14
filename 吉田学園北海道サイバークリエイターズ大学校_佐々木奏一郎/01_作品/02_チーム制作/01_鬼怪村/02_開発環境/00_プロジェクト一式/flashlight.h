//=============================================================================
//
//		�����d��  flashlight.cpp
//		Auther:Sasaki Soichiro
//
//=============================================================================

#ifndef _FLASHLIGHT_H_
#define _FLASHLIGHT_H_

#include "main.h"

// �}�N����`
#define MAX_FLASH (1)

// �����d���̍\����
typedef struct
{
	D3DLIGHT9 light;	//	���C�g���
	bool bLight;
}FLASHLIGHT;

// �v���g�^�C�v�錾
void InitFlashLight(void);
void UninitFlashLight(void);
void UpdateFlashLight(void);
FLASHLIGHT* GetFlashLight(void);
void InitFlashGlobal(int nCnt);
void bFlashTRUE(int nCnt);
void bFlashFALSE(int nCnt);

#endif // !_LIGHT_H_