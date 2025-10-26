//**************************************
//
// �z�C�[������ [wheel.h]
// Author:Sasaki Soichiro
//
//**************************************
#ifndef _WHEEL_H_ // ���̃}�N����`������Ă��Ȃ�������
#define _WHEEL_H_ // ��d�C���N���[�h�h�~�̃}�N����`

//******************
// �C���N���[�h
//******************
#include "main.h"
#include "model.h"

//***************
// �O���錾
//***************
class CCarBody;

//************************
// �z�C�[���̃N���X
//************************
class CWheel :public CModel
{
public:
	CWheel(int nPriority = 4);	// �R���X�g���N�^
	~CWheel();					// �f�X�g���N�^
	static CWheel* Create(D3DXVECTOR3 pos, const char* pFileName);// �C���X�^���X����
	HRESULT Init(D3DXVECTOR3 pos);	// ������
	void Uninit(void);				// �I��
	void Update(void);				// �X�V
	void Draw(void);				// �`��
	void SetPos(D3DXVECTOR3 pos);	// �ʒu
	void SetRot(D3DXVECTOR3 rot);	// ����
	void SetPosion(D3DXVECTOR3 pos);
	void SetOffsetY(float fOffsetY) { m_fOffset = fOffsetY; }// �����̃I�t�Z�b�g
	void SetCarBody(CCarBody* pCarBody) { m_pCarBody = pCarBody; }
	void SetAttachY(float fAttachY) { m_fAttachY = fAttachY; }
	D3DXVECTOR3 GetPos(void);		// �ʒu���̎擾
	D3DXVECTOR3 GetRot(void);		// �������̎擾
	void CollisionMesh(void);		// �n�ʂƂ̓����蔻��
	float GetDeltaHeight(void) { return m_fDeltaHeight; }
private:
	float m_fOffset;
	float m_fSuspension;					// ���݂̃T�X�y���V�����̒���
	float m_fSuspensionOld;					// �O�t���[���̃T�X�y���V�����̒���
	float m_fDeltaHeight;					// �ԑ̂ɓ`��鍂���̕ω���
	float m_fAttachY;						// �ڑ������̍���
	CCarBody* m_pCarBody;
	static constexpr float fSusMin = -20.0f;// �T�X�y���V�����̍ŏ��̒���
	static constexpr float fSusMax = 20.0f;	// �T�X�y���V�����̍ő�̒��� 
	static constexpr float fSusRest = -10.0f;
	static constexpr float fRadius = 25.0f;	// �^�C���̔��a
	static constexpr float fSpringK = 12.0f;
	static constexpr float fDanperC = 1.0f;
};

#endif