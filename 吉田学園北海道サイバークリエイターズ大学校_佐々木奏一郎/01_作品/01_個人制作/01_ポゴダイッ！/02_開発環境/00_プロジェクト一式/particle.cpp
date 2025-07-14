//=============================================================================
//
//	�p�[�e�B�N������ [particle.cpp]
// Author : ���X�ؑt��Y
//
//=============================================================================
#include "particle.h"
#include "effect.h"
#define MAX_PARTICLE (128)//�p�[�e�B�N���̍ő吔
//�p�[�e�B�N���\����
typedef struct
{
	D3DXVECTOR3 pos;//�ʒu
	int nLife;//����
	float fLengs;//�ړ�����
	float fRadius;//���a
	int nAngle;
	PARTICLETYPE type;
	bool bUse;//�g�p���Ă��邩�ǂ���
}Particle;
//�O���[�o���ϐ�
Particle g_aParticle[MAX_PARTICLE];//�p�[�e�B�N���̏��
void InitParticle(void)
{
	int nCnt;
	for (nCnt = 0; nCnt < MAX_PARTICLE; nCnt++)
	{
		g_aParticle[nCnt].pos = g_aParticle[nCnt].pos;
		g_aParticle[nCnt].nLife = 0;
		g_aParticle[nCnt].fLengs =0.0f;
		g_aParticle[nCnt].fRadius =0.0f;
		g_aParticle[nCnt].nAngle = 0;
		g_aParticle[nCnt].bUse = false;
	}
}
void UninitParticle(void)
{

}
void UpdateParticle(void)
{
	int nCnt;
	D3DXVECTOR3 pos,move;
	int nLife, nAngleS;
	float fAngle,fLengs,fLengsS,fRadius;

	for (nCnt = 0; nCnt < MAX_PARTICLE; nCnt++)
	{
		if (g_aParticle[nCnt].bUse == true)
		{
			//�p�[�e�B�N���̐���
			for (int nCntAppear = 0; nCntAppear <5; nCntAppear++)
			{
				pos = g_aParticle[nCnt].pos;
				nAngleS = g_aParticle[nCnt].nAngle;
				fLengsS = g_aParticle[nCnt].fLengs;
				fRadius = g_aParticle[nCnt].fRadius;
				fAngle = (float)(rand() % nAngleS - 314) / 100.0f;
				fLengs = (float)(rand() % 10) /  fLengsS+ 10.0f;
				move.x = sinf(fAngle) * fLengs;
				move.y = cosf(fAngle) *fLengs;
				g_aParticle[nCnt].nLife--;
				nLife = g_aParticle[nCnt].nLife;
				switch (g_aParticle[nCnt].type)
				{
				case PARTICLETYPE_1:
					SetEffect(pos, D3DXVECTOR3(move.x, move.y, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), fRadius, nLife, EFFECTTYPE_PARTICLE1);
					break;
				case PARTICLETYPE_2:
					SetEffect(pos, D3DXVECTOR3(move.x, move.y, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), fRadius, nLife, EFFECTTYPE_PARTICLE2);
					break;

				}
				
			}
			if (g_aParticle[nCnt].nLife <= 0)
			{
				g_aParticle[nCnt].bUse = false;
			}
		}
	}
}
void DrawParticle(void)
{

}
void SetParticle(D3DXVECTOR3 pos,float fLengs,float fRadius,int nAngle,int nLife, PARTICLETYPE type)
{
	for (int nCnt = 0; nCnt < MAX_PARTICLE; nCnt++)
	{
		if (g_aParticle[nCnt].bUse == false)
		{
			g_aParticle[nCnt].pos = pos;
			g_aParticle[nCnt].nLife = nLife;
			g_aParticle[nCnt].fLengs = fLengs;
			g_aParticle[nCnt].fRadius =fRadius;
			g_aParticle[nCnt].nAngle = nAngle;
			g_aParticle[nCnt].type = type;
			g_aParticle[nCnt].bUse = true;
			break;
		}
	
	}
}