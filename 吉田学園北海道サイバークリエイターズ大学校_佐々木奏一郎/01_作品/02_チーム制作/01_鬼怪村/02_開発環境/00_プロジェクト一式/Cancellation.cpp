//==============================================
//
//
//			�����̏���
//
//			Yabuki
//
//===============================================

#include "Cancellation.h"
#include "input.h"
#include "player.h"
#include "gimmick.h"
#include "item.h"

// �O���[�o��
Cance g_Cancellation = {};
LPDIRECT3DTEXTURE9 g_CancellationTexture[TEX_MAX] = {};		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffCancellation = NULL;		// �o�b�t�@�ւ̃|�C���^

//===================
//	����������
//===================
void InitCancellation(void)
{
	VERTEX_2D* pVtx{};

	LPDIRECT3DDEVICE9 pDevice;		// �f�o�C�X�ւ̃|�C���^
	pDevice = GetDevice();			// �f�o�C�X�̎擾

	// �e�ϐ��̏�����
	g_Cancellation.bKeyhave = false;
	g_Cancellation.bUse = false;
	g_Cancellation.fCnt = 0.0f;
	g_Cancellation.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	for (int nCntLoad = 0; nCntLoad < TEX_MAX; nCntLoad++)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,
			X_TEX[nCntLoad],
			&g_CancellationTexture[nCntLoad]);
	}

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffCancellation, NULL);

	// ���_�o�b�t�@�̃��b�N�A���_�f�[�^�ւ̃|�C���^�擾
	g_pVtxBuffCancellation->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(320.0f, 340.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(640.0f, 340.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(320.0f, 400.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(640.0f, 400.0f, 0.0f);

	// rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// ���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffCancellation->Unlock();
}

//===================
//	�I������
//===================
void UinitCancellation(void)
{
	for (int nCnt = 0; nCnt < TEX_MAX; nCnt++)
	{
		// �e�N�X�`���̔j��
		if (g_CancellationTexture != NULL)
		{
			g_CancellationTexture[nCnt]->Release();
			g_CancellationTexture[nCnt] = NULL;
		}
	}

	// ���_�o�b�t�@�̔j��
	if (g_pVtxBuffCancellation != NULL)
	{
		g_pVtxBuffCancellation->Release();
		g_pVtxBuffCancellation = NULL;
	}
}

//===================
//	�X�V����
//===================
void UpdateCancellation(void)
{
	Player* pPlayer = GetPlayer();
	GIMMICK* pGimmick = GetGimmick();
	ITEM* pItem = Getitem();

	//if (g_Cancellation.bUse)
	//{
		// �v���C���[�̔��a�̎Z�o�p�ϐ�
		float fPRadPos = 50.0f;

		// �A�C�e���̔��a�̎Z�o�p�ϐ�
		float fIRadPos = 50.0f;

		// �A�C�e���̃v���C���[�̋����̍�
		D3DXVECTOR3 diff = pPlayer->pos - pGimmick->pos;

		// �͈͌v�Z
		float fDisX = pPlayer->pos.x - pGimmick->pos.x;
		float fDisY = pPlayer->pos.y - pGimmick->pos.y;
		float fDisZ = pPlayer->pos.z - pGimmick->pos.z;

		// ��̔��a�����߂�
		float fRadX = fPRadPos + fIRadPos;

		// �v���C���[���A�C�e���͈̔͂ɓ�������
		if ((fDisX * fDisX) + (fDisY * fDisY) + (fDisZ * fDisZ) <= (fRadX * fRadX))
		{
			if (pItem[0].bHold == true && pItem[1].bHold == true)
			{
				g_Cancellation.bUse = true;
				if (GetKeyboardPress(DIK_F) || GetJoypadPress(JOYKEY_B) == true)
				{// F��������Ă�����
					g_Cancellation.nType = TEX_0;
				}
				else
				{
					g_Cancellation.nType = TEX_1;
				}
			}
		}
		else
		{
			g_Cancellation.bUse = false;
		}
	//}
}

//===================
//	�`�揈��
//===================
void DrawCancellation(void)
{
	// �f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffCancellation, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	for (int nCntTex = 0; nCntTex < TEX_MAX; nCntTex++)
	{
		if (g_Cancellation.bUse == true)
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_CancellationTexture[g_Cancellation.nType]);
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(1, g_CancellationTexture[g_Cancellation.nType]);

			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

		}
	}
}
