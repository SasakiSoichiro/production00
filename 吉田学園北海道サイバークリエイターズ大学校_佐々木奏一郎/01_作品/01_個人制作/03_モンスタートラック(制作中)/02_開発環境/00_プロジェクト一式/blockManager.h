//**********************************************
// 
// �u���b�N�}�l�[�W���[���� [blockManager.h]
// Author:Sasaki Soichiro
//
//**********************************************
#ifndef _BLOCKMANAGER_H_ // ���̃}�N����`������Ă��Ȃ�������
#define _BLOCKMANAGER_H_ // ��d�C���N���[�h�h�~�̃}�N����`

//******************
// �C���N���[�h
//******************
#include "main.h"
#include <vector>
#include "Xmodel.h"
#include "block.h"


//****************************
// �u���b�N�}�l�[�W���[�N���X
//****************************
class CBlockManager
{
public:
	CBlockManager();	// �R���X�g���N�^
	~CBlockManager();	// �f�X�g���N�^
	HRESULT Init(void);	// ������
	void Uninit(void);	// �I��
	void Update(void);	// �X�V
	void Set(CBlock*block);// �u���b�N���̐ݒ�
	D3DXVECTOR3 Collision(D3DXVECTOR3 pos, D3DXVECTOR3 posOld);	// �����蔻��
	bool bCollision(D3DXVECTOR3 pos);							// �����蔻��
private:
	std::vector<CBlock*> m_Block;// �u���b�N�̃|�C���^
};
#endif