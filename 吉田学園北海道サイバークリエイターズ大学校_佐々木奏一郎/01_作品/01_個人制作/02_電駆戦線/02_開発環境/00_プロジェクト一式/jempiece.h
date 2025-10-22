//**************************************
//
// ��΂̔j�Џ��� [jempiece.h]
// Author:Sasaki Soichiro
//
//**************************************
#ifndef _JEMPIECE_H_ // ���̃}�N����`������Ă��Ȃ�������
#define _JEMPIECE_H_ // ��d�C���N���[�h�h�~�̃}�N����`

//******************
// �C���N���[�h
//******************
#include "main.h"
#include "objectX.h"

//************************
// ��΂̔j�ЃN���X
//************************
class CJemPiece :public CObjectX
{
public:
	CJemPiece(int nPriority = 3);	// �R���X�g���N�^
	~CJemPiece();					// �f�X�g���N�^
	static CJemPiece* Create(D3DXVECTOR3 pos, float fAngle,int nType);// �C���X�^���X����
	HRESULT Init(D3DXVECTOR3 pos);	// ������
	void Uninit(void);				// �I��
	void Update(void);				// �X�V
	void Draw(void);				// �`��
	void SetPos(D3DXVECTOR3 pos);	// �ʒu
	void SetRot(D3DXVECTOR3 rot);	// ����
	D3DXVECTOR3 GetPos(void);		// �ʒu���̎擾
	D3DXVECTOR3 GetRot(void);		// �������̎擾
private:
	int m_nIdxXFile;	// �g���e�N�X�`���̔ԍ�
	D3DXVECTOR3 m_move;	// ��������
	float m_fAngle;		// ����
	int m_nLife;		// ���C�t
	int m_nType;		// ���
};
#endif