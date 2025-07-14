//=============================================================================
//
//	�^�C������ [time.cpp]
// Author : ���X�ؑt��Y
//
//=============================================================================
#include "time.h"
#include "score.h"
#include "player.h"
#include "block.h"
#include "fade.h"
typedef struct
{
	bool bUse;

}Time;
//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureTime = NULL;//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTime = NULL;//���_�o�b�t�@�ւ̃|�C���^
D3DXVECTOR3 g_posTime;//�X�R�A�̈ʒu
int g_nTime;//�X�R�A�̒l
Time g_aTime[MAX_TIME];
int g_nTimeSecond;
//====================
//�X�R�A�̏���������
//====================
void InitTime(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCnt;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\number002.png",
		&g_pTextureTime);
	g_posTime = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�ʒu������������
	g_nTime = 120;//�l������������

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TIME,//(sizeof(VERTEX_2D)*�K�v�Ȓ��_��
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTime,
		NULL);
	VERTEX_2D* pVtx;
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTime->Lock(0, 0, (void**)&pVtx, 0);
	for (nCnt = 0; nCnt < MAX_TIME; nCnt++)
	{
		g_aTime[nCnt].bUse = true;
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(600.0f + nCnt * 30.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(600.0f + nCnt * 30.0f + 30.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(600.0f + nCnt * 30.0f, 50.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(600.0f + nCnt * 30.0f + 30.0f, 50.0f, 0.0f);
		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		//���_�J���[�̐ݒ�@�@�@�@
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);//���E���Őݒ肷��
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);
		pVtx += 4;//���_�f�[�^�̃|�C���^��4���W�߂�
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTime->Unlock();
}
//====================
//�X�R�A�̏I������
//====================
void UninitTime(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureTime != NULL)
	{
		g_pTextureTime->Release();
		g_pTextureTime = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffTime != NULL)
	{
		g_pVtxBuffTime->Release();
		g_pVtxBuffTime = NULL;
	}
}
//===================
//�X�R�A�̍X�V����
//===================
void UpdateTime(void)
{
	int nData1, nData2, aPosTexU[MAX_TIME] = {},nCnt;

	VERTEX_2D* pVtx;

	bool goal = GetGoal();

	nData1 = 100;//���߂��X�R�A�̌����ۑ�
	nData2 = 10;
	g_nTimeSecond++;
	if (goal == false)
	{
		if (g_nTimeSecond >= 60)
		{
			g_nTimeSecond = 0;
			if (g_nTime != 0)
			{
				g_nTime--;
				AddScore(-5);
			}
			else if (g_nTime <= 0)
			{
				SetFade(MODE_GAME);
			}
		}
	}

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTime->Lock(0, 0, (void**)&pVtx, 0);
	for (nCnt = 0; nCnt < MAX_TIME; nCnt++)
	{
		if (nCnt == 0)
		{
			aPosTexU[0] = g_nTime / nData1;
		}
		else
		{
			aPosTexU[nCnt] = g_nTime % nData1 / nData2;
			nData1 = nData1 / 10;
			nData2 = nData2 / 10;
		}
		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f + (0.1f * aPosTexU[nCnt]), 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f + (0.1f * aPosTexU[nCnt]), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + (0.1f * aPosTexU[nCnt]), 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f + (0.1f * aPosTexU[nCnt]), 1.0f);
		pVtx += 4;//���_�f�[�^�̃|�C���^��4���W�߂�
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTime->Unlock();
}
//==================
// �X�R�A�̕`�揈��
//==================
void DrawTime(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^
	int nCnt;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();
	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTime, 0, sizeof(VERTEX_2D));
	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	VERTEX_2D* pVtx;
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTime->Lock(0, 0, (void**)&pVtx, 0);
	for (nCnt = 0; nCnt < MAX_TIME; nCnt++)
	{
		if (g_aTime[nCnt].bUse == true)
		{
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureTime);
			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCnt, 2);
		}
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTime->Unlock();
}
//===================
// �X�R�A�̉��Z����
//===================
int TimeCnt(int nTime)
{
	int nNum = nTime;//�X�R�A�̂O�̕������J�E���g
	int nKeepNum = 0;//�X�R�A�̌���
	for (int nCnt = 0; nCnt < MAX_TIME; nCnt++)
	{
		if (nNum == 0)
		{
			for (int nCnt2 = 0; nCnt < nKeepNum; nCnt2++)
			{
				g_aTime[nCnt2].bUse = true;
			}
		}
		else
		{
			nNum /= 10;//10�Ŋ���
			nKeepNum++;//���������Z
		}
	}
	//while (nNum != 0)//����؂�Ȃ��Ȃ�܂ŌJ��Ԃ�
	//{
	//	nNum /= 10;//10�Ŋ���
	//	nKeepNum++;//���������Z
	//}

	return nKeepNum;
}
//==================
//�X�R�A�̎擾
//==================
int GetTime(void)
{
	return g_nTime;
}