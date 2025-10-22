//=============================================================================
//
//	�e�̏��� [shadowS.h]
// Author:Sasaki Soichiro
//
//=============================================================================
#ifndef _SHADOWS_H_// ���̃}�N����`������Ă��Ȃ�������
#define _SHADOWS_H_// 2�d�C���N���[�h�h�~�̃}�N����`
//**************
// �C���N���[�h
//**************
#include "main.h"
#include "objectX.h"

//***************
// �e�N���X
//***************
class CShadowS :public CObjectX
{
public:
	CShadowS(int nPriority = 3);// �R���X�g���N�^
	~CShadowS();				// �f�X�g���N�^
	static CShadowS* Create(D3DXVECTOR3 pos);	// �C���X�^���X����
	HRESULT Init(D3DXVECTOR3 pos);				// ������
	void Uninit(void);							// �I��
	void Update(void);							// �X�V
	void Draw(void);							// �`��
	void SetPos(D3DXVECTOR3 pos);				// �ʒu�̐ݒ�
private:
	int m_nIdxXFile;					// �g���Ă���X�t�@�C���̔ԍ�
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// ���_���̃|�C���^
	D3DXVECTOR3 m_pos;					// �ʒu
	D3DXVECTOR3 m_rot;					// ����
	D3DXCOLOR m_col;					// �F
	D3DXVECTOR2 m_size;					// �傫��
};

#endif