//**************************************
//
// �l�H�q���̏��� [skydoom.h]
// Author:Sasaki Soichiro
//
//**************************************
#ifndef _HUMANSATELLITE_H_ // ���̃}�N����`������Ă��Ȃ�������
#define _HUMANSATELLITE_H_ // ��d�C���N���[�h�h�~�̃}�N����`

//******************
// �C���N���[�h
//******************
#include "main.h"
#include "objectX.h"

//********************
// �l�H�q���N���X
//********************
class CHumanSatellite :public CObjectX
{
public:
	CHumanSatellite(int nPriority = 4);	// �R���X�g���N�^
	~CHumanSatellite();					// �f�X�g���N�^
	static CHumanSatellite* Create(D3DXVECTOR3 pos);// �C���X�^���X����
	HRESULT Init(D3DXVECTOR3 pos);	// ������
	void Uninit(void);				// �I��
	void Update(void);				// �X�V
	void Draw(void);				// �`��
	void SetPos(D3DXVECTOR3 pos);	// �ʒu
	void SetRot(D3DXVECTOR3 rot);	// ����
	D3DXVECTOR3 GetPos(void);		// �ʒu���擾
	D3DXVECTOR3 GetRot(void);		// �������擾
private:
	int m_nIdxXFile;	// �g���Ă���X�t�@�C���̔ԍ�
	float m_fAngle;		// �p�x
};
#endif