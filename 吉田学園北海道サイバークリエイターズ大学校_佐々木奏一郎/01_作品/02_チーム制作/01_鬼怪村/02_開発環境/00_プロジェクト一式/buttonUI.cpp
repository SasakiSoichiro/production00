//====================================================
//
// �A�C�e���\���̏��� [KeyUI.cpp]
// Author : chikada shouya
//
//====================================================

#include "buttonUI.h"
#include "itemUI.h"

// �O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_ButtonUiTexture[BUTTONUITYPE_MAX] = { };	// Ui�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffButtonUi = NULL;				// Ui�o�b�t�@�ւ̃|�C���^
BUTTONUI g_ButtonUI[MAX_BUTTONUI];

//====================================================
// �A�C�e��UI�\���̏���������
//====================================================
void InitButtonUI()
{
	LPDIRECT3DDEVICE9 pDevice;			// �f�o�C�X�ւ̃|�C���^
	pDevice = GetDevice();				// �f�o�C�X�̎擾

	for (int nCnt = 0; nCnt < BUTTONUITYPE_MAX; nCnt++)
	{
		// �e�N�X�`���Ǎ�
		D3DXCreateTextureFromFile(pDevice,
			BUTTONUITYPE__TEXTURE[nCnt],
			&g_ButtonUiTexture[nCnt]);
	}

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BUTTONUI,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffButtonUi, NULL);

	// ���_���ւ̃|�C���^
	VERTEX_2D* pVtx;

	// ���_�o�b�t�@�̃��b�N�A���_�f�[�^�ւ̃|�C���^�擾
	g_pVtxBuffButtonUi->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt1 = 0; nCnt1 < MAX_BUTTONUI; nCnt1++)
	{
		// �\���̕ϐ��̏�����
		g_ButtonUI[nCnt1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_ButtonUI[nCnt1].fHeight = 0.0f;
		g_ButtonUI[nCnt1].fWidth = 0.0f;
		g_ButtonUI[nCnt1].bUse = false;

		// ���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

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

		pVtx += 4;
	}

	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffButtonUi->Unlock();
}

//====================================================
// �A�C�e��UI�\���̏I������
//====================================================
void UninitButtonUI()
{
	for (int nCnt = 0; nCnt < BUTTONUITYPE_MAX; nCnt++)
	{
		// �e�N�X�`���̔j��
		if (g_ButtonUiTexture[nCnt] != NULL)
		{
			g_ButtonUiTexture[nCnt]->Release();
			g_ButtonUiTexture[nCnt] = NULL;
		}
	}

	// ���_�o�b�t�@�̔j��
	if (g_pVtxBuffButtonUi != NULL)
	{
		g_pVtxBuffButtonUi->Release();
		g_pVtxBuffButtonUi = NULL;
	}
}

//====================================================
// �A�C�e��UI�\���̍X�V����
//====================================================
void UpdateButtonUI()
{
	int nSelect = GetSelect();

	for (int nCnt = 0; nCnt < MAX_BUTTONUI; nCnt++)
	{
		if (g_ButtonUI[nCnt].aType == BUTTONUITYPE_BUTTON_Y)
		{
			if (nSelect == 0)
			{
				g_ButtonUI[0].bUse = true;
				g_ButtonUI[1].bUse = false;
				g_ButtonUI[2].bUse = false;
			}
			else if (nSelect == 1)
			{
				g_ButtonUI[1].bUse = true;
				g_ButtonUI[0].bUse = false;
				g_ButtonUI[2].bUse = false;
			}
			else if (nSelect == 2)
			{
				g_ButtonUI[2].bUse = true;
				g_ButtonUI[0].bUse = false;
				g_ButtonUI[1].bUse = false;
			}
		}
		if (g_ButtonUI[nCnt].aType == BUTTONUITYPE_BUTTON_X)
		{
			g_ButtonUI[nCnt].bUse = true;
		}
	}
}

//====================================================
// �A�C�e��UI�\���̕`�揈��
//====================================================
void DrawButtonUI()
{
	// �f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;
	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffButtonUi, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCnt = 0; nCnt < MAX_BUTTONUI; nCnt++)
	{
		if (g_ButtonUI[nCnt].bUse == true)
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_ButtonUiTexture[g_ButtonUI[nCnt].aType]);

			// �A�C�e��UI�̕`��
			pDevice->DrawPrimitive(
				D3DPT_TRIANGLESTRIP,	// �v���~�e�B�u�̎��
				nCnt * 4,				// �`�悷��ŏ��̒��_�C���f�b�N�X
				2						// �v���~�e�B�u�i�A�C�e��UI�j�̐�
			);
		}
	}
}

//====================================================
// ����UI�̐ݒ菈��
//====================================================
void SetButtonUI(D3DXVECTOR3 pos, BUTTONUITYPE aType, float fWidth, float fHeight)
{
	// ���_���̃|�C���^
	VERTEX_2D* pVtx;

	// ���_�o�b�t�@�̃��b�N�A���_�f�[�^�ւ̃|�C���^�擾
	g_pVtxBuffButtonUi->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_BUTTONUI; nCnt++)
	{
		if (g_ButtonUI[nCnt].bUse == false)
		{// ���g�p��Ԃ�������
			g_ButtonUI[nCnt].pos = pos;
			g_ButtonUI[nCnt].aType = aType;
			g_ButtonUI[nCnt].fHeight = fHeight;
			g_ButtonUI[nCnt].fWidth = fWidth;
			g_ButtonUI[nCnt].bUse = true;

			// ���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_ButtonUI[nCnt].pos.x - fWidth, g_ButtonUI[nCnt].pos.y - fHeight, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_ButtonUI[nCnt].pos.x + fWidth, g_ButtonUI[nCnt].pos.y - fHeight, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_ButtonUI[nCnt].pos.x - fWidth, g_ButtonUI[nCnt].pos.y + fHeight, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_ButtonUI[nCnt].pos.x + fWidth, g_ButtonUI[nCnt].pos.y + fHeight, 0.0f);
			break;
		}
		pVtx += 4;
	}

	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffButtonUi->Unlock();
}
