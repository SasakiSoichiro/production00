//**********************************
//
// X�t�@�C������ [objectX.cpp]
// Author:Sasaki Soichiro
//
//**********************************

//*******************
// �C���N���[�h
//*******************
#include "objectX.h"
#include "manager.h"
#include "texture.h"
#include "renderer.h"

//=================
// �R���X�g���N�^
//=================
CObjectX::CObjectX(int nPriority) :CObject(nPriority)
{
	m_XModel.pMesh=NULL;
	m_XModel.pBuffMat=NULL;
	m_XModel.dwNumMat = NULL;
	m_mtxWorld = {};
	m_pVtxBuff = NULL;	// ���_���̃|�C���^
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ʒu
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// ����
	for (int nCnt = 0; nCnt < 128; nCnt++)
	{
		m_nIdxTexture[nCnt] = -1;
	}
}

//=================
// �f�X�g���N�^
//=================
CObjectX::~CObjectX()
{
}

CObjectX* CObjectX::Create(D3DXVECTOR3 pos)
{
	CObjectX* pCObjectX;
	CTexture* pTexture = CManager::GetCTexture();

	int nNum = CObject::GetNumAll();
	if (nNum < MAX_OBJ - 1)
	{
		pCObjectX = new CObjectX;
		pCObjectX->Init(pos);
		return pCObjectX;
	}
	return NULL;
}

//����������
HRESULT CObjectX::Init(D3DXVECTOR3 pos)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	CRenderer* renderer = CManager::GetCRenderer();
	pDevice = renderer->GetDevice();

	//�e��ϐ��̏�����
	m_pos = pos;
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(1.0f, 1.0f, 1.0f);


	D3DXMATERIAL* pMat;//�}�e���A���ւ̃|�C���^

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)m_XModel.pBuffMat->GetBufferPointer();
	CTexture* pTexture = CManager::GetCTexture();

	for (int nCntMat = 0; nCntMat < (int)m_XModel.dwNumMat; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{//�e�N�X�`���t�@�C�������݂���
				//�e�N�X�`���̓ǂݍ���
			m_nIdxTexture[nCntMat] = pTexture->Register(pMat[nCntMat].pTextureFilename);
		}
	}
	return TRUE;
}
void CObjectX::Uninit(void)
{
	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	CObject::Release();

}
void CObjectX::Update(void)
{

}
void CObjectX::Draw(void)
{
	CTexture* pTexture = CManager::GetCTexture();

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	CRenderer* renderer = CManager::GetCRenderer();
	pDevice = renderer->GetDevice();

	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;
	//���݂̃}�e���A���̕ۑ��p
	D3DMATERIAL9 matDef;//���݂̃}�e���A���̕ۑ��p
	D3DXMATERIAL* pMat;//�}�e���A���f�[�^�ւ̃|�C���^
	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	// �傫���𔽉f
	D3DXMatrixScaling(&mtxTrans, m_size.x, m_size.y, m_size.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	pDevice->GetMaterial(&matDef);
	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)m_XModel.pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_XModel.dwNumMat; nCntMat++)
	{
		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		if (m_nIdxTexture[nCntMat] != -1)
		{
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, pTexture->GetAddres(m_nIdxTexture[nCntMat]));
		}
		else
		{
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, NULL);
		}
		//���f���i�p�[�c�j�̕`��
		m_XModel.pMesh->DrawSubset(nCntMat);
	}
	pDevice->SetMaterial(&matDef);

}

void CObjectX::BindXFile(CXModel::XMODEL pXFile)
{
	m_XModel = pXFile;
}
