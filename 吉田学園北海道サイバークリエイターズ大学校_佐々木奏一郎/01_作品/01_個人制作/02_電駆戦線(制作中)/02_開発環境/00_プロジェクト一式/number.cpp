//**********************************
//
// �i���o�[���� [number.cpp]
// Author:Sasaki Soichiro
//
//**********************************

//*******************
// �C���N���[�h
//*******************
#include "number.h"
#include "manager.h"

//================
// �R���X�g���N�^
//================
CNumber::CNumber()
{
	m_pVtxBuff = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR2(0.0f, 0.0f);
	nNum = 0;
}
//================
// �f�X�g���N�^
//================
CNumber::~CNumber()
{
}

//================
// ������
//================
HRESULT CNumber::Init(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	CRenderer* renderer = CManager::GetCRenderer();
	pDevice = renderer->GetDevice();
	VERTEX_2D* pVertex;//���_���ւ̃|�C���^
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,//(sizeof(VERTEX_2D)*�K�v�Ȓ��_��
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVertex, 0);

	//���_���W�̐ݒ�
	pVertex[0].pos = D3DXVECTOR3(m_pos.x - (m_size.x / 2.0f), m_pos.y - (m_size.y / 2.0f), 0.0f);//���E���Őݒ肷��
	pVertex[1].pos = D3DXVECTOR3(m_pos.x + (m_size.x / 2.0f), m_pos.y - (m_size.y / 2.0f), 0.0f);
	pVertex[2].pos = D3DXVECTOR3(m_pos.x - (m_size.x / 2.0f), m_pos.y + (m_size.y / 2.0f), 0.0f);
	pVertex[3].pos = D3DXVECTOR3(m_pos.x + (m_size.x / 2.0f), m_pos.y + (m_size.y / 2.0f), 0.0f);

	//rhw�̐ݒ�
	pVertex[0].rhw = 1.0f;
	pVertex[1].rhw = 1.0f;
	pVertex[2].rhw = 1.0f;
	pVertex[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�@�@�@�@
	pVertex[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVertex[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVertex[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVertex[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	return S_OK;
}

//=================
// �`�揈��
//=================
void CNumber::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	CRenderer* renderer = CManager::GetCRenderer();
	pDevice = renderer->GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));
	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

}

//================
// �I��
//================
void CNumber::Uninit(void)
{
	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}

//================
// �����̐ݒ�
//================
void CNumber::SetNumber(int nNum)
{
	VERTEX_2D* pVertex;//���_���ւ̃|�C���^
	float fData = 0.1f;
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVertex, 0);

	pVertex[0].tex = D3DXVECTOR2(nNum * fData,0.0f);
	pVertex[1].tex = D3DXVECTOR2(fData + nNum * fData, 0.0f);
	pVertex[2].tex = D3DXVECTOR2(nNum * fData, 1.0f);
	pVertex[3].tex = D3DXVECTOR2(fData + nNum * fData, 1.0f);
	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

}

//================
// �ʒu�̐ݒ�
//================
void CNumber::SetPos(D3DXVECTOR3 pos)
{
	VERTEX_2D* pVertex;//���_���ւ̃|�C���^
	m_pos = pos;
	float fRength = sqrtf(m_size.x * m_size.x + m_size.y * m_size.y) / 2.0f;
	float fAngle = atan2f(m_size.x, m_size.y);
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVertex, 0);
	//���_���W�̐ݒ�
	//���_���W�̐ݒ�
	pVertex[0].pos = D3DXVECTOR3(m_pos.x - (m_size.x / 2.0f), m_pos.y - (m_size.y / 2.0f), 0.0f);//���E���Őݒ肷��
	pVertex[1].pos = D3DXVECTOR3(m_pos.x + (m_size.x / 2.0f), m_pos.y - (m_size.y / 2.0f), 0.0f);
	pVertex[2].pos = D3DXVECTOR3(m_pos.x - (m_size.x / 2.0f), m_pos.y + (m_size.y / 2.0f), 0.0f);
	pVertex[3].pos = D3DXVECTOR3(m_pos.x + (m_size.x / 2.0f), m_pos.y + (m_size.y / 2.0f), 0.0f);
	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//================
// �傫���̐ݒ�
//================
void CNumber::SetSize(D3DXVECTOR2 size)
{
	VERTEX_2D* pVertex;//���_���ւ̃|�C���^
	m_size = size;
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVertex, 0);
	//���_���W�̐ݒ�
	//���_���W�̐ݒ�
	pVertex[0].pos = D3DXVECTOR3(m_pos.x - (m_size.x / 2.0f), m_pos.y - (m_size.y / 2.0f), 0.0f);//���E���Őݒ肷��
	pVertex[1].pos = D3DXVECTOR3(m_pos.x + (m_size.x / 2.0f), m_pos.y - (m_size.y / 2.0f), 0.0f);
	pVertex[2].pos = D3DXVECTOR3(m_pos.x - (m_size.x / 2.0f), m_pos.y + (m_size.y / 2.0f), 0.0f);
	pVertex[3].pos = D3DXVECTOR3(m_pos.x + (m_size.x / 2.0f), m_pos.y + (m_size.y / 2.0f), 0.0f);
	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

}

//================
// �R���X�g���N�^
//================
CSymbol::CSymbol()
{
	m_pTexture = NULL;
	m_pVtxBuff = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR2(0.0f, 0.0f);
}
//================
// �f�X�g���N�^
//================
CSymbol::~CSymbol()
{
}

//================
// ������
//================
HRESULT CSymbol::Init(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	CRenderer* renderer = CManager::GetCRenderer();
	pDevice = renderer->GetDevice();
	VERTEX_2D* pVertex;//���_���ւ̃|�C���^
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,//(sizeof(VERTEX_2D)*�K�v�Ȓ��_��
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVertex, 0);

	//���_���W�̐ݒ�
	pVertex[0].pos = D3DXVECTOR3(m_pos.x - (m_size.x / 2.0f), m_pos.y - (m_size.y / 2.0f), 0.0f);//���E���Őݒ肷��
	pVertex[1].pos = D3DXVECTOR3(m_pos.x + (m_size.x / 2.0f), m_pos.y - (m_size.y / 2.0f), 0.0f);
	pVertex[2].pos = D3DXVECTOR3(m_pos.x - (m_size.x / 2.0f), m_pos.y + (m_size.y / 2.0f), 0.0f);
	pVertex[3].pos = D3DXVECTOR3(m_pos.x + (m_size.x / 2.0f), m_pos.y + (m_size.y / 2.0f), 0.0f);

	//rhw�̐ݒ�
	pVertex[0].rhw = 1.0f;
	pVertex[1].rhw = 1.0f;
	pVertex[2].rhw = 1.0f;
	pVertex[3].rhw = 1.0f;

	pVertex[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVertex[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVertex[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVertex[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�J���[�̐ݒ�@�@�@�@
	pVertex[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVertex[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVertex[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVertex[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	return S_OK;
}

//=================
// �`�揈��
//=================
void CSymbol::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	CRenderer* renderer = CManager::GetCRenderer();
	pDevice = renderer->GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));
	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

}

//================
// �I��
//================
void CSymbol::Uninit(void)
{
	// �e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}

//================
// �ʒu�̐ݒ�
//================
void CSymbol::SetPos(D3DXVECTOR3 pos)
{
	VERTEX_2D* pVertex;//���_���ւ̃|�C���^
	m_pos = pos;
	float fRength = sqrtf(m_size.x * m_size.x + m_size.y * m_size.y) / 2.0f;
	float fAngle = atan2f(m_size.x, m_size.y);
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVertex, 0);
	//���_���W�̐ݒ�
	pVertex[0].pos = D3DXVECTOR3(m_pos.x - (m_size.x / 2.0f), m_pos.y - (m_size.y / 2.0f), 0.0f);//���E���Őݒ肷��
	pVertex[1].pos = D3DXVECTOR3(m_pos.x + (m_size.x / 2.0f), m_pos.y - (m_size.y / 2.0f), 0.0f);
	pVertex[2].pos = D3DXVECTOR3(m_pos.x - (m_size.x / 2.0f), m_pos.y + (m_size.y / 2.0f), 0.0f);
	pVertex[3].pos = D3DXVECTOR3(m_pos.x + (m_size.x / 2.0f), m_pos.y + (m_size.y / 2.0f), 0.0f);
	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//================
// �傫���̐ݒ�
//================
void CSymbol::SetSize(D3DXVECTOR2 size)
{
	VERTEX_2D* pVertex;//���_���ւ̃|�C���^
	m_size = size;
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVertex, 0);
	//���_���W�̐ݒ�
	//���_���W�̐ݒ�
	pVertex[0].pos = D3DXVECTOR3(m_pos.x - (m_size.x / 2.0f), m_pos.y - (m_size.y / 2.0f), 0.0f);//���E���Őݒ肷��
	pVertex[1].pos = D3DXVECTOR3(m_pos.x + (m_size.x / 2.0f), m_pos.y - (m_size.y / 2.0f), 0.0f);
	pVertex[2].pos = D3DXVECTOR3(m_pos.x - (m_size.x / 2.0f), m_pos.y + (m_size.y / 2.0f), 0.0f);
	pVertex[3].pos = D3DXVECTOR3(m_pos.x + (m_size.x / 2.0f), m_pos.y + (m_size.y / 2.0f), 0.0f);
	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

}

//======================
// �e�N�X�`���̊��蓖��
//======================
void CSymbol::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}