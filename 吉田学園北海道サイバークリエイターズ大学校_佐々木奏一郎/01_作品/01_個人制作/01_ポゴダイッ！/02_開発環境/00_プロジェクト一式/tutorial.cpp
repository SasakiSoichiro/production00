//=============================================================================
//
//	���U���g���� [result.cpp]
// Author : ���X�ؑt��Y
//
//=============================================================================
#include "tutorial.h"
#include "result.h"
#include "main.h"
#include "input.h"
#include "fade.h"
#include "player.h"
#include "sound.h"
//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureTutorial = NULL;//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTutorial = NULL;//���_�o�b�t�@�ւ̃|�C���^
//�^�C�g����ʂ̏���������
void InitTutorial(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,
			"data\\TEXTURE\\tutorial.png",
			&g_pTextureTutorial);
	//���_�o�b�t�@�̐����B���_���̐ݒ�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,//(sizeof(VERTEX_2D)*�K�v�Ȓ��_��
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTutorial,
		NULL);

	VERTEX_2D* pVtx;//���_���ւ̃|�C���^
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTutorial->Lock(0, 0, (void**)&pVtx, 0);
	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
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
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTutorial->Unlock();
}
//�^�C�g����ʂ̏I������
void UninitTutorial(void)
{
	//�T�E���h���~
	StopSound();
	//�e�N�X�`���̔j��
	if (g_pTextureTutorial != NULL)
	{
		g_pTextureTutorial->Release();
		g_pTextureTutorial = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffTutorial != NULL)
	{
		g_pVtxBuffTutorial->Release();
		g_pVtxBuffTutorial = NULL;
	}
}
//�^�C�g����ʂ̍X�V����
void UpdateTutorial(void)
{
	if (KeyboardTrigger(DIK_RETURN) == true)
	{//�G���^�[�L�[�������ꂽ
		//���[�h�ݒ�
		SetFade(MODE_STAGESELECT);
	}
	if (JoyPadTrigger(JOYKEY_A) == true)
	{//�G���^�[�L�[�������ꂽ
		//���[�h�ݒ�
		SetFade(MODE_STAGESELECT);
	}
}
//�^�C�g����ʂ̕`�揈��
void DrawTutorial(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^
	int nCntBG;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();
	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTutorial, 0, sizeof(VERTEX_2D));
	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureTutorial);
	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}