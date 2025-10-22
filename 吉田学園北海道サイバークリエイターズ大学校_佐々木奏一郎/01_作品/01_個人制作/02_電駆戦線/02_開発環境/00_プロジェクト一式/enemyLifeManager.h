//*************************************************
// 
// �G�̗̑̓}�l�[�W���[���� [enemyLifeManager.h]
// Author:Sasaki Soichiro
//
//*************************************************
#ifndef _ENEMYLIFEMANAGER_H_ // ���̃}�N����`������Ă��Ȃ�������
#define _ENEMYLIFEMANAGER_H_ // ��d�C���N���[�h�h�~�̃}�N����`

//******************
// �C���N���[�h
//******************
#include "main.h"
#include "object.h"

class CEnemyLifeUI;

//****************************
// �G�̗̑̓}�l�[�W���[�N���X
//****************************
class CEnemyLifeManager :public CObject
{
public:
	CEnemyLifeManager(int nPriority = 1);	// �R���X�g���N�^
	~CEnemyLifeManager();					// �f�X�g���N�^
	static CEnemyLifeManager* Create(D3DXVECTOR3 pos,int nLife);
	HRESULT Init(D3DXVECTOR3 pos);	// ������
	void Uninit(void);				// �I��
	void Update(void);				// �X�V
	void Draw(void);				// �`��
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }	// �ʒu�ݒ�
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }	// �����ݒ�
	void SetLife(int nLife);	// �����̐ݒ�	
	D3DXVECTOR3 GetPos(void) { return m_pos; }		// �ʒu���擾
	int GetLife(void) { return m_nLife; }			// �������̎擾
private:
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;
	int m_nLife;
	int m_nOffsetLife;
	CEnemyLifeUI* m_pLifeUI[5];
	static constexpr float size = 7.0f;
};
#endif