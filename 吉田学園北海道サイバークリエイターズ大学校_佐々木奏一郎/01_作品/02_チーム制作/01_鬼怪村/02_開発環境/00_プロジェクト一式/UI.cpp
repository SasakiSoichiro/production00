//====================================================
//
// �\���̏��� [UI.cpp]
// Author : yabuki yukito
//
//====================================================

#include "UI.h"
#include "player.h"

//++++++++++++++++++++++++++++++++++++++++++++++++++++
// �O���[�o���ϐ�
//++++++++++++++++++++++++++++++++++++++++++++++++++++
D3DXVECTOR3 pos;								// ���Ԃ̈ʒu
LPDIRECT3DTEXTURE9 g_UiTexture[MAX_TEX] = {};			// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffUi = NULL;	// �o�b�t�@�ւ̃|�C���^

//====================================================
// �\���̏���������
//====================================================
void InitEyeUI()
{
	VERTEX_2D* pVtx{};

	LPDIRECT3DDEVICE9 pDevice;					// �f�o�C�X�ւ̃|�C���^

	pDevice = GetDevice();						// �f�o�C�X�̎擾

	D3DXVECTOR3 pos = D3DXVECTOR3(630.0f, 100.0f, 0.0f);

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\texture\\Eye.png",
		&g_UiTexture[0]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\texture\\Eye1.png",
		&g_UiTexture[1]);

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffUi, NULL);

	// ���_�o�b�t�@�̃��b�N�A���_�f�[�^�ւ̃|�C���^�擾
	g_pVtxBuffUi->Lock(0, 0, (void**)&pVtx, 0);

	//���_���̐ݒ�
	pVtx[0].pos.x = pos.x - MAX_TIMEWIDTH / 2.0f;
	pVtx[0].pos.y = pos.y - MAX_TIMEHEIGHT / 2.0f;
	pVtx[0].pos.z = pos.z;

	pVtx[1].pos.x = pos.x + MAX_TIMEWIDTH / 2.0f;
	pVtx[1].pos.y = pos.y - MAX_TIMEHEIGHT / 2.0f;
	pVtx[1].pos.z = pos.z;

	pVtx[2].pos.x = pos.x - MAX_TIMEWIDTH / 2.0f;
	pVtx[2].pos.y = pos.y + MAX_TIMEHEIGHT / 2.0f;
	pVtx[2].pos.z = pos.z;

	pVtx[3].pos.x = pos.x + MAX_TIMEWIDTH / 2.0f;
	pVtx[3].pos.y = pos.y + MAX_TIMEHEIGHT / 2.0f;
	pVtx[3].pos.z = pos.z;

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
	g_pVtxBuffUi->Unlock();
}

//====================================================
// �\���̏I������
//====================================================
void UninitEyeUI()
{
	// �e�N�X�`���̔j��
	for (int nCnt = 0; nCnt < MAX_TEX; nCnt++)
	{
		if (g_UiTexture[nCnt] != NULL)
		{
			g_UiTexture[nCnt]->Release();
			g_UiTexture[nCnt] = NULL;
		}
	}

	// ���_�o�b�t�@�̔j��
	if (g_pVtxBuffUi != NULL)
	{
		g_pVtxBuffUi->Release();
		g_pVtxBuffUi = NULL;
	}
}

//====================================================
// �\���̍X�V����
//====================================================
void UpdateEyeUI()
{
	Player* pPlayer = GetPlayer();

	VERTEX_2D* pVtx{};

	// ���_�o�b�t�@�̃��b�N�A���_�f�[�^�ւ̃|�C���^�擾
	g_pVtxBuffUi->Lock(0, 0, (void**)&pVtx, 0);

	if (pPlayer->bEye == true)
	{
		// ���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}
	else if (pPlayer->bEye == false)
	{
		// ���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.4f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.4f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.4f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.4f);
	}

	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffUi->Unlock();
}

//====================================================
//�\���̕`�揈��
//====================================================
void DrawEyeUI()
{
	Player* pPlayer = GetPlayer();

	LPDIRECT3DDEVICE9 pDevice;					// �f�o�C�X�ւ̃|�C���^

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffUi, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCnt = 0; nCnt < MAX_TEX; nCnt++)
	{
		if (pPlayer->bEye == true)
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_UiTexture[0]);

		}
		else if (pPlayer->bEye == false)
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_UiTexture[1]);

		}
	}

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}
