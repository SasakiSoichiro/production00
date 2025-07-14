//=============================================================================
//
//	�M�~�b�N���� [gimmick.cpp]
// author chikada shouya
//
//=============================================================================

#include "gimmick.h"
#include "camera.h"
#include "Input.h"
#include "enemy.h"
#include "game.h"
#include "item.h"

// �O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_apTextureDoor[MAX_DOOR] = {};	// �e�N�X�`���ւ̃|�C���^
GIMMICK g_Door[MAX_DOOR];
HOLD g_hold;
bool isGoal;
bool isBill;

//================================
// ����������
//================================
void InitGimmick(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	g_hold.nHoldCount = 0;
	g_hold.NoTouch = 0;
	g_hold.HolTime = 0;
	g_hold.count = 0;
	g_hold.bPush = false;
	g_hold.bClear = false;
	g_hold.bNoPush = false;

	// �\���̕ϐ��̏�����
	for (int nCnt = 0; nCnt < MAX_DOOR; nCnt++)
	{
		// �e��ϐ��̏�����
		g_Door[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Door[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Door[nCnt].size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Door[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Door[nCnt].vtxMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Door[nCnt].vtxMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Door[nCnt].dwNumMat = 0;
		g_Door[nCnt].bUse = false;
		//g_Door[nCnt1][nCnt].bGoal = false;
		//g_Door[nCnt1][nCnt].bMove = false;

		// ���f���ǂݍ���
		// X�t�@�C���̓ǂݍ���
		D3DXLoadMeshFromX("data\\MODEL\\door.x",
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_Door[nCnt].pBuffMat,
			NULL,
			&g_Door[nCnt].dwNumMat,
			&g_Door[nCnt].pMesh);

		isGoal = false;
		isBill = false;
		// �T�C�Y���̎擾
		int nNumVtx;			// ���_��
		DWORD sizeFVF;			// ���_�t�H�[�}�b�g�̃T�C�Y
		BYTE* pVtxBuff;			// ���_�o�b�t�@�ւ̃|�C���^
		D3DXMATERIAL* pMat;		// �}�e���A���ւ̃|�C���^

		// ���_���̎擾
		nNumVtx = g_Door[nCnt].pMesh->GetNumVertices();

		// ���_�t�H�[�}�b�g�̎擾
		sizeFVF = D3DXGetFVFVertexSize(g_Door[nCnt].pMesh->GetFVF());

		// ���_�o�b�t�@�̃��b�N
		g_Door[nCnt].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			// ���_���W�̑��
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

			if (vtx.x > g_Door[nCnt].vtxMax.x)
			{// ����X�̒l���傫��������
				g_Door[nCnt].vtxMax.x = vtx.x;
			}
			else if (vtx.x < g_Door[nCnt].vtxMin.x)
			{// ����X�̒l��������������
				g_Door[nCnt].vtxMin.x = vtx.x;
			}

			if (vtx.y > g_Door[nCnt].vtxMax.y)
			{// ����Y�̒l���傫��������
				g_Door[nCnt].vtxMax.y = vtx.y;
			}
			else if (vtx.y < g_Door[nCnt].vtxMin.y)
			{// ����Y�̒l��������������
				g_Door[nCnt].vtxMin.y = vtx.y;
			}

			if (vtx.z > g_Door[nCnt].vtxMax.z)
			{// ����Z�̒l���傫��������
				g_Door[nCnt].vtxMax.z = vtx.z;
			}
			else if (vtx.z < g_Door[nCnt].vtxMin.z)
			{// ����Z�̒l��������������
				g_Door[nCnt].vtxMin.z = vtx.z;
			}

			// ���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
			pVtxBuff += sizeFVF;
		}

		// �T�C�Y����
		g_Door[nCnt].size.x = g_Door[nCnt].vtxMax.x - g_Door[nCnt].vtxMin.x;
		g_Door[nCnt].size.y = g_Door[nCnt].vtxMax.y - g_Door[nCnt].vtxMin.y;
		g_Door[nCnt].size.z = g_Door[nCnt].vtxMax.z - g_Door[nCnt].vtxMin.z;

		// ���_�o�b�t�@�̃A�����b�N
		g_Door[nCnt].pMesh->UnlockVertexBuffer();

		// �}�e���A���f�[�^�ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL*)g_Door[nCnt].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_Door[nCnt].dwNumMat; nCntMat++)
		{
			if (pMat[nCntMat].pTextureFilename != NULL)
			{// �e�N�X�`���t�@�C�������݂���
				// �e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice,
					pMat[nCntMat].pTextureFilename,
					&g_apTextureDoor[nCntMat]);
			}
		}
	}
}
//================================
// �I������
//================================
void UninitGimmick(void)
{
	for (int nCnt = 0; nCnt < MAX_DOOR; nCnt++)
	{
		// ���b�V���̔j��
		if (g_Door[nCnt].pMesh != NULL)
		{
			g_Door[nCnt].pMesh->Release();
			g_Door[nCnt].pMesh = NULL;
		}
		// �}�e���A���̔j��
		if (g_Door[nCnt].pBuffMat != NULL)
		{
			g_Door[nCnt].pBuffMat->Release();
			g_Door[nCnt].pBuffMat = NULL;
		}
		// �e�N�X�`���̔j��
		if (g_apTextureDoor[nCnt] != NULL)
		{
			g_apTextureDoor[nCnt]->Release();
			g_apTextureDoor[nCnt] = NULL;
		}
	}
}
//================================
// �X�V����
//================================
void UpdateGimmick(void)
{
	Player* pPlayer = GetPlayer();
	Enemy* pEnemy = GetEnemy();
	ITEM* pItem = Getitem();

	for (int nCnt = 0; nCnt < MAX_DOOR; nCnt++)
	{
		if (g_Door[nCnt].bUse == true)
		{
			// ���a�̎Z�o�ϐ�
			float PRadiusPos = 50.0f;
			float BRadiusPos = 50.0f;

			// �v���C���[�̈ʒu�̎擾
			D3DXVECTOR3 PlayerPos = GetPlayer()->pos;

			// �G�ƃv���C���[�̋����̍�
			D3DXVECTOR3 diff = PlayerPos - g_Door[nCnt].pos;

			// �͈͌v�Z
			float fDisX = PlayerPos.x - g_Door[nCnt].pos.x;
			float fDisY = PlayerPos.y - g_Door[nCnt].pos.y;
			float fDisZ = PlayerPos.z - g_Door[nCnt].pos.z;

			// ��̔��a�����߂�
			float fRadX = PRadiusPos + BRadiusPos;

			// �v���C���[���͈͂ɓ�������
			if ((fDisX * fDisX) + (fDisY * fDisY) + (fDisZ * fDisZ) <= (fRadX * fRadX))
			{
				// �r���{�[�h��\������
				isBill = true;

				if (pItem[0].bHold == true && pItem[1].bHold == true)
				{

					if (GetKeyboardPress(DIK_F) || GetJoypadPress(JOYKEY_B) == true)
					{

						g_hold.bPush = true;
						g_hold.bNoPush = false;
						g_hold.NoTouch = 0;
					}
					else if (KeybordRelease(DIK_F) || GetJoypadPress(JOYKEY_B) == false)
					{
						g_hold.bNoPush = true;
						g_hold.bPush = false;
					}
				}
			}
			// �v���C���[���͈͂̊O�ɏo����
			else if ((fDisX * fDisX) + (fDisY * fDisY) + (fDisZ * fDisZ) >= (fRadX * fRadX))
			{
				// �r���{�[�h���\���ɂ���
				isBill = false;
				g_hold.bNoPush = true;
				g_hold.bPush = false;
			}
		}
	}

	IsHold();
}
//================================
// �`�揈��
//================================
void DrawGimmick(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;	// �v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;			// ���݂̃}�e���A���ۑ��p
	D3DXMATERIAL* pMat;				// �}�e���A���f�[�^�ւ̃|�C���^

	for (int nCnt = 0; nCnt < MAX_DOOR; nCnt++)
	{
		if (g_Door[nCnt].bUse == true)
		{// ���g�p�������牺�̏�����ʂ��Ȃ�
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_Door[nCnt].mtxWorld);

			// �����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Door[nCnt].rot.y, g_Door[nCnt].rot.x, g_Door[nCnt].rot.z);
			D3DXMatrixMultiply(&g_Door[nCnt].mtxWorld, &g_Door[nCnt].mtxWorld, &mtxRot);

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_Door[nCnt].pos.x, g_Door[nCnt].pos.y, g_Door[nCnt].pos.z);
			D3DXMatrixMultiply(&g_Door[nCnt].mtxWorld, &g_Door[nCnt].mtxWorld, &mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_Door[nCnt].mtxWorld);

			// ���݂̃}�e���A�����擾
			pDevice->GetMaterial(&matDef);

			// �}�e���A���f�[�^�ւ̃|�C���^���擾
			pMat = (D3DXMATERIAL*)g_Door[nCnt].pBuffMat->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_Door[nCnt].dwNumMat; nCntMat++)
			{
				// �}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				// �e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_apTextureDoor[nCntMat]);

				// ���f��(�p�[�c)�̕`��
				g_Door[nCnt].pMesh->DrawSubset(nCntMat);
			}

			// �ۑ����Ă����}�e���A�����B��
			//pDevice->SetMaterial(NULL);
			pDevice->SetMaterial(&matDef);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, NULL);
		}
	}
}
//================================================
// �u���b�N�̐ݒ菈��
//================================================
void SetGimmick(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	for (int nCnt = 0; nCnt < MAX_DOOR; nCnt++)
	{
		if (g_Door[nCnt].bUse == false)
		{// �ǂ��g�p����Ă��Ȃ�
			g_Door[nCnt].pos = pos;		// �ʒu
			g_Door[nCnt].rot = rot;		// �p�x
			g_Door[nCnt].bUse = true;	// �g�p���Ă���
			break;
		}
	}
}
//================================================
//�u���b�N�����蔻��
//================================================
void CollisionGimmick(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld)
{
	Player* pPlayer = GetPlayer();
	D3DXVECTOR3* posOld = pPosOld;		//�O�t���[���̃v���C���[�̈ʒu
	D3DXVECTOR3* pos = pPos;			//���t���[���̃v���C���[�̈ʒu

	for (int nCnt = 0; nCnt < MAX_DOOR; nCnt++)
	{
		if (g_Door[nCnt].bUse == true)
		{
			//���E��O���̂߂荞�ݔ���
			if (pos->y< g_Door[nCnt].pos.y + g_Door[nCnt].vtxMax.y && pos->y + (OBJ_P * 2.0f) > g_Door[nCnt].pos.y + g_Door[nCnt].vtxMin.y)
			{
				//���E�̂߂荞�ݔ���
				if (pos->z - OBJ_P< g_Door[nCnt].pos.z + g_Door[nCnt].vtxMax.z && pos->z + OBJ_P > g_Door[nCnt].pos.z + g_Door[nCnt].vtxMin.z)//�v���C���[�̂��͈̔͂��u���b�N�ɏd�Ȃ��Ă���
				{

					if (posOld->x + OBJ_P< g_Door[nCnt].pos.x + g_Door[nCnt].vtxMin.x && pos->x + OBJ_P > g_Door[nCnt].pos.x + g_Door[nCnt].vtxMin.x)//�w��������E�ɂ߂荞��
					{
						//pPlayer->pos�����f���̍����ɂ�������
						pos->x = g_Door[nCnt].pos.x + g_Door[nCnt].vtxMin.x - OBJ_P - 0.1f;

					}
					if (posOld->x - OBJ_P > g_Door[nCnt].pos.x + g_Door[nCnt].vtxMax.x && pos->x - OBJ_P < g_Door[nCnt].pos.x + g_Door[nCnt].vtxMax.x)//�w��������E�ɂ߂荞��
					{
						//pPlayer->pos�����f���̉E���ɂ�������
						pos->x = g_Door[nCnt].pos.x + g_Door[nCnt].vtxMax.x + OBJ_P + 0.1f;
					}
				}

				//��O���̂߂荞�ݔ���
				if (pos->x - OBJ_P< g_Door[nCnt].pos.x + g_Door[nCnt].vtxMax.x && pos->x + OBJ_P > g_Door[nCnt].pos.x + g_Door[nCnt].vtxMin.x)//�v���C���[x�͈̔͂��u���b�N�ɏd�Ȃ��Ă���
				{

					if (posOld->z + OBJ_P< g_Door[nCnt].pos.z + g_Door[nCnt].vtxMin.z && pos->z + OBJ_P > g_Door[nCnt].pos.z + g_Door[nCnt].vtxMin.z)//Z���������ɂ߂荞��
					{
						//pPlayer->pos�����f���̎�O���ɂ�������
						pos->z = g_Door[nCnt].pos.z + g_Door[nCnt].vtxMin.z - OBJ_P - 0.1f;
					}
					if (posOld->z - OBJ_P > g_Door[nCnt].pos.z + g_Door[nCnt].vtxMax.z && pos->z - OBJ_P < g_Door[nCnt].pos.z + g_Door[nCnt].vtxMax.z)//Z���ォ�牺�ɂ߂荞��
					{
						//pPlayer->pos�����f���̉����ɂ�������
						pos->z = g_Door[nCnt].pos.z + g_Door[nCnt].vtxMax.z + OBJ_P + 0.1f;
					}
				}

			}
			if (pos->z - OBJ_P< g_Door[nCnt].pos.z + g_Door[nCnt].vtxMax.z && pos->z + OBJ_P > g_Door[nCnt].pos.z + g_Door[nCnt].vtxMin.z
				&& pos->x - OBJ_P< g_Door[nCnt].pos.x + g_Door[nCnt].vtxMax.x && pos->x + OBJ_P > g_Door[nCnt].pos.x + g_Door[nCnt].vtxMin.x)
			{
				if (posOld->y + (OBJ_P * 2.0f) < g_Door[nCnt].pos.y + g_Door[nCnt].vtxMin.y && pos->y + (OBJ_P * 2.0f) > g_Door[nCnt].pos.y + g_Door[nCnt].vtxMin.y)//�w��������E�ɂ߂荞��
				{
					//pPlayer->pos�����f���̉����ɂ�������
					pos->y = g_Door[nCnt].pos.y + g_Door[nCnt].vtxMin.y - (OBJ_P * 2.0f) - 0.1f;
				}
				if (posOld->y > g_Door[nCnt].pos.y + g_Door[nCnt].vtxMax.y && pos->y < g_Door[nCnt].pos.y + g_Door[nCnt].vtxMax.y)//�w��������E�ɂ߂荞��
				{
					//pPlayer->pos�����f���̏㑤�ɂ�������
					pos->y = g_Door[nCnt].pos.y + g_Door[nCnt].vtxMax.y + 0.1f;
				}

			}

		}

	}
}

GIMMICK* GetGimmick(void)
{
	return &g_Door[0];
}

bool IsGoal()
{
	return isGoal;
}
bool IsBill()
{
	return isBill;
}
void IsHold()
{
	if (g_hold.bPush == true)
	{
		g_hold.nHoldCount++;
	}
	else if (g_hold.bPush == false)
	{
		g_hold.nHoldCount = g_hold.HolTime;
	}

	if (g_hold.bNoPush == true)
	{
		g_hold.count++;
		if (g_hold.count >= 5)
		{
			g_hold.count = 0;
			g_hold.NoTouch++;
		}
	}

	g_hold.HolTime = g_hold.nHoldCount - 1;

	if (g_hold.HolTime <= 0)
	{
		g_hold.HolTime = 0;
	}

	if (g_hold.HolTime >= 300)
	{
		isGoal = true;
	}
}
HOLD* GetHold(void)
{
	return &g_hold;
}