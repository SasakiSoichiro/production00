//================================================
//
//		�^�C�g��	title.cpp
//
//			ryuusei.hirata
//================================================
#include "title.h"
#include "fade.h"
#include "camera.h"
#include "sound.h"

//	�}�N��
#define MAX_TITLE (3)

// �O���[�o��
LPDIRECT3DTEXTURE9 g_apTextureTitle[MAX_TITLE] = { NULL };			// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL;						// ���_�o�b�t�@�ւ̃|�C���^
Title g_aTitle[MAX_TITLE] = {};										// �^�C�g���\���̂̏��
TITLE g_Title;														// �^�C�g���񋓌^�̏��
int g_nCntTitleAnim;												// �^�C�g�����
int g_nPatternAnim;													// ��ԃp�^�[��
int ranking = 0;
int nSelect2 = 0;

//---------------
//	����������
//---------------
void InitTitle(void)
{
	// BGM��炷
	PlaySound(SOUND_LABEL_BGM);

	SetVolume(SOUND_LABEL_BGM,3.0f);

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	// �e�N�X�`���̓ǂݍ���(�^�C�g��) 
	D3DXCreateTextureFromFile(pDevice,
		"data\\texture\\title001.png",
		&g_apTextureTitle[0]);

	// �e�N�X�`���̓ǂݍ���(�`���[�g���A��)
	D3DXCreateTextureFromFile(pDevice,
		"data\\texture\\tutorial002.png",
		&g_apTextureTitle[1]);

	// �e�N�X�`���̓Ǎ�(�X�^�[�g)
	D3DXCreateTextureFromFile(pDevice,
		"data\\texture\\Start2.png",
		&g_apTextureTitle[2]);

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TITLE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTitle,
		NULL);

	VERTEX_2D* pVtx;

	// ���b�N
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntTitle = 0; nCntTitle < MAX_TITLE; nCntTitle++)
	{
		// �e��ϐ��̏�����
		g_aTitle[nCntTitle].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aTitle[nCntTitle].col = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aTitle[nCntTitle].nType = TITLE_ONE;
		g_aTitle[nCntTitle].fHeight = 0.0f;
		g_aTitle[nCntTitle].fWidth = 0.0f;
		g_aTitle[nCntTitle].bUse = false;
		g_aTitle[nCntTitle].state = TITLEMODE_NONE;//�������Ă��Ȃ����
	}

	g_nCntTitleAnim = 0;
	g_nPatternAnim = 0;
	ranking = 0;
	nSelect2 = 0;

	for (int nCnt = 0; nCnt < MAX_TITLE; nCnt++)
	{
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

		pVtx += 4;		// �厖
	}

	SetTitle(TITLE_ONE, D3DXVECTOR3(630.0f, 200.0f, 0.0f));		// �^�C�g��1
	SetTitle(TITLE_TWO, D3DXVECTOR3(650.0f, 440.0f, 0.0f));		// �^�C�g��2
	SetTitle(TITLE_THREE, D3DXVECTOR3(650.0f, 540.0f, 0.0f));	// �^�C�g��3

	// �A�����b�N
	g_pVtxBuffTitle->Unlock();
}

//---------------
//	�I������
//---------------
void UninitTitle(void)
{
	// ���y���~�߂�
	StopSound();

	UninitCamera();

	for (int nCnt = 0; nCnt < MAX_TITLE; nCnt++)
	{
		// �e�N�X�`���̔j��
		if (g_apTextureTitle[nCnt] != NULL)
		{
			g_apTextureTitle[nCnt]->Release();
			g_apTextureTitle[nCnt] = NULL;
		}
	}

	// ���_�o�b�t�@�̉��
	if (g_pVtxBuffTitle != NULL)
	{
		g_pVtxBuffTitle->Release();
		g_pVtxBuffTitle = NULL;
	}
}

//---------------
//	�X�V����
//---------------
void UpdateTitle(void)
{
	XINPUT_STATE* pStick;
	pStick = GetJoyStickAngle();

	//int Pad1, Pad2;
	//Pad1 = GetJoypadInputState(DX_INPUT_PAD1);

	//Pad2 = GetJoypadInputState(DX_INPUT_PAD2);

	XINPUT_STATE* pState = GetState();

	UpdateCamera();

	// �X�e�B�b�N��Ԃ̎擾
	VERTEX_2D* pVtx;

	// ���_�o�b�t�@�����b�N���A���傤�Ă���ւ̃|�C���^���擾
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntPause = 0; nCntPause < MAX_TITLE - 1; nCntPause++)
	{// ��x���ׂĂ𔼓�����
		// ���_�J���[�̐ݒ�
		pVtx[4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[5].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[6].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[7].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		pVtx += 4;
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTitle->Unlock();

	if (KeybordTrigger(DIK_W) == true || KeybordTrigger(DIK_UP) == true || OnMouseDown(MOUSE_L) == true || JoyPadTrigger(JOYKEY_UP) == true)//W
	{// ��I��
		nSelect2--;
	}
	else if (KeybordTrigger(DIK_S) == true || KeybordTrigger(DIK_DOWN) == true || OnMouseDown(MOUSE_R) == true || JoyPadTrigger(JOYKEY_DOWN) == true)//S
	{// ���I��
		nSelect2++;
	}
	
	////�Q�[���p�b�h1P
	//if (Pad1 & JOYKEY_DOWN)
	//{
	//	nSelect2++;
	//}
	//else if (Pad1 & JOYKEY_UP)
	//{
	//	nSelect2--;
	//}

	////�Q�[���p�b�h2P
	//if (Pad2 & JOYKEY_DOWN)
	//{
	//	nSelect2++;
	//}
	//else if (Pad2 & JOYKEY_UP)
	//{
	//	nSelect2--;
	//}

	// �͈͂𒴂��Ȃ��悤�ɂ���
	if (nSelect2 < MODE_TUTRIAL)
	{// �[����菬����
		nSelect2 = MODE_GAME;
	}
	else if (nSelect2 > MODE_GAME)
	{// �ő�l�ȏ�
		nSelect2 = MODE_TUTRIAL;
	}

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	// g_nSelect����Ƀ|���S����s�����ɂ���
	pVtx += 4 * nSelect2;

	// ���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.3f);
	pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.3f);
	pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.3f);
	pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.3f);

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTitle->Unlock();

	if (KeybordTrigger(DIK_RETURN) == true || JoyPadTrigger(JOYKEY_A) == true || OnMouseDown(MOUSE_L) == true)
	{// ����L�[�������ꂽ

		 // ���y��炷
		PlaySound(SOUND_LABEL_SE);

		// ���j���[�ɍ��킹�ă��[�h�̐؂�ւ�
		switch (nSelect2)
		{
			case MODE_TUTRIAL:
			SetFade(MODE_GAME);
			break;

			case MODE_GAME:
			SetFade(MODE_TUTRIAL);
			break;
		}
	}
}

//---------------
//	�`�揈��
//---------------
void DrawTitle(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTitle, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCnt = 0; nCnt < MAX_TITLE; nCnt++)
	{
		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_apTextureTitle[g_aTitle[nCnt].nType]);

		// �|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);
	}
}

//---------------
//	�z�u����
//---------------
void SetTitle(int nType, D3DXVECTOR3 pos)
{
	VERTEX_2D* pVtx;	// ���_���̃|�C���^

	// ���_�o�b�t�@�����b�N��,���_���ւ̃|�C���^���擾
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntTitle = 0; nCntTitle < MAX_TITLE; nCntTitle++)
	{
		if (g_aTitle[nCntTitle].bUse == false)
		{
			g_aTitle[nCntTitle].nType = nType;
			g_aTitle[nCntTitle].pos = pos;
			g_aTitle[nCntTitle].bUse = true;

			// �ꍇ����
			switch (nType)
			{
			case TITLE_ONE:

				g_aTitle[nCntTitle].fHeight = 180.0f;	// ����
				g_aTitle[nCntTitle].fWidth = 500.0f;	// ����
				break;

			case TITLE_TWO:

				g_aTitle[nCntTitle].fHeight = 100.0f;	// ����
				g_aTitle[nCntTitle].fWidth = 300.0f;	// ����
				break;

			case TITLE_THREE:
				g_aTitle[nCntTitle].fHeight = 100.0f;	// ����
				g_aTitle[nCntTitle].fWidth = 300.0f;	// ����

			}

			// ���_���W1�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aTitle[nCntTitle].pos.x - g_aTitle[nCntTitle].fWidth * 0.5f, g_aTitle[nCntTitle].pos.y - g_aTitle[nCntTitle].fHeight * 0.5f, 0.0f);	// 1�ڂ̒��_���
			pVtx[1].pos = D3DXVECTOR3(g_aTitle[nCntTitle].pos.x + g_aTitle[nCntTitle].fWidth * 0.5f, g_aTitle[nCntTitle].pos.y - g_aTitle[nCntTitle].fHeight * 0.5f, 0.0f);	// 2�ڂ̒��_���
			pVtx[2].pos = D3DXVECTOR3(g_aTitle[nCntTitle].pos.x - g_aTitle[nCntTitle].fWidth * 0.5f, g_aTitle[nCntTitle].pos.y + g_aTitle[nCntTitle].fHeight * 0.5f, 0.0f);	// 3�ڂ̒��_���
			pVtx[3].pos = D3DXVECTOR3(g_aTitle[nCntTitle].pos.x + g_aTitle[nCntTitle].fWidth * 0.5f, g_aTitle[nCntTitle].pos.y + g_aTitle[nCntTitle].fHeight * 0.5f, 0.0f);	// 4�ڂ̒��_���

			break;
		}
		pVtx += 4;
	}

	// �A�����b�N
	g_pVtxBuffTitle->Unlock();
}