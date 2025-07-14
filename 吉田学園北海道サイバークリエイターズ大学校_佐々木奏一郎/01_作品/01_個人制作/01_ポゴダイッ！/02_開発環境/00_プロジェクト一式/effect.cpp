//=============================================================================
//
//	�G�t�F�N�g���� [effect.cpp]
// Author : ���X�ؑt��Y
//
//=============================================================================
#include "effect.h"
#include "main.h"
#include "input.h"
#include "player.h"
//�}�N����`
#define MAX_EFFECT (4096)//�G�t�F�N�g�̍ő吔
#define MAX_SPEED (5)//�e�̑���
//�e�\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;//�ʒu
	D3DXVECTOR3 move;
	D3DXCOLOR col;//�F
	float fRadius;//���a
	int nLife;//����
	EFFECTTYPE type;//���
	float fAlpha;
	bool bUse;//�g�p���Ă��邩�ǂ���
}Effect;
//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureEffect = NULL;//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEffect = NULL;//���_�o�b�t�@�ւ̃|�C���^
Effect g_aEffect[MAX_EFFECT];//�G�t�F�N�g�̏��

//�e�̏���������
void InitEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntEffect;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\effect000.jpg",
		&g_pTextureEffect);
	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		g_aEffect[nCntEffect].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEffect[nCntEffect].col = D3DXCOLOR(0.0f,0.0f, 0.0f, 0.0f);
		g_aEffect[nCntEffect].fRadius = 0.0f;
		g_aEffect[nCntEffect].nLife = NULL;
		g_aEffect[nCntEffect].move= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEffect[nCntEffect].fAlpha = 1.0f;
		g_aEffect[nCntEffect].type = EFFECTTYPE_PLAYER;
		g_aEffect[nCntEffect].bUse = false;
	}
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_EFFECT,//(sizeof(VERTEX_2D)*�K�v�Ȓ��_��
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEffect,
		NULL);
	VERTEX_2D* pVtx =0;
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x - 40, g_aEffect[nCntEffect].pos.y - 40, 0.0f);//���E���Őݒ肷��
		pVtx[1].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x + 40, g_aEffect[nCntEffect].pos.y - 40, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x - 40, g_aEffect[nCntEffect].pos.y + 40, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x + 40, g_aEffect[nCntEffect].pos.y + 40, 0.0f);
		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		//���_�J���[�̐ݒ�@�@�@�@
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f,0.0f);//���E���Őݒ肷��
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx += 4;//���_�f�[�^�̃|�C���^��4���W�߂�
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEffect->Unlock();
}
void UninitEffect(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureEffect != NULL)
	{
		g_pTextureEffect->Release();
		g_pTextureEffect = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffEffect != NULL)
	{
		g_pVtxBuffEffect->Release();
		g_pVtxBuffEffect = NULL;
	}
}
void UpdateEffect(void)
{
	VERTEX_2D* pVtx = 0;
	int nCntEffect;
	int nSize=40;
	float fAlpha[MAX_EFFECT] = {};
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_aEffect[nCntEffect].bUse == true)
		{//�e���g�p����Ă���
			switch (g_aEffect[nCntEffect].type)
			{
			case EFFECTTYPE_PLAYER:
				//���_�J���[�̐ݒ�
				pVtx[0].col = D3DXCOLOR(g_aEffect[nCntEffect].col.r, g_aEffect[nCntEffect].col.g,g_aEffect[nCntEffect].fAlpha, g_aEffect[nCntEffect].fAlpha);
				pVtx[1].col = D3DXCOLOR(g_aEffect[nCntEffect].col.r, g_aEffect[nCntEffect].col.g,g_aEffect[nCntEffect].fAlpha, g_aEffect[nCntEffect].fAlpha);
				pVtx[2].col = D3DXCOLOR(g_aEffect[nCntEffect].col.r, g_aEffect[nCntEffect].col.g,g_aEffect[nCntEffect].fAlpha, g_aEffect[nCntEffect].fAlpha);
				pVtx[3].col = D3DXCOLOR(g_aEffect[nCntEffect].col.r, g_aEffect[nCntEffect].col.g,g_aEffect[nCntEffect].fAlpha, g_aEffect[nCntEffect].fAlpha);
				break;
			case EFFECTTYPE_ENEMY:
				//���_�J���[�̐ݒ�
				pVtx[0].col = D3DXCOLOR(g_aEffect[nCntEffect].col.r, g_aEffect[nCntEffect].fAlpha, g_aEffect[nCntEffect].col.b, g_aEffect[nCntEffect].fAlpha);
				pVtx[1].col = D3DXCOLOR(g_aEffect[nCntEffect].col.r, g_aEffect[nCntEffect].fAlpha, g_aEffect[nCntEffect].col.b, g_aEffect[nCntEffect].fAlpha);
				pVtx[2].col = D3DXCOLOR(g_aEffect[nCntEffect].col.r, g_aEffect[nCntEffect].fAlpha, g_aEffect[nCntEffect].col.b, g_aEffect[nCntEffect].fAlpha);
				pVtx[3].col = D3DXCOLOR(g_aEffect[nCntEffect].col.r, g_aEffect[nCntEffect].fAlpha, g_aEffect[nCntEffect].col.b, g_aEffect[nCntEffect].fAlpha);
				break;
			case EFFECTTYPE_PARTICLE1:
				//���_�J���[�̐ݒ�
				pVtx[0].col = D3DXCOLOR(g_aEffect[nCntEffect].nLife* g_aEffect[nCntEffect].col.r/30.0f, g_aEffect[nCntEffect].col.g, g_aEffect[nCntEffect].col.b, g_aEffect[nCntEffect].fAlpha);
				pVtx[1].col = D3DXCOLOR(g_aEffect[nCntEffect].nLife* g_aEffect[nCntEffect].col.r/30.0f, g_aEffect[nCntEffect].col.g, g_aEffect[nCntEffect].col.b, g_aEffect[nCntEffect].fAlpha);
				pVtx[2].col = D3DXCOLOR(g_aEffect[nCntEffect].nLife* g_aEffect[nCntEffect].col.r/30.0f, g_aEffect[nCntEffect].col.g, g_aEffect[nCntEffect].col.b, g_aEffect[nCntEffect].fAlpha);
				pVtx[3].col = D3DXCOLOR(g_aEffect[nCntEffect].nLife* g_aEffect[nCntEffect].col.r/30.0f, g_aEffect[nCntEffect].col.g, g_aEffect[nCntEffect].col.b, g_aEffect[nCntEffect].fAlpha);
				break;
			case EFFECTTYPE_PARTICLE2:
				//���_�J���[�̐ݒ�
				pVtx[0].col = D3DXCOLOR(g_aEffect[nCntEffect].col.r, g_aEffect[nCntEffect].fAlpha,g_aEffect[nCntEffect].fAlpha, g_aEffect[nCntEffect].fAlpha);
				pVtx[1].col = D3DXCOLOR(g_aEffect[nCntEffect].col.r, g_aEffect[nCntEffect].fAlpha,g_aEffect[nCntEffect].fAlpha, g_aEffect[nCntEffect].fAlpha);
				pVtx[2].col = D3DXCOLOR(g_aEffect[nCntEffect].col.r, g_aEffect[nCntEffect].fAlpha,g_aEffect[nCntEffect].fAlpha, g_aEffect[nCntEffect].fAlpha);
				pVtx[3].col = D3DXCOLOR(g_aEffect[nCntEffect].col.r, g_aEffect[nCntEffect].fAlpha,g_aEffect[nCntEffect].fAlpha, g_aEffect[nCntEffect].fAlpha);
				break;
			}
			//�ʒu�̍X�V
			g_aEffect[nCntEffect].pos.x+= g_aEffect[nCntEffect].move.x;
			g_aEffect[nCntEffect].pos.y+= g_aEffect[nCntEffect].move.y;
			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x - g_aEffect[nCntEffect].fRadius, g_aEffect[nCntEffect].pos.y - g_aEffect[nCntEffect].fRadius, 0.0f);//���E���Őݒ肷��
			pVtx[1].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x + g_aEffect[nCntEffect].fRadius, g_aEffect[nCntEffect].pos.y - g_aEffect[nCntEffect].fRadius, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x - g_aEffect[nCntEffect].fRadius, g_aEffect[nCntEffect].pos.y + g_aEffect[nCntEffect].fRadius, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x + g_aEffect[nCntEffect].fRadius, g_aEffect[nCntEffect].pos.y + g_aEffect[nCntEffect].fRadius, 0.0f);
	
			g_aEffect[nCntEffect].nLife--;
			g_aEffect[nCntEffect].fAlpha -= 0.025;
			g_aEffect[nCntEffect].fRadius -= 0.3;
			if (g_aEffect[nCntEffect].pos.x >=SCREEN_WIDTH|| g_aEffect[nCntEffect].pos.x<=0|| g_aEffect[nCntEffect].pos.y>=SCREEN_HEIGHT|| g_aEffect[nCntEffect].pos.y<=0)
			{
				g_aEffect[nCntEffect].bUse = false;
			}
			if (g_aEffect[nCntEffect].nLife<=0)
			{
				g_aEffect[nCntEffect].bUse = false;
			}
			
		}
		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEffect->Unlock();
}
void DrawEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^
	int nCntEffect;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();
	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffEffect, 0, sizeof(VERTEX_2D));
	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	//���u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_aEffect[nCntEffect].bUse == true)
		{//�e���g�p����Ă���
				//�|���S���̕`��
			pDevice->SetTexture(0, g_pTextureEffect);
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4*nCntEffect, 2);
		}
	}
	//���u�����f�B���O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

void SetEffect(D3DXVECTOR3 pos, D3DXVECTOR3 move,D3DXCOLOR col, float fRadius, int nLife,EFFECTTYPE type)
{
	VERTEX_2D* pVtx=0;
	int nCntEffect;
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_aEffect[nCntEffect].bUse == false)
		{//�e���g�p����Ă��Ȃ�
			g_aEffect[nCntEffect].pos = pos;
			g_aEffect[nCntEffect].col = col;
			g_aEffect[nCntEffect].fRadius = fRadius;
			g_aEffect[nCntEffect].nLife =nLife;
			g_aEffect[nCntEffect].move = move;
			g_aEffect[nCntEffect].type = type;
			g_aEffect[nCntEffect].fAlpha = 1.0f;
			g_aEffect[nCntEffect].bUse = true;//�g�p���Ă����Ԃɂ���
		
			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x - 40, g_aEffect[nCntEffect].pos.y - 40, 0.0f);//���E���Őݒ肷��
			pVtx[1].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x + 40, g_aEffect[nCntEffect].pos.y - 40, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x - 40, g_aEffect[nCntEffect].pos.y + 40, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x + 40, g_aEffect[nCntEffect].pos.y + 40, 0.0f);
	
			break;
		}
		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEffect->Unlock();
}