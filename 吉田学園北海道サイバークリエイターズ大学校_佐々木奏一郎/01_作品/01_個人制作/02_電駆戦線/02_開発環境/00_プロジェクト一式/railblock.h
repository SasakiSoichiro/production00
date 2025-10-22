//**************************************
//
// ���[���̃u���b�N���� [railblock.h]
// Author:Sasaki Soichiro
//
//**************************************
#ifndef _RAILBLOCK_H_ // ���̃}�N����`������Ă��Ȃ�������
#define _RAILBLOCK_H_ // ��d�C���N���[�h�h�~�̃}�N����`

//******************
// �C���N���[�h
//******************
#include "main.h"
#include "objectX.h"

//************************
// ���[���̃u���b�N�N���X
//************************
class CRailBlock :public CObjectX
{
public:
	// ���
	typedef enum
	{
		STATE_NONE=0,// �����Ȃ�
		STATE_DRAG,// �}�E�X�ł���ł���
		STATE_MAX
	}STATE;
	CRailBlock(int nPriority = 4);	// �R���X�g���N�^
	~CRailBlock();					// �f�X�g���N�^
	static CRailBlock* Create(D3DXVECTOR3 pos);// �C���X�^���X����
	HRESULT Init(D3DXVECTOR3 pos);	// ������
	void Uninit(void);				// �I��
	void Update(void);				// �X�V
	void Draw(void);				// �`��
	void SetPos(D3DXVECTOR3 pos);	// �ʒu
	void SetRot(D3DXVECTOR3 rot);	// ����
	D3DXVECTOR3 GetPos(void);		// �ʒu���擾
	D3DXVECTOR3 GetRot(void);		// �������擾
	bool CollisionCursor(void);		// �}�E�X�Ƃ̓����蔻��
	void Drag(void);				// �͂�ňړ�
private:
	int m_nIdxXFile;		// �g���Ă���X�t�@�C���̔ԍ�
	static int m_nNumAll;	// ���݂̐�
	int m_nIdx;				// �ԍ�
	STATE m_State;			// ���
};
#endif