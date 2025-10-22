//***************************************
// 
// ���[���̉�������[railmesh.cpp]
// Author:Sasaki Soichiro
// 
//***************************************

//******************
// �C���N���[�h
//******************
#include "railmesh.h"
#include "manager.h"
#include "game.h"
#include "renderer.h"
#include "mesh.h"
#include "input.h"

//****************
// �R���X�g���N�^
//****************
CRailMesh::CRailMesh(int nPriority) : CObject(nPriority)
{
	m_pTexture = NULL;						// �e�N�X�`���̃|�C���^
	m_pVtxBuff = NULL;						// ���_�o�b�t�@
	m_pIdxBuff = NULL;						// �C���f�b�N�X�o�b�t�@
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ʒu
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ����
	m_nNumVtx = 0;
	m_nNumIdx = 0;
}

//****************
// �f�X�g���N�^
//****************
CRailMesh::~CRailMesh()
{

}

//*******************
// �C���X�^���X����
//*******************
CRailMesh* CRailMesh::Create(D3DXVECTOR3 pos, int nType)
{
	CRailMesh* pOrbit;// ���b�V�����擾
	CTexture* pTexture = CManager::GetCTexture();// �e�N�X�`�����̎擾

	// ���݂̃I�u�W�F�N�g�����擾
	int nNum = CObject::GetNumAll();
	if (nNum < MAX_OBJ - 1)
	{// �ő�I�u�W�F�N�g���ɒB���Ă��Ȃ�������

		// �C���X�^���X����
		pOrbit = new CRailMesh;
		pOrbit->m_nType = nType;
		// ������
		pOrbit->Init(pos);
		// pOrbit��n��
		return pOrbit;
	}

	//(���s������)NULL��Ԃ�
	return NULL;
}

//**************
// ������
//**************
HRESULT CRailMesh::Init(D3DXVECTOR3 pos)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	CRenderer* renderer = CManager::GetCRenderer();
	pDevice = renderer->GetDevice();
	switch (m_nType)
	{
	case 0:
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,
			"data\\TEXTURE\\gameclear.png",
			&m_pTexture);

		break;
	case 1:
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,
			"data\\TEXTURE\\gameover.png",
			&m_pTexture);

		break;
	}

	// ���_�o�b�t�@�̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * VTXCNT,	// (sizeof(VERTEX_3D)*�K�v�Ȓ��_��
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	// �C���f�b�N�X�o�b�t�@�̍쐬
	pDevice->CreateIndexBuffer(sizeof(VERTEX_3D) * IDXCNT,	// (sizeof(VERTEX_3D)*�K�v�Ȓ��_��
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIdxBuff,
		NULL);

	m_nNumVtx = 4;
	m_nNumIdx = 4;

	VERTEX_3D* pVtx = 0;//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = pos;
	pVtx[1].pos = pos;
	pVtx[2].pos = pos;
	pVtx[3].pos = pos;
	for (int nCnt = 0; nCnt < VTXCNT; nCnt++)
	{
		pVtx[nCnt].pos = pos;
	}


	for (int nCnt = 0; nCnt < m_nNumVtx; nCnt++)
	{
		pVtx[nCnt].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();


	//�C���f�b�N�X�o�b�t�@�����b�N
	WORD* pIdx;
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);


	for (int nCnt = 0; nCnt < m_nNumIdx; nCnt++)
	{
		pIdx[nCnt] = nCnt;
	}

	//���_�o�b�t�@���A�����b�N����
	m_pIdxBuff->Unlock();
	return S_OK;
}

//**************
// �I������
//**************
void CRailMesh::Uninit(void)
{
	//�e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}

	//���_�o�b�t�@�̉��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	//�C���f�b�N�X�o�b�t�@�̉��
	if (m_pIdxBuff != NULL)
	{
		m_pIdxBuff->Release();
		m_pIdxBuff = NULL;
	}
	CObject::Release();
}

//**************
// �X�V
//**************
void CRailMesh::Update(void)
{

}

//**************
// �`��
//**************
void CRailMesh::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	CRenderer* renderer = CManager::GetCRenderer();
	pDevice = renderer->GetDevice();

	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;
	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	pDevice->SetRenderState(D3DRS_CULLMODE, TRUE);

	//���u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);
	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));
	//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(m_pIdxBuff);
	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);
	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);
	//�|���S���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, m_nNumVtx, 0, m_nNumVtx-2);

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	//���u�����f�B���O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

}

//*****************
// ���_�̒ǉ�
//*****************
void CRailMesh::Add(D3DXVECTOR3 pos0, D3DXVECTOR3 pos1)
{
	VERTEX_3D* pVtx = 0;//���_���ւ̃|�C���^

	m_nNumVtx += 2;
	m_nNumIdx += 2;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[m_nNumVtx-1].pos = pos0;
	pVtx[m_nNumVtx].pos = pos1;

	for (int nCnt = m_nNumVtx-2; nCnt < m_nNumVtx; nCnt++)
	{
		pVtx[nCnt].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}
	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();


	//�C���f�b�N�X�o�b�t�@�����b�N
	WORD* pIdx;
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);


	for (int nCnt = m_nNumIdx-2; nCnt < m_nNumIdx; nCnt++)
	{
		pIdx[nCnt] = nCnt;
	}

	//���_�o�b�t�@���A�����b�N����
	m_pIdxBuff->Unlock();

}

//*******************
// ���_�ʒu�̐ݒ�
//*******************
void CRailMesh::SetVtxPos(D3DXVECTOR3 pos, int nCnt)
{

	VERTEX_3D* pVtx = 0;// ���_���ւ̃|�C���^

	bool bVtx = nCnt >= 0 && nCnt < m_nNumVtx;
	
	if (bVtx)
	{// nCnt���͈͓���������

		// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		pVtx[nCnt].pos = pos;

		// ���_�o�b�t�@���A�����b�N����
		m_pVtxBuff->Unlock();
	}
}
