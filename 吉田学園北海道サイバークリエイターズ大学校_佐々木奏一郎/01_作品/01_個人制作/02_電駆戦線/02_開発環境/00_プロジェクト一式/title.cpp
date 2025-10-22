//**********************************
//
// タイトル処理 [title.cpp]
// Author:Sasaki Soichiro
//
//**********************************

//*******************
// インクルード
//*******************
#include "scene.h"
#include "title.h"
#include "titleUI.h"
#include "titleSegway.h"
#include "manager.h"
#include "stand.h"
#include "sound.h"
#include "startUI.h"
#include "input.h"
#include "camera.h"
#include "skydoom.h"
#include "fade.h"

//*******************
// コンストラクタ
//*******************
CTitle::CTitle() :CScene(CScene::MODE_TITLE)
{
}

//*******************
// デストラクタ
//*******************
CTitle::~CTitle()
{
}

//*************
// 初期化処理
//*************
HRESULT CTitle::Init(D3DXVECTOR3 pos)
{
	CSound* pSound = CManager::GetCSound();
	CTitleUI::Create(D3DXVECTOR3(300.0f, 150.0f, 0.0f));
	CTitleSegway::Create(D3DXVECTOR3(0.0f, 50.0f, 0.0f));
	CStand::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	CStartUI::Create(D3DXVECTOR3(SCREEN_WIDTH/2.0f, 600.0f, 0.0f));
	CSkyDoom::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	pSound->Play(CSound::LABEL_BGM00);
	CCamera* pCamera = CManager::GetCCamera();
	pCamera->InitTarget(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	return S_OK;
}

//*************
// 終了処理
//*************
void CTitle::Uninit(void)
{
	CObject::Release();
}

//*************
// 更新処理
//*************
void CTitle::Update(void)
{
	// キーボードの取得
	CInputKeyboard* pInputKeyboard = CManager::GetCInputKeyboard();
	CInputJoypad* pInputJoypad = CManager::GetCInputJoypad();
	if (pInputKeyboard->Trigger(DIK_RETURN)==true||pInputJoypad->GetTrigger(CInputJoypad::JOYKEY_START)==true)
	{
		CFade::Set(CScene::MODE_TUTORIAL);
	}
}

//**************
// 描画処理
//**************
void CTitle::Draw(void)
{

}