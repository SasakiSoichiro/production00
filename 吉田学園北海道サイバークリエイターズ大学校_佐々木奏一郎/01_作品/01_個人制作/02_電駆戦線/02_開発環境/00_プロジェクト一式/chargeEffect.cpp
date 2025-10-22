//*********************************
//
// �G�t�F�N�g���� [effect.cpp]
// Author Sasaki Soichiro
//
//*********************************

//*******************
// �C���N���[�h
//*******************
#include "chargeEffect.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "debugproc.h"
#include "texture.h"
#include "game.h"
#include "player.h"

//****************
// �R���X�g���N�^
//****************
CChargeEffect::CChargeEffect(int nPriority) :CEffect(nPriority)
{

}

//**************
// �f�X�g���N�^
//**************
CChargeEffect::~CChargeEffect()
{
}

//**************
// ����������
//**************
HRESULT CChargeEffect::Init(D3DXVECTOR3 pos)
{
	CEffect::Init(pos);

	return S_OK;
}

//**************
// �I������
//**************
void CChargeEffect::Uninit(void)
{
	CEffect::Uninit();
}

//**************
// �X�V����
//**************
void CChargeEffect::Update(void)
{
	// �v���C���[�ƃv���C���[�̈ʒu���擾
	CPlayer* pPlayer = CGame::GetCPlayer();
	D3DXVECTOR3 playerPos = pPlayer->GetPos();
	// �ʒu�ƌ����ƃ��[�u�l���擾
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();
	D3DXVECTOR3 move = GetMove();

	D3DXVECTOR3 moveDest;

	// �x�������Ȃ���v���C���[�̈ʒu�ɓ�����
	playerPos.y += offsetY;
	moveDest = playerPos - pos;
	move += (moveDest - move) * dest;
	pos += move;

	// ���f
	SetPos(pos);
	SetMove(move);

	CEffect::Update();
}

//**************
// �`�揈��
//**************
void CChargeEffect::Draw(void)
{
	CEffect::Draw();
}

//*******************
// �C���X�^���X���� 
//*******************
CChargeEffect* CChargeEffect::Create(D3DXVECTOR3 pos, float fAngle, D3DXVECTOR2 size, int nLife, D3DXCOLOR col)
{
	CChargeEffect* pExplosion;
	// �e�N�X�`�����擾
	CTexture* pTexture = CManager::GetCTexture();
	int nNum = GetNumAll();
	if (nNum < MAX_OBJ - 1)
	{
		// �C���X�^���X����
		pExplosion = new CChargeEffect;
		// �e�N�X�`�����蓖��
		pExplosion->SetTexture(pTexture->Register("data\\TEXTURE\\electricity000.jpg"));
		// ������
		pExplosion->Init(pos);
		pExplosion->SetRot(D3DXVECTOR3(0.0f, fAngle, (float)(rand() % 314) / 100.0f));
		pExplosion->SetMove(D3DXVECTOR3(sinf(fAngle) * speed, 0.0f, cosf(fAngle) * speed));
		pExplosion->SetSize(size);
		pExplosion->SetCol(col);
		pExplosion->SetLife(nLife);

		return pExplosion;
	}
	return NULL;
}