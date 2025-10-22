//**********************************
//
// �̗�UI���� [lifeUI.cpp]
// Author:Sasaki Soichiro
//
//**********************************

//*******************
// �C���N���[�h
//*******************
#include "tutorialcheck.h"
#include "manager.h"
#include "game.h"
#include "player.h"
#include "renderer.h"
#include "texture.h"

//************************
// �ÓI�����o�ϐ�������
//************************
const D3DXVECTOR2 CTutorialCheck::SIZE_CHECK = D3DXVECTOR2(80.0f, 80.0f);
const D3DXVECTOR2 CTutorialCheck::SIZE_CHECKBOX = D3DXVECTOR2(500.0f, 70.0f);

//*****************
// �R���X�g���N�^
//*****************
CTutorialCheck::CTutorialCheck(int nPriority) :CObject2D(nPriority)
{
	m_pCheckBox = NULL;
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		m_nIdxTextureCheck[nCnt] = 0;		// �C���f�b�N�X
	}
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		m_nIdxTextureCheckBox[nCnt] = 0;	// �C���f�b�N�X
	}
	m_bCheck = false;
	m_nCheckBox = 0;

}

//*****************
// �f�X�g���N�^
//*****************
CTutorialCheck::~CTutorialCheck()
{
}

//*****************
// ����������
//*****************
HRESULT CTutorialCheck::Init(D3DXVECTOR3 pos)
{
	// �e�N�X�`�����擾�ƃe�N�X�`���̊��蓖��
	CTexture* pTexture = CManager::GetCTexture();

	// �e�N�X�`���o�^
	m_nIdxTextureCheck[0] = pTexture->Register("data\\TEXTURE\\check00.png");
	m_nIdxTextureCheck[1] = pTexture->Register("data\\TEXTURE\\check01.png");

	// �`�F�b�N���ڂ̃e�N�X�`���o�^
	m_nIdxTextureCheckBox[0] = pTexture->Register("data\\TEXTURE\\FlontBack.png");
	m_nIdxTextureCheckBox[1] = pTexture->Register("data\\TEXTURE\\RightLeft.png");
	m_nIdxTextureCheckBox[2] = pTexture->Register("data\\TEXTURE\\roll.png");
	m_nIdxTextureCheckBox[3] = pTexture->Register("data\\TEXTURE\\jump.png");
	m_nIdxTextureCheckBox[4] = pTexture->Register("data\\TEXTURE\\jumpCancel.png");
	m_nIdxTextureCheckBox[5] = pTexture->Register("data\\TEXTURE\\rail.png");
	m_nIdxTextureCheckBox[6] = pTexture->Register("data\\TEXTURE\\attack.png");
	m_nIdxTextureCheckBox[7] = pTexture->Register("data\\TEXTURE\\free.png");


	CObject2D::BindTexture(pTexture->GetAddres(m_nIdxTextureCheck[0]));
	m_pCheckBox->BindTexture(pTexture->GetAddres(m_nIdxTextureCheckBox[m_nCheckBox]));

	// ������
	CObject2D::Init(pos);
	D3DXVECTOR3 boxPos = D3DXVECTOR3(pos.x + boxOffset, pos.y, pos.z);
	m_pCheckBox->Init(boxPos);

	// UV�̐ݒ�
	CObject2D::SetTex(D3DXVECTOR2(0.0f, 0.0f),
		D3DXVECTOR2(1.0f, 0.0f),
		D3DXVECTOR2(0.0f, 1.0f),
		D3DXVECTOR2(1.0f, 1.0f));
	m_pCheckBox->SetTex(D3DXVECTOR2(0.0f, 0.0f),
		D3DXVECTOR2(1.0f, 0.0f),
		D3DXVECTOR2(0.0f, 1.0f),
		D3DXVECTOR2(1.0f, 1.0f));

	// �傫���̐ݒ�
	CObject2D::SetSize(SIZE_CHECK);
	m_pCheckBox->SetSize(SIZE_CHECKBOX);

	return S_OK;
}

//*****************
// �I������
//*****************
void CTutorialCheck::Uninit(void)
{
	m_pCheckBox->Uninit();
	CObject2D::Uninit();
}

//*****************
// �X�V����
//*****************
void CTutorialCheck::Update(void)
{
	// �e�N�X�`�����擾�ƃe�N�X�`���̊��蓖��
	CTexture* pTexture = CManager::GetCTexture();

	if (m_bCheck==true&&m_nCnt>60)
	{
		m_nCheckBox++;
		m_bCheck = false;
		CObject2D::BindTexture(pTexture->GetAddres(m_nIdxTextureCheck[0]));
		m_pCheckBox->BindTexture(pTexture->GetAddres(m_nIdxTextureCheckBox[m_nCheckBox]));
	}
	m_nCnt++;
}

//*****************
// �`�揈��
//*****************
void CTutorialCheck::Draw(void)
{
	CObject2D::Draw();
	m_pCheckBox->Draw();
}

//******************
// �C���X�^���X����
//******************
CTutorialCheck* CTutorialCheck::Create(D3DXVECTOR3 pos)
{
	// ���C�t�̃|�C���^
	CTutorialCheck* pCheck;

	// ���݂̃I�u�W�F�N�g�����擾
	int nNum = CObject::GetNumAll();
	if (nNum < MAX_OBJ - 1)
	{// �ő�I�u�W�F�N�g���𒴂��Ă��Ȃ�������

		// �C���X�^���X����
		pCheck = new CTutorialCheck;
		pCheck->m_pCheckBox = new CObject2D(5);
		// ������
		pCheck->Init(pos);

		return pCheck;
	}

	return NULL;
}

//*****************
// �ʒu�ݒ�
//*****************
void CTutorialCheck::SetPos(D3DXVECTOR3 pos)
{
	CObject2D::SetPos(pos);
}

//*****************
// �����ݒ�
//*****************
void CTutorialCheck::SetRot(D3DXVECTOR3 rot)
{
	CObject2D::SetRot(rot);
}

//*****************
// �ʒu���擾
//*****************
D3DXVECTOR3 CTutorialCheck::GetPos(void)
{
	return CObject2D::GetPos();
}

void CTutorialCheck::Clear(void)
{
	// �e�N�X�`�����擾�ƃe�N�X�`���̊��蓖��
	CTexture* pTexture = CManager::GetCTexture();
	CObject2D::BindTexture(pTexture->GetAddres(m_nIdxTextureCheck[1]));

	m_bCheck = true;
	m_nCnt = 0;
}