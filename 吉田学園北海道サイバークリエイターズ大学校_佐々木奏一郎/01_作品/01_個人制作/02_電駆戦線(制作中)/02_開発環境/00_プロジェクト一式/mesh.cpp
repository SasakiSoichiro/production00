//***************************************
// 
// ���b�V���t�B�[���h����[mesh.cpp]
// Author:Sasaki Soichiro
// 
//***************************************

//******************
// �C���N���[�h
//******************
#include "mesh.h"
#include "manager.h"
#include <string>
#include <iostream>
#include "json.hpp"

using json = nlohmann::json;

//*****************
// �}�N����`
//*****************
#define CALDERA_SIZE (400.0f)
#define ONEFLAME_SIZE (0.012f)

int g_nTime;
float f;

//****************
// �R���X�g���N�^
//****************
CMesh::CMesh(int nPriority) : CObject(nPriority)
{
	m_pTexture = NULL;						// �e�N�X�`���̃|�C���^
	m_pVtxBuff = NULL;						// ���_�o�b�t�@
	m_pIdxBuff = NULL;						// �C���f�b�N�X�o�b�t�@
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ʒu
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ����
	m_mtxWorld = {};						// ���[���h�}�g���b�N�X
}

//****************
// �f�X�g���N�^
//****************
CMesh::~CMesh()
{

}

//*******************
// �C���X�^���X����
//*******************
CMesh* CMesh::Create(D3DXVECTOR3 pos)
{
	CMesh* pMesh;// ���b�V�����擾
	CTexture* pTexture = CManager::GetCTexture();// �e�N�X�`�����̎擾

	// ���݂̃I�u�W�F�N�g�����擾
	int nNum = CObject::GetNumAll();
	if (nNum < MAX_OBJ - 1)
	{// �ő�I�u�W�F�N�g���ɒB���Ă��Ȃ�������

		// �C���X�^���X����
		pMesh = new CMesh;
		// ������
		pMesh->Init(pos);
		// pMesh��n��
		return pMesh;
	}

	//(���s������)NULL��Ԃ�
	return NULL;
}

//**************
// ������
//**************
HRESULT CMesh::Init(D3DXVECTOR3 pos)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	CRenderer* renderer = CManager::GetCRenderer();
	pDevice = renderer->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\field.jpg",
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

	// �J�E���g�p�ϐ�
	int nCntPOS = 0;
	float Xmesh = (float)(XMESH);
	float Zmesh = (float)(ZMESH);

	// ���_�o�b�t�@�̐ݒ�
	for (int nCntZ = 0; nCntZ < ZMESH + 1; nCntZ++)
	{
		for (int nCntX = 0; nCntX < XMESH + 1; nCntX++, nCntPOS++)
		{
			float Angle = ((D3DX_PI * 0.5f) / XMESH * nCntX);
			pVtx[nCntPOS].pos = D3DXVECTOR3(((OBJ_X * 2) / Xmesh) * nCntX - OBJ_X, 1.0f, (-1 * ((OBJ_Z * 2) / Zmesh) * nCntZ + OBJ_Z));
			//pVtx[nCntPOS].pos = D3DXVECTOR3(((OBJ_X * 2) / Xmesh) * nCntX - OBJ_X, (-sinf(Angle)*radius)+radius, (-1 * ((OBJ_Z * 2) / Zmesh) * nCntZ + OBJ_Z));

		}
	}


	for (int nCnt = 0; nCnt < VTXCNT; nCnt++)
	{//�e���_�̖@���̐ݒ�
		pVtx[nCnt].nor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}

	// �J�E���g�p�ϐ�
	int nCntTEX = 0;
	for (int nCntZ = 0; nCntZ < ZMESH + 1; nCntZ++)
	{
		for (int nCntX = 0; nCntX < XMESH + 1; nCntX++, nCntTEX++)
		{
			pVtx[nCntTEX].tex = D3DXVECTOR2((1.0f / Xmesh) * nCntX, ((1.0f / Zmesh) * nCntZ));
		}
	}


	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	//�C���f�b�N�X�o�b�t�@�����b�N
	WORD* pIdx;
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	// �J�E���g�p�ϐ�
	int nCntX=0;
	int nCnt = 0;
	std::vector<int> A(IDXCNT, 0);
	std::vector<int> B(IDXCNT, 0);

	for (nCnt = 0; nCnt < IDXCNT; nCnt++, nCntX++)
	{
		if (nCnt == 0)
		{
			A[nCnt] = (2 * XMESH) + 3;
			B[nCnt] = -XMESH - 1;
			pIdx[nCnt] = XMESH + 1;
		}
		else
		{
			A[nCnt] = -1 * (A[nCnt - 1]);

			B[nCnt] = B[nCnt - 1] + A[nCnt - 1];


			if (nCntX == 2 * (XMESH + 1))
			{
				pIdx[nCnt] = pIdx[nCnt - 1];
			}

			else if (nCntX == 2 * (XMESH + 1) + 1)
			{
				pIdx[nCnt] = pIdx[nCnt - 2] + B[nCnt - 2];
			}

			else if (nCntX == 2 * (XMESH + 1) + 2)
			{
				nCntX = 0;

				pIdx[nCnt] = pIdx[nCnt - 1];
			}

			else
			{
				pIdx[nCnt] = pIdx[nCnt - 1] + B[nCnt - 1];
			}

		}

	}

	//���_�o�b�t�@���A�����b�N����
	m_pIdxBuff->Unlock();
	// ���[�h
	Load();
	f = CALDERA_SIZE;
	return S_OK;
}

//**************
// �I������
//**************
void CMesh::Uninit(void)
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
void CMesh::Update(void)
{
	VERTEX_3D* pVtx = 0;//���_���ւ̃|�C���^

	// �J�E���g�p�ϐ�
	int nCntPOS = 0;
	float Xmesh = (float)(XMESH);
	float Zmesh = (float)(ZMESH);
	D3DXVECTOR3 vec1, vec2,norAnswer,nor[4];
	D3DXVECTOR3 NOR = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �@���̍X�V
	for (int nCntZ = 0; nCntZ < ZMESH + 1; nCntZ++)
	{
		for (int nCntX = 0; nCntX < XMESH + 1; nCntX++, nCntPOS++)
		{
			if (nCntZ == 0)
			{// Z�̃J�E���g��0��������
				if (nCntX == 0)
				{// X�̃J�E���g��0��������(�p�̒��_)
					// �@���v�Z���
					pVtx[nCntPOS].nor =	VtxNor(	pVtx[nCntPOS].pos,				// �Ώۂ̒��_���W
												pVtx[nCntPOS + 1].pos,			// �אڂ̒��_���W1
												pVtx[nCntPOS + XMESH + 1].pos);	// �אڂ̒��_���W2
				}
				else if (nCntX == XMESH)
				{// X�̃J�E���g���Ōゾ������(�p�̒��_)
					// �@���v�Z���
					pVtx[nCntPOS].nor = VtxNor(	pVtx[nCntPOS].pos,				// �Ώۂ̒��_���W
												pVtx[nCntPOS + XMESH + 1].pos,	// �אڂ̒��_���W1
												pVtx[nCntPOS  - 1].pos);		// �אڂ̒��_���W2
				}
				else
				{// ����ȊO(�ӂ̒��_)
					nor[0] = VtxNor(pVtx[nCntPOS].pos,				// �Ώۂ̒��_���W
									pVtx[nCntPOS + 1].pos,			// �אڂ̒��_���W1
									pVtx[nCntPOS + XMESH + 1].pos);	// �אڂ̒��_���W2

					nor[1] = VtxNor(pVtx[nCntPOS].pos,				// �Ώۂ̒��_���W
									pVtx[nCntPOS + XMESH + 1].pos,	// �אڂ̒��_���W1
									pVtx[nCntPOS - 1].pos);			// �אڂ̒��_���W2

					norAnswer = (nor[0] + nor[1]) / 2.0f;
					D3DXVec3Normalize(&norAnswer, &norAnswer);
					pVtx[nCntPOS].nor = norAnswer;
				}
			}
			else if (nCntZ == ZMESH)
			{// Z�̃J�E���g���Ōゾ������
				if (nCntX == 0)
				{// X�̃J�E���g��0��������
					// �@���v�Z���
					pVtx[nCntPOS].nor = VtxNor(	pVtx[nCntPOS].pos,				// �Ώۂ̒��_���W
												pVtx[nCntPOS - XMESH - 1].pos,	// �אڂ̒��_���W1
												pVtx[nCntPOS + 1].pos);			// �אڂ̒��_���W2
				}
				else if (nCntX == XMESH)
				{// X�̃J�E���g���Ōゾ������
					pVtx[nCntPOS].nor = VtxNor(	pVtx[nCntPOS].pos,				// �Ώۂ̒��_���W
												pVtx[nCntPOS - 1].pos,			// �אڂ̒��_���W1
												pVtx[nCntPOS - XMESH - 1].pos);	// �אڂ̒��_���W2
				}
				else
				{// ����ȊO
					nor[0] = VtxNor(pVtx[nCntPOS].pos,				// �Ώۂ̒��_���W
									pVtx[nCntPOS - XMESH - 1].pos,	// �אڂ̒��_���W1
									pVtx[nCntPOS + 1].pos);			// �אڂ̒��_���W2
					nor[1] = VtxNor(pVtx[nCntPOS].pos,				// �Ώۂ̒��_���W
									pVtx[nCntPOS - 1].pos,			// �אڂ̒��_���W1
									pVtx[nCntPOS - XMESH - 1].pos);	// �אڂ̒��_���W2
					norAnswer = (nor[0] + nor[1]) / 2.0f;
					D3DXVec3Normalize(&norAnswer, &norAnswer);
					pVtx[nCntPOS].nor = norAnswer;
				}
			}
			else if (nCntX == 0)
			{// X�̃J�E���g��0��������
				vec1 = pVtx[nCntPOS + 1].pos - pVtx[nCntPOS].pos;
				vec2 = pVtx[nCntPOS + XMESH + 1].pos - pVtx[nCntPOS].pos;
				D3DXVec3Cross(&nor[0], &vec1, &vec2);
				vec1 = pVtx[nCntPOS - XMESH - 1].pos - pVtx[nCntPOS].pos;
				vec2 = pVtx[nCntPOS + 1].pos - pVtx[nCntPOS].pos;
				D3DXVec3Cross(&nor[1], &vec1, &vec2);
				norAnswer = (nor[0] + nor[1]) / 2.0f;
				D3DXVec3Normalize(&norAnswer, &norAnswer);
				pVtx[nCntPOS].nor = norAnswer;
			}
			else if (nCntX == XMESH)
			{// X�̃J�E���g��0��������
				vec1 = pVtx[nCntPOS - 1].pos - pVtx[nCntPOS].pos;
				vec2 = pVtx[nCntPOS - XMESH - 1].pos - pVtx[nCntPOS].pos;
				D3DXVec3Cross(&nor[0], &vec1, &vec2);
				vec1 = pVtx[nCntPOS + XMESH + 1].pos - pVtx[nCntPOS].pos;
				vec2 = pVtx[nCntPOS - 1].pos - pVtx[nCntPOS].pos;
				D3DXVec3Cross(&nor[1], &vec1, &vec2);
				norAnswer = (nor[0] + nor[1]) / 2.0f;
				D3DXVec3Normalize(&norAnswer, &norAnswer);
				pVtx[nCntPOS].nor = norAnswer;
			}
			else
			{// ����ȊO
				vec1 = pVtx[nCntPOS + 1].pos - pVtx[nCntPOS].pos;
				vec2 = pVtx[nCntPOS + XMESH + 1].pos - pVtx[nCntPOS].pos;
				D3DXVec3Cross(&nor[0], &vec1, &vec2);
				vec1 = pVtx[nCntPOS - XMESH - 1].pos - pVtx[nCntPOS].pos;
				vec2 = pVtx[nCntPOS + 1].pos - pVtx[nCntPOS].pos;
				D3DXVec3Cross(&nor[1], &vec1, &vec2);
				vec1 = pVtx[nCntPOS - 1].pos - pVtx[nCntPOS].pos;
				vec2 = pVtx[nCntPOS - XMESH - 1].pos - pVtx[nCntPOS].pos;
				D3DXVec3Cross(&nor[2], &vec1, &vec2);
				vec1 = pVtx[nCntPOS + XMESH + 1].pos - pVtx[nCntPOS].pos;
				vec2 = pVtx[nCntPOS - 1].pos - pVtx[nCntPOS].pos;
				D3DXVec3Cross(&nor[3], &vec1, &vec2);
				norAnswer = (nor[0] + nor[1]+nor[2]+nor[3]+ NOR) / 5.0f;
				D3DXVec3Normalize(&norAnswer, &norAnswer);
				pVtx[nCntPOS].nor = norAnswer;
			}
		}
	}
	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
	{
		//VERTEX_3D* pVtx = 0;//���_���ւ̃|�C���^

		//D3DXVECTOR2 uv;
		//D3DXVECTOR2 uv2;
		//float distance;
		//D3DXVECTOR2 s;
		//s.x = 12.0f;
		//s.y = 13.0f;
		//D3DXVECTOR2 ss;
		//ss.x = 23.0f;
		//ss.y = 21.0f;
		//float f = sqrtf((s.x * ss.x) + (s.y * ss.y));
		//D3DXVec2Scale(&ss, &ss, 5);
		//D3DXVec2Scale(&s, &s, 5);
		//float ff = sqrtf((s.x * ss.x) + (s.y * ss.y));


		////���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		//m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		//int nCntPOS = 0;

		//float Xmesh = (float)(XMESH);
		//float Zmesh = (float)(ZMESH);
		//for (int nCntZ = 0; nCntZ < ZMESH + 1; nCntZ++)
		//{
		//	//uv�̒lY���W���傫���Ȃ�ɂ��0.0f�`1.0f�ɂȂ�
		//	uv.y = 1.0f / ZMESH * nCntZ;

		//	for (int nCntX = 0; nCntX < XMESH + 1; nCntX++, nCntPOS++)
		//	{
		//		//uv�̒lX���W���傫���Ȃ�ɂ��0.0f�`1.0f�ɂȂ�
		//		uv.x = 1.0f / XMESH * nCntX;
		//		uv2.x = (uv.x - 0.5f) * 2.0f;
		//		uv2.y = (uv.y - 0.5f) * 2.0f;
		//		//uv2.x *= 2.0f;
		//		//uv2.y *= 2.0f;

		//		//uv2.x = uv2.x-float(floor(uv2.x));
		//		//uv2.y = uv2.y-float(floor(uv2.y));

		//		//uv2.x -= 0.5f;
		//		//uv2.y -= 0.5f;
		//		uv2.x = fabsf(uv2.x);
		//		uv2.y = fabsf(uv2.y);
		//		distance = sqrtf(((uv2.x) * (uv2.x)) + ((uv2.y) * (uv2.y)));

		//		distance = sinf(distance * 10.0f - float(g_nTime) * 0.05f) * (1.0f - distance) * 0.5f;

		//		distance = fabsf(distance);

		//		if (distance > 1.0f)
		//		{
		//			distance = 1.0f;
		//		}

		//		pVtx[nCntPOS].pos = D3DXVECTOR3(((OBJ_X * 2) / Xmesh) * nCntX - OBJ_X, distance * 200.0f, (-1 * ((OBJ_Z * 2) / Zmesh) * nCntZ + OBJ_Z));
		//		pVtx[nCntPOS].col = D3DXCOLOR(0.8f, 0.8f, distance + 0.1f, 1.0f);
		//	}
		//}
		////���_�o�b�t�@���A�����b�N����
		//m_pVtxBuff->Unlock();

		//g_nTime++;
	}
}

//**************
// �`��
//**************
void CMesh::Draw(void)
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
	//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(m_pIdxBuff);
	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);
	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);
	//�|���S���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, VTXCNT, 0, POLYCNT);
}

//**************
// �������
//**************
float CMesh::GetHeight(D3DXVECTOR3 pos)
{
	// �L�[�{�[�h�̎擾
	CInputKeyboard* pInputKeyboard;
	pInputKeyboard = CManager::GetCInputKeyboard();
	// �v���C���[���擾
	CPlayer* pPlayer = CManager::GetCPlayer();

	// �v�Z�p�ϐ�
	float sizeX, sizeZ;
	float posX,posZ;
	int nCount,a, b;
	D3DXVECTOR3 nor, vtx0, norP[6], vec1, vec2;
	float fHeight = 0.0f;

	sizeX = (OBJ_X*2) / XMESH;
	sizeZ = (OBJ_Z*2) / ZMESH;
	posX = pos.x + OBJ_X;
	posZ = pos.z - OBJ_Z;
	b = (int)(posZ / -sizeZ);
	a = (int)((posX +b*OBJ_X*2) / sizeX);
	nCount = (int)(a + b);
	CDebugProc::Print("\n���݂̃��b�V��%d\n", nCount);


	VERTEX_3D* pVtx = 0;//���_���ւ̃|�C���^

	if (nCount >= 0 && nCount <= (XMESH + 1) * (ZMESH + 1))
	{
		//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
		// 1�|���S����
		vec1 = pVtx[nCount + 1].pos - pVtx[nCount].pos;
		vec2 = pos - pVtx[nCount].pos;
		D3DXVec3Cross(&norP[0], &vec1, &vec2);

		vec1 = pVtx[nCount + XMESH + 2].pos - pVtx[nCount + 1].pos;
		vec2 = pos - pVtx[nCount + 1].pos;
		D3DXVec3Cross(&norP[1], &vec1, &vec2);

		vec1 = pVtx[nCount].pos - pVtx[nCount + XMESH + 2].pos;
		vec2 = pos - pVtx[nCount + XMESH + 2].pos;
		D3DXVec3Cross(&norP[2], &vec1, &vec2);

		// 2�|���S����
		vec1 = pVtx[nCount + XMESH + 2].pos - pVtx[nCount + XMESH + 1].pos;
		vec2 = pos - pVtx[nCount + XMESH + 1].pos;
		D3DXVec3Cross(&norP[3], &vec1, &vec2);

		vec1 = pVtx[nCount + XMESH + 1].pos - pVtx[nCount].pos;
		vec2 = pos - pVtx[nCount].pos;
		D3DXVec3Cross(&norP[4], &vec1, &vec2);

		vec1 = pVtx[nCount].pos - pVtx[nCount + XMESH + 2].pos;
		vec2 = pos - pVtx[nCount + XMESH + 2].pos;
		D3DXVec3Cross(&norP[5], &vec1, &vec2);

		if (0.0f < norP[0].y
			&& 0.0f < norP[1].y
			&& 0.0f < norP[2].y)
		{
			vec1 = pVtx[nCount].pos - pVtx[nCount + 1].pos;
			vec2 = pVtx[nCount + XMESH + 2].pos - pVtx[nCount + 1].pos;
			D3DXVec3Cross(&nor, &vec1, &vec2);
			D3DXVec3Normalize(&nor, &nor);
			
			vtx0 = pVtx[nCount + 1].pos;
			fHeight = vtx0.y - ((pos.x - vtx0.x) * nor.x + (pos.z - vtx0.z) * nor.z) / nor.y;
		}
		else if (0.0f > norP[3].y
			&& 0.0f > norP[4].y
			&& 0.0f > norP[5].y)
		{
			if (pInputKeyboard->GetPress(DIK_SPACE) == true)
			{
				pVtx[nCount].pos.y -= 0.4f;
				pVtx[nCount + XMESH + 1].pos.y -= 0.4f;
				pVtx[nCount + XMESH + 2].pos.y -= 0.4f;
			}
			vec1 = pVtx[nCount].pos - pVtx[nCount + XMESH + 1].pos;
			vec2 = pVtx[nCount + XMESH + 2].pos - pVtx[nCount + XMESH + 1].pos;
			D3DXVec3Cross(&nor, &vec1, &vec2);
			D3DXVec3Normalize(&nor, &nor);
			vtx0 = pVtx[nCount + XMESH + 1].pos;
			fHeight = vtx0.y - ((pos.x - vtx0.x) * nor.x + (pos.z - vtx0.z) * nor.z) / nor.y;
		}
		else
		{
			fHeight = 0.0f;
		}

		//���_�o�b�t�@���A�����b�N����
		m_pVtxBuff->Unlock();
	}
	return fHeight;
}

//***************
// �@���̏��
//***************
D3DXVECTOR3 CMesh::GetNormal(D3DXVECTOR3 pos)
{
	// �L�[�{�[�h�̎擾
	CInputKeyboard* pInputKeyboard;
	pInputKeyboard = CManager::GetCInputKeyboard();
	// �v���C���[���擾
	CPlayer* pPlayer = CManager::GetCPlayer();

	// �v�Z�p�ϐ�
	float sizeX, sizeZ;
	float posX, posZ;
	int nCount, a, b;
	D3DXVECTOR3 nor, vtx0, norP[6], vec1, vec2;
	float fHeight = 0.0f;

	sizeX = (OBJ_X * 2) / XMESH;
	sizeZ = (OBJ_Z * 2) / ZMESH;
	posX = pos.x + OBJ_X;
	posZ = pos.z - OBJ_Z;
	b = (int)(posZ / -sizeZ);
	a = (int)((posX + b * OBJ_X * 2) / sizeX);
	nCount = (int)(a + b);
	CDebugProc::Print("\n���݂̃��b�V��%d\n", nCount);


	VERTEX_3D* pVtx = 0;//���_���ւ̃|�C���^

	if (nCount >= 0 && nCount <= (XMESH + 1) * (ZMESH + 1))
	{
		//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
		// 1�|���S����
		vec1 = pVtx[nCount + 1].pos - pVtx[nCount].pos;
		vec2 = pos - pVtx[nCount].pos;
		D3DXVec3Cross(&norP[0], &vec1, &vec2);

		vec1 = pVtx[nCount + XMESH + 2].pos - pVtx[nCount + 1].pos;
		vec2 = pos - pVtx[nCount + 1].pos;
		D3DXVec3Cross(&norP[1], &vec1, &vec2);

		vec1 = pVtx[nCount].pos - pVtx[nCount + XMESH + 2].pos;
		vec2 = pos - pVtx[nCount + XMESH + 2].pos;
		D3DXVec3Cross(&norP[2], &vec1, &vec2);

		// 2�|���S����
		vec1 = pVtx[nCount + XMESH + 2].pos - pVtx[nCount + XMESH + 1].pos;
		vec2 = pos - pVtx[nCount + XMESH + 1].pos;
		D3DXVec3Cross(&norP[3], &vec1, &vec2);

		vec1 = pVtx[nCount + XMESH + 1].pos - pVtx[nCount].pos;
		vec2 = pos - pVtx[nCount].pos;
		D3DXVec3Cross(&norP[4], &vec1, &vec2);

		vec1 = pVtx[nCount].pos - pVtx[nCount + XMESH + 2].pos;
		vec2 = pos - pVtx[nCount + XMESH + 2].pos;
		D3DXVec3Cross(&norP[5], &vec1, &vec2);

		if (0.0f < norP[0].y
			&& 0.0f < norP[1].y
			&& 0.0f < norP[2].y)
		{
			vec1 = pVtx[nCount].pos - pVtx[nCount + 1].pos;
			vec2 = pVtx[nCount + XMESH + 2].pos - pVtx[nCount + 1].pos;
			D3DXVec3Cross(&nor, &vec2, &vec1);
			D3DXVec3Normalize(&nor, &nor);
			return nor;
		}
		else if (0.0f > norP[3].y
			&& 0.0f > norP[4].y
			&& 0.0f > norP[5].y)
		{
			vec1 = pVtx[nCount].pos - pVtx[nCount + XMESH + 1].pos;
			vec2 = pVtx[nCount + XMESH + 2].pos - pVtx[nCount + XMESH + 1].pos;
			D3DXVec3Cross(&nor, &vec1, &vec2);
			D3DXVec3Normalize(&nor, &nor);
			return nor;
		}
		else
		{
			return D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		}

		//���_�o�b�t�@���A�����b�N����
		m_pVtxBuff->Unlock();
	}
	return D3DXVECTOR3(0.0f, 1.0f, 0.0f);
}

void CMesh::MoveY(D3DXVECTOR3 pos)
{
	VERTEX_3D* pVtx = 0;// ���_���ւ̃|�C���^
	D3DXVECTOR2 pPos = D3DXVECTOR2(pos.x, pos.z);
	int nCntPOS = 0;
	float Xmesh = (float)(XMESH);
	float Zmesh = (float)(ZMESH);
	if (0.0f < f)
	{
		f -= ONEFLAME_SIZE * g_nTime;
	}
	g_nTime++;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntZ = 0; nCntZ < ZMESH + 1; nCntZ++)
	{
		for (int nCntX = 0; nCntX < XMESH + 1; nCntX++, nCntPOS++)
		{
			D3DXVECTOR2 vPos =D3DXVECTOR2(pVtx[nCntPOS].pos.x, pVtx[nCntPOS].pos.z);
			float a = vPos.x - pPos.x;
			float b = vPos.y - pPos.y;
			float distance = sqrtf((a * a) + (b * b));
			if (f > distance)
			{
				pVtx[nCntPOS].pos.y -= 0.8f;
			}
		}
	}

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//*******************
// �n�`�Z�[�u
//*******************
void CMesh::Save(const std::vector<int>& nNum, const std::string& FileName)
{
	// �ۑ�����t�@�C�����J��
	std::ofstream outFile("data\\output.txt");
	if (!outFile)
	{// �J���Ȃ������ꍇ
		return;
	}

	// �����_�ȉ����ۑ�����
	outFile << std::fixed << std::setprecision(2); 

	VERTEX_3D* pVtx = 0;// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < VTXCNT; nCnt++)
	{// ���_�������[�v����
		// �ʒu�E�@����ۑ�
		float posX = pVtx[nCnt].pos.x, posY = pVtx[nCnt].pos.y, posZ = pVtx[nCnt].pos.z;
		float norX = pVtx[nCnt].nor.x, norY = pVtx[nCnt].nor.y, norZ = pVtx[nCnt].nor.z;

		outFile << "vtx" << nCnt << ":"								// ���_�ԍ�
			<< "pos = " << posX << " " << posY << " " << posZ<<" "	// �ʒu
			<< "nor = " << norX << " " << norY << " " << norZ		// �@��
			<< std::endl;											// �s�I���
	}

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
	
	// �t�@�C���𖾎��I�ɕ���
	outFile.close();
}

//*************
// �n�`���[�h
//*************
void CMesh::Load(void)
{
	std::ifstream file("data\\output.txt");
	if (file.is_open() == false)
	{
		return;
	}
	std::string line;
	VERTEX_3D* pVtx;//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	int index = 0;
	int nCnt = 0;
	while (std::getline(file, line))
	{
		int scan=sscanf(line.c_str(),
			"vtx %d:pos = %f %f %f nor = %f %f %f",
			&index, &pVtx[nCnt].pos.x, &pVtx[nCnt].pos.y, &pVtx[nCnt].pos.z,
			&pVtx[nCnt].nor.x, &pVtx[nCnt].nor.y, &pVtx[nCnt].nor.z);
		nCnt++;
	}
	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	// �t�@�C���𖾎��I�ɕ���
	file.close();
}

//*****************
// ���_�̖@���v�Z
//*****************
D3DXVECTOR3 CMesh::VtxNor(D3DXVECTOR3 pos0, D3DXVECTOR3 pos1, D3DXVECTOR3 pos2)
{
	D3DXVECTOR3 vec1, vec2, nor;

	// �x�N�g��1�̌v�Z
	vec1 = pos1 - pos0;
	// �x�N�g��2�̌v�Z
	vec2 = pos2 - pos0;
	// �O�ςŖ@�������߂�
	D3DXVec3Cross(&nor, &vec1, &vec2);
	// �m�[�}���C�Y
	D3DXVec3Normalize(&nor, &nor);

	// �v�Z���ʂ�n��
	return nor;
}