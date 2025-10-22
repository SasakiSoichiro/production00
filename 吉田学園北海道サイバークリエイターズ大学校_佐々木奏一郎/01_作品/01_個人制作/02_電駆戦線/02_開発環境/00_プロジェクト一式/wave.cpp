//*****************************************
//
// �E�F�[�u���� [block.cpp]
// Author:Sasaki Soichiro
//
//*****************************************

//*******************
// �C���N���[�h
//*******************
#include "wave.h"
#include "enemy.h"
#include <iostream>
#include <fstream>
#include "debugproc.h"
#include "texture.h"
#include "manager.h"
#include <cmath>
#include "game.h"
#include "number.h"
#include "renderer.h"
#include "sound.h"

//**********************
// �ÓI�����o�ϐ�������
//**********************
int CWave::m_nCurrent = 0;
int CWave::m_nAll = 0;
CNumber* CWave::m_pNumber=NULL;



//*****************
// �R���X�g���N�^
//*****************
CWave::CWave(int nPriority) :CObject2D(nPriority)
{
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		m_nIdxTexture[nCnt] = 0;
	}
	m_nScreenTime = 0;
	m_bScreen = false;
	m_bGo = false;
	m_bStop = false;
	m_bEnd = false;
	m_fCnt = 0.0f;
}

//*****************
// �f�X�g���N�^
//*****************
CWave::~CWave()
{
}

//******************
// �C���X�^���X����
//******************
CWave* CWave::Create(D3DXVECTOR3 pos)
{
	CWave* pWave;								// ���C�t�̃|�C���^
	CTexture* pTexture = CManager::GetCTexture();	// �e�N�X�`���̃|�C���^

	int nNum = CObject::GetNumAll();// ���݂̃I�u�W�F�N�g�����擾
	if (nNum < MAX_OBJ - 1)
	{// �ő�I�u�W�F�N�g���𒴂��Ă��Ȃ�������

		pWave = new CWave;// �C���X�^���X����
		// �e�N�X�`��
		pWave->m_nIdxTexture[0] = pTexture->Register("data\\TEXTURE\\wave.png");
		pWave->m_nIdxTexture[1] = pTexture->Register("data\\TEXTURE\\number017.png");
		pWave->m_pNumber = new CNumber;
		// ������
		pWave->Init(pos);

		// ����n��
		return pWave;
	}

	// (���s������)NULL��Ԃ�
	return NULL;
}

//*****************
// ����������
//*****************
HRESULT CWave::Init(D3DXVECTOR3 pos)
{
	m_nAll = 3;
	m_nCurrent = 0;
	CTexture* pTexture = CManager::GetCTexture();
	CObject2D::BindTexture(pTexture->GetAddres(m_nIdxTexture[0]));

	CObject2D::Init(pos);						// 2D�̏�����

	// UV�̐ݒ�
	CObject2D::SetTex(D3DXVECTOR2(0.0f, 0.0f),
		D3DXVECTOR2(1.0f, 0.0f),
		D3DXVECTOR2(0.0f, 1.0f),
		D3DXVECTOR2(1.0f, 1.0f));
	// �傫���̐ݒ�
	CObject2D::SetSize(D3DXVECTOR2(300.0f, 70.0f));
	// �L���̃|�C���^������
	// ������
	m_pNumber->Init();
	// �傫��
	m_pNumber->SetSize(D3DXVECTOR2(40.0f, 55.0f));
	m_pNumber->SetNumber(0);
	// �ʒu�ݒ�
	m_pNumber->SetPos(D3DXVECTOR3((pos.x + 100.0f), pos.y, 0.0f));


	// ����������
	return S_OK;
}

//*****************
// �I������
//*****************
void CWave::Uninit(void)
{
	if (m_pNumber != NULL)
	{
		m_pNumber->Uninit();
		delete m_pNumber;
		m_pNumber = NULL;
	}
	CObject2D::Uninit();						// 2D�̏�����
}

//*****************
// �X�V����
//*****************
void CWave::Update(void)
{
	int nNum=CEnemy::GetNumAll();
	CSound* pSound = CManager::GetCSound();
	CDebugProc::Print("���݂̃E�F�[�u:%d", m_nCurrent);
	if (nNum <= 0)
	{
		if (m_nAll > m_nCurrent)
		{
			
			Load(m_nCurrent);
			m_nCurrent++;
			m_nScreenTime = 60;
			m_bScreen = true;
			pSound->Play(CSound::LABEL_SE00);
		}
		else
		{
			CGame::SetState(CGame::STATE_END);
		}
	}
	Move();
	m_pNumber->SetNumber(m_nCurrent);
}
//*****************
// �`�揈��
//*****************
void CWave::Draw(void)
{
	CObject2D::Draw();
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;						// �f�o�C�X
	CTexture* pTexture = CManager::GetCTexture();	// �e�N�X�`���̃|�C���^�擾
	CRenderer* renderer = CManager::GetCRenderer();	// �����_���[�̃|�C���^�擾
	pDevice = renderer->GetDevice();				// �f�o�C�X�擾
	// �L���`��
	// �e�N�X�`���ݒ�
	pDevice->SetTexture(0, pTexture->GetAddres(m_nIdxTexture[1]));
	m_pNumber->Draw();
}


void CWave::SetPos(D3DXVECTOR3 pos)
{
	CObject2D::SetPos(pos);
}
void CWave::SetRot(D3DXVECTOR3 rot)
{
	CObject2D::SetRot(rot);
}
D3DXVECTOR3 CWave::GetPos(void)
{
	return CObject2D::GetPos();
}

void CWave::Load(int nWave)
{

	std::ifstream file(WAVE[nWave]);
	
	int nType = 0;
	int nCnt = 0;
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	if (file.is_open() == false)
	{
		return;
	}
	std::string line;
	while (std::getline(file, line))
	{
		int scan = sscanf(line.c_str(),
			"pos = %f %f %f : type %d",
			&pos.x, &pos.y, &pos.z,&nType);

		CEnemy::Create(pos, nType);
		nCnt++;
	}
	// �t�@�C���𖾎��I�ɕ���
	file.close();
}

void CWave::Move(void)
{
	D3DXVECTOR3 pos = GetPos();
	if (m_bScreen == true)
	{
		SetPos(D3DXVECTOR3(-100.0f, 150.0f, 0.0f));
		m_pNumber->SetPos(D3DXVECTOR3((pos.x + 100.0f), pos.y, 0.0f));
		m_bScreen = false;
		m_bGo = true;
		m_fCnt = 0.0f;
	}
	if (m_bGo == true)
	{
		if (m_fCnt < 1.0f)
		{
			pos.x = -100.0f + ((SCREEN_WIDTH/2.0f) + 100.0f) * (1.0f - std::pow(1.0f - m_fCnt, 5.0f));
			SetPos(D3DXVECTOR3(pos.x, 150.0f, 0.0f));
			m_pNumber->SetPos(D3DXVECTOR3((pos.x + 100.0f), pos.y, 0.0f));
			m_fCnt += 0.01f;
		}
		else
		{
			m_bGo = false;
			m_bStop = true;
			m_fCnt = 0.0f;
		}
	}
	else if (m_bStop == true)
	{
		if (m_nScreenTime <= 0)
		{
			m_bEnd = true;
			m_bStop = false;
		}
		m_nScreenTime--;
	}
	else if (m_bEnd == true)
	{
		if (m_fCnt < 1.0f)
		{
			pos.x = (SCREEN_WIDTH / 2.0f) + (1500.0f - (SCREEN_WIDTH / 2.0f)) * (1.0f - std::pow(1.0f - m_fCnt, 5.0f));
			SetPos(D3DXVECTOR3(pos.x, 150.0f, 0.0f));
			m_pNumber->SetPos(D3DXVECTOR3((pos.x + 100.0f), pos.y, 0.0f));
			m_fCnt += 0.01f;
		}
		else
		{
			m_bEnd = false;
			m_fCnt += 0.0f;
		}
	}

}