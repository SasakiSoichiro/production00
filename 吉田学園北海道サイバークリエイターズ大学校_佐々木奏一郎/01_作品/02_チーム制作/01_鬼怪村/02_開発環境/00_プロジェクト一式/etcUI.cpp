//=============================================================================
//
//�@2D�\��������UI���� [etcUI.cpp]
// �@Author : ���X�ؑt��Y
//
//=============================================================================
#include "etcUI.h"

// �O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureEtcUI[ETCUI_MAX] = {};		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEtcUI = NULL;			// ���_�o�b�t�@�ւ̃|�C���^
EtcUI g_aEtcUI[ETCUI_MAX];								// �u���b�N�̏��

//=============================================================================
// �A�C�e��UI�̏���������
//=============================================================================
void InitEtcUI(void)
{
	// ���[�J���ϐ�
	LPDIRECT3DDEVICE9 pDevice;	// �f�o�C�X�ւ̃|�C���^
	VERTEX_2D* pVtx = 0;		// ���_���ւ̃|�C���^

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	for (int nCnt = 0; nCnt < ETCUI_MAX; nCnt++)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,
			ETCUI_TEXTURE[nCnt],
			&g_pTextureEtcUI[nCnt]);
	}

	// ���[�v����
	for (int nCntBlock = 0; nCntBlock < ETCUI_MAX; nCntBlock++)
	{// �u���b�N�̐������[�v����

		g_aEtcUI[nCntBlock].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ʒu������������
		g_aEtcUI[nCntBlock].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ړ��l������������
		g_aEtcUI[nCntBlock].fWidth = 0.0f;							// ��������������
		g_aEtcUI[nCntBlock].fHeight = 0.0f;							// ����������������
		g_aEtcUI[nCntBlock].nType = ETCUI_MAX;						// ��ނ�����������
		g_aEtcUI[nCntBlock].bUse = false;							// �g���Ă��Ȃ���Ԃɂ���	
	}

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * ETCUI_MAX,	// (sizeof(VERTEX_2D)*�K�v�Ȓ��_��
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEtcUI,
		NULL);

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffEtcUI->Lock(0, 0, (void**)&pVtx, 0);

	// ���[�v����
	for (int nCntBlock = 0; nCntBlock < ETCUI_MAX; nCntBlock++)
	{// �u���b�N�̐������[�v����

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

		// ���_�J���[�̐ݒ�@�@�@�@
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.4f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.4f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.4f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.4f);

		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;			// ���_�f�[�^�̃|�C���^��4���W�߂�
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEtcUI->Unlock();
}

//=============================================================================
// �A�C�e��UI�̏I������
//=============================================================================
void UninitEtcUI(void)
{
	for (int nCnt = 0; nCnt < ETCUI_MAX; nCnt++)
	{
		// �e�N�X�`���̔j��
		if (g_pTextureEtcUI[nCnt] != NULL)
		{
			g_pTextureEtcUI[nCnt]->Release();
			g_pTextureEtcUI[nCnt] = NULL;
		}
	}

	// ���_�o�b�t�@�̔j��
	if (g_pVtxBuffEtcUI != NULL)
	{
		g_pVtxBuffEtcUI->Release();
		g_pVtxBuffEtcUI = NULL;
	}
}

//=============================================================================
// �A�C�e��UI�̍X�V����
//=============================================================================
void UpdateEtcUI()
{

}

//=============================================================================
// �A�C�e��UI�̕`�揈��
//=============================================================================
void DrawEtcUI(void)
{
	LPDIRECT3DDEVICE9 pDevice;		// �f�o�C�X�ւ̃|�C���^

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffEtcUI, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// ���[�v����
	for (int nCntItemUI = 0; nCntItemUI < ETCUI_MAX; nCntItemUI++)
	{// �u���b�N�̐������[�v����
		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(ETCUI_DASH, g_pTextureEtcUI[g_aEtcUI[nCntItemUI].nType]);
		pDevice->SetTexture(ETCUI_KEY, g_pTextureEtcUI[g_aEtcUI[nCntItemUI].nType]);
		pDevice->SetTexture(ETCUI_MASTER, g_pTextureEtcUI[g_aEtcUI[nCntItemUI].nType]);

		// �|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntItemUI, 2);
	}
}

//=============================================================================
// �A�C�e��UI�̐ݒ菈��
//=============================================================================
void SetEtcUI(int nType,D3DXVECTOR3 pos,float fHeight,float fWidth)
{
	// ���_���̃|�C���^
	VERTEX_2D* pVtx;

	// ���_�o�b�t�@�̃��b�N�A���_�f�[�^�ւ̃|�C���^�擾
	g_pVtxBuffEtcUI->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < ETCUI_MAX; nCnt++)
	{
		if (g_aEtcUI[nCnt].bUse == false)
		{// ���g�p��Ԃ�������
			g_aEtcUI[nCnt].pos = pos;
			g_aEtcUI[nCnt].nType = nType;
			g_aEtcUI[nCnt].fHeight = fHeight;
			g_aEtcUI[nCnt].fWidth = fWidth;
			g_aEtcUI[nCnt].bUse = true;

			// ���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aEtcUI[nCnt].pos.x - fWidth, g_aEtcUI[nCnt].pos.y - fHeight, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aEtcUI[nCnt].pos.x + fWidth, g_aEtcUI[nCnt].pos.y - fHeight, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aEtcUI[nCnt].pos.x - fWidth, g_aEtcUI[nCnt].pos.y + fHeight, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEtcUI[nCnt].pos.x + fWidth, g_aEtcUI[nCnt].pos.y + fHeight, 0.0f);

			break;
		}
		pVtx += 4;
	}

	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffEtcUI->Unlock();
}