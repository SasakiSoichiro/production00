//*****************************************
//
// �p�[�e�B�N������ [particle.h]
// Author:Sasaki Soichiro
//
//*****************************************
#ifndef _PARTICLE_H_ // ���̃}�N����`������Ă��Ȃ�������
#define _PARTICLE_H_ // ��d�C���N���[�h�h�~�̃}�N����`

//******************
// �C���N���[�h
//******************
#include "main.h"
#include "object.h"

//********************
// �p�[�e�B�N���N���X
//********************
class CParticle :public CObject
{
public:
	CParticle(int nPriority=3);	// �R���X�g���N�^
	~CParticle();				// �f�X�g���N�^
	static CParticle* Create(D3DXVECTOR3 pos, D3DXCOLOR col);// �C���X�^���X����
	HRESULT Init(D3DXVECTOR3 pos);	// ������
	void Uninit(void);				// �I��
	void Update(void);				// �X�V		
	void Draw(void);				// �`��
	void SetPos(D3DXVECTOR3 pos);	// �ʒu�̐ݒ�	
	void SetRot(D3DXVECTOR3 rot);	// �����̐ݒ�
	void SetCol(D3DXCOLOR col);		// �F�̐ݒ�
	D3DXVECTOR3 GetPos(void) { return m_pos; }	// �ʒu���̎擾
	D3DXVECTOR2 GetSize(void){ return m_size; }	// �傫�����̐ݒ�
private:
	LPDIRECT3DTEXTURE9 m_pTexture;		// �e�N�X�`���̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// ���_���̃|�C���^
	D3DXVECTOR3 m_pos;	// �ʒu
	D3DXVECTOR3 m_rot;	// ����
	D3DXVECTOR2 m_size;	// �傫��
	D3DXCOLOR m_col;	// �F
	float m_fLength;	// �ړ�����
	float m_fRad;		// ���a
	int m_nAngle;		// ����
	int m_nLife;		// ����
};
#endif