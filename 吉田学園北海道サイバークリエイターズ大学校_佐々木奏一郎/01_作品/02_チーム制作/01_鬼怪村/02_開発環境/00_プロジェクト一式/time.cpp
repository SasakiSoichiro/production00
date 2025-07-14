//=============================================================================
//
// �^�C�}�[���� [time.cpp]
// Author:Marina Harada
//
//=============================================================================
#include"time.h"
#include"fade.h"
#include"game.h"
#include"result.h"
#include"player.h"

//=============================================================================
// �O���[�o���錾
//=============================================================================
LPDIRECT3DTEXTURE9 g_pTexturetime[MAX_TEX] = {};	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffns = NULL;		// ���_�o�b�t�@�ւ̃|�C���^�i�b�j
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffmin = NULL;		// ���_�o�b�t�@�ւ̃|�C���^�i���j
LPDIRECT3DVERTEXBUFFER9 g_pVtxbuffcolon = NULL;		// ���_�o�b�t�@�ւ̃|�C���^�i:�j
D3DXVECTOR3 g_postime;								// �^�C�}�[�̈ʒu
int g_ntime = 0;									// �^�C�}�[�̒l
int g_ns = 0;										// �b
int g_min = 0;										// ��

//=============================================================================
// �^�C�}�[�̏���������
//=============================================================================
void InitTime(void)
{
	// �f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

    // �f�o�C�X�̎擾
	pDevice = GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\number005.png",
		&g_pTexturetime[0]
	);

	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\number004.png",
		&g_pTexturetime[1]
	);

	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\colon000.png",
		&g_pTexturetime[2]
	);

	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\colon001.png",
		&g_pTexturetime[3]
	);

	// �ʒu������������
	g_postime = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// �l������������
	g_ntime = 0;

	// ��
	g_min = MAX_MIN;

	// �b�|���S��
	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4 * MAX_TIME,	// �m�ۂ���o�b�t�@�̃T�C�Y�A*���͕K�v�Ȓ��_��
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,						// ���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxBuffns,
		NULL
	);

	// ���_���ւ̃|�C���^
	VERTEX_2D* pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffns->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntS = 0; nCntS < MAX_TIME; nCntS++)
	{
		// �g�p���
		bool bUse = true;

		// ���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(200.0f + nCntS * 50.0f,		 0.0f,  0.0f);
		pVtx[1].pos = D3DXVECTOR3(200.0f + nCntS * 50.0f + 50.0f, 0.0f,  0.0f);
		pVtx[2].pos = D3DXVECTOR3(200.0f + nCntS * 50.0f,		 50.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(200.0f + nCntS * 50.0f + 50.0f, 50.0f, 0.0f);

		// rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// ���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		
		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		pVtx += 4;
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffns->Unlock();

	// ���|���S��
	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4 * MAX_TIME,	//�m�ۂ���o�b�t�@�̃T�C�Y�A*���͕K�v�Ȓ��_��
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,						//���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxBuffmin,
		NULL
	);

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffmin->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntS = 0; nCntS < MAX_TIME; nCntS++)
	{
		// �g�p���
		bool bUse = true;

		// ���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(50.0f + nCntS * 40.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(50.0f + nCntS * 40.0f + 50.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(50.0f + nCntS * 40.0f, 50.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(50.0f + nCntS * 40.0f + 50.0f, 50.0f, 0.0f);

		// rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// ���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		pVtx += 4;
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffmin->Unlock();

	// :�|���S��
	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4,	//�m�ۂ���o�b�t�@�̃T�C�Y�A*���͕K�v�Ȓ��_��
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,			//���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxbuffcolon,
		NULL
	);

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxbuffcolon->Lock(0, 0, (void**)&pVtx, 0);

	// �g�p���
	bool bUse = true;

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(150.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(200.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(150.0f, 50.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(200.0f, 50.0f, 0.0f);

	// rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

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

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxbuffcolon->Unlock();
}

//=============================================================================
// �^�C�}�[�̏I������
//=============================================================================
void UninitTime(void)
{
	// �e�N�X�`���̔j��
	for (int nCnt = 0; nCnt < MAX_TEX; nCnt++)
	{
		// �e�N�X�`���̔j��
		if (g_pTexturetime[nCnt] != NULL)
		{
			g_pTexturetime[nCnt]->Release();

			g_pTexturetime[nCnt] = NULL;
		}
	}

	//���_�o�b�t�@�̔j���i�b�j
	if (g_pVtxBuffns != NULL)
	{  
		g_pVtxBuffns->Release();

		g_pVtxBuffns = NULL;
	}

	//���_�o�b�t�@�̔j���i���j
	if (g_pVtxBuffmin != NULL)
	{
		g_pVtxBuffmin->Release();

		g_pVtxBuffmin = NULL;
	}

	//���_�o�b�t�@�̔j���i:�j
	if (g_pVtxbuffcolon != NULL)
	{
		g_pVtxbuffcolon->Release();

		g_pVtxbuffcolon = NULL;
	}
}

//=============================================================================
// �^�C�}�[�̍X�V����
//=============================================================================
void UpdateTime(void)
{
	g_ns++;
	Player* pPlayer = GetPlayer();

	// 1�b�o��
	if (g_ns >= 60)
	{
		SubNs(1);

		g_ns = 0;
	}

	// 1���o��
	if (g_ntime <= 0)
	{
		if (g_min <= 0)
		{// 0��0�b�ɂȂ�����Q�[������

			pPlayer->nLife = 0;

			// ���[�h�ݒ�
			SetGameState(GAMESTATE_END);// �Q�[�����I��������
		}
		else
		{// ����ȊO
			SubNs(-59);

			SubMin(1);
		}
	}
}

//=============================================================================
// �^�C�}�[�̕`�揈��
//=============================================================================
void DrawTime(void)
{
	// �f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

    // �f�o�C�X�̎擾
	pDevice = GetDevice();

	// �b�̕`��
	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(
		0,
		g_pVtxBuffns,
		0,
		sizeof(VERTEX_2D)
	);

	// ���_���ւ̃|�C���^
	VERTEX_2D* pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffns->Lock(0, 0, (void**)&pVtx, 0);

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCnttime = 0; nCnttime < MAX_TIME; nCnttime++)
	{
			    
			// 90�b�o��
			if (g_ntime <= 30 && g_min <= 0)
			{

				// �e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_pTexturetime[1]);

			}
			else
			{

				// �e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_pTexturetime[0]);

			}

			// �^�C�}�[�̕`��
			pDevice->DrawPrimitive(
				D3DPT_TRIANGLESTRIP,	// �v���~�e�B�u�̎��
				4 * nCnttime,			// �`�悷��ŏ��̒��_�C���f�b�N�X
				2						// �v���~�e�B�u�i�^�C�}�[�j�̐�
			);
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffns->Unlock();

	// ���̕`��
	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(
		0,
		g_pVtxBuffmin,
		0,
		sizeof(VERTEX_2D)
	);

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffmin->Lock(0, 0, (void**)&pVtx, 0);

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCnttime = 0; nCnttime < MAX_TIME; nCnttime++)
	{
		// 90�b�o��
		if (g_ntime <= 30 && g_min <= 0)
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTexturetime[1]);
		}
		else
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTexturetime[0]);

		}

		// �^�C�}�[�̕`��
		pDevice->DrawPrimitive(
			D3DPT_TRIANGLESTRIP,	// �v���~�e�B�u�̎��
			4 * nCnttime,			// �`�悷��ŏ��̒��_�C���f�b�N�X
			2						// �v���~�e�B�u�i�^�C�}�[�j�̐�
		);
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffmin->Unlock();

	//:�̕`��
	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(
		0,
		g_pVtxbuffcolon,
		0,
		sizeof(VERTEX_2D)
	);

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxbuffcolon->Lock(0, 0, (void**)&pVtx, 0);

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// 90�b�o��
	if (g_ntime <= 30 && g_min <= 0)
	{
		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTexturetime[3]);
	}
	else
	{
		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTexturetime[2]);
	}

	// �^�C�}�[�̕`��
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,	// �v���~�e�B�u�̎��
		0,						// �`�悷��ŏ��̒��_�C���f�b�N�X
		2						// �v���~�e�B�u�i�^�C�}�[�j�̐�
	);

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxbuffcolon->Unlock();
}

//=============================================================================
// �^�C�}�[�̐ݒ菈��
//=============================================================================
void SetTime(int ntime)
{
	// �b��
	int aPosTexU[MAX_TIME] = {};	// �e���̐������i�[
	int nData = 100;				// 3��
	int nData1 = 10;				// 2��

	g_ntime += ntime;

	// ���_���ւ̃|�C���^
	VERTEX_2D* pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffns->Lock(0, 0, (void**)&pVtx, 0);

	for (int ncount = 0; ncount < MAX_TIME; ncount++)
	{
		if (ncount == 0)
		{
			// 0�Ԗڂ�������
			aPosTexU[0] = g_ntime / nData;
		}
		else
		{
			// 0�ԖڈȊO
			aPosTexU[ncount] = (g_ntime % nData) / nData1;
			nData = nData / 10;
			nData1 = nData1 / 10;
		}

		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f + (0.1f * aPosTexU[ncount]), 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f + (0.1f * aPosTexU[ncount]), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + (0.1f * aPosTexU[ncount]), 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f + (0.1f * aPosTexU[ncount]), 1.0f);

		pVtx += 4;
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffns->Unlock();

	//����
	int aPosTexu[MAX_TIME] = {};	// �e���̐������i�[
	int nData2 = 100;				// 3��
	int nData3 = 10;				// 2��

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffmin->Lock(0, 0, (void**)&pVtx, 0);

	for (int ncount = 0; ncount < MAX_TIME; ncount++)
	{
		if (ncount == 0)
		{
			// 0�Ԗڂ�������
			aPosTexu[0] = g_min / nData2;
		}
		else
		{
			// 0�ԖڈȊO
			aPosTexu[ncount] = (g_min % nData2) / nData3;
			nData2 = nData2 / 10;
			nData3 = nData3 / 10;
		}

		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f + (0.1f * aPosTexu[ncount]), 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f + (0.1f * aPosTexu[ncount]), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + (0.1f * aPosTexu[ncount]), 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f + (0.1f * aPosTexu[ncount]), 1.0f);

		pVtx += 4;
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffmin->Unlock();
}

//=============================================================================
// �^�C�}�[�̕b���Z����
//=============================================================================
void SubNs(int nValue)
{
	int aPosTexU[MAX_TIME] = {};	// �e���̐������i�[
	int nData = 100;				// 3��
	int nData1 = 10;				// 2��

	g_ntime -= nValue;

	// ���_���ւ̃|�C���^
	VERTEX_2D* pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffns->Lock(0, 0, (void**)&pVtx, 0);

	for (int ncount = 0; ncount < MAX_TIME; ncount++)
	{
		// 0�ԖڈȊO
		aPosTexU[ncount] = (g_ntime % nData) / nData1;
		nData = nData / 10;
		nData1 = nData1 / 10;

		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f + (0.1f * aPosTexU[ncount]), 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f + (0.1f * aPosTexU[ncount]), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + (0.1f * aPosTexU[ncount]), 1.0f);
 		pVtx[3].tex = D3DXVECTOR2(0.1f + (0.1f * aPosTexU[ncount]), 1.0f);

		pVtx += 4;

	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffns->Unlock();
}

//=============================================================================
// �^�C�}�[�̕����Z����
//=============================================================================
void SubMin(int nValue)
{
	int aPosTexU[MAX_TIME] = {};	// �e���̐������i�[
	int nData = 100;				// 3��
	int nData1 = 10;				// 2��

	g_min -= nValue;

	// ���_���ւ̃|�C���^
	VERTEX_2D* pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffmin->Lock(0, 0, (void**)&pVtx, 0);

	for (int ncount = 0; ncount < MAX_TIME; ncount++)
	{
		// 0�ԖڈȊO
		aPosTexU[ncount] = (g_min % nData) / nData1;
		nData = nData / 10;
		nData1 = nData1 / 10;

		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f + (0.1f * aPosTexU[ncount]), 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f + (0.1f * aPosTexU[ncount]), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + (0.1f * aPosTexU[ncount]), 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f + (0.1f * aPosTexU[ncount]), 1.0f);

		pVtx += 4;
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffmin->Unlock();
}

//=============================================================================
//�^�C�}�[�̕b�擾
//=============================================================================
int GetNs(void)
{
	return g_ntime;
}

//=============================================================================
//�^�C�}�[�̕��擾
//=============================================================================
int GetMin(void)
{
	return g_min;
}