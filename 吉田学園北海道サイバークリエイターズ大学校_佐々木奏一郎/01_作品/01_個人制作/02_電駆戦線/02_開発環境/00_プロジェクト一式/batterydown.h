//***************************************
// 
// �o�b�e���[�ቺUI���� [batterydown.h]
// Author:Sasaki Soichiro
//
//***************************************
#ifndef _BATTERYDOWN_H_ // ���̃}�N����`������Ă��Ȃ�������
#define _BATTERYDOWN_H_ // ��d�C���N���[�h�h�~�̃}�N����`

//******************
// �C���N���[�h
//******************
#include "main.h"
#include "object2D.h"

//************************
// �o�b�e���[�ቺUI�N���X
//************************
class CBatteryDown :public CObject2D
{
public:
	CBatteryDown(int nPriority = 5);	// �R���X�g���N�^
	~CBatteryDown();					// �f�X�g���N�^
	static CBatteryDown* Create(D3DXVECTOR3 pos);// �C���X�^���X����
	HRESULT Init(D3DXVECTOR3 pos);	// ������
	void Uninit(void);				// �I��
	void Update(void);				// �X�V
	void Draw(void);				// �`��
	void SetPos(D3DXVECTOR3 pos);	// �ʒu�ݒ�
	void SetRot(D3DXVECTOR3 rot);	// �����ݒ�
	D3DXVECTOR3 GetPos(void);		// �ʒu���擾
private:
	int  m_nIdxTexture;		// �e�N�X�`���̃C���f�b�N�X
	static constexpr float line = 20.0f;// �\������̗͂̃��C��
	static const D3DXVECTOR2 SIZE;		// �傫��
};
#endif