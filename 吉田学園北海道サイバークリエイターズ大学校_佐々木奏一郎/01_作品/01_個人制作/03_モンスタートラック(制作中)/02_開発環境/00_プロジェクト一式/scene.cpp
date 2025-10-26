//**************************************
//
// �V�[������ [scene.cpp]
// Author:Sasaki Soichiro
//
//**************************************
//******************
// �C���N���[�h
//******************
#include "scene.h"
#include "game.h"
#include "title.h"

//****************
// �R���X�g���N�^
//****************
CScene::CScene(MODE mode) : CObject(0)
{
	m_mode = mode;
	CObject::SetType(CObject::TYPE_SCENE);
}

//****************
// �f�X�g���N�^
//****************
CScene::~CScene()
{
}

//********************
// �C���X�^���X����
//********************
CScene*CScene::Create(MODE mode)
{
	CScene* pScene = NULL;
	switch (mode)
	{
	case MODE_TITLE:
		pScene = new CTitle;
		break;
	case MODE_GAME:
		pScene = new CGame;
		break;
	}
	pScene->Init(NONE);
	return pScene;
}