//**********************************
//
// �̗�UI���� [lifeUI.cpp]
// Author:Sasaki Soichiro
//
//**********************************

//*******************
// �C���N���[�h
//*******************
#include "adjustUI.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"

//*****************
// �R���X�g���N�^
//*****************
CAdjustUI::CAdjustUI(int nPriority) :CObject2DMulti(nPriority)
{
	// �e�N�X�`��������
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		m_nIdxTexture[nCnt] = 0;	
	}
	m_size = D3DXVECTOR2(0.0f, 0.0f);	
	m_fLife = 0.0f;					
}

//*****************
// �f�X�g���N�^
//*****************
CAdjustUI::~CAdjustUI()
{
}

//*****************
// ����������
//*****************
HRESULT CAdjustUI::Init(D3DXVECTOR3 pos)
{
	// �e�N�X�`�����擾
	CTexture* pTexture = CManager::GetCTexture();	

	// 2D�̏�����
	CObject2DMulti::Init(pos);						

	// �e�N�X�`�������蓖�Ă�
	CObject2DMulti::BindTexture(pTexture->GetAddres(m_nIdxTexture[TYPE_SHAPE]),
								pTexture->GetAddres(m_nIdxTexture[TYPE_COLOR]));

	// UV�̐ݒ�
	CObject2DMulti::SetTex(D3DXVECTOR2(0.0f, 0.0f),
		D3DXVECTOR2(1.0f, 0.0f),
		D3DXVECTOR2(0.0f, 1.0f),
		D3DXVECTOR2(1.0f, 1.0f));

	// �e�N�X�`���̗Ε������ڂ�悤�ɐݒ�
	CObject2DMulti::SetTex2(D3DXVECTOR2(0.0f, 0.0f),
		D3DXVECTOR2(texOffset, 0.0f),
		D3DXVECTOR2(0.0f, 1.0f),
		D3DXVECTOR2(texOffset, 1.0f));

	// �傫���̐ݒ�
	CObject2DMulti::SetSize(D3DXVECTOR2(150.0f, 500.0f));

	return S_OK;
}

//*****************
// �I������
//*****************
void CAdjustUI::Uninit(void)
{
	CObject2DMulti::Uninit();
}

//*****************
// �X�V����
//*****************
void CAdjustUI::Update(void)
{
	// �������v�Z
	float fLife = maxLife - m_fLife;
	float p = fLife / maxLife;

	// �e�N�X�`�����W�𔽉f
	if (m_fLife >= 0.0f && m_fLife <= maxLife)
	{
		// UV���W(�����ɉ����ĐF���ς��悤�Ɍv�Z)
		CObject2DMulti::SetTex2(D3DXVECTOR2(0.0f,p * texOffset),
								D3DXVECTOR2(1.0f, p * texOffset),
								D3DXVECTOR2(0.0f, texOffset + p * texOffset),
								D3DXVECTOR2(1.0f, texOffset + p * texOffset));
	}

	// �����ŏI��
	if (m_fLife <= 0.0f)
	{
		Uninit();
	}
}

//*****************
// �`�揈��
//*****************
void CAdjustUI::Draw(void)
{
	CObject2DMulti::Draw();
}

//******************
// �C���X�^���X����
//******************
CAdjustUI* CAdjustUI::Create(D3DXVECTOR3 pos)
{
	CAdjustUI* pAdjustUI;							// �̃|�C���^
	CTexture* pTexture = CManager::GetCTexture();	// �e�N�X�`���̃|�C���^

	int nNum = CObject::GetNumAll();// ���݂̃I�u�W�F�N�g�����擾
	if (nNum < MAX_OBJ - 1)
	{// �ő�I�u�W�F�N�g���𒴂��Ă��Ȃ�������

		pAdjustUI = new CAdjustUI;// �C���X�^���X����
		// �}���`�e�N�X�`��1����(�d�r�̉摜)
		pAdjustUI->m_nIdxTexture[TYPE_SHAPE] = pTexture->Register("data\\TEXTURE\\adjust.png");
		// �}���`�e�N�X�`��2����(�΁E���̓�F�̉摜)
		pAdjustUI->m_nIdxTexture[TYPE_COLOR] = pTexture->Register("data\\TEXTURE\\purple.png");

		// ������
		pAdjustUI->Init(pos);

		return pAdjustUI;
	}

	return NULL;
}

//*****************
// �ʒu�ݒ�
//*****************
void CAdjustUI::SetPos(D3DXVECTOR3 pos)
{
	CObject2DMulti::SetPos(pos);
}

//*****************
// �����ݒ�
//*****************
void CAdjustUI::SetRot(D3DXVECTOR3 rot)
{
	CObject2DMulti::SetRot(rot);
}

//*****************
// �ʒu���擾
//*****************
D3DXVECTOR3 CAdjustUI::GetPos(void)
{
	return CObject2DMulti::GetPos();
}