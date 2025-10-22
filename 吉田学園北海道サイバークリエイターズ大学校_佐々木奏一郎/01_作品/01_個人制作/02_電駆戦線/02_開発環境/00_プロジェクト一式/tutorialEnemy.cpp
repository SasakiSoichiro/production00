//*****************************************
//
// �G�l�~�[���� [enemy.cpp]
// Author:Sasaki Soichiro
//
//*****************************************

//*******************
// �C���N���[�h
//*******************
#include "tutorialEnemy.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "texture.h"
#include "camera.h"
#include "object3D.h"
#include "enemychild.h"
#include "tutorial.h"
#include "score.h"
#include "combo.h"
#include "mesh.h"
#include "enemyLifeManager.h"
#include "tutorialPlayer.h"
#include "sound.h"

//*******************
// �}�N����`
//*******************
#define SPEED (8.0f)	// �v���C���[�̈ړ����x
#define NUMMODEL (15)	// ���f���̃p�[�c��
#define DEST (0.3f)

//*****************
// �ÓI�����o�ϐ�
//*****************
int CTutorialEnemy::m_nNumAll = 0;

//*****************
// �R���X�g���N�^
//*****************
CTutorialEnemy::CTutorialEnemy(int nPriority) :CObject(nPriority)
{
	// �ϐ��̃N���A
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_oldPos = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nLife = 0;
	m_fAngle = 0.0f;
	m_nIdxXFile = -1;
	m_nLife = 0;
	m_pMotion = NULL;
	for (int nCnt = 0; nCnt < NUMMODEL; nCnt++)
	{
		m_apModel[nCnt] = NULL;
	}
	m_nNumModel = 0;
	m_nNumAll++;
	m_pLifeManager = NULL;
}

//*****************
// �f�X�g���N�^
//*****************
CTutorialEnemy::~CTutorialEnemy()
{
	m_nNumAll--;
}

//******************
// �C���X�^���X����
//*******************
CTutorialEnemy* CTutorialEnemy::Create(D3DXVECTOR3 pos)
{
	CTutorialEnemy* pEnemy = NULL;// �G�̃|�C���^
	// �e�N�X�`�����̎擾
	CTexture* pTexture = CManager::GetCTexture();
	// ���݂̃I�u�W�F�N�g�̑����擾
	int nNum = CObject::GetNumAll();
	if (nNum < MAX_OBJ - 1)
	{// �I�u�W�F�N�g���ő吔�ɒB���Ă��Ȃ��ꍇ

		pEnemy = new CTutorialEnemy;	// �C���X�^���X����

		pEnemy->Init(pos);		// ������

		// ����n��
		return pEnemy;
	}

	return NULL;
}

//*****************
// ����������
//*****************
HRESULT CTutorialEnemy::Init(D3DXVECTOR3 pos)
{
	CTutorialEnemy::LoadMotion("data\\MOTION\\fanmotor.txt");
	m_pos = pos;							// �ʒu�����ݒ�
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ���������ݒ�
	m_nLife = initLife;						// ���C�t�����ݒ�
	m_pLifeManager = CEnemyLifeManager::Create(pos, initLife);

	// ����������
	return S_OK;
}

//***********
// �I������
//***********
void CTutorialEnemy::Uninit(void)
{
	m_pMotion->Uninit();
	delete m_pMotion;
	m_pMotion = NULL;
	for (int nCnt = 0; nCnt < m_nNumModel; nCnt++)
	{
		m_apModel[nCnt]->Uninit();
		delete m_apModel[nCnt];
		m_apModel[nCnt] = NULL;
	}

	CObject::Release();
}

//*****************
// �X�V����
//*****************
void CTutorialEnemy::Update(void)
{
	D3DXVECTOR3 pos = m_pos;// ���݂̈ʒu����
	// �O�t���[���̈ʒu���ۑ�
	m_oldPos = m_pos;

	// ���b�V�����̎擾
	CMesh* pMesh = CTutorial::GetCMesh();
	// �������̎擾
	pos.y = pMesh->GetHeight(pos);
	SetMotion(1);
	// �ʒu��ݒ�
	SetPos(pos);
	CTutorialPlayer* pPlayer = CTutorial::GetCPlayer();
	CSound* pSound = CManager::GetCSound();
	D3DXVECTOR3 playerPos = pPlayer->GetPos();

	// �����蔻��v�Z
	float DistX, DistY, DistZ;
	// ���̋���
	DistX = playerPos.x - pos.x;
	DistY = playerPos.y - pos.y;
	DistZ = playerPos.z - pos.z;
	float Dist = sqrtf((DistX * DistX) + (DistY * DistY) + (DistZ * DistZ));

	m_nHitCool++;
	// �q�b�g�̏���
	bool bHit = Dist < Range
		&& pPlayer->GetState() != CTutorialPlayer::STATE_RAIL
		&& m_nHitCool>hitCool;

	if (bHit)
	{// �q�b�g������

		if (pPlayer->GetState() == CTutorialPlayer::STATE_NONE)
		{
			pSound->Play(CSound::LABEL_SE02);
			pPlayer->SetMove(D3DXVECTOR3(DistX * 0.05f, 0.0f, DistZ * 0.05f));
			// �v���C���[�̏�Ԃ�ύX
			pPlayer->SetState(CTutorialPlayer::STATE_INOPERABLE);
			CTutorialInoperableState* pInoperableState = new CTutorialInoperableState;
			pPlayer->ChangeState(pInoperableState);

		}

		m_nHitCool = 0;
		m_nLife--;
	}

	pos.y += 90.0f;
	m_pLifeManager->SetPos(pos);
	m_pLifeManager->SetLife(m_nLife);

	if (m_nLife <= 0)
	{
		m_pLifeManager->Uninit();
		Uninit();
	}
}

//*****************
// �`�揈��
//*****************
void CTutorialEnemy::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	CRenderer* renderer = CManager::GetCRenderer();
	pDevice = renderer->GetDevice();

	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;
	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);
	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

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
void CTutorialEnemy::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}
//******************
// �����̐ݒ�
//*******************
void CTutorialEnemy::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

void CTutorialEnemy::LoadMotion(const char* pMotionScript)
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
											m_apModel[nCntParts]->SetOffSetRot(rot);
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
							m_pMotion = CMotion::Create(&m_apModel[0], m_nNumModel, true);
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

void CTutorialEnemy::EnemyUpdate(void)
{
	if (m_nNumAll <= 0)
	{
		CTutorialEnemy::Create(D3DXVECTOR3(0.2f, 0.2f, 0.2f));
	}
}