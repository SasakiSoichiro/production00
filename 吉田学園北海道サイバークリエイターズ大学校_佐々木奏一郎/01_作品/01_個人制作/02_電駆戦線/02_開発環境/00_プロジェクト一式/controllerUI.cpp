//**********************************
//
// �X�^��UI���� [stanUI.cpp]
// Author:Sasaki Soichiro
//
//**********************************

//*******************
// �C���N���[�h
//*******************
#include "controllerUI.h"
#include "manager.h"
#include "game.h"
#include "player.h"
#include "renderer.h"
#include "texture.h"
#include "input.h"

//*****************
// �R���X�g���N�^
//*****************
CControllerUI::CControllerUI(int nPriority) :CObject2D(nPriority)
{
	m_nIdxTexture = 0;	// �C���f�b�N�X
	m_bScreen = false;
}

//*****************
// �f�X�g���N�^
//*****************
CControllerUI::~CControllerUI()
{
}

//*****************
// ����������
//*****************
HRESULT CControllerUI::Init(D3DXVECTOR3 pos)
{
	CTexture* pTexture = CManager::GetCTexture();
	CObject2D::BindTexture(pTexture->GetAddres(m_nIdxTexture));

	CObject2D::Init(pos);						// 2D�̏�����

	// UV�̐ݒ�
	CObject2D::SetTex(D3DXVECTOR2(0.0f, 0.0f),
		D3DXVECTOR2(1.0f, 0.0f),
		D3DXVECTOR2(0.0f, 1.0f),
		D3DXVECTOR2(1.0f, 1.0f));
	// �傫���̐ݒ�
	CObject2D::SetSize(D3DXVECTOR2(150.0f, 300.0f));
	m_bScreen = true;

	return S_OK;
}

//*****************
// �I������
//*****************
void CControllerUI::Uninit(void)
{
	CObject2D::Uninit();
}

//*****************
// �X�V����
//*****************
void CControllerUI::Update(void)
{
	// ���͎擾
	CInputKeyboard* pKeyboard = CManager::GetCInputKeyboard();
	if (pKeyboard->Trigger(DIK_C))
	{
		m_bScreen = !m_bScreen;
	}

	// �\���E��\������
	if(m_bScreen)
	{
		// �ʒu�ƐF
		SetPos(D3DXVECTOR3(100.0f, SCREEN_HEIGHT / 2, 0.0f));
		CObject2D::SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
	else
	{
		// �ʒu�ƐF
		SetPos(D3DXVECTOR3(-100.0f, SCREEN_HEIGHT / 2, 0.0f));
		CObject2D::SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	}
}

//*****************
// �`�揈��
//*****************
void CControllerUI::Draw(void)
{
	CObject2D::Draw();
}

//******************
// �C���X�^���X����
//******************
CControllerUI* CControllerUI::Create(D3DXVECTOR3 pos)
{
	// ���g�̃|�C���^
	CControllerUI* pControllerUI;
	// �e�N�X�`���擾
	CTexture* pTexture = CManager::GetCTexture();

	int nNum = CObject::GetNumAll();// ���݂̃I�u�W�F�N�g�����擾
	if (nNum < MAX_OBJ - 1)
	{// �ő�I�u�W�F�N�g���𒴂��Ă��Ȃ�������

		// �C���X�^���X����
		pControllerUI = new CControllerUI;
		// �e�N�X�`��
		pControllerUI->m_nIdxTexture = pTexture->Register("data\\TEXTURE\\controller.png");
		// ������
		pControllerUI->Init(pos);

		return pControllerUI;
	}

	return NULL;
}

//*****************
// �ʒu�ݒ�
//*****************
void CControllerUI::SetPos(D3DXVECTOR3 pos)
{
	CObject2D::SetPos(pos);
}

//*****************
// �����ݒ�
//*****************
void CControllerUI::SetRot(D3DXVECTOR3 rot)
{
	CObject2D::SetRot(rot);
}

//*****************
// �ʒu���擾
//*****************
D3DXVECTOR3 CControllerUI::GetPos(void)
{
	return CObject2D::GetPos();
}