//=========================================
//
//		�`���[�g���A��		tutrial.cpp
//
//			hirata ryuusei
//
//=========================================
#include "tutrial.h"
#include "input.h"
#include "fade.h"

// �O���[�o��
LPDIRECT3DTEXTURE9 g_apTextureTutrial = NULL;			// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTutrial = NULL;		// ���_�o�b�t�@�ւ̃|�C���^

// ����������
void InitTutrial(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	// �e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\texture\\tutrial000.png",
		&g_apTextureTutrial);

	// ���_�o�b�t�@
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTutrial,
		NULL);

	VERTEX_2D* pVtx;
	
	// ���b�N
	g_pVtxBuffTutrial->Lock(0, 0, (void**)&pVtx, 0);

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
	g_pVtxBuffTutrial->Unlock();
}

// �I������
void UninitTutrial(void)
{
	// �e�N�X�`���̔j��
	if (g_apTextureTutrial != NULL)
	{
		g_apTextureTutrial->Release();
		g_apTextureTutrial = NULL;
	}

	//���_�o�b�t�@�̉��
	if (g_pVtxBuffTutrial != NULL)
	{
		g_pVtxBuffTutrial->Release();
		g_pVtxBuffTutrial = NULL;
	}
}

// �X�V����
void UpdateTutrial(void)
{
	if (KeybordTrigger(DIK_RETURN) || GetJoypadPress(JOYKEY_A) == true || OnMouseDown(MOUSE_L) == true)
	{// �G���^�[�������ꂽ��
		SetFade(MODE_GAME);
	}
}

// �`�揈��
void DrawTutrial(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTutrial, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_apTextureTutrial);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}