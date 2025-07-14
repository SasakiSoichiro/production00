//=============================================================================
//
//�@�u���b�N���� [block.cpp]
// �@Author : ���X�ؑt��Y
//
//=============================================================================
#include "block.h"
#include "main.h"
#include "input.h"
#include "player.h"
#include "particle.h"
#include "sound.h"
#include "score.h"



//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureBlock[MAX_NUMBLOCK]= {};	//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBlock = NULL;			//���_�o�b�t�@�ւ̃|�C���^
Block g_aBlock[MAX_BLOCK];								//�u���b�N�̏��
//�O���[�o���錾
int g_nCntBlockState;
int g_nCntBlockState2;
bool g_bButton = false;
bool g_bUp = false;
bool g_goal = false;
bool g_Right = false;

//==================
//�u���b�N�̏���������
//==================
void InitBlock(void)
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
			&g_pTextureBlock[nCnt]);
	}
	//���[�v����
	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{//�u���b�N�̐������[�v����

		g_aBlock[nCntBlock].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ʒu������������
		g_aBlock[nCntBlock].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ړ��l������������
		g_aBlock[nCntBlock].fWidth = 0.0f;							//��������������
		g_aBlock[nCntBlock].fHeight = 0.0f;							//����������������
		g_aBlock[nCntBlock].nType = BLOCK_NORMAL;					//��ނ�����������
		g_aBlock[nCntBlock].bUse = false;							//�g���Ă��Ȃ���Ԃɂ���	
	}

	g_bButton = false;
	g_goal = false;
	g_bUp = false;
	g_Right = false;
	g_nCntBlockState = 0; 
	g_nCntBlockState2 = 0;

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BLOCK,//(sizeof(VERTEX_2D)*�K�v�Ȓ��_��
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBlock,
		NULL);


	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	//���[�v����
	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{//�u���b�N�̐������[�v����

		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x - 40, g_aBlock[nCntBlock].pos.y - 40, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + 40, g_aBlock[nCntBlock].pos.y - 40, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x - 40, g_aBlock[nCntBlock].pos.y + 40, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + 40, g_aBlock[nCntBlock].pos.y + 40, 0.0f);

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
		pVtx[0].tex = D3DXVECTOR2(0.0f,0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx += 4;//���_�f�[�^�̃|�C���^��4���W�߂�
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBlock->Unlock();
}

//==================
//�u���b�N�̏I������
//==================
void UninitBlock(void)
{
	for (int nCnt = 0; nCnt < MAX_NUMBLOCK; nCnt++)
	{
		//�e�N�X�`���̔j��
		if (g_pTextureBlock[nCnt] != NULL)
		{
			g_pTextureBlock[nCnt]->Release();
			g_pTextureBlock[nCnt] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffBlock != NULL)
	{
		g_pVtxBuffBlock->Release();
		g_pVtxBuffBlock = NULL;
	}

}

//==================
//�u���b�N�̍X�V����
//==================
void UpdateBlock(void)
{
	VERTEX_2D* pVtx = 0;	//���_���ւ̃|�C���^
	g_nCntBlockState++;
	g_nCntBlockState2++;
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	//���[�v����
	for (int nCnt = 0; nCnt < MAX_BLOCK; nCnt++)
	{//�u���b�N�̍ő吔���Ԃ��


		if (g_aBlock[nCnt].bUse == true)
		{//�u���b�N���g�p���Ă���ꍇ

			g_aBlock[nCnt].pos.x += g_aBlock[nCnt].move.x;
			g_aBlock[nCnt].pos.y += g_aBlock[nCnt].move.y;


			switch (g_aBlock[nCnt].nType)
			{
			case BLOCK_BUTTON://�{�^��
				if (g_bButton == true)
				{
					if (g_aBlock[nCnt].pos.y < g_aBlock[nCnt].pos.y - g_aBlock[nCnt].fHeight)
					{
						g_aBlock[nCnt].bUse = false;
					}
						g_aBlock[nCnt].fHeight--;
						g_aBlock[nCnt].pos.y++;
				}
				break;

			case BLOCK_MOVEWALL://������
				if (g_bButton == true)
				{
					if (g_aBlock[nCnt].pos.y < g_aBlock[nCnt].pos.y - g_aBlock[nCnt].fHeight)
					{
						g_aBlock[nCnt].bUse = false;
					}
					g_aBlock[nCnt].fHeight --;
					g_aBlock[nCnt].pos.y --;
						
						
				}
				break;
			case BLOCK_LR://���E�ɓ�����
				if (g_Right==true)
				{
					g_aBlock[nCnt].move.x = MAX_MOVE;
				}
				else if(g_Right==false)
				{
					g_aBlock[nCnt].move.x = -MAX_MOVE;
				}
				if (g_nCntBlockState >= 180)
				{
					g_nCntBlockState = 0;
					g_Right = !g_Right;
				}
				break;
			case BLOCK_UPDOWN://���E�ɓ�����

				if (g_bUp == true)
				{
					g_aBlock[nCnt].move.y = MAX_MOVE;
				}
				else if (g_bUp == false)
				{
					g_aBlock[nCnt].move.y = -MAX_MOVE;
				}
				if (g_nCntBlockState2 >= 180)
				{
					g_nCntBlockState2 = 0;
					g_bUp = !g_bUp;
				}
				break;
			}
			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aBlock[nCnt].pos.x - g_aBlock[nCnt].fWidth, g_aBlock[nCnt].pos.y - g_aBlock[nCnt].fHeight, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aBlock[nCnt].pos.x + g_aBlock[nCnt].fWidth, g_aBlock[nCnt].pos.y - g_aBlock[nCnt].fHeight, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aBlock[nCnt].pos.x - g_aBlock[nCnt].fWidth, g_aBlock[nCnt].pos.y + g_aBlock[nCnt].fHeight, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aBlock[nCnt].pos.x + g_aBlock[nCnt].fWidth, g_aBlock[nCnt].pos.y + g_aBlock[nCnt].fHeight, 0.0f);
		}
		pVtx += 4;//4���炷
	}


}

//==================
//�u���b�N�̕`�揈��
//==================
void DrawBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();
	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffBlock, 0, sizeof(VERTEX_2D));
	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//���[�v����
	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{//�u���b�N�̐������[�v����

		if (g_aBlock[nCntBlock].bUse == true)
		{//�e���g�p����Ă���


			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(BLOCK_NORMAL, g_pTextureBlock[g_aBlock[nCntBlock].nType]);
			pDevice->SetTexture(BLOCK_BUTTON, g_pTextureBlock[g_aBlock[nCntBlock].nType]);
			pDevice->SetTexture(BLOCK_MOVEWALL, g_pTextureBlock[g_aBlock[nCntBlock].nType]);
			pDevice->SetTexture(BLOCK_SLIME, g_pTextureBlock[g_aBlock[nCntBlock].nType]);
			pDevice->SetTexture(BLOCK_TRANPORIN, g_pTextureBlock[g_aBlock[nCntBlock].nType]);
			pDevice->SetTexture(BLOCK_GOAL, g_pTextureBlock[g_aBlock[nCntBlock].nType]);
			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4*nCntBlock, 2);
		}
	}
}

//===================
//�u���b�N�̐ݒ菈��
//===================
void SetBlock(D3DXVECTOR3 pos,	//�ʒu�̐ݒ�
				float fWidth,	//���̐ݒ�
				float fHeight,	//�����̐ݒ�
				int nType)		//���	

{	
	VERTEX_2D* pVtx=0;		//���_���ւ̃|�C���^
	float fU=0;				//�e�N�X�`���̖���
	float fV = 0;			//�e�N�X�`���̖���
	Player* pPlayer = GetPlayer();

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	//���[�v����
	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{//�u���b�N�̍ő吔�����[�v����
		if (g_aBlock[nCntBlock].bUse == false)
		{//�u���b�N���g�p����Ă��Ȃ�


			g_aBlock[nCntBlock].pos = pos;			//�u���b�N�̒��_���W����
			g_aBlock[nCntBlock].fWidth=fWidth;		//�u���b�N�̕�����
			g_aBlock[nCntBlock].fHeight = fHeight;	//�u���b�N�̍�������
			g_aBlock[nCntBlock].nType = nType;		//�u���b�N�̎�ނ���
			g_aBlock[nCntBlock].bUse = true;		//�g�p���Ă����Ԃɂ���

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x - fWidth, g_aBlock[nCntBlock].pos.y - fHeight, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + fWidth, g_aBlock[nCntBlock].pos.y - fHeight, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x - fWidth, g_aBlock[nCntBlock].pos.y + fHeight, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + fWidth, g_aBlock[nCntBlock].pos.y + fHeight, 0.0f);
			switch (g_aBlock[nCntBlock].nType)
			{
			case BLOCK_NORMAL://�m�[�}��

				//���_���W�̐ݒ�
				pVtx[0].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x - fWidth, g_aBlock[nCntBlock].pos.y - fHeight, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + fWidth, g_aBlock[nCntBlock].pos.y - fHeight, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x - fWidth, g_aBlock[nCntBlock].pos.y + fHeight, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + fWidth, g_aBlock[nCntBlock].pos.y + fHeight, 0.0f);

				fU = fWidth / MAX_BLOCKWIDTH;
				fV = fHeight / MAX_BLOCKHEIGHT;
				//�e�N�X�`�����W�̐ݒ�
				pVtx[0].tex = D3DXVECTOR2(fU, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(fU, fV);
				pVtx[3].tex = D3DXVECTOR2(0.0f, fV);
	

				break;

			case BLOCK_SLIME://�X���C��

				//���_���W�̐ݒ�
				pVtx[0].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x - fWidth, g_aBlock[nCntBlock].pos.y - fHeight, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + fWidth, g_aBlock[nCntBlock].pos.y - fHeight, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x - fWidth, g_aBlock[nCntBlock].pos.y + fHeight, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + fWidth, g_aBlock[nCntBlock].pos.y + fHeight, 0.0f);

				fU = fWidth / MAX_BLOCKWIDTH;
				fV = fHeight / MAX_BLOCKHEIGHT;
				//�e�N�X�`�����W�̐ݒ�
				pVtx[0].tex = D3DXVECTOR2(fU, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(fU, fV);
				pVtx[3].tex = D3DXVECTOR2(0.0f, fV);

				break;
			}
			
			break;
		}
		pVtx += 4;//���_�f�[�^�̃|�C���^��4���W�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBlock->Unlock();
}


//===========================
//�u���b�N�̓����蔻�菈��
//===========================
bool CollisionBlock(D3DXVECTOR3* pPos,		//���݂̃|�S�ʒu
	                D3DXVECTOR3* pPosOld,	//�O��̃|�S�ʒu
					D3DXVECTOR3* pPYPos,	//���݂̃v���C���[�ʒu
					D3DXVECTOR3* pPYPosOld,	//�O��̃v���C���[�ʒu
	                D3DXVECTOR3* pMove,		//�ړ���
					float fWidth,			//��
					float fHeight,			//����
					Block**pBlock)			//pBlock�̃|�C���^
{
	//���[�J���ϐ�
	bool bLanding = false;					//���n���Ă��邩�ǂ���
	float Width = fWidth;					//�v���C���[�̕�
	float Height = fHeight;					//�v���C���[�̍���
	float fX[4];
	float fY[4];
	D3DXVECTOR3 *PosOld=pPosOld;			//�O�t���[���̃|�S�̈ʒu
	D3DXVECTOR3* Pos = pPos;				//���t���[���̃|�S�̈ʒu
	D3DXVECTOR3* PYPosOld = pPYPosOld;		//�O�t���[���̃v���C���[�̈ʒu
	D3DXVECTOR3* PYPos = pPYPos;			//���t���[���̃v���C���[�̈ʒu
	Player*pPlayer= GetPlayer();

	
	//���[�v����
	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{//�u���b�N�̍ő吔�����[�v����


		if (g_aBlock[nCntBlock].bUse == true)
		{//�u���b�N���g�p���Ă���ꍇ

			fX[0] = (g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].fWidth - pPos->x) * (g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].fWidth - pPos->x);
			fY[0] = (g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].fHeight - pPos->y) * (g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].fHeight - pPos->y);
			fX[1] = (g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth - pPos->x) * (g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth - pPos->x);
			fY[1] = (g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight - pPos->y) * (g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight - pPos->y);
			fX[2] = (g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].fWidth - pPYPos->x) * (g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].fWidth - pPYPos->x);
			fY[2] = (g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].fHeight - pPYPos->y) * (g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].fHeight - pPYPos->y);
			fX[3] = (g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth - pPYPos->x) * (g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth - pPYPos->x);
			fY[3] = (g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight - pPYPos->y) * (g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight - pPYPos->y);
				

				if ((pPos->x > g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].fWidth) && (pPos->x < g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth) && (pPos->y > g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].fHeight - MAX_POSCIRCLE) && (pPos->y < g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight + MAX_POSCIRCLE))
				{//�㉺�̃|�S�����蔻��

					
					//���n�̔����true�ɂ���
					bLanding = true;
					if (g_aBlock[nCntBlock].nType == BLOCK_GOAL)
					{
						g_goal = true;
					}

					//�W�����v���Ă���

					//y������move������
					pMove->y = 0.0f;
					if (pBlock != NULL)
					{//�u���b�N�̃A�h���X������ꏊ������
						*pBlock = &g_aBlock[nCntBlock];
					}

					if (g_aBlock[nCntBlock].nType == BLOCK_BUTTON)
					{
						g_bButton = true;
					}

				}


				if ((pPos->x > g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].fWidth - MAX_POSCIRCLE) && (pPos->x < g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth + MAX_POSCIRCLE) && (pPos->y > g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].fHeight) && (pPos->y < g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight))
				{//���E�̃|�S�����蔻��


					//���n�̔����true�ɂ���
					bLanding = true;
					if (g_aBlock[nCntBlock].nType == BLOCK_GOAL)
					{
						g_goal = true;
					}
					//�W�����v���Ă���

					//x������move������
					pMove->x = 0.0f;
					if (pBlock != NULL)
					{//�u���b�N�̃A�h���X������ꏊ������
						*pBlock = &g_aBlock[nCntBlock];
					}
					if (g_aBlock[nCntBlock].nType == BLOCK_BUTTON)
					{
						g_bButton = true;
					}

				}


				if (fX[0] + fY[0] < MAX_POSCIRCLE * MAX_POSCIRCLE)
				{//�E��̃|�S�����蔻��


					//���n�̔����true�ɂ���
					bLanding = true;
					if (g_aBlock[nCntBlock].nType == BLOCK_GOAL)
					{
						g_goal = true;
					}
					//x������move������
					pMove->x = 0.0f;

					if (pBlock != NULL)
					{//�u���b�N�̃A�h���X������ꏊ������
						*pBlock = &g_aBlock[nCntBlock];
					}
					if (g_aBlock[nCntBlock].nType == BLOCK_BUTTON)
					{
						g_bButton = true;
					}

				}


				if (fX[1] + fY[0] < MAX_POSCIRCLE * MAX_POSCIRCLE)
				{//����̃|�S�����蔻��


					//���n�̔����true�ɂ���
					bLanding = true;

					if (g_aBlock[nCntBlock].nType == BLOCK_GOAL)
					{
						g_goal = true;
					}

								//�W�����v���Ă���

					//x������move������
					pMove->x = 0.0f;

					if (pBlock != NULL)
					{//�u���b�N�̃A�h���X������ꏊ������
						*pBlock = &g_aBlock[nCntBlock];
					}
					if (g_aBlock[nCntBlock].nType == BLOCK_BUTTON)
					{
						g_bButton = true;
					}

				}


				if (fX[0] + fY[1] < MAX_POSCIRCLE * MAX_POSCIRCLE)
				{//�E���̃|�S�����蔻��


					//���n�̔����true�ɂ���
					bLanding = true;

					if (g_aBlock[nCntBlock].nType == BLOCK_GOAL)
					{
						g_goal = true;
					}


					//x������move������
					pMove->x = 0.0f;

					if (pBlock != NULL)
					{//�u���b�N�̃A�h���X������ꏊ������
						*pBlock = &g_aBlock[nCntBlock];
					}
					if (g_aBlock[nCntBlock].nType == BLOCK_BUTTON)
					{
						g_bButton = true;
					}

				}


				if (fX[1] + fY[1] < MAX_POSCIRCLE * MAX_POSCIRCLE)
				{//�����̃|�S�����蔻��


					//���n�̔����true�ɂ���
					bLanding = true;

					if (g_aBlock[nCntBlock].nType == BLOCK_GOAL)
					{
						g_goal = true;
						//AddScore(1000);
					}

					//x������move������
					pMove->x = 0.0f;

					if (pBlock != NULL)
					{//�u���b�N�̃A�h���X������ꏊ������
						*pBlock = &g_aBlock[nCntBlock];
					}

					if (g_aBlock[nCntBlock].nType == BLOCK_BUTTON)
					{
						g_bButton = true;
					}

				}

				if ((pPYPos->x > g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].fWidth) && (pPYPos->x < g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth) && (pPYPos->y > g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].fHeight - MAX_POSCIRCLE) && (pPYPos->y < g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight + MAX_POSCIRCLE))
				{//�㉺�̃v���C���[�����蔻��

					//�v���C���[�̃��C�t��1���炷
					pPlayer->nLife--;


					if (g_aBlock[nCntBlock].nType == BLOCK_GOAL)
					{
						g_goal = true;

					}
					//y������move������
					pMove->y = 0.0f;

					if (g_aBlock[nCntBlock].nType == BLOCK_BUTTON)
					{
						g_bButton = true;

					}

				}


				if ((pPYPos->x > g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].fWidth - MAX_POSCIRCLE) && (pPYPos->x < g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth + MAX_POSCIRCLE) && (pPYPos->y > g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].fHeight) && (pPYPos->y < g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight))
				{//���E�̃v���C���[�����蔻��

					//�v���C���[�̃��C�t��1���炷
					pPlayer->nLife--;

					//x������move������
					pMove->x = 0.0f;
					//x������move������
					pMove->y = 0.0f;

					if (g_aBlock[nCntBlock].nType == BLOCK_BUTTON)
					{
						g_bButton = true;
					}
					if (g_aBlock[nCntBlock].nType == BLOCK_GOAL)
					{
						g_goal = true;

					}
				}


				if (fX[2] + fY[2] < MAX_POSCIRCLE * MAX_POSCIRCLE)
				{//�E��̃v���C���[�����蔻��

					//�v���C���[�̃��C�t��1���炷
					pPlayer->nLife--;

					//x������move������
					pMove->x = 0.0f;
					//x������move������
					pMove->y = 0.0f;

					if (g_aBlock[nCntBlock].nType == BLOCK_BUTTON)
					{
						g_bButton = true;
					}
					if (g_aBlock[nCntBlock].nType == BLOCK_GOAL)
					{
						g_goal = true;


					}
				}

				if (fX[3] + fY[2] < MAX_POSCIRCLE * MAX_POSCIRCLE)
				{//����̃v���C���[�����蔻��

					//�v���C���[�̃��C�t��1���炷
					pPlayer->nLife--;

					//x������move������
					pMove->x = 0.0f;
					//x������move������
					pMove->y = 0.0f;

					if (g_aBlock[nCntBlock].nType == BLOCK_BUTTON)
					{
						g_bButton = true;
					}
					if (g_aBlock[nCntBlock].nType == BLOCK_GOAL)
					{
						g_goal = true;

					}
				}


				if (fX[2] + fY[3] < MAX_POSCIRCLE * MAX_POSCIRCLE)
				{//�E���̃v���C���[�����蔻��

					//�v���C���[�̃��C�t��1���炷
					pPlayer->nLife--;

					//x������move������
					pMove->x = 0.0f;
					//x������move������
					pMove->y = 0.0f;
					if (g_aBlock[nCntBlock].nType == BLOCK_BUTTON)
					{
						g_bButton = true;
					}
					if (g_aBlock[nCntBlock].nType == BLOCK_GOAL)
					{
						g_goal = true;

					}
				}

				if (fX[3] + fY[3] < MAX_POSCIRCLE * MAX_POSCIRCLE)
				{//�����̃v���C���[�����蔻��

					//�v���C���[�̃��C�t��1���炷
					pPlayer->nLife--;

					//x������move������
					pMove->x = 0.0f;
					//x������move������
					pMove->y = 0.0f;
					if (g_aBlock[nCntBlock].nType == BLOCK_BUTTON)
					{
						g_bButton = true;
					}
					if (g_aBlock[nCntBlock].nType == BLOCK_GOAL)
					{
						g_goal = true;

					}
				}

		}
	}

	//bLanding�̒l��Ԃ�
	return bLanding;
}
bool GetGoal(void)
{
	return g_goal;
}
bool GetButton(void)
{
	return &g_bButton;
}