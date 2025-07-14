//=============================================================================
//
// �I�u�W�F�N�g2D���� [object2D.cpp]
// Author Sasaki Soichiro
//
//=============================================================================

//*******************
// �C���N���[�h
//*******************
#include "object2DMulti.h"
#include "renderer.h"
#include "manager.h"

//*******************
// �}�N����`
//*******************
#define OBJ_HEIGHT (150.0f)
#define OBJ_WIDTH (250.0f)

//=================
// �R���X�g���N�^
//=================
CObject2DMulti::CObject2DMulti(int nPriority) :CObject(nPriority)
{
	m_pTexture[0] = NULL;
	m_pTexture[1] = NULL;
	m_pVtxBuff = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR2(0.0f, 0.0f);
	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
}

//=================
// �f�X�g���N�^
//=================
CObject2DMulti::~CObject2DMulti()
{
}

//=================
// ����������
//=================
HRESULT CObject2DMulti::Init(D3DXVECTOR3 pos)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	CRenderer* renderer = CManager::GetCRenderer();
	pDevice = renderer->GetDevice();
	m_pos = pos;
	float fAngle = atan2f(m_size.x, m_size.y);
	VERTEX_2D_MULTI* pVertex;//���_���ւ̃|�C���^
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D_MULTI) * 4,//(sizeof(VERTEX_2D_MULTI)*�K�v�Ȓ��_��
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D_MULTI,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVertex, 0);

	//���_���W�̐ݒ�
	pVertex[0].pos = D3DXVECTOR3(m_pos.x + sinf(m_rot.z + (-D3DX_PI + fAngle)) * m_size.x, m_pos.y + cosf(m_rot.z + (-D3DX_PI + fAngle)) * m_size.y, 0.0f);//���E���Őݒ肷��
	pVertex[1].pos = D3DXVECTOR3(m_pos.x + sinf(m_rot.z + (D3DX_PI - fAngle)) * m_size.x, m_pos.y + cosf(m_rot.z + (D3DX_PI - fAngle)) * m_size.y, 0.0f);
	pVertex[2].pos = D3DXVECTOR3(m_pos.x + sinf(m_rot.z - fAngle) * m_size.x, m_pos.y + cosf(m_rot.z - fAngle) * m_size.y, 0.0f);
	pVertex[3].pos = D3DXVECTOR3(m_pos.x + sinf(m_rot.z + fAngle) * m_size.x, m_pos.y + cosf(m_rot.z + fAngle) * m_size.y, 0.0f);

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
// �I������
//=================
void CObject2DMulti::Uninit(void)
{
	//// �e�N�X�`���̔j��
	//if (m_pTexture != NULL)
	//{
	//	//m_pTexture->Release();
	//	m_pTexture = NULL;
	//}
	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	CObject::Release();
}

//=================
// �X�V����
//=================
void CObject2DMulti::Update(void)
{
}

//=================
// �`�揈��
//=================
void CObject2DMulti::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	CRenderer* renderer = CManager::GetCRenderer();
	pDevice = renderer->GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D_MULTI));
	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D_MULTI);
	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture[0]);
	pDevice->SetTexture(1, m_pTexture[1]);
	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	pDevice->SetTexture(1, NULL);
}
void CObject2DMulti::SetPos(D3DXVECTOR3 pos)
{
	VERTEX_2D_MULTI* pVertex;//���_���ւ̃|�C���^
	m_pos = pos;
	float fRength = sqrtf(m_size.x * m_size.x + m_size.y * m_size.y) / 2.0f;
	float fAngle = atan2f(m_size.x, m_size.y);
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVertex, 0);
	//���_���W�̐ݒ�
	pVertex[0].pos = D3DXVECTOR3(m_pos.x + sinf(m_rot.z + (-D3DX_PI + fAngle)) * fRength, m_pos.y + cosf(m_rot.z + (-D3DX_PI + fAngle)) * fRength, 0.0f);//���E���Őݒ肷��
	pVertex[1].pos = D3DXVECTOR3(m_pos.x + sinf(m_rot.z + (D3DX_PI - fAngle)) * fRength, m_pos.y + cosf(m_rot.z + (D3DX_PI - fAngle)) * fRength, 0.0f);
	pVertex[2].pos = D3DXVECTOR3(m_pos.x + sinf(m_rot.z - fAngle) * fRength, m_pos.y + cosf(m_rot.z - fAngle) * fRength, 0.0f);
	pVertex[3].pos = D3DXVECTOR3(m_pos.x + sinf(m_rot.z + fAngle) * fRength, m_pos.y + cosf(m_rot.z + fAngle) * fRength, 0.0f);
	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

void CObject2DMulti::SetRot(D3DXVECTOR3 rot)
{
	VERTEX_2D_MULTI* pVertex;//���_���ւ̃|�C���^
	m_rot = rot;
	float fRength = sqrtf(m_size.x * m_size.x + m_size.y * m_size.y) / 2.0f;
	float fAngle = atan2f(m_size.x, m_size.y);
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVertex, 0);
	//���_���W�̐ݒ�
	pVertex[0].pos = D3DXVECTOR3(m_pos.x + sinf(m_rot.z + (-D3DX_PI + fAngle)) * fRength, m_pos.y + cosf(m_rot.z + (-D3DX_PI + fAngle)) * fRength, 0.0f);//���E���Őݒ肷��
	pVertex[1].pos = D3DXVECTOR3(m_pos.x + sinf(m_rot.z + (D3DX_PI - fAngle)) * fRength, m_pos.y + cosf(m_rot.z + (D3DX_PI - fAngle)) * fRength, 0.0f);
	pVertex[2].pos = D3DXVECTOR3(m_pos.x + sinf(m_rot.z - fAngle) * fRength, m_pos.y + cosf(m_rot.z - fAngle) * fRength, 0.0f);
	pVertex[3].pos = D3DXVECTOR3(m_pos.x + sinf(m_rot.z + fAngle) * fRength, m_pos.y + cosf(m_rot.z + fAngle) * fRength, 0.0f);
	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}
void CObject2DMulti::SetTex(D3DXVECTOR2 uv1, D3DXVECTOR2 uv2, D3DXVECTOR2 uv3, D3DXVECTOR2 uv4)
{
	VERTEX_2D_MULTI* pVertex;//���_���ւ̃|�C���^
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVertex, 0);
	//���_���W�̐ݒ�
	pVertex[0].tex = uv1;
	pVertex[1].tex = uv2;
	pVertex[2].tex = uv3;
	pVertex[3].tex = uv4;
	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

void CObject2DMulti::SetTex2(D3DXVECTOR2 uv1, D3DXVECTOR2 uv2, D3DXVECTOR2 uv3, D3DXVECTOR2 uv4)
{
	VERTEX_2D_MULTI* pVertex;//���_���ւ̃|�C���^
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVertex, 0);
	//���_���W�̐ݒ�
	pVertex[0].texM = uv1;
	pVertex[1].texM = uv2;
	pVertex[2].texM = uv3;
	pVertex[3].texM = uv4;
	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

void CObject2DMulti::SetCol(D3DXCOLOR col)
{
	m_col = col;
	VERTEX_2D_MULTI* pVertex;//���_���ւ̃|�C���^
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVertex, 0);
	//���_���W�̐ݒ�
	pVertex[0].col = col;
	pVertex[1].col = col;
	pVertex[2].col = col;
	pVertex[3].col = col;
	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

void CObject2DMulti::SetSize(D3DXVECTOR2 size)
{
	VERTEX_2D_MULTI* pVertex;//���_���ւ̃|�C���^
	m_size = size;
	float fRength = sqrtf(m_size.x * m_size.x + m_size.y * m_size.y) / 2.0f;
	float fAngle = atan2f(m_size.x, m_size.y);
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVertex, 0);
	//���_���W�̐ݒ�
	pVertex[0].pos = D3DXVECTOR3(m_pos.x + sinf(m_rot.z + (-D3DX_PI + fAngle)) * fRength, m_pos.y + cosf(m_rot.z + (-D3DX_PI + fAngle)) * fRength, 0.0f);//���E���Őݒ肷��
	pVertex[1].pos = D3DXVECTOR3(m_pos.x + sinf(m_rot.z + (D3DX_PI - fAngle)) * fRength, m_pos.y + cosf(m_rot.z + (D3DX_PI - fAngle)) * fRength, 0.0f);
	pVertex[2].pos = D3DXVECTOR3(m_pos.x + sinf(m_rot.z - fAngle) * fRength, m_pos.y + cosf(m_rot.z - fAngle) * fRength, 0.0f);
	pVertex[3].pos = D3DXVECTOR3(m_pos.x + sinf(m_rot.z + fAngle) * fRength, m_pos.y + cosf(m_rot.z + fAngle) * fRength, 0.0f);
	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

}


void CObject2DMulti::BindTexture(LPDIRECT3DTEXTURE9 pTexture0, LPDIRECT3DTEXTURE9 pTexture1)
{
	m_pTexture[0] = pTexture0;
	m_pTexture[1] = pTexture1;
}