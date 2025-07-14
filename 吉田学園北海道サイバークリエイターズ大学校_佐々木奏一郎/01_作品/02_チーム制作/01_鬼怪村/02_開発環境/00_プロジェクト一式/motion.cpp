//=============================================================================
//
//	���[�V�������� [motion.h]
// Author : SasakiSoichiro
//
//=============================================================================

#include "motion.h"
#include "input.h"
#include "camera.h"
#include "player.h"

//=============================================================================
//����������
//=============================================================================
void ReadScript(int nType)
{
	FILE* pFile=NULL;
	switch (nType)
	{
	case 1:
		pFile = fopen("data\\MOTION\\motion05.txt", "r");
		break;
	case 2:
		pFile = fopen("data\\MOTION\\motion06.txt", "r");
		break;
	}


	Player* pPlayer = GetPlayer();
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();
	int nCntModel = 0, nCntParts = 0, nIdx = 0, nParents = 0, nCntKey = 0, nCntMotion = 0;
	int nBool;
	char str[MAX_WORD];
	char FileName[30][MAX_WORD];
	D3DXVECTOR3 pos, rot;


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
						fscanf(pFile, "%d", &pPlayer->motion.nNumModel);
						while (nCntModel < pPlayer->motion.nNumModel)
						{
							//�t�@�C����ǂݍ���
							fscanf(pFile, "%s", &aString[0]);

							if (strcmp(aString, "MODEL_FILENAME") == 0)
							{
								fscanf(pFile, "%s", &str[0]);
								fscanf(pFile, "%s", &FileName[nCntModel][0]);

								//x�t�@�C���̓ǂݍ���
								D3DXLoadMeshFromX(FileName[nCntModel],
									D3DXMESH_SYSTEMMEM,
									pDevice,
									NULL,
									&pPlayer->motion.aModel[nCntModel].pBuffMat,
									NULL,
									&pPlayer->motion.aModel[nCntModel].dwNumMat,
									&pPlayer->motion.aModel[nCntModel].pMesh);

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
								fscanf(pFile, "%d", &pPlayer->motion.nNumModel);

							}
							while (nCntParts < pPlayer->motion.nNumModel)
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
											fscanf(pFile, "%d", &pPlayer->motion.aModel[nIdx].nIdxModelParent);

										}
										else if (strcmp(aString, "POS") == 0)
										{
											fscanf(pFile, "%s", &str[0]);
											fscanf(pFile, "%f", &pPlayer->motion.aModel[nIdx].pos.x);
											fscanf(pFile, "%f", &pPlayer->motion.aModel[nIdx].pos.y);
											fscanf(pFile, "%f", &pPlayer->motion.aModel[nIdx].pos.z);
										}
										else if (strcmp(aString, "ROT") == 0)
										{
											fscanf(pFile, "%s", &str[0]);
											fscanf(pFile, "%f", &pPlayer->motion.aModel[nIdx].rot.x);
											fscanf(pFile, "%f", &pPlayer->motion.aModel[nIdx].rot.y);
											fscanf(pFile, "%f", &pPlayer->motion.aModel[nIdx].rot.z);

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
									pPlayer->motion.aMotionInfo[nCntMotion].bLoop = false;
								}
								else
								{
									pPlayer->motion.aMotionInfo[nCntMotion].bLoop = true;
								}
							}

							if (strcmp(aString, "NUM_KEY") == 0)
							{
								fscanf(pFile, "%s", &str[0]);
								fscanf(pFile, "%d", &pPlayer->motion.aMotionInfo[nCntMotion].nNumKey);

								while (nCntKey < pPlayer->motion.aMotionInfo[nCntMotion].nNumKey)
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
												fscanf(pFile, "%d", &pPlayer->motion.aMotionInfo[nCntMotion].aKeyInfo[nCntKey].nFlame);
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
														fscanf(pFile, "%f", &pPlayer->motion.aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntParts].fPosX);
														fscanf(pFile, "%f", &pPlayer->motion.aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntParts].fPosY);
														fscanf(pFile, "%f", &pPlayer->motion.aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntParts].fPosZ);
													}
													if (strcmp(aString, "ROT") == 0)
													{
														fscanf(pFile, "%s", &str[0]);
														fscanf(pFile, "%f", &pPlayer->motion.aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntParts].fRotX);
														fscanf(pFile, "%f", &pPlayer->motion.aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntParts].fRotY);
														fscanf(pFile, "%f", &pPlayer->motion.aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntParts].fRotZ);
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

}
void ReadModel(void)
{

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateMotion(void)
{

	Player* pPlayer = GetPlayer();
	//Slow* pSlow = GetSlow();

	pPlayer->motion.nNumKey = pPlayer->motion.aMotionInfo[pPlayer->motion.motionType].nNumKey;
	if (pPlayer->motion.motionType != pPlayer->motion.motionTypeOld)
	{
		pPlayer->motion.nKey = 0;
		pPlayer->motion.nCntMotion = 0;
	}

	//�S���f��(�p�[�c)�̍X�V
	for (int nCntModel = 0; nCntModel < pPlayer->motion.nNumModel; nCntModel++)
	{
		KEY k_Answer;

		//�L�[��񂩂�ʒu.�������Z�o
		k_Answer.fPosX = (pPlayer->motion.aMotionInfo[pPlayer->motion.motionType].aKeyInfo[(pPlayer->motion.nKey + 1) % pPlayer->motion.nNumKey].aKey[nCntModel].fPosX) - (pPlayer->motion.aMotionInfo[pPlayer->motion.motionType].aKeyInfo[pPlayer->motion.nKey].aKey[nCntModel].fPosX);
		k_Answer.fPosY = (pPlayer->motion.aMotionInfo[pPlayer->motion.motionType].aKeyInfo[(pPlayer->motion.nKey + 1) % pPlayer->motion.nNumKey].aKey[nCntModel].fPosY) - (pPlayer->motion.aMotionInfo[pPlayer->motion.motionType].aKeyInfo[pPlayer->motion.nKey].aKey[nCntModel].fPosY);
		k_Answer.fPosZ = (pPlayer->motion.aMotionInfo[pPlayer->motion.motionType].aKeyInfo[(pPlayer->motion.nKey + 1) % pPlayer->motion.nNumKey].aKey[nCntModel].fPosZ) - (pPlayer->motion.aMotionInfo[pPlayer->motion.motionType].aKeyInfo[pPlayer->motion.nKey].aKey[nCntModel].fPosZ);
		k_Answer.fRotX = (pPlayer->motion.aMotionInfo[pPlayer->motion.motionType].aKeyInfo[(pPlayer->motion.nKey + 1) % pPlayer->motion.nNumKey].aKey[nCntModel].fRotX) - (pPlayer->motion.aMotionInfo[pPlayer->motion.motionType].aKeyInfo[pPlayer->motion.nKey].aKey[nCntModel].fRotX);
		k_Answer.fRotY = (pPlayer->motion.aMotionInfo[pPlayer->motion.motionType].aKeyInfo[(pPlayer->motion.nKey + 1) % pPlayer->motion.nNumKey].aKey[nCntModel].fRotY) - (pPlayer->motion.aMotionInfo[pPlayer->motion.motionType].aKeyInfo[pPlayer->motion.nKey].aKey[nCntModel].fRotY);
		k_Answer.fRotZ = (pPlayer->motion.aMotionInfo[pPlayer->motion.motionType].aKeyInfo[(pPlayer->motion.nKey + 1) % pPlayer->motion.nNumKey].aKey[nCntModel].fRotZ) - (pPlayer->motion.aMotionInfo[pPlayer->motion.motionType].aKeyInfo[pPlayer->motion.nKey].aKey[nCntModel].fRotZ);

		//�p�[�c�̈ʒu.������ݒ�
		//�ʒu
		pPlayer->motion.aModel[nCntModel].pos.x = pPlayer->motion.aModel[nCntModel].posFirst.x + pPlayer->motion.aMotionInfo[pPlayer->motion.motionType].aKeyInfo[pPlayer->motion.nKey].aKey[nCntModel].fPosX + k_Answer.fPosX * (pPlayer->motion.nCntMotion / (float)pPlayer->motion.aMotionInfo[pPlayer->motion.motionType].aKeyInfo[pPlayer->motion.nKey].nFlame);
		pPlayer->motion.aModel[nCntModel].pos.y = pPlayer->motion.aModel[nCntModel].posFirst.y + pPlayer->motion.aMotionInfo[pPlayer->motion.motionType].aKeyInfo[pPlayer->motion.nKey].aKey[nCntModel].fPosY + k_Answer.fPosY * (pPlayer->motion.nCntMotion / (float)pPlayer->motion.aMotionInfo[pPlayer->motion.motionType].aKeyInfo[pPlayer->motion.nKey].nFlame);
		pPlayer->motion.aModel[nCntModel].pos.z = pPlayer->motion.aModel[nCntModel].posFirst.z + pPlayer->motion.aMotionInfo[pPlayer->motion.motionType].aKeyInfo[pPlayer->motion.nKey].aKey[nCntModel].fPosZ + k_Answer.fPosZ * (pPlayer->motion.nCntMotion / (float)pPlayer->motion.aMotionInfo[pPlayer->motion.motionType].aKeyInfo[pPlayer->motion.nKey].nFlame);

		//����
		pPlayer->motion.aModel[nCntModel].rot.x = pPlayer->motion.aModel[nCntModel].rotFirst.x + pPlayer->motion.aMotionInfo[pPlayer->motion.motionType].aKeyInfo[pPlayer->motion.nKey].aKey[nCntModel].fRotX + k_Answer.fRotX * (pPlayer->motion.nCntMotion / (float)pPlayer->motion.aMotionInfo[pPlayer->motion.motionType].aKeyInfo[pPlayer->motion.nKey].nFlame);//�I�t�Z�b�g�l��
		pPlayer->motion.aModel[nCntModel].rot.y = pPlayer->motion.aModel[nCntModel].rotFirst.y + pPlayer->motion.aMotionInfo[pPlayer->motion.motionType].aKeyInfo[pPlayer->motion.nKey].aKey[nCntModel].fRotY + k_Answer.fRotY * (pPlayer->motion.nCntMotion / (float)pPlayer->motion.aMotionInfo[pPlayer->motion.motionType].aKeyInfo[pPlayer->motion.nKey].nFlame);//�I�t�Z�b�g�l��
		pPlayer->motion.aModel[nCntModel].rot.z = pPlayer->motion.aModel[nCntModel].rotFirst.z + pPlayer->motion.aMotionInfo[pPlayer->motion.motionType].aKeyInfo[pPlayer->motion.nKey].aKey[nCntModel].fRotZ + k_Answer.fRotZ * (pPlayer->motion.nCntMotion / (float)pPlayer->motion.aMotionInfo[pPlayer->motion.motionType].aKeyInfo[pPlayer->motion.nKey].nFlame);//�I�t�Z�b�g�l��


	}

	if (pPlayer->motion.aMotionInfo[pPlayer->motion.motionType].bLoop == false && pPlayer->motion.nKey >= pPlayer->motion.nNumKey - 1)
	{
		pPlayer->motion.motionType = MOTIONTYPE_NEUTRAL;
	}

	if (pPlayer->motion.aMotionInfo[pPlayer->motion.motionType].bLoop == false)
	{
		if (pPlayer->motion.nKey + 1 != pPlayer->motion.nNumKey)
		{
			pPlayer->motion.nCntMotion++;//�Đ��t���[�����ɒB�����猻�݂̃L�[��1�i�߂�
		}
	}


	else
	{
		pPlayer->motion.nCntMotion++;//�Đ��t���[�����ɒB�����猻�݂̃L�[��1�i�߂�
	}



	if (pPlayer->motion.nCntMotion >= pPlayer->motion.aMotionInfo[pPlayer->motion.motionType].aKeyInfo[pPlayer->motion.nKey].nFlame)
	{
		pPlayer->motion.nCntMotion = 0;

		pPlayer->motion.nKey += 1;
		if (pPlayer->motion.nKey >= pPlayer->motion.nNumKey)
		{
			pPlayer->motion.nKey = 0;
		}
	}

}