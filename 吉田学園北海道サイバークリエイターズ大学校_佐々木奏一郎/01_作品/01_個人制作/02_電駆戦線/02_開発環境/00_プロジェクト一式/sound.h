//***************************************
//
// �T�E���h���� [sound.h]
// Author:Sasaki Soichiro
//
//***************************************
#ifndef _SOUND_H_// ���̃}�N����`������Ă��Ȃ�������
#define _SOUND_H_// ��d�C���N���[�h�h�~�̃}�N����`

//*********************
// �C���N���[�h
//*********************
#include "main.h"

//******************
// �T�E���h�N���X
//******************
class CSound
{
public:
	// ���x��
	typedef enum
	{
		LABEL_BGM00 = 0,
		LABEL_BGM01,
		LABEL_SE00,
		LABEL_SE01,
		LABEL_SE02,
		LABEL_SE03,
		LABEL_SE04,
		LABEL_SE05,
		LABEL_SE06,
		LABEL_SE07,
		LABEL_SE08,
		LABEL_SE09,
		LABEL_SE10,
		LABEL_SE11,
		LABEL_MAX,
	} LABEL;
	typedef struct
	{
		const char* pFilename;	// �t�@�C����
		int nCntLoop;			// ���[�v�J�E���g
	} SOUNDINFO;

	CSound();	// �R���X�g���N�^
	~CSound();	// �f�X�g���N�^
	HRESULT Init(HWND hWnd);	// ������
	void Uninit(void);			// �I��
	HRESULT Play(LABEL label);	// �Đ�
	void Stop(LABEL label);		// ��~
	void Stop(void);			// ���ׂĒ�~
private:
	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD* pChunkSize, DWORD* pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void* pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);
	IXAudio2* m_pXAudio2;								// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
	IXAudio2MasteringVoice* m_pMasteringVoice;			// �}�X�^�[�{�C�X
	IXAudio2SourceVoice* m_apSourceVoice[LABEL_MAX];	// �\�[�X�{�C�X
	BYTE* m_apDataAudio[LABEL_MAX];						// �I�[�f�B�I�f�[�^
	DWORD m_aSizeAudio[LABEL_MAX];						// �I�[�f�B�I�f�[�^�T�C�Y
	static SOUNDINFO m_aSoundInfo[LABEL_MAX];			// �T�E���h�̏��
};

#endif
