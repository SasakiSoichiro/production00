//**********************************
//
// �u���[�Ǘ����� [blurManager.cpp]
// Author:Sasaki Soichiro
//
//**********************************

//*******************
// �C���N���[�h
//*******************
#include "fade.h"
#include "manager.h"
#include "renderer.h"

//**********************
// �ÓI�����o�ϐ�������
//**********************
CFade::STATE CFade::m_state=STATE_IN;
CScene::MODE CFade::m_modeNext=CScene::MODE_TITLE;


//*****************
// �R���X�g���N�^
//*****************
CFade::CFade()
{
	m_pVtxBuff = NULL;
	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
}

//*****************
// �f�X�g���N�^
//*****************
CFade::~CFade()
{
}

//*****************
// ����������
//*****************
HRESULT CFade::Init(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	CRenderer* renderer = CManager::GetCRenderer();
	pDevice = renderer->GetDevice();
	VERTEX_2D* pVtx;// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,// (sizeof(VERTEX_2D)*�K�v�Ȓ��_��
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	// ���_�o�b�t�@�����b�N����
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	// rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// ���_�J���[�̐ݒ�@�@�@�@
	pVtx[0].col = D3DXCOLOR(m_col);
	pVtx[1].col = D3DXCOLOR(m_col);
	pVtx[2].col = D3DXCOLOR(m_col);
	pVtx[3].col = D3DXCOLOR(m_col);

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	// ���[�h��ݒ�
	CManager::SetMode(m_modeNext);

	return S_OK;
}

//*****************
// �I������
//*****************
void CFade::Uninit(void)
{
	// ���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}

//*****************
// �X�V����
//*****************
void CFade::Update(void)
{
	VERTEX_2D* pVtx;

	if (m_state != STATE_NONE)
	{
		if (m_state == STATE_IN)
		{// �t�F�[�h�C�����
			// �|���S���𓧖��ɂ��Ă���
			m_col.a -= 0.03f;
			if (m_col.a <= 0.0f)
			{// ���S�ɓ����ɂȂ�����
				m_col.a = 0.0f;
				// �ʏ��Ԃɂ���
				m_state = STATE_NONE;
			}
		}
		else if (m_state == STATE_OUT)
		{// �t�F�[�h�A�E�g���
			m_col.a += 0.03f;
			if (m_col.a >= 1.0f)
			{// ���S�ɕs�����ɂȂ�����
				m_col.a = 1.0f;
				// �t�F�[�h�C����ԂɕύX
				m_state = STATE_IN;
				// ���̉�ʂ̈ڍs
				CManager::SetMode(m_modeNext);
			}
		}

		// ���_�o�b�t�@�����b�N����
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// ���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(m_col);
		pVtx[1].col = D3DXCOLOR(m_col);
		pVtx[2].col = D3DXCOLOR(m_col);
		pVtx[3].col = D3DXCOLOR(m_col);

		// ���_�o�b�t�@���A�����b�N����
		m_pVtxBuff->Unlock();
	}

}

//*****************
// �`�揈��
//*****************
void CFade::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	CRenderer* renderer = CManager::GetCRenderer();
	pDevice = renderer->GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));
	pDevice->SetTexture(0, NULL);
	pDevice->SetTexture(1, NULL);

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//*****************
// �V�[���ݒ�
//*****************
void CFade::Set(CScene::MODE modeNext)
{
	// �t�F�[�h�A�E�g��Ԃ�
	m_state = STATE_OUT;	
	// ���̉�ʂ�ݒ�
	m_modeNext = modeNext;	
}