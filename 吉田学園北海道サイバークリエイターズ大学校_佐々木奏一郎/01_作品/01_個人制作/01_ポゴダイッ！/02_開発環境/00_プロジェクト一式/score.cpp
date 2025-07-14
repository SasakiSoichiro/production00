//=============================================================================
//
//	�X�R�A���� [score.cpp]
// Author : ���X�ؑt��Y
//
//=============================================================================
#include "score.h"
#include "rankingscore.h"
typedef struct
{
	bool bUse;

}Score;
//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureScore = NULL;//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffScore = NULL;//���_�o�b�t�@�ւ̃|�C���^
D3DXVECTOR3 g_posScore;//�X�R�A�̈ʒu
int g_nScore;//�X�R�A�̒l
Score g_aScore[MAX_SCORE];
//====================
//�X�R�A�̏���������
//====================
void InitScore(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCnt;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\number002.png",
		&g_pTextureScore);
	g_posScore = D3DXVECTOR3(50.0f,350.0f,0.0f);//�ʒu������������
	//g_nScore = 0;
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4*MAX_SCORE,//(sizeof(VERTEX_2D)*�K�v�Ȓ��_��
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffScore,
		NULL);
	VERTEX_2D* pVtx;
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);
	for (nCnt = 0; nCnt < MAX_SCORE; nCnt++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos.x = g_posScore.x - MAX_WIDTH / 2 + (MAX_WIDTH * nCnt);
		pVtx[0].pos.y = g_posScore.y - MAX_WIDTH / 2;
		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = g_posScore.x + MAX_WIDTH / 2 + (MAX_WIDTH * nCnt);
		pVtx[1].pos.y = g_posScore.y - MAX_WIDTH / 2;
		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = g_posScore.x - MAX_WIDTH / 2 + (MAX_WIDTH * nCnt);
		pVtx[2].pos.y = g_posScore.y + MAX_WIDTH / 2;
		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = g_posScore.x + MAX_WIDTH / 2 + (MAX_WIDTH * nCnt);
		pVtx[3].pos.y = g_posScore.y + MAX_WIDTH / 2;
		pVtx[3].pos.z = 0.0f;
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
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);
		pVtx += 4;//���_�f�[�^�̃|�C���^��4���W�߂�
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffScore->Unlock();
}
//====================
//�X�R�A�̏I������
//====================
void UninitScore(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureScore != NULL)
	{
		g_pTextureScore->Release();
		g_pTextureScore = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffScore != NULL)
	{
		g_pVtxBuffScore->Release();
		g_pVtxBuffScore = NULL;
	}
}
//===================
//�X�R�A�̍X�V����
//===================
void UpdateScore(void)
{
	int nData1, nData2;
	nData1 = ScoreCnt(g_nScore);//���߂��X�R�A�̌����ۑ�
	for (nData2 = 0; nData2 < MAX_SCORE; nData2++)
	{
		if (nData2 >= MAX_SCORE - nData1)
		{
			g_aScore[nData2].bUse = true;//0���\������Ă���Ƃ�
		}
		else
		{
			g_aScore[nData2].bUse = false;
		}
	}
}
//==================
// �X�R�A�̕`�揈��
//==================
void DrawScore(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^
	int nCnt;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();
	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffScore, 0, sizeof(VERTEX_2D));
	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	VERTEX_2D* pVtx;
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);
	for (nCnt = 0; nCnt < MAX_SCORE; nCnt++)
	{
		//if (g_aScore[nCnt].bUse == true)
		//{
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureScore);
			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCnt, 2);
		//}
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffScore->Unlock();
}
//====================
//�X�R�A�̐ݒ菈��
//====================
void SetScore(int nScore)
{
	int aPosTexU[MAX_SCORE], nData[2], nCnt;
	nData[0] = 10000000; nData[1] = 1000000;;//�e���̐������i�[
	g_nScore = nScore;
	VERTEX_2D* pVtx;
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);
	for (nCnt = 0; nCnt < MAX_SCORE; nCnt++)
	{
		if (nCnt==0)
		{
			aPosTexU[0] = g_nScore / nData[0];
		}
		else
		{
		aPosTexU[nCnt] = nScore % nData[0] / nData[1];
		nData[0] = nData[0] / 10;
		nData[1] = nData[1] / 10;
		}
		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f+(0.1f*aPosTexU[nCnt]), 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f + (0.1f * aPosTexU[nCnt]), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + (0.1f * aPosTexU[nCnt]), 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f + (0.1f * aPosTexU[nCnt]), 1.0f);
		pVtx += 4;//���_�f�[�^�̃|�C���^��4���W�߂�
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffScore->Unlock();
}
//===================
//�X�R�A�̉��Z����
//===================
void AddScore(int nValue)
{
	int aPosTexU[MAX_SCORE],nData[2], nCnt;
	nData[0] = 10000000; nData[1] = 1000000;
	g_nScore += nValue;
	VERTEX_2D* pVtx;
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);
	for (nCnt = 0; nCnt < MAX_SCORE; nCnt++)
	{
		if (nCnt==0)
		{
			aPosTexU[0] = g_nScore / nData[0];
		}
		else
		{
			aPosTexU[nCnt] = g_nScore % nData[0] / nData[1];
			nData[0] =nData[0]/ 10;
			nData[1] =nData[1]/ 10;
		}
		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f + (0.1f * aPosTexU[nCnt]), 0.0f);//���E���Őݒ肷��
		pVtx[1].tex = D3DXVECTOR2(0.1f + (0.1f * aPosTexU[nCnt]), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + (0.1f * aPosTexU[nCnt]), 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f + (0.1f * aPosTexU[nCnt]), 1.0f);
		pVtx += 4;//���_�f�[�^�̃|�C���^��4���W�߂�
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffScore->Unlock();
}
//===================
// �X�R�A�̉��Z����
//===================
int ScoreCnt(int nScore)
{
	int nNum = nScore;//�X�R�A�̂O�̕������J�E���g
	int nKeepNum = 0;//�X�R�A�̌���
	while (nNum != 0)//����؂�Ȃ��Ȃ�܂ŌJ��Ԃ�
	{
		nNum /= 10;//10�Ŋ���
		nKeepNum++;//���������Z
	}
	if (nScore == 0)
	{
		nKeepNum = 1;//�ꌅ�ڂ��O�̎�
	}
	return nKeepNum;
}
//==================
//�X�R�A�̎擾
//==================
int GetScore(void)
{
	return g_nScore;
}