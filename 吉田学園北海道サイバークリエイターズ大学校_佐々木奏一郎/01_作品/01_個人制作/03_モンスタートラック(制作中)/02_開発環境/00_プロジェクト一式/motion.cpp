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
#include "game.h"

//*****************
// �}�N����`
//*****************
#define BLEND_FRAME (20)

//*****************
// �R���X�g���N�^
//*****************
CMotion::CMotion()
{
	m_ppModel=NULL;
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
	m_bSlow = false;
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
CMotion* CMotion::Create(CModel** ppModel, int nNumModel,bool bSlow)
{
	CMotion* pMotion;
	pMotion = new CMotion;
	pMotion->m_ppModel = ppModel;
	pMotion->m_nNumModel = nNumModel;
	pMotion->m_bSlow = bSlow;
	pMotion->Init();
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
}

//*******************
// �X�V����
//*******************
void CMotion::Update(void)
{
	//�����i�[�p
	KEY k_Answer = {};
	float fPosX = 0.0f;
	float fPosY = 0.0f;
	float fPosZ = 0.0f;
	float fRotX = 0.0f;
	float fRotY = 0.0f;
	float fRotZ = 0.0f;


	//�v�Z�p
	float fDiffMotionPosX;
	float fDiffMotionPosY;
	float fDiffMotionPosZ;
	float fDiffMotionRotX;
	float fDiffMotionRotY;
	float fDiffMotionRotZ;

	float fPosXCurrent;
	float fPosYCurrent;
	float fPosZCurrent;
	float fRotXCurrent;
	float fRotYCurrent;
	float fRotZCurrent;

	float DiffMotionBlendPosX;
	float DiffMotionBlendPosY;
	float DiffMotionBlendPosZ;
	float DiffMotionBlendRotX;
	float DiffMotionBlendRotY;
	float DiffMotionBlendRotZ;

	float fPosXBlend;
	float fPosYBlend;
	float fPosZBlend;
	float fRotXBlend;
	float fRotYBlend;
	float fRotZBlend;

	float fDiffBlendPosX;
	float fDiffBlendPosY;
	float fDiffBlendPosZ;
	float fDiffBlendRotX;
	float fDiffBlendRotY;
	float fDiffBlendRotZ;

	D3DXVECTOR3 ModelPos, ModelRot;
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


			// X���̈ړ�
			//=============================================================================================
			fDiffMotionPosX = pKeyNext.fPosX - pKey.fPosX;							// ���̃L�[�Ƃ̍���
			fPosXCurrent = pKey.fPosX + (fDiffMotionPosX * fRateMotion);
			DiffMotionBlendPosX = pKeyNextBlend.fPosX - pKeyBlend.fPosX;
			fPosXBlend = pKeyBlend.fPosX + (DiffMotionBlendPosX * fRateMotionBlend);
			fDiffBlendPosX = fPosXBlend - fPosXCurrent;								// ����
			fPosX = fPosXCurrent + (fDiffBlendPosX * fRateBlend);					// ���߂�l
			// X���̉�]
			//=============================================================================================
			fDiffMotionRotX = Normalize(pKeyNext.fRotX, pKey.fRotX);				// ���̃L�[�Ƃ̍���
			fRotXCurrent = pKey.fRotX + (fDiffMotionRotX * fRateMotion);
			DiffMotionBlendRotX = pKeyNextBlend.fRotX - pKeyBlend.fRotX;
			fRotXBlend = pKeyBlend.fRotX + (DiffMotionBlendRotX * fRateMotionBlend);
			fDiffBlendRotX = fRotXBlend - fRotXCurrent;								// ����
			fRotX = fRotXCurrent + (fDiffBlendRotX * fRateBlend);					// ���߂�l
			//=============================================================================================

			// Y���̈ړ�
			//=============================================================================================
			fDiffMotionPosY = pKeyNext.fPosY - pKey.fPosY;							// ���̃L�[�Ƃ̍���
			fPosYCurrent = pKey.fPosY + (fDiffMotionPosY * fRateMotion);
			DiffMotionBlendPosY = pKeyNextBlend.fPosY - pKeyBlend.fPosY;
			fPosYBlend = pKeyBlend.fPosY + (DiffMotionBlendPosY * fRateMotionBlend);
			fDiffBlendPosY = fPosYBlend - fPosYCurrent;								// ����
			fPosY = fPosYCurrent + (fDiffBlendPosY * fRateBlend);					// ���߂�l
			// Y���̉�]
			//=============================================================================================
			fDiffMotionRotY = Normalize(pKeyNext.fRotY, pKey.fRotY);				// ���̃L�[�Ƃ̍���
			fRotYCurrent = pKey.fRotY + (fDiffMotionRotY * fRateMotion);
			DiffMotionBlendRotY = pKeyNextBlend.fRotY - pKeyBlend.fRotY;
			fRotYBlend = pKeyBlend.fRotY + (DiffMotionBlendRotY * fRateMotionBlend);
			fDiffBlendRotY = fRotYBlend - fRotYCurrent;								// ����
			fRotY = fRotYCurrent + (fDiffBlendRotY * fRateBlend);					// ���߂�l
			//=============================================================================================

			// Z���̈ړ�
			//=============================================================================================
			fDiffMotionPosZ = pKeyNext.fPosZ - pKey.fPosZ;							// ���̃L�[�Ƃ̍���
			fPosZCurrent = pKey.fPosZ + (fDiffMotionPosZ * fRateMotion);
			DiffMotionBlendPosZ = pKeyNextBlend.fPosZ - pKeyBlend.fPosZ;
			fPosZBlend = pKeyBlend.fPosZ + (DiffMotionBlendPosZ * fRateMotionBlend);
			fDiffBlendPosZ = fPosZBlend - fPosZCurrent;								// ����
			fPosZ = fPosZCurrent + (fDiffBlendPosZ * fRateBlend);					// ���߂�l
			// Z���̉�]
			//=============================================================================================
			fDiffMotionRotZ = Normalize(pKeyNext.fRotZ, pKey.fRotZ);				// ���̃L�[�Ƃ̍���
			fRotZCurrent = pKey.fRotZ + (fDiffMotionRotZ * fRateMotion);
			DiffMotionBlendRotZ = pKeyNextBlend.fRotZ - pKeyBlend.fRotZ;
			fRotZBlend = pKeyBlend.fRotZ + (DiffMotionBlendRotZ * fRateMotionBlend);
			fDiffBlendRotZ = fRotZBlend - fRotZCurrent;								// ����
			fRotZ = fRotZCurrent + (fDiffBlendRotZ * fRateBlend);					// ���߂�l
			//=============================================================================================

		}
		else
		{//�u�����h����

			// �L�[��񂩂�ʒu.�������Z�o
			// ���̃L�[�Ƃ̍���
			fDiffMotionPosX = (pKeyNext.fPosX) - (pKey.fPosX);
			fDiffMotionPosY = (pKeyNext.fPosY) - (pKey.fPosY);
			fDiffMotionPosZ = (pKeyNext.fPosZ) - (pKey.fPosZ);
			fDiffMotionRotX = Normalize(pKeyNext.fRotX, pKey.fRotX);
			fDiffMotionRotY = Normalize(pKeyNext.fRotY, pKey.fRotY);
			fDiffMotionRotZ = Normalize(pKeyNext.fRotZ, pKey.fRotZ);

			//���߂�l
			fPosX = pKey.fPosX + fDiffMotionPosX * fRateMotion;
			fPosY = pKey.fPosY + fDiffMotionPosY * fRateMotion;
			fPosZ = pKey.fPosZ + fDiffMotionPosZ * fRateMotion;
			fRotX = pKey.fRotX + fDiffMotionRotX * fRateMotion;
			fRotY = pKey.fRotY + fDiffMotionRotY * fRateMotion;
			fRotZ = pKey.fRotZ + fDiffMotionRotZ * fRateMotion;
		}


		//�p�[�c�̈ʒu.������ݒ�
		D3DXVECTOR3 offsetPos = m_ppModel[nCntModel]->GetOffSetPos();
		//�ʒu
		ModelPos.x = offsetPos.x+fPosX;//�I�t�Z�b�g�l��
		ModelPos.y = offsetPos.y+fPosY;//�I�t�Z�b�g�l��
		ModelPos.z = offsetPos.z+fPosZ;//�I�t�Z�b�g�l��
		m_ppModel[nCntModel]->SetPos(ModelPos);
		D3DXVECTOR3 offsetRot = m_ppModel[nCntModel]->GetOffSetRot();
		//����
		ModelRot.x =offsetRot.x+fRotX;//�I�t�Z�b�g�l��
		ModelRot.y =offsetRot.y+fRotY;//�I�t�Z�b�g�l��
		ModelRot.z =offsetRot.z+fRotZ;//�I�t�Z�b�g�l��
		m_ppModel[nCntModel]->SetRot(ModelRot);
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
			SetMotion(0);
			m_bFinish = true;
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
		m_bFinish = false;
	}
}

void CMotion::SetInfo(MOTION_INFO motionInfo)
{
	m_aInfo[m_nNum] = motionInfo;
	m_nNum++;
}

//****************
// ���K��
//****************
float CMotion::Normalize(float fData0, float fData1)
{
	float fData = fData0 - fData1;

	if (fData > D3DX_PI)
	{
		fData -= D3DX_PI * 2.0f;
	}
	else if (fData < -D3DX_PI)
	{
		fData += D3DX_PI * 2.0f;
	}

	return fData;
}