//=============================================================================
//
//    �����Q�[�W���� [gauge.cpp]
//    Author : Chikada
//
//=============================================================================
#include "gauge.h"
#include "input.h"
#include "player.h"
#include "gimmick.h"
#include "item.h"

// �O���[�o��
Gauge g_gauge = {};
LPDIRECT3DTEXTURE9 g_GaugeTexture =  NULL ;			// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffGauge = NULL;		// �o�b�t�@�ւ̃|�C���^

//===================
// ����������
//===================
void InitGauge(void)
{
	VERTEX_2D* pVtx{};

	LPDIRECT3DDEVICE9 pDevice;					// �f�o�C�X�ւ̃|�C���^
	pDevice = GetDevice();						// �f�o�C�X�̎擾

		// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\texture\\hold.jpg",
		&g_GaugeTexture);

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffGauge, NULL);

	// ���_�o�b�t�@�̃��b�N�A���_�f�[�^�ւ̃|�C���^�擾
	g_pVtxBuffGauge->Lock(0, 0, (void**)&pVtx, 0);

	// �e�ϐ��̏�����
	g_gauge.bKeyhave = false;
	g_gauge.bUse = false;
	g_gauge.fCnt = 0.0f;
	g_gauge.fCnt1 = 0.0f;
	g_gauge.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// ���_���̐ݒ�
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

	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffGauge->Unlock();
}

//===================
//	�I������
//===================
void UinitGauge(void)
{

	// �e�N�X�`���̔j��
	if (g_GaugeTexture != NULL)
	{
		g_GaugeTexture->Release();
		g_GaugeTexture = NULL;
	}
	
	// ���_�o�b�t�@�̔j��
	if (g_pVtxBuffGauge != NULL)
	{
		g_pVtxBuffGauge->Release();
		g_pVtxBuffGauge = NULL;
	}
}

//===================
//	�X�V����
//===================
void UpdateGauge(void)
{
	Player* pPlayer = GetPlayer();
	bool isbill = IsBill();			// �͈͎擾
	ITEM* pItem = Getitem();

	VERTEX_2D* pVtx{};

	// ���_�o�b�t�@�̃��b�N�A���_�f�[�^�ւ̃|�C���^�擾
	g_pVtxBuffGauge->Lock(0, 0, (void**)&pVtx, 0);

	// �v���C���[���A�C�e���͈̔͂ɓ�������
	if (isbill == true)
	{
		g_gauge.bUse = true;

		if (pItem[0].bHold == true && pItem[1].bHold == true)
		{
			if (g_gauge.fCnt < 3.0f)
			{
				if (GetKeyboardPress(DIK_F) || GetJoypadPress(JOYKEY_B) == true)
				{
					g_gauge.fCnt += 0.01f;
				}
				else if (g_gauge.fCnt >= 0)
				{
					g_gauge.fCnt -= 0.01f;
				}
			}
			if (g_gauge.fCnt >= 3.0f)
			{
				g_gauge.fCnt = 3.0f;
			}
			if (g_gauge.fCnt < 0)
			{
				g_gauge.fCnt1 = 321.5f;
			}

			// ���_���̐ݒ�
			pVtx[0].pos.x = g_gauge.fCnt1;
			pVtx[0].pos.y = 399.5f;
			pVtx[0].pos.z = 0.0f;

			pVtx[1].pos.x = g_gauge.fCnt1 * g_gauge.fCnt;
			pVtx[1].pos.y = 399.5f;
			pVtx[1].pos.z = 0.0f;

			pVtx[2].pos.x = g_gauge.fCnt1;
			pVtx[2].pos.y = 450.5f;
			pVtx[2].pos.z = 0.0f;

			pVtx[3].pos.x = g_gauge.fCnt1 * g_gauge.fCnt;
			pVtx[3].pos.y = 450.5f;
			pVtx[3].pos.z = 0.0f;
		}
	}
	else
	{
		g_gauge.bUse = false;

		if (g_gauge.fCnt >= 0)
		{
			g_gauge.fCnt -= 0.01f;
		}
	}
	
	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffGauge->Unlock();
}

//===================
//	�`�揈��
//===================
void DrawGauge(void)
{
	// �f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffGauge, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	if (g_gauge.bUse == true)
	{
		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_GaugeTexture);
		
		// �|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}
}

//===================
//	�z�u����
//===================
void SetGauge(D3DXVECTOR3 pos)
{
	if (g_gauge.bUse == false)
	{
		g_gauge.pos = pos;
		
		g_gauge.bUse = true;
	}
}