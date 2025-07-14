//=============================================================================
//
//	�v���C���[���� [player.h]
// Author : ���X�ؑt��Y
//
//=============================================================================
#ifndef _PLAYER_H_				//���̃}�N����`������Ă��Ȃ�������
#define _PLAYER_H_				//2�d�C���N���[�h�h�~�̃}�N����`
#define GRAVI (0.15f)			//�d��
#define JUMP (8.0f)				//�W�����v��
#define SLIMEJUMP (4.0f)
#define TRANPORINJUMP (12.0f)
#define MOVE_X (3.0f)			//X���ړ���
#define MAX_POSCIRCLE (15.0f)	//�T�[�N�����a
#define MAX_PGPOS (15.0f)		//�|�S�̓����蔻����W
#define MAX_PYPOS (45.0f)		//�v���C���[�̓����蔻����W
#include "block.h"


//�v���C���[��Ԃ̎��
typedef enum
{
	PLAYERSTATE_APPEAR=0,	//�o����ԁi�_�Łj
	PLAYERSTATE_NORMAL,		//�ʏ���
	PLAYERSTATE_DAMAGE,		//�_���[�W���
	PLAYERSTATE_DEATH,		//���S���
	PLAYERSTATE_MAX
}PLAYERSTATE;
//�v���C���[�\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;			//���݂̈ʒu
	D3DXVECTOR3 posPGCircle;	//�|�S�����蔻��p�̈ʒu
	D3DXVECTOR3 posPYCircle;	//�v���C���[�����蔻��p�̈ʒu
	D3DXVECTOR3 posPGOld;		//�O��̃|�S�����蔻��p�̈ʒu
	D3DXVECTOR3 posPYOld;		//�O��̃v���C���[�����蔻��p�̈ʒu
	D3DXVECTOR3 move;			//�ړ���
	PLAYERSTATE state;			//�v���C���[�̏��
	int nCntState;				//��ԊǗ��J�E���^�[
	int nLife;					//�̗�
	bool bDisp;					//�\�����邩���Ȃ���
	D3DXVECTOR3 rot;			//����
	float fLength;				//�Ίp���̒���
	float fAngle;				//�Ίp���̊p�x
	int nCounterAnim;			//�J�E���^�[
	int nPatternAnim;			//�p�^�[��No.
	bool bJump;					//�W�����v���Ă��邩���ĂȂ���
	bool bRightMove;			//�E������
	bool bMove;					//�����Ă��邩�Ƃ܂��Ă��邩
	Block* pBlock;				//�Ώۃu���b�N�ւ̃|�C���^
	bool bUse;					//�g���Ă��邩�ǂ���
}Player;
//�v���g�^�C�v�錾
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
Player* GetPlayer(void);
#endif