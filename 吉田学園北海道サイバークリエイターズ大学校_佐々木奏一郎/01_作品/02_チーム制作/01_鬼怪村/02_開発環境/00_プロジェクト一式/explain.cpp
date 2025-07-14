//=============================================================================
//
// �A�C�e���\���̏��� [KeyUI.cpp]
// Author : chikada shouya
//
//=============================================================================
#include "explain.h"
#include "item.h"
#include "input.h"

// �O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_ExplainTexture[EXPLAINTYPE_MAX] = { };	// Ui�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffExplain = NULL;			// Ui�o�b�t�@�ւ̃|�C���^

LPDIRECT3DTEXTURE9 g_ExplainTexture2 = NULL;				// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffExplain2 = NULL;			// �o�b�t�@

EXPLAIN g_Explain[EXPLAINTYPE_MAX];

bool bCount,bCount1,bCount2;

//=============================================================================
//�A�C�e��UI�\���̏���������
//=============================================================================
void InitExplain()
{
	LPDIRECT3DDEVICE9 pDevice;					// �f�o�C�X�ւ̃|�C���^
	pDevice = GetDevice();						// �f�o�C�X�̎擾

	for (int nCnt = 0; nCnt < EXPLAINTYPE_MAX; nCnt++)
	{
			// �e�N�X�`���̓Ǎ�
		D3DXCreateTextureFromFile(pDevice,
			EXPLAIN_TEXTURE[nCnt],
			&g_ExplainTexture[nCnt]);
	}

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\texture\\usukawa.png",
		&g_ExplainTexture2);

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * EXPLAINTYPE_MAX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffExplain, NULL);

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffExplain2,NULL);

	// ���_���ւ̃|�C���^
	VERTEX_2D* pVtx;

	bCount = false;
	bCount1 = false;
	bCount2 = false;

	// ���_�o�b�t�@�̃��b�N�A���_�f�[�^�ւ̃|�C���^�擾
	g_pVtxBuffExplain->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt1 = 0; nCnt1 < EXPLAINTYPE_MAX; nCnt1++)
	{
		// �\���̕ϐ��̏�����
		g_Explain[nCnt1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Explain[nCnt1].fHeight = 0.0f;
		g_Explain[nCnt1].fWidth = 0.0f;
		g_Explain[nCnt1].bLook = false;
		g_Explain[nCnt1].bUse = false;

		// ���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(240.0f, 85.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(1040.0f, 85.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(240.0f, 635.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(1040.0f, 635.0f, 0.0f);

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
	g_pVtxBuffExplain->Unlock();

	// ���b�N
	g_pVtxBuffExplain2->Lock(0, 0, (void**)&pVtx, 0);

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
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// �e�N�X�`�����W�̐ݒ�@�@�P�Q�T
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// �A�����b�N
	g_pVtxBuffExplain2->Unlock();
}

//=============================================================================
// �A�C�e��UI�\���̏I������
//=============================================================================
void UninitExplain()
{
	for (int nCnt = 0; nCnt < EXPLAINTYPE_MAX; nCnt++)
	{
		if (g_ExplainTexture[nCnt] != NULL)
		{
			g_ExplainTexture[nCnt]->Release();
			g_ExplainTexture[nCnt] = NULL;
		}
	}

	// ���_�o�b�t�@�̔j��
	if (g_pVtxBuffExplain != NULL)
	{
		g_pVtxBuffExplain->Release();
		g_pVtxBuffExplain = NULL;
	}

	if (g_ExplainTexture2 != NULL)
	{
		g_ExplainTexture2->Release();
		g_ExplainTexture2 = NULL;
	}

	// ���_�o�b�t�@�̔j��
	if (g_pVtxBuffExplain2 != NULL)
	{
		g_pVtxBuffExplain2->Release();
		g_pVtxBuffExplain2 = NULL;
	}
}

//=============================================================================
// �A�C�e��UI�\���̍X�V����
//=============================================================================
void UpdateExplain()
{
	// �A�C�e���̎擾����
	ITEM* pItem = Getitem();
	VERTEX_2D* pVtx;

	if (g_Explain[0].bLook == true || g_Explain[1].bLook == true || g_Explain[2].bLook == true)
	{
		// ���b�N
		g_pVtxBuffExplain2->Lock(0, 0, (void**)&pVtx, 0);

		// ���_�J���[
		pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.8f);
		pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.8f);
		pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.8f);
		pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.8f);

		// �A�����b�N
		g_pVtxBuffExplain2->Unlock();
	}

	// ���̏㕔�̂ݎ�����ꍇ
	if (pItem[2].bHold == true && bCount == false)
	{
		g_Explain[0].bLook = true;
	}

	// ���̉����̂ݎ�����ꍇ
	if (pItem[3].bHold == true && bCount1 == false)
	{
		g_Explain[1].bLook = true;
	}

	if (pItem[4].bHold == true && bCount2 == false)
	{
		g_Explain[2].bLook = true;
	}

	if (g_Explain[0].bLook == true && (GetJoypadPress(JOYKEY_A) == true || KeybordTrigger(DIK_RETURN) == true))
	{
		g_Explain[0].bLook = false;
		bCount = true;
	}

	if (g_Explain[1].bLook == true && (GetJoypadPress(JOYKEY_A) == true || KeybordTrigger(DIK_RETURN) == true))
	{
		g_Explain[1].bLook = false;
		bCount1 = true;
	}

	if (g_Explain[2].bLook == true && (GetJoypadPress(JOYKEY_A) == true || KeybordTrigger(DIK_RETURN) == true))
	{
		g_Explain[2].bLook = false;
		bCount2 = true;
	}
}

//=============================================================================
// �A�C�e��UI�\���̕`�揈��
//=============================================================================
void DrawExplain()
{
	// �f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	//=====================================================================//
	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffExplain2, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_ExplainTexture2);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	//=====================================================================//

	//=====================================================================//
	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffExplain, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCnt = 0; nCnt < EXPLAINTYPE_MAX; nCnt++)
	{

		if (g_Explain[0].bLook == true)
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_ExplainTexture[0]);
		}

		if (g_Explain[1].bLook == true)
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_ExplainTexture[1]);
		}
		if (g_Explain[2].bLook == true)
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_ExplainTexture[2]);
		}

		// �A�C�e��UI�̕`��
		pDevice->DrawPrimitive(
			D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
			nCnt * 4,				//�`�悷��ŏ��̒��_�C���f�b�N�X
			2						//�v���~�e�B�u�i�A�C�e��UI�j�̐�
		);
		
	}
	//=====================================================================//
}
//=============================================================================
// ����UI�̐ݒ菈��
//=============================================================================
void SetExplain(D3DXVECTOR3 pos, EXPLAINTYPE aType, float fWidth, float fHeight)
{
	// ���_���̃|�C���^
	VERTEX_2D* pVtx;

	// ���_�o�b�t�@�̃��b�N�A���_�f�[�^�ւ̃|�C���^�擾
	g_pVtxBuffExplain->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < EXPLAINTYPE_MAX; nCnt++)
	{
		if (g_Explain[nCnt].bUse == false)
		{// ���g�p��Ԃ�������
			g_Explain[nCnt].pos = pos;
			g_Explain[nCnt].aType = aType;
			g_Explain[nCnt].fHeight = fHeight;
			g_Explain[nCnt].fWidth = fWidth;
			g_Explain[nCnt].bLook = false;
			g_Explain[nCnt].bUse = true;

			// ���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_Explain[nCnt].pos.x - fWidth, g_Explain[nCnt].pos.y - fHeight, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_Explain[nCnt].pos.x + fWidth, g_Explain[nCnt].pos.y - fHeight, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_Explain[nCnt].pos.x - fWidth, g_Explain[nCnt].pos.y + fHeight, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_Explain[nCnt].pos.x + fWidth, g_Explain[nCnt].pos.y + fHeight, 0.0f);
			break;
		}
		pVtx += 4;
	}
	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffExplain->Unlock();
}

//=============================================================================
// �擾(�l��n��)����
//=============================================================================
EXPLAIN* GetExplain()
{
	return &g_Explain[0];
}
