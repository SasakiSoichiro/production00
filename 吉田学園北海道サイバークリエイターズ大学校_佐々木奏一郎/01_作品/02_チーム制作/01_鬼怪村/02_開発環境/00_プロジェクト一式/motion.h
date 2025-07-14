//=============================================================================
//
//	���[�V�������� [motion.h]
// Author : SasakiSoichiro
//
//=============================================================================
#ifndef _MOTION_H_//���̃}�N����`������Ă��Ȃ�������
#define _MOTION_H_//2�e�C���N���[�h�h�~�̃}�N����`
#include "main.h"
#include "model.h"
#define PARTS_MAX (20)
#define MAX_WORD (256)

//���[�V�����̎��
typedef enum
{
	MOTIONTYPE_NEUTRAL = 0,	//���n
	MOTIONTYPE_MOVE,		//�ړ�
	MOTIONTYPE_RUN,			//�_�b�V��
	MOTIONTYPE_DAMAGE,		//�_���[�W
	MOTIONTYPE_DEATH,		//��
	MOTIONTYPE_BREATH,		//��J
	MOTIONTYPE_MAX
}MOTIONTYPE;

//�L�[�̍\����
typedef struct
{
	float fPosX;//�ʒu
	float fPosY;
	float fPosZ;
	float fRotX;//����
	float fRotY;
	float fRotZ;
}KEY;

//�L�[���̍\����
typedef struct
{
	int nFlame;//�Đ��t���[��
	KEY aKey[20];//�p�[�c�̍ő吔������//�L�[���

}KEY_INFO;

//���[�V�������̍\����
typedef struct
{
	bool bLoop;//���[�v���邩�ǂ���
	int nNumKey;//�L�[�̑���
	KEY_INFO aKeyInfo[30];//�L�[�̍ő吔//�L�[���
}MOTION_INFO;




//�v���C���[�\����
typedef struct
{
	Model aModel[16];	//���f���̃p�[�c��
	int nNumModel;		//���f���̃p�[�c����
	MOTION_INFO aMotionInfo[8];//���[�V�����̍ő吔
	int nNumMotion;//���[�V�����̑���
	MOTIONTYPE motionType;//���[�V�����̎��
	MOTIONTYPE motionTypeOld;//���[�V�����̎��
	bool bLoopMotion;//���[�v���邩�ǂ���
	int nNumKey;//�L�[�̑���
	int nKey;//���݂̃L�[No.
	int nCntMotion;//���[�V�����J�E���^�[

}Motion;

//�v���g�^�C�v�錾
void ReadScript(int nType);
void ReadModel(void);
//void CharacterSet(void);
//void ReadMotion(void);
//void ReadKey(void);
void UpdateMotion(void);
//void SetModel(void);
//void SetMotion(void);
//void SetKey(void);

#endif