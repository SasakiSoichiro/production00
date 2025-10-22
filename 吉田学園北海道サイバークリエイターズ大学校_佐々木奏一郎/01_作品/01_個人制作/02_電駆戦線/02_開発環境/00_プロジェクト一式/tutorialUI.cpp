//**********************************
//
// �^�C�g��UI���� [titleUI.cpp]
// Author:Sasaki Soichiro
//
//**********************************

//*******************
// �C���N���[�h
//*******************
#include "tutorialUI.h"
#include "manager.h"
#include "game.h"
#include "player.h"
#include "renderer.h"
#include "texture.h"

//*****************
// �R���X�g���N�^
//*****************
CTutorialUI::CTutorialUI(int nPriority) :CObject2D(nPriority)
{
	m_nIdxTexture = 0;	// �C���f�b�N�X
}

//*****************
// �f�X�g���N�^
//*****************
CTutorialUI::~CTutorialUI()
{
}

//*****************
// ����������
//*****************
HRESULT CTutorialUI::Init(D3DXVECTOR3 pos)
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
	CObject2D::SetSize(D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT));
	CObject2D::SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	return S_OK;
}

//*****************
// �I������
//*****************
void CTutorialUI::Uninit(void)
{
	// �I������
	CObject2D::Uninit();
}

//*****************
// �X�V����
//*****************
void CTutorialUI::Update(void)
{

}

//*****************
// �`�揈��
//*****************
void CTutorialUI::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	CRenderer* renderer = CManager::GetCRenderer();
	pDevice = renderer->GetDevice();

	// �`�揈��
	CObject2D::Draw();
}

//******************
// �C���X�^���X����
//******************
CTutorialUI* CTutorialUI::Create(D3DXVECTOR3 pos)
{
	CTutorialUI* TitleUI;								// ���C�t�̃|�C���^
	CTexture* pTexture = CManager::GetCTexture();	// �e�N�X�`���̃|�C���^

	int nNum = CObject::GetNumAll();// ���݂̃I�u�W�F�N�g�����擾
	if (nNum < MAX_OBJ - 1)
	{// �ő�I�u�W�F�N�g���𒴂��Ă��Ȃ�������

		TitleUI = new CTutorialUI;// �C���X�^���X����
		// �e�N�X�`��
		TitleUI->m_nIdxTexture = pTexture->Register("data\\TEXTURE\\tutorial00.jpg");

		// ������
		TitleUI->Init(pos);

		// ����n��
		return TitleUI;
	}

	// (���s������)NULL��Ԃ�
	return NULL;
}

//*****************
// �ʒu�ݒ�
//*****************
void CTutorialUI::SetPos(D3DXVECTOR3 pos)
{
	// �ʒu�ݒ�
	CObject2D::SetPos(pos);
}

//*****************
// �����ݒ�
//*****************
void CTutorialUI::SetRot(D3DXVECTOR3 rot)
{
	// �ʒu�ݒ�
	CObject2D::SetRot(rot);
}

//*****************
// �ʒu���擾
//*****************
D3DXVECTOR3 CTutorialUI::GetPos(void)
{
	// �ʒu���擾
	return CObject2D::GetPos();
}