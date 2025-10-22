//**********************************
//
// �{�[�i�X���� [bonus.cpp]
// Author:Sasaki Soichiro
//
//**********************************

//*******************
// �C���N���[�h
//*******************
#include "bonus.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"


//*****************
// �R���X�g���N�^
//*****************
CBonus::CBonus(int nPriority) :CObject2D(nPriority)
{
	m_nIdxTexture = 0;	// �C���f�b�N�X
}

//*****************
// �f�X�g���N�^
//*****************
CBonus::~CBonus()
{
}

//*****************
// ����������
//*****************
HRESULT CBonus::Init(D3DXVECTOR3 pos)
{
	// �e�N�X�`���擾
	CTexture* pTexture = CManager::GetCTexture();
	// �e�N�X�`�����蓖��
	CObject2D::BindTexture(pTexture->GetAddres(m_nIdxTexture));

	CObject2D::Init(pos);

	// UV�̐ݒ�
	CObject2D::SetTex(D3DXVECTOR2(0.0f, 0.0f),
		D3DXVECTOR2(1.0f, 0.0f),
		D3DXVECTOR2(0.0f, 1.0f),
		D3DXVECTOR2(1.0f, 1.0f));

	return S_OK;
}

//*****************
// �I������
//*****************
void CBonus::Uninit(void)
{
	CObject2D::Uninit();
}

//*****************
// �X�V����
//*****************
void CBonus::Update(void)
{

}

//*****************
// �`�揈��
//*****************
void CBonus::Draw(void)
{
	// �`�揈��
	CObject2D::Draw();
}

//*****************
// �ʒu�ݒ�
//*****************
void CBonus::SetPos(D3DXVECTOR3 pos)
{
	CObject2D::SetPos(pos);
}

//*****************
// �����ݒ�
//*****************
void CBonus::SetRot(D3DXVECTOR3 rot)
{
	CObject2D::SetRot(rot);
}

//******************
// �傫���̐ݒ�
//******************
void CBonus::SetSize(D3DXVECTOR2 size)
{
	CObject2D::SetSize(size);
}

//***********************
// �g���e�N�X�`���̐ݒ�
//***********************
void CBonus::SetTexture(const char* pFileName)
{
	CTexture* pTexture=CManager::GetCTexture();
	// �e�N�X�`��
	m_nIdxTexture = pTexture->Register(pFileName);
}

//*****************
// �ʒu���擾
//*****************
D3DXVECTOR3 CBonus::GetPos(void)
{
	// �ʒu���擾
	return CObject2D::GetPos();
}
