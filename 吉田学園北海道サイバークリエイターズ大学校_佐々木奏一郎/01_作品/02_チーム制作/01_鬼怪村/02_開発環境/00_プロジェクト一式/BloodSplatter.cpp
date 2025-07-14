//=============================================================================
//
// �����Ԃ��̏��� [BloodSplatter.cpp]
// Author : Hirata ryuusei
//
//=============================================================================

#include "BloodSplatter.h"
#include "ui.h"
#include "player.h"
#include "item.h"

// �O���[�o���ϐ�

// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureUI[BLOODTYPE_MAX] = {};

// ���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffUI = NULL;

UI g_ui[BLOODTYPE_MAX] = {};

//====================
//	����������
//====================
void InitBloodSplatter(void)
{
	for (int nCnt = 0; nCnt < BLOODTYPE_MAX; nCnt++)
	{//�O���[�o���ϐ�������
		g_ui[nCnt].ui = UI_NONE;
		g_ui[nCnt].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.1f);
		g_ui[nCnt].count = 0;
		g_ui[nCnt].bUse = false;
	}

	// �f�o�C�X���̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	for (int nCnt = 0; nCnt < BLOODTYPE_MAX; nCnt++)
	{// �e�N�X�`���o�b�t�@����
		D3DXCreateTextureFromFile(pDevice,
			UI_TEXTURE[nCnt],
			&g_pTextureUI[nCnt]);
	}

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * BLOODTYPE_MAX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffUI,
		NULL);

	VERTEX_2D* pVtx;

	// ���b�N
	g_pVtxBuffUI->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < BLOODTYPE_MAX; nCnt++)
	{
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
		pVtx[0].col = D3DXCOLOR(g_ui[nCnt].col);
		pVtx[1].col = D3DXCOLOR(g_ui[nCnt].col);
		pVtx[2].col = D3DXCOLOR(g_ui[nCnt].col);
		pVtx[3].col = D3DXCOLOR(g_ui[nCnt].col);

		pVtx += 4;
	}

	// �A�����b�N
	g_pVtxBuffUI->Unlock();
}

//====================
//	�I������
//====================
void UinitBloodSplatter(void)
{
	// �e�N�X�`���̔j��
	for (int nCnt = 0; nCnt < BLOODTYPE_MAX; nCnt++)
	{
		if (g_pTextureUI[nCnt] != NULL)
		{
			g_pTextureUI[nCnt]->Release();
			g_pTextureUI[nCnt] = NULL;
		}
	}

	// ���_�o�b�t�@�̉��
	if (g_pVtxBuffUI != NULL)
	{
		g_pVtxBuffUI->Release();
		g_pVtxBuffUI = NULL;
	}
}

//====================
//	�X�V����
//====================
void UpdateBloodSplatter(void)
{
	// ���[�J���ϐ��錾
	Player* pPlayer = GetPlayer();
	ITEM* pItem = Getitem();
	VERTEX_2D* pVtx;


	// ���b�N
	g_pVtxBuffUI->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < BLOODTYPE_MAX; nCnt++)
	{
		if (g_ui[nCnt].ui != UI_NONE)
		{// NONE�łȂ��ꍇ

			if (g_ui[nCnt].ui == UI_IN)
			{// IN�̏ꍇ

				// �t�F�[�h�C��
				g_ui[nCnt].col.a -= 0.01f;			// �|���S���������ɂȂ鑬��

				if (g_ui[nCnt].col.a <= 0.0f)
				{// ���l��0.0f�ȉ��ɂȂ����ꍇ

					g_ui[nCnt].col.a = 0.0f;		// ���l��0.0f�ɐݒ�
					g_ui[nCnt].ui = UI_NONE;		// �������Ă��Ȃ����
					g_ui[nCnt].bUse = false;		//�g���Ă��Ȃ���Ԃɐݒ�
					
				}
			}

			else if (g_ui[nCnt].ui == UI_OUT)
			{// OUT�̏ꍇ

				// �t�F�[�h�A�E�g
				g_ui[nCnt].col.a += 0.05f;			// �|���S�����s�����ɂȂ鑬��

				if (g_ui[nCnt].col.a >= 0.7f)
				{// ���l��0.7f�ȉ��ɂȂ����ꍇ

					g_ui[nCnt].col.a = 0.7f;		// ���l��0.7f�ɐݒ�
					g_ui[nCnt].ui = UI_NONE;		// �������Ă��Ȃ����

				}
			}


		}



		// ���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(g_ui[nCnt].col);
		pVtx[1].col = D3DXCOLOR(g_ui[nCnt].col);
		pVtx[2].col = D3DXCOLOR(g_ui[nCnt].col);
		pVtx[3].col = D3DXCOLOR(g_ui[nCnt].col);

		// pVtx��4����
		pVtx += 4;



		if (g_ui[nCnt].bUse == true)
		{// �g���Ă���ꍇ

			g_ui[nCnt].count--;	// �f�N�������g

		}


		if (g_ui[nCnt].count <= 0 && pPlayer->nLife >= 2 && g_ui[nCnt].bUse == true)
		{// count��0�ȉ�����life��2�ȏォ��true�̏ꍇ

			g_ui[nCnt].ui = UI_NONE;	// �������Ă��Ȃ����
			g_ui[nCnt].count = 0;		// count������

		}

		else if (g_ui[nCnt].count <= 0 && pPlayer->nLife <= 1 && g_ui[nCnt].bUse == true)
		{// count��0�ȉ�����life��1�ȏォ��true�̏ꍇ

			g_ui[nCnt].ui = UI_NONE;	// �������Ă��Ȃ����
			g_ui[nCnt].count = 0;		// count������

		}


		if (pPlayer->nLife >= 3)
		{// life��3�ȏ�̏ꍇ

			g_ui[nCnt].bUse = false;	// �\������Ă��Ȃ��Ƃ�
			g_ui[nCnt].ui = UI_IN;		// �t�F�[�h�C�����
			g_ui[nCnt].count = 0;		// count������

		}
	}
	// �A�����b�N
	g_pVtxBuffUI->Unlock();
}

//====================
//	�`�揈��
//====================
void DrawBloodSplatter(void)
{
	// �f�o�C�X�ւ̃|�C���^�A��Ԏ擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	Player* pPlayer = GetPlayer();

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffUI, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCnt = 0; nCnt < BLOODTYPE_MAX; nCnt++)
	{
		if (g_ui[nCnt].bUse == true)
		{// �g���Ă���ꍇ

				// �e�N�X�`���̐ݒ�
				pDevice->SetTexture(BLOODTYPE_RED, g_pTextureUI[g_ui[nCnt].nType]);
				// �e�N�X�`���̐ݒ�
				pDevice->SetTexture(BLOODTYPE_SMALL, g_pTextureUI[g_ui[nCnt].nType]);
				// �e�N�X�`���̐ݒ�
				pDevice->SetTexture(BLOODTYPE_BIG, g_pTextureUI[g_ui[nCnt].nType]);

				// �|���S���̕`��
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4*nCnt, 2);
		}
	}


}

//====================
//	�ݒ菈��
//====================
void SetBloodSplatter(int count, int nType,UI_MODE uiType)
{
	for (int nCnt = 0; nCnt < BLOODTYPE_MAX; nCnt++)
	{
		if (g_ui[nCnt].bUse == false)
		{
			g_ui[nCnt].ui = uiType;		// �t�F�[�h�A�E�g���
			if (uiType == UI_IN|| uiType == UI_NONE)
			{
				g_ui[nCnt].col.a = 0.5f;
			}
			g_ui[nCnt].count = count;
			g_ui[nCnt].nType = nType;
			g_ui[nCnt].bUse = true;		// �\������Ă���Ƃ�
			break;
		}
	}
}