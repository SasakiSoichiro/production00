//=============================================================================
//
//	パーティクル処理 [particle.h]
// Author : 佐々木奏一郎
//
//=============================================================================
#ifndef _PARTICLE__H_
#define _PARTICLE_H_
#include "main.h"
typedef enum
{
	PARTICLETYPE_1 = 0,
	PARTICLETYPE_2,
	PARTICLETYPE_MAX
}PARTICLETYPE;
//プロトタイプ宣言
void InitParticle(void);
void UninitParticle(void);
void UpdateParticle(void);
void DrawParticle(void);
void SetParticle(D3DXVECTOR3 pos,float fLengs, float fRadius, int nAngle,int nLife,PARTICLETYPE type);
#endif
