//**********************************
//
// �̗�UI���� [lifeUI.cpp]
// Author:Sasaki Soichiro
//
//**********************************

//*******************
// �C���N���[�h
//*******************
#include "numbermulti.h"
#include "manager.h"
#include "texture.h"

//*****************
// �R���X�g���N�^
//*****************
CNumberMulti::CNumberMulti(int nPriority) :CObject2DMulti(nPriority)
{
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		m_nIdxTexture[nCnt]=0;	// �C���f�b�N�X
	}
	m_nNum=0;
}

//*****************
// �f�X�g���N�^
//*****************
CNumberMulti::~CNumberMulti()
{
}

//*****************
// ����������
//*****************
HRESULT CNumberMulti::Init(D3DXVECTOR3 pos)
{
	CTexture* pTexture = CManager::GetCTexture();	// �e�N�X�`���̃|�C���^�擾
	CObject2DMulti::Init(pos);						// 2D�̏�����
	// �e�N�X�`�������蓖�Ă�
	CObject2DMulti::BindTexture(pTexture->GetAddres(m_nIdxTexture[0]), pTexture->GetAddres(m_nIdxTexture[1]));

	// UV�̐ݒ�
	CObject2DMulti::SetTex(D3DXVECTOR2(0.0f, 0.0f),
		D3DXVECTOR2(1.0f, 0.0f),
		D3DXVECTOR2(0.0f, 1.0f),
		D3DXVECTOR2(1.0f, 1.0f));
	// �e�N�X�`���̗Ε������ڂ�悤�ɐݒ�
	CObject2DMulti::SetTex2(D3DXVECTOR2(0.0f, 0.0f),
		D3DXVECTOR2(0.5f, 0.0f),
		D3DXVECTOR2(0.0f, 1.0f),
		D3DXVECTOR2(0.5f, 1.0f));

	// �傫���̐ݒ�
	CObject2DMulti::SetSize(D3DXVECTOR2(120.0f, 150.0f));
	SetNumber(m_nNum);
	SetGauge(50);

	return S_OK;
}

//*****************
// �I������
//*****************
void CNumberMulti::Uninit(void)
{
	// �I������
	CObject2DMulti::Uninit();
}

//*****************
// �X�V����
//*****************
void CNumberMulti::Update(void)
{

}

//*****************
// �`�揈��
//*****************
void CNumberMulti::Draw(void)
{
	// �`�揈��
	CObject2DMulti::Draw();
}

//******************
// �C���X�^���X����
//******************
CNumberMulti* CNumberMulti::Create(D3DXVECTOR3 pos)
{
	CNumberMulti* pLifeUI;								// ���C�t�̃|�C���^
	CTexture* pTexture = CManager::GetCTexture();	// �e�N�X�`���̃|�C���^

	int nNum = CObject::GetNumAll();// ���݂̃I�u�W�F�N�g�����擾
	if (nNum < MAX_OBJ - 1)
	{// �ő�I�u�W�F�N�g���𒴂��Ă��Ȃ�������

		pLifeUI = new CNumberMulti;// �C���X�^���X����
		// �}���`�e�N�X�`��1����(�d�r�̉摜)
		pLifeUI->m_nIdxTexture[0] = pTexture->Register("data\\TEXTURE\\number005.png");
		// �}���`�e�N�X�`��2����(�΁E���̓�F�̉摜)
		pLifeUI->m_nIdxTexture[1] = pTexture->Register("data\\TEXTURE\\orange.jpg");

		// ������
		pLifeUI->Init(pos);

		// ����n��
		return pLifeUI;
	}

	// (���s������)NULL��Ԃ�
	return NULL;
}

//*****************
// �ʒu�ݒ�
//*****************
void CNumberMulti::SetPos(D3DXVECTOR3 pos)
{
	// �ʒu�ݒ�
	CObject2DMulti::SetPos(pos);
}

//*****************
// �����ݒ�
//*****************
void CNumberMulti::SetRot(D3DXVECTOR3 rot)
{
	// �ʒu�ݒ�
	CObject2DMulti::SetRot(rot);
}
void CNumberMulti::SetCol(D3DXCOLOR col)
{
	CObject2DMulti::SetCol(col);
}
//*****************
// �ʒu���擾
//*****************
D3DXVECTOR3 CNumberMulti::GetPos(void)
{
	// �ʒu���擾
	return CObject2DMulti::GetPos();
}

void CNumberMulti::SetNumber(int nNum)
{
	float fData = 0.1f;

	// UV�̐ݒ�
	CObject2DMulti::SetTex(D3DXVECTOR2(nNum * fData, 0.0f),
		D3DXVECTOR2(fData + nNum * fData, 0.0f),
		D3DXVECTOR2(nNum * fData, 1.0f),
		D3DXVECTOR2(fData + nNum * fData, 1.0f));
}
void CNumberMulti::SetGauge(int nGauge)
{
	float p = (float)nGauge / 100;		// 1����100�̒l�ɒ���

	if (nGauge >= 0.0f && nGauge <= 100.0f)
	{
		// UV���W(�����ɉ����ĐF���ς��悤�Ɍv�Z)
		CObject2DMulti::SetTex2(D3DXVECTOR2(0.0f, p * 0.5f),
			D3DXVECTOR2(1.0f, p * 0.5f),
			D3DXVECTOR2(0.0f, 0.5f + p * 0.5f),
			D3DXVECTOR2(1.0f, 0.5f + p * 0.5f));
	}
}