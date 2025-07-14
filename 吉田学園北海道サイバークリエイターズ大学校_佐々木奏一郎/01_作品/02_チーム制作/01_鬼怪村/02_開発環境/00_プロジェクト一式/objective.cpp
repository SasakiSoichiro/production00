//=============================================================================
//
//�@�A�C�e�������� [objective.cpp]
// �@Author : ���X�ؑt��Y
//
//=============================================================================
#include "objective.h"
#include "player.h"
#include "input.h"
#include "item.h"

#define MAX_OBJECTIVE (10)

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureObjective[OBJECTIVETYPE_MAX] = {};		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffObjective = NULL;		//���_�o�b�t�@�ւ̃|�C���^
OBJECTIVE g_aObjective[MAX_OBJECTIVE];							//�u���b�N�̏��

//=============================================================================
//�A�C�e��UI�̏���������
//=============================================================================
void InitObjective(void)
{
	//���[�J���ϐ�
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^
	VERTEX_2D* pVtx = 0;		//���_���ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();
	for (int nCnt = 0; nCnt < OBJECTIVETYPE_MAX; nCnt++)
	{
		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,
			OBJECTIVE_TEXTURE[nCnt],
			&g_pTextureObjective[nCnt]);
	}
	//���[�v����
	for (int nCntBlock = 0; nCntBlock < MAX_OBJECTIVE; nCntBlock++)
	{//�u���b�N�̐������[�v����

		g_aObjective[nCntBlock].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ʒu������������
		g_aObjective[nCntBlock].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ړ��l������������
		g_aObjective[nCntBlock].fWidth = 0.0f;							//��������������
		g_aObjective[nCntBlock].fHeight = 0.0f;						//����������������
		g_aObjective[nCntBlock].nType = OBJECTIVETYPE_OBJECTIVE;					//��ނ�����������
		g_aObjective[nCntBlock].bUse = false;							//�g���Ă��Ȃ���Ԃɂ���	
		g_aObjective[nCntBlock].bText = false;							//�g���Ă��Ȃ���Ԃɂ���	

	}

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_OBJECTIVE,//(sizeof(VERTEX_2D)*�K�v�Ȓ��_��
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffObjective,
		NULL);


	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffObjective->Lock(0, 0, (void**)&pVtx, 0);

	//���[�v����
	for (int nCntBlock = 0; nCntBlock < MAX_OBJECTIVE; nCntBlock++)
	{//�u���b�N�̐������[�v����

		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

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

		pVtx += 4;//���_�f�[�^�̃|�C���^��4���W�߂�
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffObjective->Unlock();
}

//=============================================================================
//�A�C�e��UI�̏I������
//=============================================================================
void UninitObjective(void)
{
	for (int nCnt = 0; nCnt < OBJECTIVETYPE_MAX; nCnt++)
	{
		//�e�N�X�`���̔j��
		if (g_pTextureObjective[nCnt] != NULL)
		{
			g_pTextureObjective[nCnt]->Release();
			g_pTextureObjective[nCnt] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffObjective != NULL)
	{
		g_pVtxBuffObjective->Release();
		g_pVtxBuffObjective = NULL;
	}

}

//=============================================================================
//�A�C�e��UI�̍X�V����
//=============================================================================
void UpdateObjective(void)
{
	ITEM* pItem = Getitem();
	VERTEX_2D* pVtx = 0;	//���_���ւ̃|�C���^

	for (int nCnt = 0; nCnt < MAX_OBJECTIVE; nCnt++)
	{
		if (pItem[0].bHold == true && pItem[1].bHold == true)
		{
			g_aObjective[nCnt].bText = true;
		}
		if (g_aObjective[nCnt].nType == OBJECTIVETYPE_CHECK)
		{
			g_aObjective[nCnt].bUse = false;
		}
		if (g_aObjective[nCnt].bText == true && g_aObjective[nCnt].nType == OBJECTIVETYPE_CHECK)
		{
			g_aObjective[nCnt].bUse = true;
		}
		else if (g_aObjective[nCnt].bText == true && g_aObjective[nCnt].nType == OBJECTIVETYPE_WAKU1)
		{
			g_aObjective[nCnt].bUse = false;
		}
	}

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffObjective->Lock(0, 0, (void**)&pVtx, 0);

	//���[�v����
	for (int nCntBlock = 0; nCntBlock < MAX_OBJECTIVE; nCntBlock++)
	{//�u���b�N�̐������[�v����

		if (g_aObjective[nCntBlock].nType == OBJECTIVETYPE_TEXT1)
		{
			if (g_aObjective[nCntBlock].bText == false)
			{
				//���_�J���[�̐ݒ�@�@�@�@
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			}
			else if (g_aObjective[nCntBlock].bText == true)
			{
				//���_�J���[�̐ݒ�@�@�@�@
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.4f);
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.4f);
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.4f);
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.4f);

			}
		}

		if (g_aObjective[nCntBlock].nType == OBJECTIVETYPE_TEXT2)
		{
			if (g_aObjective[nCntBlock].bText == true)
			{
				//���_�J���[�̐ݒ�@�@�@�@
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			}
			else if (g_aObjective[nCntBlock].bText == false)
			{
				//���_�J���[�̐ݒ�@�@�@�@
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.4f);
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.4f);
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.4f);
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.4f);

			}
		}
		pVtx += 4;//���_�f�[�^�̃|�C���^��4���W�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffObjective->Unlock();

}

//=============================================================================
//�A�C�e��UI�̕`�揈��
//=============================================================================
void DrawObjective(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();
	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffObjective, 0, sizeof(VERTEX_2D));
	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//���[�v����
	for (int nCntItemUI = 0; nCntItemUI < MAX_OBJECTIVE; nCntItemUI++)
	{//�u���b�N�̐������[�v����

		if (g_aObjective[nCntItemUI].bUse == true)
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureObjective[g_aObjective[nCntItemUI].nType]);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntItemUI, 2);
		}
	}
}

//=============================================================================
// �ݒ菈��
//=============================================================================
void SetObjective(D3DXVECTOR3 pos, float fWidth, float fHeight, OBJECTIVETYPE nType)
{
	VERTEX_2D* pVtx = 0;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffObjective->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntUI = 0; nCntUI < OBJECTIVETYPE_MAX; nCntUI++)
	{
		if (g_aObjective[nCntUI].bUse == false)
		{// ���g�p��Ԃ�������
			g_aObjective[nCntUI].pos = pos;
			g_aObjective[nCntUI].nType = nType;
			g_aObjective[nCntUI].fHeight = fHeight;
			g_aObjective[nCntUI].fWidth = fWidth;
			g_aObjective[nCntUI].bText = false;
			g_aObjective[nCntUI].bUse = true;
			

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aObjective[nCntUI].pos.x - fWidth, g_aObjective[nCntUI].pos.y - fHeight, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aObjective[nCntUI].pos.x + fWidth, g_aObjective[nCntUI].pos.y - fHeight, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aObjective[nCntUI].pos.x - fWidth, g_aObjective[nCntUI].pos.y + fHeight, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aObjective[nCntUI].pos.x + fWidth, g_aObjective[nCntUI].pos.y + fHeight, 0.0f);
			break;
		}
		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffObjective->Unlock();
}

//=============================================================================
//�I����������n������
//=============================================================================
OBJECTIVE* GetObjective()
{
	return &g_aObjective[0];
}