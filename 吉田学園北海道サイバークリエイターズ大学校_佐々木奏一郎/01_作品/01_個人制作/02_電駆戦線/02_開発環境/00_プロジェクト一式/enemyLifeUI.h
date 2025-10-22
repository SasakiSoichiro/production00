//**************************************
//
// �G�̗̑�UI���� [enemyLifeUI.h]
// Author:Sasaki Soichiro
//
//**************************************
#ifndef _ENEMYLIFEUI_H_ // ���̃}�N����`������Ă��Ȃ�������
#define _ENEMYLIFEUI_H_ // ��d�C���N���[�h�h�~�̃}�N����`

//******************
// �C���N���[�h
//******************
#include "main.h"
#include "objectBillboard.h"

//************************
// �G�̗̑�UI�N���X
//************************
class CEnemyLifeUI :public CObjectBillboard
{
public:
	CEnemyLifeUI(int nPriority = 6);	// �R���X�g���N�^
	~CEnemyLifeUI();					// �f�X�g���N�^
	static CEnemyLifeUI* Create(D3DXVECTOR3 pos,D3DXVECTOR2 offset, int nIdx);// �C���X�^���X����
	HRESULT Init(D3DXVECTOR3 pos);	// ������
	void Uninit(void);				// �I��
	void Update(void);				// �X�V
	void Draw(void);				// �`��
	void SetPos(D3DXVECTOR3 pos);	// �ʒu
	void SetRot(D3DXVECTOR3 rot);	// ����
	D3DXVECTOR3 GetPos(void);		// �ʒu���̎擾
	D3DXVECTOR3 GetRot(void);		// �������̎擾
	void SetLife(int nLife);		// �I�����邩�̔��f
private:
	int m_nIdxTexture[2];		// �g���e�N�X�`���̔ԍ�
	int m_nIdx;					// �C���f�b�N�X
	int m_nUseTexture;			// ���ݎg���Ă���e�N�X�`��
};
#endif