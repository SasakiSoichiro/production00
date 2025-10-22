//**********************************
//
// �|�[�Y���� [pause.cpp]
// Author:Sasaki Soichiro
//
//**********************************

//*******************
// �C���N���[�h
//*******************
#include "pause.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "input.h"
#include "player.h"
#include "game.h"
#include "fade.h"

//*****************
// �}�N����`
//*****************
#define PAUSE_WIDTH (300.0f)
#define PAUSE_HEIGHT (100.0f)

//*****************
// �ÓI�����o�ϐ�
//*****************
bool CPause::m_bPause = false;
int CPause::m_nSelect = 0;

//=================
// �R���X�g���N�^
//=================
CPause::CPause(int nPriority) :CObject2D(nPriority)
{
	m_nIdxTexture = 0;
	m_nAnim = 0;
}

//=================
// �f�X�g���N�^
//=================
CPause::~CPause()
{
}

//=================
// ����������
//=================
HRESULT CPause::Init(D3DXVECTOR3 pos)
{
	CObject2D::Init(pos);
	CObject2D::SetTex(D3DXVECTOR2(0.0f, 0.0f),
		D3DXVECTOR2(1.0f, 0.0f),
		D3DXVECTOR2(0.0f, 1.0f),
		D3DXVECTOR2(1.0f, 1.0f));
	CObject2D::SetSize(D3DXVECTOR2(PAUSE_WIDTH, PAUSE_HEIGHT));
	CTexture* pTexture = CManager::GetCTexture();
	CObject2D::BindTexture(pTexture->GetAddres(m_nIdxTexture));
	CObject::SetType(CObject::TYPE_PAUSE);

	return S_OK;

}

//=================
// �I������
//=================
void CPause::Uninit(void)
{
	CObject2D::Uninit();
}

//=================
// �X�V����
//=================
void CPause::Update(void)
{
}

//=================
// �`�揈��
//=================
void CPause::Draw(void)
{
	if (m_bPause == true)
	{
		// �f�o�C�X�̎擾
		LPDIRECT3DDEVICE9 pDevice;
		CTexture* pTexture = CManager::GetCTexture();
		CRenderer* renderer = CManager::GetCRenderer();
		pDevice = renderer->GetDevice();
		CObject2D::Draw();
	}
}
CPause* CPause::Create(D3DXVECTOR3 pos,int nType)
{
	CPause* pPause=NULL;
	CTexture* pTexture = CManager::GetCTexture();
	int nNum = GetNumAll();
	if (nNum < MAX_OBJ - 1)
	{
		switch (nType)
		{
		case TYPE_BACKGAME:
			pPause = new CBackGame;
			pPause->m_nIdxTexture = pTexture->Register("data\\TEXTURE\\backgame.png");

			break;
		case TYPE_STARTGAME:
			pPause = new CStartGame;
			pPause->m_nIdxTexture = pTexture->Register("data\\TEXTURE\\startgame.png");

			break;

		case TYPE_BACKTITLE:
			pPause = new CBackTitle;
			pPause->m_nIdxTexture = pTexture->Register("data\\TEXTURE\\backtitle.png");

			break;

		case TYPE_REVERSE:
			pPause = new CReverse;
			pPause->m_nIdxTexture = pTexture->Register("data\\TEXTURE\\reverse.png");

			break;


		}
		pPause->Init(pos);
		return pPause;
	}
	return NULL;
}
void CPause::SetPos(D3DXVECTOR3 pos)
{
	CObject2D::SetPos(pos);
}
void CPause::SetRot(D3DXVECTOR3 rot)
{
	CObject2D::SetRot(rot);
}

D3DXVECTOR3 CPause::GetPos(void)
{
	return CObject2D::GetPos();
}
D3DXVECTOR2 CPause::GetSize(void)
{
	return CObject2D::GetSize();
}

void CPause::AnimSize(void)
{
	D3DXVECTOR2 size = GetSize();
	size.x += sinf(m_nAnim)*0.5f;
	size.y += sinf(m_nAnim)*0.5f;

	SetSize(size);
	m_nAnim += 0.05f;
}

//*********************
// �R���X�g���N�^
//*********************
CBackGame::CBackGame()
{

}

//*********************
// �f�X�g���N�^
//*********************
CBackGame::~CBackGame() 
{

}

//**********
// ������
//**********
HRESULT CBackGame::Init(D3DXVECTOR3 pos)
{
	CPause::Init(pos);
	return S_OK;
}

//***********
// �I������
//***********
void CBackGame::Uninit(void)
{
	CPause::Uninit();
}

//***********
// �X�V����
//***********
void CBackGame::Update(void)
{
	int nSelect = GetSelect();
	CInputKeyboard* pKeyboard = CManager::GetCInputKeyboard();
	CInputJoypad* pJoypad = CManager::GetCInputJoypad();

	if (CPause::TYPE_BACKGAME == nSelect)
	{
		AnimSize();
		SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		if (pKeyboard->Trigger(DIK_RETURN) || pJoypad->GetTrigger(CInputJoypad::JOYKEY_A))
		{
			CPause::SwitchPause();
		}
	}
	else
	{
		SetSize(D3DXVECTOR2(PAUSE_WIDTH, PAUSE_HEIGHT));
		SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.6f));
	}
}

//***********
// �`�揈��
//***********
void CBackGame::Draw(void)
{
	CPause::Draw();
}

//*********************
// �R���X�g���N�^
//*********************
CStartGame::CStartGame()
{

}

//*********************
// �f�X�g���N�^
//*********************
CStartGame::~CStartGame()
{

}

//**********
// ������
//**********
HRESULT CStartGame::Init(D3DXVECTOR3 pos)
{
	CPause::Init(pos);
	return S_OK;
}

//***********
// �I������
//***********
void CStartGame::Uninit(void)
{
	CPause::Uninit();
}

//***********
// �X�V����
//***********
void CStartGame::Update(void)
{
	int nSelect = GetSelect();
	CInputKeyboard* pKeyboard = CManager::GetCInputKeyboard();
	if (CPause::TYPE_STARTGAME == nSelect)
	{
		AnimSize();
		SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
	else
	{
		SetSize(D3DXVECTOR2(PAUSE_WIDTH, PAUSE_HEIGHT));
		SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.6f));
	}

}

//***********
// �`�揈��
//***********
void CStartGame::Draw(void)
{
	CPause::Draw();
}

//*********************
// �R���X�g���N�^
//*********************
CBackTitle::CBackTitle()
{

}

//*********************
// �f�X�g���N�^
//*********************
CBackTitle::~CBackTitle()
{

}

//**********
// ������
//**********
HRESULT CBackTitle::Init(D3DXVECTOR3 pos)
{
	CPause::Init(pos);
	return S_OK;
}

//***********
// �I������
//***********
void CBackTitle::Uninit(void)
{
	CPause::Uninit();
}

//***********
// �X�V����
//***********
void CBackTitle::Update(void)
{
	int nSelect = GetSelect();
	CInputKeyboard* pKeyboard = CManager::GetCInputKeyboard();
	CInputJoypad* pJoypad = CManager::GetCInputJoypad();

	if (CPause::TYPE_BACKTITLE == nSelect)
	{
		AnimSize();
		SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		if (pKeyboard->Trigger(DIK_RETURN) || pJoypad->GetTrigger(CInputJoypad::JOYKEY_A))
		{
			CPause::SwitchPause();
			CFade::Set(CScene::MODE_TITLE);
		}

	}
	else
	{
		SetSize(D3DXVECTOR2(PAUSE_WIDTH, PAUSE_HEIGHT));
		SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.6f));
	}

}

//***********
// �`�揈��
//***********
void CBackTitle::Draw(void)
{
	CPause::Draw();
}

//*********************
// �R���X�g���N�^
//*********************
CReverse::CReverse()
{

}

//*********************
// �f�X�g���N�^
//*********************
CReverse::~CReverse()
{

}

//**********
// ������
//**********
HRESULT CReverse::Init(D3DXVECTOR3 pos)
{
	CPause::Init(pos);
	return S_OK;
}

//***********
// �I������
//***********
void CReverse::Uninit(void)
{
	CPause::Uninit();
}

//***********
// �X�V����
//***********
void CReverse::Update(void)
{
	int nSelect = GetSelect();
	CInputKeyboard* pKeyboard = CManager::GetCInputKeyboard();
	CInputJoypad* pJoypad = CManager::GetCInputJoypad();
	CPlayer* pPlayer = CGame::GetCPlayer();

	if (CPause::TYPE_REVERSE == nSelect)
	{
		AnimSize();
		SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		if (pKeyboard->Trigger(DIK_RETURN) || pJoypad->GetTrigger(CInputJoypad::JOYKEY_A))
		{
			pPlayer->SwitchReverse();
			CPause::SwitchPause();
		}

	}
	else
	{
		SetSize(D3DXVECTOR2(PAUSE_WIDTH, PAUSE_HEIGHT));
		SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.6f));
	}

}

//***********
// �`�揈��
//***********
void CReverse::Draw(void)
{
	CPause::Draw();
}
