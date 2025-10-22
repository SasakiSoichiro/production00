//**************************************
//
// �E�F�[�u���� [wave.h]
// Author:Sasaki Soichiro
//
//**************************************
#ifndef _WAVE_H_ // ���̃}�N����`������Ă��Ȃ�������
#define _WAVE_H_ // ��d�C���N���[�h�h�~�̃}�N����`

//******************
// �C���N���[�h
//******************
#include "main.h"
#include <string>
#include "object2D.h"

class CNumber;

//********************
// �E�F�[�u�N���X
//********************
class CWave:public CObject2D
{
public:
	CWave(int nPriority = 6);	// �R���X�g���N�^
	~CWave();					// �f�X�g���N�^
	static CWave* Create(D3DXVECTOR3 pos);// �C���X�^���X����
	HRESULT Init(D3DXVECTOR3 pos);	// ������
	void Uninit(void);				// �I��
	void Update(void);				// �X�V
	void Draw(void);				// �`��
	void SetPos(D3DXVECTOR3 pos);	// �ʒu�ݒ�
	void SetRot(D3DXVECTOR3 rot);	// �����ݒ�
	D3DXVECTOR3 GetPos(void);		// �ʒu���擾
	void Load(int nWave);			// �ǂݍ���
	void Move(void);				// ������
private:
	static int m_nCurrent;	// ���݂̃E�F�[�u
	static int m_nAll;		// �E�F�[�u�̍ő�
	// �E�F�[�u�̃t�@�C����
	std::string WAVE[3] =
	{
		"data\\WAVE\\wave00.txt",
		"data\\WAVE\\wave01.txt",
		"data\\WAVE\\wave02.txt",
	};
	int  m_nIdxTexture[2];		// �g���Ă���e�N�X�`���̔ԍ�
	static CNumber* m_pNumber;	// �i���o�[�ւ̃|�C���^
	int m_nScreenTime;			// �E�F�[�u���̕\������
	bool m_bScreen;				// �\�����Ă��邩
	bool m_bGo;					// �n�܂�
	bool m_bStop;				// �~�߂Ă���Ƃ�
	bool m_bEnd;				// �I���
	float m_fCnt;				// �J�E���g
};
#endif