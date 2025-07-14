//=============================================================================
//
// ��ʓ_�ł̏��� [BloodSplatter.cpp]
// Author : Sasaki Soichiro
//
//=============================================================================

#include "BloodFlash.h"
#include "player.h"

// �O���[�o���ϐ�

// ���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBloodFlash = NULL;

BLOODFLASH g_BloodFlash;

int g_nCntBloodState;

//====================
//	����������
//====================
void InitBloodFlash(void)
{
	//�O���[�o���ϐ�������
	g_BloodFlash.col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.3f);
	g_BloodFlash.bPlus = false;
	g_BloodFlash.bUse = false;
	g_nCntBloodState = 0;

	// �f�o�C�X���̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBloodFlash,
		NULL);

	VERTEX_2D* pVtx;

	// ���b�N
	g_pVtxBuffBloodFlash->Lock(0, 0, (void**)&pVtx, 0);

		// ���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);

		// rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// tex���W
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		// ���_�J���[
		pVtx[0].col = D3DXCOLOR(g_BloodFlash.col);
		pVtx[1].col = D3DXCOLOR(g_BloodFlash.col);
		pVtx[2].col = D3DXCOLOR(g_BloodFlash.col);
		pVtx[3].col = D3DXCOLOR(g_BloodFlash.col);

	// �A�����b�N
	g_pVtxBuffBloodFlash->Unlock();
}

//====================
//	�I������
//====================
void UninitBloodFlash(void)
{

	// ���_�o�b�t�@�̉��
	if (g_pVtxBuffBloodFlash != NULL)
	{
		g_pVtxBuffBloodFlash->Release();
		g_pVtxBuffBloodFlash = NULL;
	}
}

//====================
//	�X�V����
//====================
void UpdateBloodFlash(void)
{
	// ���[�J���ϐ��錾
	Player* pPlayer = GetPlayer();
	VERTEX_2D* pVtx;
	if (pPlayer->nLife == 1)
	{
		g_BloodFlash.bUse = true;
		if (g_BloodFlash.bPlus == true)
		{
			g_BloodFlash.col.a += DELTA;
			if (g_BloodFlash.col.a >= MAX_BLOODALPHA)
			{
				g_BloodFlash.bPlus = false;
			}
		}
		else
		{
			g_BloodFlash.col.a -= DELTA;
			if (g_BloodFlash.col.a <= 0.0f)
			{
				g_BloodFlash.bPlus = true;
			}
		}

		// ���b�N
		g_pVtxBuffBloodFlash->Lock(0, 0, (void**)&pVtx, 0);

		// ���_�J���[
		pVtx[0].col = D3DXCOLOR(g_BloodFlash.col);
		pVtx[1].col = D3DXCOLOR(g_BloodFlash.col);
		pVtx[2].col = D3DXCOLOR(g_BloodFlash.col);
		pVtx[3].col = D3DXCOLOR(g_BloodFlash.col);

		// �A�����b�N
		g_pVtxBuffBloodFlash->Unlock();
	}
	else
	{
		g_BloodFlash.bUse = false;
	}

}

//====================
//	�`�揈��
//====================
void DrawBloodFlash(void)
{
	// �f�o�C�X�ւ̃|�C���^�A��Ԏ擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	Player* pPlayer = GetPlayer();

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffBloodFlash, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	if (g_BloodFlash.bUse == true)
	{// �g���Ă���ꍇ

		// �|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}


}