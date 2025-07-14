//=============================================================================
//
//�@�G���_�̃r���[�|�[�g�̘g�̏��� [viewportwaku.cpp]
// �@Author : �ߓc����
//
//=============================================================================
#include "unlock.h"
#include "gimmick.h"
#include "item.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureUnlock = {};			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffUnlock = NULL;	//���_�o�b�t�@�ւ̃|�C���^
bool bUse;
//====================================
//�G���_�̃r���[�|�[�g�̘g�̏���������
//====================================
void InitUnlock(void)
{
	//���[�J���ϐ�
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^
	VERTEX_2D* pVtx;		//���_���ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\texture\\waku2.png",
		&g_pTextureUnlock);

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,//(sizeof(VERTEX_2D)*�K�v�Ȓ��_��
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffUnlock,
		NULL);

	bUse = false;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffUnlock->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(307.5f, 397.5f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(972.5f, 397.5f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(307.5f, 452.5f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(972.5f, 452.5f, 0.0f);

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
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffUnlock->Unlock();
}

//====================================
//�G���_�̃r���[�|�[�g�̘g�̏I������
//====================================
void UninitUnlock(void)
{

	//�e�N�X�`���̔j��
	if (g_pTextureUnlock != NULL)
	{
		g_pTextureUnlock->Release();
		g_pTextureUnlock = NULL;
	}


	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffUnlock != NULL)
	{
		g_pVtxBuffUnlock->Release();
		g_pVtxBuffUnlock = NULL;
	}

}

//====================================
//�G���_�̃r���[�|�[�g�̘g�̍X�V����
//====================================
void UpdateUnlock(void)
{
	bool isBill = IsBill();
	ITEM* pItem = Getitem();

	if (isBill == true)
	{
		if (pItem[0].bHold == true && pItem[1].bHold == true)
		{
			bUse = true;
		}

	}
	else
	{
		bUse = false;
	}
}

//====================================
//�G���_�̃r���[�|�[�g�̘g�̕`�揈��
//====================================
void DrawUnlock(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffUnlock, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	if (bUse == true)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureUnlock);

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}
}
