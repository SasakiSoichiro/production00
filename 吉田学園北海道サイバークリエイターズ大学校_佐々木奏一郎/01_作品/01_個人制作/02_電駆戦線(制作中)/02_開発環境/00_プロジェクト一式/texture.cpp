//**********************************
//
// �e�N�X�`������ [texture.cpp]
// Author:Sasaki Soichiro
//
//**********************************

//*******************
// �C���N���[�h
//*******************
#include "texture.h"
#include "manager.h"

// �ÓI�����o�ϐ�������
int CTexture::m_nNumAll=0;

//=================
// �R���X�g���N�^
//=================
CTexture::CTexture()
{
	for (int nCnt = 0; nCnt < 256; nCnt++)
	{
		m_apTexture[nCnt] = NULL;
	}
	m_nNumAll++;
}

//=================
// �f�X�g���N�^
//=================
CTexture::~CTexture()
{
}

HRESULT CTexture::Load(void)
{

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	CRenderer* renderer = CManager::GetCRenderer();
	pDevice = renderer->GetDevice();
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,
			TEXTURE[nCnt],
			&m_apTexture[nCnt]);
	}

	return S_OK;
}

void CTexture::Unload(void)
{
	// �e�N�X�`���̔j��
	for (int nCnt = 0; nCnt < 256; nCnt++)
	{
		if (m_apTexture[nCnt] != NULL)
		{
			m_apTexture[nCnt]->Release();
			m_apTexture[nCnt] = NULL;
		}
	}
}

int CTexture::Register(const char* pFilename)
{
	int nCntRegister = 0;
	for (nCntRegister = 0; nCntRegister < 256; nCntRegister++)
	{
		if (TEXTURE[nCntRegister] == NULL)
		{
			if (m_apTexture[nCntRegister] == NULL)
			{
				// �f�o�C�X�̎擾
				LPDIRECT3DDEVICE9 pDevice;
				CRenderer* renderer = CManager::GetCRenderer();
				pDevice = renderer->GetDevice();
				//�e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice,
					pFilename,
					&m_apTexture[nCntRegister]);
				TEXTURE[nCntRegister] = pFilename;
				return nCntRegister;
			}
			else
			{
				return -1;
			}
		}

		else if (strcmp(pFilename, TEXTURE[nCntRegister]) == 0)
		{
			return nCntRegister;
		}
	}
	return -1;
}

LPDIRECT3DTEXTURE9 CTexture::GetAddres(int nIdx)
{
	return m_apTexture[nIdx];
}