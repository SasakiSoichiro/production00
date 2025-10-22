//**********************************
//
// �G�̗̑�UI���� [enemyLifeUI.cpp]
// Author:Sasaki Soichiro
//
//**********************************

//*******************
// �C���N���[�h
//*******************
#include "enemyLifeUI.h"
#include "manager.h"
#include "game.h"
#include "player.h"
#include "renderer.h"
#include "texture.h"

//*****************
// �R���X�g���N�^
//*****************
CEnemyLifeUI::CEnemyLifeUI(int nPriority) :CObjectBillboard(nPriority)
{
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		m_nIdxTexture[nCnt] = 0;
	}
	m_nIdx = 0;
	m_nUseTexture = 0;
}

//*****************
// �f�X�g���N�^
//*****************
CEnemyLifeUI::~CEnemyLifeUI()
{
}

//*****************
// ����������
//*****************
HRESULT CEnemyLifeUI::Init(D3DXVECTOR3 pos)
{
	// �e�N�X�`�����̎擾
	CTexture* pTexture = CManager::GetCTexture();

	CObjectBillboard::Init(pos);

	// �e�N�X�`�����W�̐ݒ�
	CObjectBillboard::SetTex(D3DXVECTOR2(0.0f, 0.0f),
		D3DXVECTOR2(1.0f, 0.0f),
		D3DXVECTOR2(0.0f, 1.0f),
		D3DXVECTOR2(1.0f, 1.0f));
	// �傫���̐ݒ�
	CObjectBillboard::SetSize(D3DXVECTOR2(5.0f, 5.0f));
	return S_OK;
}

//*****************
// �I������
//*****************
void CEnemyLifeUI::Uninit(void)
{
	// �I������
	CObjectBillboard::Uninit();
}

//*****************
// �X�V����
//*****************
void CEnemyLifeUI::Update(void)
{

}

//*****************
// �`�揈��
//*****************
void CEnemyLifeUI::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	CRenderer* renderer = CManager::GetCRenderer();
	pDevice = renderer->GetDevice();
	// �e�N�X�`�����̎擾
	CTexture* pTexture = CManager::GetCTexture();

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, pTexture->GetAddres(m_nIdxTexture[m_nUseTexture]));
	pDevice->SetTexture(1,NULL);

	CObjectBillboard::Draw();
}

//******************
// �C���X�^���X����
//******************
CEnemyLifeUI* CEnemyLifeUI::Create(D3DXVECTOR3 pos, D3DXVECTOR2 offset,int nIdx)
{
	CEnemyLifeUI* pEnemyUI;
	// �e�N�X�`�����̎擾
	CTexture* pTexture = CManager::GetCTexture();	

	int nNum = CObject::GetNumAll();// ���݂̃I�u�W�F�N�g�����擾
	if (nNum < MAX_OBJ - 1)
	{// �ő�I�u�W�F�N�g���𒴂��Ă��Ȃ�������

		// �C���X�^���X����
		pEnemyUI = new CEnemyLifeUI;
		// �e�N�X�`��
		pEnemyUI->m_nIdxTexture[0] = pTexture->Register("data\\TEXTURE\\memori.png");
		// �e�N�X�`��
		pEnemyUI->m_nIdxTexture[1] = pTexture->Register("data\\TEXTURE\\memori01.png");
		// ������
		pEnemyUI->Init(pos);

		pEnemyUI->m_nIdx=nIdx;

		pEnemyUI->SetOffset(offset);

		return pEnemyUI;
	}

	return NULL;
}

//*****************
// �ʒu�ݒ�
//*****************
void CEnemyLifeUI::SetPos(D3DXVECTOR3 pos)
{
	CObjectBillboard::SetPos(pos);
}

//*****************
// �����ݒ�
//*****************
void CEnemyLifeUI::SetRot(D3DXVECTOR3 rot)
{
	CObjectBillboard::SetRot(rot);
}

//*****************
// �ʒu���擾
//*****************
D3DXVECTOR3 CEnemyLifeUI::GetPos(void)
{
	return CObjectBillboard::GetPos();
}

//*****************
// UI�\���̐ݒ�
//*****************
void CEnemyLifeUI::SetLife(int nLife)
{
	// �e�N�X�`�������ւ���
	if (m_nIdx > nLife)
	{
		m_nUseTexture = 1;
	}
}