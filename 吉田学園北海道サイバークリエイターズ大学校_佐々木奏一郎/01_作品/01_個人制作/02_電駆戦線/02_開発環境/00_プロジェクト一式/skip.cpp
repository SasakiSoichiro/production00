//**********************************
//
// �^�C�g��UI���� [titleUI.cpp]
// Author:Sasaki Soichiro
//
//**********************************

//*******************
// �C���N���[�h
//*******************
#include "skip.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"

//*****************
// �R���X�g���N�^
//*****************
CSkip::CSkip(int nPriority) :CObject2D(nPriority)
{
	m_nIdxTexture = 0;	// �C���f�b�N�X
}

//*****************
// �f�X�g���N�^
//*****************
CSkip::~CSkip()
{
}

//*****************
// ����������
//*****************
HRESULT CSkip::Init(D3DXVECTOR3 pos)
{
	CTexture* pTexture = CManager::GetCTexture();
	CObject2D::BindTexture(pTexture->GetAddres(m_nIdxTexture));

	// 2D�̏�����
	CObject2D::Init(pos);

	// UV�̐ݒ�
	CObject2D::SetTex(D3DXVECTOR2(0.0f, 0.0f),
		D3DXVECTOR2(1.0f, 0.0f),
		D3DXVECTOR2(0.0f, 1.0f),
		D3DXVECTOR2(1.0f, 1.0f));
	// �傫���̐ݒ�
	CObject2D::SetSize(D3DXVECTOR2(400.0f, 50.0f));
	CObject2D::SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	return S_OK;
}

//*****************
// �I������
//*****************
void CSkip::Uninit(void)
{
	// �I������
	CObject2D::Uninit();
}

//*****************
// �X�V����
//*****************
void CSkip::Update(void)
{

}

//*****************
// �`�揈��
//*****************
void CSkip::Draw(void)
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
CSkip* CSkip::Create(D3DXVECTOR3 pos)
{
	CSkip* TitleUI;								// ���C�t�̃|�C���^
	CTexture* pTexture = CManager::GetCTexture();	// �e�N�X�`���̃|�C���^

	int nNum = CObject::GetNumAll();// ���݂̃I�u�W�F�N�g�����擾
	if (nNum < MAX_OBJ - 1)
	{// �ő�I�u�W�F�N�g���𒴂��Ă��Ȃ�������

		TitleUI = new CSkip;// �C���X�^���X����
		// �e�N�X�`��
		TitleUI->m_nIdxTexture = pTexture->Register("data\\TEXTURE\\tutorialSkip.png");

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
void CSkip::SetPos(D3DXVECTOR3 pos)
{
	// �ʒu�ݒ�
	CObject2D::SetPos(pos);
}

//*****************
// �����ݒ�
//*****************
void CSkip::SetRot(D3DXVECTOR3 rot)
{
	// �ʒu�ݒ�
	CObject2D::SetRot(rot);
}

//*****************
// �ʒu���擾
//*****************
D3DXVECTOR3 CSkip::GetPos(void)
{
	// �ʒu���擾
	return CObject2D::GetPos();
}