//=============================================================================
//
// �A�C�e���\���̏��� [KeyUI.cpp]
// Author : chikada shouya
//
//=============================================================================

#include "KeyUI.h"
#include "item.h"

// �O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_ItemKeyUiTexture[ITEMKEYUITYPE_MAX] = { };		// Ui�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffItemKeyUi = NULL;					// Ui�o�b�t�@�ւ̃|�C���^
ITEMKEYUI g_ItemKeyUI[ITEMKEYUITYPE_MAX];
bool bHave;
bool bHave1;

//=============================================================================
// �A�C�e��UI�\���̏���������
//=============================================================================
void InitKeyUI()
{
	LPDIRECT3DDEVICE9 pDevice;				// �f�o�C�X�ւ̃|�C���^
	pDevice = GetDevice();					// �f�o�C�X�̎擾

	for (int nCnt = 0; nCnt < ITEMKEYUITYPE_MAX; nCnt++)
	{
		// �e�N�X�`���̓Ǎ�
		D3DXCreateTextureFromFile(pDevice,
			ITEMKEYUI_TEXTURE[nCnt],
			&g_ItemKeyUiTexture[nCnt]);
	}

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * ITEMKEYUITYPE_MAX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffItemKeyUi, NULL);

	// ���_���ւ̃|�C���^
	VERTEX_2D* pVtx;

	// ���_�o�b�t�@�̃��b�N�A���_�f�[�^�ւ̃|�C���^�擾
	g_pVtxBuffItemKeyUi->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt1 = 0; nCnt1 < ITEMKEYUITYPE_MAX; nCnt1++)
	{
		// �\���̕ϐ��̏�����
		g_ItemKeyUI[nCnt1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_ItemKeyUI[nCnt1].fHeight = 0.0f;
		g_ItemKeyUI[nCnt1].fWidth = 0.0f;
		g_ItemKeyUI[nCnt1].bUse = false;
		bHave = false;
		bHave1 = false;

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
	g_pVtxBuffItemKeyUi->Unlock();
}

//=============================================================================
// �A�C�e��UI�\���̏I������
//=============================================================================
void UninitKeyUI()
{
	for (int nCnt = 0; nCnt < ITEMKEYUITYPE_MAX; nCnt++)
	{
		// �e�N�X�`���̔j��
		if (g_ItemKeyUiTexture[nCnt] != NULL)
		{
			g_ItemKeyUiTexture[nCnt]->Release();
			g_ItemKeyUiTexture[nCnt] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffItemKeyUi != NULL)
	{
		g_pVtxBuffItemKeyUi->Release();
		g_pVtxBuffItemKeyUi = NULL;
	}
}

//=============================================================================
//�A�C�e��UI�\���̍X�V����
//=============================================================================
void UpdateKeyUI()
{
	// �A�C�e���̎擾����
	ITEM* pItem = Getitem();

	// ���̏㕔�̂ݎ�����ꍇ
	if (pItem[0].bHold == true && pItem[1].bHold == false)
	{
		bHave = true;
	}

	// ���̉����̂ݎ�����ꍇ
	if (pItem[1].bHold == true && pItem[0].bHold == false)
	{
		bHave = true;
	}

	// ���̏㕔�Ɖ����̗������Ƃ����ꍇ
	if (pItem[0].bHold == true && pItem[1].bHold == true)
	{
		bHave = false;
		bHave1 = true;
	}
}
//=============================================================================
// �A�C�e��UI�\���̕`�揈��
//=============================================================================
void DrawKeyUI()
{
	// �f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffItemKeyUi, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCnt = 0; nCnt < ITEMKEYUITYPE_MAX; nCnt++)
	{

		if (g_ItemKeyUI[nCnt].bUse == true)
		{

			if (bHave == true)
			{
				// �e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_ItemKeyUiTexture[1]);
			}
			else if (bHave1 == true)
			{
				// �e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_ItemKeyUiTexture[2]);
			}
			else
			{
				// �e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_ItemKeyUiTexture[g_ItemKeyUI[nCnt].aType]);

			}

			// �A�C�e��UI�̕`��
			pDevice->DrawPrimitive(
				D3DPT_TRIANGLESTRIP,	// �v���~�e�B�u�̎��
				nCnt * 4,				// �`�悷��ŏ��̒��_�C���f�b�N�X
				2						// �v���~�e�B�u�i�A�C�e��UI�j�̐�
			);
		}
	}
}
//=============================================================================
// ����UI�̐ݒ菈��
//=============================================================================
void SetKeyUI(D3DXVECTOR3 pos, ITEMKEYUITYPE aType, float fWidth, float fHeight)
{
	// ���_���̃|�C���^
	VERTEX_2D* pVtx;

	// ���_�o�b�t�@�̃��b�N�A���_�f�[�^�ւ̃|�C���^�擾
	g_pVtxBuffItemKeyUi->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < ITEMKEYUITYPE_MAX; nCnt++)
	{
		if (g_ItemKeyUI[nCnt].bUse == false)
		{// ���g�p��Ԃ�������
			g_ItemKeyUI[nCnt].pos = pos;
			g_ItemKeyUI[nCnt].aType = aType;
			g_ItemKeyUI[nCnt].fHeight = fHeight;
			g_ItemKeyUI[nCnt].fWidth = fWidth;
			g_ItemKeyUI[nCnt].bUse = true;

			// ���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_ItemKeyUI[nCnt].pos.x - fWidth, g_ItemKeyUI[nCnt].pos.y - fHeight, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_ItemKeyUI[nCnt].pos.x + fWidth, g_ItemKeyUI[nCnt].pos.y - fHeight, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_ItemKeyUI[nCnt].pos.x - fWidth, g_ItemKeyUI[nCnt].pos.y + fHeight, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_ItemKeyUI[nCnt].pos.x + fWidth, g_ItemKeyUI[nCnt].pos.y + fHeight, 0.0f);
			break;
		}
		pVtx += 4;
	}

	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffItemKeyUi->Unlock();
}
