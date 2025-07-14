//****************************************
//
// �I�u�W�F�N�g2D���� [object2D.cpp]
// Author:Sasaki Soichiro
//
//****************************************

//*******************
// �C���N���[�h
//*******************
#include "object2D.h"
#include "renderer.h"
#include "manager.h"

//*******************
// �}�N����`
//*******************
#define OBJ_HEIGHT (150.0f) // �I�u�W�F�N�g�̍���
#define OBJ_WIDTH (250.0f)	// �I�u�W�F�N�g�̕�

//*******************
// �R���X�g���N�^
//*******************
CObject2D::CObject2D(int nPriority):CObject(nPriority)
{
	//m_pTexture = NULL;
	m_pVtxBuff = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR2(0.0f, 0.0f);
	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
}

//*******************
// �f�X�g���N�^
//*******************
CObject2D::~CObject2D()
{
}

//**************
// ����������
//**************
HRESULT CObject2D::Init(D3DXVECTOR3 pos)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	CRenderer* renderer = CManager::GetCRenderer();
	pDevice = renderer->GetDevice();
	m_pos = pos;
	float fAngle = atan2f(m_size.x, m_size.y);
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
	pVertex[0].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
	pVertex[1].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
	pVertex[2].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
	pVertex[3].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	return S_OK;

}

//**************
// �I������
//**************
void CObject2D::Uninit(void)
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

//**************
// �X�V����
//**************
void CObject2D::Update(void)
{
}

//**************
// �`�揈��
//**************
void CObject2D::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	CRenderer* renderer = CManager::GetCRenderer();
	pDevice = renderer->GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));
	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	//�e�N�X�`���̐ݒ�
	//pDevice->SetTexture(0, m_pTexture);
	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

}

//**************
// �ʒu�ݒ�
//**************
void CObject2D::SetPos(D3DXVECTOR3 pos)
{
	VERTEX_2D* pVertex;//���_���ւ̃|�C���^
	m_pos = pos;
	float fRength = sqrtf(m_size.x * m_size.x + m_size.y * m_size.y)/2.0f;
	float fAngle= atan2f(m_size.x, m_size.y);
//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVertex, 0);
	//���_���W�̐ݒ�
	pVertex[0].pos = D3DXVECTOR3(m_pos.x + sinf(m_rot.z + (-D3DX_PI+fAngle)) * fRength, m_pos.y + cosf(m_rot.z + (-D3DX_PI + fAngle)) * fRength, 0.0f);//���E���Őݒ肷��
	pVertex[1].pos = D3DXVECTOR3(m_pos.x + sinf(m_rot.z + (D3DX_PI - fAngle)) * fRength, m_pos.y + cosf(m_rot.z + (D3DX_PI - fAngle)) * fRength, 0.0f);
	pVertex[2].pos = D3DXVECTOR3(m_pos.x + sinf(m_rot.z - fAngle) * fRength, m_pos.y + cosf(m_rot.z - fAngle) * fRength, 0.0f);
	pVertex[3].pos = D3DXVECTOR3(m_pos.x + sinf(m_rot.z + fAngle) * fRength, m_pos.y + cosf(m_rot.z + fAngle)* fRength, 0.0f);
	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//**************
// �����̐ݒ�
//**************
void CObject2D::SetRot(D3DXVECTOR3 rot)
{
	VERTEX_2D* pVertex;//���_���ւ̃|�C���^
	m_rot=rot;
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

//**************
// UV���W�̐ݒ�
//**************
void CObject2D::SetTex(D3DXVECTOR2 uv1, D3DXVECTOR2 uv2, D3DXVECTOR2 uv3, D3DXVECTOR2 uv4)
{
	VERTEX_2D* pVertex;//���_���ւ̃|�C���^
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

//**************
// �F�̐ݒ�
//**************
void CObject2D::SetCol(D3DXCOLOR col)
{
	m_col = col;
	VERTEX_2D* pVertex;//���_���ւ̃|�C���^
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

//**************
// �傫���̐ݒ�
//**************
void CObject2D::SetSize(D3DXVECTOR2 size)
{
	VERTEX_2D* pVertex;//���_���ւ̃|�C���^
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


//void CObject2D::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
//{
//	m_pTexture = pTexture;
//}
//CObject2D*CObject2D::Create(void)
//{
//	CObject2D* pObject2D;
//	pObject2D = new CObject2D;
//	pObject2D->Init();
//	return pObject2D;
//}