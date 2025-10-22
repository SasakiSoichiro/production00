//**********************************
//
// �R���{���� [combo.cpp]
// Author:Sasaki Soichiro
//
//**********************************

//*******************
// �C���N���[�h
//*******************
#include "combo.h"
#include "manager.h"
#include "game.h"
#include "player.h"
#include "score.h"
#include "sound.h"
#include "numbermulti.h"

//**********************
// �ÓI�����o�ϐ�������
//**********************
CNumberMulti* CCombo::m_pNumberMulti[2]={};
int CCombo::m_nCurrent = 0;
int CCombo::m_nTime = 0;
int CCombo::m_nScore = 0;
const D3DXCOLOR CCombo::COMBO_ON = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
const D3DXCOLOR CCombo::COMBO_OFF = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);

//*****************
// �R���X�g���N�^
//*****************
CCombo::CCombo(int nPriority) :CObject(nPriority)
{
}

//*****************
// �f�X�g���N�^
//*****************
CCombo::~CCombo()
{
}

//*****************
// ����������
//*****************
HRESULT CCombo::Init(D3DXVECTOR3 pos)
{
	// �����̈ʒu�ƐF������
	m_pNumberMulti[0]->SetPos(D3DXVECTOR3(pos.x + offsetX, pos.y, 0.0f));
	m_pNumberMulti[1]->SetPos(D3DXVECTOR3(pos.x - offsetX, pos.y, 0.0f));
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		m_pNumberMulti[nCnt]->SetCol(COMBO_OFF);
	}
	m_nCurrent = 0;

	return S_OK;
}

//*****************
// �I������
//*****************
void CCombo::Uninit(void)
{
	CObject::Release();
}

//*****************
// �X�V����
//*****************
void CCombo::Update(void)
{
	// �R���{�I�����̃��Z�b�g
	Reset();

	// �R���{���̕\��
	Set();

	// �^�C�}�[�����炷
	m_nTime--;
}

//*****************
// �`�揈��
//*****************
void CCombo::Draw(void)
{

}

//******************
// �C���X�^���X����
//******************
CCombo* CCombo::Create(D3DXVECTOR3 pos)
{
	CCombo* TitleUI;
	// �e�N�X�`�����擾
	CTexture* pTexture = CManager::GetCTexture();	

	int nNum = CObject::GetNumAll();
	if (nNum < MAX_OBJ - 1)
	{// �ő�I�u�W�F�N�g���𒴂��Ă��Ȃ�������

		// �C���X�^���X����
		TitleUI = new CCombo;
		// �e�N�X�`��
		for (int nCnt = 0; nCnt < 2; nCnt++)
		{
			TitleUI->m_pNumberMulti[nCnt] = CNumberMulti::Create(D3DXVECTOR3(0.0f,0.0f,0.0f));
		}

		// ������
		TitleUI->Init(pos);

		return TitleUI;
	}

	return NULL;
}

//*****************
// �ʒu�ݒ�
//*****************
void CCombo::SetPos(D3DXVECTOR3 pos)
{
	m_pNumberMulti[0]->SetPos(D3DXVECTOR3(pos.x + offsetX, pos.y, 0.0f));
	m_pNumberMulti[1]->SetPos(D3DXVECTOR3(pos.x - offsetX, pos.y, 0.0f));
}

//*****************
// �����ݒ�
//*****************
void CCombo::SetRot(D3DXVECTOR3 rot)
{
	m_pNumberMulti[0]->SetRot(rot);
	m_pNumberMulti[1]->SetRot(rot);
}

//*****************
// �ʒu���擾
//*****************
D3DXVECTOR3 CCombo::GetPos(void)
{
	return NONE;
}

//*****************
// ������Ԃ�
//*****************
int CCombo::Digit(int nScore)
{
	int nNum = nScore;
	int nKeepNum = 0;

	// ����؂�Ȃ��Ȃ�܂ŌJ��Ԃ�
	while (nNum != 0)
	{
		nNum /= 10;// 10�Ŋ���
		nKeepNum++;// ���������Z
	}
	if (nScore == 0)
	{
		nKeepNum = 1;// 1���ڂ��O�̎�
	}

	return nKeepNum;
}

//*************
// �R���{���Z
//*************
void CCombo::Add(int nScore)
{
	// �T�E���h���̎擾��SE�Đ�
	CSound* pSound = CManager::GetCSound();
	pSound->Play(CSound::LABEL_SE07);

	// �R���{�����Z
	m_nCurrent++;
	m_nTime = maxTime;
	m_nScore += nScore;
}

//****************
// �R���{���̕\��
//****************
void CCombo::Set(void)
{
	int nData[2], nTime;

	// ������
	nData[0] = 10;
	nData[1] = 1;
	nTime = m_nTime / (maxTime/100);

	// �i���o�[�ɒl��ݒ�
	for (int nCntD = 0; nCntD < 2; nCntD++)
	{
		// �v�Z���Ēl��1�����ݒ�
		m_pNumberMulti[nCntD]->SetNumber((m_nCurrent % nData[0]) / nData[1]);
		m_pNumberMulti[nCntD]->SetGauge(nTime);
		nData[0] *= 10;
		nData[1] *= 10;
		m_pNumberMulti[nCntD]->SetCol(COMBO_OFF);
	}

	// �i���o�[�������`��
	if (m_nCurrent >= 1)
	{
		for (int nCntD = 0; nCntD < Digit(m_nCurrent); nCntD++)
		{
			m_pNumberMulti[nCntD]->SetCol(COMBO_ON);
		}
	}
}

//*************
// �R���{�I��
//*************
void CCombo::Reset(void)
{
	// �Q�[����Ԃ̎擾
	CGame::STATE state = CGame::GetState();
	if (m_nTime <= 0|| state==CGame::STATE_END)
	{// ���Ԍo��or�Q�[���I��������

		// �R���{���ɉ����ăX�R�A���Z
		int nFinishCombo = m_nCurrent;
		CScore::Add(m_nScore * nFinishCombo);

		// ������
		m_nCurrent = 0;
		m_nTime = 0;
		m_nScore = 0;
	}
	
}