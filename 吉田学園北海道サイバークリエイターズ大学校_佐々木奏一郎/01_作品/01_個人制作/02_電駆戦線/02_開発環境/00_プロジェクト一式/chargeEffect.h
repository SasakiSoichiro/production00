//=============================================================================
//
// �[�d�G�t�F�N�g���� [chargeEffect.h]
// Author Sasaki Soichiro
//
//=============================================================================
#ifndef _CHARGEEFFECT_H_// ���̃}�N����`������Ă��Ȃ�������
#define _CHARGEEFFECT_H_// 2�d�C���N���[�h�h�~�̃}�N����`
//*******************
// �C���N���[�h
//*******************
#include "main.h"
#include "effect.h"

//**********************
// �[�d�G�t�F�N�g�N���X
//**********************
class CChargeEffect :public CEffect
{
public:
	CChargeEffect(int nPriority = 4);	// �R���X�g���N�^
	~CChargeEffect();					// �f�X�g���N�^
	static CChargeEffect* Create(D3DXVECTOR3 pos, float fAngle, D3DXVECTOR2 size, int nLife, D3DXCOLOR col);// �C���X�^���X����
	HRESULT Init(D3DXVECTOR3 pos);	// ������
	void Uninit(void);				// �I��
	void Update(void);				// �X�V
	void Draw(void);				// �`��
private:
	static constexpr float dest = 0.01f;	// �x��
	static constexpr float offsetY = 20.0f;	// �I�t�Z�b�g
	static constexpr float speed = 4.0f;	// �X�s�[�h
};
#endif