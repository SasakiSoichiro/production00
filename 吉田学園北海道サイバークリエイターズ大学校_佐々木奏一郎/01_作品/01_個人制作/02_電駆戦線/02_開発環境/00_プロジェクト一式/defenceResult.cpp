//**********************************
//
// �h�q���ʕ\������ [defenceResult.cpp]
// Author:Sasaki Soichiro
//
//**********************************

//*******************
// �C���N���[�h
//*******************
#include "defenceResult.h"
#include "manager.h"
#include "game.h"
#include "timer.h"
#include "renderer.h"
#include "texture.h"
#include "player.h"


//*****************
// �R���X�g���N�^
//*****************
CDefenceResult::CDefenceResult(int nPriority) :CObject2D(nPriority)
{
	m_nIdxTexture = 0;	// �C���f�b�N�X
}

//*****************
// �f�X�g���N�^
//*****************
CDefenceResult::~CDefenceResult()
{
}

//*****************
// ����������
//*****************
HRESULT CDefenceResult::Init(D3DXVECTOR3 pos)
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
	// �傫���̐ݒ�
	CObject2D::SetSize(D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT));

	return S_OK;
}

//*****************
// �I������
//*****************
void CDefenceResult::Uninit(void)
{
	CObject2D::Uninit();
}

//*****************
// �X�V����
//*****************
void CDefenceResult::Update(void)
{

}

//*****************
// �`�揈��
//*****************
void CDefenceResult::Draw(void)
{
	CObject2D::Draw();
}

//******************
// �C���X�^���X����
//******************
CDefenceResult* CDefenceResult::Create(D3DXVECTOR3 pos)
{
	CDefenceResult* pDefenceResult;								// ���C�t�̃|�C���^

	int nNum = CObject::GetNumAll();// ���݂̃I�u�W�F�N�g�����擾
	if (nNum < MAX_OBJ - 1)
	{// �ő�I�u�W�F�N�g���𒴂��Ă��Ȃ�������

		// �C���X�^���X����
		pDefenceResult = new CDefenceResult;
		// �e�N�X�`��
		pDefenceResult->SetTex();
		// ������
		pDefenceResult->Init(pos);

		return pDefenceResult;
	}

	return NULL;
}

//*****************
// �ʒu�ݒ�
//*****************
void CDefenceResult::SetPos(D3DXVECTOR3 pos)
{
	CObject2D::SetPos(pos);
}

//*****************
// �����ݒ�
//*****************
void CDefenceResult::SetRot(D3DXVECTOR3 rot)
{
	CObject2D::SetRot(rot);
}

//*****************
// �ʒu���擾
//*****************
D3DXVECTOR3 CDefenceResult::GetPos(void)
{
	return CObject2D::GetPos();
}

//******************
// �e�N�X�`���̐ݒ�
//******************
void CDefenceResult::SetTex(void)
{
	// �e�N�X�`���ƃv���C���[�擾
	CTexture* pTexture = CManager::GetCTexture();
	CPlayer* pPlayer = CGame::GetCPlayer();
	// �c�莞�Ԏ擾
	int time = CTimer::GetTime();

	if (pPlayer->GetLife() <= 0.0f || time <= 0)
	{// �������Ƃ�
		m_nIdxTexture = pTexture->Register("data\\TEXTURE\\gameover.png");
	}
	else
	{// �������Ƃ�
		m_nIdxTexture = pTexture->Register("data\\TEXTURE\\gameclear.png");
	}
}