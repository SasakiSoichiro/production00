//**********************************
//
// �^�C���{�[�i�X���� [timeBonus.cpp]
// Author:Sasaki Soichiro
//
//**********************************

//*******************
// �C���N���[�h
//*******************
#include "timeBonus.h"
#include "manager.h"

int CTimeBonus::m_nTime = 0;

//*****************
// �R���X�g���N�^
//*****************
CTimeBonus::CTimeBonus(int nPriority) :CBonus(nPriority)
{
	for (int nCnt = 0; nCnt < 5; nCnt++)
	{
		m_pNumber[nCnt]=NULL;
	}
}

//*****************
// �f�X�g���N�^
//*****************
CTimeBonus::~CTimeBonus()
{
}

//*****************
// ����������
//*****************
HRESULT CTimeBonus::Init(D3DXVECTOR3 pos)
{

	CBonus::Init(pos);						// 2D�̏�����

	return S_OK;
}

//*****************
// �I������
//*****************
void CTimeBonus::Uninit(void)
{
	// �I������
	CBonus::Uninit();
}

//*****************
// �X�V����
//*****************
void CTimeBonus::Update(void)
{

}

//*****************
// �`�揈��
//*****************
void CTimeBonus::Draw(void)
{
	// �`�揈��
	CBonus::Draw();
}

//******************
// �C���X�^���X����
//******************
CTimeBonus* CTimeBonus::Create(D3DXVECTOR3 pos)
{
	CTimeBonus* pTimeBonus;							// ���C�t�̃|�C���^
	CTexture* pTexture = CManager::GetCTexture();	// �e�N�X�`���̃|�C���^

	int nNum = CObject::GetNumAll();// ���݂̃I�u�W�F�N�g�����擾
	if (nNum < MAX_OBJ - 1)
	{// �ő�I�u�W�F�N�g���𒴂��Ă��Ȃ�������

		pTimeBonus = new CTimeBonus;// �C���X�^���X����
		// �e�N�X�`��
		pTimeBonus->SetTexture("data\\TEXTURE\\timeBonus.png");
		// ������
		pTimeBonus->Init(pos);

		// ����n��
		return pTimeBonus;
	}

	// (���s������)NULL��Ԃ�
	return NULL;
}

//*****************
// �ʒu�ݒ�
//*****************
void CTimeBonus::SetPos(D3DXVECTOR3 pos)
{
	// �ʒu�ݒ�
	CObject2D::SetPos(pos);
}

//*****************
// �����ݒ�
//*****************
void CTimeBonus::SetRot(D3DXVECTOR3 rot)
{
	// �ʒu�ݒ�
	CObject2D::SetRot(rot);
}

//*****************
// �ʒu���擾
//*****************
D3DXVECTOR3 CTimeBonus::GetPos(void)
{
	// �ʒu���擾
	return CObject2D::GetPos();
}