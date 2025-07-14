//=============================================================
//
// Athor: HRT ryuusei  �����L���O
// 
//=============================================================
#include "ranking.h"
#include "input.h"
#include "fade.h"
#include "game.h"
#include "stdio.h"
#include "time.h"
#include "player.h"

//�����L���O�X�R�A�̍\����
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	int nRank;			//����
	int nTime;          //�^�C�}�[
	int nNs;			//�b
	int nMin;           //��
}RankTime;

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_pTextureBKG = NULL;			    //�e�N�X�`���ւ̃|�C���^(�w�i)
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBKG = NULL;			//���_�o�b�t�@�ւ̃|�C���^(�w�i)

LPDIRECT3DTEXTURE9 g_pTextureRank = NULL;				//�e�N�X�`���ւ̃|�C���^(����)
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRank = NULL;			//���_�o�b�t�@�ւ̃|�C���^(����)

LPDIRECT3DTEXTURE9 g_pTextureRankTime = NULL;			//�e�N�X�`���ւ̃|�C���^(�b�E��)
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRankNs = NULL;		//���_�o�b�t�@�ւ̃|�C���^(�b)
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRankMin = NULL;		//���_�o�b�t�@�ւ̃|�C���^(��)

LPDIRECT3DTEXTURE9 g_pTextureRankColon = NULL;			//�e�N�X�`���ւ̃|�C���^(:)
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRankColon = NULL;		//���_�o�b�t�@�ւ̃|�C���^(:)

RankTime g_aRankTime[MAX_RANK] = {};					//�����L���O�^�C�}�[(5�ʕ�)�\��
int g_nRankUpdate = -1;									//�X�V�����NNo.
int g_nTimerRanking;									//�����L���O��ʕ\���^�C�}�[

//----------------------------
//�����L���O�̏���������
//----------------------------
void InitRanking(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	int nCntRank;
	int nRankTime;

	g_nRankUpdate = -1;//�X�VNo.��������
	g_nTimerRanking = 0;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���(����)
	D3DXCreateTextureFromFile(pDevice,
		"data\\texture\\number006.png",
		&g_pTextureRank);

	//�e�N�X�`���̓ǂݍ���(�b�E��)
	D3DXCreateTextureFromFile(pDevice,
		"data\\texture\\number005.png",
		&g_pTextureRankTime);

	//�e�N�X�`���̓ǂݍ���(�w�i)
	D3DXCreateTextureFromFile(pDevice,
		"data\\texture\\BloodSplatter.png",
		&g_pTextureBKG);

	//�e�N�X�`���̓ǂݍ���(:)
	D3DXCreateTextureFromFile(pDevice,
		"data\\texture\\colon000.png",
		&g_pTextureRankColon);

	//���_�o�b�t�@�̐���(����)
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_RANK, //�K�v�Ȓ��_��
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRank,
		NULL);

	//���_�o�b�t�@�̐���(�b)
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_RANK * MAX_RANKNS_NUM, //�K�v�Ȓ��_��
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRankNs,
		NULL);

	//���_�o�b�t�@�̐���(��)
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_RANK * MAX_RANKMIN_NUM, //�K�v�Ȓ��_��
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRankMin,
		NULL);

	//���_�o�b�t�@�̐���(:)
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_RANK, //�K�v�Ȓ��_��
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRankColon,
		NULL);

	//���_�o�b�t�@�̐���(�w�i)
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, //�K�v�Ȓ��_��
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBKG,
		NULL);

	VERTEX_2D* pVtx;

	//�b
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffRankNs->Lock(0, 0, (void**)&pVtx, 0);

	//�����L���O�̏��̏�����
	for (nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
	{//�����L���O�̏��ʕ���
		g_aRankTime[nCntRank].pos = D3DXVECTOR3(750.0f, 150.0f + MAX_RANKTIME_HEIGHT * nCntRank, 0.0f);
		g_aRankTime[nCntRank].nTime = 0;
		g_aRankTime[nCntRank].nRank = nCntRank + 1;

		for (nRankTime = 0; nRankTime < MAX_RANKNS_NUM; nRankTime++)
		{//�b�̌�������

			//���_���W�̐ݒ�
			pVtx[0].pos.x = g_aRankTime[nCntRank].pos.x - MAX_RANKTIME_WIDTH / 2 + MAX_RANKTIME_WIDTH * nRankTime;
			pVtx[0].pos.y = g_aRankTime[nCntRank].pos.y - MAX_RANKTIME_HEIGHT / 2;
			pVtx[0].pos.z = 0.0f;

			pVtx[1].pos.x = g_aRankTime[nCntRank].pos.x + MAX_RANKTIME_WIDTH / 2 + MAX_RANKTIME_WIDTH * nRankTime;
			pVtx[1].pos.y = g_aRankTime[nCntRank].pos.y - MAX_RANKTIME_HEIGHT / 2;
			pVtx[1].pos.z = 0.0f;

			pVtx[2].pos.x = g_aRankTime[nCntRank].pos.x - MAX_RANKTIME_WIDTH / 2 + MAX_RANKTIME_WIDTH * nRankTime;
			pVtx[2].pos.y = g_aRankTime[nCntRank].pos.y + MAX_RANKTIME_HEIGHT / 2;
			pVtx[2].pos.z = 0.0f;

			pVtx[3].pos.x = g_aRankTime[nCntRank].pos.x + MAX_RANKTIME_WIDTH / 2 + MAX_RANKTIME_WIDTH * nRankTime;
			pVtx[3].pos.y = g_aRankTime[nCntRank].pos.y + MAX_RANKTIME_HEIGHT / 2;
			pVtx[3].pos.z = 0.0f;

			//rhw�̐ݒ�
			pVtx[0].rhw = 1.0f;
			pVtx[1].rhw = 1.0f;
			pVtx[2].rhw = 1.0f;
			pVtx[3].rhw = 1.0f;

			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//�e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

			pVtx += 4;//���_�f�[�^�̃|�C���^���l���i�߂�
		}
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffRankNs->Unlock();

	//��
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffRankMin->Lock(0, 0, (void**)&pVtx, 0);

	//�����L���O�̏��̏�����
	for (nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
	{//�����L���O�̏��ʕ���
		g_aRankTime[nCntRank].pos = D3DXVECTOR3(550.0f, 150.0f + MAX_RANKTIME_HEIGHT * nCntRank, 0.0f);
		g_aRankTime[nCntRank].nMin = 0;
		g_aRankTime[nCntRank].nRank = nCntRank + 1;

		for (nRankTime = 0; nRankTime < MAX_RANKMIN_NUM; nRankTime++)
		{//���̌�������

			//���_���W�̐ݒ�
			pVtx[0].pos.x = g_aRankTime[nCntRank].pos.x - MAX_RANKTIME_WIDTH / 2 + MAX_RANKTIME_WIDTH * nRankTime;
			pVtx[0].pos.y = g_aRankTime[nCntRank].pos.y - MAX_RANKTIME_HEIGHT / 2;
			pVtx[0].pos.z = 0.0f;

			pVtx[1].pos.x = g_aRankTime[nCntRank].pos.x + MAX_RANKTIME_WIDTH / 2 + MAX_RANKTIME_WIDTH * nRankTime;
			pVtx[1].pos.y = g_aRankTime[nCntRank].pos.y - MAX_RANKTIME_HEIGHT / 2;
			pVtx[1].pos.z = 0.0f;

			pVtx[2].pos.x = g_aRankTime[nCntRank].pos.x - MAX_RANKTIME_WIDTH / 2 + MAX_RANKTIME_WIDTH * nRankTime;
			pVtx[2].pos.y = g_aRankTime[nCntRank].pos.y + MAX_RANKTIME_HEIGHT / 2;
			pVtx[2].pos.z = 0.0f;

			pVtx[3].pos.x = g_aRankTime[nCntRank].pos.x + MAX_RANKTIME_WIDTH / 2 + MAX_RANKTIME_WIDTH * nRankTime;
			pVtx[3].pos.y = g_aRankTime[nCntRank].pos.y + MAX_RANKTIME_HEIGHT / 2;
			pVtx[3].pos.z = 0.0f;

			//rhw�̐ݒ�
			pVtx[0].rhw = 1.0f;
			pVtx[1].rhw = 1.0f;
			pVtx[2].rhw = 1.0f;
			pVtx[3].rhw = 1.0f;

			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//�e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

			pVtx += 4;//���_�f�[�^�̃|�C���^���l���i�߂�
		}
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffRankNs->Unlock();

	//����
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffRank->Lock(0, 0, (void**)&pVtx, 0);

	//�����L���O�̏��̏�����
	for (nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
	{
		g_aRankTime[nCntRank].pos = D3DXVECTOR3(500.0f - MAX_RANK_WIDTH, 150.0f + MAX_RANKTIME_HEIGHT * nCntRank, 0.0f);

		//���_���W�̐ݒ�
		pVtx[0].pos.x = g_aRankTime[nCntRank].pos.x - MAX_RANK_WIDTH / 2;
		pVtx[0].pos.y = g_aRankTime[nCntRank].pos.y - MAX_RANKTIME_HEIGHT / 2;
		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = g_aRankTime[nCntRank].pos.x + MAX_RANK_WIDTH / 2;
		pVtx[1].pos.y = g_aRankTime[nCntRank].pos.y - MAX_RANKTIME_HEIGHT / 2;
		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = g_aRankTime[nCntRank].pos.x - MAX_RANK_WIDTH / 2;
		pVtx[2].pos.y = g_aRankTime[nCntRank].pos.y + MAX_RANKTIME_HEIGHT / 2;
		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = g_aRankTime[nCntRank].pos.x + MAX_RANK_WIDTH / 2;
		pVtx[3].pos.y = g_aRankTime[nCntRank].pos.y + MAX_RANKTIME_HEIGHT / 2;
		pVtx[3].pos.z = 0.0f;

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.1f + 0.1f * nCntRank, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.2f + 0.1f * nCntRank, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.1f + 0.1f * nCntRank, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.2f + 0.1f * nCntRank, 1.0f);

		pVtx += 4;//���_�f�[�^�̃|�C���^���l���i�߂�
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffRank->Unlock();

	//�w�i
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBKG->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
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
	g_pVtxBuffBKG->Unlock();

	//:
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffRankColon->Lock(0, 0, (void**)&pVtx, 0);

	//�����L���O�̏��̏�����
	for (nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
	{//�����L���O�̏��ʕ���
		g_aRankTime[nCntRank].pos = D3DXVECTOR3(730.0f - MAX_RANK_WIDTH, 150.0f + MAX_RANKTIME_HEIGHT * nCntRank, 0.0f);

		//���_���W�̐ݒ�
		pVtx[0].pos.x = g_aRankTime[nCntRank].pos.x - MAX_RANK_WIDTH / 2;
		pVtx[0].pos.y = g_aRankTime[nCntRank].pos.y - MAX_RANKTIME_HEIGHT / 2;
		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = g_aRankTime[nCntRank].pos.x + MAX_RANK_WIDTH / 2;
		pVtx[1].pos.y = g_aRankTime[nCntRank].pos.y - MAX_RANKTIME_HEIGHT / 2;
		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = g_aRankTime[nCntRank].pos.x - MAX_RANK_WIDTH / 2;
		pVtx[2].pos.y = g_aRankTime[nCntRank].pos.y + MAX_RANKTIME_HEIGHT / 2;
		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = g_aRankTime[nCntRank].pos.x + MAX_RANK_WIDTH / 2;
		pVtx[3].pos.y = g_aRankTime[nCntRank].pos.y + MAX_RANKTIME_HEIGHT / 2;
		pVtx[3].pos.z = 0.0f;

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;//���_�f�[�^�̃|�C���^���l���i�߂�
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffRankColon->Unlock();

	//�����L���O���Z�b�g
	ResetRanking(FILE_TXT_NS);

	ResetRanking(FILE_TXT_MIN);

	Player* pPlayer = GetPlayer();	//�@�v���C���[���擾

	

	//�v���C���[�����񂾂Ƃ�
	if (pPlayer->nLife <= 0)
	{

		//���[�h�ݒ�
		SetGameState(GAMESTATE_END);// �Q�[�����I��������
		//�^�C�}�[�̕b�E��
		SetRanking(GetNs(), GetMin());
	}
	else
	{

		//�^�C�}�[�̕b�E��
		SetRanking(GetNs(), GetMin());

	}
}
//----------------------------
//�����L���O�̏I������
//----------------------------
void UninitRanking(void)
{
	//�e�N�X�`���̔j��(����)
	if (g_pTextureRank != NULL)
	{
		g_pTextureRank->Release();
		g_pTextureRank = NULL;
	}

	//�e�N�X�`���̔j��(�^�C�}�[)
	if (g_pTextureRankTime != NULL)
	{
		g_pTextureRankTime->Release();
		g_pTextureRankTime = NULL;
	}

	//�e�N�X�`���̔j��(�w�i)
	if (g_pTextureBKG != NULL)
	{
		g_pTextureBKG->Release();
		g_pTextureBKG = NULL;
	}

	//�e�N�X�`���̔j��(:)
	if (g_pTextureRankColon != NULL)
	{
		g_pTextureRankColon->Release();
		g_pTextureRankColon = NULL;
	}

	//���_�o�b�t�@�̔j��(����)
	if (g_pVtxBuffRank != NULL)
	{
		g_pVtxBuffRank->Release();
		g_pVtxBuffRank = NULL;
	}

	//���_�o�b�t�@�̔j��(�b)
	if (g_pVtxBuffRankNs != NULL)
	{
		g_pVtxBuffRankNs->Release();
		g_pVtxBuffRankNs = NULL;
	}

	//���_�o�b�t�@�̔j��(��)
	if (g_pVtxBuffRankMin != NULL)
	{
		g_pVtxBuffRankMin->Release();
		g_pVtxBuffRankMin = NULL;
	}

	//���_�o�b�t�@�̔j��(�w�i)
	if (g_pVtxBuffBKG != NULL)
	{
		g_pVtxBuffBKG->Release();
		g_pVtxBuffBKG = NULL;
	}

	//���_�o�b�t�@�̔j��(:)
	if (g_pVtxBuffRankColon != NULL)
	{
		g_pVtxBuffRankColon->Release();
		g_pVtxBuffRankColon = NULL;
	}

}
//----------------------------
//�����L���O�̍X�V����
//----------------------------
void UpdateRanking(void)
{
	int nRankTime;

	g_nTimerRanking += 1;
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx;

	//�b
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffRankNs->Lock(0, 0, (void**)&pVtx, 0);

	for (nRankTime = 0; nRankTime < MAX_RANKNS_NUM * MAX_RANK; nRankTime++)
	{//�b�̌�������
		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		pVtx += 4;
	}

	pVtx -= 4 * MAX_RANKNS_NUM * MAX_RANK;

	//�Y���^�C�}�[�����L���O(�b)��_��
	if (g_nRankUpdate != -1 && g_nTimerRanking >= 0)
	{//�����N�C�����ĂāA���A�^�C�}�[���[���ȏゾ������
		pVtx += 4 * MAX_RANKNS_NUM * g_nRankUpdate;

		for (nRankTime = 0; nRankTime < MAX_RANKNS_NUM; nRankTime++)
		{//�b�̌�������
			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(0.3f, 1.0f, 0.3f, 1.0f);
			pVtx[1].col = D3DXCOLOR(0.3f, 1.0f, 0.3f, 1.0f);
			pVtx[2].col = D3DXCOLOR(0.3f, 1.0f, 0.3f, 1.0f);
			pVtx[3].col = D3DXCOLOR(0.3f, 1.0f, 0.3f, 1.0f);

			pVtx += 4;
		}
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffRankNs->Unlock();

	//��
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffRankMin->Lock(0, 0, (void**)&pVtx, 0);

	for (nRankTime = 0; nRankTime < MAX_RANKMIN_NUM * MAX_RANK; nRankTime++)
	{//���̌�������
		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		pVtx += 4;
	}

	pVtx -= 4 * MAX_RANKMIN_NUM * MAX_RANK;

	//�Y���^�C�}�[�����L���O(��)��_��
	if (g_nRankUpdate != -1 && g_nTimerRanking >= 0)
	{//�����N�C�����ĂāA���A�^�C�}�[���[���ȏゾ������
		pVtx += 4 * MAX_RANKMIN_NUM * g_nRankUpdate;

		for (nRankTime = 0; nRankTime < MAX_RANKMIN_NUM; nRankTime++)
		{//���̌�������
			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(0.3f, 1.0f, 0.3f, 1.0f);
			pVtx[1].col = D3DXCOLOR(0.3f, 1.0f, 0.3f, 1.0f);
			pVtx[2].col = D3DXCOLOR(0.3f, 1.0f, 0.3f, 1.0f);
			pVtx[3].col = D3DXCOLOR(0.3f, 1.0f, 0.3f, 1.0f);

			pVtx += 4;
		}
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffRankMin->Unlock();

	//:
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffRankColon->Lock(0, 0, (void**)&pVtx, 0);

	for (nRankTime = 0; nRankTime < MAX_RANK; nRankTime++)
	{//:�̏��ʕ���
		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		pVtx += 4;
	}

	pVtx -= 4 * MAX_RANK;

	//�Y���^�C�}�[�����L���O(:)��_��
	if (g_nRankUpdate != -1 && g_nTimerRanking >= 0)
	{//�����N�C�����ĂāA���A�^�C�}�[���[���ȏゾ������
		pVtx += 4 * g_nRankUpdate;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(0.3f, 1.0f, 0.3f, 1.0f);
		pVtx[1].col = D3DXCOLOR(0.3f, 1.0f, 0.3f, 1.0f);
		pVtx[2].col = D3DXCOLOR(0.3f, 1.0f, 0.3f, 1.0f);
		pVtx[3].col = D3DXCOLOR(0.3f, 1.0f, 0.3f, 1.0f);

	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffRankColon->Unlock();

	//�^�C�}�[���}�C�i�X�ɂ���
	if (g_nTimerRanking >= 5)
	{
		g_nTimerRanking *= -1;
	}

	if (KeybordTrigger(DIK_RETURN) == true || JoyPadTrigger(JOYKEY_A) == true || OnMouseDown(MOUSE_L) == true)
	{
		//���[�h�ݒ�(�Q�[����ʂɈڍs)
		SetFade(MODE_TITLE);
	}
}
//----------------------------
//�����L���O�̕`�揈��
//----------------------------
void DrawRanking(void)
{
	int nCntTime;

	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�ւ̃|�C���^
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�w�i
	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffBKG, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureBKG);

	//�|���S���`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
		0,							//�`�悷��ŏ��̒��_�C���f�b�N�X
		2);

	//�b
	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffRankNs, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�����L���O�X�R�A�̕`��
	for (nCntTime = 0; nCntTime < MAX_RANK * MAX_RANKNS_NUM; nCntTime++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureRankTime);
		//�|���S���`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
			4 * nCntTime,							//�`�悷��ŏ��̒��_�C���f�b�N�X
			2);
	}

	//��
	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffRankMin, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�����L���O�X�R�A�̕`��
	for (nCntTime = 0; nCntTime < MAX_RANK * MAX_RANKMIN_NUM; nCntTime++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureRankTime);
		//�|���S���`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
			4 * nCntTime,							//�`�悷��ŏ��̒��_�C���f�b�N�X
			2);
	}

	//����
	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffRank, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�G�t�F�N�g�̕`��
	for (nCntTime = 0; nCntTime < MAX_RANK; nCntTime++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureRank);
		//�|���S���`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
			4 * nCntTime,						   //�`�悷��ŏ��̒��_�C���f�b�N�X
			2);
	}

	//:
	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffRankColon, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�G�t�F�N�g�̕`��
	for (nCntTime = 0; nCntTime < MAX_RANK; nCntTime++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureRankColon);
		//�|���S���`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
			4 * nCntTime,						   //�`�悷��ŏ��̒��_�C���f�b�N�X
			2);
	}

}
//----------------------------
//�����L���O�̃��Z�b�g
//----------------------------
void ResetRanking(const char* DateScore)
{
	int nCnt = 0;
	int foge = NULL;

	//�����L���O�X�R�A���̏����ݒ�
	FILE* pFile = fopen(FILE_TXT_NS, "r");

	if (pFile == NULL)
	{

	}
	else
	{

		//�ǂݍ���
		for (nCnt = 0; nCnt < MAX_RANK; nCnt++)
		{
			foge = fscanf(pFile, "%d\n", &g_aRankTime[nCnt].nTime);
		}

		fclose(pFile);
	}

	//�����L���O�X�R�A���̏����ݒ�
	pFile = fopen(FILE_TXT_MIN, "r");

	if (pFile == NULL)
	{

	}
	else
	{

		//�ǂݍ���
		for (nCnt = 0; nCnt < MAX_RANK; nCnt++)
		{
			foge = fscanf(pFile, "%d\n", &g_aRankTime[nCnt].nMin);
		}

		fclose(pFile);
	}

}
//----------------------------
//�����L���O�̐ݒ�
//----------------------------
void SetRanking(int ntime,int nmin)
{
	Player* pPlayer = GetPlayer();
	int nCntRank;
	int nSelect;
	int nTemp;
	int aPosTexU[MAX_RANKNS_NUM] = {};//�i���̐������i�[(�b)
	int aPosTexu[MAX_RANKMIN_NUM] = {};//�i���̐������i�[(��)
	int nData1,nData2,nData3,nData4;
	int nCnt;

	//---�����L���O�^�C�}�[�̕��ёւ�
	//-----�w��^�C�}�[�������N�C�������� g_nRankUpdate ���X�V
	if (pPlayer->nLife > 0)
	{
		if (ntime >= g_aRankTime[MAX_RANK - 1].nTime)//�\�[�g����
		{
			g_aRankTime[MAX_RANK - 1].nTime = ntime;

			for (nCntRank = 0; nCntRank < MAX_RANK - 1; nCntRank++)
			{
				for (nSelect = nCntRank + 1; nSelect < MAX_RANK; nSelect++)
				{
					if (g_aRankTime[nCntRank].nTime <= g_aRankTime[nSelect].nTime)
					{
						nTemp = g_aRankTime[nCntRank].nTime;
						g_aRankTime[nCntRank].nTime = g_aRankTime[nSelect].nTime;
						g_aRankTime[nSelect].nTime = nTemp;
					}
				}
			}
			//���ʂ��Ԃ�����
			for (nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
			{
				if (g_aRankTime[nCntRank].nTime == ntime)
				{
					g_nRankUpdate = g_aRankTime[nCntRank].nRank - 1;
				}
			}
		}

		if (nmin >= g_aRankTime[MAX_RANK - 1].nMin)//�\�[�g����
		{
			g_aRankTime[MAX_RANK - 1].nMin = nmin;

			for (nCntRank = 0; nCntRank < MAX_RANK - 1; nCntRank++)
			{
				for (nSelect = nCntRank + 1; nSelect < MAX_RANK; nSelect++)
				{
					if (g_aRankTime[nCntRank].nMin <= g_aRankTime[nSelect].nMin)
					{
						nTemp = g_aRankTime[nCntRank].nMin;
						g_aRankTime[nCntRank].nMin = g_aRankTime[nSelect].nMin;
						g_aRankTime[nSelect].nMin = nTemp;
					}
				}
			}
			//���ʂ��Ԃ�����
			for (nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
			{
				if (g_aRankTime[nCntRank].nMin == nmin)
				{
					g_nRankUpdate = g_aRankTime[nCntRank].nRank - 1;
				}
			}
		}
	}
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx;

	//�b
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffRankNs->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
	{
		nData1 = 100;
		nData2 = 10;

		//�����Ƃɕ�������(�b)
		for (nCnt = 0; nCnt < MAX_RANKNS_NUM; nCnt++)
		{
			aPosTexU[nCnt] = (g_aRankTime[nCntRank].nTime % nData1 / nData2);
			nData1 = nData1 / 10;
			nData2 = nData2 / 10;

			//-----�e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f + (0.1f * aPosTexU[nCnt]), 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.1f + (0.1f * aPosTexU[nCnt]), 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f + (0.1f * aPosTexU[nCnt]), 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.1f + (0.1f * aPosTexU[nCnt]), 1.0f);

			pVtx += 4;
		}
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffRankNs->Unlock();

	//��
	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffRankMin->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
	{
		nData3 = 100;
		nData4 = 10;

		//�����Ƃɕ�������(��)
		for (nCnt = 0; nCnt < MAX_RANKMIN_NUM; nCnt++)
		{
			aPosTexu[nCnt] = (g_aRankTime[nCntRank].nMin % nData3 / nData4);
			nData3 /= 10;
			nData4 /= 10;

			//-----�e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.1f * aPosTexu[nCnt], 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.1f + (0.1f * aPosTexu[nCnt]), 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.1f * aPosTexu[nCnt], 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.1f + (0.1f * aPosTexu[nCnt]), 1.0f);

			pVtx += 4;
		}
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffRankMin->Unlock();

	//���ʂ���������
	//�����L���O�^�C�}�[���̏����ݒ�
	FILE* pFile = fopen(FILE_TXT_NS, "w");

	if (pFile == NULL)
	{

	}
	else
	{

		//��������
		for (int nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
		{
			fprintf(pFile, "%d\n", g_aRankTime[nCntRank].nTime);
		}

		fclose(pFile);
	}

	//�����L���O�^�C�}�[���̏����ݒ�
	pFile = fopen(FILE_TXT_MIN, "w");

	if (pFile == NULL)
	{

	}
	else
	{

		//��������
		for (int nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
		{
			fprintf(pFile, "%d\n", g_aRankTime[nCntRank].nMin);
		}

		fclose(pFile);
	}

}