//*****************************************
//
// �u���b�N���� [block.cpp]
// Author:Sasaki Soichiro
//
//*****************************************

//*******************
// �C���N���[�h
//*******************
#include "jempiece.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "texture.h"
#include "camera.h"
#include "object3D.h"
#include "game.h"

//*****************
// �}�N����`
//*****************
#define HORIZON (0.08f)

//*****************
// �R���X�g���N�^
//*****************
CJemPiece::CJemPiece(int nPriority) :CObjectX(nPriority)
{
	m_nIdxXFile = -1;
	m_move = NONE;
	m_nLife = 0;
	m_nType = 0;
	m_fAngle = 0.0f;
}

//*****************
// �f�X�g���N�^
//*****************
CJemPiece::~CJemPiece()
{
}

//******************
// �C���X�^���X����
//*******************
CJemPiece* CJemPiece::Create(D3DXVECTOR3 pos, float fAngle,int nType)
{
	CJemPiece* pAttackBolt;
	CTexture* pTexture = CManager::GetCTexture();
	int nNum = CObject::GetNumAll();
	if (nNum < MAX_OBJ - 1)
	{// �I�u�W�F�N�g���ő吔�ɒB���Ă��Ȃ��ꍇ

		pAttackBolt = new CJemPiece;	// �C���X�^���X����
		pAttackBolt->m_nType = nType;	// ���
		pAttackBolt->m_fAngle = fAngle;	// ����
		pAttackBolt->Init(pos);			// ������
		return pAttackBolt;				// ����n��
	}

	// �I�u�W�F�N�g���ő吔�ɒB���Ă����ꍇ
	return NULL;	// NULL��Ԃ�
}

//*****************
// ����������
//*****************
HRESULT CJemPiece::Init(D3DXVECTOR3 pos)
{
	// CXModel�̃|�C���^�ɏ�������
	CXModel* pXModel = CManager::GetCXModel();
	switch (m_nType)
	{
	case 0:
		// �g�����f���̃C���f�b�N�X������
		m_nIdxXFile = pXModel->Register("data\\MODEL\\piece00.x");
		break;
	case 1:
		// �g�����f���̃C���f�b�N�X������
		m_nIdxXFile = pXModel->Register("data\\MODEL\\piece01.x");
		break;
	case 2:
		// �g�����f���̃C���f�b�N�X������
		m_nIdxXFile = pXModel->Register("data\\MODEL\\piece02.x");
		break;
	}
	// X�t�@�C�������蓖�Ă�
	BindXFile(pXModel->GetAddres(m_nIdxXFile));

	// ������
	CObjectX::Init(pos);
	m_move.y = rand()%50*0.1f;
	m_nLife = 80;

	// ����������
	return S_OK;
}

//*****************
// �I������
//*****************
void CJemPiece::Uninit(void)
{
	// �I������
	CObjectX::Uninit();
}

//*****************
// �X�V����
//*****************
void CJemPiece::Update(void)
{
	// �ʒu�Ƒ傫���擾
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 size = GetSize();

	// �����l�̐ݒ�
	m_move.x = sinf(m_fAngle) * 1.5f;
	m_move.y -= HORIZON;
	m_move.z = cosf(m_fAngle) * 1.5f;

	// �傫��������������
	size *= 0.98f;

	pos += m_move;

	// �ʒu�Ƒ傫���ݒ�
	SetPos(pos);
	SetSize(size);

	// ���������炷
	m_nLife--;
	if (m_nLife < 0)
	{
		Uninit();
	}
}

//*****************
// �`�揈��
//*****************
void CJemPiece::Draw(void)
{
	CObjectX::Draw();// �`��
}

//******************
// �ʒu�̐ݒ�
//******************
void CJemPiece::SetPos(D3DXVECTOR3 pos)
{
	CObjectX::SetPos(pos);// �ʒu�ݒ�
}

//******************
// �����̐ݒ�
//******************
void CJemPiece::SetRot(D3DXVECTOR3 rot)
{
	CObjectX::SetRot(rot);// �����ݒ�
}

//******************
// �ʒu���̎擾
//******************
D3DXVECTOR3 CJemPiece::GetPos(void)
{
	return CObjectX::GetPos();// �ʒu���擾
}
D3DXVECTOR3 CJemPiece::GetRot(void)
{
	return CObjectX::GetRot();// �ʒu���擾
}