//=============================================================================
//
//�@�m�C�Y���� [noise.cpp]
// �@Author : ���X�ؑt��Y
//
//=============================================================================
#include "noise.h"
#define MAX_NOISE (3)
//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureNoise[NOISE_MAX] = {};		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffNoise = NULL;			//���_�o�b�t�@�ւ̃|�C���^
Noise g_Noise[MAX_NOISE];
int g_nCnt;
float g_aPosTexU[3];//�e�N�X�`���̊J�n�ʒu(U�l)
float g_aPosTexV[3];//�e�N�X�`���̊J�n�ʒu(U�l)


//=============================================================================
//�m�C�Y�̏���������
//=============================================================================
void InitNoise(void)
{
	//���[�J���ϐ�
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^
	VERTEX_2D* pVtx = 0;		//���_���ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();
	for (int nCnt = 0; nCnt < NOISE_MAX; nCnt++)
	{
		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,
			NOISE_TEXTURE[nCnt],
			&g_pTextureNoise[nCnt]);
	}


	//���[�v����
	for (int nCntNoise = 0; nCntNoise < MAX_NOISE; nCntNoise++)
	{
		g_Noise[nCntNoise].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ʒu������������
		g_Noise[nCntNoise].fWidth = 0.0f;							//��������������
		g_Noise[nCntNoise].fHeight = 0.0f;							//����������������
		g_Noise[nCntNoise].nType = nCntNoise;						//��ނ�����������
		g_Noise[nCntNoise].bUse = false;							//�g���Ă��Ȃ���Ԃɂ���
		g_aPosTexU[nCntNoise] = 0.0f;
		g_aPosTexV[nCntNoise] = 0.0f;

	}



	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4*MAX_NOISE,//(sizeof(VERTEX_2D)*�K�v�Ȓ��_��
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffNoise,
		NULL);



	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffNoise->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCnt = 0; nCnt < MAX_NOISE; nCnt++)
	{
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

		// ���_�J���[�̐ݒ�@�@�@�@
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);

		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(g_aPosTexU[nCnt], g_aPosTexV[nCnt]);
		pVtx[1].tex = D3DXVECTOR2(g_aPosTexU[nCnt]+1.0f, g_aPosTexV[nCnt]);
		pVtx[2].tex = D3DXVECTOR2(g_aPosTexU[nCnt], g_aPosTexV[nCnt]+1.0f);
		pVtx[3].tex = D3DXVECTOR2(g_aPosTexU[nCnt]+1.0f, g_aPosTexV[nCnt]+1.0f);

		pVtx += 4;
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffNoise->Unlock();
}

//=============================================================================
//�m�C�Y�̏I������
//=============================================================================
void UninitNoise(void)
{
	for (int nCnt = 0; nCnt < NOISE_MAX; nCnt++)
	{
		//�e�N�X�`���̔j��
		if (g_pTextureNoise[nCnt] != NULL)
		{
			g_pTextureNoise[nCnt]->Release();
			g_pTextureNoise[nCnt] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffNoise != NULL)
	{
		g_pVtxBuffNoise->Release();
		g_pVtxBuffNoise = NULL;
	}

}

//=============================================================================
//�m�C�Y�̍X�V����
//=============================================================================
void UpdateNoise(void)
{

	VERTEX_2D* pVtx = 0;		//���_���ւ̃|�C���^



	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffNoise->Lock(0, 0, (void**)&pVtx, 0);

	RandNoise(&g_aPosTexU[0], &g_aPosTexV[0],0);

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(g_aPosTexU[0], g_aPosTexV[0]);
	pVtx[1].tex = D3DXVECTOR2(g_aPosTexU[0] + 1.0f, g_aPosTexV[0]);
	pVtx[2].tex = D3DXVECTOR2(g_aPosTexU[0], g_aPosTexV[0] + 1.0f);
	pVtx[3].tex = D3DXVECTOR2(g_aPosTexU[0] + 1.0f, g_aPosTexV[0] + 1.0f);

	pVtx += 4;

	RandNoise(&g_aPosTexU[1], &g_aPosTexV[1],1);
	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(g_aPosTexU[1], g_aPosTexV[1]);
	pVtx[1].tex = D3DXVECTOR2(g_aPosTexU[1] + 1.0f, g_aPosTexV[1]);
	pVtx[2].tex = D3DXVECTOR2(g_aPosTexU[1], g_aPosTexV[1] + 1.0f);
	pVtx[3].tex = D3DXVECTOR2(g_aPosTexU[1] + 1.0f, g_aPosTexV[1] + 1.0f);

	pVtx += 4;

	RandNoise(&g_aPosTexU[2], &g_aPosTexV[2],2);
	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(g_aPosTexU[2], g_aPosTexV[2]);
	pVtx[1].tex = D3DXVECTOR2(g_aPosTexU[2] + 1.0f, g_aPosTexV[2]);
	pVtx[2].tex = D3DXVECTOR2(g_aPosTexU[2], g_aPosTexV[2] + 1.0f);
	pVtx[3].tex = D3DXVECTOR2(g_aPosTexU[2] + 1.0f, g_aPosTexV[2] + 1.0f);

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffNoise->Unlock();

	g_nCnt++;
}

//=============================================================================
//�m�C�Y�̕`�揈��
//=============================================================================
void DrawNoise(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^

	// �f�o�C�X�̎擾
	pDevice = GetDevice();
	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffNoise, 0, sizeof(VERTEX_2D));
	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntNoise = 0; nCntNoise < MAX_NOISE; nCntNoise++)
	{
		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(NOISE_A, g_pTextureNoise[g_Noise[nCntNoise].nType]);
		pDevice->SetTexture(NOISE_B, g_pTextureNoise[g_Noise[nCntNoise].nType]);
		pDevice->SetTexture(NOISE_C, g_pTextureNoise[g_Noise[nCntNoise].nType]);

		// �|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,4*nCntNoise , 2);

	}

}

//=============================================================================
//�����_���ȓ����������鏈��
//=============================================================================
void RandNoise(float *U, float *V ,int nCnt)
{
	int nRand[MAX_NOISE] = {};

	nRand[nCnt] = rand() % 6;
	g_nCnt = 0;

	
	switch (nRand[nCnt])
	{
	case 0:
		*U += 0.025f;
		*V += 0.025f;
		break;
	case 1:
		*U += 0.0025f;
		break;
	case 2:
		*U += 0.0065f;
		*V -= 0.0025f;
		break;
	case 3:
		*U += 0.05f;
		*V -= 0.0025f;
		break;
	case 4:
		*U -= 0.0025f;
		break;
	case 5:
		*U -= 0.0025f;
		*V -= 0.085f;
		break;
	}

}