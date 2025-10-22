//***************************************
// 
// �e����[shadowS.cpp]
// Author:Sasaki Soichiro
// 
//***************************************

//******************
// �C���N���[�h
//******************
#include "shadowS.h"
#include "manager.h"
#include "renderer.h"

//****************
// �R���X�g���N�^
//****************
CShadowS::CShadowS(int nPriority) : CObjectX(nPriority)
{
	m_pVtxBuff = NULL;						// ���_�o�b�t�@
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ʒu
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ����
	m_nIdxXFile = 0;
}

//****************
// �f�X�g���N�^
//****************
CShadowS::~CShadowS()
{

}

//*******************
// �C���X�^���X����
//*******************
CShadowS* CShadowS::Create(D3DXVECTOR3 pos)
{
	CShadowS* pMesh;// ���b�V�����擾
	CTexture* pTexture = CManager::GetCTexture();// �e�N�X�`�����̎擾

	// ���݂̃I�u�W�F�N�g�����擾
	int nNum = CObject::GetNumAll();
	if (nNum < MAX_OBJ - 1)
	{// �ő�I�u�W�F�N�g���ɒB���Ă��Ȃ�������

		// �C���X�^���X����
		pMesh = new CShadowS;
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
HRESULT CShadowS::Init(D3DXVECTOR3 pos)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	CRenderer* renderer = CManager::GetCRenderer();
	pDevice = renderer->GetDevice();


	// CXModel�̃|�C���^�ɏ�������
	CXModel* pXModel = CManager::GetCXModel();
	// �g�����f���̃C���f�b�N�X������
	m_nIdxXFile = pXModel->Register("data\\MODEL\\shadow.x");
	// X�t�@�C�������蓖�Ă�
	BindXFile(pXModel->GetAddres(m_nIdxXFile));

	// ������
	CObjectX::Init(pos);

	VERTEX_2D* pVtx;//���_���ւ̃|�C���^

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,//(sizeof(VERTEX_2D)*�K�v�Ȓ��_��
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-0.5f, -0.5f, 0.0f);//���E���Őݒ肷��
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH - 0.5f, -0.5f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-0.5f, SCREEN_HEIGHT - 0.5f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH - 0.5f, SCREEN_HEIGHT - 0.5f, 0.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;
	//���_�J���[�̐ݒ�@�@�@�@
	pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.6f);
	pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.6f);
	pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.6f);
	pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.6f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();



	return S_OK;
}

//**************
// �I������
//**************
void CShadowS::Uninit(void)
{
	//���_�o�b�t�@�̉��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	// �I������
	CObjectX::Uninit();
}

//**************
// �X�V
//**************
void CShadowS::Update(void)
{

}

//**************
// �`��
//**************
void CShadowS::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	CRenderer* renderer = CManager::GetCRenderer();
	pDevice = renderer->GetDevice();

	// �X�e���V���e�X�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);
	// Z�o�b�t�@�̏������݂𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	// �J���[�o�b�t�@�ւ̏������݂𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0x00000000);

	// �X�e���V���o�b�t�@�̔�r�p�����[�^��ݒ�
	pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_KEEP);		// �X:���i�@Z:���i
	pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_INCRSAT);	// �X:���i�@Z:�s���i
	pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_INCRSAT);	// �X:�s���i

	// �\�ʂ��J�����O
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);				// �J�����O�̐ݒ�

	 //�e���f����`��
	CObjectX::Draw();

	// �X�e���V���o�b�t�@�̎Q�ƒl��ݒ�("1"�ɂ���)
	pDevice->SetRenderState(D3DRS_STENCILREF, 0x01);
	//�X�e���V���o�b�t�@�̔�r�p�����[�^��ݒ�
	pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);
	pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_INCRSAT);	// �X:���i�@Z:���i
	pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);		// �X:���i�@Z:�s���i
	pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);		// �X:�s���i

	// ���ʂ��J�����O
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);				// �J�����O�̐ݒ�

	// �e���f���̕`��
	CObjectX::Draw();

	// �J���[�o�b�t�@�ւ̏������݂�L���ɂ���
	pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0x00000000F);

	// �X�e���V���o�b�t�@�̎Q�ƒl��ݒ肷��("2"�ɂ���)
	pDevice->SetRenderState(D3DRS_STENCILREF, 0x02);

	//�X�e���V���o�b�t�@�̔�r�p�����[�^��ݒ�
	pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);
	pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_KEEP);	// �X:���i�@Z:���i
	pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);	// �X:���i�@Z:�s���i
	pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);	// �X:�s���i

	// ��ʂ̑傫���̍����|���S����`��
	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));
	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	// ���ׂČ��ɖ߂�
	// �X�e���V���e�X�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);
	// Z�o�b�t�@�̏������݂𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	// �X�e���V���o�b�t�@�̎Q�ƒl��ݒ肷��("2"�ɂ���)
	pDevice->SetRenderState(D3DRS_STENCILREF, 0x00);
}

void CShadowS::SetPos(D3DXVECTOR3 pos)
{
	CObjectX::SetPos(pos);
}