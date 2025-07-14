//**********************************
//
// �̗�UI���� [lifeUI.cpp]
// Author:Sasaki Soichiro
//
//**********************************

//*******************
// �C���N���[�h
//*******************
#include "lifeUI.h"
#include "manager.h"

//*****************
// �ÓI�����o�ϐ�
//*****************
CNumber* CLifeUI::m_apNumber[3] = {};	// �i���o�[�ւ̃|�C���^
CSymbol* CLifeUI::m_pSymbol = NULL;		// �R�����ւ̃|�C���^

//*****************
// �R���X�g���N�^
//*****************
CLifeUI::CLifeUI(int nPriority) :CObject2DMulti(nPriority)
{
	// �e�N�X�`��������
	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		m_nIdxTexture[nCnt] = 0;	// �C���f�b�N�X
	}

	m_size = D3DXVECTOR2(0.0f, 0.0f);	// �傫��
	m_fLife = 100.0f;					// �̗�
	m_nDigit = 0;						// ����
}

//*****************
// �f�X�g���N�^
//*****************
CLifeUI::~CLifeUI()
{
}

//*****************
// ����������
//*****************
HRESULT CLifeUI::Init(D3DXVECTOR3 pos)
{
	CTexture* pTexture = CManager::GetCTexture();	// �e�N�X�`���̃|�C���^�擾
	CObject2DMulti::Init(pos);						// 2D�̏�����
	// �e�N�X�`�������蓖�Ă�
	CObject2DMulti::BindTexture(pTexture->GetAddres(m_nIdxTexture[0]), pTexture->GetAddres(m_nIdxTexture[1]));

	// UV�̐ݒ�
	CObject2DMulti::SetTex(D3DXVECTOR2(0.0f, 0.0f),
		D3DXVECTOR2(1.0f, 0.0f),
		D3DXVECTOR2(0.0f, 1.0f),
		D3DXVECTOR2(1.0f, 1.0f));
	// �e�N�X�`���̗Ε������ڂ�悤�ɐݒ�
	CObject2DMulti::SetTex2(D3DXVECTOR2(0.0f, 0.0f),
		D3DXVECTOR2(0.5f, 0.0f),
		D3DXVECTOR2(0.0f, 1.0f),
		D3DXVECTOR2(0.5f, 1.0f));

	// �傫���̐ݒ�
	CObject2DMulti::SetSize(D3DXVECTOR2(170.0f, 100.0f));

	// �i���o�[�̃|�C���^������
	for (int nCntD = 0; nCntD < 3; nCntD++)
	{
		// ������
		m_apNumber[nCntD]->Init();
		// �i���o�[�ݒ�
		m_apNumber[nCntD]->SetNumber(0);											
		// �傫���ݒ�
		m_apNumber[nCntD]->SetSize(D3DXVECTOR2(20.0f, 30.0f));
		// �ʒu�ݒ�(�X�N���[���E��)
		m_apNumber[nCntD]->SetPos(D3DXVECTOR3((pos.x-115.0f) - 20.0f * nCntD, pos.y, 0.0f));	
	}

	// �L���̃|�C���^������
	// ������
	m_pSymbol->Init();
	// �傫��
	m_pSymbol->SetSize(D3DXVECTOR2(20.0f, 30.0f));		
	// �ʒu�ݒ�
	m_pSymbol->SetPos(D3DXVECTOR3((pos.x - 95.0f), pos.y, 0.0f));	
	return S_OK;
}

//*****************
// �I������
//*****************
void CLifeUI::Uninit(void)
{
	// �i���o�[�̃|�C���^�I������
	for (int nCnt = 0; nCnt < 3; nCnt++)
	{
		if (m_apNumber[nCnt] != NULL)
		{// NULL����Ȃ�������

			// �I������
			m_apNumber[nCnt]->Uninit();
			// ���
			delete m_apNumber[nCnt];
			// NULL����
			m_apNumber[nCnt] = NULL;
		}
	}

	// �L���̃|�C���^�I������
	if (m_pSymbol != NULL)
	{// NULL����Ȃ�������

		// �I������
		m_pSymbol->Uninit();
		// ���
		delete m_pSymbol;
		// NULL����
		m_pSymbol = NULL;	
	}

	// �I������
	CObject2DMulti::Uninit();
}

//*****************
// �X�V����
//*****************
void CLifeUI::Update(void)
{
	m_fLife -= 0.01f;				// ���C�t�����炷
	float fLife = 100.0f - m_fLife;	// �v�Z�p
	float p = fLife / 100.0f;		// 1����100�̒l�ɒ���

	// UV���W(�����ɉ����ĐF���ς��悤�Ɍv�Z)
	CObject2DMulti::SetTex2(D3DXVECTOR2(p * 0.5f, 0.0f),
		D3DXVECTOR2(0.5f + p * 0.5f, 0.0f),
		D3DXVECTOR2(p * 0.5f, 1.0f),
		D3DXVECTOR2(0.5f + p * 0.5f, 1.0f));

	int nData[2];	// �v�Z�p

	// �v�Z�p�̒l����
	nData[0] = 10; 
	nData[1] = 1;

	// �i���o�[�ɒl��ݒ�
	for (int nCntD = 0; nCntD < 3; nCntD++)
	{
		// �v�Z���Ēl��1�����ݒ�
		m_apNumber[nCntD]->SetNumber(((int)m_fLife % nData[0]) / nData[1]);
		nData[0] *= 10;
		nData[1] *= 10;
	}
}

//*****************
// �`�揈��
//*****************
void CLifeUI::Draw(void)
{
	// �`�揈��
	CObject2DMulti::Draw();

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;						// �f�o�C�X
	CTexture* pTexture = CManager::GetCTexture();	// �e�N�X�`���̃|�C���^�擾
	CRenderer* renderer = CManager::GetCRenderer();	// �����_���[�̃|�C���^�擾
	pDevice = renderer->GetDevice();				// �f�o�C�X�擾

	// �i���o�[�������`��
	for (int nCntD = 0; nCntD < Digit((int)m_fLife); nCntD++)
	{
		// �e�N�X�`���ݒ�
		pDevice->SetTexture(0, pTexture->GetAddres(m_nIdxTexture[2]));
		// �`��
		m_apNumber[nCntD]->Draw();
	}
	// �L���`��
	// �e�N�X�`���ݒ�
	pDevice->SetTexture(0, pTexture->GetAddres(m_nIdxTexture[3]));
	// �`��
	m_pSymbol->Draw();
}

//******************
// �C���X�^���X����
//******************
CLifeUI* CLifeUI::Create(D3DXVECTOR3 pos)
{
	CLifeUI* pLifeUI;								// ���C�t�̃|�C���^
	CTexture* pTexture = CManager::GetCTexture();	// �e�N�X�`���̃|�C���^

	int nNum = CObject::GetNumAll();// ���݂̃I�u�W�F�N�g�����擾
	if (nNum < MAX_OBJ - 1)
	{// �ő�I�u�W�F�N�g���𒴂��Ă��Ȃ�������

		pLifeUI = new CLifeUI;// �C���X�^���X����
		// �}���`�e�N�X�`��1����(�d�r�̉摜)
		pLifeUI->m_nIdxTexture[0] = pTexture->Register("data\\TEXTURE\\enegy.png");
		// �}���`�e�N�X�`��2����(�΁E���̓�F�̉摜)
		pLifeUI->m_nIdxTexture[1] = pTexture->Register("data\\TEXTURE\\green001.jpg");
		// �����e�N�X�`��
		pLifeUI->m_nIdxTexture[2] = pTexture->Register("data\\TEXTURE\\number000.png");
		// �L���e�N�X�`��(%�̉摜)
		pLifeUI->m_nIdxTexture[3] = pTexture->Register("data\\TEXTURE\\percent000.png");

		// �i���o�[�̃C���X�^���X����
		for (int nCntD = 0; nCntD < 3; nCntD++)
		{
			if (m_apNumber[nCntD] == NULL)
			{// NULL��������
				m_apNumber[nCntD] = new CNumber;	// �C���X�^���X����
			}
		}
		// �L���̃C���X�^���X����
		if (m_pSymbol == NULL)
		{// NULL��������
			m_pSymbol = new CSymbol;	// �C���X�^���X����
		}

		// ������
		pLifeUI->Init(pos);

		// ����n��
		return pLifeUI;
	}

	// (���s������)NULL��Ԃ�
	return NULL;
}

//*****************
// �ʒu�ݒ�
//*****************
void CLifeUI::SetPos(D3DXVECTOR3 pos)
{
	// �ʒu�ݒ�
	CObject2DMulti::SetPos(pos);
}

//*****************
// �����ݒ�
//*****************
void CLifeUI::SetRot(D3DXVECTOR3 rot)
{
	// �ʒu�ݒ�
	CObject2DMulti::SetRot(rot);
}

//*****************
// �ʒu���擾
//*****************
D3DXVECTOR3 CLifeUI::GetPos(void)
{
	// �ʒu���擾
	return CObject2DMulti::GetPos();
}

//*****************
// ������Ԃ�
//*****************
int CLifeUI::Digit(int nScore)
{
	int nNum = nScore;	// �X�R�A��0�̕������J�E���g
	int nKeepNum = 0;	// �X�R�A�̌���

	// ����؂�Ȃ��Ȃ�܂ŌJ��Ԃ�
	while (nNum != 0)	
	{
		nNum /= 10;// 10�Ŋ���
		nKeepNum++;// ���������Z
	}
	if (nScore == 0)
	{
		nKeepNum = 1;// 1���ڂ��O�̎�
	}

	// ���݂̌���Ԃ�
	return nKeepNum;
}