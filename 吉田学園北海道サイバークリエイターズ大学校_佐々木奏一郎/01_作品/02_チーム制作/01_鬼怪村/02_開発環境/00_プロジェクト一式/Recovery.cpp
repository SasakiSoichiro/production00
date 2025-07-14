//=============================================================================
//
// �񕜂̏��� [Recovery.cpp]
// Author : Hirata ryuusei
//
//=============================================================================
#include "Recovery.h"
#include "ui.h"
#include "player.h"
#include "sound.h"

// �O���[�o��
Recovery g_Recovery = {};

// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureRecovery = NULL;

// ���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRecovery = NULL;

//====================
//	����������
//====================
void InitRecovery(void)
{
	// �e�ϐ��̏�����
	g_Recovery.ui = Recovery_IN;							// �t�F�[�h�C�����
	g_Recovery.col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 0.2f);		// �J���[�̐ݒ�
	g_Recovery.count = 0;
	g_Recovery.bUse = false;

	// �f�o�C�X���̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRecovery,
		NULL);

	VERTEX_2D* pVtx;

	// ���b�N
	g_pVtxBuffRecovery->Lock(0, 0, (void**)&pVtx, 0);

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

	// ���_�J���[
	pVtx[0].col = D3DXCOLOR(g_Recovery.col);
	pVtx[1].col = D3DXCOLOR(g_Recovery.col);
	pVtx[2].col = D3DXCOLOR(g_Recovery.col);
	pVtx[3].col = D3DXCOLOR(g_Recovery.col);

	// �A�����b�N
	g_pVtxBuffRecovery->Unlock();
}

//====================
//	�I������
//====================
void UinitRecovery(void)
{
	// SE���~�߂�
	StopSound(SOUND_LABEL_SE2);

	// ���_�o�b�t�@�̉��
	if (g_pVtxBuffRecovery != NULL)
	{
		g_pVtxBuffRecovery->Release();
		g_pVtxBuffRecovery = NULL;
	}
}

//====================
//	�X�V����
//====================
void UpdateRecovery(void)
{
	if (g_Recovery.bUse == true)
	{
		// �f�N�������g
		g_Recovery.count--;

		if (g_Recovery.count <= 0 && g_Recovery.ui == Recovery_NONE)
		{
			g_Recovery.ui = Recovery_IN;	// �t�F�[�h�C�����
			g_Recovery.bUse = false;		// �\������Ă��Ȃ�������
			g_Recovery.count = 0;			// 0�ɂ���
		}
	}

	if (g_Recovery.ui != Recovery_NONE)
	{
		if (g_Recovery.ui == Recovery_IN)
		{
			// �t�F�[�h�C��
			g_Recovery.col.a -= 0.01f;				// �|���S���������ɂȂ鑬��
			if (g_Recovery.col.a <= 0.0f)
			{
				g_Recovery.col.a = 0.0f;
				g_Recovery.ui = Recovery_NONE;		// �������Ă��Ȃ����
			}
		}
		else if (g_Recovery.ui == Recovery_OUT)
		{
			// �t�F�[�h�A�E�g
			g_Recovery.col.a += 0.02f;

			if (g_Recovery.col.a >= 0.3f)
			{
				g_Recovery.col.a = 0.3f;
				g_Recovery.ui = Recovery_IN;		// �t�F�[�h�C�����
			}
		}

		VERTEX_2D* pVtx;

		// ���b�N
		g_pVtxBuffRecovery->Lock(0, 0, (void**)&pVtx, 0);

		// ���_�J���[
		pVtx[0].col = D3DXCOLOR(g_Recovery.col);
		pVtx[1].col = D3DXCOLOR(g_Recovery.col);
		pVtx[2].col = D3DXCOLOR(g_Recovery.col);
		pVtx[3].col = D3DXCOLOR(g_Recovery.col);

		// �A�����b�N
		g_pVtxBuffRecovery->Unlock();
	}
}

//====================
//	�`�揈��
//====================
void DrawRecovery(void)
{
	// �f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffRecovery, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	if (g_Recovery.bUse == true)
	{
		// �|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}
}

//====================
//	�z�u����
//====================
void SetRecovery(int count)
{
	g_Recovery.ui = Recovery_OUT;	// �t�F�[�h�A�E�g���
	g_Recovery.count = count;		// �J�E���g
	g_Recovery.bUse = true;			// �\������Ă���Ȃ�
}