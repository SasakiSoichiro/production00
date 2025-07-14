//=============================================================================
//
//	�����L���O�Z�b�g���� [rankingset.cpp]
// Author : ���X�ؑt��Y
//
//=============================================================================
#include "rankingset.h"
#include "input.h"
#include "fade.h"
//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureRank = {};//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRank = NULL;//���_�o�b�t�@�ւ̃|�C���^
int g_RankTimeCnt;
void InitRankingSet(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCnt;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();
	//�e�N�X�`���̓ǂݍ���
		//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\irekae.png",
		&g_pTextureRank);
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,//(sizeof(VERTEX_2D)*�K�v�Ȓ��_��
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRank,
		NULL);
	VERTEX_2D* pVtx;
	g_RankTimeCnt=0;
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffRank->Lock(0, 0, (void**)&pVtx, 0);
	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(250.0f, 90.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(400.0f, 90.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(250.0f, 560.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(400.0f, 560.0f, 0.0f);
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
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	/*	pVtx += 4;*/
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffRank->Unlock();
}
//�^�C�g����ʂ̏I������
void UninitRankingSet(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureRank != NULL)
	{
		g_pTextureRank->Release();
		g_pTextureRank = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffRank != NULL)
	{
		g_pVtxBuffRank->Release();
		g_pVtxBuffRank = NULL;
	}
}
//�^�C�g����ʂ̍X�V����
void UpdateRankingSet(void)
{
	g_RankTimeCnt++;
	if (g_RankTimeCnt>=300 ||KeyboardTrigger(DIK_RETURN) == true|| JoyPadTrigger(JOYKEY_A) == true)
	{//�G���^�[�L�[�������ꂽ
		//���[�h�ݒ�
		SetFade(MODE_TITLE);
	}

}
void DrawRankingSet(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^
	int nCntBG;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();
	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffRank, 0, sizeof(VERTEX_2D));
	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureRank);
	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}