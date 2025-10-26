//******************************************
//
// X�t�@�C������ [Xmodel.cpp]
// Author:Sasaki Soichiro
//
//******************************************

//*******************
// �C���N���[�h
//*******************
#include "Xmodel.h"
#include "manager.h"
#include "renderer.h"

// �ÓI�����o�ϐ�������
int CXModel::m_nNumAll = 0;

//*****************
// �R���X�g���N�^
//*****************
CXModel::CXModel()
{
	for (int nCnt = 0; nCnt < 256; nCnt++)
	{
		m_apXModel[nCnt].dwNumMat = NULL;
		m_apXModel[nCnt].pBuffMat = NULL;
		m_apXModel[nCnt].pMesh = NULL;
		m_apXModel[nCnt].vtxMax = NONE;
		m_apXModel[nCnt].vtxMin = NONE;
	}
	m_nNumAll++;
}

//*****************
// �f�X�g���N�^
//*****************
CXModel::~CXModel()
{
}

HRESULT CXModel::Load(void)
{

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	CRenderer* renderer = CManager::GetCRenderer();
	pDevice = renderer->GetDevice();
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		////x�t�@�C���̓ǂݍ���
		//D3DXLoadMeshFromX(XFILE[nCnt],
		//	D3DXMESH_SYSTEMMEM,
		//	pDevice,
		//	NULL,
		//	&m_apXModel[nCnt].pBuffMat,
		//	NULL,
		//	&m_apXModel[nCnt].dwNumMat,
		//	&m_apXModel[nCnt].pMesh);
	}

	return S_OK;
}

void CXModel::Unload(void)
{
	// �e�N�X�`���̔j��
	for (int nCnt = 0; nCnt < 256; nCnt++)
	{
		if (m_apXModel[nCnt].pBuffMat != NULL)
		{
			m_apXModel[nCnt].pBuffMat->Release();
			m_apXModel[nCnt].pBuffMat = NULL;
		}
		if (m_apXModel[nCnt].pMesh != NULL)
		{
			m_apXModel[nCnt].pMesh->Release();
			m_apXModel[nCnt].pMesh = NULL;
		}
	}
}

int CXModel::Register(const char* pFilename)
{
	int nCntRegister;
	int nNumVtx;//���_��
	DWORD sizeFVF;//���_�t�H�[�}�b�g�̃T�C�Y
	BYTE* pVtxBuff;//���_�o�b�t�@�ւ̃|�C���^

	for (nCntRegister = 0; nCntRegister < 256; nCntRegister++)
	{
		if (XFILE[nCntRegister].empty() == true)
		{
			if (m_apXModel[nCntRegister].dwNumMat==0
				&& m_apXModel[nCntRegister].pBuffMat == NULL
				&& m_apXModel[nCntRegister].pMesh == NULL)
			{
				// �f�o�C�X�̎擾
				LPDIRECT3DDEVICE9 pDevice;
				CRenderer* renderer = CManager::GetCRenderer();
				pDevice = renderer->GetDevice();
				//x�t�@�C���̓ǂݍ���
				D3DXLoadMeshFromX(pFilename,
					D3DXMESH_SYSTEMMEM,
					pDevice,
					NULL,
					&m_apXModel[nCntRegister].pBuffMat,
					NULL,
					&m_apXModel[nCntRegister].dwNumMat,
					&m_apXModel[nCntRegister].pMesh);
				nNumVtx = m_apXModel[nCntRegister].pMesh->GetNumVertices();
				sizeFVF = D3DXGetFVFVertexSize(m_apXModel[nCntRegister].pMesh->GetFVF());
				//���_�o�b�t�@�̃��b�N
				m_apXModel[nCntRegister].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

				for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
				{
					//���_���W�̑��
					D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

					//���_���W���r���ă��f���̍ŏ��l�ő�l���擾
					//X============================
					if (vtx.x > m_apXModel[nCntRegister].vtxMax.x)
					{
						m_apXModel[nCntRegister].vtxMax.x = vtx.x;
					}

					if (vtx.x < m_apXModel[nCntRegister].vtxMin.x)
					{
						m_apXModel[nCntRegister].vtxMin.x = vtx.x;
					}
					//Y============================
					if (vtx.y > m_apXModel[nCntRegister].vtxMax.y)
					{
						m_apXModel[nCntRegister].vtxMax.y = vtx.y;
					}

					if (vtx.y < m_apXModel[nCntRegister].vtxMin.y)
					{
						m_apXModel[nCntRegister].vtxMin.y = vtx.y;
					}
					//Z=============================
					if (vtx.z > m_apXModel[nCntRegister].vtxMax.z)
					{
						m_apXModel[nCntRegister].vtxMax.z = vtx.z;
					}

					if (vtx.z < m_apXModel[nCntRegister].vtxMin.z)
					{
						m_apXModel[nCntRegister].vtxMin.z = vtx.z;
					}

					//���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
					pVtxBuff += sizeFVF;
				}

				//���_�o�b�t�@�̃A�����b�N
				m_apXModel[nCntRegister].pMesh->UnlockVertexBuffer();
				XFILE[nCntRegister] = pFilename;
				return nCntRegister;
			}
			else
			{
				return -1;
			}
		}

		else if (XFILE[nCntRegister] == pFilename)
		{
			return nCntRegister;
		}
	}
	return -1;
}

CXModel::XMODEL CXModel::GetAddres(int nIdx)
{
	return m_apXModel[nIdx];
}