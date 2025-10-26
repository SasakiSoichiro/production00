//**********************************************
// 
// �ԃ}�l�[�W���[���� [carManager.h]
// Author:Sasaki Soichiro
//
//**********************************************
#ifndef _CARMANAGER_H_ // ���̃}�N����`������Ă��Ȃ�������
#define _CARMANAGER_H_ // ��d�C���N���[�h�h�~�̃}�N����`

//******************
// �C���N���[�h
//******************
#include "main.h"
#include "object.h"

//***********
// �O���錾
//***********
class CCarBody;


//****************************
// �ԃ}�l�[�W���[�N���X
//****************************
class CCar:CObject
{
public:
	CCar();				// �R���X�g���N�^
	~CCar();			// �f�X�g���N�^

	static CCar* Create(D3DXVECTOR3 pos);
	HRESULT Init(D3DXVECTOR3  pos);	// ������
	void Uninit(void);	// �I��
	void Update(void);	// �X�V
	void Draw(void);	// �`��
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }
	D3DXVECTOR3 GetPos(void) { return m_pos; }
private:
	CCarBody* m_pCarBody;
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;
	D3DXMATRIX m_mtxWorld;	// ���[���h�}�g���b�N�X
};
#endif