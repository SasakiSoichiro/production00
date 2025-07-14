//=============================================================================
//
//�@���[�u�u���b�N���� [moveblock.cpp]
// �@Author : ���X�ؑt��Y
//
//=============================================================================
#include "moveblock.h"
#include "main.h"
#include "input.h"
#include "player.h"
#include "particle.h"

//�}�N����`
#define MAX_MOVEBLOCK (128)		//�u���b�N�̍ő吔
#define MAX_NUMMOVEBLOCK (3)	//�u���b�N�̎��

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureMoveBlock[MAX_NUMMOVEBLOCK] = {};	//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMoveBlock = NULL;			//���_�o�b�t�@�ւ̃|�C���^
MoveBlock g_aMoveBlock[MAX_MOVEBLOCK];								//�u���b�N�̏��


//==================
//�u���b�N�̏���������
//==================
void InitMoveBlock(void)
{
	//���[�J���ϐ�
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^
	VERTEX_2D* pVtx = 0;		//���_���ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();
	for (int nCnt = 0; nCnt < BLOCK_MOVEMAX; nCnt++)
	{
		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,
			MOVEBLOCK_TEXTURE[nCnt],
			&g_pTextureMoveBlock[nCnt]);
	}
	//���[�v����
	for (int nCntBlock = 0; nCntBlock < MAX_MOVEBLOCK; nCntBlock++)
	{//�u���b�N�̐������[�v����

		g_aMoveBlock[nCntBlock].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�ʒu������������
		g_aMoveBlock[nCntBlock].fWidth = 0.0f;						//��������������
		g_aMoveBlock[nCntBlock].fHeight = 0.0f;						//����������������
		g_aMoveBlock[nCntBlock].nType = BLOCK_BEFORE;				//��ނ�����������
		g_aMoveBlock[nCntBlock].bUse = false;						//�g���Ă��Ȃ���Ԃɂ���	
	}

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_MOVEBLOCK,//(sizeof(VERTEX_2D)*�K�v�Ȓ��_��
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMoveBlock,
		NULL);


	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffMoveBlock->Lock(0, 0, (void**)&pVtx, 0);

	//���[�v����
	for (int nCntBlock = 0; nCntBlock < MAX_MOVEBLOCK; nCntBlock++)
	{//�u���b�N�̐������[�v����

		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_aMoveBlock[nCntBlock].pos.x - 40, g_aMoveBlock[nCntBlock].pos.y - 40, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aMoveBlock[nCntBlock].pos.x + 40, g_aMoveBlock[nCntBlock].pos.y - 40, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aMoveBlock[nCntBlock].pos.x - 40, g_aMoveBlock[nCntBlock].pos.y + 40, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aMoveBlock[nCntBlock].pos.x + 40, g_aMoveBlock[nCntBlock].pos.y + 40, 0.0f);

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
	g_pVtxBuffMoveBlock->Unlock();
}

//==================
//�u���b�N�̏I������
//==================
void UninitMoveBlock(void)
{
	for (int nCnt = 0; nCnt < MAX_NUMMOVEBLOCK; nCnt++)
	{
		//�e�N�X�`���̔j��
		if (g_pTextureMoveBlock[nCnt] != NULL)
		{
			g_pTextureMoveBlock[nCnt]->Release();
			g_pTextureMoveBlock[nCnt] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffMoveBlock != NULL)
	{
		g_pVtxBuffMoveBlock->Release();
		g_pVtxBuffMoveBlock = NULL;
	}

}

//==================
//�u���b�N�̍X�V����
//==================
void UpdateMoveBlock(void)
{
	VERTEX_2D* pVtx = 0;	//���_���ւ̃|�C���^

	Player* pPlayer = GetPlayer();

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffMoveBlock->Lock(0, 0, (void**)&pVtx, 0);

	//���[�v����
	for (int nCnt = 0; nCnt < MAX_MOVEBLOCK; nCnt++)
	{//�u���b�N�̍ő吔���Ԃ��


		if (g_aMoveBlock[nCnt].bUse == true)
		{//�u���b�N���g�p���Ă���ꍇ


			switch (g_aMoveBlock[nCnt].nType)
			{
			case BLOCK_BEFORE:
				break;
			case BLOCK_MOVE:
				g_aMoveBlock[nCnt].pos.x = pPlayer->pos.x;
				g_aMoveBlock[nCnt].pos.y = pPlayer->pos.y-80.0f;
				if (GetKeyboardPress(DIK_RETURN) == true || GetJoypadPress(JOYKEY_X) == true)
				{//F�L�[�������ꂽ�Ƃ�
					g_aMoveBlock[nCnt].nType = BLOCK_AFTER;
				}
				break;
			case BLOCK_AFTER:
				break;
			}
			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aMoveBlock[nCnt].pos.x - g_aMoveBlock[nCnt].fWidth, g_aMoveBlock[nCnt].pos.y - g_aMoveBlock[nCnt].fHeight, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aMoveBlock[nCnt].pos.x + g_aMoveBlock[nCnt].fWidth, g_aMoveBlock[nCnt].pos.y - g_aMoveBlock[nCnt].fHeight, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aMoveBlock[nCnt].pos.x - g_aMoveBlock[nCnt].fWidth, g_aMoveBlock[nCnt].pos.y + g_aMoveBlock[nCnt].fHeight, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aMoveBlock[nCnt].pos.x + g_aMoveBlock[nCnt].fWidth, g_aMoveBlock[nCnt].pos.y + g_aMoveBlock[nCnt].fHeight, 0.0f);

			break;
		}
		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffMoveBlock->Unlock();

}

//==================
//�u���b�N�̕`�揈��
//==================
void DrawMoveBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();
	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffMoveBlock, 0, sizeof(VERTEX_2D));
	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//���[�v����
	for (int nCntBlock = 0; nCntBlock < MAX_MOVEBLOCK; nCntBlock++)
	{//�u���b�N�̐������[�v����

		if (g_aMoveBlock[nCntBlock].bUse == true)
		{//�e���g�p����Ă���


			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(BLOCK_BEFORE, g_pTextureMoveBlock[g_aMoveBlock[nCntBlock].nType]);
			pDevice->SetTexture(BLOCK_MOVE, g_pTextureMoveBlock[g_aMoveBlock[nCntBlock].nType]);
			pDevice->SetTexture(BLOCK_AFTER, g_pTextureMoveBlock[g_aMoveBlock[nCntBlock].nType]);
			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntBlock, 2);
		}
	}
}

//===================
//�u���b�N�̐ݒ菈��
//===================
void SetMoveBlock(D3DXVECTOR3 pos,	//�ʒu�̐ݒ�
	float fWidth,					//���̐ݒ�
	float fHeight,					//�����̐ݒ�
	int nType)						//���	

{
	VERTEX_2D* pVtx = 0;	//���_���ւ̃|�C���^
	float fU = 0;			//�e�N�X�`���̖���
	Player* pPlayer = GetPlayer();

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffMoveBlock->Lock(0, 0, (void**)&pVtx, 0);

	//���[�v����
	for (int nCntBlock = 0; nCntBlock < MAX_MOVEBLOCK; nCntBlock++)
	{//�u���b�N�̍ő吔�����[�v����
		if (g_aMoveBlock[nCntBlock].bUse == false)
		{//�u���b�N���g�p����Ă��Ȃ�


			g_aMoveBlock[nCntBlock].pos = pos;			//�u���b�N�̒��_���W����
			g_aMoveBlock[nCntBlock].fWidth = fWidth;	//�u���b�N�̕�����
			g_aMoveBlock[nCntBlock].fHeight = fHeight;	//�u���b�N�̍�������
			g_aMoveBlock[nCntBlock].nType = nType;		//�u���b�N�̎�ނ���
			g_aMoveBlock[nCntBlock].bUse = true;		//�g�p���Ă����Ԃɂ���

			switch (g_aMoveBlock[nCntBlock].nType)
			{
			case BLOCK_BEFORE://�m�[�}��

				//���_���W�̐ݒ�
				pVtx[0].pos = D3DXVECTOR3(g_aMoveBlock[nCntBlock].pos.x - fWidth, g_aMoveBlock[nCntBlock].pos.y - fHeight, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_aMoveBlock[nCntBlock].pos.x + fWidth, g_aMoveBlock[nCntBlock].pos.y - fHeight, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aMoveBlock[nCntBlock].pos.x - fWidth, g_aMoveBlock[nCntBlock].pos.y + fHeight, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aMoveBlock[nCntBlock].pos.x + fWidth, g_aMoveBlock[nCntBlock].pos.y + fHeight, 0.0f);

				break;

			case BLOCK_MOVE://�{�^��

				//���_���W�̐ݒ�
				pVtx[0].pos = D3DXVECTOR3(g_aMoveBlock[nCntBlock].pos.x - fWidth, g_aMoveBlock[nCntBlock].pos.y - fHeight, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_aMoveBlock[nCntBlock].pos.x + fWidth, g_aMoveBlock[nCntBlock].pos.y - fHeight, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aMoveBlock[nCntBlock].pos.x - fWidth, g_aMoveBlock[nCntBlock].pos.y + fHeight, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aMoveBlock[nCntBlock].pos.x + fWidth, g_aMoveBlock[nCntBlock].pos.y + fHeight, 0.0f);

				break;

			case BLOCK_AFTER://�{�^��

				//���_���W�̐ݒ�
				pVtx[0].pos = D3DXVECTOR3(g_aMoveBlock[nCntBlock].pos.x - fWidth, g_aMoveBlock[nCntBlock].pos.y - fHeight, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_aMoveBlock[nCntBlock].pos.x + fWidth, g_aMoveBlock[nCntBlock].pos.y - fHeight, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aMoveBlock[nCntBlock].pos.x - fWidth, g_aMoveBlock[nCntBlock].pos.y + fHeight, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aMoveBlock[nCntBlock].pos.x + fWidth, g_aMoveBlock[nCntBlock].pos.y + fHeight, 0.0f);

				break;
			}

			break;
		}
		pVtx += 4;//���_�f�[�^�̃|�C���^��4���W�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffMoveBlock->Unlock();
}


//===========================
//�u���b�N�̓����蔻�菈��
//===========================
bool CollisionMoveBlock(D3DXVECTOR3* pPos,		//���݂̃|�S�ʒu
	D3DXVECTOR3* pPosOld,	//�O��̃|�S�ʒu
	D3DXVECTOR3* pPYPos,	//���݂̃v���C���[�ʒu
	D3DXVECTOR3* pPYPosOld,	//�O��̃v���C���[�ʒu
	D3DXVECTOR3* pMove,		//�ړ���
	float fWidth,			//��
	float fHeight)			//����
{
	//���[�J���ϐ�
	bool bLanding = false;					//���n���Ă��邩�ǂ���
	float Width = fWidth;					//�v���C���[�̕�
	float Height = fHeight;					//�v���C���[�̍���
	float fX[4];
	float fY[4];
	D3DXVECTOR3* PosOld = pPosOld;			//�O�t���[���̃|�S�̈ʒu
	D3DXVECTOR3* Pos = pPos;				//���t���[���̃|�S�̈ʒu
	D3DXVECTOR3* PYPosOld = pPYPosOld;		//�O�t���[���̃v���C���[�̈ʒu
	D3DXVECTOR3* PYPos = pPYPos;			//���t���[���̃v���C���[�̈ʒu
	Player* pPlayer = GetPlayer();


	//���[�v����
	for (int nCntBlock = 0; nCntBlock < MAX_MOVEBLOCK; nCntBlock++)
	{//�u���b�N�̍ő吔�����[�v����


		if (g_aMoveBlock[nCntBlock].bUse == true)
		{//�u���b�N���g�p���Ă���ꍇ

			switch (g_aMoveBlock[nCntBlock].nType)
			{
			case BLOCK_BEFORE://���O

				fX[0] = (g_aMoveBlock[nCntBlock].pos.x - g_aMoveBlock[nCntBlock].fWidth - pPos->x) * (g_aMoveBlock[nCntBlock].pos.x - g_aMoveBlock[nCntBlock].fWidth - pPos->x);
				fY[0] = (g_aMoveBlock[nCntBlock].pos.y - g_aMoveBlock[nCntBlock].fHeight - pPos->y) * (g_aMoveBlock[nCntBlock].pos.y - g_aMoveBlock[nCntBlock].fHeight - pPos->y);
				fX[1] = (g_aMoveBlock[nCntBlock].pos.x + g_aMoveBlock[nCntBlock].fWidth - pPos->x) * (g_aMoveBlock[nCntBlock].pos.x + g_aMoveBlock[nCntBlock].fWidth - pPos->x);
				fY[1] = (g_aMoveBlock[nCntBlock].pos.y + g_aMoveBlock[nCntBlock].fHeight - pPos->y) * (g_aMoveBlock[nCntBlock].pos.y + g_aMoveBlock[nCntBlock].fHeight - pPos->y);
				fX[2] = (g_aMoveBlock[nCntBlock].pos.x - g_aMoveBlock[nCntBlock].fWidth - pPYPos->x) * (g_aMoveBlock[nCntBlock].pos.x - g_aMoveBlock[nCntBlock].fWidth - pPYPos->x);
				fY[2] = (g_aMoveBlock[nCntBlock].pos.y - g_aMoveBlock[nCntBlock].fHeight - pPYPos->y) * (g_aMoveBlock[nCntBlock].pos.y - g_aMoveBlock[nCntBlock].fHeight - pPYPos->y);
				fX[3] = (g_aMoveBlock[nCntBlock].pos.x + g_aMoveBlock[nCntBlock].fWidth - pPYPos->x) * (g_aMoveBlock[nCntBlock].pos.x + g_aMoveBlock[nCntBlock].fWidth - pPYPos->x);
				fY[3] = (g_aMoveBlock[nCntBlock].pos.y + g_aMoveBlock[nCntBlock].fHeight - pPYPos->y) * (g_aMoveBlock[nCntBlock].pos.y + g_aMoveBlock[nCntBlock].fHeight - pPYPos->y);

				break;

			case BLOCK_MOVE://�������Ă�Ƃ�

				fX[0] = (g_aMoveBlock[nCntBlock].pos.x - g_aMoveBlock[nCntBlock].fWidth - pPos->x) * (g_aMoveBlock[nCntBlock].pos.x - g_aMoveBlock[nCntBlock].fWidth - pPos->x);
				fY[0] = (g_aMoveBlock[nCntBlock].pos.y - g_aMoveBlock[nCntBlock].fHeight - pPos->y) * (g_aMoveBlock[nCntBlock].pos.y - g_aMoveBlock[nCntBlock].fHeight - pPos->y);
				fX[1] = (g_aMoveBlock[nCntBlock].pos.x + g_aMoveBlock[nCntBlock].fWidth - pPos->x) * (g_aMoveBlock[nCntBlock].pos.x + g_aMoveBlock[nCntBlock].fWidth - pPos->x);
				fY[1] = (g_aMoveBlock[nCntBlock].pos.y + g_aMoveBlock[nCntBlock].fHeight - pPos->y) * (g_aMoveBlock[nCntBlock].pos.y + g_aMoveBlock[nCntBlock].fHeight - pPos->y);
				fX[2] = (g_aMoveBlock[nCntBlock].pos.x - g_aMoveBlock[nCntBlock].fWidth - pPYPos->x) * (g_aMoveBlock[nCntBlock].pos.x - g_aMoveBlock[nCntBlock].fWidth - pPYPos->x);
				fY[2] = (g_aMoveBlock[nCntBlock].pos.y - g_aMoveBlock[nCntBlock].fHeight - pPYPos->y) * (g_aMoveBlock[nCntBlock].pos.y - g_aMoveBlock[nCntBlock].fHeight - pPYPos->y);
				fX[3] = (g_aMoveBlock[nCntBlock].pos.x + g_aMoveBlock[nCntBlock].fWidth - pPYPos->x) * (g_aMoveBlock[nCntBlock].pos.x + g_aMoveBlock[nCntBlock].fWidth - pPYPos->x);
				fY[3] = (g_aMoveBlock[nCntBlock].pos.y + g_aMoveBlock[nCntBlock].fHeight - pPYPos->y) * (g_aMoveBlock[nCntBlock].pos.y + g_aMoveBlock[nCntBlock].fHeight - pPYPos->y);

				break;

			case BLOCK_AFTER://�g��������

				fX[0] = (g_aMoveBlock[nCntBlock].pos.x - g_aMoveBlock[nCntBlock].fWidth - pPos->x) * (g_aMoveBlock[nCntBlock].pos.x - g_aMoveBlock[nCntBlock].fWidth - pPos->x);
				fY[0] = (g_aMoveBlock[nCntBlock].pos.y - g_aMoveBlock[nCntBlock].fHeight - pPos->y) * (g_aMoveBlock[nCntBlock].pos.y - g_aMoveBlock[nCntBlock].fHeight - pPos->y);
				fX[1] = (g_aMoveBlock[nCntBlock].pos.x + g_aMoveBlock[nCntBlock].fWidth - pPos->x) * (g_aMoveBlock[nCntBlock].pos.x + g_aMoveBlock[nCntBlock].fWidth - pPos->x);
				fY[1] = (g_aMoveBlock[nCntBlock].pos.y + g_aMoveBlock[nCntBlock].fHeight - pPos->y) * (g_aMoveBlock[nCntBlock].pos.y + g_aMoveBlock[nCntBlock].fHeight - pPos->y);
				fX[2] = (g_aMoveBlock[nCntBlock].pos.x - g_aMoveBlock[nCntBlock].fWidth - pPYPos->x) * (g_aMoveBlock[nCntBlock].pos.x - g_aMoveBlock[nCntBlock].fWidth - pPYPos->x);
				fY[2] = (g_aMoveBlock[nCntBlock].pos.y - g_aMoveBlock[nCntBlock].fHeight - pPYPos->y) * (g_aMoveBlock[nCntBlock].pos.y - g_aMoveBlock[nCntBlock].fHeight - pPYPos->y);
				fX[3] = (g_aMoveBlock[nCntBlock].pos.x + g_aMoveBlock[nCntBlock].fWidth - pPYPos->x) * (g_aMoveBlock[nCntBlock].pos.x + g_aMoveBlock[nCntBlock].fWidth - pPYPos->x);
				fY[3] = (g_aMoveBlock[nCntBlock].pos.y + g_aMoveBlock[nCntBlock].fHeight - pPYPos->y) * (g_aMoveBlock[nCntBlock].pos.y + g_aMoveBlock[nCntBlock].fHeight - pPYPos->y);

				break;
			}

			switch (g_aMoveBlock[nCntBlock].nType)
			{
			case BLOCK_BEFORE:

				if ((pPos->x > g_aMoveBlock[nCntBlock].pos.x - g_aMoveBlock[nCntBlock].fWidth) && (pPos->x < g_aMoveBlock[nCntBlock].pos.x + g_aMoveBlock[nCntBlock].fWidth) && (pPos->y > g_aMoveBlock[nCntBlock].pos.y - g_aMoveBlock[nCntBlock].fHeight - MAX_POSCIRCLE) && (pPos->y < g_aMoveBlock[nCntBlock].pos.y + g_aMoveBlock[nCntBlock].fHeight + MAX_POSCIRCLE))
				{//�㉺�̃|�S�����蔻��

			
					//���n�̔����true�ɂ���
					bLanding = true;

					SetParticle(pPlayer->pos, 50.0f, 30.0f, 629, 40, PARTICLETYPE_1);

					//y������move������
					pMove->y = 0.0f;

					pPlayer->move.x = -sinf(pPlayer->rot.z) * JUMP;	//�W�����v�͉��Z
					pPlayer->move.y = -cosf(pPlayer->rot.z) * JUMP;	//�W�����v�͉��Z
					pPlayer->bJump = true;

				}


				if ((pPos->x > g_aMoveBlock[nCntBlock].pos.x - g_aMoveBlock[nCntBlock].fWidth - MAX_POSCIRCLE) && (pPos->x < g_aMoveBlock[nCntBlock].pos.x + g_aMoveBlock[nCntBlock].fWidth + MAX_POSCIRCLE) && (pPos->y > g_aMoveBlock[nCntBlock].pos.y - g_aMoveBlock[nCntBlock].fHeight) && (pPos->y < g_aMoveBlock[nCntBlock].pos.y + g_aMoveBlock[nCntBlock].fHeight))
				{//���E�̃|�S�����蔻��


					//���n�̔����true�ɂ���
					bLanding = true;

					SetParticle(pPlayer->pos, 50.0f, 30.0f, 629, 40, PARTICLETYPE_1);

					//�W�����v���Ă���

					//x������move������
					pMove->x = 0.0f;
					pPlayer->move.x = -sinf(pPlayer->rot.z) * JUMP;	//�W�����v�͉��Z
					pPlayer->move.y = -cosf(pPlayer->rot.z) * JUMP;	//�W�����v�͉��Z
					pPlayer->bJump = true;

				}


				if (fX[0] + fY[0] < MAX_POSCIRCLE * MAX_POSCIRCLE)
				{//�E��̃|�S�����蔻��


					//���n�̔����true�ɂ���
					bLanding = true;

					SetParticle(pPlayer->pos, 50.0f, 30.0f, 629, 40, PARTICLETYPE_1);

					//�W�����v���Ă���

					//x������move������
					pMove->x = 0.0f;

					pPlayer->move.x = -sinf(pPlayer->rot.z) * JUMP;	//�W�����v�͉��Z
					pPlayer->move.y = -cosf(pPlayer->rot.z) * JUMP;	//�W�����v�͉��Z
					pPlayer->bJump = true;
				}


				if (fX[1] + fY[0] < MAX_POSCIRCLE * MAX_POSCIRCLE)
				{//����̃|�S�����蔻��


					//���n�̔����true�ɂ���
					bLanding = true;

					SetParticle(pPlayer->pos, 50.0f, 30.0f, 629, 40, PARTICLETYPE_1);

					//�W�����v���Ă���

					//x������move������
					pMove->x = 0.0f;
					pPlayer->move.x = -sinf(pPlayer->rot.z) * JUMP;	//�W�����v�͉��Z
					pPlayer->move.y = -cosf(pPlayer->rot.z) * JUMP;	//�W�����v�͉��Z
					pPlayer->bJump = true;
				}


				if (fX[0] + fY[1] < MAX_POSCIRCLE * MAX_POSCIRCLE)
				{//�E���̃|�S�����蔻��


					//���n�̔����true�ɂ���
					bLanding = true;

					SetParticle(pPlayer->pos, 50.0f, 30.0f, 629, 40, PARTICLETYPE_1);

					//�W�����v���Ă���

					//x������move������
					pMove->x = 0.0f;
					pPlayer->move.x = -sinf(pPlayer->rot.z) * JUMP;	//�W�����v�͉��Z
					pPlayer->move.y = -cosf(pPlayer->rot.z) * JUMP;	//�W�����v�͉��Z
					pPlayer->bJump = true;
				}


				if (fX[1] + fY[1] < MAX_POSCIRCLE * MAX_POSCIRCLE)
				{//�����̃|�S�����蔻��


					//���n�̔����true�ɂ���
					bLanding = true;

					SetParticle(pPlayer->pos, 50.0f, 30.0f, 629, 40, PARTICLETYPE_1);

					//�W�����v���Ă���

					//x������move������
					pMove->x = 0.0f;
					pPlayer->move.x = -sinf(pPlayer->rot.z) * JUMP;	//�W�����v�͉��Z
					pPlayer->move.y = -cosf(pPlayer->rot.z) * JUMP;	//�W�����v�͉��Z
					pPlayer->bJump = true;
				}

				if ((pPYPos->x > g_aMoveBlock[nCntBlock].pos.x - g_aMoveBlock[nCntBlock].fWidth) && (pPYPos->x < g_aMoveBlock[nCntBlock].pos.x + g_aMoveBlock[nCntBlock].fWidth) && (pPYPos->y > g_aMoveBlock[nCntBlock].pos.y - g_aMoveBlock[nCntBlock].fHeight - MAX_POSCIRCLE) && (pPYPos->y < g_aMoveBlock[nCntBlock].pos.y + g_aMoveBlock[nCntBlock].fHeight + MAX_POSCIRCLE))
				{//�㉺�̃v���C���[�����蔻��

					if (pPosOld->y >= g_aMoveBlock[nCntBlock].pos.y + g_aMoveBlock[nCntBlock].fHeight + MAX_POSCIRCLE)
					{
						g_aMoveBlock[nCntBlock].nType = BLOCK_MOVE;
					}
					else
					{
						//�v���C���[�̃��C�t��1���炷
						pPlayer->nLife--;
					}

					//y������move������
					pMove->y = 0.0f;

				}


				if ((pPYPos->x > g_aMoveBlock[nCntBlock].pos.x - g_aMoveBlock[nCntBlock].fWidth - MAX_POSCIRCLE) && (pPYPos->x < g_aMoveBlock[nCntBlock].pos.x + g_aMoveBlock[nCntBlock].fWidth + MAX_POSCIRCLE) && (pPYPos->y > g_aMoveBlock[nCntBlock].pos.y - g_aMoveBlock[nCntBlock].fHeight) && (pPYPos->y < g_aMoveBlock[nCntBlock].pos.y + g_aMoveBlock[nCntBlock].fHeight))
				{//���E�̃v���C���[�����蔻��


					if (pPosOld->y >= g_aMoveBlock[nCntBlock].pos.y + g_aMoveBlock[nCntBlock].fHeight + MAX_POSCIRCLE)
					{
						g_aMoveBlock[nCntBlock].nType = BLOCK_MOVE;
					}

					//x������move������
					pMove->x = 0.0f;
					//x������move������
					pMove->y = 0.0f;

				}


				if (fX[2] + fY[2] < MAX_POSCIRCLE * MAX_POSCIRCLE)
				{//�E��̃v���C���[�����蔻��


					//�v���C���[�̃��C�t��1���炷
					pPlayer->nLife--;


					//x������move������
					pMove->x = 0.0f;
					//x������move������
					pMove->y = 0.0f;
				}


				if (fX[3] + fY[2] < MAX_POSCIRCLE * MAX_POSCIRCLE)
				{//����̃v���C���[�����蔻��


					//�v���C���[�̃��C�t��1���炷
					pPlayer->nLife--;

					//x������move������
					pMove->x = 0.0f;
					//x������move������
					pMove->y = 0.0f;
				}


				if (fX[2] + fY[3] < MAX_POSCIRCLE * MAX_POSCIRCLE)
				{//�E���̃v���C���[�����蔻��


					if (pPosOld->y >= g_aMoveBlock[nCntBlock].pos.y + g_aMoveBlock[nCntBlock].fHeight + MAX_POSCIRCLE)
					{
						g_aMoveBlock[nCntBlock].nType = BLOCK_MOVE;
					}

					//x������move������
					pMove->x = 0.0f;
					//x������move������
					pMove->y = 0.0f;
				}


				if (fX[3] + fY[3] < MAX_POSCIRCLE * MAX_POSCIRCLE)
				{//�����̃v���C���[�����蔻��


					if (pPosOld->y >= g_aMoveBlock[nCntBlock].pos.y + g_aMoveBlock[nCntBlock].fHeight + MAX_POSCIRCLE)
					{
						g_aMoveBlock[nCntBlock].nType = BLOCK_MOVE;
					}


					//x������move������
					pMove->x = 0.0f;
					//x������move������
					pMove->y = 0.0f;
				}

				break;
			case BLOCK_AFTER:
				if ((pPos->x > g_aMoveBlock[nCntBlock].pos.x - g_aMoveBlock[nCntBlock].fWidth) && (pPos->x < g_aMoveBlock[nCntBlock].pos.x + g_aMoveBlock[nCntBlock].fWidth) && (pPos->y > g_aMoveBlock[nCntBlock].pos.y - g_aMoveBlock[nCntBlock].fHeight - MAX_POSCIRCLE)&& (pPosOld->y + MAX_POSCIRCLE < g_aMoveBlock[nCntBlock].pos.y - g_aMoveBlock[nCntBlock].fHeight) && (pPos->y < g_aMoveBlock[nCntBlock].pos.y + g_aMoveBlock[nCntBlock].fHeight + MAX_POSCIRCLE))
				{//�㉺�̃|�S�����蔻��


					//���n�̔����true�ɂ���
					bLanding = true;

					//y������move������
					pMove->y = 0.0f;

					pPlayer->move.x = -sinf(pPlayer->rot.z) * JUMP;	//�W�����v�͉��Z
					pPlayer->move.y = -cosf(pPlayer->rot.z) * JUMP;	//�W�����v�͉��Z
					pPlayer->bJump = true;

				}


				if ((pPos->x > g_aMoveBlock[nCntBlock].pos.x - g_aMoveBlock[nCntBlock].fWidth - MAX_POSCIRCLE) && (pPos->x < g_aMoveBlock[nCntBlock].pos.x + g_aMoveBlock[nCntBlock].fWidth + MAX_POSCIRCLE) && (pPos->y > g_aMoveBlock[nCntBlock].pos.y - g_aMoveBlock[nCntBlock].fHeight) && (pPos->y < g_aMoveBlock[nCntBlock].pos.y + g_aMoveBlock[nCntBlock].fHeight) && (pPosOld->y + MAX_POSCIRCLE < g_aMoveBlock[nCntBlock].pos.y - g_aMoveBlock[nCntBlock].fHeight))
				{//���E�̃|�S�����蔻��


					//���n�̔����true�ɂ���
					bLanding = true;

					//�W�����v���Ă���

					//x������move������
					pMove->x = 0.0f;
					pPlayer->move.x = -sinf(pPlayer->rot.z) * JUMP;	//�W�����v�͉��Z
					pPlayer->move.y = -cosf(pPlayer->rot.z) * JUMP;	//�W�����v�͉��Z
					pPlayer->bJump = true;

				}


				if (fX[0] + fY[0] < MAX_POSCIRCLE * MAX_POSCIRCLE && (pPosOld->y + MAX_POSCIRCLE < g_aMoveBlock[nCntBlock].pos.y - g_aMoveBlock[nCntBlock].fHeight))
				{//�E��̃|�S�����蔻��


					//���n�̔����true�ɂ���
					bLanding = true;

					//�W�����v���Ă���

					//x������move������
					pMove->x = 0.0f;

					pPlayer->move.x = -sinf(pPlayer->rot.z) * JUMP;	//�W�����v�͉��Z
					pPlayer->move.y = -cosf(pPlayer->rot.z) * JUMP;	//�W�����v�͉��Z
					pPlayer->bJump = true;
				}


				if (fX[1] + fY[0] < MAX_POSCIRCLE * MAX_POSCIRCLE && (pPosOld->y + MAX_POSCIRCLE < g_aMoveBlock[nCntBlock].pos.y - g_aMoveBlock[nCntBlock].fHeight))
				{//����̃|�S�����蔻��


					//���n�̔����true�ɂ���
					bLanding = true;

					//�W�����v���Ă���

					//x������move������
					pMove->x = 0.0f;
					pPlayer->move.x = -sinf(pPlayer->rot.z) * JUMP;	//�W�����v�͉��Z
					pPlayer->move.y = -cosf(pPlayer->rot.z) * JUMP;	//�W�����v�͉��Z
					pPlayer->bJump = true;
				}


				if (fX[0] + fY[1] < MAX_POSCIRCLE * MAX_POSCIRCLE && (pPosOld->y + MAX_POSCIRCLE < g_aMoveBlock[nCntBlock].pos.y - g_aMoveBlock[nCntBlock].fHeight))
				{//�E���̃|�S�����蔻��


					//���n�̔����true�ɂ���
					bLanding = true;

					//�W�����v���Ă���

					//x������move������
					pMove->x = 0.0f;
					pPlayer->move.x = -sinf(pPlayer->rot.z) * JUMP;	//�W�����v�͉��Z
					pPlayer->move.y = -cosf(pPlayer->rot.z) * JUMP;	//�W�����v�͉��Z
					pPlayer->bJump = true;
				}


				if (fX[1] + fY[1] < MAX_POSCIRCLE * MAX_POSCIRCLE && (pPosOld->y + MAX_POSCIRCLE < g_aMoveBlock[nCntBlock].pos.y - g_aMoveBlock[nCntBlock].fHeight))
				{//�����̃|�S�����蔻��


					//���n�̔����true�ɂ���
					bLanding = true;

					//�W�����v���Ă���

					//x������move������
					pMove->x = 0.0f;
					pPlayer->move.x = -sinf(pPlayer->rot.z) * JUMP;	//�W�����v�͉��Z
					pPlayer->move.y = -cosf(pPlayer->rot.z) * JUMP;	//�W�����v�͉��Z
					pPlayer->bJump = true;
				}

				if ((pPYPos->x > g_aMoveBlock[nCntBlock].pos.x - g_aMoveBlock[nCntBlock].fWidth) && (pPYPos->x < g_aMoveBlock[nCntBlock].pos.x + g_aMoveBlock[nCntBlock].fWidth) && (pPYPos->y > g_aMoveBlock[nCntBlock].pos.y - g_aMoveBlock[nCntBlock].fHeight - MAX_POSCIRCLE) && (pPosOld->y + MAX_POSCIRCLE < g_aMoveBlock[nCntBlock].pos.y - g_aMoveBlock[nCntBlock].fHeight ))
				{//�㉺�̃v���C���[�����蔻��


					//�v���C���[�̃��C�t��1���炷
					pPlayer->nLife--;

					//y������move������
					pMove->y = 0.0f;

				}


				if ((pPYPos->x > g_aMoveBlock[nCntBlock].pos.x - g_aMoveBlock[nCntBlock].fWidth - MAX_POSCIRCLE) && (pPYPos->x < g_aMoveBlock[nCntBlock].pos.x + g_aMoveBlock[nCntBlock].fWidth + MAX_POSCIRCLE) && (pPYPos->y > g_aMoveBlock[nCntBlock].pos.y - g_aMoveBlock[nCntBlock].fHeight) && (pPYPos->y < g_aMoveBlock[nCntBlock].pos.y + g_aMoveBlock[nCntBlock].fHeight) && (pPosOld->y + MAX_POSCIRCLE < g_aMoveBlock[nCntBlock].pos.y - g_aMoveBlock[nCntBlock].fHeight))
				{//���E�̃v���C���[�����蔻��


					//�v���C���[�̃��C�t��1���炷
					pPlayer->nLife--;

					//x������move������
					pMove->x = 0.0f;
					//x������move������
					pMove->y = 0.0f;

				}


				if (fX[2] + fY[2] < MAX_POSCIRCLE * MAX_POSCIRCLE && (pPosOld->y + MAX_POSCIRCLE < g_aMoveBlock[nCntBlock].pos.y - g_aMoveBlock[nCntBlock].fHeight))
				{//�E��̃v���C���[�����蔻��


					//�v���C���[�̃��C�t��1���炷
					pPlayer->nLife--;

					//x������move������
					pMove->x = 0.0f;
					//x������move������
					pMove->y = 0.0f;
				}


				if (fX[3] + fY[2] < MAX_POSCIRCLE * MAX_POSCIRCLE && (pPosOld->y + MAX_POSCIRCLE < g_aMoveBlock[nCntBlock].pos.y - g_aMoveBlock[nCntBlock].fHeight))
				{//����̃v���C���[�����蔻��


					//�v���C���[�̃��C�t��1���炷
					pPlayer->nLife--;

					//x������move������
					pMove->x = 0.0f;
					//x������move������
					pMove->y = 0.0f;
				}


				if (fX[2] + fY[3] < MAX_POSCIRCLE * MAX_POSCIRCLE && (pPosOld->y + MAX_POSCIRCLE < g_aMoveBlock[nCntBlock].pos.y - g_aMoveBlock[nCntBlock].fHeight))
				{//�E���̃v���C���[�����蔻��


					//�v���C���[�̃��C�t��1���炷
					pPlayer->nLife--;

					//x������move������
					pMove->x = 0.0f;
					//x������move������
					pMove->y = 0.0f;
				}


				if (fX[3] + fY[3] < MAX_POSCIRCLE * MAX_POSCIRCLE && (pPosOld->y + MAX_POSCIRCLE < g_aMoveBlock[nCntBlock].pos.y - g_aMoveBlock[nCntBlock].fHeight))
				{//�����̃v���C���[�����蔻��


					//�v���C���[�̃��C�t��1���炷
					pPlayer->nLife--;

					//x������move������
					pMove->x = 0.0f;
					//x������move������
					pMove->y = 0.0f;
				}
				break;
			}

		}
	}

	//bLanding�̒l��Ԃ�
	return bLanding;
}