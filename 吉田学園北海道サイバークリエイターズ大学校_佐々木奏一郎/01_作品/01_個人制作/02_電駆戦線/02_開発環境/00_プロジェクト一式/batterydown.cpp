//**********************************
//
// �̗�UI���� [lifeUI.cpp]
// Author:Sasaki Soichiro
//
//**********************************

//*******************
// �C���N���[�h
//*******************
#include "batterydown.h"
#include "manager.h"
#include "game.h"
#include "player.h"
#include "renderer.h"
#include "texture.h"

//************************
// �ÓI�����o�ϐ�������
//************************
const D3DXVECTOR2 CBatteryDown::SIZE = D3DXVECTOR2(200.0f, 50.0f);

//*****************
// �R���X�g���N�^
//*****************
CBatteryDown::CBatteryDown(int nPriority) :CObject2D(nPriority)
{
	m_nIdxTexture = 0;
}

//*****************
// �f�X�g���N�^
//*****************
CBatteryDown::~CBatteryDown()
{
}

//*****************
// ����������
//*****************
HRESULT CBatteryDown::Init(D3DXVECTOR3 pos)
{
	// �e�N�X�`�����擾�ƃe�N�X�`���̊��蓖��
	CTexture* pTexture = CManager::GetCTexture();
	CObject2D::BindTexture(pTexture->GetAddres(m_nIdxTexture));

	// ������
	CObject2D::Init(pos);						

	// UV�̐ݒ�
	CObject2D::SetTex(D3DXVECTOR2(0.0f, 0.0f),
		D3DXVECTOR2(1.0f, 0.0f),
		D3DXVECTOR2(0.0f, 1.0f),
		D3DXVECTOR2(1.0f, 1.0f));

	// �傫���̐ݒ�
	CObject2D::SetSize(SIZE);

	return S_OK;
}

//*****************
// �I������
//*****************
void CBatteryDown::Uninit(void)
{
	CObject2D::Uninit();
}

//*****************
// �X�V����
//*****************
void CBatteryDown::Update(void)
{
	// �v���C���[�Ƒ̗͂̏��擾
	CPlayer* pPlayer = CGame::GetCPlayer();
	float fLife = pPlayer->GetLife();

	// �̗͒ቺUI�\��
	if (fLife < line && fLife > 0.0f)
	{// �s����
		CObject2D::SetPos(D3DXVECTOR3(SCREEN_WIDTH / 2, 150.0f, 0.0f));

		CObject2D::SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
	else
	{// ����
		CObject2D::SetPos(D3DXVECTOR3(SCREEN_WIDTH / 2, -150.0f, 0.0f));

		CObject2D::SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	}

}

//*****************
// �`�揈��
//*****************
void CBatteryDown::Draw(void)
{
	CObject2D::Draw();
}

//******************
// �C���X�^���X����
//******************
CBatteryDown* CBatteryDown::Create(D3DXVECTOR3 pos)
{
	// ���C�t�̃|�C���^
	CBatteryDown* BatteryDown;
	// �e�N�X�`�����擾
	CTexture* pTexture = CManager::GetCTexture();

	// ���݂̃I�u�W�F�N�g�����擾
	int nNum = CObject::GetNumAll();
	if (nNum < MAX_OBJ - 1)
	{// �ő�I�u�W�F�N�g���𒴂��Ă��Ȃ�������

		// �C���X�^���X����
		BatteryDown = new CBatteryDown;
		// �e�N�X�`��
		BatteryDown->m_nIdxTexture = pTexture->Register("data\\TEXTURE\\batteryDown.png");
		// ������
		BatteryDown->Init(pos);

		return BatteryDown;
	}

	return NULL;
}

//*****************
// �ʒu�ݒ�
//*****************
void CBatteryDown::SetPos(D3DXVECTOR3 pos)
{
	CObject2D::SetPos(pos);
}

//*****************
// �����ݒ�
//*****************
void CBatteryDown::SetRot(D3DXVECTOR3 rot)
{
	CObject2D::SetRot(rot);
}

//*****************
// �ʒu���擾
//*****************
D3DXVECTOR3 CBatteryDown::GetPos(void)
{
	return CObject2D::GetPos();
}