//=============================================================================
//
// �G�t�F�N�g���� [effect.cpp]
// Author :Marina Harada
//
//=============================================================================
#include"effect.h"
#include"player.h"

// �O���[�o���錾
LPDIRECT3DTEXTURE9 g_pTextureeffect = NULL;			// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffeffect = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
Effect g_effect[MAX_EFFECT];

//=============================================================================
// �G�t�F�N�g�̏���������
//=============================================================================
void InitEffect(void)
{
	// �f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ������
	for (int nCnt = 0; nCnt < MAX_EFFECT; nCnt++)
	{
		g_effect[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		g_effect[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		g_effect[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		g_effect[nCnt].col = D3DXCOLOR(1.0f, 1.0, 1.0f, 1.0f);

		g_effect[nCnt].nLife = 0;

		g_effect[nCnt].buse = false;
	}

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * 4 * MAX_EFFECT,		// �m�ۂ���o�b�t�@�̃T�C�Y�A*���͕K�v�Ȓ��_��
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,							//���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxBuffeffect,
		NULL
	);

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\effect000.jpg",
		&g_pTextureeffect
	);

	// ���_���ւ̃|�C���^
	VERTEX_3D* pVtx = NULL;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffeffect->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_EFFECT; nCnt++)
	{
		// ���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_effect[nCnt].pos.x - 1.0f, g_effect[nCnt].pos.y + 1.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_effect[nCnt].pos.x + 1.0f, g_effect[nCnt].pos.y + 1.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_effect[nCnt].pos.x - 1.0f, g_effect[nCnt].pos.y - 1.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_effect[nCnt].pos.x + 1.0f, g_effect[nCnt].pos.y - 1.0f, 0.0f);

		// �e���_�̖@���̐ݒ�(���x�N�g���̑傫���͂P�ɂ���K�v������)
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		// ���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(0.5f, 0.5, 0.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(0.5f, 0.5, 0.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(0.5f, 0.5, 0.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(0.5f, 0.5, 0.0f, 1.0f);

		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffeffect->Unlock();
}

//=============================================================================
//�G�t�F�N�g�̏I������
//=============================================================================
void UninitEffect(void)
{
	// ���_�o�b�t�@�̉��
	if (g_pVtxBuffeffect != NULL)
	{
		g_pVtxBuffeffect->Release();

		g_pVtxBuffeffect = NULL;
	}

	// �e�N�X�`���̔j��
	if (g_pTextureeffect != NULL)
	{
		g_pTextureeffect->Release();

		g_pTextureeffect = NULL;
	}
}

//=============================================================================
//�G�t�F�N�g�̍X�V����
//=============================================================================
void UpdateEffect(void)
{
	Player* pPlayer = GetPlayer();

	for (int nCnt = 0; nCnt < MAX_EFFECT; nCnt++)
	{
		if (g_effect[nCnt].buse == true)
		{
			g_effect[nCnt].pos += g_effect[nCnt].move;

			g_effect[nCnt].nLife--;

			if (g_effect[nCnt].nLife <= 0)
			{
				g_effect[nCnt].buse = false;
			}
		}
	}
}

//=============================================================================
//�G�t�F�N�g�̕`�揈��
//=============================================================================
void DrawEffect(void)
{
	// �f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	////���e�X�g��L��
	//pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	//pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	//pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	// ���Z�����̐ݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);	// Z�̔�r
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);		// Z�o�b�t�@�ɏ������܂Ȃ�

	for (int nCnt = 0; nCnt < MAX_EFFECT; nCnt++)
	{
		if (g_effect[nCnt].buse == true)
		{
			// ���C�g�𖳌��ɂ���
			pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

			// �v�Z�p�}�g���b�N�X
			D3DXMATRIX mtxRot, mtxTrans;

			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_effect[nCnt].mtxWorld);

			D3DMATRIX mtxView;
			// �r���[�}�g���b�N�X�擾
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			// �J�����̋t�s���ݒ�
			g_effect[nCnt].mtxWorld._11 = mtxView._11;
			g_effect[nCnt].mtxWorld._12 = mtxView._21;
			g_effect[nCnt].mtxWorld._13 = mtxView._31;
			g_effect[nCnt].mtxWorld._21 = mtxView._12;
			g_effect[nCnt].mtxWorld._22 = mtxView._22;
			g_effect[nCnt].mtxWorld._23 = mtxView._32;
			g_effect[nCnt].mtxWorld._31 = mtxView._13;
			g_effect[nCnt].mtxWorld._32 = mtxView._23;
			g_effect[nCnt].mtxWorld._33 = mtxView._33;

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_effect[nCnt].pos.x, g_effect[nCnt].pos.y, g_effect[nCnt].pos.z);
			D3DXMatrixMultiply(&g_effect[nCnt].mtxWorld, &g_effect[nCnt].mtxWorld, &mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_effect[nCnt].mtxWorld);

			// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(
				0,
				g_pVtxBuffeffect,
				0,
				sizeof(VERTEX_3D)
			);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureeffect);

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			// �G�t�F�N�g�̕`��
			pDevice->DrawPrimitive(
				D3DPT_TRIANGLESTRIP,	// �v���~�e�B�u�̎��
				nCnt * 4,				// �`�悷��ŏ��̒��_�C���f�b�N�X
				2						// �v���~�e�B�u�i�w�i�j�̐�
			);

			// ���C�g��L���ɖ߂�
			pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
		}
	}

	////���e�X�g�𖳌��ɖ߂�
	//pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);

	// �ݒ�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);	// Z�̔�r���@�ύX
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);		// Z�o�b�t�@�ɏ�������
}

//=============================================================================
//�G�t�F�N�g�̐ݒ�
//=============================================================================
void SetEffect(D3DXVECTOR3 pos, D3DXVECTOR3 dir, int nLife, D3DXCOLOR col)
{
	for (int nCnt = 0; nCnt < MAX_EFFECT; nCnt++)
	{
		if (g_effect[nCnt].buse == false)
		{
			g_effect[nCnt].pos = pos;
			g_effect[nCnt].move = dir;
			g_effect[nCnt].nLife = nLife;
			g_effect[nCnt].col = col;
			g_effect[nCnt].buse = true;
			break;
		}
	}

}