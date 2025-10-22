//*********************************
//
// ���[���G�t�F�N�g���� [railEffect.cpp]
// Author Sasaki Soichiro
//
//*********************************

//*******************
// �C���N���[�h
//*******************
#include "railEffect.h"
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
#define EX_SIZE (30.0f)

//*****************
// �R���X�g���N�^
//*****************
CRailEffect::CRailEffect(int nPriority) :CObject3D(nPriority)
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nCntAnim = 0;				// �J�E���^�[������������
	m_nPatternAnim = 0;			// �p�^�[��No.������������
	m_nIdxTexture = 0;
	m_nLife = 0;
	m_bLife = false;
}

//***************
// �f�X�g���N�^
//***************
CRailEffect::~CRailEffect()
{
}

//*************
// ����������
//*************
HRESULT CRailEffect::Init(D3DXVECTOR3 pos)
{
	CTexture* pTexture = CManager::GetCTexture();
	m_nIdxTexture = pTexture->Register("data\\TEXTURE\\railThunder01.png");
	CObject3D::BindTexture(pTexture->GetAddres(m_nIdxTexture));
	CObject3D::Init(pos);
	// �e�N�X�`�������蓖�Ă�
	CObject3D::SetTex(D3DXVECTOR2(0.0f, 0.0f),
		D3DXVECTOR2(0.5f, 0.5f));
	m_nLife = 20;
	m_bLife = true;
	m_nPatternAnim = rand() % 4;
	return S_OK;
}

//************
// �I������
//************
void CRailEffect::Uninit(void)
{
	CObject3D::Uninit();
}

//***********
// �X�V����
//***********
void CRailEffect::Update(void)
{
	static float fData = 0.5f;
	CPlayer* pPlayer = CGame::GetCPlayer();

	D3DXVECTOR3 pos = CObject3D::GetPos();
	D3DXVECTOR3 rot = CObject3D::GetRot();
	CPlayer::STATE state = pPlayer->GetState();

	m_move.x = sinf(rot.y)*3.0f;
	m_move.z = cosf(rot.y)*3.0f;

	pos += m_move;
	SetPos(pos);

	//�A�j���[�V�����J�E���g���Z
	m_nCntAnim++;
	m_nLife--;

	if (m_nCntAnim >= 4)
	{//�A�j���[�V�����J�E���g��7�𒴂����Ƃ�
		//�A�j���[�V�����J�E���g������������
		m_nCntAnim = 0;
		//�A�j���[�V�����p�^�[�������Z
		m_nPatternAnim++;
		SetTex(D3DXVECTOR2(m_nPatternAnim * fData, (m_nPatternAnim / 2) * fData),
			D3DXVECTOR2(m_nPatternAnim * fData+fData, (m_nPatternAnim / 2) * fData + fData));

		if (m_nPatternAnim >= 4)
		{// �A�j���[�V�����p�^�[����4�𒴂����ꍇ
			// �A�j���[�V�����p�^�[��������������
			m_nPatternAnim = 0;
		}
	}
	if (m_nLife <= 0)
	{
		Uninit();
		return;
	}
}

//***********
// �`�揈��
//***********
void CRailEffect::Draw(void)
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
	CObject3D::Draw();
	//���u�����f�B���O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

}

//******************
// �C���X�^���X���� 
//******************
CRailEffect* CRailEffect::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR2 size)
{
	CRailEffect* pRailEffect;
	CTexture* pTexture = CManager::GetCTexture();
	int nNum = GetNumAll();
	if (nNum < MAX_OBJ - 1)
	{
		pRailEffect = new CRailEffect;
		pRailEffect->Init(pos);
		pRailEffect->SetRot(rot);
		pRailEffect->SetSize(size);

		return pRailEffect;
	}
	return NULL;
}

//**************
// �ʒu��ݒ�
//**************
void CRailEffect::SetPos(D3DXVECTOR3 pos)
{
	CObject3D::SetPos(pos);
}

//**************
// �F��ݒ�
//**************
void CRailEffect::SetCol(D3DXCOLOR col)
{
	CObject3D::SetCol(col);
}

//**************
// �傫����ݒ�
//**************
void CRailEffect::SetSize(D3DXVECTOR2 size)
{
	CObject3D::SetSize(size);
}

//**************
// �ʒu���擾
//**************
D3DXVECTOR3 CRailEffect::GetPos(void)
{
	D3DXVECTOR3 pos = CObject3D::GetPos();
	return pos;
}

//****************
// �傫�����擾
//****************
D3DXVECTOR2 CRailEffect::GetSize(void)
{
	return CObject3D::GetSize();
}