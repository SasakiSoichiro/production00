//**********************************
//
// �I�u�W�F�N�g3D���� [object3D.cpp]
// Author:Sasaki Soichiro
//
//**********************************

//*******************
// �C���N���[�h
//*******************
#include "object3D.h"
#include "manager.h"
#include "renderer.h"


CObject3D::CObject3D(int nPriority) : CObject(nPriority)
{
	m_pTexture = NULL;
	m_pVtxBuff = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_mtxWorld = {};
}
CObject3D::~CObject3D()
{

}
CObject3D* CObject3D::Create(D3DXVECTOR3 pos)
{
	CObject3D* pObject3D;
	CTexture* pTexture = CManager::GetCTexture();

	int nNum = CObject::GetNumAll();
	if (nNum < MAX_OBJ - 1)
	{
		pObject3D = new CObject3D;
		pObject3D->Init(pos);
		return pObject3D;
	}
	return NULL;
}

HRESULT CObject3D::Init(D3DXVECTOR3 pos)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	CRenderer* renderer = CManager::GetCRenderer();
	pDevice = renderer->GetDevice();
	D3DXVECTOR3 vec0, vec1, nor0, nor1;

	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,//(sizeof(VERTEX_3D)*�K�v�Ȓ��_��
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_3D* pVtx = 0;//���_���ւ̃|�C���^

//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̍X�V
	pVtx[0].pos.x =  - 150.0f;
	pVtx[0].pos.y;
	pVtx[0].pos.z =  + 150.0f;
	pVtx[1].pos.x =  + 150.0f;
	pVtx[1].pos.y;
	pVtx[1].pos.z =  + 150.0f;
	pVtx[2].pos.x =  - 150.0f;
	pVtx[2].pos.y;
	pVtx[2].pos.z =  - 150.0f;
	pVtx[3].pos.x =  + 150.0f;
	pVtx[3].pos.y;
	pVtx[3].pos.z =  - 150.0f;


	vec0 = pVtx[1].pos - pVtx[0].pos;
	vec1 = pVtx[2].pos - pVtx[0].pos;
	D3DXVec3Cross(&nor0, &vec0, &vec1);
	D3DXVec3Normalize(&nor0, &nor0);
	pVtx[0].nor = nor0;
	vec0 = pVtx[1].pos - pVtx[3].pos;
	vec1 = pVtx[2].pos - pVtx[3].pos;
	D3DXVec3Cross(&nor1, &vec0, &vec1);
	D3DXVec3Normalize(&nor1, &nor1);
	pVtx[3].nor = nor1;
	pVtx[1].nor = nor0 + nor1 / 2.0f;
	pVtx[2].nor = nor0 + nor1 / 2.0f;


	//���_�J���[�̐ݒ�@�@�@�@
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	m_pos = pos;

	return S_OK;
}

void CObject3D::Uninit(void)
{
	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	CObject::Release();
}
void CObject3D::Update(void)
{

}
void CObject3D::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	CRenderer* renderer = CManager::GetCRenderer();
	pDevice = renderer->GetDevice();

	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;
	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);
	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);
	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));
	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);
	pDevice->SetTexture(1, NULL);
	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);
	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

void CObject3D::SetSize(D3DXVECTOR2 size)
{
	VERTEX_3D* pVtx = 0;//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	////���_���W�̍X�V
	pVtx[0].pos.x =  - (size.x * 0.5f);
	pVtx[0].pos.y;
	pVtx[0].pos.z =  + (size.y * 0.5f);
	pVtx[1].pos.x =  + (size.x * 0.5f);
	pVtx[1].pos.y;
	pVtx[1].pos.z =  + (size.y * 0.5f);
	pVtx[2].pos.x =  - (size.x * 0.5f);
	pVtx[2].pos.y;
	pVtx[2].pos.z =  - (size.y * 0.5f);
	pVtx[3].pos.x =  + (size.x * 0.5f);
	pVtx[3].pos.y;
	pVtx[3].pos.z =  - (size.y * 0.5f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

}

void CObject3D::SetCol(D3DXCOLOR col)
{
	VERTEX_3D* pVtx = 0;//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].col = col;
	pVtx[1].col = col;
	pVtx[2].col = col;
	pVtx[3].col = col;

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

void CObject3D::SetTex(D3DXVECTOR2 uv1, D3DXVECTOR2 uv2)
{

	VERTEX_3D* pVtx = 0;//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(uv1.x, uv1.y);
	pVtx[1].tex = D3DXVECTOR2(uv2.x, uv1.y);
	pVtx[2].tex = D3DXVECTOR2(uv1.x, uv2.y);
	pVtx[3].tex = D3DXVECTOR2(uv2.x, uv2.y);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

}


float CObject3D::GetHeight(D3DXVECTOR3 pos)
{
	VERTEX_3D* pVtx = 0;//���_���ւ̃|�C���^
	D3DXVECTOR3 nor,vtx0,norP[6];
	float fHeight=0.0f;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	D3DXVECTOR3 vec1, vec2;
	// 1�|���S����
	vec1 = pVtx[1].pos - pVtx[0].pos;
	vec2 = pos - pVtx[0].pos;
	D3DXVec3Cross(&norP[0], &vec1, &vec2);

	vec1 = pVtx[2].pos - pVtx[1].pos;
	vec2 = pos - pVtx[1].pos;
	D3DXVec3Cross(&norP[1], &vec1, &vec2);

	vec1 = pVtx[0].pos - pVtx[2].pos;
	vec2 = pos - pVtx[2].pos;
	D3DXVec3Cross(&norP[2], &vec1, &vec2);

	// 2�|���S����
	vec1 = pVtx[3].pos - pVtx[2].pos;
	vec2 = pos - pVtx[2].pos;
	D3DXVec3Cross(&norP[3], &vec1, &vec2);

	vec1 = pVtx[2].pos - pVtx[1].pos;
	vec2 = pos - pVtx[1].pos;
	D3DXVec3Cross(&norP[4], &vec1, &vec2);

	vec1 = pVtx[1].pos - pVtx[3].pos;
	vec2 = pos - pVtx[3].pos;
	D3DXVec3Cross(&norP[5], &vec1, &vec2);

	if (0.0f < norP[0].y
		&& 0.0f < norP[1].y
		&& 0.0f < norP[2].y)
	{
		//���_�J���[�̐ݒ�@�@�@�@
		pVtx[0].col = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);
		nor = pVtx[0].nor;
		vtx0 = pVtx[0].pos;
		fHeight = vtx0.y -((pos.x - vtx0.x) * nor.x + (pos.z - vtx0.z) * nor.z)/nor.y;
	}
	else if (0.0f > norP[3].y
		&& 0.0f > norP[4].y
		&& 0.0f > norP[5].y)
	{
		//���_�J���[�̐ݒ�@�@�@�@
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		nor = pVtx[3].nor;
		vtx0 = pVtx[3].pos;
		fHeight = vtx0.y - ((pos.x - vtx0.x) * nor.x + (pos.z - vtx0.z) * nor.z) / nor.y;
	}
	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	
	if (fHeight > 0.0f)
	{
		return fHeight;
	}
	return 0.0f;
}

void CObject3D::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}