//*****************************************
//
// �v���C���[���� [player.cpp]
// Author:Sasaki Soichiro
//
//*****************************************

//*******************
// �C���N���[�h
//*******************
#include "tutorialPlayer.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "texture.h"
#include "camera.h"
#include "object3D.h"
#include "game.h"
#include "rail.h"
#include "particle.h"
#include "blurManager.h"
#include "blockManager.h"
#include "orbit.h"
#include "lifeUI.h"
#include "motion.h"
#include "state.h"
#include "shadowS.h"
#include "mesh.h"
#include "sound.h"
#include "debugproc.h"
#include "itemmanager.h"
#include "gatherparticle.h"
#include "sparkParticle.h"
#include "tutorial.h"

//*******************
// �}�N����`
//*******************
#define SPEED (5.0f)			// �v���C���[�̈ړ����x
#define LANDING_SPEED (20.0f)	// �v���C���[�̈ړ����x
#define DEST (0.3f)
#define BOOST (7.0f)		// �������̔{��
#define HORIZON (0.1f)		// �d��
#define JUMP (5.0f)			// �W�����v��
#define RAIL_JUMP (5.0f)	// ���[�����̃W�����v��
#define RAIL_HORIZON (0.23f)	// ���[�����̏d��

//*****************
// �ÓI�����o�ϐ�
//*****************
float CTutorialPlayer::m_fLife = NULL;

//*****************
// �R���X�g���N�^
//*****************
CTutorialPlayer::CTutorialPlayer(int nPriority) :CObject(nPriority)
{
	// �ϐ��̃N���A
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_oldPos = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	m_vecF = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	m_vecR = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fAngle = 0.0f;
	m_nIdxXFile = -1;
	m_fLife = 100.0f;
	m_State = STATE_NONE;
	m_pMotion = NULL;
	m_pShadow = NULL;
	m_pLifeUI = NULL;
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		m_pOrbit[nCnt] = NULL;
	}
	m_pItemManager = NULL;
	m_nBoostTime = 0;
	m_nStanTime = 0;
	m_nStanCnt = 0;
	m_fSpeed = 0.0f;
	m_nATK = 0;
	m_bReverse = false;
	m_bJumpCancel = false;
}

//*****************
// �f�X�g���N�^
//*****************
CTutorialPlayer::~CTutorialPlayer()
{
}

//******************
// �C���X�^���X����
//*******************
CTutorialPlayer* CTutorialPlayer::Create(D3DXVECTOR3 pos)
{
	CTutorialPlayer* pPlayer;
	// �e�N�X�`�����̎擾
	CTexture* pTexture = CManager::GetCTexture();
	// ���݂̃I�u�W�F�N�g�̑����擾
	int nNum = CObject::GetNumAll();
	if (nNum < MAX_OBJ - 1)
	{// �I�u�W�F�N�g���ő吔�ɒB���Ă��Ȃ��ꍇ

		// �C���X�^���X����
		pPlayer = new CTutorialPlayer;
		// ������
		pPlayer->Init(pos);

		return pPlayer;
	}

	return NULL;
}

//*****************
// ����������
//*****************q
HRESULT CTutorialPlayer::Init(D3DXVECTOR3 pos)
{
	CMesh* pMesh = CTutorial::GetCMesh();
	CCamera* pCamera = CManager::GetCCamera();

	pos.y = pMesh->GetHeight(pos);
	m_pos = pos;							// �ʒu�����ݒ�
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ���������ݒ�
	m_fLife = 50.0f;						// ���C�t�����ݒ�
	m_Machine = new CStateMachine;
	m_pLifeUI = CLifeUI::Create(D3DXVECTOR3(170.0f, 80.0f, 0.0f));
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		m_pOrbit[nCnt] = COrbit::Create(pos);
	}
	m_pItemManager = new CItemManager;
	m_pItemManager->Init();
	m_fAngle = D3DX_PI * 0.5f;
	pCamera->InitTarget(m_pos, D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f));

	// ���[�V�����̓ǂݍ���
	LoadMotion("data\\MOTION\\segway.txt");
	D3DMATRIX mtx0 = m_apModel[14]->GetMtxWorld();
	D3DMATRIX mtx1 = m_apModel[15]->GetMtxWorld();
	D3DXVECTOR3 pos0, pos1;
	pos0.x = mtx0._41;
	pos0.y = mtx0._42;
	pos0.z = mtx0._43;
	pos1.x = mtx1._41;
	pos1.y = mtx1._42;
	pos1.z = mtx1._43;
	m_pOrbit[0]->SetPosS(pos0, pos1);

	mtx0 = m_apModel[17]->GetMtxWorld();
	mtx1 = m_apModel[16]->GetMtxWorld();
	pos0, pos1;
	pos0.x = mtx0._41;
	pos0.y = mtx0._42;
	pos0.z = mtx0._43;
	pos1.x = mtx1._41;
	pos1.y = mtx1._42;
	pos1.z = mtx1._43;
	m_pOrbit[1]->SetPosS(pos0, pos1);

	CTutorialRandState* pRandState = new CTutorialRandState;
	ChangeState(pRandState);
	m_pShadow = CShadowS::Create(pos);

	return S_OK;
}

//*****************
// �I������
//*****************
void CTutorialPlayer::Uninit(void)
{
	if (m_pMotion != NULL)
	{
		m_pMotion->Uninit();
		delete m_pMotion;
		m_pMotion = NULL;
	}
	if (m_pItemManager != NULL)
	{
		m_pItemManager->Uninit();
		delete m_pItemManager;
		m_pItemManager = NULL;
	}

	for (int nCnt = 0; nCnt < m_nNumModel; nCnt++)
	{
		m_apModel[nCnt]->Uninit();
		delete m_apModel[nCnt];
		m_apModel[nCnt] = NULL;
	}
	if (m_Machine != NULL)
	{
		m_Machine->Uninit();
		delete m_Machine;
		m_Machine = NULL;
	}
	CObject::Release();
}

//*****************
// �X�V����
//*****************
void CTutorialPlayer::Update(void)
{
	// �L�[�{�[�h�̎擾
	CInputKeyboard* pInputKeyboard;
	CInputJoypad* pInputJoypad;
	pInputKeyboard = CManager::GetCInputKeyboard();
	pInputJoypad = CManager::GetCInputJoypad();
	CSound* pSound = CManager::GetCSound();
	CBlockManager* pBlockManager = CTutorial::GetCBlockManager();
	m_oldPos = m_pos;

	if (m_fLife >= 102.0f)
	{
		m_nStanTime = 60;
	}
	m_Machine->Update();
	SetRot(D3DXVECTOR3(0.0f, m_fAngle, 0.0f));
	m_pItemManager->Update();
	m_pMotion->Update();
	CDebugProc::Print("\n�v���C���[�̈ʒu X:%f Y:%f Z:%f\n", m_pos.x, m_pos.y, m_pos.z);
	m_pShadow->SetPos(m_pos);
	m_pLifeUI->SetLife(m_fLife);
	m_fLife -= 0.01f * ((m_nStanCnt + 1) * 0.5f);
	m_nBoostTime--;
	m_pos = pBlockManager->Collision(m_pos, m_oldPos);
	D3DMATRIX mtx0 = m_apModel[14]->GetMtxWorld();
	D3DMATRIX mtx1 = m_apModel[15]->GetMtxWorld();
	D3DXVECTOR3 pos0, pos1;
	pos0.x = mtx0._41;
	pos0.y = mtx0._42;
	pos0.z = mtx0._43;
	pos1.x = mtx1._41;
	pos1.y = mtx1._42;
	pos1.z = mtx1._43;

	m_pOrbit[0]->SetPosS(pos0, pos1);

	mtx0 = m_apModel[17]->GetMtxWorld();
	mtx1 = m_apModel[16]->GetMtxWorld();
	pos0, pos1;
	pos0.x = mtx0._41;
	pos0.y = mtx0._42;
	pos0.z = mtx0._43;
	pos1.x = mtx1._41;
	pos1.y = mtx1._42;
	pos1.z = mtx1._43;
	m_pOrbit[1]->SetPosS(pos0, pos1);

	if (m_fLife <= 0.0f)
	{
		m_pLifeUI->SetLife(0.0f);
	}
}

//*****************
// �`�揈��
//*****************
void CTutorialPlayer::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	CRenderer* renderer = CManager::GetCRenderer();
	pDevice = renderer->GetDevice();

	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;
	if (m_State == CTutorialPlayer::STATE_JUMP)
	{
		JumpPosture();
	}
	else
	{
		Posture();
	}

	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// �S�Ẵ��f���̕`��
	for (int nCnt = 0; nCnt < m_nNumModel; nCnt++)
	{
		// ���f���̕`��
		m_apModel[nCnt]->Draw();
	}
}

//******************
// �ʒu�̐ݒ�
//*******************
void CTutorialPlayer::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}
//******************
// �����̐ݒ�
//*******************
void CTutorialPlayer::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//******************
// ���x�̐ݒ�
//*******************
void CTutorialPlayer::SetMove(D3DXVECTOR3 move)
{
	m_move = move;
}

//***************
// �̐��̐ݒ�
//***************
void CTutorialPlayer::Posture(void)
{
	CMesh* pMesh = CTutorial::GetCMesh();

	// �v���C���[�̏�x�N�g��
	D3DXVECTOR3 vecU = pMesh->GetNormal(m_pos);

	m_vecU += (vecU - m_vecU) * DEST;

	D3DXVECTOR3 vecF = -(m_pos - m_oldPos);

	D3DXVec3Normalize(&vecF, &vecF);

	if (D3DXVec3LengthSq(&vecF) > 0.001f)
	{
		m_vecF = vecF;
	}

	D3DXVECTOR3 baseForward = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	D3DXMATRIX rotMtx;
	D3DXMatrixRotationAxis(&rotMtx, &vecU, m_fAngle);

	D3DXVec3TransformNormal(&m_vecF, &baseForward, &rotMtx);


	D3DXVECTOR3 vecR, vecFa;
	D3DXVec3Cross(&vecR, &vecU, &m_vecF);
	D3DXVec3Normalize(&vecR, &vecR);
	m_vecR += (vecR - m_vecR) * DEST;
	D3DXVec3Cross(&m_vecF, &vecR, &vecU);
	D3DXVec3Normalize(&vecFa, &m_vecF);
	m_vecF += (vecFa - m_vecF) * DEST;
	D3DXMatrixIdentity(&m_mtxWorld);

	// ���[���h�}�g���b�N�X�̍X�V
	m_mtxWorld._11 = m_vecR.x;
	m_mtxWorld._12 = m_vecR.y;
	m_mtxWorld._13 = m_vecR.z;
	m_mtxWorld._14 = 0;
	m_mtxWorld._21 = m_vecU.x;
	m_mtxWorld._22 = m_vecU.y;
	m_mtxWorld._23 = m_vecU.z;
	m_mtxWorld._24 = 0;
	m_mtxWorld._31 = m_vecF.x;
	m_mtxWorld._32 = m_vecF.y;
	m_mtxWorld._33 = m_vecF.z;
	m_mtxWorld._34 = 0;
	m_mtxWorld._41 = m_pos.x;
	m_mtxWorld._42 = m_pos.y;
	m_mtxWorld._43 = m_pos.z;
	m_mtxWorld._44 = 1;
}

//************************
// �W�����v���̑̐��̐ݒ�
//************************
void CTutorialPlayer::JumpPosture(void)
{
	CMesh* pMesh = CTutorial::GetCMesh();
	// �v���C���[�̏�x�N�g��
	D3DXVECTOR3 vecU = pMesh->GetNormal(m_pos);
	m_vecU = vecU;

	D3DXVECTOR3 vecF = -m_pos;

	D3DXVec3Normalize(&vecF, &vecF);

	if (D3DXVec3LengthSq(&vecF) > 0.001f)
	{
		m_vecF = vecF;
	}

	D3DXVECTOR3 baseForward = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	D3DXMATRIX rotMtx;
	D3DXMatrixRotationAxis(&rotMtx, &vecU, m_fAngle);

	D3DXVec3TransformNormal(&m_vecF, &baseForward, &rotMtx);


	D3DXVECTOR3 vecR, vecFa;
	D3DXVec3Cross(&vecR, &vecU, &m_vecF);
	D3DXVec3Normalize(&vecR, &vecR);
	m_vecR += (vecR - m_vecR) * DEST;
	D3DXVec3Cross(&m_vecF, &vecR, &vecU);
	D3DXVec3Normalize(&vecFa, &m_vecF);
	m_vecF += (vecFa - m_vecF) * DEST;
	D3DXMatrixIdentity(&m_mtxWorld);

	// ���[���h�}�g���b�N�X�̍X�V
	m_mtxWorld._11 = m_vecR.x;
	m_mtxWorld._12 = m_vecR.y;
	m_mtxWorld._13 = m_vecR.z;
	m_mtxWorld._14 = 0;
	m_mtxWorld._21 = m_vecU.x;
	m_mtxWorld._22 = m_vecU.y;
	m_mtxWorld._23 = m_vecU.z;
	m_mtxWorld._24 = 0;
	m_mtxWorld._31 = m_vecF.x;
	m_mtxWorld._32 = m_vecF.y;
	m_mtxWorld._33 = m_vecF.z;
	m_mtxWorld._34 = 0;
	m_mtxWorld._41 = m_pos.x;
	m_mtxWorld._42 = m_pos.y;
	m_mtxWorld._43 = m_pos.z;
	m_mtxWorld._44 = 1;
}

//************************
// ���[�V�����̓ǂݍ���
//************************
void CTutorialPlayer::LoadMotion(const char* pMotionScript)
{
	FILE* pFile = NULL;
	pFile = fopen(pMotionScript, "r");

	int nCntModel = 0, nCntParts = 0, nIdx = 0, nParents = 0, nCntKey = 0, nCntMotion = 0;
	int nBool;
	int nParent;
	char str[MAX_WORD];
	char FileName[30][MAX_WORD];
	D3DXVECTOR3 pos, rot;
	CMotion::MOTION_INFO Info;

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
						fscanf(pFile, "%d", &m_nNumModel);
						while (nCntModel < m_nNumModel)
						{
							//�t�@�C����ǂݍ���
							fscanf(pFile, "%s", &aString[0]);

							if (strcmp(aString, "MODEL_FILENAME") == 0)
							{
								fscanf(pFile, "%s", &str[0]);
								fscanf(pFile, "%s", &FileName[nCntModel][0]);
								m_apModel[nCntModel] = CModel::Create(pos, FileName[nCntModel]);
								nCntModel++;
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
								fscanf(pFile, "%d", &m_nNumModel);

							}
							while (nCntParts < m_nNumModel)
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
											fscanf(pFile, "%d", &nParent);
											if (nParent != -1)
											{
												m_apModel[nIdx]->SetParent(m_apModel[nParent]);
											}
										}
										else if (strcmp(aString, "POS") == 0)
										{
											fscanf(pFile, "%s", &str[0]);
											fscanf(pFile, "%f", &pos.x);
											fscanf(pFile, "%f", &pos.y);
											fscanf(pFile, "%f", &pos.z);
											m_apModel[nCntParts]->SetOffSetPos(pos);
											m_apModel[nCntParts]->SetPos(pos);
										}
										else if (strcmp(aString, "ROT") == 0)
										{
											fscanf(pFile, "%s", &str[0]);
											fscanf(pFile, "%f", &rot.x);
											fscanf(pFile, "%f", &rot.y);
											fscanf(pFile, "%f", &rot.z);
											m_apModel[nCntParts]->SetRot(rot);
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
						if (m_pMotion == NULL)
						{
							m_pMotion = CMotion::Create(&m_apModel[0], m_nNumModel, false);
						}
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
									Info.bLoop = false;
								}
								else
								{
									Info.bLoop = true;
								}
							}

							if (strcmp(aString, "NUM_KEY") == 0)
							{
								fscanf(pFile, "%s", &str[0]);
								fscanf(pFile, "%d", &Info.nNumKey);

								while (nCntKey < Info.nNumKey)
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
												fscanf(pFile, "%d", &Info.aKeyInfo[nCntKey].nFlame);
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
														fscanf(pFile, "%f", &Info.aKeyInfo[nCntKey].aKey[nCntParts].fPosX);
														fscanf(pFile, "%f", &Info.aKeyInfo[nCntKey].aKey[nCntParts].fPosY);
														fscanf(pFile, "%f", &Info.aKeyInfo[nCntKey].aKey[nCntParts].fPosZ);
													}
													if (strcmp(aString, "ROT") == 0)
													{
														fscanf(pFile, "%s", &str[0]);
														fscanf(pFile, "%f", &Info.aKeyInfo[nCntKey].aKey[nCntParts].fRotX);
														fscanf(pFile, "%f", &Info.aKeyInfo[nCntKey].aKey[nCntParts].fRotY);
														fscanf(pFile, "%f", &Info.aKeyInfo[nCntKey].aKey[nCntParts].fRotZ);
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
								if (m_pMotion != NULL)
								{
									m_pMotion->SetInfo(Info);
								}
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
}

//***********
// �i�ޕ���
//***********
void CTutorialPlayer::AngleVelocity(float speed, float omega)
{
	float fSpeed = speed;
	if (m_nBoostTime > 0)
	{
		fSpeed = BOOST;
	}

	m_move.x = sinf(m_fAngle) * fSpeed;
	m_move.z = cosf(m_fAngle) * fSpeed;
	m_fAngle += omega;
	// ����
	SpeedUp();
}

//**************
// �~�܂�x��
//**************
void CTutorialPlayer::Decay(void)
{
	// ���X�Ɏ~�܂�
	m_move.x += (0.0f - m_move.x) * 0.05f;
	m_move.z += (0.0f - m_move.z) * 0.05f;

	m_pos += m_move;	// ���݂̈ʒu��move�l�𑫂�
}

//*********************
// ���X�ɉ������Ă���
//*********************
void CTutorialPlayer::SpeedUp(void)
{
	if (m_fSpeed < SPEED)
	{
		m_fSpeed += Acceleration;
	}
}

//*********************
// ����
//*********************
void CTutorialPlayer::SpeedDown(void)
{
	if (m_fSpeed > 0.0f)
	{
		m_fSpeed -= 0.1f;
	}
	else
	{
		m_fSpeed = 0.0f;
	}

}

int CTutorialPlayer::GetATK(void)
{
	int nATK = m_nATK;
	if (m_bElec)
	{
		nATK += 2;
	}
	return nATK;
}


//****************
// ���[�����o��
//****************
void CTutorialPlayer::PutOutRail(void)
{
	D3DXVECTOR3 pos[4];
	pos[0].x = m_pos.x + sinf(m_fAngle + D3DX_PI) * 200.0f * -1;
	pos[0].y = m_pos.y;
	pos[0].z = m_pos.z + cosf(m_fAngle + D3DX_PI) * 200.0f * -1;

	for (int nCnt = 1; nCnt < 4; nCnt++)
	{
		pos[nCnt].x = m_pos.x + sinf(m_fAngle + D3DX_PI) * 200.0f * nCnt;
		pos[nCnt].y = m_pos.y;
		pos[nCnt].z = m_pos.z + cosf(m_fAngle + D3DX_PI) * 200.0f * nCnt;
	}
	CRail::Create(pos[0], pos[1], pos[2], pos[3], 1);
}

void CTutorialPlayer::ChangeState(CTutorialPlayerStateBase* pState)
{
	pState->SetOwner(this);
	m_Machine->ChangeState(pState);
}

CTutorialPlayerStateBase::CTutorialPlayerStateBase()
{
	m_pPlayer = NULL;
}

CTutorialPlayerStateBase::~CTutorialPlayerStateBase()
{

}

void CTutorialPlayerStateBase::SetOwner(CTutorialPlayer* pPlayer)
{
	m_pPlayer = pPlayer;
}


CTutorialRandState::CTutorialRandState()
{

}
CTutorialRandState::~CTutorialRandState()
{

}
void CTutorialRandState::Init(void)
{
	m_pPlayer->SetATK(1);
}
void CTutorialRandState::Update(void)
{
	// �L�[�{�[�h�̎擾
	CInputKeyboard* pInputKeyboard;
	CInputJoypad* pInputJoypad;
	CCamera* pCamera = CManager::GetCCamera();
	pInputKeyboard = CManager::GetCInputKeyboard();
	pInputJoypad = CManager::GetCInputJoypad();
	XINPUT_STATE* pInputJoyStick = pInputJoypad->GetState();
	CMotion* pMotion = m_pPlayer->GetMotion();
	float fLife = m_pPlayer->GetLife();
	D3DXVECTOR3 posC, rotC;
	posC = m_pPlayer->GetPos();
	rotC = m_pPlayer->GetRot();
	float RightSpeed = 0.0f, LeftSpeed = 0.0f;

	int nStanTime = m_pPlayer->GetStan();
	bool bStan = nStanTime > 0;// �X�^������������
	if (bStan == true)
	{
		nStanTime--;
		m_pPlayer->SetLife(101.0f);
		if (nStanTime <= 0)
		{
			m_pPlayer->SetLife(95.0f);
			m_pPlayer->AddStanCnt();
		}
		m_pPlayer->SetStan(nStanTime);
	}
	else
	{
		Controll();
	}


	//m_pPlayer->Decay();

	CMesh* pMesh = CTutorial::GetCMesh();
	D3DXVECTOR3 pos = m_pPlayer->GetPos();// ���݂̈ʒu����
	if (m_pPlayer->GetState() != CTutorialPlayer::STATE_RAIL)
	{
		pos.y = pMesh->GetHeight(pos);
	}
	// �v���C���[�̏�x�N�g��
	D3DXVECTOR3 vecU = pMesh->GetNormal(pos);
	D3DXVECTOR3 playerVecU = m_pPlayer->GetVecU();
	bool KeyboardVecU = vecU.y - playerVecU.y > 0.4 && pInputKeyboard->GetPress(DIK_LSHIFT) == false && pInputKeyboard->GetPress(DIK_RSHIFT) == false;
	bool JoypadVecU = vecU.y - playerVecU.y > 0.4 && pInputJoypad->GetPress(CInputJoypad::JOYKEY_Y) == false;
	bool JoypadCancel = vecU.y - playerVecU.y > 0.4 && pInputJoypad->GetPress(CInputJoypad::JOYKEY_Y) == true;
	bool Speed = m_pPlayer->GetSpeed() > 3.0f;
	if (JoypadCancel)
	{
		m_pPlayer->SetJumpCancel(true);
	}
	if (KeyboardVecU == true && JoypadVecU == true && Speed)
	{// �W�����v����
		m_pPlayer->SetState(CTutorialPlayer::STATE_JUMP);
		pos.x = pos.x + sinf(m_pPlayer->GetAngle()) * 10.0f;
		pos.z = pos.z + cosf(m_pPlayer->GetAngle()) * 10.0f;
		m_pPlayer->SetPos(pos);
		CTutorialJumpState* pJumpState = new CTutorialJumpState;
		m_pPlayer->ChangeState(pJumpState);
	}
	else
	{
		m_pPlayer->SetPos(pos);	// �ʒu��ݒ�
	}

}
void CTutorialRandState::Uninit(void)
{

}
void CTutorialRandState::Controll(void)
{
	CCamera* pCamera = CManager::GetCCamera();
	CInputJoypad* pInputJoypad;
	CInputKeyboard* pInputKeyboard;
	pInputJoypad = CManager::GetCInputJoypad();
	pInputKeyboard = CManager::GetCInputKeyboard();
	XINPUT_STATE* pInputJoyStick = pInputJoypad->GetState();

	CSound* pSound = CManager::GetCSound();

	float fSpeed = m_pPlayer->GetSpeed();

	bool bFlont = pInputJoyStick->Gamepad.sThumbLY >= 10000;
	bool bBack = pInputJoyStick->Gamepad.sThumbLY <= -10000;
	bool bLeft = pInputJoypad->GetPress(CInputJoypad::JOYKEY_RIGHTS);
	bool bRight = pInputJoypad->GetPress(CInputJoypad::JOYKEY_LEFTS);
	bool bLeftback = pInputKeyboard->GetPress(DIK_A) == true;
	bool bRightback = pInputKeyboard->GetPress(DIK_D) == true;
	bool bLeftflont = pInputKeyboard->GetPress(DIK_Q) == true;
	bool bRightflont = pInputKeyboard->GetPress(DIK_E) == true;

	if (m_pPlayer->GetReverse() == true)
	{
		bLeft = pInputJoypad->GetPress(CInputJoypad::JOYKEY_LEFTS);
		bRight = pInputJoypad->GetPress(CInputJoypad::JOYKEY_RIGHTS);
		bLeftback = pInputKeyboard->GetPress(DIK_D) == true;
		bRightback = pInputKeyboard->GetPress(DIK_A) == true;
		bLeftflont = pInputKeyboard->GetPress(DIK_E) == true;
		bRightflont = pInputKeyboard->GetPress(DIK_Q) == true;
	}

	CMotion* pMotion = m_pPlayer->GetMotion();
	D3DXVECTOR3 posC, rotC;
	posC = m_pPlayer->GetPos();
	rotC = m_pPlayer->GetRot();

	float RightSpeed = 0.0f, LeftSpeed = 0.0f;

	if (bBack == true)
	{// �������������ɐi�ނƂ�
		if (bRight == true)
		{// �E�����������̂Ƃ�
			RightSpeed = fSpeed;
			pMotion->SetMotion(CTutorialPlayer::MOTION_RB);
			// �v���C���[�J�����Ǐ]
			pCamera->Target(posC, rotC);
		}
		else if (bLeft == true)
		{// �E�����O�����̂Ƃ�
			LeftSpeed = fSpeed;
			// �v���C���[�J�����Ǐ]
			pCamera->Target(posC, rotC);
			pMotion->SetMotion(CTutorialPlayer::MOTION_LB);
		}
		else
		{
			RightSpeed = fSpeed * backSpeed;
			LeftSpeed = fSpeed * backSpeed;
			// �v���C���[�J�����Ǐ]
			pCamera->BackTarget(posC, rotC);
			pMotion->SetMotion(CTutorialPlayer::MOTION_BACK);
		}

		float fSumSpeed = (RightSpeed + LeftSpeed) / 2.0f;
		float omega = (RightSpeed - LeftSpeed) / 50.0f; // ��]�����i�p���x�j
		m_pPlayer->AngleVelocity(fSumSpeed, omega);

	}
	else if (bFlont == true)
	{// �������O�����ɐi�ނƂ�
		if (bRight == true)
		{// �E�����������̂Ƃ�
			RightSpeed = -fSpeed;
			// �v���C���[�J�����Ǐ]
			pCamera->Target(posC, rotC);
			pMotion->SetMotion(CTutorialPlayer::MOTION_RF);

		}
		else if (bLeft == true)
		{// �E�����O�����̂Ƃ�
			LeftSpeed = -fSpeed;
			// �v���C���[�J�����Ǐ]
			pCamera->Target(posC, rotC);
			pMotion->SetMotion(CTutorialPlayer::MOTION_LF);
		}
		else
		{
			RightSpeed = -fSpeed;
			LeftSpeed = -fSpeed;
			// �v���C���[�J�����Ǐ]
			pCamera->Target(posC, rotC);

			pMotion->SetMotion(CTutorialPlayer::MOTION_FLONT);
		}

		float fSumSpeed = (RightSpeed + LeftSpeed) / 2.0f;
		float omega = (RightSpeed - LeftSpeed) / 50.0f; // ��]�����i�p���x�j
		m_pPlayer->AngleVelocity(fSumSpeed, omega);

	}
	else if (pInputJoypad->GetPress(CInputJoypad::JOYKEY_A) == true)
	{// �E�����������̂Ƃ�
		RightSpeed = -fSpeed;
		LeftSpeed = fSpeed;
		// �v���C���[�J�����Ǐ]
		pCamera->Target(posC, D3DXVECTOR3(0.0f, 0.0f, 0.0f));

		pMotion->SetMotion(CTutorialPlayer::MOTION_FB);

		float fSumSpeed = (RightSpeed + LeftSpeed) / 2.0f;
		float omega = (RightSpeed - LeftSpeed) / 50.0f; // ��]�����i�p���x�j
		m_pPlayer->AngleVelocity(fSumSpeed, omega);

	}
	else if (pInputJoypad->GetPress(CInputJoypad::JOYKEY_X) == true)
	{// �E�����O�����̂Ƃ�
		RightSpeed = fSpeed;
		LeftSpeed = -fSpeed;
		// �v���C���[�J�����Ǐ]
		pCamera->Target(posC, D3DXVECTOR3(0.0f, 0.0f, 0.0f));

		pMotion->SetMotion(CTutorialPlayer::MOTION_BF);

		float fSumSpeed = (RightSpeed + LeftSpeed) / 2.0f;
		float omega = (RightSpeed - LeftSpeed) / 50.0f; // ��]�����i�p���x�j
		m_pPlayer->AngleVelocity(fSumSpeed, omega);

	}
	else if (bLeftback == true)
	{// �������������ɐi�ނƂ�
		if (bRightback == true)
		{// �E�����������̂Ƃ�
			RightSpeed = fSpeed;
			pMotion->SetMotion(CTutorialPlayer::MOTION_BACK);
			// �v���C���[�J�����Ǐ]
			pCamera->BackTarget(posC, rotC);
		}
		else if (bRightflont == true)
		{// �E�����O�����̂Ƃ�
			RightSpeed = -fSpeed;
			pMotion->SetMotion(CTutorialPlayer::MOTION_BF);
			// �v���C���[�J�����Ǐ]
			pCamera->Target(posC, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		}
		else
		{
			// �v���C���[�J�����Ǐ]
			pCamera->Target(posC, rotC);
			pMotion->SetMotion(CTutorialPlayer::MOTION_LB);
		}
		LeftSpeed = fSpeed;

		float fSumSpeed = (RightSpeed + LeftSpeed) / 2.0f;
		float omega = (RightSpeed - LeftSpeed) / 50.0f; // ��]�����i�p���x�j
		m_pPlayer->AngleVelocity(fSumSpeed, omega);

	}
	else if (bLeftflont == true)
	{// �������O�����ɐi�ނƂ�
		if (bRightback == true)
		{// �E�����������̂Ƃ�
			RightSpeed = fSpeed;
			pMotion->SetMotion(CTutorialPlayer::MOTION_FB);
			// �v���C���[�J�����Ǐ]
			pCamera->Target(posC, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		}
		else if (bRightflont == true)
		{// �E�����O�����̂Ƃ�
			RightSpeed = -fSpeed;
			// �v���C���[�J�����Ǐ]
			pCamera->Target(posC, rotC);
			pMotion->SetMotion(CTutorialPlayer::MOTION_FLONT);
		}
		else
		{
			// �v���C���[�J�����Ǐ]
			pCamera->Target(posC, rotC);

			pMotion->SetMotion(CTutorialPlayer::MOTION_LF);
		}
		LeftSpeed = -fSpeed;

		float fSumSpeed = (RightSpeed + LeftSpeed) / 2.0f;
		float omega = (RightSpeed - LeftSpeed) / 50.0f; // ��]�����i�p���x�j
		m_pPlayer->AngleVelocity(fSumSpeed, omega);

	}
	else if (bRightback == true)
	{// �E�����������̂Ƃ�
		RightSpeed = fSpeed;
		// �v���C���[�J�����Ǐ]
		pCamera->Target(posC, rotC);

		pMotion->SetMotion(CTutorialPlayer::MOTION_RB);

		float fSumSpeed = (RightSpeed + LeftSpeed) / 2.0f;
		float omega = (RightSpeed - LeftSpeed) / 50.0f; // ��]�����i�p���x�j
		m_pPlayer->AngleVelocity(fSumSpeed, omega);

	}
	else if (bRightflont == true)
	{// �E�����O�����̂Ƃ�
		RightSpeed = -fSpeed;
		// �v���C���[�J�����Ǐ]
		pCamera->Target(posC, rotC);

		pMotion->SetMotion(CTutorialPlayer::MOTION_RF);

		float fSumSpeed = (RightSpeed + LeftSpeed) / 2.0f;
		float omega = (RightSpeed - LeftSpeed) / 50.0f; // ��]�����i�p���x�j
		m_pPlayer->AngleVelocity(fSumSpeed, omega);

	}
	else
	{
		// �v���C���[�J�����Ǐ]
		pCamera->Target(posC, rotC);
		pMotion->SetMotion(CTutorialPlayer::MOTION_NUETORAL);
		m_pPlayer->SpeedDown();
	}
	int nBoost = m_pPlayer->GetBoostTime();
	if (pInputKeyboard->Trigger(DIK_S) && nBoost < -20 || pInputJoypad->GetTrigger(CInputJoypad::JOYKEY_B) && nBoost < -20)
	{
		nBoost = 10;
		float fSumSpeed = (RightSpeed + LeftSpeed) / 2.0f;
		float omega = (RightSpeed - LeftSpeed) / 50.0f; // ��]�����i�p���x�j

		m_pPlayer->SetBoostTime(nBoost);
		m_pPlayer->AngleVelocity(fSumSpeed, omega);

		pSound->Play(CSound::LABEL_SE03);
	}


	m_pPlayer->Decay();

}

CTutorialJumpState::CTutorialJumpState()
{
	m_fAngle = 0.0f;
	m_fAngleSum = 0.0f;
}
CTutorialJumpState::~CTutorialJumpState()
{

}
void CTutorialJumpState::Init(void)
{
	D3DXVECTOR3 move = m_pPlayer->GetMove();
	move.y = m_pPlayer->GetSpeed();
	m_pPlayer->SetMove(move);
	m_fAngleSum = 0.0f;
	m_pPlayer->SetATK(2);

	CMotion* pMotion = m_pPlayer->GetMotion();
	pMotion->SetMotion(CTutorialPlayer::MOTION_JUMP);

}
void CTutorialJumpState::Update(void)
{
	// �L�[�{�[�h�̎擾
	CInputKeyboard* pKeyboard;
	CInputJoypad* pJoypad;
	CCamera* pCamera = CManager::GetCCamera();
	pKeyboard = CManager::GetCInputKeyboard();
	pJoypad = CManager::GetCInputJoypad();
	XINPUT_STATE* pJoyStick = pJoypad->GetState();
	CMotion* pMotion = m_pPlayer->GetMotion();
	float fLife = m_pPlayer->GetLife();
	D3DXVECTOR3 posC, rotC;
	posC = m_pPlayer->GetPos();
	rotC = m_pPlayer->GetRot();
	float RightSpeed = 0.0f, LeftSpeed = 0.0f;
	Controll();
	float DistX = posC.x - 0.0f;
	float DistZ = posC.z - 0.0f;
	float fAngle = atan2f(DistX, DistZ);
	// �v���C���[�J�����Ǐ]
	pCamera->JumpTarget(posC, fAngle);
	D3DXVECTOR3 pos = m_pPlayer->GetPos();// ���݂̈ʒu����
	D3DXVECTOR3 move = m_pPlayer->GetMove();
	move.x = 0.0f;
	move.y -= HORIZON;
	move.z = 0.0f;
	if (move.y > 0.0f)
	{
		bool bElec = pKeyboard->Trigger(DIK_RSHIFT)
			|| pKeyboard->Trigger(DIK_LSHIFT)
			|| pJoypad->GetTrigger(CInputJoypad::JOYKEY_Y);

		if (bElec)
		{
			// ���[�V�����̎擾
			CMotion* pMotion = m_pPlayer->GetMotion();
			pMotion->SetMotion(CTutorialPlayer::MOTION_ELECJUMP);
			m_pPlayer->SetElec(true);
		}
	}
	pos += move;
	m_pPlayer->Decay();
	// ��]���J�E���g����
	Rotation();
	CMesh* pMesh = CTutorial::GetCMesh();
	if (pos.y < pMesh->GetHeight(pos))
	{
		m_pPlayer->SetState(CTutorialPlayer::STATE_LANDING);
		m_pPlayer->SetAngle(fAngle);
		CTutorialLandingState* pLandingState = new CTutorialLandingState;
		m_pPlayer->ChangeState(pLandingState);
	}
	else
	{
		m_pPlayer->SetPos(pos);		// �ʒu��ݒ�
		m_pPlayer->SetMove(move);	// �ʒu��ݒ�
	}
}
void CTutorialJumpState::Uninit(void)
{

}

void CTutorialJumpState::Rotation(void)
{
	float OldAngle = m_fAngle;
	float fLife = m_pPlayer->GetLife();
	m_fAngle = m_pPlayer->GetAngle();
	m_fAngleSum += fabs(OldAngle - m_fAngle);

	if (m_fAngleSum > D3DX_PI * 2.0f)
	{
		m_fAngleSum = 0.0f;
		fLife += 2.0f;
		if (fLife < 100.0f)
		{
			m_pPlayer->SetLife(fLife);
		}
		else
		{
			m_pPlayer->SetLife(100.0f);
		}


	}
}

void CTutorialJumpState::Controll(void)
{
	// �L�[�{�[�h�̎擾
	CInputKeyboard* pInputKeyboard;
	CInputJoypad* pInputJoypad;

	CCamera* pCamera = CManager::GetCCamera();
	pInputKeyboard = CManager::GetCInputKeyboard();
	pInputJoypad = CManager::GetCInputJoypad();
	XINPUT_STATE* pInputJoyStick = pInputJoypad->GetState();
	CMotion* pMotion = m_pPlayer->GetMotion();
	D3DXVECTOR3 pos, rot;
	pos = m_pPlayer->GetPos();
	rot = m_pPlayer->GetRot();
	float RightSpeed = 0.0f, LeftSpeed = 0.0f;
	bool bFlont = pInputJoyStick->Gamepad.sThumbLY >= 10000;
	bool bBack = pInputJoyStick->Gamepad.sThumbLY <= -10000;
	bool bLeft = pInputJoypad->GetPress(CInputJoypad::JOYKEY_RIGHTS);
	bool bRight = pInputJoypad->GetPress(CInputJoypad::JOYKEY_LEFTS);
	bool bLeftback = pInputKeyboard->GetPress(DIK_A) == true;	// ��:��
	bool bRightback = pInputKeyboard->GetPress(DIK_D) == true;	// �E:��
	bool bLeftflont = pInputKeyboard->GetPress(DIK_Q) == true;	// ��:�O
	bool bRightflont = pInputKeyboard->GetPress(DIK_E) == true;	// �E:�O

	if (bBack == true)
	{// �������������ɐi�ނƂ�
		if (bRight == true)
		{// �E�����������̂Ƃ�
			RightSpeed = SPEED;
		}
		else if (bLeft == true)
		{// �E�����O�����̂Ƃ�
			LeftSpeed = SPEED;
		}
		else
		{
			RightSpeed = SPEED;
			LeftSpeed = SPEED;
		}
		float omega = (RightSpeed - LeftSpeed) / 50.0f; // ��]�����i�p���x�j
		m_pPlayer->AngleVelocity(0.0f, omega);

	}
	else if (bFlont == true)
	{// �������O�����ɐi�ނƂ�
		if (bRight == true)
		{// �E�����������̂Ƃ�
			RightSpeed = -SPEED;

		}
		else if (bLeft == true)
		{// �E�����O�����̂Ƃ�
			LeftSpeed = -SPEED;
		}
		else
		{
			RightSpeed = -SPEED;
			LeftSpeed = -SPEED;

		}
		float omega = (RightSpeed - LeftSpeed) / 50.0f; // ��]�����i�p���x�j
		m_pPlayer->AngleVelocity(0.0f, omega);

	}
	else if (pInputJoypad->GetPress(CInputJoypad::JOYKEY_A) == true)
	{// �E�����������̂Ƃ�
		RightSpeed = -SPEED;
		LeftSpeed = SPEED;

		float omega = (RightSpeed - LeftSpeed) / 50.0f; // ��]�����i�p���x�j
		m_pPlayer->AngleVelocity(0.0f, omega);

	}
	else if (pInputJoypad->GetPress(CInputJoypad::JOYKEY_X) == true)
	{// �E�����O�����̂Ƃ�
		RightSpeed = SPEED;
		LeftSpeed = -SPEED;

		float omega = (RightSpeed - LeftSpeed) / 50.0f; // ��]�����i�p���x�j
		m_pPlayer->AngleVelocity(0.0f, omega);

	}
	else if (bLeftback == true)
	{// �������������ɐi�ނƂ�
		if (bRightback == true)
		{// �E�����������̂Ƃ�
			RightSpeed = SPEED;
		}
		else if (bRightflont == true)
		{// �E�����O�����̂Ƃ�
			RightSpeed = -SPEED;
		}
		LeftSpeed = SPEED;
		float omega = (RightSpeed - LeftSpeed) / 50.0f; // ��]�����i�p���x�j
		m_pPlayer->AngleVelocity(0.0f, omega);

	}
	else if (bLeftflont == true)
	{// �������O�����ɐi�ނƂ�
		if (bRightback == true)
		{// �E�����������̂Ƃ�
			RightSpeed = SPEED;
		}
		else if (bRightflont == true)
		{// �E�����O�����̂Ƃ�
			RightSpeed = -SPEED;
		}

		LeftSpeed = -SPEED;
		float omega = (RightSpeed - LeftSpeed) / 50.0f; // ��]�����i�p���x�j
		m_pPlayer->AngleVelocity(0.0f, omega);

	}
	else if (bRightback == true)
	{// �E�����������̂Ƃ�
		RightSpeed = SPEED;
		float omega = (RightSpeed - LeftSpeed) / 50.0f; // ��]�����i�p���x�j
		m_pPlayer->AngleVelocity(0.0f, omega);

	}
	else if (bRightflont == true)
	{// �E�����O�����̂Ƃ�
		RightSpeed = -SPEED;
		float omega = (RightSpeed - LeftSpeed) / 50.0f; // ��]�����i�p���x�j
		m_pPlayer->AngleVelocity(0.0f, omega);

	}

}

CTutorialRailState::CTutorialRailState()
{

}
CTutorialRailState::~CTutorialRailState()
{

}
void CTutorialRailState::Init(void)
{
	// ���[�V�����̎擾
	CMotion* pMotion = m_pPlayer->GetMotion();
	pMotion->SetMotion(CTutorialPlayer::MOTION_RAILL);

}
void CTutorialRailState::Update(void)
{
	// ���͂̎擾
	CInputKeyboard* pKeyboard = CManager::GetCInputKeyboard();
	CInputJoypad* pJoypad = CManager::GetCInputJoypad();
	XINPUT_STATE* pInputJoyStick = pJoypad->GetState();
	// ���[�V�����̎擾
	CMotion* pMotion = m_pPlayer->GetMotion();

	bool bLeft = pInputJoyStick->Gamepad.sThumbLX <= -20000 || pKeyboard->GetPress(DIK_Q);
	bool bRight = pInputJoyStick->Gamepad.sThumbLX >= 20000 || pKeyboard->GetPress(DIK_E);

	if (bLeft)
	{// ������
		pMotion->SetMotion(CTutorialPlayer::MOTION_RAILL);
	}
	else if (bRight)
	{// �E����
		pMotion->SetMotion(CTutorialPlayer::MOTION_RAILR);
	}

	// �J����
	CCamera* pCamera = CManager::GetCCamera();
	D3DXVECTOR3 pos, rot;
	pos = m_pPlayer->GetPos();
	rot = m_pPlayer->GetRot();
	pCamera->Target(pos, rot);
}
void CTutorialRailState::Uninit(void)
{

}


CTutorialRailChangeState::CTutorialRailChangeState()
{

}
CTutorialRailChangeState::~CTutorialRailChangeState()
{

}
void CTutorialRailChangeState::Init(void)
{
	// ���͂̎擾
	CInputKeyboard* pKeyboard = CManager::GetCInputKeyboard();
	CInputJoypad* pJoypad = CManager::GetCInputJoypad();
	XINPUT_STATE* pInputJoyStick = pJoypad->GetState();
	// ���[�V�����̎擾
	CMotion* pMotion = m_pPlayer->GetMotion();
	pMotion->SetMotion(CTutorialPlayer::MOTION_RAILJUMP);

	D3DXVECTOR3 rot = m_pPlayer->GetRot();
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	bool bLeft = pInputJoyStick->Gamepad.sThumbLX <= -20000 || pKeyboard->GetPress(DIK_Q);
	bool bRight = pInputJoyStick->Gamepad.sThumbLX >= 20000 || pKeyboard->GetPress(DIK_E);
	if (bLeft)
	{
		move.x = sinf(rot.y + (D3DX_PI * 0.5f));
		move.z = cosf(rot.y + (D3DX_PI * 0.5f));
	}
	else if (bRight)
	{
		move.x = sinf(rot.y - (D3DX_PI * 0.5f));
		move.z = cosf(rot.y - (D3DX_PI * 0.5f));
	}
	move.y = RAIL_JUMP;
	m_pPlayer->SetMove(move);
}
void CTutorialRailChangeState::Update(void)
{
	// �v���C���[���擾
	D3DXVECTOR3 pos = m_pPlayer->GetPos();
	D3DXVECTOR3 rot = m_pPlayer->GetRot();
	D3DXVECTOR3 move = m_pPlayer->GetMove();
	// ���b�V���擾
	CMesh* pMesh = CTutorial::GetCMesh();
	// �J�����擾
	CCamera* pCamera = CManager::GetCCamera();

	move.y -= RAIL_HORIZON;
	pos += move;
	pCamera->Target(pos, rot);

	m_pPlayer->Decay();

	if (pos.y < pMesh->GetHeight(pos))
	{
		m_pPlayer->SetState(CTutorialPlayer::STATE_NONE);
		CTutorialRandState* pRandState = new CTutorialRandState;
		m_pPlayer->ChangeState(pRandState);
	}
	else
	{
		m_pPlayer->SetPos(pos);		// �ʒu��ݒ�
		m_pPlayer->SetMove(move);	// �ʒu��ݒ�
	}

}
void CTutorialRailChangeState::Uninit(void)
{

}

//*****************
// �R���X�g���N�^
//*****************
CTutorialLandingState::CTutorialLandingState()
{
	m_nCnt = 0;
	m_nDirectionType = 0;
}

//*****************
// �f�X�g���N�^
//*****************
CTutorialLandingState::~CTutorialLandingState()
{

}

//*************
// ����������
//*************
void CTutorialLandingState::Init(void)
{
	// ���͂̎擾
	CInputKeyboard* pKeyboard = CManager::GetCInputKeyboard();
	CInputJoypad* pJoypad = CManager::GetCInputJoypad();

	m_nCnt = 30;
	m_pPlayer->SetATK(2);

	// ����
	bool bLeft = pJoypad->GetPress(CInputJoypad::JOYKEY_A);
	bool bRight = pJoypad->GetPress(CInputJoypad::JOYKEY_X);
	bool bLeftback = pKeyboard->GetPress(DIK_A) == true;
	bool bRightback = pKeyboard->GetPress(DIK_D) == true;
	bool bLeftflont = pKeyboard->GetPress(DIK_Q) == true;
	bool bRightflont = pKeyboard->GetPress(DIK_E) == true;


	if (m_pPlayer->GetReverse() == true)
	{// ���͔��]
		bLeft = pJoypad->GetPress(CInputJoypad::JOYKEY_X);
		bRight = pJoypad->GetPress(CInputJoypad::JOYKEY_A);
		bLeftback = pKeyboard->GetPress(DIK_D) == true;
		bRightback = pKeyboard->GetPress(DIK_A) == true;
		bLeftflont = pKeyboard->GetPress(DIK_E) == true;
		bRightflont = pKeyboard->GetPress(DIK_Q) == true;
	}

	// �i�ޕ���
	if (bLeftback && bRightflont || bLeft)
	{
		m_nDirectionType = 1;
	}
	else if (bLeftflont && bRightback || bRight)
	{
		m_nDirectionType = 2;

	}
}

//*************
// �X�V����
//*************
void CTutorialLandingState::Update(void)
{
	// �J�������擾
	CCamera* pCamera = CManager::GetCCamera();
	// �v���C���[���擾
	D3DXVECTOR3 pos = m_pPlayer->GetPos();
	D3DXVECTOR3 rot = m_pPlayer->GetRot();
	// ���[�V�����̎擾
	CMotion* pMotion = m_pPlayer->GetMotion();
	// ���b�V���擾
	CMesh* pMesh = CTutorial::GetCMesh();

	// �v���C���[�J�����Ǐ]
	pCamera->Target(pos, rot);
	pMotion->SetMotion(CTutorialPlayer::MOTION_FLONT);

	float RightSpeed = 0.0f;
	float LeftSpeed = 0.0f;

	// �܂������ɐi��
	RightSpeed = maxSpeed;
	LeftSpeed = maxSpeed;

	// ���ɋȂ���
	if (m_nDirectionType == 1)
	{
		RightSpeed = maxSpeed;
		LeftSpeed = minSpeed;

	}

	// �E�ɋȂ���
	else if (m_nDirectionType == 2)
	{
		RightSpeed = minSpeed;
		LeftSpeed = maxSpeed;
	}

	// �i�ޕ����v�Z
	float speed = (RightSpeed + LeftSpeed) / speedDivision;
	float omega = (RightSpeed - LeftSpeed) / omegaRadius; // ��]�����i�p���x�j
	m_pPlayer->AngleVelocity(speed, omega);

	// ���b�V���̍���
	pos.y = pMesh->GetHeight(pos);

	// �ʒu�𔽉f
	m_pPlayer->SetPos(pos);
	m_pPlayer->Decay();
	// �p�[�e�B�N��
	if (m_pPlayer->GetElec())
	{
		CParticle::Create(D3DXVECTOR3(pos.x, pos.y + 40.0f, pos.z),
			20,
			D3DXVECTOR2(3.0f, 3.0f),
			4,
			50,
			1,
			D3DXCOLOR(0.9f, 0.3f, 0.9f, 1.0f));
		float fLife = m_pPlayer->GetLife();
		fLife -= 1.0f;
		m_pPlayer->SetLife(fLife);
	}


	// �J�E���g�ŏ�Ԃ�ς���
	m_nCnt--;
	if (m_nCnt <= 0)
	{
		// ��Ԃ�ς���
		m_pPlayer->SetState(CTutorialPlayer::STATE_NONE);
		CTutorialRandState* pRandState = new CTutorialRandState;
		m_pPlayer->ChangeState(pRandState);
		return;
	}

}

//*************
// �I������
//*************
void CTutorialLandingState::Uninit(void)
{
	m_pPlayer->SetElec(false);
}


CTutorialInoperableState::CTutorialInoperableState()
{
	m_nCnt = 0;
}
CTutorialInoperableState::~CTutorialInoperableState()
{

}
void CTutorialInoperableState::Init(void)
{
	m_nCnt = 0;
}
void CTutorialInoperableState::Update(void)
{
	// ���b�V���擾
	CMesh* pMesh = CTutorial::GetCMesh();
	// �v���C���[���擾
	D3DXVECTOR3 pos = m_pPlayer->GetPos();
	D3DXVECTOR3 rot = m_pPlayer->GetRot();
	// �J�������擾
	CCamera* pCamera = CManager::GetCCamera();


	// ���b�V���̍���
	pos.y = pMesh->GetHeight(pos);
	// �J�����ʒu
	pCamera->Target(pos, rot);
	// �ʒu�𔽉f
	m_pPlayer->SetPos(pos);

	m_pPlayer->Decay();
	m_nCnt++;
	if (m_nCnt > Cool)
	{
		m_pPlayer->SetState(CTutorialPlayer::STATE_NONE);
		CTutorialRandState* pRandState = new CTutorialRandState;
		m_pPlayer->ChangeState(pRandState);
		return;
	}
}
void CTutorialInoperableState::Uninit(void)
{

}
