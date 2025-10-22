//*****************************************
//
// �j�Ѓp�[�e�B�N������ [pieceparticle.h]
// Author:Sasaki Soichiro
//
//*****************************************
#ifndef _PIECEPARTICLE_H_ // ���̃}�N����`������Ă��Ȃ�������
#define _PIECEPARTICLE_H_ // ��d�C���N���[�h�h�~�̃}�N����`

//******************
// �C���N���[�h
//******************
#include "main.h"
#include "object.h"

//************************
// �j�Ѓp�[�e�B�N���N���X
//************************
class CPieceParticle :public CObject
{
public:
	CPieceParticle(int nPriority = 3);	// �R���X�g���N�^
	~CPieceParticle();				// �f�X�g���N�^
	static CPieceParticle* Create(D3DXVECTOR3 pos,int nAngle);// �C���X�^���X����
	HRESULT Init(D3DXVECTOR3 pos);	// ������
	void Uninit(void);				// �I��
	void Update(void);				// �X�V		
	void Draw(void);				// �`��
	void SetPos(D3DXVECTOR3 pos);	// �ʒu�̐ݒ�	
	void SetRot(D3DXVECTOR3 rot);	// �����̐ݒ�
	D3DXVECTOR3 GetPos(void) { return m_pos; }	// �ʒu���̎擾
private:
	D3DXVECTOR3 m_pos;	// �ʒu
	int m_nAngle;		// ����
};
#endif