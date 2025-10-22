//***************************************
// 
// �R���{���� [combo.h]
// Author:Sasaki Soichiro
//
//***************************************
#ifndef _COMBO_H_ // ���̃}�N����`������Ă��Ȃ�������
#define _COMBO_H_ // ��d�C���N���[�h�h�~�̃}�N����`

//******************
// �C���N���[�h
//******************
#include "main.h"
#include "object.h"
#include "object2D.h"

class CNumberMulti;

//************************
// �R���{�N���X
//************************
class CCombo :public CObject
{
public:
	CCombo(int nPriority = 5);	// �R���X�g���N�^
	~CCombo();					// �f�X�g���N�^
	static CCombo* Create(D3DXVECTOR3 pos);
	HRESULT Init(D3DXVECTOR3 pos);	// ������
	void Uninit(void);				// �I��
	void Update(void);				// �X�V
	void Draw(void);				// �`��
	void SetPos(D3DXVECTOR3 pos);	// �ʒu�ݒ�
	void SetRot(D3DXVECTOR3 rot);	// �����ݒ�
	D3DXVECTOR3 GetPos(void);		// �ʒu���擾
	int Digit(int nScore);			// ����Ԃ�
	static void Add(int nScore);	// �R���{���Z
	static int GetCombo(void) { return m_nCurrent; }// ���݂̃R���{�����擾
private:
	void Set(void);					// �}���`�e�N�X�`���̐ݒ�
	void Reset(void);				// �R���{���r�؂ꂽ���̐ݒ�
	static CNumberMulti* m_pNumberMulti[2];	// �i���o�[�ւ̃|�C���^
	static int m_nCurrent;					// ���݂̃R���{��
	static int m_nTime;						// �p������
	static int m_nScore;					// ���݂̃X�R�A
	static constexpr int maxTime = 1400;	// �ő厞��
	static constexpr float offsetX = 35.0f;	// �I�t�Z�b�g
	static const D3DXCOLOR COMBO_ON;		// �R���{���̐F
	static const D3DXCOLOR COMBO_OFF;		// �R���{���ĂȂ��Ƃ��̐F
};
#endif