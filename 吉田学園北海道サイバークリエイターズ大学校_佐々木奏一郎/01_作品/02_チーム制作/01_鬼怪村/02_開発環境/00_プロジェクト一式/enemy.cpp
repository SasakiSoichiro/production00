//=============================================================================
//
//	�G���� [enemy.cpp]
// Author : ���X�ؑt��Y
//
//=============================================================================
#include "enemy.h"
#include "input.h"
#include "camera.h"
#include "block.h"
#include "score.h"
#include "meshwall.h"
#include "slow.h"
#include "game.h"
#include "fade.h"
#include "sound.h"
#include "player.h"
#include "enemy.h"

Enemy g_Enemy[MAX_ENEMY];
int g_nEIdxShadow;
int nCntTypeState;
int g_nNumEnemy = 0;//�G�̑���
int g_nCntEnemyState = 0;
int g_nIdxEnemyShadow;
int g_nCntPos = 0;
bool bRange;
Enemy g_LoadEnemy[3];

//=============================================================================
//����������
//=============================================================================
void InitEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	for (int nCnt = 0; nCnt < MAX_ENEMY; nCnt++)
	{
		//�e��ϐ��̏�����
		g_Enemy[nCnt].pos = D3DXVECTOR3(0.0f, 50.0f, 0.0f);
		g_Enemy[nCnt].posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Enemy[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Enemy[nCnt].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Enemy[nCnt].nLife = 360;
		g_Enemy[nCnt].nType = 0;
		g_Enemy[nCnt].bBlendMotion = false;
		g_Enemy[nCnt].bUse = false;
		g_Enemy[nCnt].nCount = 0;
	}
	bRange = false;
	nCntTypeState = 0;
	g_nNumEnemy = 0;
	for (int nCntType = 0; nCntType < 1; nCntType++)
	{
		LoadEnemy(nCntType);
		g_LoadEnemy[nCntType].nLife = 30;
		D3DXMATERIAL* pMat;//�}�e���A���ւ̃|�C���^

		for (int nCntModel = 0; nCntModel < g_LoadEnemy[nCntType].nNumModel; nCntModel++)
		{
			//�}�e���A���f�[�^�ւ̃|�C���^���擾
			pMat = (D3DXMATERIAL*)g_LoadEnemy[nCntType].aModel[nCntModel].pBuffMat->GetBufferPointer();


			for (int nCntMat = 0; nCntMat < (int)g_LoadEnemy[nCntType].aModel[nCntModel].dwNumMat; nCntMat++)
			{
				if (pMat[nCntMat].pTextureFilename != NULL)
				{//�e�N�X�`���t�@�C�������݂���
						//�e�N�X�`���̓ǂݍ���
					D3DXCreateTextureFromFile(pDevice,
						pMat[nCntMat].pTextureFilename,
						&g_LoadEnemy[nCntType].aModel[nCntModel].apTexture[nCntMat]);
				}
			}
			g_LoadEnemy[nCntType].aModel[nCntModel].Diffuse = pMat->MatD3D.Diffuse;
			g_LoadEnemy[nCntType].aModel[nCntModel].firstDiffuse = g_LoadEnemy[nCntType].aModel[nCntModel].Diffuse;
		}

		//g_nEIdxShadow = SetShadow(g_Enemy[nCntEnemy].pos, g_Enemy[nCntEnemy].rot);

	}
	g_LoadEnemy[0].fRad = 30.01f;
	SetMotionType(EMOTIONTYPE_MOVE, true, 10, 0);
}

//=============================================================================
// �I������
//=============================================================================
void UninitEnemy(void)
{
	//// �U�������~�߂�
	StopSound(SOUND_LABEL_SE6);

	for (int nCntType = 0; nCntType < 1; nCntType++)
	{
		for (int nCntModel = 0; nCntModel < g_LoadEnemy[nCntType].nNumModel; nCntModel++)
		{
			if (g_LoadEnemy[nCntType].aModel[nCntModel].pMesh != NULL)
			{
				g_LoadEnemy[nCntType].aModel[nCntModel].pMesh->Release();
				g_LoadEnemy[nCntType].aModel[nCntModel].pMesh = NULL;

			}
		}

		for (int nCntModel = 0; nCntModel < g_LoadEnemy[nCntType].nNumModel; nCntModel++)
		{
			//���_�o�b�t�@�̉��
			if (g_LoadEnemy[nCntType].aModel[nCntModel].pBuffMat != NULL)
			{
				g_LoadEnemy[nCntType].aModel[nCntModel].pBuffMat->Release();
				g_LoadEnemy[nCntType].aModel[nCntModel].pBuffMat = NULL;
			}
		}

	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateEnemy(void)
{

	//==========
	// �ϐ��錾
	//==========

	//�����i�[�p
	KEY k_Answer;
	float fRotX = 0.0f;
	float fRotY = 0.0f;
	float fRotZ = 0.0f;


	//�v�Z�p
	float fDiffMotionX;
	float fDiffMotionY;
	float fDiffMotionZ;

	float fRotXCurrent;
	float fRotYCurrent;
	float fRotZCurrent;

	float DiffMotionBlendX;
	float DiffMotionBlendY;
	float DiffMotionBlendZ;

	float fRotXBlend;
	float fRotYBlend;
	float fRotZBlend;

	float fDiffBlendX;
	float fDiffBlendY;
	float fDiffBlendZ;

	// �v���C���[�̔��a�̎Z�o�p�ϐ�
	float fPRadPos = 1000.0f;

	// �G�̔��a�̎Z�o�p�ϐ�
	float fERadPos = 200.0f;

	// �G�̔��a�̎Z�o�p�ϐ�1
	float fERadPos1 = 300.0f;

	// �G�̔��a�̎Z�o�p�ϐ�2
	float fERadPos2 = 350.0f;

	//�J�������擾
	Camera* pCamera = GetCamera();
	//�v���C���[���擾
	Player* pPlayer = GetPlayer();
	//�X���[���擾
	Slow* pSlow = GetSlow();
	//�R���g���[���[�U���̏�����
	static VibrationState vibrationState = { 0,0,0,0,0 };//������

	// �v����[�̈ʒu���擾
	D3DXVECTOR3 PlayerPos = pPlayer->pos;

	// �͈͌v�Z
	float fDisX = PlayerPos.x - g_Enemy[0].pos.x;
	float fDisY = PlayerPos.y - g_Enemy[0].pos.y;
	float fDisZ = PlayerPos.z - g_Enemy[0].pos.z;

	// ��̔��a�����߂�
	float fRadX = fPRadPos + fERadPos;

	// ��̔��a�����߂�
	float fRadX1 = fPRadPos + fERadPos1;

	// ��̔��a�����߂�
	float fRadX2 = fPRadPos + fERadPos2;

	//�G�̌����p�ϐ�
	float fAnglemove = 0.0f;

	//���݂̃v���C���[�ƓG�̋���
	float fDistanceChase = (g_Enemy[0].pos.x - pPlayer->pos.x) * (g_Enemy[0].pos.x - pPlayer->pos.x) + (g_Enemy[0].pos.y - pPlayer->pos.y) * (g_Enemy[0].pos.y - pPlayer->pos.y) + (g_Enemy[0].pos.z - pPlayer->pos.z) * (g_Enemy[0].pos.z - pPlayer->pos.z);

	//�G�̎���
	float fFOV = D3DX_PI / 3.0f;

	//�v���C���[��ǂ������鋗��
	D3DXVECTOR3 fRadChaseP(200.0f, 0.0f, 200.0f);
	D3DXVECTOR3 fRadChaseE(200.0f, 0.0f, 200.0f);

	//�ǂ������锼�a�̐ݒ�
	float fRadiusChase = (fRadChaseP.x + fRadChaseE.x) * (fRadChaseP.x + fRadChaseE.x) + (fRadChaseP.y + fRadChaseE.y) * (fRadChaseP.y + fRadChaseE.y) + (fRadChaseP.z + fRadChaseE.z) * (fRadChaseP.z + fRadChaseE.z);

	//�G�̎��E�x�N�g��1
	g_Enemy[0].posVec[0].x = sinf((g_Enemy[0].rot.y + fFOV / 2.0f)+D3DX_PI) * fRadiusChase - g_Enemy[0].pos.x;
	g_Enemy[0].posVec[0].z = cosf((g_Enemy[0].rot.y + fFOV / 2.0f)+D3DX_PI) * fRadiusChase - g_Enemy[0].pos.y;

	//�G�̎��E�x�N�g��2
	g_Enemy[0].posVec[1].x = sinf((g_Enemy[0].rot.y - fFOV / 2.0f)+D3DX_PI) * fRadiusChase - g_Enemy[0].pos.x;
	g_Enemy[0].posVec[1].z = cosf((g_Enemy[0].rot.y - fFOV / 2.0f)+D3DX_PI) * fRadiusChase - g_Enemy[0].pos.y;

	D3DXVECTOR3 vec;
	float fvecCross[2];
	vec = pPlayer->pos - g_Enemy[0].pos;
	fvecCross[0] = (g_Enemy[0].posVec[0].x * vec.x) + (g_Enemy[0].posVec[0].y * vec.y) + (g_Enemy[0].posVec[0].z * vec.z);

	fvecCross[1] = (g_Enemy[0].posVec[1].x * vec.x) + (g_Enemy[0].posVec[1].y * vec.y) + (g_Enemy[0].posVec[1].z * vec.z);

	nCntTypeState++;

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		g_Enemy[nCntEnemy].nCount++;	// �C���N�������g

		if (g_Enemy[nCntEnemy].nCount > 60)	// 60���傫��������
		{
			PlaySound(SOUND_LABEL_SE7);		// ������炷
			g_Enemy[nCntEnemy].nCount = 0;	// 0�ɖ߂�
		}

		if (g_Enemy[nCntEnemy].bUse == true)
		{			
			switch (g_Enemy[nCntEnemy].State)
			{
			case ENEMYSTATE_NORMAL:
				//�p�j����
				LoiterEnemy();

				if ((fDisX * fDisX) + (fDisY * fDisY) + (fDisZ * fDisZ) <= (fRadX * fRadX))
				{
					SetVolume(SOUND_LABEL_SE7, 3.0f);
				}
				else if ((fDisX * fDisX) + (fDisY * fDisY) + (fDisZ * fDisZ) <= (fRadX1 * fRadX1))
				{
					SetVolume(SOUND_LABEL_SE7, 2.0f);
				}
				else if ((fDisX * fDisX) + (fDisY * fDisY) + (fDisZ * fDisZ) <= (fRadX2 * fRadX2))
				{
					SetVolume(SOUND_LABEL_SE7, 1.0f);
				}
				else
				{
					SetVolume(SOUND_LABEL_SE7, 0.0f);
				}

				if (fDistanceChase <= fRadiusChase && fvecCross[0] > 0 && fvecCross[1] > 0)
				{//�G�l�~�[�̎��E���ɓ�������

					bRange = true;

					//�`�F�C�X���
					g_Enemy[0].State = ENEMYSTATE_CHASE;
					SetMotionType(EMOTIONTYPE_MOVE, true, 10, nCntEnemy);

					// BGM��炷
					PlaySound(SOUND_LABEL_BGM3);

					// ���鉹��炷
					
					//if (g_Enemy[nCntEnemy].nCount < 60)
					//{
						StopSound(SOUND_LABEL_SE5);
					//	//g_Enemy[nCntEnemy].nCount = 0;
					//}

				}
				if (fvecCross[0] > 0 && fvecCross[1] > 0)
				{//�����֌W�Ȃ�
					pPlayer->bEye = true;
				}
				else
				{
					pPlayer->bEye = false;
				}

				break;

			case ENEMYSTATE_CHASE://�`�F�C�X���

				if (fDistanceChase > fRadiusChase)
				{//���E������O�ꂽ��

					bRange = false;

					//�p�j���
					g_Enemy[0].State = ENEMYSTATE_NORMAL;
					SetMotionType(EMOTIONTYPE_NEUTRAL, true, 10, nCntEnemy);
					pPlayer->bEye = false;

					// BGM������
					StopSound(SOUND_LABEL_BGM3);

					//// ���鉹������
					//StopSound();

					// ��������炷


					//PlaySound(SOUND_LABEL_BGM2);
				}

				//�`�F�C�X����
				g_Enemy[0].rotDest.y = atan2f((pPlayer->pos.x - g_Enemy[0].pos.x), (pPlayer->pos.z - g_Enemy[0].pos.z)) + D3DX_PI;
				fAnglemove = atan2f((pPlayer->pos.x - g_Enemy[0].pos.x), (pPlayer->pos.z - g_Enemy[0].pos.z));
				g_Enemy[0].move.x = sinf(fAnglemove) * 1.25f;
				g_Enemy[0].move.z = cosf(fAnglemove) * 1.25f;
				StartVibration(&vibrationState, 20,20000,20000);
				break;

			case ENEMYSTATE_DAMAGE:
				g_nCntEnemyState--;

				//g_Enemy[nCntEnemy].move.x = 0.0f;
				//g_Enemy[nCntEnemy].move.z = 0.0f;
				
				if (g_nCntEnemyState <= 0)
				{
					g_Enemy[nCntEnemy].State = ENEMYSTATE_NORMAL;
					//SetMotionType(EMOTIONTYPE_NEUTRAL, true, 10, nCntEnemy);
				}

				break;
			case ENEMYSTATE_ACTION:
				g_nCntEnemyState--;
				

				//g_Enemy[nCntEnemy].move.x = 0.0f;
				//g_Enemy[nCntEnemy].move.z = 0.0f;
				if (g_nCntEnemyState >= 0)
				{
					if (g_Enemy[nCntEnemy].motionType != EMOTIONTYPE_ACTION)
					{

						SetMotionType(EMOTIONTYPE_ACTION, true, 10, nCntEnemy);
						g_Enemy[nCntEnemy].move.x = 0.0f;
						g_Enemy[nCntEnemy].move.z = 0.0f;
						StartVibration(&vibrationState, 1000, 60000, 60000);

					}
					if (g_nCntEnemyState <= 0)
					{
						g_Enemy[nCntEnemy].State = ENEMYSTATE_NORMAL;
						SetMotionType(EMOTIONTYPE_NEUTRAL, true, 10, nCntEnemy);
						bRange = false;
						pPlayer->bCaught = false;
						// BGM������
						StopSound(SOUND_LABEL_BGM3);
					}
				}
				break;
			}


			g_Enemy[nCntEnemy].OldState = g_Enemy[nCntEnemy].State;

			//���݂̈ʒu��ۑ�
			g_Enemy[nCntEnemy].posOld = g_Enemy[nCntEnemy].pos;

			//�d�͉��Z
			g_Enemy[nCntEnemy].move.y -= GRAVI;

			//�ʒu���X�V
			g_Enemy[nCntEnemy].pos.x += g_Enemy[nCntEnemy].move.x * pSlow->fDivi;
			g_Enemy[nCntEnemy].pos.z += g_Enemy[nCntEnemy].move.z * pSlow->fDivi;

			//SetPositionGaugeLife(g_Enemy[nCntEnemy].nIdxLife, D3DXVECTOR3(g_Enemy[nCntEnemy].pos.x, g_Enemy[nCntEnemy].pos.y + 40.0f, g_Enemy[nCntEnemy].pos.z));


			float fDistance = (g_Enemy[nCntEnemy].pos.x - pPlayer->pos.x) * (g_Enemy[nCntEnemy].pos.x - pPlayer->pos.x) + (g_Enemy[nCntEnemy].pos.y - pPlayer->pos.y) * (g_Enemy[nCntEnemy].pos.y - pPlayer->pos.y) + (g_Enemy[nCntEnemy].pos.z - pPlayer->pos.z) * (g_Enemy[nCntEnemy].pos.z - pPlayer->pos.z);
			D3DXVECTOR3 fRadP(50.0f, 0.0f, 50.0f);
			D3DXVECTOR3 fRadE(50.0f, 0.0f, 50.0f);


			float fRadius = (fRadP.x + fRadE.x) * (fRadP.x + fRadE.x) + (fRadP.y + fRadE.y) * (fRadP.y + fRadE.y) + (fRadP.z + fRadE.z) * (fRadP.z + fRadE.z);

			//�����蔻��
			if ((fDistance <= fRadius) && pPlayer->bAttack == false)
			{
				pPlayer->bCaught = true;
				g_nCntEnemyState = 150;
				g_Enemy[nCntEnemy].State = ENEMYSTATE_ACTION;

				if (g_Enemy[nCntEnemy].motionType == EMOTIONTYPE_ACTION && g_Enemy[nCntEnemy].nKey >= 2)
				{
					if (pPlayer->pState != PLAYERSTATE_DAMAGE)
					{
						HitPlayer(1);
						PlaySound(SOUND_LABEL_SE6);
					}
				}
			}



			if (g_Enemy[nCntEnemy].rotDest.y - g_Enemy[nCntEnemy].rot.y > D3DX_PI)
			{
				g_Enemy[nCntEnemy].rot.y = g_Enemy[nCntEnemy].rot.y + (D3DX_PI * 2);
			}
			else if (g_Enemy[nCntEnemy].rot.y - g_Enemy[nCntEnemy].rotDest.y > D3DX_PI)
			{
				g_Enemy[nCntEnemy].rot.y = g_Enemy[nCntEnemy].rot.y - (D3DX_PI * 2);
			}

			g_Enemy[nCntEnemy].pos += g_Enemy[nCntEnemy].move * pSlow->fDivi;

			if (g_Enemy[nCntEnemy].pos.y < 0.0f)
			{
				g_Enemy[nCntEnemy].pos.y = 0.0f;
			}

			g_Enemy[nCntEnemy].rot.y += (g_Enemy[nCntEnemy].rotDest.y - g_Enemy[nCntEnemy].rot.y) * 0.2f;

			//CollisionWall(&g_Enemy[nCntEnemy].pos, &g_Enemy[nCntEnemy].posOld);

			//�G���m�̓����蔻��
			CollisionEnemytoEnemy(nCntEnemy);

			CollisionBlock(&g_Enemy[nCntEnemy].pos, &g_Enemy[nCntEnemy].posOld);

			//SetPositionShadow(g_Enemy[nCntEnemy].IdxShadow, D3DXVECTOR3(g_Enemy[nCntEnemy].pos.x, 1.0f, g_Enemy[nCntEnemy].pos.z), g_Enemy[nCntEnemy].pos.y);

			//SetPositionShadow(g_nEIdxShadow, D3DXVECTOR3(g_Enemy[nCntEnemy].pos.x, 0.1f, g_Enemy[nCntEnemy].pos.z));
		}

		g_Enemy[nCntEnemy].nNumKey = g_Enemy[nCntEnemy].aMotionInfo[g_Enemy[nCntEnemy].motionType].nNumKey;
		g_Enemy[nCntEnemy].nNumKeyBlend = g_Enemy[nCntEnemy].aMotionInfo[g_Enemy[nCntEnemy].motionTypeBlend].nNumKey;


		//�S���f��(�p�[�c)�̍X�V
		for (int nCntModel = 0; nCntModel < g_Enemy[nCntEnemy].nNumModel; nCntModel++)
		{
			//���݂̃L�[�����(�|�C���g
			EKEY pKey = g_Enemy[nCntEnemy].aMotionInfo[g_Enemy[nCntEnemy].motionType].aKeyInfo[g_Enemy[nCntEnemy].nKey].aKey[nCntModel];
			//���̃L�[�����(�|�C���g
			EKEY pKeyNext = g_Enemy[nCntEnemy].aMotionInfo[g_Enemy[nCntEnemy].motionType].aKeyInfo[(g_Enemy[nCntEnemy].nKey + 1) % g_Enemy[nCntEnemy].nNumKey].aKey[nCntModel];

			//���Βl
			float fRateMotion = g_Enemy[nCntEnemy].nCntMotion /( (float)g_Enemy[nCntEnemy].aMotionInfo[g_Enemy[nCntEnemy].motionType].aKeyInfo[g_Enemy[nCntEnemy].nKey].nFlame * pSlow->nMulti);

			//�u�����h����t���[��
			g_Enemy[nCntEnemy].nFrameBlend = EBLEND_FRAME * pSlow->nMulti;


			//�u�����h���[�V��������
			if (g_Enemy[nCntEnemy].bBlendMotion == true)
			{//bBlend��true��������


				//==========
				// �ϐ��錾
				//==========

				// �u�����h��̏�����
				// ���݂̃L�[�����(�|�C���g
				EKEY pKeyBlend = g_Enemy[nCntEnemy].aMotionInfo[g_Enemy[nCntEnemy].motionTypeBlend].aKeyInfo[g_Enemy[nCntEnemy].nKeyBlend].aKey[nCntModel];												// ���݂̃L�[

				// ���̃L�[�����(�|�C���g
				EKEY pKeyNextBlend = g_Enemy[nCntEnemy].aMotionInfo[g_Enemy[nCntEnemy].motionTypeBlend].aKeyInfo[(g_Enemy[nCntEnemy].nKeyBlend + 1) % g_Enemy[nCntEnemy].nNumKeyBlend].aKey[nCntModel];	// ���̃L�[

				// ���Βl
				float fRateMotionBlend = g_Enemy[nCntEnemy].nCntMotionBlend / ((float)g_Enemy[nCntEnemy].aMotionInfo[g_Enemy[nCntEnemy].motionTypeBlend].aKeyInfo[g_Enemy[nCntEnemy].nKeyBlend].nFlame * pSlow->nMulti);

				// �u�����h�̑��Βl
				float fRateBlend = g_Enemy[nCntEnemy].nCntBlend / ((float)g_Enemy[nCntEnemy].nFrameBlend*pSlow->nMulti);



				// X���̉�]
				//=============================================================================================
				fDiffMotionX = pKeyNext.fRotX - pKey.fRotX;							// ���̃L�[�Ƃ̍���
				fRotXCurrent = pKey.fRotX + (fDiffMotionX * fRateMotion);
				DiffMotionBlendX = pKeyNextBlend.fRotX - pKeyBlend.fRotX;
				fRotXBlend = pKeyBlend.fRotX + (DiffMotionBlendX * fRateMotionBlend);
				fDiffBlendX = fRotXBlend - fRotXCurrent;								// ����
				fRotX = fRotXCurrent + (fDiffBlendX * fRateBlend);						// ���߂�l
				//=============================================================================================


				// Y���̉�]
				//=============================================================================================
				fDiffMotionY = pKeyNext.fRotY - pKey.fRotY;							// ���̃L�[�Ƃ̍���
				fRotYCurrent = pKey.fRotY + (fDiffMotionY * fRateMotion);
				DiffMotionBlendY = pKeyNextBlend.fRotY - pKeyBlend.fRotY;
				fRotYBlend = pKeyBlend.fRotY + (DiffMotionBlendY * fRateMotionBlend);
				fDiffBlendY = fRotYBlend - fRotYCurrent;								// ����
				fRotY = fRotYCurrent + (fDiffBlendY * fRateBlend);						// ���߂�l
				//=============================================================================================


				// Z���̉�]
				//=============================================================================================
				fDiffMotionZ = pKeyNext.fRotZ - pKey.fRotZ;							// ���̃L�[�Ƃ̍���
				fRotZCurrent = pKey.fRotZ + (fDiffMotionZ * fRateMotion);
				DiffMotionBlendZ = pKeyNextBlend.fRotZ - pKeyBlend.fRotZ;
				fRotZBlend = pKeyBlend.fRotZ + (DiffMotionBlendZ * fRateMotionBlend);
				fDiffBlendZ = fRotZBlend - fRotZCurrent;								// ����
				fRotZ = fRotZCurrent + (fDiffBlendZ * fRateBlend);						// ���߂�l
				//=============================================================================================

			}
			else
			{//�u�����h����

				//�L�[��񂩂�ʒu.�������Z�o
				//���̃L�[�Ƃ̍���
				k_Answer.fPosX = (g_Enemy[nCntEnemy].aMotionInfo[g_Enemy[nCntEnemy].motionType].aKeyInfo[(g_Enemy[nCntEnemy].nKey + 1) % g_Enemy[nCntEnemy].nNumKey].aKey[nCntModel].fPosX) - (g_Enemy[nCntEnemy].aMotionInfo[g_Enemy[nCntEnemy].motionType].aKeyInfo[g_Enemy[nCntEnemy].nKey].aKey[nCntModel].fPosX);
				k_Answer.fPosY = (g_Enemy[nCntEnemy].aMotionInfo[g_Enemy[nCntEnemy].motionType].aKeyInfo[(g_Enemy[nCntEnemy].nKey + 1) % g_Enemy[nCntEnemy].nNumKey].aKey[nCntModel].fPosY) - (g_Enemy[nCntEnemy].aMotionInfo[g_Enemy[nCntEnemy].motionType].aKeyInfo[g_Enemy[nCntEnemy].nKey].aKey[nCntModel].fPosY);
				k_Answer.fPosZ = (g_Enemy[nCntEnemy].aMotionInfo[g_Enemy[nCntEnemy].motionType].aKeyInfo[(g_Enemy[nCntEnemy].nKey + 1) % g_Enemy[nCntEnemy].nNumKey].aKey[nCntModel].fPosZ) - (g_Enemy[nCntEnemy].aMotionInfo[g_Enemy[nCntEnemy].motionType].aKeyInfo[g_Enemy[nCntEnemy].nKey].aKey[nCntModel].fPosZ);
				fDiffMotionX = (pKeyNext.fRotX) - (pKey.fRotX);
				fDiffMotionY = (pKeyNext.fRotY) - (pKey.fRotY);
				fDiffMotionZ = (pKeyNext.fRotZ) - (pKey.fRotZ);

				//���߂�l
				fRotX = pKey.fRotX + fDiffMotionX * fRateMotion;
				fRotY = pKey.fRotY + fDiffMotionY * fRateMotion;
				fRotZ = pKey.fRotZ + fDiffMotionZ * fRateMotion;

			}


			//�p�[�c�̈ʒu.������ݒ�
			//�ʒu
			//g_Enemy[nCntEnemy].aModel[nCntModel].pos.x = g_Enemy[nCntEnemy].aModel[nCntModel].posFirst.x + g_Enemy[nCntEnemy].aMotionInfo[g_Enemy[nCntEnemy].motionType].aKeyInfo[g_Enemy[nCntEnemy].nKey].aKey[nCntModel].fPosX + k_Answer.fPosX * (g_Enemy[nCntEnemy].nCntMotion / ((float)g_Enemy[nCntEnemy].aMotionInfo[g_Enemy[nCntEnemy].motionType].aKeyInfo[g_Enemy[nCntEnemy].nKey].nFlame /** pSlow->nMulti*/));//�I�t�Z�b�g�l��
			//g_Enemy[nCntEnemy].aModel[nCntModel].pos.y = g_Enemy[nCntEnemy].aModel[nCntModel].posFirst.y + g_Enemy[nCntEnemy].aMotionInfo[g_Enemy[nCntEnemy].motionType].aKeyInfo[g_Enemy[nCntEnemy].nKey].aKey[nCntModel].fPosY + k_Answer.fPosY * (g_Enemy[nCntEnemy].nCntMotion / ((float)g_Enemy[nCntEnemy].aMotionInfo[g_Enemy[nCntEnemy].motionType].aKeyInfo[g_Enemy[nCntEnemy].nKey].nFlame /** pSlow->nMulti*/));
			//g_Enemy[nCntEnemy].aModel[nCntModel].pos.z = g_Enemy[nCntEnemy].aModel[nCntModel].posFirst.z + g_Enemy[nCntEnemy].aMotionInfo[g_Enemy[nCntEnemy].motionType].aKeyInfo[g_Enemy[nCntEnemy].nKey].aKey[nCntModel].fPosZ + k_Answer.fPosZ * (g_Enemy[nCntEnemy].nCntMotion / ((float)g_Enemy[nCntEnemy].aMotionInfo[g_Enemy[nCntEnemy].motionType].aKeyInfo[g_Enemy[nCntEnemy].nKey].nFlame /** pSlow->nMulti*/));

			//����
			g_Enemy[nCntEnemy].aModel[nCntModel].rot.x = g_Enemy[nCntEnemy].aModel[nCntModel].rotFirst.x + fRotX;//�I�t�Z�b�g�l��
			g_Enemy[nCntEnemy].aModel[nCntModel].rot.y = g_Enemy[nCntEnemy].aModel[nCntModel].rotFirst.y + fRotY;//�I�t�Z�b�g�l��
			g_Enemy[nCntEnemy].aModel[nCntModel].rot.z = g_Enemy[nCntEnemy].aModel[nCntModel].rotFirst.z + fRotZ;//�I�t�Z�b�g�l��


		}


		if (g_Enemy[nCntEnemy].bBlendMotion == true)
		{//�u�����h����
			if (g_Enemy[nCntEnemy].aMotionInfo[g_Enemy[nCntEnemy].motionTypeBlend].bLoop == false)
			{//���[�v���[�V��������Ȃ��ꍇ

				if (g_Enemy[nCntEnemy].nKeyBlend + 1 != g_Enemy[nCntEnemy].nNumKeyBlend)
				{//�L�[�����ɒB���Ă��Ȃ��ꍇ

					g_Enemy[nCntEnemy].nCntMotionBlend += 1;//�Đ��t���[�����ɒB�����猻�݂̃L�[��1�i�߂�

				}
			}

			else
			{//���[�v���[�V�����̏ꍇ

				g_Enemy[nCntEnemy].nCntMotionBlend += 1;//�J�E���g���[�V������1�i�߂�

			}

			if (g_Enemy[nCntEnemy].nCntMotionBlend >= (g_Enemy[nCntEnemy].aMotionInfo[g_Enemy[nCntEnemy].motionTypeBlend].aKeyInfo[g_Enemy[nCntEnemy].nKeyBlend].nFlame * pSlow->nMulti))
			{//�t���[�����𒴂�����

				//�J�E���g���[�V������0�ɂ���
				g_Enemy[nCntEnemy].nCntMotionBlend = 0;

				//���݂̃L�[��1�i�߂�
				g_Enemy[nCntEnemy].nKeyBlend += 1;

				if (g_Enemy[nCntEnemy].nKeyBlend >= g_Enemy[nCntEnemy].nNumKeyBlend)
				{//�L�[�����ɒB������

					//���݂̃L�[��0�ɂ���
					g_Enemy[nCntEnemy].nKeyBlend = 0;
				}
			}

			//�u�����h�J�E���g��1�i�߂�
			g_Enemy[nCntEnemy].nCntBlend++;


			if (g_Enemy[nCntEnemy].nCntBlend >= (g_Enemy[nCntEnemy].nFrameBlend*pSlow->nMulti))
			{//�u�����h�̃t���[�����ɒB������

				//���������ʏ탂�[�V�����ɏ�����
				g_Enemy[nCntEnemy].nCntMotion = g_Enemy[nCntEnemy].nCntMotionBlend;
				g_Enemy[nCntEnemy].nCntBlend = 0;
				g_Enemy[nCntEnemy].motionType = g_Enemy[nCntEnemy].motionTypeBlend;
				g_Enemy[nCntEnemy].nKey = g_Enemy[nCntEnemy].nKeyBlend;
				g_Enemy[nCntEnemy].bBlendMotion = false;

			}

			if (g_Enemy[nCntEnemy].aMotionInfo[g_Enemy[nCntEnemy].motionType].nNumKey - 1 <= g_Enemy[nCntEnemy].nKey && g_Enemy[nCntEnemy].aMotionInfo[g_Enemy[nCntEnemy].motionType].bLoop == false)
			{
				g_Enemy[nCntEnemy].motionType = EMOTIONTYPE_NEUTRAL;
			}
		}


		else
		{//�u�����h�Ȃ�

			if (g_Enemy[nCntEnemy].aMotionInfo[g_Enemy[nCntEnemy].motionType].bLoop == false)
			{//���[�v���[�V��������Ȃ��ꍇ

				if (g_Enemy[nCntEnemy].nKey + 1 != g_Enemy[nCntEnemy].nNumKey)
				{//�L�[�����ɒB���Ă��Ȃ��ꍇ

					g_Enemy[nCntEnemy].nCntMotion++;//���[�V�����J�E���g��1�i�߂�

				}
			}


			else
			{//���[�v���[�V�����̏ꍇ

				g_Enemy[nCntEnemy].nCntMotion++;//���[�V�����J�E���g��1�i�߂�

			}



			if (g_Enemy[nCntEnemy].nCntMotion >= (g_Enemy[nCntEnemy].aMotionInfo[g_Enemy[nCntEnemy].motionType].aKeyInfo[g_Enemy[nCntEnemy].nKey].nFlame * pSlow->nMulti))
			{//�t���[�����𒴂�����

				//�J�E���g���[�V������0�ɂ���
				g_Enemy[nCntEnemy].nCntMotion = 0;

				//���݂̃L�[��1�i�߂�
				g_Enemy[nCntEnemy].nKey += 1;

				if (g_Enemy[nCntEnemy].nKey >= g_Enemy[nCntEnemy].nNumKey)
				{//�L�[�����ɒB������

					//���݂̃L�[��0�ɂ���
					g_Enemy[nCntEnemy].nKey = 0;

				}
			}
		}
	}
	UpdateVibration(&vibrationState);
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();
	Camera* pCamera = GetCamera();

	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;
	//���݂̃}�e���A���̕ۑ��p
	D3DMATERIAL9 matDef;//���݂̃}�e���A���̕ۑ��p
	D3DXMATERIAL* pMat;//�}�e���A���f�[�^�ւ̃|�C���^


	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_Enemy[nCntEnemy].bUse == true)
		{
			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_Enemy[nCntEnemy].mtxWorld);
			//�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Enemy[nCntEnemy].rot.y, g_Enemy[nCntEnemy].rot.x, g_Enemy[nCntEnemy].rot.z);
			D3DXMatrixMultiply(&g_Enemy[nCntEnemy].mtxWorld, &g_Enemy[nCntEnemy].mtxWorld, &mtxRot);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_Enemy[nCntEnemy].pos.x, g_Enemy[nCntEnemy].pos.y, g_Enemy[nCntEnemy].pos.z);
			D3DXMatrixMultiply(&g_Enemy[nCntEnemy].mtxWorld, &g_Enemy[nCntEnemy].mtxWorld, &mtxTrans);

			pDevice->SetTransform(D3DTS_WORLD, &g_Enemy[nCntEnemy].mtxWorld);

			pDevice->GetMaterial(&matDef);

			//�S���f���i�p�[�c�j�̕`��
			for (int nCntModel = 0; nCntModel < g_Enemy[nCntEnemy].nNumModel; nCntModel++)
			{
				//�v�Z�p�}�g���b�N�X
				D3DXMATRIX mtxRotModel, mtxTransModel;
				D3DXMATRIX mtxParent;//�e�̃}�g���b�N�X

				//�p�[�c�̃��[���h�}�g���b�N�X�̏�����
				D3DXMatrixIdentity(&g_Enemy[nCntEnemy].aModel[nCntModel].mtxWorld);

				//�����𔽉f
				D3DXMatrixRotationYawPitchRoll(&mtxRotModel, g_Enemy[nCntEnemy].aModel[nCntModel].rot.y, g_Enemy[nCntEnemy].aModel[nCntModel].rot.x, g_Enemy[nCntEnemy].aModel[nCntModel].rot.z);
				D3DXMatrixMultiply(&g_Enemy[nCntEnemy].aModel[nCntModel].mtxWorld, &g_Enemy[nCntEnemy].aModel[nCntModel].mtxWorld, &mtxRotModel);

				//�ʒu�𔽉f
				D3DXMatrixTranslation(&mtxTransModel, g_Enemy[nCntEnemy].aModel[nCntModel].pos.x, g_Enemy[nCntEnemy].aModel[nCntModel].pos.y, g_Enemy[nCntEnemy].aModel[nCntModel].pos.z);
				D3DXMatrixMultiply(&g_Enemy[nCntEnemy].aModel[nCntModel].mtxWorld, &g_Enemy[nCntEnemy].aModel[nCntModel].mtxWorld, &mtxTransModel);

				//�p�[�c�́u�e�̃}�g���b�N�X�v��ݒ�
				if (g_Enemy[nCntEnemy].aModel[nCntModel].nIdxModelParent != -1)
				{//�e���f��������ꍇ
					mtxParent = g_Enemy[nCntEnemy].aModel[g_Enemy[nCntEnemy].aModel[nCntModel].nIdxModelParent].mtxWorld;
				}
				else
				{
					mtxParent = g_Enemy[nCntEnemy].mtxWorld;
				}

				//�Z�o�����u�p�[�c�̃��[���h�}�g���b�N�X�v�Ɓu�e�̃}�g���b�N�X�v���|�����킹��
				D3DXMatrixMultiply(&g_Enemy[nCntEnemy].aModel[nCntModel].mtxWorld,
					&g_Enemy[nCntEnemy].aModel[nCntModel].mtxWorld,
					&mtxParent);
				//�p�[�c�̃��[���h�}�g���b�N�X�̐ݒ�
				pDevice->SetTransform(D3DTS_WORLD,
					&g_Enemy[nCntEnemy].aModel[nCntModel].mtxWorld);


				//�}�e���A���f�[�^�ւ̃|�C���^���擾
				pMat = (D3DXMATERIAL*)g_Enemy[nCntEnemy].aModel[nCntModel].pBuffMat->GetBufferPointer();

				for (int nCntMat = 0; nCntMat < (int)g_Enemy[nCntEnemy].aModel[nCntModel].dwNumMat; nCntMat++)
				{

					//�}�e���A���̐ݒ�
					pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

					//�e�N�X�`���̐ݒ�
					pDevice->SetTexture(0, g_Enemy[nCntEnemy].aModel[nCntModel].apTexture[nCntMat]);

					//���f���i�p�[�c�j�̕`��
					g_Enemy[nCntEnemy].aModel[nCntModel].pMesh->DrawSubset(nCntMat);

				}
			}
			pDevice->SetMaterial(&matDef);
		}

	}

}

//=============================================================================
// �ݒ菈��
//=============================================================================
void SetEnemy(D3DXVECTOR3 pos, int nType)
{
	for (int nCnt = 0; nCnt < MAX_ENEMY; nCnt++)
	{
		if (g_Enemy[nCnt].bUse == false)
		{
			g_Enemy[nCnt] = g_LoadEnemy[nType];
			g_Enemy[nCnt].pos = pos;
			//g_Enemy[nCnt].nIdxLife = SetGaugeLife(g_Enemy[nCnt].pos, g_Enemy[nCnt].rot, g_Enemy[nCnt].nLife);
			//g_Enemy[nCnt].IdxShadow = SetShadow(pos, g_Enemy[nCnt].rot, D3DXVECTOR3(10.0f, 1.0f, 10.0f));
			g_Enemy[nCnt].bUse = true;
			g_nNumEnemy++;//�G�̑���
			break;
		}
	}
}

//=============================================================================
// �G�̓Ǎ�����
//=============================================================================
void LoadEnemy(int nType)
{

	FILE* pFile;
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();
	int nCntModel = 0, nCntParts = 0, nIdx = 0, nParents = 0, nCntKey = 0, nCntMotion = 0;
	int nBool;
	char str[MAX_WORD];

	pFile = fopen("data\\MOTION\\EnemyMotion1.txt", "r");

	if (pFile != NULL)
	{
		char aString[MAX_WORD];//���������i�[

		while (1)
		{
			//�t�@�C����ǂݍ���
			fscanf(pFile, "%s", &aString[0]);


			if (strcmp(aString, "SCRIPT") == 0)
			{
				while (1)
				{
					//�t�@�C����ǂݍ���
					fscanf(pFile, "%s", &aString[0]);

					if (strcmp(aString, "NUM_MODEL") == 0)
					{
						fscanf(pFile, "%s", &str[0]);
						fscanf(pFile, "%d", &g_LoadEnemy[nType].nNumModel);
						while (nCntModel < g_LoadEnemy[nType].nNumModel)
						{
							//�t�@�C����ǂݍ���
							fscanf(pFile, "%s", &aString[0]);

							if (strcmp(aString, "MODEL_FILENAME") == 0)
							{
								fscanf(pFile, "%s", &str[0]);
								fscanf(pFile, "%s", &aString[0]);

								const char* MODEL_FILE = {};
								MODEL_FILE = aString;

								//x�t�@�C���̓ǂݍ���
								D3DXLoadMeshFromX(MODEL_FILE,
									D3DXMESH_SYSTEMMEM,
									pDevice,
									NULL,
									&g_LoadEnemy[nType].aModel[nCntModel].pBuffMat,
									NULL,
									&g_LoadEnemy[nType].aModel[nCntModel].dwNumMat,
									&g_LoadEnemy[nType].aModel[nCntModel].pMesh);

								if (nCntModel < g_LoadEnemy[nType].nNumModel)
								{
									nCntModel++;
								}
							}
						}
					}

					if (strcmp(aString, "CHARACTERSET") == 0)
					{
						while (1)
						{
							//�t�@�C����ǂݍ���
							fscanf(pFile, "%s", &aString[0]);

							if (strcmp(aString, "NUM_PARTS") == 0)
							{
								fscanf(pFile, "%s", &str[0]);
								fscanf(pFile, "%d", &g_LoadEnemy[nType].nNumModel);

							}
							while (nCntParts < g_LoadEnemy[nType].nNumModel)
							{
								//�t�@�C����ǂݍ���
								fscanf(pFile, "%s", &aString[0]);

								if (strcmp(aString, "PARTSSET") == 0)
								{
									while (1)
									{
										//�t�@�C����ǂݍ���
										fscanf(pFile, "%s", &aString[0]);

										if (strcmp(aString, "INDEX") == 0)
										{
											fscanf(pFile, "%s", &str[0]);
											fscanf(pFile, "%d", &nIdx);
										}
										else if (strcmp(aString, "PARENT") == 0)
										{
											fscanf(pFile, "%s", &str[0]);
											fscanf(pFile, "%d", &g_LoadEnemy[nType].aModel[nIdx].nIdxModelParent);

										}
										else if (strcmp(aString, "POS") == 0)
										{
											fscanf(pFile, "%s", &str[0]);
											fscanf(pFile, "%f", &g_LoadEnemy[nType].aModel[nIdx].pos.x);
											fscanf(pFile, "%f", &g_LoadEnemy[nType].aModel[nIdx].pos.y);
											fscanf(pFile, "%f", &g_LoadEnemy[nType].aModel[nIdx].pos.z);
										}
										else if (strcmp(aString, "ROT") == 0)
										{
											fscanf(pFile, "%s", &str[0]);
											fscanf(pFile, "%f", &g_LoadEnemy[nType].aModel[nIdx].rot.x);
											fscanf(pFile, "%f", &g_LoadEnemy[nType].aModel[nIdx].rot.y);
											fscanf(pFile, "%f", &g_LoadEnemy[nType].aModel[nIdx].rot.z);

										}
										else if (strcmp(aString, "END_PARTSSET") == 0)
										{
											nCntParts++;
											break;
										}
									}

								}

							}
							if (strcmp(aString, "END_CHARACTERSET") == 0)
							{
								break;
							}

						}
					}
					if (strcmp(aString, "MOTIONSET") == 0)
					{
						while (1)
						{
							//�t�@�C����ǂݍ���
							fscanf(pFile, "%s", &aString[0]);

							if (strcmp(aString, "LOOP") == 0)
							{
								fscanf(pFile, "%s", &str[0]);
								fscanf(pFile, "%d", &nBool);
								if (nBool == 0)
								{
									g_LoadEnemy[nType].aMotionInfo[nCntMotion].bLoop = false;
								}
								else
								{
									g_LoadEnemy[nType].aMotionInfo[nCntMotion].bLoop = true;
								}
							}

							if (strcmp(aString, "NUM_KEY") == 0)
							{
								fscanf(pFile, "%s", &str[0]);
								fscanf(pFile, "%d", &g_LoadEnemy[nType].aMotionInfo[nCntMotion].nNumKey);

								while (nCntKey < g_LoadEnemy[nType].aMotionInfo[nCntMotion].nNumKey)
								{
									//�t�@�C����ǂݍ���
									fscanf(pFile, "%s", &aString[0]);

									if (strcmp(aString, "KEYSET") == 0)
									{
										nCntParts = 0;
										while (1)
										{
											//�t�@�C����ǂݍ���
											fscanf(pFile, "%s", &aString[0]);

											if (strcmp(aString, "FRAME") == 0)
											{
												fscanf(pFile, "%s", &str[0]);
												fscanf(pFile, "%d", &g_LoadEnemy[nType].aMotionInfo[nCntMotion].aKeyInfo[nCntKey].nFlame);
												break;
											}
										}

										while (1)
										{
											//�t�@�C����ǂݍ���
											fscanf(pFile, "%s", &aString[0]);

											if (strcmp(aString, "KEY") == 0)
											{
												while (1)
												{
													//�t�@�C����ǂݍ���
													fscanf(pFile, "%s", &aString[0]);

													if (strcmp(aString, "POS") == 0)
													{
														fscanf(pFile, "%s", &str[0]);
														fscanf(pFile, "%f", &g_LoadEnemy[nType].aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntParts].fPosX);
														fscanf(pFile, "%f", &g_LoadEnemy[nType].aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntParts].fPosY);
														fscanf(pFile, "%f", &g_LoadEnemy[nType].aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntParts].fPosZ);
													}
													if (strcmp(aString, "ROT") == 0)
													{
														fscanf(pFile, "%s", &str[0]);
														fscanf(pFile, "%f", &g_LoadEnemy[nType].aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntParts].fRotX);
														fscanf(pFile, "%f", &g_LoadEnemy[nType].aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntParts].fRotY);
														fscanf(pFile, "%f", &g_LoadEnemy[nType].aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntParts].fRotZ);
													}
													if (strcmp(aString, "END_KEY") == 0)
													{
														nCntParts++;
														break;
													}
												}
											}
											if (strcmp(aString, "END_KEYSET") == 0)
											{
												nCntKey++;
												break;
											}

										}
									}


								}

							}

							if (strcmp(aString, "END_MOTIONSET") == 0)
							{
								nCntMotion++;
								nCntKey = 0;
								break;
							}
						}
					}
					if (strcmp(aString, "END_SCRIPT") == 0)
					{
						break;
					}
				}
				break;

			}
		}
	}
	for (int nCnt = 0; nCnt < g_LoadEnemy[nType].nNumModel; nCnt++)
	{
		g_LoadEnemy[nType].aModel[nCnt].posFirst = g_LoadEnemy[nType].aModel[nCnt].pos;
		g_LoadEnemy[nType].aModel[nCnt].rotFirst = g_LoadEnemy[nType].aModel[nCnt].rot;
	}

}

//=============================================================================
// �G�̓����蔻��
//=============================================================================
void CollisionEnemy(void)
{
	Player* pPlayer = GetPlayer();
	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_Enemy[nCntEnemy].bUse == true)
		{
			float mtxX = (pPlayer->SwordmtxWorld._41 - pPlayer->motion.aModel[15].mtxWorld._41);
			float mtxY = (pPlayer->SwordmtxWorld._42 - pPlayer->motion.aModel[15].mtxWorld._42);
			float mtxZ = (pPlayer->SwordmtxWorld._43 - pPlayer->motion.aModel[15].mtxWorld._43);
			for (int nCnt = 0; nCnt < 4; nCnt++)
			{
				D3DXVECTOR3 pos;
				pos.x = pPlayer->motion.aModel[15].mtxWorld._41 + mtxX * 0.25f * nCnt;
				pos.y = pPlayer->motion.aModel[15].mtxWorld._42 + mtxY * 0.25f * nCnt;
				pos.z = pPlayer->motion.aModel[15].mtxWorld._43 + mtxZ * 0.25f * nCnt;

				float DistanceX = g_Enemy[nCntEnemy].pos.x - pos.x;
				float DistanceY = g_Enemy[nCntEnemy].pos.y - pos.y;
				float DistanceZ = g_Enemy[nCntEnemy].pos.z - pos.z;

				float fDistance = (DistanceX * DistanceX) + (DistanceY * DistanceY) + (DistanceZ * DistanceZ);

				float fPlayerRad = 20.0f;

				float fRad = g_Enemy[nCntEnemy].fRad + fPlayerRad;
				fRad = fRad * fRad;

				if (fDistance <= fRad && g_Enemy[nCntEnemy].State != ENEMYSTATE_DAMAGE)
				{

				}
			}
		}
	}
}

//=============================================================================
// �G�̃q�b�g����
//=============================================================================
void HitEnemy(int nCnt, int nDamage)
{
	g_Enemy[nCnt].nLife -= nDamage;

	if (g_Enemy[nCnt].nLife <= 0 && g_Enemy[nCnt].bUse == true)
	{
		//�����̐ݒ�
		g_Enemy[nCnt].bUse = false;
		//EraseGaugeLife(g_Enemy[nCnt].nIdxLife);
		//EraseShadow(g_Enemy[nCnt].IdxShadow);
		AddScore(150);
		g_nNumEnemy--;//�G�̑����J�E���g�_�E��
	}
	else
	{
		g_Enemy[nCnt].State = ENEMYSTATE_DAMAGE;
		g_Enemy[nCnt].move.x = sinf(D3DX_PI) * 80.0f;
		g_Enemy[nCnt].move.z = cosf(D3DX_PI) * 80.0f;
		g_nCntEnemyState = 240;
	}

}

//=============================================================================
//�G���m�̓����蔻��
//=============================================================================
void CollisionEnemytoEnemy(int nCnt)
{


	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{

		if (g_Enemy[nCntEnemy].bUse == true && nCnt != nCntEnemy)
		{
			D3DXVECTOR3 pos;


			float fDistance = (g_Enemy[nCntEnemy].pos.x - g_Enemy[nCnt].pos.x) * (g_Enemy[nCntEnemy].pos.x - g_Enemy[nCnt].pos.x) + (g_Enemy[nCntEnemy].pos.y - g_Enemy[nCnt].pos.y) * (g_Enemy[nCntEnemy].pos.y - g_Enemy[nCnt].pos.y) + (g_Enemy[nCntEnemy].pos.z - g_Enemy[nCnt].pos.z) * (g_Enemy[nCntEnemy].pos.z - g_Enemy[nCnt].pos.z);
			D3DXVECTOR3 fRadP(1.0f, 0.0f, 1.0f);
			D3DXVECTOR3 fRadE(1.0f, 0.0f, 1.0f);


			float fRadius = (fRadP.x + fRadE.x) * (fRadP.x + fRadE.x) + (fRadP.y + fRadE.y) * (fRadP.y + fRadE.y) + (fRadP.z + fRadE.z) * (fRadP.z + fRadE.z);

			fRadius = fRadius * fRadius;

			if (fDistance <= fRadius)
			{
				g_Enemy[nCnt].pos = g_Enemy[nCnt].posOld;
			}
		}
	}

}

//=============================================================================
// �p�j����
//=============================================================================
void LoiterEnemy(void)
{


	D3DXVECTOR3 Turn[POINT_MAX];

	float fAnglemove = 0.0f;

	Turn[0] = D3DXVECTOR3(800.0f, 0.0f, 250.0f);
	Turn[1] = D3DXVECTOR3(700.0f, 0.0f, -500.0f);
	Turn[2] = D3DXVECTOR3(20.0f, 0.0f, -150.0f);
	Turn[3] = D3DXVECTOR3(-800.0f, 0.0f, -400.0f);
	Turn[4] = D3DXVECTOR3(-850.0f, 0.0f, 950.0f);
	Turn[5] = D3DXVECTOR3(20.0f, 0.0f, -150.0f);
	Turn[6] = D3DXVECTOR3(500.0f, 0.0f, 600.0f);
	Turn[7] = D3DXVECTOR3(500.0f, 0.0f, 400.0f);
	Turn[8] = D3DXVECTOR3(300.0f, 0.0f, 300.0f);
	Turn[9] = D3DXVECTOR3(300.0f, 0.0f, -300.0f);

	float fDistance = (g_Enemy[0].pos.x - Turn[g_nCntPos].x) * (g_Enemy[0].pos.x - Turn[g_nCntPos].x) + (g_Enemy[0].pos.y - Turn[g_nCntPos].y) * (g_Enemy[0].pos.y - Turn[g_nCntPos].y) + (g_Enemy[0].pos.z - Turn[g_nCntPos].z) * (g_Enemy[0].pos.z - Turn[g_nCntPos].z);
	D3DXVECTOR3 fRadP(100.0f, 0.0f, 100.0f);
	D3DXVECTOR3 fRadE(100.0f, 0.0f, 100.0f);


	float fRadius = (fRadP.x + fRadE.x) * (fRadP.x + fRadE.x) + (fRadP.y + fRadE.y) * (fRadP.y + fRadE.y) + (fRadP.z + fRadE.z) * (fRadP.z + fRadE.z);


	if (fDistance <= fRadius)
	{//�^�[���n�_�܂ŗ�����

		//���̃^�[���n�_��ݒ�
		g_nCntPos += 1;
		g_nCntPos = g_nCntPos % POINT_MAX;

	}

	g_Enemy[0].rotDest.y = atan2f((Turn[g_nCntPos].x - g_Enemy[0].pos.x), (Turn[g_nCntPos].z - g_Enemy[0].pos.z))+D3DX_PI;
	fAnglemove = atan2f((Turn[g_nCntPos].x - g_Enemy[0].pos.x), (Turn[g_nCntPos].z - g_Enemy[0].pos.z));
	g_Enemy[0].move.x = sinf(fAnglemove) * 0.7f;
	g_Enemy[0].move.z = cosf(fAnglemove) * 0.7f;

}

//=============================================================================
// �G�̎擾����
//=============================================================================
Enemy* GetEnemy(void)
{
	return &g_Enemy[0];
}

//=============================================================================
// 
//=============================================================================
int GetNumEnemy()
{
	return g_nNumEnemy;
}

//=============================================================================
//���[�V�����̐ݒ�
//=============================================================================
void SetMotionType(EMOTIONTYPE MotionType, bool bBlendMotion, int nFrameBlend,int nCnt)
{
	g_Enemy[0].motionTypeBlend = MotionType;
	g_Enemy[0].bBlendMotion = bBlendMotion;
	g_Enemy[0].nFrameBlend = nFrameBlend;
	g_Enemy[0].nKeyBlend = 0;
	g_Enemy[0].nCntMotionBlend = 0;
}

//=============================================================================
//�G�̏���������
//=============================================================================
bool IsRange()
{
	return bRange;
}