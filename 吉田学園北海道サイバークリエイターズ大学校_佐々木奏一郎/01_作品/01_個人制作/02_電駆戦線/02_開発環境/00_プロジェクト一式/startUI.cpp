//**********************************
//
// �X�^��UI���� [stanUI.cpp]
// Author:Sasaki Soichiro
//
//**********************************

//*******************
// �C���N���[�h
//*******************
#include "startUI.h"
#include "manager.h"
#include "texture.h"
#include "renderer.h"

//*****************
// �R���X�g���N�^
//*****************
CStartUI::CStartUI(int nPriority) :CObject2D(nPriority)
{
	m_nIdxTexture = 0;	// �C���f�b�N�X
}

//*****************
// �f�X�g���N�^
//*****************
CStartUI::~CStartUI()
{
}

//*****************
// ����������
//*****************
HRESULT CStartUI::Init(D3DXVECTOR3 pos)
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
	CObject2D::SetSize(D3DXVECTOR2(500.0f, 100.0f));
	return S_OK;
}

//*****************
// �I������
//*****************
void CStartUI::Uninit(void)
{
	// �I������
	CObject2D::Uninit();
}

//*****************
// �X�V����
//*****************
void CStartUI::Update(void)
{

}

//*****************
// �`�揈��
//*****************
void CStartUI::Draw(void)
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
CStartUI* CStartUI::Create(D3DXVECTOR3 pos)
{
	CStartUI* TitleUI;								// ���C�t�̃|�C���^
	CTexture* pTexture = CManager::GetCTexture();	// �e�N�X�`���̃|�C���^

	int nNum = CObject::GetNumAll();// ���݂̃I�u�W�F�N�g�����擾
	if (nNum < MAX_OBJ - 1)
	{// �ő�I�u�W�F�N�g���𒴂��Ă��Ȃ�������

		TitleUI = new CStartUI;// �C���X�^���X����
		// �e�N�X�`��
		TitleUI->m_nIdxTexture = pTexture->Register("data\\TEXTURE\\gamestart.png");

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
void CStartUI::SetPos(D3DXVECTOR3 pos)
{
	// �ʒu�ݒ�
	CObject2D::SetPos(pos);
}

//*****************
// �����ݒ�
//*****************
void CStartUI::SetRot(D3DXVECTOR3 rot)
{
	// �ʒu�ݒ�
	CObject2D::SetRot(rot);
}

//*****************
// �ʒu���擾
//*****************
D3DXVECTOR3 CStartUI::GetPos(void)
{
	// �ʒu���擾
	return CObject2D::GetPos();
}