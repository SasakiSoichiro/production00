//***************************************
// 
// �O�Տ���[orbit.cpp]
// Author:Sasaki Soichiro
// 
//***************************************

//******************
// �C���N���[�h
//******************
#include "orbit.h"
#include "manager.h"
#include <string>
#include <iostream>
#include "json.hpp"
#include "game.h"
#include "renderer.h"
#include "mesh.h"

//****************
// �R���X�g���N�^
//****************
COrbit::COrbit(int nPriority) : CObject(nPriority)
{
	m_pTexture = NULL;						// �e�N�X�`���̃|�C���^
	m_pVtxBuff = NULL;						// ���_�o�b�t�@
	m_pIdxBuff = NULL;						// �C���f�b�N�X�o�b�t�@
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ʒu
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ����
	m_FPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ʒu
	m_SPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ʒu;
	m_mtxWorld = {};						// ���[���h�}�g���b�N�X
	m_Frame = 0;
	for (int nCnt = 0; nCnt < MAX_ORBITVTX / 2 - 1; nCnt++)
	{
		m_oldFPos[nCnt]=D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_oldSPos[nCnt]=D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
	m_Time = 0;
}

//****************
// �f�X�g���N�^
//****************
COrbit::~COrbit()
{

}

//*******************
// �C���X�^���X����
//*******************
COrbit* COrbit::Create(D3DXVECTOR3 pos)
{
	COrbit* pOrbit;
	// �e�N�X�`�����̎擾
	CTexture* pTexture = CManager::GetCTexture();

	// ���݂̃I�u�W�F�N�g�����擾
	int nNum = CObject::GetNumAll();
	if (nNum < MAX_OBJ - 1)
	{// �ő�I�u�W�F�N�g���ɒB���Ă��Ȃ�������

		// �C���X�^���X����
		pOrbit = new COrbit;
		// ������
		pOrbit->Init(pos);

		return pOrbit;
	}

	return NULL;
}

//**************
// ������
//**************
HRESULT COrbit::Init(D3DXVECTOR3 pos)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	CRenderer* renderer = CManager::GetCRenderer();
	pDevice = renderer->GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\orbit.jpg",
		&m_pTexture);

	// ���_�o�b�t�@�̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * VTXCNT,//(sizeof(VERTEX_3D)*�K�v�Ȓ��_��
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);
	// �C���f�b�N�X�o�b�t�@�̍쐬
	pDevice->CreateIndexBuffer(sizeof(VERTEX_3D) * IDXCNT,//(sizeof(VERTEX_3D)*�K�v�Ȓ��_��
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIdxBuff,
		NULL);

	VERTEX_3D* pVtx = 0;//���_���ւ̃|�C���^


	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	int nCC = MAX_ORBITVTX;
	for (int nCnt = 0; nCnt < MAX_ORBITVTX; nCnt++, nCC--)
	{
		pVtx[nCnt].pos = D3DXVECTOR3(408.0f, 1.0f, -3.5f);
		//�e���_�̖@���̐ݒ�
		pVtx[nCnt].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f-(0.07f*nCnt));
	}
	int nCntTEX = 0;
	for (int nCnt = 0; nCnt < MAX_ORBITVTX; nCnt += 2, nCntTEX++)
	{
		pVtx[nCnt + 1].tex = D3DXVECTOR2((1.0f / (MAX_ORBITVTX / 2) * nCntTEX), 0.0f);
		pVtx[nCnt].tex = D3DXVECTOR2((1.0f / (MAX_ORBITVTX / 2) * nCntTEX), 1.0f);
	}

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();


	//�C���f�b�N�X�o�b�t�@�����b�N
	WORD* pIdx;
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);


	for (int nCnt = 0; nCnt < MAX_ORBITVTX; nCnt++)
	{
		pIdx[nCnt] = nCnt;
	}
	for (int nCnt = 0; nCnt < MAX_ORBITVTX / 2 - 1; nCnt++)
	{
		m_oldFPos[nCnt] = D3DXVECTOR3(408.0f, 1.0f, -3.5f);
		m_oldSPos[nCnt] = D3DXVECTOR3(408.0f, 1.0f, -3.5f);
	}
	//���_�o�b�t�@���A�����b�N����
	m_pIdxBuff->Unlock();
	return S_OK;
}

//**************
// �I������
//**************
void COrbit::Uninit(void)
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
void COrbit::Update(void)
{
	VERTEX_3D* pVtx = 0;//���_���ւ̃|�C���^
	//D3DXVECTOR3 posOld[2];
	int nCnt = 0;
	int nCntEX = 0;
	m_Time++;
	m_Frame++;


	if (m_Time >= (MAX_ORBITVTX / 2) - 1)
	{
		m_Time = 0;
	}
	nCntEX = m_Time;
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	m_oldFPos[m_Time] = pVtx[0].pos;
	m_oldSPos[m_Time] = pVtx[1].pos;

	pVtx[0].pos = m_FPos;
	pVtx[1].pos = m_SPos;

	for (int nCntOrbit = 2; nCntOrbit < MAX_ORBITVTX; nCntOrbit += 2, nCnt += 2)
	{

		pVtx[nCntOrbit].pos.x = m_oldFPos[nCntEX].x;
		pVtx[nCntOrbit].pos.y = m_oldFPos[nCntEX].y;
		pVtx[nCntOrbit].pos.z = m_oldFPos[nCntEX].z;

		pVtx[nCntOrbit + 1].pos.x = m_oldSPos[nCntEX].x;
		pVtx[nCntOrbit + 1].pos.y = m_oldSPos[nCntEX].y;
		pVtx[nCntOrbit + 1].pos.z = m_oldSPos[nCntEX].z;

		if (nCntEX <= 0)
		{
			nCntEX = (MAX_ORBITVTX / 2) - 2;
		}
		else
		{
			nCntEX--;
		}
	}


	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//**************
// �`��
//**************
void COrbit::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	CRenderer* renderer = CManager::GetCRenderer();
	pDevice = renderer->GetDevice();

	// �v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;
	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	// ���u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// �����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);
	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));
	// �C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(m_pIdxBuff);
	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);
	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);
	// �|���S���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, MAX_ORBITVTX, 0, 14);

	//���u�����f�B���O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

}

//**************
// �ʒu�̐ݒ�
//**************
void COrbit::SetPosS(D3DXVECTOR3 pos0, D3DXVECTOR3 pos1)
{
	m_FPos = pos0;
	m_SPos = pos1;
}