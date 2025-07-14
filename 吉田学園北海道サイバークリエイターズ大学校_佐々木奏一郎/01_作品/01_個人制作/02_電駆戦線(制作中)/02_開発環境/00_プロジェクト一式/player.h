//**************************************
//
// �v���C���[���� [player.h]
// Author:Sasaki Soichiro
//
//**************************************
#ifndef _PLAYER_H_ // ���̃}�N����`������Ă��Ȃ�������
#define _PLAYER_H_ // ��d�C���N���[�h�h�~�̃}�N����`

//******************
// �C���N���[�h
//******************
#include "main.h"
#include "object.h"
#include "objectX.h"
#include "motion.h"

//********************
// �v���C���[�N���X
//********************
class CPlayer :public CObject
{
public:
	typedef enum
	{
		STATE_NONE = 0,
		STATE_RAIL
	}STATE;
	typedef enum
	{
		MOTION_NUETORAL=0,
		MOTION_FLONT,
		MOTION_BACK,
		MOTION_LF,
		MOTION_LB,
		MOTION_RF,
		MOTION_RB,
		MOTION_FB,
		MOTION_BF,
	}MOTION;
	CPlayer(int nPriority = 4);	// �R���X�g���N�^
	~CPlayer();					// �f�X�g���N�^
	static CPlayer* Create(D3DXVECTOR3 pos);// �C���X�^���X����
	HRESULT Init(D3DXVECTOR3 pos);	// ������
	void Uninit(void);				// �I��
	void Update(void);				// �X�V
	void Draw(void);				// �`��
	void SetPos(D3DXVECTOR3 pos);	// �ʒu
	void SetRot(D3DXVECTOR3 rot);	// ����
	void SetState(STATE state) { m_State = state; }
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }	
	STATE GetState(void) { return m_State; }
	static int GetLife(void) { return m_nLife; }// ���C�t���̎擾
	void Posture(void);
private:
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_oldPos;
	D3DXVECTOR3 m_move;	// ����
	D3DXVECTOR3 m_rot;
	D3DXVECTOR3 m_rotDest;
	D3DXVECTOR3 m_vecF;
	D3DXVECTOR3 m_vecR;
	D3DXVECTOR3 m_vecU;
	D3DXMATRIX m_mtxWorld;
	float m_fAngle;
	static int m_nLife;
	int m_nIdxXFile;
	STATE m_State;
	CMotion* m_pMotion;		// ���f��(�p�[�c)�ւ̃|�C���^
};
#endif