//**************************************
//
// �O�Տ��� [orbit.h]
// Author:Sasaki Soichiro
//
//**************************************
#ifndef _ORBIT_H_// ���̃}�N����`������Ă��Ȃ�������
#define _ORBIT_H_// 2�d�C���N���[�h�h�~�̃}�N����`

//***********************
// �C���N���[�h
//***********************
#include "main.h"
#include "object.h"

//********************
// �}�N����`
//********************
#define MAX_ORBITVTX (30)


//*********************
// �O�ՃN���X
//*********************
class COrbit :public CObject
{
public:
	COrbit(int nPriority = 2);	// �R���X�g���N�^
	~COrbit();					// �f�X�g���N�^
	static COrbit* Create(D3DXVECTOR3 pos);	// �C���X�^���X����
	HRESULT Init(D3DXVECTOR3 pos);			// ������
	void Uninit(void);						// �I��
	void Update(void);						// �X�V
	void Draw(void);						// �`��
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; };		// �ʒu�̐ݒ�
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; };		// �����̐ݒ�
	void SetPosS(D3DXVECTOR3 pos0, D3DXVECTOR3 pos1);	// 2�_�̈ʒu�ݒ�
	D3DXVECTOR3 GetPos(void) { return m_pos; };			// �ʒu���
private:
	LPDIRECT3DTEXTURE9 m_pTexture = NULL;		// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff = NULL;	// �C���f�b�N�X�ւ̃|�C���^
	D3DXVECTOR3 m_pos;							// �ʒu
	D3DXVECTOR3 m_rot;							// ����
	D3DXMATRIX m_mtxWorld;						// ���[���h�}�g���b�N�X
	int m_Time;									// ����
	int m_Frame;								// �t���[��
	D3DXVECTOR3 m_FPos, m_SPos;					// ��_�̈ʒu
	D3DXVECTOR3 m_oldFPos[MAX_ORBITVTX / 2 - 1], m_oldSPos[MAX_ORBITVTX / 2 - 1];// ��_�̑O�t���[���̈ʒu
};

#endif