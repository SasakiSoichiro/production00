//====================================================
//
// �X�^�~�i�̏��� [stamina.cpp]
// Author : Sasaki Soichiro
//
//====================================================

#include "stamina.h"
#include "player.h"
#include "enemy.h"

//�}�N����`
#define MAX_TIMEWIDTH (1000)
#define MAX_TIMEHEIGHT (10)

//�O���[�o���ϐ�
D3DXVECTOR3 StaminaPos;								// �X�^�~�i�̈ʒu
LPDIRECT3DTEXTURE9 g_StaminaTexture;				// �X�^�~�i�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffStamina = NULL;	// �o�b�t�@�ւ̃|�C���^
int g_nCntState;
bool bStamina;
bool bScreen;
int g_nStamina;

//====================================================
//�\���̏���������
//====================================================
void InitStamina()
{
	VERTEX_2D* pVtx=NULL;

	LPDIRECT3DDEVICE9 pDevice;					//�f�o�C�X�ւ̃|�C���^

	pDevice = GetDevice();						//�f�o�C�X�̎擾

	StaminaPos = D3DXVECTOR3(150.0f, 700.0f, 0.0f);

	bStamina = true;
	bScreen = false;

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\texture\\staminaFrame.png",
		&g_StaminaTexture);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4*STAMINA_MAX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffStamina, NULL);

	//���_�o�b�t�@�̃��b�N�A���_�f�[�^�ւ̃|�C���^�擾
	g_pVtxBuffStamina->Lock(0, 0, (void**)&pVtx, 0);

	// ���[�v����
	for (int nCntStamina = 0; nCntStamina <STAMINA_MAX; nCntStamina++)
	{// �u���b�N�̐������[�v����

		//���_���̐ݒ�
		pVtx[0].pos.x = StaminaPos.x - 0.0f;
		pVtx[0].pos.y = StaminaPos.y - MAX_TIMEHEIGHT;
		pVtx[0].pos.z = StaminaPos.z;
						
		pVtx[1].pos.x = StaminaPos.x + MAX_TIMEWIDTH;
		pVtx[1].pos.y = StaminaPos.y - MAX_TIMEHEIGHT;
		pVtx[1].pos.z = StaminaPos.z;
						
		pVtx[2].pos.x = StaminaPos.x - 0.0f;
		pVtx[2].pos.y = StaminaPos.y + MAX_TIMEHEIGHT;
		pVtx[2].pos.z = StaminaPos.z;
						
		pVtx[3].pos.x = StaminaPos.x + MAX_TIMEWIDTH;
		pVtx[3].pos.y = StaminaPos.y + MAX_TIMEHEIGHT;
		pVtx[3].pos.z = StaminaPos.z;

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		switch (nCntStamina)
		{
		case STAMINA_GAUGE:
			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(0.5f, 0.5f, 0.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(0.5f, 0.5f, 0.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(0.5f, 0.5f, 0.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(0.5f, 0.5f, 0.0f, 1.0f);
			break;
		case STAMINA_FRAME:
			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(0.6f, 0.6f, 0.6f, 1.0f);
			pVtx[1].col = D3DXCOLOR(0.6f, 0.6f, 0.6f, 1.0f);
			pVtx[2].col = D3DXCOLOR(0.6f, 0.6f, 0.6f, 1.0f);
			pVtx[3].col = D3DXCOLOR(0.6f, 0.6f, 0.6f, 1.0f);
			break;
		}

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffStamina->Unlock();
}

//====================================================
//�\���̏I������
//====================================================
void UninitStamina()
{

	// �e�N�X�`���̔j��
	if (g_StaminaTexture != NULL)
	{
		g_StaminaTexture->Release();
		g_StaminaTexture = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffStamina != NULL)
	{
		g_pVtxBuffStamina->Release();
		g_pVtxBuffStamina = NULL;
	}

}

//====================================================
//�\���̍X�V����
//====================================================
void UpdateStamina()
{
	Player* pPlayer = GetPlayer();
	bool pRange = IsRange();

	int nDate = 2;
	int aDate = 1;

	VERTEX_2D* pVtx=0;

	g_nStamina = pPlayer->nStamina;
	if (pPlayer->pState == PLAYERSTATE_DASH)
	{//�v���C���[�������Ă���Ƃ�

		if (pRange == false)
		{
			//�X�^�~�i�l�����炷
			pPlayer->nStamina--;

			if (pPlayer->nStamina <= 0)
			{//�X�^�~�i��0�ɂȂ����Ƃ�
				bStamina = false;
			}
		}
		else if (pRange == true)
		{
			//�X�^�~�i�l�����炷
			pPlayer->nStamina = pPlayer->nStamina - nDate;

			if (pPlayer->nStamina <= 0)
			{//�X�^�~�i��0�ɂȂ����Ƃ�
				bStamina = false;
			}
		}
	}
	else
	{
		if (pPlayer->nStamina <= 0)
		{//�X�^�~�i��0�ɂȂ����Ƃ�

			//�J�E���g����
			g_nCntState++;

			if (g_nCntState >= 120)
			{//120F��������
				pPlayer->nStamina = 1;

				//�J�E���g������������
				g_nCntState = 0;

				//�X�^�~�i���g����悤�ɂ���
				bStamina = true;
			}

		}
		else if (pPlayer->nStamina < 400)
		{//�X�^�~�i��100�����ő����Ă��Ȃ��Ƃ�

			if (pRange == false)
			{
				pPlayer->nStamina++;
			}
			else if (pRange == true)
			{
				pPlayer->nStamina = pPlayer->nStamina + aDate;
			}
		}

	}

	float fStamina = (float(MAX_TIMEWIDTH)/400)*pPlayer->nStamina;
	//���_�o�b�t�@�̃��b�N�A���_�f�[�^�ւ̃|�C���^�擾
	g_pVtxBuffStamina->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < STAMINA_MAX; nCnt++)
	{
		switch (nCnt)
		{
		case STAMINA_GAUGE:
			pVtx[0].pos.x = StaminaPos.x;
			pVtx[1].pos.x = StaminaPos.x + fStamina;
			pVtx[2].pos.x = StaminaPos.x;
			pVtx[3].pos.x = StaminaPos.x + fStamina;
			break;
		case STAMINA_FRAME:
			pVtx[0].pos.x = StaminaPos.x;
			pVtx[1].pos.x = StaminaPos.x + MAX_TIMEWIDTH;
			pVtx[2].pos.x = StaminaPos.x;
			pVtx[3].pos.x = StaminaPos.x + MAX_TIMEWIDTH;

			break;
		}
		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffStamina->Unlock();

	if (g_nStamina == pPlayer->nStamina)
	{
		bScreen = false;
	}
	else
	{
		bScreen = true;
	}

}

//====================================================
//�\���̕`�揈��
//====================================================
void DrawStamina()
{
	LPDIRECT3DDEVICE9 pDevice;					//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffStamina, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCnt = 0; nCnt < STAMINA_MAX; nCnt++)
	{
		if (bScreen == true)
		{
			switch (nCnt)
			{
			case STAMINA_GAUGE:
				//�|���S���̕`��
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4*nCnt, 2);
				break;
			case STAMINA_FRAME:

				//// �e�N�X�`���̐ݒ�
				//pDevice->SetTexture(0, g_StaminaTexture);

				////�|���S���̕`��
				//pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4, 2);
				break;

			}

		}

	}


}
bool GetStamina(void)
{
	return bStamina;
}