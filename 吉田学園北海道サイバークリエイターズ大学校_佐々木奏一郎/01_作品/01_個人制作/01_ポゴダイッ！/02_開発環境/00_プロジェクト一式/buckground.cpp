//=============================================================================
//
//	�o�b�N�O���E���h���� [background.cpp]
// Author : ���X�ؑt��Y
//
//=============================================================================
#include "main.h"
#include "buckground.h"
#include "stageselect.h"
//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureBuckground = {};//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBuckground = NULL;//���_�o�b�t�@�ւ̃|�C���^
float g_aPosTexU;//�e�N�X�`���̊J�n�ʒu(U�l)

//�|���S���̏���������
void InitBuckground(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^
	int nCntBG;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();
	int nStage= GetStageSelect();
	if (nStage == 9)
	{
		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,
			"data\\TEXTURE\\back002.png",
			&g_pTextureBuckground);
	}
	else
	{
		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,
			"data\\TEXTURE\\back001.png",
			&g_pTextureBuckground);
	}

	//�e�N�X�`�����W�̊J�n�ʒu(U�l)�̏�����
	g_aPosTexU= 0.0f;

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,//(sizeof(VERTEX_2D)*�K�v�Ȓ��_��
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBuckground,
		NULL);
	VERTEX_2D* pVtx;//���_���ւ̃|�C���^
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBuckground->Lock(0, 0, (void**)&pVtx, 0);

		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//���E���Őݒ肷��
		pVtx[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);
		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		//���_�J���[�̐ݒ�@�@�@�@
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(g_aPosTexU, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(g_aPosTexU + 1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(g_aPosTexU, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(g_aPosTexU + 1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBuckground->Unlock();
}
//�|���S���̏I������
void UninitBuckground(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureBuckground != NULL)
	{
		g_pTextureBuckground->Release();
		g_pTextureBuckground = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffBuckground != NULL)
	{
		g_pVtxBuffBuckground->Release();
		g_pVtxBuffBuckground = NULL;
	}
}
//�|���S���̍X�V����
void UpdateBuckground(void)
{
	//int nCntBG;
	//VERTEX_2D*pVtx{};
	////���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	//g_pVtxBuffBuckground->Lock(0, 0, (void**)&pVtx, 0);
	////�e�N�X�`�����W�̊J�n�ʒu(U�l)�̍X�V
	//g_aPosTexU += 0.00025;
	//	//�e�N�X�`�����W�̍X�V
	//	//rhw�̐ݒ�
	//	pVtx[0].rhw = 1.0f;
	//	pVtx[1].rhw = 1.0f;
	//	pVtx[2].rhw = 1.0f;
	//	pVtx[3].rhw = 1.0f;
	//	//���_�J���[�̐ݒ�@�@�@�@
	//	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 190);
	//	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 190);
	//	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 190);
	//	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 190);
	//	//�e�N�X�`�����W�̐ݒ�
	//	pVtx[0].tex = D3DXVECTOR2(g_aPosTexU, 0.0f);
	//	pVtx[1].tex = D3DXVECTOR2(g_aPosTexU + 1.0f, 0.0f);
	//	pVtx[2].tex = D3DXVECTOR2(g_aPosTexU, 1.0f);
	//	pVtx[3].tex = D3DXVECTOR2(g_aPosTexU + 1.0f, 1.0f);

	////���_�o�b�t�@���A�����b�N����
	//g_pVtxBuffBuckground->Unlock();
}
//�|���S���̕`�揈��
void DrawBuckground(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffBuckground, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureBuckground);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

}