//======================================================
//
//		ƒ‰ƒCƒg  light.cpp
//		ryuusei hirata
//
//======================================================
#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "main.h"

#define MAX_LIGHT (3)

typedef enum
{
	TYPE_NORMAL = 0,
	TYPE_POINT,
	TYPE_MAX
}LIGHTTYPE;

void InitLight(void);
void UninitLight(void);
void UpdateLight(void);
void SetupPointLight(D3DXVECTOR3 pos);

#endif // !_LIGHT_H_
