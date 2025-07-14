//***************************************
// 
// ���b�V���t�B�[���h����[mesh.cpp]
// Author:Sasaki Soichiro
// 
//***************************************

//******************
// �C���N���[�h
//******************
#include "model.h"
#include "manager.h"


//*****************
// �R���X�g���N�^
//*****************
CModel::CModel()
{
	m_pos = D3DXVECTOR3{ 0.0f,0.0f,0.0f };
	m_rot = D3DXVECTOR3{ 0.0f,0.0f,0.0f };
	m_nIdxXFile = 0;
	m_pParent = NULL;
	m_mtxWorld = {};
	m_pXModel = {};
	
}

//=================
// �f�X�g���N�^
//=================
CModel::~CModel()
{
}

//=================
// ����������
//=================
void CModel::Init(D3DXVECTOR3 pos)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	CRenderer* renderer = CManager::GetCRenderer();
	CXModel* pXModel = CManager::GetCXModel();
	pDevice = renderer->GetDevice();

	//x�t�@�C���̓ǂݍ���
	m_pXModel = pXModel->GetAddres(m_nIdxXFile);
	m_pos = pos;
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//=================
// �I������
//=================
void CModel::Uninit(void)
{
}

//=================
// �X�V����
//=================
void CModel::Update(void)
{

}

//=================
// �`�揈��
//=================
void CModel::Draw(void)
{
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
	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	D3DXMATRIX mtxParent;// �e�̃}�g���b�N�X
	if (m_pParent != NULL)
	{// �e�����݂���
		// �e�̃}�g���b�N�X���擾����
		mtxParent = m_pParent->GetMtxWorld();
	}
	else
	{// �e�����݂��Ȃ�
		// ����(�ŐV)�̃}�g���b�N�X���擾����[=�v���C���[�̃}�g���b�N�X]
		pDevice->GetTransform(D3DTS_WORLD, &mtxParent);
	}
	// �e�̃}�g���b�N�X�Ɗ|�����킹��
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxParent);
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);
	pDevice->GetMaterial(&matDef);
	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)m_pXModel.pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_pXModel.dwNumMat; nCntMat++)
	{
		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		////�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, NULL);

		//���f���i�p�[�c�j�̕`��
		m_pXModel.pMesh->DrawSubset(nCntMat);
	}
	pDevice->SetMaterial(&matDef);

}

CModel* CModel::Create(D3DXVECTOR3 pos,const char*pFileName)
{
	CModel* pModel;
	CXModel* pXModel = CManager::GetCXModel();
	int nNum = CObject::GetNumAll();
	if (nNum < MAX_OBJ - 1)
	{
		pModel = new CModel;
		pModel->m_nIdxXFile = pXModel->Register(pFileName);
		pModel->Init(pos);
		return pModel;
	}
	return NULL;
}
//****************
// �e�̐ݒ�
//****************
void CModel::SetParent(CModel* pModel)
{
	m_pParent = pModel;
}

//************************
// �}�g���b�N�X���̎擾
//************************
D3DXMATRIX CModel::GetMtxWorld()
{
	return m_mtxWorld;
}