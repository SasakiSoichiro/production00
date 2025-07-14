//***************************************
// 
// ���b�V���t�B�[���h����[mesh.cpp]
// Author:Sasaki Soichiro
// 
//***************************************

//******************
// �C���N���[�h
//******************
#include "motion.h"

//*****************
// �}�N����`
//*****************
#define BLEND_FRAME (20)

//*****************
// �R���X�g���N�^
//*****************
CMotion::CMotion()
{
	for (int nCnt = 0; nCnt < PARTS_MAX; nCnt++)
	{
		m_apModel[nCnt]=NULL;
	}
	m_nNumModel=0;			
	for (int nCnt = 0; nCnt < 8; nCnt++)
	{
		m_aInfo[nCnt] = {};
	}
	m_nNum=0;
	m_type=0;
	m_typeBlend = 0;
	m_bLoop=false;
	m_nNumKey=0;
	m_nKey=0;
	m_nCnt=0;
	m_nCntBlend = 0;
	m_bBlend = false;
	m_bFinish = false;
	m_nFrameBlend = 0;
	m_nKeyBlend = 0;
	m_nNumKeyBlend = 0;
	m_nCntMotionBlend = 0;
}

//*****************
// �f�X�g���N�^
//*****************
CMotion::~CMotion()
{
}

//*******************
// �C���X�^���X����
//*******************
CMotion*CMotion::Create(const char*pMotionScript)
{
	CMotion* pMotion;
	pMotion = new CMotion;
	pMotion->Init();
	pMotion->ReadScript(pMotionScript);
	return pMotion;
}

//*******************
// ����������
//*******************
HRESULT CMotion::Init(void)
{

	return S_OK;
}

//*******************
// �I������
//*******************
void CMotion::Uninit(void)
{
	for (int nCnt = 0; nCnt < 20; nCnt++)
	{
		if (m_apModel[nCnt] != NULL)
		{
			m_apModel[nCnt]->Uninit();
			delete m_apModel[nCnt];
			m_apModel[nCnt] = NULL;
		}
	}
}

//*******************
// �X�V����
//*******************
void CMotion::Update(void)
{
	//�����i�[�p
	KEY k_Answer = {};
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

	//m_nNumKey = m_aInfo[m_type].nNumKey;
	////m_typeOld = m_type;
	D3DXVECTOR3 ModelPos, ModelRot;
	//if (m_type != m_typeOld)
	//{
	//	m_nKey = 0;
	//	m_nCnt = 0;
	//}

	////�S���f��(�p�[�c)�̍X�V
	//for (int nCntModel = 0; nCntModel < m_nNumModel; nCntModel++)
	//{
	//	KEY k_Answer;

	//	//�L�[��񂩂�ʒu.�������Z�o
	//	k_Answer.fPosX = (m_aInfo[m_type].aKeyInfo[(m_nKey + 1) % m_nNumKey].aKey[nCntModel].fPosX) - (m_aInfo[m_type].aKeyInfo[m_nKey].aKey[nCntModel].fPosX);
	//	k_Answer.fPosY = (m_aInfo[m_type].aKeyInfo[(m_nKey + 1) % m_nNumKey].aKey[nCntModel].fPosY) - (m_aInfo[m_type].aKeyInfo[m_nKey].aKey[nCntModel].fPosY);
	//	k_Answer.fPosZ = (m_aInfo[m_type].aKeyInfo[(m_nKey + 1) % m_nNumKey].aKey[nCntModel].fPosZ) - (m_aInfo[m_type].aKeyInfo[m_nKey].aKey[nCntModel].fPosZ);
	//	k_Answer.fRotX = (m_aInfo[m_type].aKeyInfo[(m_nKey + 1) % m_nNumKey].aKey[nCntModel].fRotX) - (m_aInfo[m_type].aKeyInfo[m_nKey].aKey[nCntModel].fRotX);
	//	k_Answer.fRotY = (m_aInfo[m_type].aKeyInfo[(m_nKey + 1) % m_nNumKey].aKey[nCntModel].fRotY) - (m_aInfo[m_type].aKeyInfo[m_nKey].aKey[nCntModel].fRotY);
	//	k_Answer.fRotZ = (m_aInfo[m_type].aKeyInfo[(m_nKey + 1) % m_nNumKey].aKey[nCntModel].fRotZ) - (m_aInfo[m_type].aKeyInfo[m_nKey].aKey[nCntModel].fRotZ);

	//	//�p�[�c�̈ʒu.������ݒ�
	//	//�ʒu
	//	//ModelPos.x = m_aInfo[m_type].aKeyInfo[m_nKey].aKey[nCntModel].fPosX + k_Answer.fPosX * (m_nCnt / (float)m_aInfo[m_type].aKeyInfo[m_nKey].nFlame);
	//	//ModelPos.y = m_aInfo[m_type].aKeyInfo[m_nKey].aKey[nCntModel].fPosY + k_Answer.fPosY * (m_nCnt / (float)m_aInfo[m_type].aKeyInfo[m_nKey].nFlame);
	//	//ModelPos.z = m_aInfo[m_type].aKeyInfo[m_nKey].aKey[nCntModel].fPosZ + k_Answer.fPosZ * (m_nCnt / (float)m_aInfo[m_type].aKeyInfo[m_nKey].nFlame);
	//	//m_apModel[nCntModel]->SetPos(ModelPos);
	//	//����
	//	ModelRot.x = m_aInfo[m_type].aKeyInfo[m_nKey].aKey[nCntModel].fRotX + k_Answer.fRotX * (m_nCnt / (float)m_aInfo[m_type].aKeyInfo[m_nKey].nFlame);//�I�t�Z�b�g�l��
	//	ModelRot.y = m_aInfo[m_type].aKeyInfo[m_nKey].aKey[nCntModel].fRotY + k_Answer.fRotY * (m_nCnt / (float)m_aInfo[m_type].aKeyInfo[m_nKey].nFlame);//�I�t�Z�b�g�l��
	//	ModelRot.z = m_aInfo[m_type].aKeyInfo[m_nKey].aKey[nCntModel].fRotZ + k_Answer.fRotZ * (m_nCnt / (float)m_aInfo[m_type].aKeyInfo[m_nKey].nFlame);//�I�t�Z�b�g�l��
	//	m_apModel[nCntModel]->SetRot(ModelRot);
	//}

	//if (m_aInfo[m_type].bLoop == false && m_nKey >= m_nNumKey - 1)
	//{
	//	m_type = TYPE_NEUTRAL;
	//}

	//if (m_aInfo[m_type].bLoop == false)
	//{
	//	if (m_nKey + 1 != m_nNumKey)
	//	{
	//		m_nCnt++;//�Đ��t���[�����ɒB�����猻�݂̃L�[��1�i�߂�
	//	}
	//}
	//else
	//{
	//	m_nCnt++;//�Đ��t���[�����ɒB�����猻�݂̃L�[��1�i�߂�
	//}

	//if (m_nCnt >= m_aInfo[m_type].aKeyInfo[m_nKey].nFlame)
	//{
	//	m_nCnt = 0;

	//	m_nKey += 1;
	//	if (m_nKey >= m_nNumKey)
	//	{
	//		m_nKey = 0;
	//	}
	//}
	m_nNumKey = m_aInfo[m_type].nNumKey;
	m_nNumKeyBlend = m_aInfo[m_typeBlend].nNumKey;


	//�S���f��(�p�[�c)�̍X�V
	for (int nCntModel = 0; nCntModel < m_nNumModel; nCntModel++)
	{
		//���݂̃L�[�����(�|�C���g
		KEY pKey = m_aInfo[m_type].aKeyInfo[m_nKey].aKey[nCntModel];
		//���̃L�[�����(�|�C���g
		KEY pKeyNext = m_aInfo[m_type].aKeyInfo[(m_nKey + 1) % m_nNumKey].aKey[nCntModel];

		//���Βl
		float fRateMotion = m_nCnt / ((float)m_aInfo[m_type].aKeyInfo[m_nKey].nFlame);

		//�u�����h����t���[��
		m_nFrameBlend = BLEND_FRAME;


		//�u�����h���[�V��������
		if (m_bBlend == true)
		{//bBlend��true��������


			//==========
			// �ϐ��錾
			//==========

			// �u�����h��̏�����
			// ���݂̃L�[�����(�|�C���g
			KEY pKeyBlend = m_aInfo[m_typeBlend].aKeyInfo[m_nKeyBlend].aKey[nCntModel];								// ���݂̃L�[

			// ���̃L�[�����(�|�C���g
			KEY pKeyNextBlend = m_aInfo[m_typeBlend].aKeyInfo[(m_nKeyBlend + 1) % m_nNumKeyBlend].aKey[nCntModel];	// ���̃L�[

			// ���Βl
			float fRateMotionBlend = m_nCntMotionBlend / ((float)m_aInfo[m_typeBlend].aKeyInfo[m_nKeyBlend].nFlame);

			// �u�����h�̑��Βl
			float fRateBlend = m_nCntBlend / ((float)m_nFrameBlend);



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

			// �L�[��񂩂�ʒu.�������Z�o
			// ���̃L�[�Ƃ̍���
			k_Answer.fPosX = (m_aInfo[m_type].aKeyInfo[(m_nKey + 1) % m_nNumKey].aKey[nCntModel].fPosX) - (m_aInfo[m_type].aKeyInfo[m_nKey].aKey[nCntModel].fPosX);
			k_Answer.fPosY = (m_aInfo[m_type].aKeyInfo[(m_nKey + 1) % m_nNumKey].aKey[nCntModel].fPosY) - (m_aInfo[m_type].aKeyInfo[m_nKey].aKey[nCntModel].fPosY);
			k_Answer.fPosZ = (m_aInfo[m_type].aKeyInfo[(m_nKey + 1) % m_nNumKey].aKey[nCntModel].fPosZ) - (m_aInfo[m_type].aKeyInfo[m_nKey].aKey[nCntModel].fPosZ);
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
		ModelRot.x =fRotX;//�I�t�Z�b�g�l��
		ModelRot.y =fRotY;//�I�t�Z�b�g�l��
		ModelRot.z =fRotZ;//�I�t�Z�b�g�l��
		m_apModel[nCntModel]->SetRot(ModelRot);
	}


	if (m_bBlend == true)
	{//�u�����h����
		if (m_aInfo[m_typeBlend].bLoop == false)
		{//���[�v���[�V��������Ȃ��ꍇ

			if (m_nKeyBlend + 1 != m_nNumKeyBlend)
			{//�L�[�����ɒB���Ă��Ȃ��ꍇ

				m_nCntMotionBlend += 1;//�Đ��t���[�����ɒB�����猻�݂̃L�[��1�i�߂�

			}
			else
			{
				SetMotion(0);
			}
		}

		else
		{//���[�v���[�V�����̏ꍇ

			m_nCntMotionBlend += 1;//�J�E���g���[�V������1�i�߂�

		}

		if (m_nCntMotionBlend >= (m_aInfo[m_typeBlend].aKeyInfo[m_nKeyBlend].nFlame))
		{//�t���[�����𒴂�����

			//�J�E���g���[�V������0�ɂ���
			m_nCntMotionBlend = 0;

			//���݂̃L�[��1�i�߂�
			m_nKeyBlend += 1;

			if (m_nKeyBlend >= m_nNumKeyBlend)
			{//�L�[�����ɒB������

				//���݂̃L�[��0�ɂ���
				m_nKeyBlend = 0;
			}
		}

		//�u�����h�J�E���g��1�i�߂�
		m_nCntBlend++;


		if (m_nCntBlend >= m_nFrameBlend)
		{//�u�����h�̃t���[�����ɒB������

			//���������ʏ탂�[�V�����ɏ�����
			m_nCnt = m_nCntMotionBlend;
			m_nCntBlend = 0;
			m_type = m_typeBlend;
			m_nKey = m_nKeyBlend;
			m_bBlend = false;

		}

		if (m_aInfo[m_type].nNumKey - 1 <= m_nKey && m_aInfo[m_type].bLoop == false)
		{
			//m_typeBlend = TYPE_NEUTRAL;
			//m_bBlend = true;
			//m_nKeyBlend = 0;
			//m_nCntMotionBlend = 0;
			SetMotion(0);
		}
	}


	else
	{//�u�����h�Ȃ�

		if (m_aInfo[m_type].bLoop == false)
		{//���[�v���[�V��������Ȃ��ꍇ

			if (m_nKey + 1 != m_nNumKey)
			{//�L�[�����ɒB���Ă��Ȃ��ꍇ

				m_nCnt++;// ���[�V�����J�E���g��1�i�߂�

			}
			else
			{
				SetMotion(0);
			}
		}


		else
		{//���[�v���[�V�����̏ꍇ

			m_nCnt++;//���[�V�����J�E���g��1�i�߂�
		}



		if (m_nCnt >= (m_aInfo[m_type].aKeyInfo[m_nKey].nFlame))
		{//�t���[�����𒴂�����

			//�J�E���g���[�V������0�ɂ���
			m_nCnt = 0;

			//���݂̃L�[��1�i�߂�
			m_nKey += 1;

			if (m_nKey >= m_nNumKey)
			{//�L�[�����ɒB������

				//���݂̃L�[��0�ɂ���
				m_nKey = 0;

			}
		}
	}
}

//*******************
// �`�揈��
//*******************
void CMotion::Draw(void)
{
	// �S�Ẵ��f���̕`��
	for (int nCnt = 0; nCnt < m_nNumModel; nCnt++)
	{
		// ���f���̕`��
		m_apModel[nCnt]->Draw();
	}
}

//*******************
// ���[�V�����̐ݒ�
//*******************
void CMotion::SetMotion(int type)
{
	if (m_type != type)
	{// ���݂̃��[�V�����Ƃ������Ă����Ƃ�
		m_typeBlend = type;		// ���݂̃��[�V�����ɐݒ�
		m_bBlend = true;		// �u�����h����ɐݒ�
		m_nKeyBlend = 0;		// �L�[���Z�b�g
		m_nCntMotionBlend = 0;	// �J�E���g���[�V�������Z�b�g
	}
}

//******************************
// ���[�V�����t�@�C���̓ǂݍ���
//******************************
void CMotion::ReadScript(const char* pMotionScript)
{
	FILE* pFile = NULL;
	pFile = fopen(pMotionScript, "r");

	int nCntModel = 0, nCntParts = 0, nIdx = 0, nParents = 0, nCntKey = 0, nCntMotion = 0;
	int nBool;
	int nParent;
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
									m_aInfo[nCntMotion].bLoop = false;
								}
								else
								{
									m_aInfo[nCntMotion].bLoop = true;
								}
							}

							if (strcmp(aString, "NUM_KEY") == 0)
							{
								fscanf(pFile, "%s", &str[0]);
								fscanf(pFile, "%d", &m_aInfo[nCntMotion].nNumKey);

								while (nCntKey < m_aInfo[nCntMotion].nNumKey)
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
												fscanf(pFile, "%d", &m_aInfo[nCntMotion].aKeyInfo[nCntKey].nFlame);
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
														fscanf(pFile, "%f", &m_aInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntParts].fPosX);
														fscanf(pFile, "%f", &m_aInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntParts].fPosY);
														fscanf(pFile, "%f", &m_aInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntParts].fPosZ);
													}
													if (strcmp(aString, "ROT") == 0)
													{
														fscanf(pFile, "%s", &str[0]);
														fscanf(pFile, "%f", &m_aInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntParts].fRotX);
														fscanf(pFile, "%f", &m_aInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntParts].fRotY);
														fscanf(pFile, "%f", &m_aInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntParts].fRotZ);
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