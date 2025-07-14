//=============================================================================
//
//	�^�C�g������ [title.cpp]
// Author : ���X�ؑt��Y
//
//=============================================================================
#include "title.h"
#include "main.h"
#include "input.h"
#include "sound.h"
#include "fade.h"
#include "buckground.h"
#define MAX_TITLE (2)
//�^�C�g���\����
typedef struct
{
	D3DXVECTOR3 pos;//���W
	D3DXVECTOR3 col;//�J���[
	int nType;//���
	bool bUse;//�g�p���
	float fHeight;//����
	float fWidth;//��
	TITLESTATE state;//���
}Title;
//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureTitle[MAX_TITLE] = {};//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL;//���_�o�b�t�@�ւ̃|�C���^
Title g_aTitle[MAX_TITLE];//�^�C�g���\���̂̏��
TITLE g_Title;//�^�C�g���񋓌^�̏��
int g_nCntAnim;//�^�C�g�����
int g_nPatternAnim;//��ԃp�^�[��
int g_nTimeCnt;
//�^�C�g����ʂ̏���������
void InitTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^
	//�f�o�C�X�̎擾
	pDevice = GetDevice();
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\TITLE000.png",
		&g_pTextureTitle[1]);
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\GAMESTART000.png",
		&g_pTextureTitle[0]);

	for (int nCntTitle = 0; nCntTitle < MAX_TITLE; nCntTitle++)
	{
		g_aTitle[nCntTitle].nType = 0;
		g_aTitle[nCntTitle].fHeight = 0.0f;
		g_aTitle[nCntTitle].fWidth = 0.0f;
		g_aTitle[nCntTitle].bUse = false;
		g_aTitle[nCntTitle].state = TITLESTATE_NONE;//�������Ă��Ȃ����
	}

	g_nCntAnim = 0;//�^�C�g�����
	g_nPatternAnim = 0;//��ԃp�^�[��
	g_nTimeCnt = 0;
	//���_�o�b�t�@�̐����B���_���̐ݒ�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4*MAX_TITLE,//(sizeof(VERTEX_2D)*�K�v�Ȓ��_��
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTitle,
		NULL);
	VERTEX_2D* pVtx;//���_���ւ̃|�C���^
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCnt = 0; nCnt < MAX_TITLE; nCnt++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
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
		pVtx += 4;
	}
	
	SetTitle(TITLE_1, D3DXVECTOR3(630.0f, 600.0f, 0.0f));
	SetTitle(TITLE_2, D3DXVECTOR3(650.0f, 250.0f, 1.0f));
	
	
	
	
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTitle->Unlock();

	//�w�i�̏���������
	InitBuckground();

	////�T�E���h�̍Đ�
	//PlaySound(SOUND_LABEL_BGM02);
}
//�^�C�g����ʂ̏I������
void UninitTitle(void)
{

	//�e�N�X�`���̔j��
	for (int nCnt = 0; nCnt < MAX_TITLE; nCnt++)
	{
		if (g_pTextureTitle[nCnt] != NULL)
		{
			g_pTextureTitle[nCnt]->Release();
			g_pTextureTitle[nCnt] = NULL;
		}
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffTitle!= NULL)
	{
		g_pVtxBuffTitle->Release();
		g_pVtxBuffTitle= NULL;
	}

	//�w�i�̏I������
	UninitBuckground();
}
//�^�C�g����ʂ̍X�V����
void UpdateTitle(void)
{
	GetFade();//�t�F�[�h�̎擾

	FADE g_fade = GetFade();//���݂̏��

	if (KeyboardTrigger(DIK_RETURN) == true)
	{//Enter�L�[�������ꂽ

		//SE�Đ�
		PlaySound(SOUND_LABEL_SE002);
		
		for (int nCntTitle = 0; nCntTitle < MAX_TITLE; nCntTitle++)
		{
			if (g_aTitle[nCntTitle].bUse == true && nCntTitle==1/*g_aTitle[nCntTitle].nType == TITLE_2*/)
			{
				g_aTitle[nCntTitle].state = TITLESTATE_FLASH;
			}
		}
		//���[�h�ݒ�(�Q�[����ʂɈړ�)
		SetFade(MODE_BLOCKINFO);
	}
	if (JoyPadTrigger(JOYKEY_A) == true)
	{//A�{�^���������ꂽ

		//SE�Đ�
		PlaySound(SOUND_LABEL_SE002);

		for (int nCntTitle = 0; nCntTitle < MAX_TITLE; nCntTitle++)
		{
			if (g_aTitle[nCntTitle].bUse == true && nCntTitle == 1/*g_aTitle[nCntTitle].nType == TITLE_2*/)
			{
				g_aTitle[nCntTitle].state = TITLESTATE_FLASH;
			}
		}

		//���[�h�ݒ�(�Q�[����ʂɈړ�)
		SetFade(MODE_BLOCKINFO);
	}

	g_nTimeCnt++;
	if (g_nTimeCnt >= 900)
	{
		//���[�h�ݒ�(�����L���O��ʂɈړ�)
		SetFade(MODE_BLOCKINFO);
	}
	TitleFlash(TITLE_2);//�^�C�g���̓_��

	if (KeyboardTrigger(DIK_F2) == true)
	{
		//���[�h�ݒ�(�����L���O��ʂɈړ�)
		SetFade(MODE_EDIT);
	}

	//�w�i�̍X�V����
	UpdateBuckground();

}
//�^�C�g����ʂ̕`�揈��
void DrawTitle(void)
{
	//�w�i�̕`�揈��
	DrawBuckground();

	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^
	int nCntBG;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();
	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTitle, 0, sizeof(VERTEX_2D));
	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	for(int nCnt=0;nCnt<MAX_TITLE;nCnt++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureTitle[g_aTitle[nCnt].nType]);
		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4*nCnt, 2);
	}
		

}
void SetTitle(int nType, D3DXVECTOR3 pos)
{
	int nCnt;
	VERTEX_2D* pVtx;//���_���ւ̃|�C���^
//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);
	for (nCnt = 0; nCnt < MAX_TITLE; nCnt++)
	{
		if (g_aTitle[nCnt].bUse == false)
		{
			g_aTitle[nCnt].nType = nType;
			g_aTitle[nCnt].pos = pos;
			g_aTitle[nCnt].bUse = true;
			//�ꍇ����
			switch (nType)
			{
			case TITLE_1:
				g_aTitle[nCnt].fHeight = 150.0f;//����
				g_aTitle[nCnt].fWidth = 400.0f;//����
				break;
			case TITLE_2:
				g_aTitle[nCnt].fHeight = 350.0f;//����
				g_aTitle[nCnt].fWidth = 800.0f;//����
				break;
			}
			//���_���W1�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aTitle[nCnt].pos.x - g_aTitle[nCnt].fWidth * 0.5f, g_aTitle[nCnt].pos.y - g_aTitle[nCnt].fHeight * 0.5f, 0.0f);//1�ڂ̒��_���
			pVtx[1].pos = D3DXVECTOR3(g_aTitle[nCnt].pos.x + g_aTitle[nCnt].fWidth * 0.5f, g_aTitle[nCnt].pos.y - g_aTitle[nCnt].fHeight * 0.5f, 0.0f);//2�ڂ̒��_���
			pVtx[2].pos = D3DXVECTOR3(g_aTitle[nCnt].pos.x - g_aTitle[nCnt].fWidth * 0.5f, g_aTitle[nCnt].pos.y + g_aTitle[nCnt].fHeight * 0.5f, 0.0f);//3�ڂ̒��_���
			pVtx[3].pos = D3DXVECTOR3(g_aTitle[nCnt].pos.x + g_aTitle[nCnt].fWidth * 0.5f, g_aTitle[nCnt].pos.y + g_aTitle[nCnt].fHeight * 0.5f, 0.0f);//4�ڂ̒��_���
			break;
		}
		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTitle->Unlock();
}
void TitleFlash(int nType)
{
	int nCnt;
	VERTEX_2D* pVtx;//���_���ւ̃|�C���^
//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);
	for (nCnt = 0; nCnt < MAX_TITLE; nCnt++)
	{
		if (g_aTitle[nCnt].bUse == true && g_aTitle[nCnt].state == TITLESTATE_FLASH)
		{
			
			g_nCntAnim++;
			if (g_nCntAnim == 5)
			{
				//���_�J���[�̐ݒ�@�@�@�@
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.2f);
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.2f);
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.2f);
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.2f);
			}
			else if (g_nCntAnim == 10)
			{
				//���_�J���[�̐ݒ�@�@�@�@
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				g_nCntAnim = 0;//�J�E���^�[�������l�ɖ߂�
			}
			pVtx += 4;
		}
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTitle->Unlock();
}