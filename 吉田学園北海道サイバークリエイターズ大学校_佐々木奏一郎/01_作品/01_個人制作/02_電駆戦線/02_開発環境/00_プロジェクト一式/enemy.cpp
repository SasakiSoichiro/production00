//*****************************************
//
// �G�l�~�[���� [enemy.cpp]
// Author:Sasaki Soichiro
//
//*****************************************

//*******************
// �C���N���[�h
//*******************
#include "enemy.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "texture.h"
#include "camera.h"
#include "object3D.h"
#include "enemychild.h"
#include "game.h"
#include "score.h"
#include "combo.h"
#include "mesh.h"
#include "enemyLifeManager.h"

//*******************
// �}�N����`
//*******************
#define SPEED (8.0f)	// �v���C���[�̈ړ����x
#define NUMMODEL (15)	// ���f���̃p�[�c��
#define DEST (0.3f)

//*****************
// �ÓI�����o�ϐ�
//*****************
int CEnemy::m_nNumAll = 0;

//*****************
// �R���X�g���N�^
//*****************
CEnemy::CEnemy(int nPriority) :CObject(nPriority)
{
	// �ϐ��̃N���A
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_oldPos = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vecF = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	m_vecR = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_speed = 0;
	m_nLife = 0;
	m_fAngle = 0.0f;
	m_nIdxXFile = -1;
	m_nLife = 0;
	m_State = STATE_NONE;
	m_pMotion = NULL;
	for (int nCnt = 0; nCnt < NUMMODEL; nCnt++)
	{
		m_apModel[nCnt] = NULL;
	}
	m_nNumModel = 0;
	m_Machine = NULL;
	m_nNumAll++;
	m_nType = 0;
	m_pLifeManager = NULL;
}

//*****************
// �f�X�g���N�^
//*****************
CEnemy::~CEnemy()
{
	m_nNumAll--;
}

//******************
// �C���X�^���X����
//*******************
CEnemy* CEnemy::Create(D3DXVECTOR3 pos,int nType)
{
	// ���g�̃|�C���^
	CEnemy* pEnemy = NULL;
	// �e�N�X�`�����̎擾
	CTexture* pTexture = CManager::GetCTexture();
	// ���݂̃I�u�W�F�N�g�̑����擾
	int nNum = CObject::GetNumAll();
	if (nNum < MAX_OBJ - 1)
	{// �I�u�W�F�N�g���ő吔�ɒB���Ă��Ȃ��ꍇ

		switch (nType)
		{// �C���X�^���X����
		case TYPE_SPIDER:
			pEnemy = new CSpiderEnemy;	
			pEnemy->m_nType = TYPE_SPIDER;
			break;
		case TYPE_FANMOTOR:
			pEnemy = new CFanmotorEnemy;
			pEnemy->m_nType = TYPE_FANMOTOR;
			break;
		}
		
		// ������
		pEnemy->Init(pos);		

		return pEnemy;
	}

	return NULL;
}

//*****************
// ����������
//*****************
HRESULT CEnemy::Init(D3DXVECTOR3 pos)
{
	// �����ݒ�
	m_pos = pos;							
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	
	m_speed = 0.0f;							
	m_nLife = initLife;	
	// �X�e�[�g�}�V������
	m_Machine = new CStateMachine;
	// ���C�t�}�l�[�W���[����
	m_pLifeManager = CEnemyLifeManager::Create(pos, initLife);
	// �j���[�g�������
	CNuetoralState* pNuetoralState = new CNuetoralState;
	ChangeState(pNuetoralState);

	return S_OK;
}

//***********
// �I������
//***********
void CEnemy::Uninit(void)
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
	m_Machine->Uninit();
	delete 	m_Machine;
	m_Machine = NULL;

	CObject::Release();
}

//*****************
// �X�V����
//*****************
void CEnemy::Update(void)
{
	D3DXVECTOR3 pos = m_pos;// ���݂̈ʒu����
	// �O�t���[���̈ʒu���ۑ�
	m_oldPos = m_pos;

	// ���b�V�����̎擾
	CMesh* pMesh = CGame::GetCMesh();
	// �������̎擾
	pos.y = pMesh->GetHeight(pos);
	// �ʒu��ݒ�
	SetPos(pos);
	pos.y += 90.0f;
	// ���[�V�����ƃX�e�[�g�}�V���̍X�V
	m_pMotion->Update();
	m_Machine->Update();

	// ���C�t�̐ݒ�
	m_pLifeManager->SetPos(pos);
	m_pLifeManager->SetLife(m_nLife);

	// �̗�0�ȉ��ŏI��
	if (m_nLife <= 0)
	{
		CCombo::Add(400);
		m_pLifeManager->Uninit();
		Uninit();
	}
}

//*****************
// �`�揈��
//*****************
void CEnemy::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	CRenderer* renderer = CManager::GetCRenderer();
	pDevice = renderer->GetDevice();

	if (m_nType == TYPE_SPIDER)
	{
		CMesh* pMesh = CGame::GetCMesh();

		// ���f���̏�x�N�g��
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
		D3DXMatrixRotationAxis(&rotMtx, &vecU, m_rot.y);

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
	else
	{
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
	}

	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// �S�Ẵ��f���̕`��
	for (int nCnt = 0; nCnt < m_nNumModel; nCnt++)
	{
		m_apModel[nCnt]->Draw();
	}


}

//******************
// �ʒu�̐ݒ�
//*******************
void CEnemy::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}
//******************
// �����̐ݒ�
//*******************
void CEnemy::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

bool CEnemy::Distance(float fDistance)
{
	// �v���C���[�̈ʒu�擾
	CPlayer* pPlayer = CGame::GetCPlayer();
	D3DXVECTOR3 playerPos = pPlayer->GetPos();
	// �ʒu�擾
	D3DXVECTOR3 pos = GetPos();

	// �v���C���[�Ƃ̋����v�Z
	float radX = playerPos.x - pos.x;
	float radY = playerPos.y - pos.y;
	float radZ = playerPos.z - pos.z;
	float fRadius = sqrtf((radX * radX) + (radY * radY) + (radZ * radZ));

	if (fDistance > fRadius)
	{// �͈͓�
		return true;
	}
	return false;
}

//**********************
// ���[�V�����̓ǂݍ���
//**********************
void CEnemy::LoadMotion(const char* pMotionScript)
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
							m_pMotion = CMotion::Create(&m_apModel[0], m_nNumModel,true);
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

//****************
// �X�e�[�g�̕ύX
//****************
void CEnemy::ChangeState(CEnemyStateBase* pState)
{
	pState->SetOwner(this);
	m_Machine->ChangeState(pState);
}