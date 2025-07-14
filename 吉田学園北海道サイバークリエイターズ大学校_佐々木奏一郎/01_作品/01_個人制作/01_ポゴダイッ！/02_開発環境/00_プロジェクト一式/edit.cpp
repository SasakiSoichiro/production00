#include "edit.h"
#include "Input.h"
#include "player.h"
#include "stageselect.h"
#include "moveblock.h"
#include <stdio.h>
#include <string.h>

//�}�N����`
#define EDIT_MOVE (5.0f)
#define MAX_WORD (4096)
#define MAX_STAGE (10)
#define TXTFILE ("data\\stage000.txt")
#define TXTFILE1 ("data\\stage001.txt")
#define TXTFILE2 ("data\\stage002.txt")
#define TXTFILE3 ("data\\stage003.txt")
#define TXTFILE4 ("data\\stage004.txt")
#define TXTFILE5 ("data\\stage005.txt")
#define TXTFILE6 ("data\\stage006.txt")
#define TXTFILE7 ("data\\stage007.txt")
#define TXTFILE8 ("data\\stage008.txt")
#define TXTFILE9 ("data\\stage009.txt")
//�\���̒�`
typedef struct
{
	D3DXVECTOR3 pos;
	float fWidth;
	float fHeight;
	int nType;
	bool bUse;
}EditInfo;

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_pTextureEdit[MAX_NUMBLOCK] = {};	//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEdit = NULL;			//���_�o�b�t�@�ւ̃|�C���^
EditInfo g_EditInfo[MAX_BLOCK];								//�u���b�N�̏��
int g_nCntEdit;
int g_stage;

void InitEdit(void)
{

	//���[�J���ϐ�
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^
	VERTEX_2D* pVtx = 0;		//���_���ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();
	for (int nCnt = 0; nCnt < BLOCK_MAX; nCnt++)
	{
		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,
			BLOCK_TEXTURE[nCnt],
			&g_pTextureEdit[nCnt]);
	}

	//����������
	for (int nCnt=0;nCnt<MAX_BLOCK;nCnt++)
	{
		g_EditInfo[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ʒu������������
		g_EditInfo[nCnt].fWidth = 30.0f;						//��������������
		g_EditInfo[nCnt].fHeight = 30.0f;						//����������������
		g_EditInfo[nCnt].nType = 0;								//��ނ�����������
		g_EditInfo[nCnt].bUse = false;							//�g���Ă��Ȃ���Ԃɂ���	
	}
	g_EditInfo[0].bUse = true;
	g_stage = 0;
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BLOCK,//(sizeof(VERTEX_2D)*�K�v�Ȓ��_��
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEdit,
		NULL);


	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffEdit->Lock(0, 0, (void**)&pVtx, 0);

	//���[�v����
	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{//�u���b�N�̐������[�v����

		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_EditInfo[nCntBlock].pos.x - 40, g_EditInfo[nCntBlock].pos.y - 40, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_EditInfo[nCntBlock].pos.x + 40, g_EditInfo[nCntBlock].pos.y - 40, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_EditInfo[nCntBlock].pos.x - 40, g_EditInfo[nCntBlock].pos.y + 40, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_EditInfo[nCntBlock].pos.x + 40, g_EditInfo[nCntBlock].pos.y + 40, 0.0f);

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
		pVtx[0].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx += 4;//���_�f�[�^�̃|�C���^��4���W�߂�
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEdit->Unlock();

}
void UninitEdit(void)
{
	for (int nCnt = 0; nCnt < MAX_NUMBLOCK; nCnt++)
	{
		//�e�N�X�`���̔j��
		if (g_pTextureEdit[nCnt] != NULL)
		{
			g_pTextureEdit[nCnt]->Release();
			g_pTextureEdit[nCnt] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffEdit != NULL)
	{
		g_pVtxBuffEdit->Release();
		g_pVtxBuffEdit = NULL;
	}

}

void UpdateEdit(void)
{
	if (GetKeyboardPress(DIK_A) == true)
	{//���Ɉړ�
		g_EditInfo[g_nCntEdit].pos.x -= EDIT_MOVE;
	}
	else if (GetKeyboardPress(DIK_D) == true)
	{//���Ɉړ�
		g_EditInfo[g_nCntEdit].pos.x += EDIT_MOVE;
	}
	else if (GetKeyboardPress(DIK_W) == true)
	{//���Ɉړ�
		g_EditInfo[g_nCntEdit].pos.y -= EDIT_MOVE;
	}
	else if (GetKeyboardPress(DIK_S) == true)
	{//���Ɉړ�
		g_EditInfo[g_nCntEdit].pos.y += EDIT_MOVE;
	}
	else if (KeyboardTrigger(DIK_T) == true)
	{//���Ɉړ�
		if (g_EditInfo[g_nCntEdit].nType >=1)
		{
			g_EditInfo[g_nCntEdit].nType -= 1;
		}
	}
	else if (KeyboardTrigger(DIK_G) == true)
	{//���Ɉړ�
		if (g_EditInfo[g_nCntEdit].nType < MAX_NUMBLOCK-1)
		{
			g_EditInfo[g_nCntEdit].nType += 1;
		}
		
	}
	else if (KeyboardTrigger(DIK_O) == true)
	{//���Ɉړ�
		if (g_stage >= 1)
		{
			g_stage -= 1;
		}
	}
	else if (KeyboardTrigger(DIK_L) == true)
	{//���Ɉړ�
		if (g_stage < MAX_STAGE - 1)
		{
			g_stage += 1;
		}

	}


	else if (KeyboardTrigger(DIK_Y) == true&& GetKeyboardPress(DIK_SPACE) == true)
	{//�c�ɏ�����������
		g_EditInfo[g_nCntEdit].fHeight -= 2.0f;
	}


	else if (KeyboardTrigger(DIK_H) == true&& GetKeyboardPress(DIK_SPACE) == true)
	{//�c�ɑ傫��������
		g_EditInfo[g_nCntEdit].fHeight += 2.0f;
	}


	else if (KeyboardTrigger(DIK_Y) == true)
	{//�c�ɏ�����
			g_EditInfo[g_nCntEdit].fHeight -= 40.0f;
	}


	else if (KeyboardTrigger(DIK_H) == true)
	{//�c�ɑ傫��
			g_EditInfo[g_nCntEdit].fHeight += 40.0f;
	}


	else if (KeyboardTrigger(DIK_U) == true && GetKeyboardPress(DIK_SPACE) == true)
	{//���ɏ�����������
		g_EditInfo[g_nCntEdit].fWidth -= 2.0f;
	}


	else if (KeyboardTrigger(DIK_J) == true && GetKeyboardPress(DIK_SPACE) == true)
	{//���ɑ傫��������
		g_EditInfo[g_nCntEdit].fWidth += 2.0f;

	}


	else if (KeyboardTrigger(DIK_U) == true)
	{//���ɏ�����
		g_EditInfo[g_nCntEdit].fWidth -= 40.0f;
	}


	else if (KeyboardTrigger(DIK_J) == true)
	{//���ɑ傫��
		g_EditInfo[g_nCntEdit].fWidth += 40.0f;
	}


	if (KeyboardTrigger(DIK_RETURN) == true)
	{//Enter�L�[�������Ĕz�u
		g_EditInfo[g_nCntEdit + 1].pos = g_EditInfo[g_nCntEdit].pos;


		g_EditInfo[g_nCntEdit + 1].nType = g_EditInfo[g_nCntEdit].nType;

		g_EditInfo[g_nCntEdit + 1].bUse = true;
		g_nCntEdit++;
	}
	if (KeyboardTrigger(DIK_F7) == true)
	{
		SaveEdit();
	}
	//���_���W�̐ݒ�
	VERTEX_2D* pVtx = 0;	//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffEdit->Lock(0, 0, (void**)&pVtx, 0);

	//���[�v����
	for (int nCnt = 0; nCnt < MAX_BLOCK; nCnt++)
	{//�u���b�N�̍ő吔���Ԃ��


		if (g_EditInfo[nCnt].bUse == true)
		{//�u���b�N���g�p���Ă���ꍇ

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_EditInfo[nCnt].pos.x - g_EditInfo[nCnt].fWidth, g_EditInfo[nCnt].pos.y - g_EditInfo[nCnt].fHeight, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_EditInfo[nCnt].pos.x + g_EditInfo[nCnt].fWidth, g_EditInfo[nCnt].pos.y - g_EditInfo[nCnt].fHeight, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_EditInfo[nCnt].pos.x - g_EditInfo[nCnt].fWidth, g_EditInfo[nCnt].pos.y + g_EditInfo[nCnt].fHeight, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_EditInfo[nCnt].pos.x + g_EditInfo[nCnt].fWidth, g_EditInfo[nCnt].pos.y + g_EditInfo[nCnt].fHeight, 0.0f);
		}
		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEdit->Unlock();

}

void DrawEdit(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^

//�f�o�C�X�̎擾
	pDevice = GetDevice();
	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffEdit, 0, sizeof(VERTEX_2D));
	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//���[�v����
	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{//�u���b�N�̐������[�v����

		if (g_EditInfo[nCntBlock].bUse == true)
		{//�e���g�p����Ă���


			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(BLOCK_NORMAL, g_pTextureEdit[g_EditInfo[nCntBlock].nType]);
			pDevice->SetTexture(BLOCK_BUTTON, g_pTextureEdit[g_EditInfo[nCntBlock].nType]);
			pDevice->SetTexture(BLOCK_MOVEWALL, g_pTextureEdit[g_EditInfo[nCntBlock].nType]);
			pDevice->SetTexture(BLOCK_SLIME, g_pTextureEdit[g_EditInfo[nCntBlock].nType]);
			pDevice->SetTexture(BLOCK_TRANPORIN, g_pTextureEdit[g_EditInfo[nCntBlock].nType]);
			pDevice->SetTexture(BLOCK_GOAL, g_pTextureEdit[g_EditInfo[nCntBlock].nType]);
			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntBlock, 2);
		}
	}

}

void SaveEdit(void)
{
	//�t�@�C���|�C���^��錾
	FILE* pFile;

	D3DXVECTOR3 pos = {};
	float fWidth=0.0f;
	float fHeight=0.0f;
	int nType=0;

	switch (g_stage)
	{
	case 0:
		pFile = fopen(TXTFILE, "w");
		break;
	case 1:
		pFile = fopen(TXTFILE1, "w");
		break;
	case 2:
		pFile = fopen(TXTFILE2, "w");
		break;
	case 3:
		pFile = fopen(TXTFILE3, "w");
		break;
	case 4:
		pFile = fopen(TXTFILE4, "w");
		break;
	case 5:
		pFile = fopen(TXTFILE5, "w");
		break;
	case 6:
		pFile = fopen(TXTFILE6, "w");
		break;
	case 7:
		pFile = fopen(TXTFILE7, "w");
		break;
	case 8:
		pFile = fopen(TXTFILE8, "w");
		break;
	case 9:
		pFile = fopen(TXTFILE9, "w");
		break;
	default:
		pFile = NULL;
		break;
	}

	if (pFile!=NULL)
	{
		fwrite(&g_nCntEdit, sizeof(int), 0, pFile);

		for (int nCnt = 0; nCnt < g_nCntEdit; nCnt++)
		{
			if (g_EditInfo[nCnt].bUse== true)
			{
				fprintf(pFile, "BLOCKSET\n\n");
				fprintf(pFile, "POS %f %f %f\n\n", g_EditInfo[nCnt].pos.x, g_EditInfo[nCnt].pos.y, g_EditInfo[nCnt].pos.z);
				fprintf(pFile, "fWIDTH %f\n\n", g_EditInfo[nCnt].fWidth);
				fprintf(pFile, "fHEIGHT %f\n\n", g_EditInfo[nCnt].fHeight);
				fprintf(pFile, "TYPE %d\n\n", g_EditInfo[nCnt].nType);
				fprintf(pFile, "END_BLOCKSET\n\n");
			}
		}
		fprintf(pFile, "END_SCRIPT\n\n\n");
		fclose(pFile);
	}
	else
	{//�J���Ȃ������Ƃ��̏���
		return;
	}
}

void LoadEdit(void)
{
	FILE* pFile;

	D3DXVECTOR3 pos = {};
	float fWidth=0.0f;
	float fHeight=0.0f;
	int nType=0;
	g_stage = GetStageSelect();
	//�t�@�C�����J��
	switch (g_stage)
	{
	case 0://�X�e�[�W1
		pFile = fopen(TXTFILE, "r");
		break;
	case 1://�X�e�[�W2
		pFile = fopen(TXTFILE1, "r");
		SetMoveBlock(D3DXVECTOR3(340.0f, 450.0f, 0.0f), 100.0f, 20.0f, BLOCK_BEFORE);
		break;
	case 2://�X�e�[�W3
		pFile = fopen(TXTFILE2, "r");
		break;
	case 3:
		pFile = fopen(TXTFILE3, "r");
		break;
	case 4:
		pFile = fopen(TXTFILE4, "r");
		break;
	case 5:
		pFile = fopen(TXTFILE5, "r");
		SetMoveBlock(D3DXVECTOR3(200.0f, 300.0f, 0.0f), 100.0f, 20.0f, BLOCK_BEFORE);
		break;
	case 6:
		pFile = fopen(TXTFILE6, "r");
		SetMoveBlock(D3DXVECTOR3(1100.0f, 450.0f, 0.0f), 100.0f, 20.0f, BLOCK_BEFORE);
		break;
	case 7:
		pFile = fopen(TXTFILE7, "r");
		break;
	case 8:
		pFile = fopen(TXTFILE8, "r");
		break;
	case 9:
		pFile = fopen(TXTFILE9, "r");
		SetMoveBlock(D3DXVECTOR3(900.0f, 450.0f, 0.0f), 100.0f, 20.0f, BLOCK_BEFORE);
		break;
	default:
		pFile = NULL;
		break;
	}
	
	if (pFile != NULL)
	{
		char aString[MAX_WORD];//���������i�[
		//�S���̃e�L�X�g�ɏ����ꂽ����ǂݎ�肪�I���܂ŉ�
		while (1)
		{
			//�t�@�C����ǂݍ���
			fscanf(pFile, "%s", &aString[0]);

			//�ǂݎ�����̕����񂪈�v���Ă�����
			if (strcmp(aString, "BLOCKSET") == 0)
			{
				while (1)
				{
					//�t�@�C����ǂݍ���
					fscanf(pFile, "%s", &aString[0]);

					if (strcmp(aString, "POS") == 0)
					{//POS��ǂݎ������
						fscanf(pFile, "%f", &pos.x);
						fscanf(pFile, "%f", &pos.y);
						fscanf(pFile, "%f", &pos.z);
					}
					else if (strcmp(aString, "fWIDTH") == 0)
					{
						fscanf(pFile, "%f", &fWidth);
					}
					else if (strcmp(aString, "fHEIGHT") == 0)
					{
						fscanf(pFile, "%f", &fHeight);
					}
					else if (strcmp(aString, "TYPE") == 0)
					{
						fscanf(pFile, "%d", &nType);
					}
					else if (strcmp(aString, "END_BLOCKSET") == 0)
					{
						SetBlock(pos, fWidth, fHeight, nType);
						break;
					}
				}
			}
			if (strcmp(aString, "END_SCRIPT") == 0)
			{
				//while�𔲂��邽��
				break;
			}
		}
		fclose(pFile);

		Player* pPlayer = GetPlayer();

	}
	else
	{//�J���Ȃ������Ƃ��̏���
		return;
	}
}

int GetStage(void)
{
	return g_stage;
}