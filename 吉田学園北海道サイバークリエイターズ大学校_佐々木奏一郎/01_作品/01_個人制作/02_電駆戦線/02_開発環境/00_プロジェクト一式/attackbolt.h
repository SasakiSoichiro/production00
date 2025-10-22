//**************************************
//
// �{���g�U������ [attackbolt.h]
// Author:Sasaki Soichiro
//
//**************************************
#ifndef _ATTACKBOLT_H_ // ���̃}�N����`������Ă��Ȃ�������
#define _ATTACKBOLT_H_ // ��d�C���N���[�h�h�~�̃}�N����`

//******************
// �C���N���[�h
//******************
#include "main.h"
#include "objectX.h"

//************************
// �{���g�U���̃N���X
//************************
class CAttackBolt :public CObjectX
{
public:
	CAttackBolt(int nPriority = 4);	// �R���X�g���N�^
	~CAttackBolt();					// �f�X�g���N�^
	static CAttackBolt* Create(D3DXVECTOR3 pos,float fAngle);// �C���X�^���X����
	HRESULT Init(D3DXVECTOR3 pos);	// ������
	void Uninit(void);				// �I��
	void Update(void);				// �X�V
	void Draw(void);				// �`��
	void SetPos(D3DXVECTOR3 pos);	// �ʒu
	void SetRot(D3DXVECTOR3 rot);	// ����
	void SetAngle(float fAngle) { m_fAngle = fAngle; }// �����̐ݒ�
	D3DXVECTOR3 GetPos(void);		// �ʒu���̎擾
	D3DXVECTOR3 GetRot(void);		// �������̎擾
private:
	int m_nIdxXFile;	// �g���e�N�X�`���̔ԍ�
	D3DXVECTOR3 m_move;	// ��������
	float m_fAngle;		// ����
	int m_nLife;		// ���C�t
	static constexpr float jump = 2.5f;
	static constexpr float speed = 1.2f;
	static constexpr float horizon = 0.08f;
	static constexpr int maxLife = 80;
	static const D3DXVECTOR3 ROT_MOVE;
};
#endif