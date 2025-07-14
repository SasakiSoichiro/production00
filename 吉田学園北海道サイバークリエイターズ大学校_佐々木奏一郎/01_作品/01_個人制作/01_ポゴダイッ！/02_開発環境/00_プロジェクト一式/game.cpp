//=============================================================================
//
//	�Q�[������[game.cpp]
// Author : ���X�ؑt��Y
//
//=============================================================================
#include "game.h"
#include "player.h"
#include "buckground.h"
#include "input.h"
#include "pause.h"
#include "fade.h"
#include "ranking.h"
#include "rankingscore.h"
#include "score.h"
#include "block.h"
#include "moveblock.h"
#include "time.h"
#include "effect.h"
#include "particle.h"
#include "edit.h"
#include "sound.h"
//�O���[�o���ϐ�
GAMESTATE g_gameState = GAMESTATE_NONE;		//�Q�[���̏��
bool g_bPause = false;						//�|�[�Y�����ǂ���
int g_nCntGameState = 0;					//��ԊǗ��J�E���^�[
int g_nCntGameStateB = 0;					//��ԊǗ��J�E���^�[
//=====================
//�Q�[���̏���������
//=====================
void InitGame(void)
{
	//�e�I�u�W�F�N�g�̏���������
	
	//�w�i�̏���������
	InitBuckground();

	//�v���C���[�̏���������
	InitPlayer();

	//�G�t�F�N�g�̏���������
	InitEffect();

	//�p�[�e�B�N���̏���������
	InitParticle();

	//�u���b�N�̏���������
	InitBlock();

	//���[�u�u���b�N�̏���������
	InitMoveBlock();

	//�X�R�A�̏���������
	InitScore();

	//�|�[�Y�̏���������
	InitPause();

	//�^�C���̏���������
	InitTime();

	
	g_gameState = GAMESTATE_NORMAL;		//�ʏ��Ԃɐݒ�
	g_nCntGameState = 0;				//�Q�[���J�E���g������
	g_nCntGameStateB = 0;				//�Q�[���J�E���g������
	g_bPause = false;					//�|�[�Y����
	SetScore(1000);
	LoadEdit();
	PlaySound(SOUND_LABEL_BGM01);
}
//===================
//�Q�[���̏I������
//===================
void UninitGame(void)
{
	//�e�I�u�W�F�N�g�̏I������

	//�T�E���h�̒�~
	StopSound();

	//�w�i�̏I������
	UninitBuckground();

	//�v���C���[�̏I������
	UninitPlayer();

	//�G�t�F�N�g�̏I������
	UninitEffect();

	//�p�[�e�B�N���̏I������
	UninitParticle();

	//�u���b�N�̏I������
	UninitBlock();

	//���[�u�u���b�N�̏I������
	UninitMoveBlock();

	//�X�R�A�̏I������
	UninitScore();

	//�|�[�Y�̏I������
	UninitPause();

	//�^�C���̏I������
	UninitTime();

}
//===================
//�Q�[���̍X�V����
//===================
void UpdateGame(void)
{
	Player *LifePlayer = GetPlayer();
	
	bool goal = GetGoal();
	if (goal==true)
	{
		//���[�h�ݒ�
		g_gameState = GAMESTATE_END;
		g_nCntGameState++;
	}
	if (LifePlayer->nLife <= 0)
	{
		//���[�h�ݒ�
		//g_gameState = GAMESTATE_END;
		SetFade(MODE_GAME);
		//�J�E���g��i�߂�
		g_nCntGameState++;
	}
	if (KeyboardTrigger(DIK_P)==true)
	{//P�L�[�������ꂽ

		g_bPause = g_bPause ? false: true;
	}
	if (JoyPadTrigger(JOYKEY_START) == true)
	{//X�{�^���������ꂽ

		g_bPause = g_bPause ? false : true;
	}
	if (g_bPause == true)
	{//�|�[�Y��

		//�|�[�Y�̍X�V����
		UpdatePause();
	}
	else
	{
		//�e�I�u�W�F�N�g�̍X�V����


		//�w�i�̍X�V����
		UpdateBuckground();

		//�v���C���[�̍X�V����
		UpdatePlayer();

		//�G�t�F�N�g�̍X�V����
		UpdateEffect();

		//�p�[�e�B�N���̍X�V����
		UpdateParticle();

		//�u���b�N�̍X�V����
		UpdateBlock();

		//���[�u�u���b�N�̍X�V����
		UpdateMoveBlock();

		//�X�R�A�̍X�V����
		UpdateScore();

		//�^�C���̍X�V����
		UpdateTime();

		switch (g_gameState)
		{
		case GAMESTATE_NORMAL:
 		
			break;
		case GAMESTATE_END:
			if (g_nCntGameState >= 60)
			{
				AddScore(1000);
				g_nCntGameState = 0;
				g_gameState = GAMESTATE_NONE;//�������Ă��Ȃ���Ԃɐݒ�
				//��ʂ̐ݒ�
				SetFade(MODE_RESULT);
				//�����L���O�̐ݒ�
				ResetRanking();
				SetRanking(GetScore());
			}
			break;
		}
	}
	
}
//=======================
//�Q�[����ʂ̕`�揈��
//=======================
void DrawGame(void)
{
	//�e�I�u�W�F�N�g�̕`�揈��
	

	//�o�b�N�O���E���h�̕`�揈��
	DrawBuckground();

	//�v���C���[�̕`�揈��
	DrawPlayer();

	//�G�t�F�N�g�̕`�揈��
	DrawEffect();

	//�p�[�e�B�N���̕`�揈��
	DrawParticle();

	//�u���b�N�̕`�揈��
	DrawBlock();

	//���[�u�u���b�N�̕`�揈��
	DrawMoveBlock();

	//�^�C���̕`�揈��
	DrawTime();


	if (g_bPause == true)
	{//�|�[�Y��

		//�|�[�Y�̕`�揈��
		DrawPause();
	}

}

//===================
//�Q�[���̏�Ԃ̐ݒ�
//===================
void SetGameState(GAMESTATE state)
{
	g_gameState = state;
	g_nCntGameState = 0;
}

//====================
//�Q�[���̏�Ԃ̎擾
//====================
GAMESTATE GetGameState(void)
{
	return g_gameState;
}

//=====================
//�|�[�Y�̗L�������ݒ�
//=====================
void SetEnblePause(bool bPause)
{
	g_bPause = bPause;
}