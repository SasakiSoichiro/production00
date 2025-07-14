//====================================================
//
// �؂̏��� [billboard.cpp]
// Author : yabuki yukito
//
//====================================================

#include "billboard.h"
#include "player.h"
#include "item.h"
#include "input.h"
#include "gimmick.h"

//++++++++++++++++++++++++++++++++++++++++++++++++++++
// �O���[�o���ϐ��錾
//++++++++++++++++++++++++++++++++++++++++++++++++++++
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBillboard = NULL;					// ���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureBillboard[BILLBOARDTYPE_MAX] = {};		// �e�N�X�`���ւ̃|�C���^
Billboard g_Billboard[MAX_BILLBOARD];								// �\���̕ϐ�
bool bExchange;		// �E�o�\���ۂ�
bool bNext;			// ���߃Q�[�W���g�p����Ă��邩�ۂ�
bool bChange;		// ���������Ă��Ȃ�(1 / 2)
bool bGive;			// ���������Ă��Ȃ�(0/2)

//====================================================
//�A�C�e���̏���������
//====================================================
void InitBillboard()
{
	LPDIRECT3DDEVICE9 pDevice;			// �f�o�C�X�ւ̃|�C���^

	pDevice = GetDevice();				// �f�o�C�X�̎擾

	// �e�N�X�`���̓ǂݍ���
	for (int nCnt = 0; nCnt < BILLBOARDTYPE_MAX; nCnt++)
	{
		D3DXCreateTextureFromFile(pDevice,
			ITEM_TEXTURE[nCnt],
			&g_pTextureBillboard[nCnt]);
	}

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_BILLBOARD,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBillboard, NULL);

	// ���_���̃|�C���^
	VERTEX_3D* pVtx = NULL;

	// ���_�o�b�t�@�����b�N
	g_pVtxBuffBillboard->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_BILLBOARD; nCnt++)
	{
		// �e�ϐ��̏�����
		g_Billboard[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Billboard[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Billboard[nCnt].bTest = false;
		g_Billboard[nCnt].bDisplay = true;
		g_Billboard[nCnt].bUse = false;

		bExchange = false;
		bNext = false;
		bChange = false;
		bGive = false;

		// ���_���̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		// �e���_�̖@���̐ݒ�(�x�N�g���̑傫����1�ɂ���)
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		// ���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}

	// ���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffBillboard->Unlock();
}

//====================================================
//�A�C�e���̏I������
//====================================================
void UninitBillboard()
{
	// ���_�o�b�t�@�̉��
	if (g_pVtxBuffBillboard != NULL)
	{
		g_pVtxBuffBillboard->Release();
		g_pVtxBuffBillboard = NULL;
	}

	for (int nCnt = 0; nCnt < BILLBOARDTYPE_MAX; nCnt++)
	{
		// �e�N�X�`���̔j��
		if (g_pTextureBillboard[nCnt] != NULL)
		{
			g_pTextureBillboard[nCnt]->Release();
			g_pTextureBillboard[nCnt] = NULL;
		}
	}
}

//====================================================
//�A�C�e���̍X�V����
//====================================================
void UpdateBillboard()
{
	// ���_���̃|�C���^
	VERTEX_3D* pVtx = NULL;

	Player* pPlayer = GetPlayer();		// �v���C���[�̎擾
	ITEM* pItem = Getitem();			// �A�C�e���̎擾
	bool isbill = IsBill();				// �͈͎擾
	GIMMICK* pGimick = GetGimmick();	// �M�~�b�N�̎擾
	HOLD* pHold = GetHold();			// �A�C�e���̎擾����ϐ�

	// ���_�o�b�t�@�����b�N
	g_pVtxBuffBillboard->Lock(0, 0, (void**)&pVtx, 0);

	for (int count = 0; count < ITEMTYPE_MAX; count++,pItem++)
	{
		for (int nCnt = 0; nCnt < MAX_BILLBOARD; nCnt++)
		{

			if (pItem[count].bUse == true)
			{
				// �v���C���[�̔��a�̎Z�o�p�ϐ�
				float fPRadPos = 28.0f;

				// �A�C�e���̔��a�̎Z�o�p�ϐ�
				float fIRadPos = 28.0f;

				// �v���C���[�̈ʒu���擾
				D3DXVECTOR3 PlayerPos = GetPlayer()->pos;

				// �A�C�e���̃v���C���[�̋����̍�
				D3DXVECTOR3 diff = PlayerPos - pItem->pos;

				// �͈͌v�Z
				float fDisX = PlayerPos.x - pItem->pos.x;
				float fDisY = PlayerPos.y - pItem->pos.y;
				float fDisZ = PlayerPos.z - pItem->pos.z;

				// ��̔��a�����߂�
				float fRadX = fPRadPos + fIRadPos;

				// �񓚊i�[�p
				float fDistance = (fDisX * fDisX) + (fDisY * fDisY) + (fDisZ * fDisZ);
				float fRadius = (fRadX * fRadX);

				// �v���C���[���A�C�e���͈̔͂ɓ�������
				if (fDistance < fRadius)
				{

					//�E���r���{�[�h���g���Ă�Ƃ�
					//if (g_Billboard[nCnt].nType == BILLBOARDTYPE_1)
					//{

						g_Billboard[nCnt].bUse = true;
						g_Billboard[nCnt].bDisplay = true;
						g_Billboard[nCnt].pos.x = pItem->pos.x;
						g_Billboard[nCnt].pos.y = pItem->pos.y + 10.0f;
						g_Billboard[nCnt].pos.z = pItem->pos.z;

						// F�������ꂽ�Ƃ�
						if (KeybordTrigger(DIK_F) == true)
						{
							g_Billboard[nCnt].bUse = false;
						}
					//}
				}

				// �v���C���[���A�C�e���͈̔͊O�ɂ�������
				else if (fDistance > fRadius)
				{
					g_Billboard[nCnt].bDisplay = false;
				}
			}

			// ������������
			if (pItem[0].bHold == true && pItem[1].bHold == true)
			{
				// �v���C���[�̔��a�̎Z�o�p�ϐ�
				float fPRadPos = 50.0f;

				// �A�C�e���̔��a�̎Z�o�p�ϐ�
				float fIRadPos = 50.0f;

				// �v���C���[�̈ʒu���擾
				D3DXVECTOR3 PlayerPos = GetPlayer()->pos;

				// �A�C�e���̃v���C���[�̋����̍�
				D3DXVECTOR3 diff = PlayerPos - pGimick->pos;

				// �͈͌v�Z
				float fDisX = PlayerPos.x - pGimick->pos.x;
				float fDisY = PlayerPos.y - pGimick->pos.y;
				float fDisZ = PlayerPos.z - pGimick->pos.z;

				// ��̔��a�����߂�
				float fRadX = fPRadPos + fIRadPos;

				// �v���C���[���A�C�e���͈̔͂ɓ�������
				if ((fDisX * fDisX) + (fDisY * fDisY) + (fDisZ * fDisZ) <= (fRadX * fRadX))
				{

					if (g_Billboard[nCnt].nType == BILLBOARDTYPE_4)
					{
						bExchange = true;						// �E�o�\�̏�����
						g_Billboard[nCnt].bUse = true;			// �g�p
						g_Billboard[nCnt].bDisplay = true;		// ����
					}			
				}

				// �v���C���[���A�C�e���͈̔͊O�ɂ�������
				if ((fDisX * fDisX) + (fDisY * fDisY) + (fDisZ * fDisZ) > (fRadX * fRadX))
				{
					g_Billboard[nCnt].bDisplay = false;
				}
			}

			// (1/2)������������
			else if (pItem[1].bHold == false && pItem[0].bHold == true)
			{
				// �v���C���[�̔��a�̎Z�o�p�ϐ�
				float fPRadPos = 50.0f;

				// �A�C�e���̔��a�̎Z�o�p�ϐ�
				float fIRadPos = 50.0f;

				// �v���C���[�̈ʒu���擾
				D3DXVECTOR3 PlayerPos = GetPlayer()->pos;

				// �A�C�e���̃v���C���[�̋����̍�
				D3DXVECTOR3 diff = PlayerPos - pGimick->pos;

				// �͈͌v�Z
				float fDisX = PlayerPos.x - pGimick->pos.x;
				float fDisY = PlayerPos.y - pGimick->pos.y;
				float fDisZ = PlayerPos.z - pGimick->pos.z;

				// ��̔��a�����߂�
				float fRadX = fPRadPos + fIRadPos;

				// �v���C���[���A�C�e���͈̔͂ɓ�������
				if ((fDisX * fDisX) + (fDisY * fDisY) + (fDisZ * fDisZ) <= (fRadX * fRadX))
				{

					// 1/2��
					if (g_Billboard[nCnt].nType == BILLBOARDTYPE_3)
					{
						bChange = true;						// �E�o�\�̏�����
						bGive = false;
						g_Billboard[nCnt].bUse = true;		// �g�p
						g_Billboard[nCnt].bDisplay = true;	// ����
					}
				}

				// �v���C���[���A�C�e���͈̔͊O�ɂ�������
				if ((fDisX * fDisX) + (fDisY * fDisY) + (fDisZ * fDisZ) > (fRadX * fRadX))
				{
					g_Billboard[nCnt].bDisplay = false;
				}
			}

			// (1/2)������������
			else if (pItem[0].bHold == false && pItem[1].bHold == true)
			{
				// �v���C���[�̔��a�̎Z�o�p�ϐ�
				float fPRadPos = 50.0f;

				// �A�C�e���̔��a�̎Z�o�p�ϐ�
				float fIRadPos = 50.0f;

				// �v���C���[�̈ʒu���擾
				D3DXVECTOR3 PlayerPos = GetPlayer()->pos;

				// �A�C�e���̃v���C���[�̋����̍�
				D3DXVECTOR3 diff = PlayerPos - pGimick->pos;

				// �͈͌v�Z
				float fDisX = PlayerPos.x - pGimick->pos.x;
				float fDisY = PlayerPos.y - pGimick->pos.y;
				float fDisZ = PlayerPos.z - pGimick->pos.z;

				// ��̔��a�����߂�
				float fRadX = fPRadPos + fIRadPos;

				// �v���C���[���A�C�e���͈̔͂ɓ�������
				if ((fDisX * fDisX) + (fDisY * fDisY) + (fDisZ * fDisZ) <= (fRadX * fRadX))
				{
					// 1/2��
					if (g_Billboard[nCnt].nType == BILLBOARDTYPE_3)
					{
						bChange = true;						// �E�o�\�̏�����
						bGive = false;
						g_Billboard[nCnt].bUse = true;		// �g�p
						g_Billboard[nCnt].bDisplay = true;	// ����
					}
				}

				// �v���C���[���A�C�e���͈̔͊O�ɂ�������
				if ((fDisX * fDisX) + (fDisY * fDisY) + (fDisZ * fDisZ) > (fRadX * fRadX))
				{
					g_Billboard[nCnt].bDisplay = false;
				}
			}

			// (0/2)���������ĂȂ���
			else if (pItem[0].bHold == false && pItem[1].bHold == false)
			{
				// �v���C���[�̔��a�̎Z�o�p�ϐ�
				float fPRadPos = 50.0f;

				// �A�C�e���̔��a�̎Z�o�p�ϐ�
				float fIRadPos = 50.0f;

				// �v���C���[�̈ʒu���擾
				D3DXVECTOR3 PlayerPos = GetPlayer()->pos;

				// �A�C�e���̃v���C���[�̋����̍�
				D3DXVECTOR3 diff = PlayerPos - pGimick->pos;

				// �͈͌v�Z
				float fDisX = PlayerPos.x - pGimick->pos.x;
				float fDisY = PlayerPos.y - pGimick->pos.y;
				float fDisZ = PlayerPos.z - pGimick->pos.z;

				// ��̔��a�����߂�
				float fRadX = fPRadPos + fIRadPos;

				// �v���C���[���A�C�e���͈̔͂ɓ�������
				if ((fDisX * fDisX) + (fDisY * fDisY) + (fDisZ * fDisZ) <= (fRadX * fRadX))
				{
					// 0/2��
					if (g_Billboard[nCnt].nType == BILLBOARDTYPE_2)
					{
						bGive = true;						// �E�o�\�̏�����
						g_Billboard[nCnt].bUse = true;		// �g�p
						g_Billboard[nCnt].bDisplay = true;	// ����
					}
				}

				// �v���C���[���A�C�e���͈̔͊O�ɂ�������
				if ((fDisX * fDisX) + (fDisY * fDisY) + (fDisZ * fDisZ) > (fRadX * fRadX))
				{
					g_Billboard[nCnt].bDisplay = false;
				}
			}
		}
	}

	// ���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffBillboard->Unlock();
}

//====================================================
//�A�C�e���̕`�揈��
//====================================================
void DrawBillboard()
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	ITEM* pItem = Getitem();

	// �v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;

	// ���C�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	for (int nCnt = 0; nCnt < MAX_BILLBOARD; nCnt++)
	{
		if (g_Billboard[nCnt].bUse == true && g_Billboard[nCnt].bDisplay == true)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_Billboard[nCnt].mtxWorld);

			D3DXMATRIX mtxView;
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			// �J�����̋t�s����w��
			g_Billboard[nCnt].mtxWorld._11 = mtxView._11;
			g_Billboard[nCnt].mtxWorld._12 = mtxView._21;
			g_Billboard[nCnt].mtxWorld._13 = mtxView._31;
			g_Billboard[nCnt].mtxWorld._21 = mtxView._12;
			g_Billboard[nCnt].mtxWorld._22 = mtxView._22;
			g_Billboard[nCnt].mtxWorld._23 = mtxView._32;
			g_Billboard[nCnt].mtxWorld._31 = mtxView._13;
			g_Billboard[nCnt].mtxWorld._32 = mtxView._23;
			g_Billboard[nCnt].mtxWorld._33 = mtxView._33;

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_Billboard[nCnt].pos.x, g_Billboard[nCnt].pos.y, g_Billboard[nCnt].pos.z);
			D3DXMatrixMultiply(&g_Billboard[nCnt].mtxWorld, &g_Billboard[nCnt].mtxWorld, &mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_Billboard[nCnt].mtxWorld);

			// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffBillboard, 0, sizeof(VERTEX_3D));

			// �E�o�\�̏�����
			if (bExchange == true && g_Billboard[nCnt].nType == BILLBOARDTYPE_4)
			{
				// �e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_pTextureBillboard[4]);
			}
			// ���߃Q�[�W�̏�����
			else if (bNext == true && g_Billboard[nCnt].nType == BILLBOARDTYPE_5)
			{
				// �e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_pTextureBillboard[5]);
			}
			// ���������Ă��Ȃ�(1/2)�Ƃ��̏�����
			else if (bChange == true && g_Billboard[nCnt].nType == BILLBOARDTYPE_3)
			{
				// �e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_pTextureBillboard[2]);
			}
			// ���������Ă��Ȃ�(0/2)�Ƃ��̏�����
			else if (bGive == true && g_Billboard[nCnt].nType == BILLBOARDTYPE_2)
			{
				// �e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_pTextureBillboard[3]);
			}
			// �S���̏������ȊO
			else if (bExchange == false && bChange == false && bGive == false)
			{
				// �e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_pTextureBillboard[g_Billboard[nCnt].nType]);
			}

			// ���_�t�H�[�}�b�g
			pDevice->SetFVF(FVF_VERTEX_3D);

			// �A�C�e���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);
		}
	}

	// ���C�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//====================================================
//�A�C�e���̐ݒ菈��
//====================================================
void SetBillboard(D3DXVECTOR3 pos, D3DXVECTOR3 dir, TYPE nType, D3DXVECTOR3 size)
{
	VERTEX_3D* pVtx = NULL;		// ���_���̃|�C���^

	LPDIRECT3DDEVICE9 pDevice;	// �f�o�C�X�ւ̃|�C���^

	pDevice = GetDevice();		// �f�o�C�X�̎擾

	// ���_�o�b�t�@�����b�N
	g_pVtxBuffBillboard->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_BILLBOARD; nCnt++)
	{
		if (g_Billboard[nCnt].bUse == false)
		{
			g_Billboard[nCnt].pos = pos;		// �ʒu
			g_Billboard[nCnt].nType = nType;	// ���
			g_Billboard[nCnt].size = size;		// �傫��
			g_Billboard[nCnt].bUse = true;		// �g�p���Ă���Ƃ�

			// ���_���̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(-size.x, size.y, size.z);
			pVtx[1].pos = D3DXVECTOR3(size.x, size.y, size.z);
			pVtx[2].pos = D3DXVECTOR3(-size.x, -size.y, size.z);
			pVtx[3].pos = D3DXVECTOR3(size.x, -size.y, size.z);

			break;
		}

		pVtx += 4;
	}

	// ���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffBillboard->Unlock();
}
