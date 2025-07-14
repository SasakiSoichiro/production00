//**********************************
//
// �f�o�b�O�\������ [debugproc.cpp]
// Author:Sasaki Soichiro
//
//**********************************

//*******************
// �C���N���[�h
//*******************
#include "debugproc.h"
#include "renderer.h"
#include "manager.h"

//**********************
// �ÓI�����o�ϐ�������
//**********************
LPD3DXFONT CDebugProc::m_pFont = NULL;
char CDebugProc::m_aStr[1024] = {};
bool CDebugProc::m_bDebug = false;

//****************
// �R���X�g���N�^
//****************
CDebugProc::CDebugProc()
{

}

//****************
// �f�X�g���N�^
//****************
CDebugProc::~CDebugProc()
{
}

//*********
// ������
//*********
void CDebugProc::Init(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	CRenderer* renderer = CManager::GetCRenderer();
	pDevice = renderer->GetDevice();

	// �t�H���g�̍쐬
	D3DXCreateFont(pDevice, 18, 0, 0, 0,
		FALSE,
		SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH,
		"Terminal", &m_pFont);
	
	// ������̏�����
	memset(&m_aStr[0],0,sizeof(m_aStr));
}

//*********
// �I��
//*********
void CDebugProc::Uninit(void)
{
	//�f�o�b�O�\���p�̃t�H���g��j��
	if (m_pFont != NULL)
	{
		m_pFont->Release();
		m_pFont = NULL;
	}
}

//*******************
// �f�o�b�O�\������
//*******************
void CDebugProc::Print(const char* fmt, ...)
{
	if (m_bDebug == true)
	{
		va_list args;
		size_t len;
		va_start(args, fmt);
		int nCnt = 0;
		int nData = 0;
		double fData = 0.0;
		while (*fmt)
		{
			if (*fmt == '%')
			{
				fmt++;
				int nPrec = 6;	// ���x
				if (*fmt == '.')
				{
					fmt++;
					nPrec = 0;
					//nPrec= va_arg(args, int);
					while (*fmt >= '0' && *fmt <= '9') {
						nPrec = nPrec * 10 + (*fmt - '0');
						fmt++;
					}
				}
				switch (*fmt)
				{
				case 'd':
					nData = va_arg(args, int);
					len = strlen(m_aStr);
					sprintf(&m_aStr[len], "%d", nData);
					break;
				case 'f':
					fData = va_arg(args, double);
					len = strlen(m_aStr);
					sprintf(&m_aStr[len], "%*.*f", 6, nPrec, fData);
					break;
				}
			}
			else
			{
				char c = putchar(*fmt);
				len = strlen(m_aStr);
				m_aStr[len] += c;
			}
			fmt++;
		}
		va_end(args);
	}
}

//********************
// �`��
//********************
void CDebugProc::Draw(void)
{
	if (m_bDebug == true)
	{
		RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
		m_pFont->DrawText(NULL, &m_aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 0, 255, 255));
		memset(&m_aStr[0], 0, sizeof(m_aStr));
	}
}