//**************************************
//
// �r���{�[�h���� [objectBillboard.cpp]
// Author:Sasaki Soichiro
//
//**************************************

//*******************
// �C���N���[�h
//*******************
#include "objectBillboard.h"
#include "manager.h"
#include "renderer.h"

//*******************
// �R���X�g���N�^
//*******************
CObjectBillboard::CObjectBillboard(int nPriority) :CObject(nPriority)
{
	m_pVtxBuff = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR2(0.0f, 0.0f);
	m_offset = D3DXVECTOR2(0.0f, 0.0f);
	m_mtxWorld = {};
}

//*******************
// �f�X�g���N�^
//*******************
CObjectBillboard::~CObjectBillboard()
{

}

//*******************
// ����������
//*******************
HRESULT CObjectBillboard::Init(D3DXVECTOR3 pos)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	CRenderer* renderer = CManager::GetCRenderer();
	pDevice = renderer->GetDevice();

	//�e��ϐ��̏�����
	m_pos = pos;
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);


	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,//(sizeof(VERTEX_3D)*�K�v�Ȓ��_��
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_3D* pVtx = 0;//���_���ւ̃|�C���^

//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(-20.0f+ m_offset.x, 20.0f + m_offset.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(20.0f + m_offset.x, 20.0f + m_offset.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-20.0f + m_offset.x, -20.0f + m_offset.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(20.0f + m_offset.x, -20.0f + m_offset.y, 0.0f);

	//�e���_�̖@���̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

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
	return S_OK;
}

//*******************
// �I������
//*******************
void CObjectBillboard::Uninit(void)
{
	//���_�o�b�t�@�̉��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	CObject::Release();
}

//*******************
// �X�V����
//*******************
void CObjectBillboard::Update(void)
{
}

//*******************
// �`�揈��
//*******************
void CObjectBillboard::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	CRenderer* renderer = CManager::GetCRenderer();
	pDevice = renderer->GetDevice();
	CTexture* pTexture = CManager::GetCTexture();
	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;

	//���C�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�r���[�}�g���b�N�X�擾
	D3DXMATRIX mtxView;
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	//�J�����̋t�s���ݒ�
	m_mtxWorld._11 = mtxView._11;
	m_mtxWorld._12 = mtxView._21;
	m_mtxWorld._13 = mtxView._31;
	m_mtxWorld._21 = mtxView._12;
	m_mtxWorld._22 = mtxView._22;
	m_mtxWorld._23 = mtxView._32;
	m_mtxWorld._31 = mtxView._13;
	m_mtxWorld._32 = mtxView._23;
	m_mtxWorld._33 = mtxView._33;

	// �����𔽉f
	D3DXMatrixRotationZ(&mtxRot, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &mtxRot, &m_mtxWorld);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);
	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));
	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);//for���ɓ����

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);//for���ɓ����

	//���C�g��L���ɖ߂�
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//*******************
// �ʒu�ݒ�
//*******************
void CObjectBillboard::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//*******************
// �����ݒ�
//*******************
void CObjectBillboard::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//*********************
// �e�N�X�`�����W�ݒ�
//*********************
void CObjectBillboard::SetTex(D3DXVECTOR2 uv1, D3DXVECTOR2 uv2, D3DXVECTOR2 uv3, D3DXVECTOR2 uv4)
{
	VERTEX_3D* pVertex;//���_���ւ̃|�C���^
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

//*******************
// �F�ݒ�
//*******************
void CObjectBillboard::SetCol(D3DXCOLOR col)
{
	m_col = col;
	VERTEX_3D* pVertex;//���_���ւ̃|�C���^
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

//*******************
// �傫���ݒ�
//*******************
void CObjectBillboard::SetSize(D3DXVECTOR2 size)
{
	VERTEX_3D* pVtx;//���_���ւ̃|�C���^
	m_size = size;
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-m_size.x + m_offset.x, m_size.y + m_offset.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_size.x + m_offset.x, m_size.y + m_offset.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-m_size.x + m_offset.x, -m_size.y + m_offset.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_size.x + m_offset.x, -m_size.y + m_offset.y, 0.0f);	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

}

//*******************
// �I�t�Z�b�g�̐ݒ�
//*******************
void CObjectBillboard::SetOffset(D3DXVECTOR2 offset)
{
	VERTEX_3D* pVtx;//���_���ւ̃|�C���^
	m_offset = offset;
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-m_size.x + m_offset.x, m_size.y + m_offset.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_size.x + m_offset.x, m_size.y + m_offset.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-m_size.x + m_offset.x, -m_size.y + m_offset.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_size.x + m_offset.x, -m_size.y + m_offset.y, 0.0f);	
	m_pVtxBuff->Unlock();

}