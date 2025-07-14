//=============================================================================
//
// �X���[���[�V�������� [slow.h]
// Author : ���X�ؑt��Y
//
//=============================================================================

#include "slow.h"
#include "sound.h"

//�O���[�o���ϐ��錾
//	�O���[�o��
//	���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffSlow = NULL;
D3DXCOLOR g_colorSlow;
Slow g_Slow;
int g_nCntSlowState;

//----------------
// �X���[�̏���������
//----------------
void InitSlow(void)
{
	g_Slow.fMulti = 1.0f;
	g_Slow.fDivi = 1.0f;
	g_Slow.nMulti = 1;
	g_Slow.nDivi = 1;
	g_Slow.fade = SLOWFADE_IN;
	g_Slow.color = D3DXCOLOR(0.0f, 0.0f, 0.3f, 1.0f);
	g_Slow.bUse = false;
	g_nCntSlowState = 0;

	

	//	�f�o�C�X���̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//	���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffSlow,
		NULL);

	VERTEX_2D* pVtx;
	//	���b�N
	g_pVtxBuffSlow->Lock(0, 0, (void**)&pVtx, 0);

	//	���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);

	//	rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//	���_�J���[
	pVtx[0].col = D3DXCOLOR(g_Slow.color);
	pVtx[1].col = D3DXCOLOR(g_Slow.color);
	pVtx[2].col = D3DXCOLOR(g_Slow.color);
	pVtx[3].col = D3DXCOLOR(g_Slow.color);

	//	�A�����b�N
	g_pVtxBuffSlow->Unlock();

}

//-------------------
//�X���[�̏I������
//-------------------
void UninitSlow(void)
{
	// SE���~�߂�
	StopSound(SOUND_LABEL_SE3);

	//	���_�o�b�t�@�̔j��
	if (g_pVtxBuffSlow != NULL)
	{
		g_pVtxBuffSlow->Release();
		g_pVtxBuffSlow = NULL;
	}
}

//-------------------
// �X���[�̍X�V����
//-------------------
void UpdateSlow(void)
{
	if (g_Slow.bUse == true)
	{
		g_Slow.fade = SLOWFADE_OUT;
		g_nCntSlowState++;
		if (g_nCntSlowState > 600)
		{
			g_nCntSlowState = 0;
			g_Slow.fade = SLOWFADE_IN;
			g_Slow.bUse = false;
			SetSlow();
		}
	}
	if (g_Slow.fade!= SLOWFADE_NONE)
	{
		if (g_Slow.fade == SLOWFADE_IN)
		{
			//	�t�F�[�h�C��
			g_Slow.color.a -= 0.01f;		//�|���S���������ɂȂ鑬��
			if (g_Slow.color.a <= 0.0f)
			{
				g_Slow.color.a = 0.0f;
				g_Slow.fade = SLOWFADE_NONE;		//�������Ă��Ȃ����
			}
		}
		else if (g_Slow.fade == SLOWFADE_OUT)
		{
			//	�t�F�[�h�A�E�g
			g_Slow.color.a += 0.02f;

			if (g_Slow.color.a >= 0.3f)
			{
				g_Slow.color.a = 0.3f;
			}
		}

		VERTEX_2D* pVtx;
		//	���b�N
		g_pVtxBuffSlow->Lock(0, 0, (void**)&pVtx, 0);

		//	���_�J���[
		pVtx[0].col = D3DXCOLOR(g_Slow.color);
		pVtx[1].col = D3DXCOLOR(g_Slow.color);
		pVtx[2].col = D3DXCOLOR(g_Slow.color);
		pVtx[3].col = D3DXCOLOR(g_Slow.color);

		//	�A�����b�N
		g_pVtxBuffSlow->Unlock();
	}
}

//-------------------
// �X���[�̕`�揈��
//-------------------
void DrawSlow(void)
{
	//	�f�o�C�X���̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//	�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, NULL);

	//	���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffSlow, 0, sizeof(VERTEX_2D));

	//	���_�t�H�[�}�b�g�ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//	�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

void SetSlow()
{
	if (g_Slow.bUse == true)
	{
		g_Slow.fMulti = (int)SLOW;
		g_Slow.fDivi = 1.0 / SLOW;
		g_Slow.nMulti = SLOW;
	}
	else if (g_Slow.bUse == false)
	{
		g_Slow.fMulti = 1.0f;
		g_Slow.fDivi = 1.0f;
		g_Slow.nMulti = 1;
	}
}

Slow*GetSlow(void)
{
	return &g_Slow;
}