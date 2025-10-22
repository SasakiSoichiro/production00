//********************************************
//
//	���[�V�������� [motion.h]
// Author:Sasaki Soichiro
//
//********************************************
#ifndef _MOTION_H_// ���̃}�N����`������Ă��Ȃ�������
#define _MOTION_H_// 2�d�C���N���[�h�h�~�̃}�N����`

//*****************
// �C���N���[�h
//*****************
#include "main.h"
#include "model.h"

//*****************
// �}�N����`
//*****************
#define PARTS_MAX (20)// �p�[�c���̍ő�
#define MAX_WORD (256)// �ǂݍ��ݎ��̕�����



//*******************
// ���[�V�����N���X
//*******************
class CMotion
{
public:
	//**************
// �L�[�̍\����
//**************
	typedef struct
	{
		float fPosX;// �ʒu
		float fPosY;
		float fPosZ;
		float fRotX;// ����
		float fRotY;
		float fRotZ;
	}KEY;

	//******************
	// �L�[���̍\����
	//******************
	typedef struct
	{
		int nFlame;		// �Đ��t���[��
		KEY aKey[20];	// �p�[�c�̍ő吔������//�L�[���

	}KEY_INFO;

	//***********************
	//���[�V�������̍\����
	//***********************
	typedef struct
	{
		bool bLoop;				// ���[�v���邩�ǂ���
		int nNumKey;			// �L�[�̑���
		KEY_INFO aKeyInfo[30];	// �L�[�̏��
	}MOTION_INFO;

	CMotion();		// �R���X�g���N�^
	~CMotion();		// �f�X�g���N�^
	static CMotion*Create(CModel** ppModel, int nNumModel,bool bSlow);	// �C���X�^���X����
	HRESULT Init(void);	// ������
	void Uninit(void);	// �I��
	void Update(void);	// �X�V
	void Draw(void);	// �`��
	void SetInfo(MOTION_INFO motionInfo);		// ���[�V�������̐ݒ�
	void SetMotion(int type);					// ���[�V�����̐ݒ�
	int GetType(void) { return m_type; }		// ��ޏ��擾
	bool GetFinish(void) { return m_bFinish; }	// ���[�V�������I��������ǂ���
	float Normalize(float fData0, float fData1);// ���K��
private:
	CModel** m_ppModel;				// ���f���̃|�C���^
	int m_nNumModel;				// ���f���̃p�[�c����
	MOTION_INFO m_aInfo[15];		// ���[�V�����̍ő吔
	int m_nNum;						// ���[�V�����̑���
	int m_type;						// ���[�V�����̎��
	//TYPE m_typeOld;				// ���[�V�����̎��
	bool m_bLoop;					// ���[�v���邩�ǂ���
	int m_nNumKey;					// �L�[�̑���
	int m_nKey;						// ���݂̃L�[No.
	int m_nCnt;						// ���[�V�����J�E���^�[
		
	bool m_bFinish;			// ���݂̃��[�V�������I�����Ă��邩�ǂ���
	bool m_bBlend;			// �u�����h���[�V���������邩�ǂ���
	int m_typeBlend;		// ���[�V�����̎��
	int m_nNumKeyBlend;		// �L�[�̑���
	int m_nKeyBlend;		// ���݂̃L�[No.
	int m_nCntBlend;		// ���[�V�����J�E���^�[
	int m_nFrameBlend;		// �u�����h�̃t���[����
	int m_nCntMotionBlend;	// ���[�V�����J�E���^�[
	bool m_bSlow;			// �X���[�ɂȂ邩
};

#endif