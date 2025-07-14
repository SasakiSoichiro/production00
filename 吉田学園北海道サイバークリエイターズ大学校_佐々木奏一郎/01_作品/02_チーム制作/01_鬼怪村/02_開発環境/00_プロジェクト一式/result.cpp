//====================================================
//
//			���U���g			result.cpp
//				ryuusei.hirata
//
//=====================================================
#include "result.h"
#include "fade.h"
#include "player.h"
#include "time.h"

//	�O���[�o��
LPDIRECT3DTEXTURE9 g_apTextureResult = NULL;			// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResult = NULL;		// ���_�o�b�t�@�ւ̃|�C���^

//---------------
//	����������
//---------------
void InitResult(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	Player* pPlayer = GetPlayer();
	int nTime = GetMin();

	if (pPlayer->nLife > 0)
	{
		// �e�N�X�`���̓ǂݍ���(�N���A)
		D3DXCreateTextureFromFile(pDevice,
			"data\\texture\\GameClear.png",
			&g_apTextureResult);
	}
	else
	{
		// �e�N�X�`���̓ǂݍ���(�Q�[���I�[�o�[)
		D3DXCreateTextureFromFile(pDevice,
			"data\\texture\\GameOver1.png",
			&g_apTextureResult);
	}

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffResult,
		NULL);

	VERTEX_2D* pVtx;

	// ���b�N
	g_pVtxBuffResult->Lock(0, 0, (void**)&pVtx, 0);

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
	g_pVtxBuffResult->Unlock();
}

//---------------
//	�I������
//---------------
void UninitResult(void)
{
	// �e�N�X�`���̔j��
	if (g_apTextureResult != NULL)
	{
		g_apTextureResult->Release();
		g_apTextureResult = NULL;
	}

	// ���_�o�b�t�@�̉��
	if (g_pVtxBuffResult != NULL)
	{
		g_pVtxBuffResult->Release();
		g_pVtxBuffResult = NULL;
	}
}

//---------------
//	�X�V����
//----------------
void UpdateResult(void)
{
	if (KeybordTrigger(DIK_RETURN) || GetJoypadPress(JOYKEY_A) == true || OnMouseDown(MOUSE_L) == true)
	{// �G���^�[�������ꂽ��
		SetFade(MODE_RANKING);
	}
}

//---------------
//	�`�揈��
//---------------
void DrawResult(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffResult, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_apTextureResult);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}