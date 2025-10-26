//**************************************
//
// �V�[������ [scene.h]
// Author:Sasaki Soichiro
//
//**************************************
#ifndef _SCENE_H_ // ���̃}�N����`������Ă��Ȃ�������
#define _SCENE_H_ // ��d�C���N���[�h�h�~�̃}�N����`

//******************
// �C���N���[�h
//******************
#include "main.h"
#include "object.h"

//****************
// �}�N����`
//****************
#define NONE (D3DXVECTOR3(0.0f,0.0f,0.0f))


//********************
// �V�[���N���X
//********************
class CScene:public CObject
{
public:
	typedef enum
	{
		MODE_TITLE=0,	// �^�C�g��
		MODE_GAME,		// �Q�[��
		MODE_MAX
	}MODE;
	CScene(MODE mode);	// �R���X�g���N�^
	~CScene();			// �f�X�g���N�^
	static CScene* Create(MODE mode);			// �C���X�^���X����
	virtual HRESULT Init(D3DXVECTOR3 pos)=0;	// ������
	virtual void Uninit(void)=0;				// �I��
	virtual void Update(void)=0;				// �X�V
	virtual void Draw(void)=0;					// �`��
	void SetPos(D3DXVECTOR3 pos) {};			// �ʒu�̐ݒ�
	void SetRot(D3DXVECTOR3 rot) {};			// �����̐ݒ�
	D3DXVECTOR3 GetPos(void) { return NONE; }	// �ʒu���擾
	MODE GetMode(void) { return m_mode; }		// ���[�h���擾
private:
	MODE m_mode;	// ���[�h
};
#endif