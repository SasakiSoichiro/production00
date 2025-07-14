//=============================================================================
//
//	�G�f�B�b�g���� [edit.h]
// Author : ���X�ؑt��Y
//
//=============================================================================
#ifndef _EDIT_H_//���̃}�N����`������Ă��Ȃ�������
#define _EDIT_H_//2�e�C���N���[�h�h�~�̃}�N����`

#include "main.h"

//�}�N����`
#define NUM_EDIT (200)
#define EDITTEXTURE (128)	// �e�N�X�`���̍ő吔
#define EDIT_MOVE (2.0f)
#define TEXTFILE "data\\STAGE\\stage.txt"

// �Ƃ̎��
typedef enum
{
	// ��2
	EDIT_HOUSE000_L = 0,
	EDIT_HOUSE000_r,

	// ��3
	EDIT_HOUSE01_L,
	EDIT_HOUSE01_R,

	// ��3
	EDIT_HOUSE04_L,
	EDIT_HOUSE04_R,

	// �ԗ��
	EDIT_IREIHI,

	// �Ŕ�
	EDIT_KANBAN,

	// ��
	EDIT_KURA,

	// �N���ƃN���̑�
	EDIT_KUMO,
	EDIT_KUMONOSU,

	// ������
	EDIT_TORIGOYA,

	// ���
	EDIT_WELL,

	// �d��(�ؐ�)
	EDIT_WTPOLE,

	// �͂�Ă��
	EDIT_DEADTREE,

	// �X�s�[�J�[
	EDIT_SPEACAR,

	// ��
	EDIT_KEY,
	EDIT_KEYBOTTOM,
	EDIT_KEYTOP,

	// ��
	EDIT_WALL00,
	EDIT_WALL01,
	EDIT_MAX

}EDITTYPE;

// �e�N�X�`���̍\����
typedef struct
{
	LPD3DXMESH pMesh;							// ���b�V���i���_���)�ւ̃|�C���^
	LPDIRECT3DTEXTURE9 apTexture[EDITTEXTURE];	// �e�N�X�`���ւ̃|�C���^
	LPD3DXBUFFER pBuffMat;						// �}�e���A���ւ̃|�C���^
	DWORD dwNumMat;								// �}�e���A���̐�
}EDITTEX;

// �\����
typedef struct
{
	EDITTEX tex[EDIT_MAX];				// �e�N�X�`�����
	D3DXVECTOR3 pos;					// �ʒu
	D3DXVECTOR3 move;					// �ړ�
	D3DXVECTOR3 rot;					// ����
	D3DXMATRIX mtxWorld;				// ���[���h�}�g���b�N�X
	D3DXVECTOR3 vtxMin, vtxMax;			// ���f���̍ŏ��l,�ő�l
	int nType;							// ���
	bool bUse;							// �g�p���Ă��邩

}EDITINFO;

static const char* X_EDIT[EDIT_MAX] =
{
	// ��2��
	"data\\model\\house000_L.x",
	"data\\model\\house000_r.x",


	// ��3��
	"data\\model\\house01_L.x",
	"data\\model\\house01_R.x",


	// ��4��
	"data\\model\\house04_L.x",
	"data\\model\\house04_R.x",


	// �ԗ��
	"data\\model\\ireihi.x",

	// �Ŕ�
	"data\\model\\kanban.x",

	// ��
	"data\\model\\kura.x",

	// �N���A�N���̑�
	"data\\model\\kumo.x",
	"data\\model\\kumonosu.x",

	// ������
	"data\\model\\torigoya.x",

	// ���
	"data\\model\\Well.x",

	// �d��(�ؐ�)
	"data\\model\\WoodenTelephonePole.x",

	// �͂�Ă��
	"data\\model\\deadtree000.x",

	// �X�s�[�J�[
	"data\\model\\speacar.x",

	// ��
	"data\\model\\key.x",
	"data\\model\\key_bottom.x",
	"data\\model\\key_top.x",

	// ��
	"data\\model\\wall00.x",
	"data\\model\\wall01.x",
};

// �v���g�^�C�v�錾
void InitEdit(void);
void UninitEdit(void);
void UpdateEdit(void);
void DrawEdit(void);
void SaveEdit(void);
void LoadEdit(void);
void ReloadEdit(void);
#endif