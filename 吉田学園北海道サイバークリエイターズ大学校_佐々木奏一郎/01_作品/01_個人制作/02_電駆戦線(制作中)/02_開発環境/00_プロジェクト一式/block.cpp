//*****************************************
//
// �u���b�N���� [block.cpp]
// Author:Sasaki Soichiro
//
//*****************************************

//*******************
// �C���N���[�h
//*******************
#include "block.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "texture.h"
#include "camera.h"
#include "object3D.h"

//**********************
// �ÓI�����o�ϐ�������
//**********************
int CBlock::m_nNumAll = 0;

//*****************
// �R���X�g���N�^
//*****************
CBlock::CBlock(int nPriority) :CObjectX(nPriority)
{
	m_nIdxXFile = -1;
	m_nIdx = m_nNumAll; 
	m_State=STATE_NONE;
}

//*****************
// �f�X�g���N�^
//*****************
CBlock::~CBlock()
{
}

//******************
// �C���X�^���X����
//*******************
CBlock* CBlock::Create(D3DXVECTOR3 pos)
{
	CBlock* pBlock;
	CTexture* pTexture = CManager::GetCTexture();
	int nNum = CObject::GetNumAll();
	if (nNum < MAX_OBJ - 1)
	{// �I�u�W�F�N�g���ő吔�ɒB���Ă��Ȃ��ꍇ

		pBlock = new CBlock;	// �C���X�^���X����
		pBlock->Init(pos);		// ������
		return pBlock;			// ����n��
	}

	// �I�u�W�F�N�g���ő吔�ɒB���Ă����ꍇ
	return NULL;	// NULL��Ԃ�
}

//*****************
// ����������
//*****************
HRESULT CBlock::Init(D3DXVECTOR3 pos)
{
	// CXModel�̃|�C���^�ɏ�������
	CXModel* pXModel = CManager::GetCXModel();
	// �g�����f���̃C���f�b�N�X������
	m_nIdxXFile = pXModel->Register("data\\MODEL\\box002.x");
	// X�t�@�C�������蓖�Ă�
	BindXFile(pXModel->GetAddres(m_nIdxXFile));	
	// ������
	CObjectX::Init(pos);

	// ����������
	return S_OK;		
}

//*****************
// �I������
//*****************
void CBlock::Uninit(void)
{
	// �I������
	CObjectX::Uninit();
}

//*****************
// �X�V����
//*****************
void CBlock::Update(void)
{
	// CInputMouse�̃|�C���^�ɏ�������
	CInputMouse* pInputMouse = CManager::GetCInputMouse();
	// CInputKeyboard�̃|�C���^�ɏ�������
	CInputKeyboard* pInputKeyboard = CManager::GetCInputKeyboard();
	
	bool bCursor = CollisionCursor();// �J�[�\�����������Ă��邩
	switch (m_State)
	{
	case STATE_NONE:
		// �����Ȃ����
		if (bCursor==true&&pInputMouse->GetDown(CInputMouse::MOUSE_L)==true)
		{// �������Ă邩�}�E�X�������ꂽ�Ƃ�
			CDebugProc::Print("\n�J�[�\���������Ă�%d", m_nIdx);

			m_State = STATE_DRAG;// ����ł��Ԃɂ���
		}
		break;
	case STATE_DRAG:
		// ����ł���

		// �u���b�N�𓮂���
		Drag();
		// ���݂̈ʒu�擾
		D3DXVECTOR3 pos = GetPos();
		if (pInputKeyboard->GetPress(DIK_UP) == true)
		{// ������������
			pos.y += 0.5f;
		}
		else if (pInputKeyboard->GetPress(DIK_DOWN) == true)
		{// ������������
			pos.y -= 0.5f;
		}

		// �ʒu��ݒ�
		SetPos(pos);
		if (pInputMouse->GetUp(CInputMouse::MOUSE_L) == true)
		{// �}�E�X�𗣂�����
			m_State = STATE_NONE;// �����Ȃ���Ԃɂ���
		}
		break;
	}
}

//*****************
// �`�揈��
//*****************
void CBlock::Draw(void)
{
	CObjectX::Draw();// �`��
}

//******************
// �ʒu�̐ݒ�
//******************
void CBlock::SetPos(D3DXVECTOR3 pos)
{
	CObjectX::SetPos(pos);// �ʒu�ݒ�
}

//******************
// �����̐ݒ�
//******************
void CBlock::SetRot(D3DXVECTOR3 rot)
{
	CObjectX::SetRot(rot);// �����ݒ�
}

//******************
// �ʒu���̎擾
//******************
D3DXVECTOR3 CBlock::GetPos(void)
{
	return CObjectX::GetPos();// �ʒu���擾
}
D3DXVECTOR3 CBlock::GetRot(void)
{
	return CObjectX::GetRot();// �ʒu���擾
}

bool CBlock::CollisionCursor(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	CRenderer* renderer = CManager::GetCRenderer();
	pDevice = renderer->GetDevice();
	CInputMouse* pInputMouse = CManager::GetCInputMouse();

	D3DXMATRIX matProj, matView,matWorld;
	D3DVIEWPORT9 viewport;
	D3DXVECTOR3 blockPos;
	D3DXVECTOR2 blockPos2D;
	D3DXVECTOR2 CursorPos = pInputMouse->GetVelocity();
	pDevice->GetViewport(&viewport);
	pDevice->GetTransform(D3DTS_PROJECTION, &matProj);
	pDevice->GetTransform(D3DTS_VIEW, &matView);
	D3DXMatrixIdentity(&matWorld);
	D3DXVECTOR3 pos = GetPos();
	D3DXVec3Project(&blockPos, &pos, &viewport, &matProj, &matView, &matWorld);
	float VecX, VecY;
	VecX = blockPos.x - CursorPos.x;
	VecY = blockPos.y - CursorPos.y;
	float fDistance = sqrtf((VecX*VecX) + (VecY - VecY));

	float fRad = 20.0f;

	if (fRad > fDistance)
	{
		return true;
	}

	return false;

}

void CBlock::Drag(void)
{
	CInputMouse* pInputMouse = CManager::GetCInputMouse();
	D3DXVECTOR2 CursorPos = pInputMouse->GetVelocity();
	D3DXVECTOR2 CursorPosOld = pInputMouse->GetVelocityOld();
	CPlayer* pPlayer = CManager::GetCPlayer();

	D3DXVECTOR3 rot = pPlayer->GetRot();
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR2 Vec = CursorPos - CursorPosOld;
	Vec *= 0.3f;
	D3DXVECTOR3 move=D3DXVECTOR3(0.0f,0.0f,0.0f);
	move.x = cosf(rot.y) * Vec.x + sinf(rot.y) * Vec.y;
	move.z = -sinf(rot.y) * Vec.x - cosf(rot.y) * Vec.y;
	pos += move;

	SetPos(pos);
}