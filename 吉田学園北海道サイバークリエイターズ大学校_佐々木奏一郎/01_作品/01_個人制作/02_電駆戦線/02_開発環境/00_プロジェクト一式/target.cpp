//**********************************
//
// �^�C�g��UI���� [titleUI.cpp]
// Author:Sasaki Soichiro
//
//**********************************

//*******************
// �C���N���[�h
//*******************
#include "target.h"
#include "manager.h"
#include "texture.h"
#include "renderer.h"

//*****************
// �R���X�g���N�^
//*****************
CTarget::CTarget(int nPriority) :CObject2D(nPriority)
{
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		m_nIdxTexture[nCnt] = 0;	// �C���f�b�N�X
	}
	m_nType = 0;
}

//*****************
// �f�X�g���N�^
//*****************
CTarget::~CTarget()
{
}

//*****************
// ����������
//*****************
HRESULT CTarget::Init(D3DXVECTOR3 pos)
{
	CTexture* pTexture = CManager::GetCTexture();
	CObject2D::BindTexture(pTexture->GetAddres(m_nIdxTexture[m_nType]));

	CObject2D::Init(pos);						// 2D�̏�����

	// UV�̐ݒ�
	CObject2D::SetTex(D3DXVECTOR2(0.0f, 0.0f),
		D3DXVECTOR2(1.0f, 0.0f),
		D3DXVECTOR2(0.0f, 1.0f),
		D3DXVECTOR2(1.0f, 1.0f));
	// �傫���̐ݒ�
	CObject2D::SetSize(D3DXVECTOR2(500.0f, 40.0f));
	return S_OK;
}

//*****************
// �I������
//*****************
void CTarget::Uninit(void)
{
	// �I������
	CObject2D::Uninit();
}

//*****************
// �X�V����
//*****************
void CTarget::Update(void)
{
	CTexture* pTexture = CManager::GetCTexture();

	if (m_nCnt > cool)
	{
		switch (m_nType)
		{
		case 0:
			m_nType++;
			CObject2D::BindTexture(pTexture->GetAddres(m_nIdxTexture[m_nType]));
			m_nCnt = 0;
			break;
		case 1:
			m_nType++;
			CObject2D::BindTexture(pTexture->GetAddres(m_nIdxTexture[m_nType]));
			m_nCnt = 0;
			break;

			break;
		case 2:
			CObject2D::SetCol(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
			CObject2D::SetPos(D3DXVECTOR3(SCREEN_WIDTH / 2, -200.0f, 0.0f));
			break;
		}
	}
	m_nCnt++;
}

//*****************
// �`�揈��
//*****************
void CTarget::Draw(void)
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
CTarget* CTarget::Create(D3DXVECTOR3 pos)
{
	CTarget* TitleUI;								// ���C�t�̃|�C���^
	CTexture* pTexture = CManager::GetCTexture();	// �e�N�X�`���̃|�C���^

	int nNum = CObject::GetNumAll();// ���݂̃I�u�W�F�N�g�����擾
	if (nNum < MAX_OBJ - 1)
	{// �ő�I�u�W�F�N�g���𒴂��Ă��Ȃ�������

		TitleUI = new CTarget;// �C���X�^���X����
		// �e�N�X�`��
		TitleUI->m_nIdxTexture[0] = pTexture->Register("data\\TEXTURE\\tutorial0.png");
		TitleUI->m_nIdxTexture[1] = pTexture->Register("data\\TEXTURE\\tutorial1.png");
		TitleUI->m_nIdxTexture[2] = pTexture->Register("data\\TEXTURE\\tutorial2.png");

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
void CTarget::SetPos(D3DXVECTOR3 pos)
{
	// �ʒu�ݒ�
	CObject2D::SetPos(pos);
}

//*****************
// �����ݒ�
//*****************
void CTarget::SetRot(D3DXVECTOR3 rot)
{
	// �ʒu�ݒ�
	CObject2D::SetRot(rot);
}

//*****************
// �ʒu���擾
//*****************
D3DXVECTOR3 CTarget::GetPos(void)
{
	// �ʒu���擾
	return CObject2D::GetPos();
}