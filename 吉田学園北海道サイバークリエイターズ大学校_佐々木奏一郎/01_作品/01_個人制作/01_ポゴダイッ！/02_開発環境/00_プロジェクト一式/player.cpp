//=============================================================================
//
//	�v���C���[���� [player.cpp]
// Author : ���X�ؑt��Y
//
//=============================================================================
#include "main.h"
#include "player.h"
#include "input.h" 
#include "block.h"
#include "moveblock.h"
#include "effect.h"
#include "sound.h"
#include "score.h"
#include "fade.h"
#include "particle.h"
//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTexturePlayer2=NULL;		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayer = NULL;//���_�o�b�t�@�ւ̃|�C���^
Player g_player;//�v���C���[�̏��

//=====================
//�|���S���̏���������
//=====================
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^
	//�f�o�C�X�̎擾
	pDevice = GetDevice();
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\hoppingman000.png",
		&g_pTexturePlayer2);
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*4,//(sizeof(VERTEX_2D)*�K�v�Ȓ��_��
		D3DUSAGE_WRITEONLY,
		 FVF_VERTEX_2D ,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPlayer,
		NULL);
	g_player.nCounterAnim=0;							//�J�E���^�[������������
	g_player.nPatternAnim = 0;							//�p�^�[��No.������������
	g_player.pos = D3DXVECTOR3(200,500, 0);				//�ʒu������������
	g_player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ړ��l������������
	g_player.rot= D3DXVECTOR3(0.0f, 1.0f, 0.0f);		//����������������
	g_player.state= PLAYERSTATE_NORMAL;					//�v���C���[�̏��
	g_player.nCntState=0;								//��ԊǗ��J�E���^�[
	g_player.nLife=1;									//�̗�
	g_player.bDisp=true;								//�\�����邩���Ȃ���
	g_player.bJump = true;								//�W�����v���Ă��邩���ĂȂ���
	g_player.bRightMove = true;							//�E�Ɍ����Ă��邩�ǂ���
	g_player.bMove = false;								//�����Ă��邩�ǂ���
	g_player.bUse = false;								//�g���Ă��邩�ǂ���
	g_player.pBlock = NULL;								//pBlock������������

	//�Ίp���̒������Z�o����
	g_player.fLength = sqrtf(((OBJ_WIDTH * OBJ_WIDTH)/2.0f) + (OBJ_HEIGHT * OBJ_HEIGHT));
	g_player.fAngle = atan2f(OBJ_WIDTH, (OBJ_HEIGHT*2.0f));

	//�����蔻��̒��S�����炷
	g_player.posPGCircle.x = g_player.pos.x - sinf(g_player.rot.z) * MAX_PGPOS;
	g_player.posPGCircle.y = g_player.pos.y - cosf(g_player.rot.z) * MAX_PGPOS;

	g_player.posPYCircle.x = g_player.pos.x - sinf(g_player.rot.z) * MAX_PYPOS;
	g_player.posPYCircle.y = g_player.pos.y - cosf(g_player.rot.z) * MAX_PYPOS;

	VERTEX_2D* pVtx=0;//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);
	//���_���W�̐ݒ�
	pVtx[0].pos.x = g_player.pos.x + sinf(g_player.rot.z - (D3DX_PI - g_player.fAngle)) * g_player.fLength;
	pVtx[0].pos.y = g_player.pos.y + cosf(g_player.rot.z - (D3DX_PI - g_player.fAngle)) * g_player.fLength;
	pVtx[0].pos.z = 0.0f;
	
	pVtx[1].pos.x = g_player.pos.x + sinf(g_player.rot.z + (D3DX_PI - g_player.fAngle)) * g_player.fLength;
	pVtx[1].pos.y = g_player.pos.y + cosf(g_player.rot.z + (D3DX_PI - g_player.fAngle)) * g_player.fLength;
	pVtx[1].pos.z = 0.0f;
	
	pVtx[2].pos.x = g_player.pos.x + sinf(g_player.rot.z - (D3DX_PI/2.0f)) * (OBJ_WIDTH / 2.0f);
	pVtx[2].pos.y = g_player.pos.y + cosf(g_player.rot.z - (D3DX_PI / 2.0f)) * (OBJ_WIDTH / 2.0f);
	pVtx[2].pos.z = 0.0f;													
																			
	pVtx[3].pos.x = g_player.pos.x + sinf(g_player.rot.z + (D3DX_PI / 2.0f)) * (OBJ_WIDTH / 2.0f);
	pVtx[3].pos.y = g_player.pos.y + cosf(g_player.rot.z + (D3DX_PI / 2.0f)) * (OBJ_WIDTH / 2.0f);
	pVtx[3].pos.z = 0.0f;

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;
	//���_�J���[�̐ݒ�@�@�@�@
	pVtx[0].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f,0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f,0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPlayer->Unlock();
}

//===================
//�|���S���̏I������
//===================
void UninitPlayer(void)
{
	StopSound();
	//�e�N�X�`���̔j��
	if (g_pTexturePlayer2 != NULL)
	{
		g_pTexturePlayer2->Release();
		g_pTexturePlayer2 = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffPlayer != NULL)
	{
		g_pVtxBuffPlayer->Release();
		g_pVtxBuffPlayer = NULL;
	}
}

//====================
//�|���S���̍X�V����
//====================
void UpdatePlayer(void)
{
	VERTEX_2D* pVtx=0;					//���_���ւ̃|�C���^
	XINPUT_STATE* pStick = GetJoypad();	//�X�e�B�b�N�擾
	static float fData = 0.25;
	bool goal=GetGoal();
	if (g_player.nLife > 0&& goal == false)
	{
		if (GetKeyboardPress(DIK_Q) == true)
		{//Q�L�[�������ꂽ�Ƃ�
			g_player.rot.z += 0.05f;
		}

		else if (GetKeyboardPress(DIK_E) == true)
		{//E�L�[�������ꂽ�Ƃ�
			g_player.rot.z -= 0.05f;
		}

		if (GetJoypadPress(JOYKEY_LEFT) == true||pStick->Gamepad.sThumbLX<=-20000)
		{//���{�^���������ꂽ�Ƃ�
			g_player.rot.z += 0.05f;
		}

		else if (GetJoypadPress(JOYKEY_RIGHT) == true || pStick->Gamepad.sThumbLX >= 20000)
		{//�E�{�^���������ꂽ�Ƃ�
			g_player.rot.z -= 0.05f;
		}
		else if (GetJoypadPress(JOYKEY_RIGHTS) == true && GetJoypadPress(JOYKEY_LEFTS) == true|| KeyboardTrigger(DIK_F) == true)
		{
			SetFade(MODE_GAME);
		}
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPlayer->Unlock();




	//�d�͉��Z
	g_player.move.y += GRAVI;

	if (goal == false)
	{
		//�ʒu�̍X�V
		g_player.pos.x += g_player.move.x;
		g_player.pos.y += g_player.move.y;
	}


	//�O��̈ʒu��ۑ�
	g_player.posPGOld = g_player.posPGCircle;

	g_player.posPYOld = g_player.posPYCircle;
	if (g_player.nLife <= 0)
	{
		g_player.rot.z += 0.2f;
	}
	//�ʒu���̍X�V
	g_player.posPGCircle.x = g_player.pos.x - sinf(g_player.rot.z) * MAX_PGPOS;
	g_player.posPGCircle.y = g_player.pos.y - cosf(g_player.rot.z) * MAX_PGPOS;

	g_player.posPYCircle.x = g_player.pos.x - sinf(g_player.rot.z) * MAX_PYPOS;
	g_player.posPYCircle.y = g_player.pos.y - cosf(g_player.rot.z) * MAX_PYPOS;

	SetEffect(g_player.pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f), 5.0f, 40, EFFECTTYPE_PLAYER);
	if (g_player.nLife > 0)
	{
		//�u���b�N�̓����蔻��
		g_player.bJump = !CollisionBlock(&g_player.posPGCircle, &g_player.posPGOld, &g_player.posPYCircle, &g_player.posPYOld, &g_player.move, OBJ_WIDTH, OBJ_HEIGHT, &g_player.pBlock);
	}

	if (g_player.pBlock != NULL && g_player.bJump == false)
	{//�v���C���[�����n�����u��

		switch (g_player.pBlock->nType)
		{
		case BLOCK_NORMAL:
			PlaySound(SOUND_LABEL_RAND01);
			SetParticle(g_player.pos, 50.0f, 25.0f, 629, 40, PARTICLETYPE_1);
			g_player.move.x = -sinf(g_player.rot.z) * JUMP;	//�W�����v�͉��Z
			g_player.move.y = -cosf(g_player.rot.z) * JUMP;	//�W�����v�͉��Z
			g_player.bJump = true;
			break;

		case BLOCK_BUTTON:
			PlaySound(SOUND_LABEL_RAND01);
			SetParticle(g_player.pos, 50.0f, 25.0f, 629, 40, PARTICLETYPE_1);
			g_player.move.x = -sinf(g_player.rot.z) * JUMP;	//�W�����v�͉��Z
			g_player.move.y = -cosf(g_player.rot.z) * JUMP;	//�W�����v�͉��Z
			g_player.bJump = true;
			break;

		case BLOCK_MOVEWALL:
			PlaySound(SOUND_LABEL_RAND01);
			SetParticle(g_player.pos, 50.0f, 25.0f, 629, 40, PARTICLETYPE_1);
			g_player.move.x = -sinf(g_player.rot.z) * JUMP;	//�W�����v�͉��Z
			g_player.move.y = -cosf(g_player.rot.z) * JUMP;	//�W�����v�͉��Z
			g_player.bJump = true;
			break;

		case BLOCK_SLIME:
			SetParticle(g_player.pos, 50.0f, 25.0f, 629, 40, PARTICLETYPE_1);
			g_player.move.x = -sinf(g_player.rot.z) * SLIMEJUMP;	//�W�����v�͉��Z
			g_player.move.y = -cosf(g_player.rot.z) * SLIMEJUMP;	//�W�����v�͉��Z
			g_player.bJump = true;
			break;

		case BLOCK_TRANPORIN:
			SetParticle(g_player.pos, 50.0f, 25.0f, 629, 40, PARTICLETYPE_1);
			g_player.move.x = -sinf(g_player.rot.z) * TRANPORINJUMP;	//�W�����v�͉��Z
			g_player.move.y = -cosf(g_player.rot.z) * TRANPORINJUMP;	//�W�����v�͉��Z
			g_player.bJump = true;
			break;

		case BLOCK_GOAL:
			
			g_player.move.x = -sinf(g_player.rot.z) * JUMP;	//�W�����v�͉��Z
			g_player.move.y = -cosf(g_player.rot.z) * JUMP;	//�W�����v�͉��Z
			g_player.bJump = true;
			break;
		case BLOCK_LR:

			g_player.move.x = g_player.pBlock->move.x;	//�ړ��l���
			g_player.move.y = 0;
			g_player.pos.y = g_player.pBlock->pos.y- g_player.pBlock->fHeight;//Y���Œ�
			if (GetKeyboardPress(DIK_SPACE) == true||GetJoypadPress(JOYKEY_A) == true)
			{//�X�y�[�X���������ꍇ
				PlaySound(SOUND_LABEL_RAND01);
				SetParticle(g_player.pos, 50.0f, 25.0f, 629, 40, PARTICLETYPE_1);
				g_player.move.x = -sinf(g_player.rot.z) * JUMP;	//�W�����v�͉��Z
				g_player.move.y = -cosf(g_player.rot.z) * JUMP;	//�W�����v�͉��Z
				g_player.bJump = true;
			}
			break;
		case BLOCK_UPDOWN:

			g_player.move.y = g_player.pBlock->move.y;	//�W�����v�͉��Z
			g_player.move.x = 0;
			g_player.pos.y = g_player.pBlock->pos.y - g_player.pBlock->fHeight;//Y���Œ�
			if (GetKeyboardPress(DIK_SPACE) == true || GetJoypadPress(JOYKEY_A) == true)
			{
				PlaySound(SOUND_LABEL_RAND01);
				SetParticle(g_player.pos, 50.0f, 25.0f, 629, 40, PARTICLETYPE_1);
				g_player.move.x = -sinf(g_player.rot.z) * JUMP;	//�W�����v�͉��Z
				g_player.move.y = -cosf(g_player.rot.z) * JUMP;	//�W�����v�͉��Z
				g_player.bJump = true;
			}
			break;
		}

	}

	if (g_player.nLife > 0)
	{
		//���[�u�u���b�N�̓����蔻��
		g_player.bJump = !CollisionMoveBlock(&g_player.posPGCircle, &g_player.posPGOld, &g_player.posPYCircle, &g_player.posPYOld, &g_player.move, OBJ_WIDTH, OBJ_HEIGHT);
	}



	if (g_player.pos.y >= 720.0f)
	{//�v���C���[�̈ʒu����ʊO�ɏo���ꍇ

		if (g_player.nLife > 0)
		{
			//�v���C���[�̃��C�t��1���炷
			g_player.nLife--;
		}
		//�W�����v���Ă��Ȃ�
		//g_player.bJump = false;	
	}

	if (g_player.pos.x  <= -150.0f)
	{//�v���C���[���E�̉�ʊO����o���ꍇ

		//���̉�ʊO�Ɉړ�������
		g_player.pos.x = 1400.0f;
	}

	if (g_player.pos.x >= 1500.0f)
	{//�v���C���[�����̉�ʊO����o���ꍇ
		g_player.pos.x = -70.0f;
	}

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);
	//���_���W�̐ݒ�
	pVtx[0].pos.x = g_player.pos.x + sinf(g_player.rot.z - (D3DX_PI - g_player.fAngle)) * g_player.fLength;
	pVtx[0].pos.y = g_player.pos.y + cosf(g_player.rot.z - (D3DX_PI - g_player.fAngle)) * g_player.fLength;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = g_player.pos.x + sinf(g_player.rot.z + (D3DX_PI - g_player.fAngle)) * g_player.fLength;
	pVtx[1].pos.y = g_player.pos.y + cosf(g_player.rot.z + (D3DX_PI - g_player.fAngle)) * g_player.fLength;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = g_player.pos.x + sinf(g_player.rot.z - (D3DX_PI/2)) * (OBJ_WIDTH / 2.0f);
	pVtx[2].pos.y = g_player.pos.y + cosf(g_player.rot.z - (D3DX_PI/2)) * (OBJ_WIDTH / 2.0f);
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = g_player.pos.x + sinf(g_player.rot.z + (D3DX_PI/2)) * (OBJ_WIDTH / 2.0f);
	pVtx[3].pos.y = g_player.pos.y + cosf(g_player.rot.z + (D3DX_PI/2)) * (OBJ_WIDTH / 2.0f);
	pVtx[3].pos.z = 0.0f;

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPlayer->Unlock();
}

//====================
//�|���S���̕`�揈��
//====================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^
	//�f�o�C�X�̎擾
	pDevice = GetDevice();
	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPlayer, 0, sizeof(VERTEX_2D));
	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
 	if (g_player.bDisp == true)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTexturePlayer2);
		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}
}

//=====================
// �v���C���[�̒l��Ԃ�
//=====================
Player* GetPlayer(void)
{
	return &g_player;
}