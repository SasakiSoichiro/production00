//--------------------------
//
// �|�[�Y
//
//--------------------------
#include "pause.h"
#include "input.h"
#include "main.h"
#include "game.h"
#include "fade.h"
#include "result.h"

//===============
// �}�N��
//===============
#define MAX_PAUSE (3)
#define MAX_MENU_HIGHT (100)
#define MAX_MENU_WID (300)

//===============
// �O���[�o��
//===============
//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTexturePause[MAX_PAUSE] = { NULL };
//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPause = NULL;

//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTexturePause2 = NULL;
// ����
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPause2 = NULL;

Pause g_aPause[MAX_PAUSE];
int nSelect;

//===============================
// ����������
//===============================
void InitPause(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\texture\\contene1.png",
		&g_pTexturePause[0]);

	//	�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\texture\\retry1.png",
		&g_pTexturePause[1]);

	//	�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\texture\\quit1.png",
		&g_pTexturePause[2]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\texture\\usukawa.png",
		&g_pTexturePause2);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_PAUSE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPause,
		NULL);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPause2,
		NULL);

	VERTEX_2D* pVtx;
	//���b�N
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

	nSelect = PAUSEMENYU_COTINUE;

	for (int nCnt = 0; nCnt < MAX_PAUSE; nCnt++)
	{
		g_aPause[nCnt].pos = D3DXVECTOR3(650.0f, 250.0f + nCnt * MAX_MENU_HIGHT, 0.0f);

		//���_���W�̐ݒ�
		pVtx[0].pos.x = g_aPause[nCnt].pos.x - MAX_MENU_WID / 2;
		pVtx[0].pos.y = g_aPause[nCnt].pos.y - MAX_MENU_HIGHT / 2;
		pVtx[0].pos.z = 0.0f;
		pVtx[1].pos.x = g_aPause[nCnt].pos.x + MAX_MENU_WID / 2;
		pVtx[1].pos.y = g_aPause[nCnt].pos.y - MAX_MENU_HIGHT / 2;
		pVtx[1].pos.z = 0.0f;
		pVtx[2].pos.x = g_aPause[nCnt].pos.x - MAX_MENU_WID / 2;
		pVtx[2].pos.y = g_aPause[nCnt].pos.y + MAX_MENU_HIGHT / 2;
		pVtx[2].pos.z = 0.0f;
		pVtx[3].pos.x = g_aPause[nCnt].pos.x + MAX_MENU_WID / 2;
		pVtx[3].pos.y = g_aPause[nCnt].pos.y + MAX_MENU_HIGHT / 2;
		pVtx[3].pos.z = 0.0f;

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�e�N�X�`�����W�̐ݒ�@�@�P�Q�T
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		// �厖
		pVtx += 4;
	}

	//�A�����b�N
	g_pVtxBuffPause->Unlock();

	// ���b�N
	g_pVtxBuffPause2->Lock(0, 0, (void**)&pVtx, 0);

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

	//���_�J���[
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�e�N�X�`�����W�̐ݒ�@�@�P�Q�T
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//�A�����b�N
	g_pVtxBuffPause2->Unlock();

}
//=============
// �I��
//============
void UninitPause(void)
{
	for (int nCnt = 0; nCnt < MAX_PAUSE; nCnt++)
	{
		if (g_pTexturePause[nCnt] != NULL)
		{
			g_pTexturePause[nCnt]->Release();
			g_pTexturePause[nCnt] = NULL;
		}
	}

	if (g_pVtxBuffPause != NULL)
	{
		g_pVtxBuffPause->Release();
		g_pVtxBuffPause = NULL;
	}

	if (g_pTexturePause2 != NULL)
	{
		g_pTexturePause2->Release();
		g_pTexturePause2 = NULL;
	}

	if (g_pVtxBuffPause2 != NULL)
	{
		g_pVtxBuffPause2->Release();
		g_pVtxBuffPause2 = NULL;
	}

}
//==========================
// �X�V
//=========================
void UpdatePause(void)
{
	int nCntPause;

	//�X�e�B�b�N��Ԃ̎擾
	VERTEX_2D* pVtx;

	// ���b�N
	g_pVtxBuffPause2->Lock(0, 0, (void**)&pVtx, 0);

	//���_�J���[
	pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.8f);
	pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.8f);
	pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.8f);
	pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.8f);

	//�A�����b�N
	g_pVtxBuffPause2->Unlock();

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntPause = 0; nCntPause < MAX_PAUSE; nCntPause++)
	{//��x���ׂĂ𔼓�����
		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);

		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPause->Unlock();

	if (KeybordTrigger(DIK_W) || KeybordTrigger(DIK_UP) || JoyPadTrigger(JOYKEY_UP) == true)//W&��
	{//W�L�[�������ꂽ
		nSelect--;
	}
	else if (KeybordTrigger(DIK_S) || KeybordTrigger(DIK_DOWN) || JoyPadTrigger(JOYKEY_DOWN) == true)//S&��
	{//S�L�[�������ꂽ
		nSelect++;
	}

	//�͈͂𒴂��Ȃ��悤�ɂ���
	if (nSelect < 0)
	{//�[����菬����
		nSelect = PAUSEMENYU_COTINUE;
	}
	else if (nSelect >= PAUSEMENYU_MAX)
	{//�ő�l�ȏ�
		nSelect = PAUSEMENYU_QUIT;
	}

	//���_�o�b�t�@�����b�N���A���傤�Ă���ւ̃|�C���^���擾
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

	//g_nSelect����Ƀ|���S����s�����ɂ���
	pVtx += 4 * nSelect;

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPause->Unlock();

	if (KeybordTrigger(DIK_RETURN) || JoyPadTrigger(JOYKEY_A) == true || OnMouseDown(MOUSE_L) == true)
	{//����L�[�������ꂽ
		//���j���[�ɍ��킹�ă��[�h�̐؂�ւ�
		switch (nSelect)
		{
		case PAUSEMENYU_COTINUE:
			SetEnablePause(false);
			break;

		case PAUSEMENYU_RETRY:
			SetEnablePause(false);
			SetFade(MODE_GAME);
			break;

		case PAUSEMENYU_QUIT:
			SetEnablePause(false);
			SetFade(MODE_TITLE);
			break;
		}
	}
}
//================
// �`��
//===============
void DrawPause(void)
{
	//�f���@�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPause2, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTexturePause2);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPause, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCnt = 0; nCnt < MAX_PAUSE; nCnt++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTexturePause[nCnt]);

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);
	}
}
