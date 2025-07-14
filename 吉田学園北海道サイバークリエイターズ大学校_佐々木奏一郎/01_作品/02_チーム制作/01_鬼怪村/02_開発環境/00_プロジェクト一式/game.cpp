//=============================================================================
//
//	�Q�[������ [game.h]
// Author : Ryuusei Hirata
//
//=============================================================================

#include "input.h"
#include "game.h"
#include "fade.h"
#include "result.h"
#include "camera.h"
#include "light.h"
#include "meshfield.h"
#include "meshwall.h"
#include "model.h"
#include "player.h"
#include "motion.h"
#include "stage.h"
#include "item.h"
#include "block.h"
#include "time.h"
#include "billboard.h"
#include "pause.h"
#include "enemy.h"
#include "edit.h"
#include "sound.h"
#include "gimmick.h"
#include "UI.h"
#include "BloodSplatter.h"
#include "slow.h"
#include "gauge.h"
#include "KeyUI.h"
#include <time.h>
#include "ItemUI.h"
#include "stamina.h"
#include "Recovery.h"
#include "Cancellation.h"
#include "viewportwaku.h"
#include "unlock.h"
#include "pickupUI.h"
#include "buttonUI.h"
#include "objective.h"
#include "flashlight.h"
#include "explain.h"
#include "Particle.h"
#include "effect.h"
#include "bloodflash.h"

//#include "etcUI.h"

// �}�N����`
#define RAND (6) // �����_���p�ϐ�

// �Q�[���̏��
GAMESTATE g_gameState = GAMESTATE_NONE;	// ������

// ��ԊǗ��J�E���^�[
int g_nCounterGameState = 0;

// �|�[�Y
bool g_bPause = false;

// �G�f�B�b�g
bool g_bEdit = false;

bool g_bExplain = false;

//---------------
//	����������
//---------------
void InitGame(void)
{
	////�@BGM��炷
	//PlaySound(SOUND_LABEL_BGM2);


	//�@�e�I�u�W�F�N�g�̏���������

	// ���C�g
	InitLight();

	// �����d��
	InitFlashLight();

	// �J����
	InitCamera();

	// ���b�V���t�B�[���h
	InitMeshfield();

	// �v���C���[
	InitPlayer();

	// �A�C�e��
	Inititem();

	// �^�C��
	InitTime();

	// �G
	InitEnemy();

	// �u���b�N
	InitBlock();

	// �G�f�B�b�g
	InitEdit();

	// �M�~�b�N
	InitGimmick();

	// �r���{�[�h
	InitBillboard();

	// �A�C�e�����W�p�r���{�[�h
	InitPickUpUI();

	// �|�[�Y
	InitPause();

	// �����Ԃ�
	InitBloodSplatter();

	// �X���[
	InitSlow();

	// �e�I�u�W�F�N�g�̐ݒ菈��
	LoadEdit();

	InitUnlock();

	// �Q�[�W
	InitGauge();

	// ����UI
	InitCancellation();

	// ����UI
	InitKeyUI();

	// �A�C�e����UI
	InitItemUI();

	// �X�^�~�i
	InitStamina();
	
	// ��
	InitRecovery();

	// �G���_�̃r���[�|�[�g�̘g
	InitViewUI();

	// �{�^����UI
	InitButtonUI();

	// �ړI�̕\��
	InitObjective();

	//	�A�C�e������
	InitExplain();

	// �G�t�F�N�g
	InitEffect();

	// �p�[�e�B�N��
	InitParticle();

	// ��ʓ_��
	InitBloodFlash();

	//InitEtcUI();

	//int a = rand() % 6 + 1;
	int a = rand() % RAND + 1;

	if (a == 1)
	{
		// ���̏㕔
		Setitem(D3DXVECTOR3(1422.6f, 1.5f, -738.7f), ITEMTYPE_ONE);
	}
	
	if (a == 2)
	{
		// ���̏㕔
		Setitem(D3DXVECTOR3(-94.6f, 1.5f, -608.8f), ITEMTYPE_ONE);
	}

	if (a == 3)
	{
		// ���̏㕔
		Setitem(D3DXVECTOR3(-1199.0f, 1.5f, 396.1f), ITEMTYPE_ONE);
	}

	if (a == 4)
	{
		// ���̏㕔
		Setitem(D3DXVECTOR3(785.7f, 1.5f, 615.6f), ITEMTYPE_ONE);
	}

	if (a == 5)
	{
		// ���̏㕔
		Setitem(D3DXVECTOR3(-94.9f, 1.5f, 480.5f), ITEMTYPE_ONE);
	}

	if (a == 6)
	{//��
		// ���̏㕔
		Setitem(D3DXVECTOR3(-1722.6f, 1.5f, -818.2f), ITEMTYPE_ONE);
	}

	int b = rand() % RAND + 1;

	if (b == 1)
	{
		// ���̉���
		Setitem(D3DXVECTOR3(1807.4f, 1.5f, 790.6f), ITEMTYPE_TWO);
	}

	if (b == 2)
	{
		// ���̉���
		Setitem(D3DXVECTOR3(674.0f, 1.5f, -261.1), ITEMTYPE_TWO);
	}

	if (b == 3)
	{
		// ���̉���
		Setitem(D3DXVECTOR3(-1049.5, 1.5f, 237.3f), ITEMTYPE_TWO);
	}

	if (b == 4)
	{
		// ���̉���
		Setitem(D3DXVECTOR3(-107.7, 1.5f, 498.6), ITEMTYPE_TWO);
	}

	if (b == 5)
	{
		// ���̉���
		Setitem(D3DXVECTOR3(-234.8, 1.5f, -492.5f), ITEMTYPE_TWO);
	}

	if (b == 6)
	{//��
		// ���̉���
		Setitem(D3DXVECTOR3(1809.9f, 1.5f, -807.0f), ITEMTYPE_TWO);
	}

	// �������v
	Setitem(D3DXVECTOR3(-1500.0f, 0.0f, 700.0f), ITEMTYPE_THREE);

	// �~�}��
	Setitem(D3DXVECTOR3(792.3f, 0.0f, -789.5f), ITEMTYPE_FIVE);

	// �����d��
	Setitem(D3DXVECTOR3(1625.0f, 9.0f, 100.0f), ITEMTYPE_SIX);

	// �r���{�[�h(��)
	SetBillboard(D3DXVECTOR3(-100.0f, 50.0f, -200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BILLBOARDTYPE_0,D3DXVECTOR3(15.0f,35.0f,0.0f));

	// �r���{�[�h(�E��)
	SetBillboard(D3DXVECTOR3(-100.0f, 75.0f, -100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BILLBOARDTYPE_1, D3DXVECTOR3(2.0f, 2.0f, 0.0f));
	SetBillboard(D3DXVECTOR3(-100.0f, 75.0f, -100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BILLBOARDTYPE_1, D3DXVECTOR3(2.0f, 2.0f, 0.0f));

	//// �r���{�[�h(0/2)
	//SetBillboard(D3DXVECTOR3(-1785.0f, 75.0f, -300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BILLBOARDTYPE_2, D3DXVECTOR3(4.0f, 4.0f, 0.0f));

	//// �r���{�[�h(1/2)
	//SetBillboard(D3DXVECTOR3(-1780.0f, 75.0f, -300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BILLBOARDTYPE_3, D3DXVECTOR3(4.0f, 4.0f, 0.0f));

	//// �r���{�[�h(�E�o�\)
	//SetBillboard(D3DXVECTOR3(-1780.0f, 75.0f, -300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BILLBOARDTYPE_4, D3DXVECTOR3(4.0f, 4.0f, 0.0f));

	// �r���{�[�h(����)
	SetBillboard(D3DXVECTOR3(-1750.0f, 75.0f, -300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), BILLBOARDTYPE_5, D3DXVECTOR3(1.0f, 1.0f, 0.0f));

	//�@
	//SetPickUpUI(D3DXVECTOR3(0.0f, 50.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//�@�G
	SetEnemy(D3DXVECTOR3(-1750.0f, 0.0f, 0.0f),0);

	// �h�A
	SetGimmick(D3DXVECTOR3(-1800.0f, 0.0f, -300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	// ����UI
	SetKeyUI(D3DXVECTOR3(960.0f, 80.0f, 0.0f), ITEMKEYUITYPE_NO5, 30.0f, 30.0f);

	// �Q�[�W
	SetGauge(D3DXVECTOR3(640.0f, 0.0f, 0.0f));

	// �ڂ�UI
	InitEyeUI();

	// �{�^����UI
	SetButtonUI(D3DXVECTOR3(1030.0f, 125.0f, 0.0f), BUTTONUITYPE_BUTTON_Y, 20.0f, 15.0f);
	SetButtonUI(D3DXVECTOR3(1090.0f, 125.0f, 0.0f), BUTTONUITYPE_BUTTON_Y, 20.0f, 15.0f);
	SetButtonUI(D3DXVECTOR3(1150.0f, 125.0f, 0.0f), BUTTONUITYPE_BUTTON_Y, 20.0f, 15.0f);
	SetButtonUI(D3DXVECTOR3(1090.0f, 25.0f, 0.0f), BUTTONUITYPE_BUTTON_X, 80.0f, 20.0f);

	// �ړI�̕\��
	SetObjective(D3DXVECTOR3(20.0f, 100.0f, 0.0f), 10.0f, 10.0f, OBJECTIVETYPE_WAKU1);
	SetObjective(D3DXVECTOR3(20.0f, 150.0f, 0.0f), 10.0f, 10.0f, OBJECTIVETYPE_WAKU2);
	SetObjective(D3DXVECTOR3(20.0f, 100.0f, 0.0f), 10.0f, 10.0f, OBJECTIVETYPE_CHECK);
	SetObjective(D3DXVECTOR3(145.0f, 100.0f, 0.0f), 110.0f, 15.0f, OBJECTIVETYPE_TEXT1);
	SetObjective(D3DXVECTOR3(165.0f, 150.0f, 0.0f), 130.0f, 15.0f, OBJECTIVETYPE_TEXT2);

	// ����������
	g_bEdit = false;
	g_gameState = GAMESTATE_NORMAL;// �ʏ��Ԃɐݒ�
}

//---------------
//	�I������
//---------------
void UninitGame(void)
{
	////�@���y���~�߂�
	//StopSound();

	//�@�e�I�u�W�F�N�g�̏I������

	// ���C�g
	UninitLight();

	// �����d��
	UninitFlashLight();

	// ���b�V���t�B�[���h
	UninitMeshfield();

	// �J����
	UninitCamera();

	// �u���b�N
	UninitBlock();

	// �v���C���[
	UninitPlayer();

	// �G
	UninitEnemy();

	// �A�C�e��
	Uninititem();

	// �^�C��
	UninitTime();

	// �G�f�B�b�g
	UninitEdit();

	// �r���{�[�h
	UninitBillboard();

	// �A�C�e�����W�p�r���{�[�h
	UninitPickUpUI();

	// �|�[�Y
	UninitPause();

	// �M�~�b�N
	UninitGimmick();

	// �ڂ�UI
	UninitEyeUI();

	// �����Ԃ�
	UinitBloodSplatter();

	// �A�����b�N
	UninitUnlock();

	// �Q�[�W
	UinitGauge();

	// ����UI
	UinitCancellation();

	// ����UI
	UninitKeyUI();

	// �A�C�e����UI
	UninitItemUI();

	// �X�^�~�i
	UninitStamina();

	// ��
	UinitRecovery();

	// �G���_�̃r���[�|�[�g�̘g
	UninitViewUI();

	// �{�^����UI
	UninitButtonUI();

	// �ړI�̕\��
	UninitObjective();

	//	�A�C�e������
	UninitExplain();

	UninitEffect();

	// ��ʓ_��
	UninitBloodFlash();

	//UninitEtcUI();
}

//---------------
//	�X�V����
//---------------
void UpdateGame(void)
{
	bool isGoal = IsGoal();			// �S�[���̔���

	Player* pPlayer = GetPlayer();	// �v���C���[���擾
	EXPLAIN* pExplain = GetExplain();

	// �|�[�Y����
	if (KeybordTrigger(DIK_TAB) || JoyPadTrigger(JOYKEY_START) == true)
	{// TAB
		g_bPause = g_bPause ? false : true;
	}

	if (g_bPause == true)
	{// g_bPause��true
		UpdatePause();
	}

	// �G�f�B�b�g����
	if (g_bEdit == true&&KeybordTrigger(DIK_F1))
	{// F1
		g_bEdit = false;

		// �u���b�N������
		InitBlock();

		// �X�e�[�W�����[�h
		LoadEdit();
	}

	else if (g_bEdit == false && KeybordTrigger(DIK_F1))
	{// b_Edit��true
		g_bEdit = true;
	}
	if (g_bPause == false)
	{// b_Pause��false
		if (g_bEdit == false)
		{// g_Edit��false
			if (pExplain[0].bLook == false && pExplain[1].bLook == false && pExplain[2].bLook == false)
			{
				// �Q�[�����̊e�I�u�W�F�N�g�̍X�V����
# if 1		// ���b�V���t�B�[���h
				UpdateMeshfield();

				// �J����
				UpdateCamera();

				// ���C�g
				UpdateLight();

				// �����d��
				UpdateFlashLight();

				// �u���b�N
				UpdateBlock();

				// �v���C���[
				UpdatePlayer();

				// �G
				UpdateEnemy();

				// �M�~�b�N
				UpdateGimmick();

				// �^�C��
				UpdateTime();

				// �r���{�[�h
				UpdateBillboard();

				// �A�C�e�����W�p�r���{�[�h
				UpdatePickUpUI();

				// �A�C�e��
				Updateitem();

				// �ڂ�UI
				UpdateEyeUI();

				// �����Ԃ�
				UpdateBloodSplatter();

				UpdateUnlock();

				// �Q�[�W
				UpdateGauge();

				// ����UI
				UpdateCancellation();

				// ����UI
				UpdateKeyUI();

				// �A�C�e����UI
				UpdateItemUI();

				// �X�^�~�i
				UpdateStamina();

				// ��
				UpdateRecovery();

				// �G���_�̃r���[�|�[�g�̘g
				UpdateViewUI();

				// �{�^����UI
				UpdateButtonUI();

				// �ړI�̕\��
				UpdateObjective();

				UpdateEffect();

				UpdateParticle();

				// ��ʓ_��
				UpdateBloodFlash();

				// �X���[
				UpdateSlow();
			}
			UpdateExplain();
#endif
		}
		else if (g_bEdit == true)
		{// g_Edit��true

			// �G�f�B�b�g���̊e�I�u�W�F�N�g�̍X�V����

			// �J����
			UpdateCamera();

			// �G�f�B�b�g
			UpdateEdit();
		}
	}

	if (isGoal == true)
	{// �S�[����true
		g_gameState = GAMESTATE_END;		// �Q�[�����I��������
	}

	if (pPlayer->nLife <= 0)
	{// �v���C���[�����񂾂Ƃ�

		// ���[�h�ݒ�
		g_gameState = GAMESTATE_END;		// �Q�[�����I��������

		// �J�E���g��i�߂�
		g_nCounterGameState++;
	}

	switch (g_gameState)
	{
		case GAMESTATE_NONE:				// �Q�[���ʏ���

			break;
		case GAMESTATE_END:					// �Q�[���I�����

		g_nCounterGameState++;

		if (g_nCounterGameState >= 30)
		{// 30F��������
			g_gameState = GAMESTATE_NONE;	// �������Ă��Ȃ�
			SetFade(MODE_RESULT);			// ���U���g��ʂɑJ��
			g_nCounterGameState = 0;		// ��ԃJ�E���^�[������
		}
		break;
	}
}

//---------------
//	�`�揈��
//---------------
void DrawGame(int nIdx)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	EXPLAIN* pExplain = GetExplain();

	// FOG�̐ݒ�
	SetupVertexFog(D3DCOLOR_XRGB(0, 0, 0), D3DFOG_LINEAR, TRUE, 0.08f);

	//�@�e�I�u�W�F�N�g�̕`�揈��

	// ���b�V���t�B�[���h
	DrawMeshfield();

	// �u���b�N
	DrawBlock();

	// �A�C�e��
	Drawitem();

	switch (nIdx)
	{
	case 0:

		// �G
		DrawEnemy();

		// �A�C�e�����W�p�r���{�[�h
		DrawPickUpUI();

		break;

	case 1:
		// �v���C���[
		DrawPlayer();
		break;

	default:
		break;
	}
	////�@���b�V���t�B�[���h
	//DrawMeshfield();

	////�@�u���b�N
	//DrawBlock();

	////�@�A�C�e��
	//Drawitem();

	//�@�v���C���[
	//DrawPlayer();

	////�@�G
	//DrawEnemy();

	// �M�~�b�N
	DrawGimmick();

	// FOG������
	pDevice->SetRenderState(D3DRS_FOGENABLE, FALSE);

	// �X���[
	DrawSlow();

	// ��ʓ_��
	DrawBloodFlash();

	// ��
	DrawRecovery();

	// �X�^�~�i
	DrawStamina();

	// �r���{�[�h
	DrawBillboard();

	// �����Ԃ�
	DrawBloodSplatter();

	// �^�C��
	DrawTime();

	// �ڂ�UI
	DrawEyeUI();

	DrawUnlock();

	// �Q�[�W
	DrawGauge();

	// ����UI
	DrawCancellation();

	// ����UI
	DrawKeyUI();

	// �A�C�e����UI
	DrawItemUI();

	// �G���_�̃r���[�|�[�g�̘g
	DrawViewUI();

	// �{�^����UI
	DrawButtonUI();

	// �ړI�̕\��
	DrawObjective();

	DrawEffect();
	//DrawEtcUI();

	if (pExplain[0].bLook == true || pExplain[1].bLook == true || pExplain[2].bLook == true)
	{
		DrawExplain();
	}

	// FOG��߂�
	pDevice->SetRenderState(D3DRS_FOGENABLE, FALSE);

	if (g_bPause == true)
	{//�@g_Pause��true

		// �|�[�Y
		DrawPause();
	}
	if (g_bEdit == true)
	{//�@g_bEdit��true

		// �G�f�B�b�g
		DrawEdit();
	}
}

//----------------------
//	�|�[�Y��bool����
//----------------------
void SetEnablePause(bool bPause)
{
	g_bPause = bPause;
}

//------------------
// �Q�[����Ԃ̐ݒ�
//------------------
void SetGameState(GAMESTATE state)
{
	g_gameState = state;
}

//------------------------
// �G�f�B�b�g�̏��̎擾
//------------------------
bool GetEditState(void)
{
	return g_bEdit;
}