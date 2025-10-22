//*********************************
//
// �G�t�F�N�g���� [effect.cpp]
// Author Sasaki Soichiro
//
//*********************************

//*******************
// �C���N���[�h
//*******************
#include "effect.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "debugproc.h"
#include "texture.h"

//****************
// �R���X�g���N�^
//****************
CEffect::CEffect(int nPriority) :CObjectBillboard(nPriority)
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nCntAnim = 0;				
	m_nPatternAnim = 0;
	m_nIdxTexture = 0;
	m_nLife = 0;
	m_bLife = false;
}

//****************
// �f�X�g���N�^
//****************
CEffect::~CEffect()
{
}

//*************
// ����������
//*************
HRESULT CEffect::Init(D3DXVECTOR3 pos)
{
	CTexture* pTexture = CManager::GetCTexture();
	CObjectBillboard::Init(pos);
	// �e�N�X�`�������蓖�Ă�
	CObjectBillboard::SetTex(D3DXVECTOR2(0.0f, 0.0f),
		D3DXVECTOR2(texOffset, 0.0f),
		D3DXVECTOR2(0.0f, 1.0f),
		D3DXVECTOR2(texOffset, 1.0f));
	m_nLife = maxLife;
	m_bLife = true;

	return S_OK;
}

//************
// �I������
//************
void CEffect::Uninit(void)
{
	CObjectBillboard::Uninit();
}

//************
// �X�V����
//************
void CEffect::Update(void)
{
	// �ʒu�ƌ����Ƒ傫���ƐF���̎擾
	D3DXVECTOR3 pos = CObjectBillboard::GetPos();
	D3DXVECTOR3 rot = CObjectBillboard::GetRot();
	D3DXVECTOR2 size = CObjectBillboard::GetSize();
	D3DXCOLOR col = CObjectBillboard::GetCol();

	// �A�j���[�V�����J�E���g���Z
	m_nCntAnim++;
	if (m_nCntAnim >= anim)
	{// �A�j���[�V�����J�E���g��3�𒴂����Ƃ�
		// �A�j���[�V�����J�E���g������������
		m_nCntAnim = 0;
		// �A�j���[�V�����p�^�[�������Z
		m_nPatternAnim++;
		// �e�N�X�`�����W���f
		SetTex(D3DXVECTOR2(m_nPatternAnim * texOffset, 0.0f),
			D3DXVECTOR2(texOffset + m_nPatternAnim * texOffset, 0.0f),
			D3DXVECTOR2(m_nPatternAnim * texOffset, 1.0f),
			D3DXVECTOR2(texOffset + m_nPatternAnim * texOffset, 1.0f));

		if (m_nPatternAnim >= patternAnim)
		{// �A�j���[�V�����p�^�[����4�𒴂����ꍇ
			// �A�j���[�V�����p�^�[��������������
			m_nPatternAnim = 0;
		}
	}

	// �����ŏI��
	m_nLife--;
	if (m_nLife <= 0)
	{
		Uninit();
		return;
	}
}

//************
// �`�揈��
//************
void CEffect::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	CTexture* pTexture = CManager::GetCTexture();
	CRenderer* renderer = CManager::GetCRenderer();

	pDevice = renderer->GetDevice();
	// ���u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, pTexture->GetAddres(m_nIdxTexture));
	CObjectBillboard::Draw();
	// ���u�����f�B���O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

}

//*******************
// �C���X�^���X���� 
//*******************
CEffect* CEffect::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot,D3DXVECTOR2 size, int nLife,D3DXCOLOR col)
{
	CEffect* pExplosion;
	// �e�N�X�`�����擾
	CTexture* pTexture = CManager::GetCTexture();
	int nNum = GetNumAll();
	if (nNum < MAX_OBJ - 1)
	{
		// �C���X�^���X����
		pExplosion = new CEffect;
		// �e�N�X�`�����蓖��
		pExplosion->m_nIdxTexture = pTexture->Register("data\\TEXTURE\\thunder005.png");
		// ������
		pExplosion->Init(pos);
		pExplosion->SetRot(rot);
		pExplosion->SetSize(size);
		pExplosion->SetCol(col);
		pExplosion->m_move = move;
		pExplosion->m_nLife = nLife;
		
		return pExplosion;
	}
	return NULL;
}

//****************
// �ʒu��ݒ�
//****************
void CEffect::SetPos(D3DXVECTOR3 pos)
{
	CObjectBillboard::SetPos(pos);
}

//****************
// ������ݒ�
//****************
void CEffect::SetRot(D3DXVECTOR3 rot)
{
	CObjectBillboard::SetRot(rot);
}

//****************
// �F��ݒ�
//****************
void CEffect::SetCol(D3DXCOLOR col)
{
	CObjectBillboard::SetCol(col);
}

//****************
// �傫����ݒ�
//****************
void CEffect::SetSize(D3DXVECTOR2 size)
{
	CObjectBillboard::SetSize(size);
}

//****************
// �ʒu���擾
//****************
D3DXVECTOR3 CEffect::GetPos(void)
{
	return CObjectBillboard::GetPos();
}

//****************
// �傫�����擾
//****************
D3DXVECTOR2 CEffect::GetSize(void)
{
	return CObjectBillboard::GetSize();
}