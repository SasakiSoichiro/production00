//=============================================================================
//
//�@�G���_�̃r���[�|�[�g�̘g�̏��� [viewportwaku.cpp]
// �@Author : �ߓc����
//
//=============================================================================
#include "viewportwaku.h"
#include "enemy.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureViewUI = {};			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffViewUI = NULL;	//���_�o�b�t�@�ւ̃|�C���^
int g_nTimer;

//====================================
//�G���_�̃r���[�|�[�g�̘g�̏���������
//====================================
void InitViewUI(void)
{
	//���[�J���ϐ�
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^
	VERTEX_2D* pVtx;		//���_���ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\texture\\viewportFrame.png",
		&g_pTextureViewUI);

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,//(sizeof(VERTEX_2D)*�K�v�Ȓ��_��
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffViewUI,
		NULL);


	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffViewUI->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(430.0f, -20.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(820.0f, -20.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(430.0f, 220.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(820.0f, 220.0f, 0.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�@�@�@�@
	pVtx[0].col = D3DXCOLOR(0.0f,0.0f, 0.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(0.0f,0.0f, 0.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(0.0f,0.0f, 0.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(0.0f,0.0f, 0.0f, 1.0f);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffViewUI->Unlock();
}

//====================================
//�G���_�̃r���[�|�[�g�̘g�̏I������
//====================================
void UninitViewUI(void)
{

	//�e�N�X�`���̔j��
	if (g_pTextureViewUI != NULL)
	{
		g_pTextureViewUI->Release();
		g_pTextureViewUI = NULL;
	}


	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffViewUI != NULL)
	{
		g_pVtxBuffViewUI->Release();
		g_pVtxBuffViewUI = NULL;
	}

}

//====================================
//�G���_�̃r���[�|�[�g�̘g�̍X�V����
//====================================
void UpdateViewUI(void)
{
	bool pRange = IsRange(); // �G�̏���������

	g_nTimer += 1; // �^�C�}�[�̃J�E���g�A�b�v

	// ���[�J���ϐ�
	VERTEX_2D* pVtx; // ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffViewUI->Lock(0, 0, (void**)&pVtx, 0);

	// �G�̎��E��
	if (pRange == true)
	{
		// ���邳�̕ϓ��i�_�Ō��ʁj
		float fGlow = 0.5f + 0.5f * sinf(D3DXToRadian(g_nTimer * 36));  // 0.5�`1.0�͈̔͂œ_��

		// ���_�J���[�̐ݒ�@�@�@�@
		pVtx[0].col = D3DXCOLOR(fGlow, 0.8f, fGlow, 1.0f);
		pVtx[1].col = D3DXCOLOR(fGlow, 0.8f, fGlow, 1.0f);
		pVtx[2].col = D3DXCOLOR(fGlow, 0.8f, fGlow, 1.0f);
		pVtx[3].col = D3DXCOLOR(fGlow, 0.8f, fGlow, 1.0f);

	}
	// �G�̎��E�O
	else
	{
		// ���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
		pVtx[1].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
		pVtx[2].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
		pVtx[3].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);

	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffViewUI->Unlock();

	// �^�C�}�[�̃��Z�b�g
	if (g_nTimer >= 10) // �_�ő��x�̒���
	{
		g_nTimer = 0;
	}

}

//====================================
//�G���_�̃r���[�|�[�g�̘g�̕`�揈��
//====================================
void DrawViewUI(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffViewUI, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureViewUI);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

}
