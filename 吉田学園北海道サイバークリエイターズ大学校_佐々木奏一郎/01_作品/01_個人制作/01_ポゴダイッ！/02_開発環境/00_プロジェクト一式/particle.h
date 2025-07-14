//=============================================================================
//
//	�p�[�e�B�N������ [particle.h]
// Author : ���X�ؑt��Y
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
//�v���g�^�C�v�錾
void InitParticle(void);
void UninitParticle(void);
void UpdateParticle(void);
void DrawParticle(void);
void SetParticle(D3DXVECTOR3 pos,float fLengs, float fRadius, int nAngle,int nLife,PARTICLETYPE type);
#endif
