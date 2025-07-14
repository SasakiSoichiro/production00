//**************************************
//
// �u���b�N���� [block.h]
// Author:Sasaki Soichiro
//
//**************************************
#ifndef _BLOCK_H_ // ���̃}�N����`������Ă��Ȃ�������
#define _BLOCK_H_ // ��d�C���N���[�h�h�~�̃}�N����`

//******************
// �C���N���[�h
//******************
#include "main.h"
#include "object.h"
#include "objectX.h"

//********************
// �v���C���[�N���X
//********************
class CBlock :public CObjectX
{
public:
	typedef enum
	{
		STATE_NONE=0,
		STATE_DRAG,
		STATE_MAX
	}STATE;
	CBlock(int nPriority = 4);	// �R���X�g���N�^
	~CBlock();					// �f�X�g���N�^
	static CBlock* Create(D3DXVECTOR3 pos);// �C���X�^���X����
	HRESULT Init(D3DXVECTOR3 pos);	// ������
	void Uninit(void);				// �I��
	void Update(void);				// �X�V
	void Draw(void);				// �`��
	void SetPos(D3DXVECTOR3 pos);	// �ʒu
	void SetRot(D3DXVECTOR3 rot);	// ����
	D3DXVECTOR3 GetPos(void);		// �ʒu���̎擾
	D3DXVECTOR3 GetRot(void);
	bool CollisionCursor(void);
	void Drag(void);
private:
	int m_nIdxXFile;
	static int m_nNumAll;
	int m_nIdx;
	STATE m_State;
};
#endif