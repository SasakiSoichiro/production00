//**************************************
//
// �ԏ��� [car.h]
// Author:Sasaki Soichiro
//
//**************************************
#ifndef _CAR_H_ // ���̃}�N����`������Ă��Ȃ�������
#define _CAR_H_ // ��d�C���N���[�h�h�~�̃}�N����`

//******************
// �C���N���[�h
//******************
#include "main.h"
#include "model.h"

class CWheel;

//********************
// �ԑ̃N���X
//********************
class CCarBody :public CModel
{
public:
	typedef enum
	{
		TYPE_BODY=0,
		TYPE_FLONTLEFT,
		TYPE_FLONTRIHGT,
		TYPE_REARLEFT,
		TYPE_REARRIGHT,
		TYPE_MAX
	}TYPE;
	CCarBody(int nPriority = 4);	// �R���X�g���N�^
	~CCarBody();					// �f�X�g���N�^
	static CCarBody* Create(D3DXVECTOR3 pos, const char* pFileName);// �C���X�^���X����
	HRESULT Init(D3DXVECTOR3 pos);	// ������
	void Uninit(void);				// �I��
	void Update(void);				// �X�V
	void Draw(void);				// �`��
	void SetWheel(void);			// �^�C���̈ʒu�ݒ�
	void WheelAttachY(void);		// �ڑ������̍���
	void SetPos(D3DXVECTOR3 pos);	// �ʒu
	void SetRot(D3DXVECTOR3 rot);	// ����
	void SetMove(D3DXVECTOR3 move);	// ���x
	D3DXVECTOR3 GetOldPos(void) { return m_oldPos; }	// �O�t���[���̈ʒu���擾
	D3DXVECTOR3 GetMove(void) { return m_move; }		// �������擾
	D3DXVECTOR3 GetVecU(void) { return m_vecU; }		// ��x�N�g�����擾
private:
	D3DXVECTOR3 m_oldPos;	// �O�t���[���̈ʒu
	D3DXVECTOR3 m_move;		// ����
	D3DXVECTOR3 m_rotDest;	// �ڕW�̌���
	D3DXVECTOR3 m_vecF;		// �O�x�N�g��
	D3DXVECTOR3 m_vecR;		// �E�x�N�g��
	D3DXVECTOR3 m_vecU;		// ��x�N�g��
	D3DXMATRIX m_mtxWorld;	// ���[���h�}�g���b�N�X
	CWheel* m_pWheel[4];	// �z�C�[��
	float m_fAngle;			// �n���h���̊p�x
	float m_fSpeed;
	int m_nIdxXFile;
	static constexpr float fWheelOffsetY = 50.0f;
	static constexpr float fWheelOffsetLeft = -30.0f;
	static constexpr float fWheelOffsetRight = 30.0f;
	static constexpr float fWheelOffsetFlont = 35.0f;
	static constexpr float fWheelOffsetRear = -35.0f;
	static constexpr float fDeltaAngle = 0.01f;
	static constexpr float fMaxSpeed = 4.0f;
	static constexpr float fMaxAngle = 1.0f;
};

#endif