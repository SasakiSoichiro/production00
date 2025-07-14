//=============================================================================
//
// 粒子の処理 [Particle.h]
// Author : yabuki yukito
//
//=============================================================================

#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#include "main.h"

typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 move;
	D3DXCOLOR col;
	int nLife;
	bool bUse;
}Particle;

//プロトタイプ
void InitParticle(void);
void UninitParticle(void);
void UpdateParticle(void);
void DrawParticle(void);
void SetParticle(D3DXVECTOR3 pos,D3DXVECTOR3 move, D3DXCOLOR col, int nLife);

#endif