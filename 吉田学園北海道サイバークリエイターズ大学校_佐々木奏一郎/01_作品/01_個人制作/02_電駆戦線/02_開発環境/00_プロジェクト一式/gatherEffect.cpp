//**************************************
//
// �W�܂�G�t�F�N�g���� [gatherEffect.cpp]
// Author:Sasaki Soichiro
//
//**************************************

//*******************
// �C���N���[�h
//*******************
#include "gatherEffect.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "debugproc.h"
#include "texture.h"
#include "player.h"
#include "game.h"

//*******************
// �}�N����`
//*******************
#define EX_SIZE (10.0f)

//******************
// �R���X�g���N�^
//******************
CGatherEffect::CGatherEffect(int nPriority) :CObjectBillboard(nPriority)
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nIdxTexture = 0;
	m_nLife = 0;
}

//******************
// �f�X�g���N�^
//******************
CGatherEffect::~CGatherEffect()
{
}

//******************
// ����������
//******************
HRESULT CGatherEffect::Init(D3DXVECTOR3 pos)
{
	CTexture* pTexture = CManager::GetCTexture();
	CObjectBillboard::Init(pos);
	// �e�N�X�`�������蓖�Ă�
	CObjectBillboard::SetTex(D3DXVECTOR2(0.0f, 0.0f),
		D3DXVECTOR2(1.0f, 0.0f),
		D3DXVECTOR2(0.0f, 1.0f),
		D3DXVECTOR2(1.0f, 1.0f));
	m_nLife = 60;
	return S_OK;
}

//******************
// �I������
//******************
void CGatherEffect::Uninit(void)
{
	CObjectBillboard::Uninit();
}

//******************
// �X�V����
//******************
void CGatherEffect::Update(void)
{
	// �ʒu�擾
	D3DXVECTOR3 pos = GetPos();
	// �v���C���[�̈ʒu�ƑO�t���[���̈ʒu�擾
	CPlayer* pPlayer = CGame::GetCPlayer();
	D3DXVECTOR3 playerPos = pPlayer->GetPos();
	D3DXVECTOR3 playerPosOld = pPlayer->GetPos();
	D3DXVECTOR3 vec;

	// �v���C���[�ւ̃x�N�g��
	vec.x = (playerPos.x - pos.x);
	vec.y = (playerPos.y + 25.0f - pos.y);
	vec.z = (playerPos.z - pos.z);

	// �v���C���[�֓���
	pos = playerPos + vec;
	m_move.x = (playerPos.x - pos.x) * 0.05f;
	m_move.y = (playerPos.y+25.0f - pos.y) * 0.05f;
	m_move.z = (playerPos.z - pos.z) * 0.05f;
	pos += m_move;

	// ���f
	SetPos(pos);

	// �����ŏ���
	m_nLife--;
	if (m_nLife <= 0)
	{
		Uninit();
	}
}

//******************
// �`�揈��
//******************
void CGatherEffect::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	CTexture* pTexture = CManager::GetCTexture();
	CRenderer* renderer = CManager::GetCRenderer();
	pDevice = renderer->GetDevice();
	//���u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, pTexture->GetAddres(m_nIdxTexture));
	CObjectBillboard::Draw();
	//���u�����f�B���O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//******************
// �C���X�^���X���� 
//******************
CGatherEffect* CGatherEffect::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, int nLife, D3DXCOLOR col)
{
	// ���g�̃|�C���^
	CGatherEffect* pSmoke;
	// �e�N�X�`���擾
	CTexture* pTexture = CManager::GetCTexture();
	int nNum = GetNumAll();
	if (nNum < MAX_OBJ - 1)
	{
		// �C���X�^���X����
		pSmoke = new CGatherEffect;
		// �e�N�X�`��
		pSmoke->m_nIdxTexture = pTexture->Register("data\\TEXTURE\\effect000.jpg");
		// ������
		pSmoke->Init(pos);
		pSmoke->SetSize(size);
		pSmoke->SetCol(col);
		pSmoke->m_nLife = nLife;


		return pSmoke;
	}
	return NULL;
}

//******************
// �ʒu��ݒ�
//******************
void CGatherEffect::SetPos(D3DXVECTOR3 pos)
{
	CObjectBillboard::SetPos(pos);
}

//******************
// �F��ݒ�
//******************
void CGatherEffect::SetCol(D3DXCOLOR col)
{
	CObjectBillboard::SetCol(col);
}

//******************
// �傫����ݒ�
//******************
void CGatherEffect::SetSize(D3DXVECTOR2 size)
{
	CObjectBillboard::SetSize(size);
}

//******************
// �ʒu�����擾
//******************
D3DXVECTOR3 CGatherEffect::GetPos(void)
{
	return CObjectBillboard::GetPos();
}

//******************
// �傫�������擾
//******************
D3DXVECTOR2 CGatherEffect::GetSize(void)
{
	return CObjectBillboard::GetSize();
}