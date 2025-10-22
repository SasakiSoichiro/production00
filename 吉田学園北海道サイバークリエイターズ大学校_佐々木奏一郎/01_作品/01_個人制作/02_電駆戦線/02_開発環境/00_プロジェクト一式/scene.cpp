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
#include "reslut.h"
#include "edit.h"
#include "tutorial.h"

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
	case MODE_RESULT:
		pScene = new CResult;
		break;
	case MODE_EDIT:
		pScene = new CEdit;
		break;
	case MODE_TUTORIAL:
		pScene = new CTutorial;
		break;
	}
	pScene->Init(NONE);
	return pScene;
}