//=============================================================================
//
//���C������ [main.cpp]
// Author : ���X�ؑt��Y 
// 
//=============================================================================
#include "main.h"
#include "player.h"
#include "input.h"
#include "block.h"
#include "fade.h"
#include "sound.h"
#include "title.h"
#include "tutorial.h"
#include "game.h"
#include "result.h"
//#include "ranking.h"
#include "edit.h"
#include "stageselect.h"
#include "blockinfo.h"
//�O���[�o���ϐ�
LPDIRECT3D9 g_pD3D = NULL;				//Direct3D�I�u�W�F�N�g�ւ̃|�C���^
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;	//Direct3D�f�o�C�X�ւ̃|�C���^
LPD3DXFONT g_pFont = NULL;				//�Ȃɂ���
int g_nCntFPS = 0;						//FPS�̃J�E���g
bool g_Start = false;					//�Q�[�����X�^�[�g�����ǂ���
MODE g_mode = MODE_TITLE;				//���݂̃��[�h

//====================================
// ���C���֐�
//====================================
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_ HINSTANCE hInstanceprev, _In_ LPSTR bCmdLine, int nCmdShow)
{
	DWORD dwCurrentTime;	//���ݎ���
	DWORD dwExecLastTime;	//�Ō�ɏ�����������
	DWORD dwFrameCnt;
	DWORD dwFPSLastTime;
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WindowProc,
		0,
		0,
		hInstance,
		LoadIcon(NULL,IDI_APPLICATION),
		LoadCursor(NULL,IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		CLASS_NAME,
		LoadIcon(NULL,IDI_APPLICATION)
	};
	HWND hWnd;
	MSG msg;
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	//�E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);
	//�E�B���h�E�𐶐�
	hWnd = CreateWindowEx(0,
		CLASS_NAME,
		WINDOW_NAME,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		NULL,
		NULL,
		hInstance,
		NULL);
	//����������
	if (FAILED(Init(hInstance, hWnd, TRUE)))
	{//���������������s�����ꍇ
		return-1;
	}
	//����\��ݒ�
	timeBeginPeriod(1);
	dwCurrentTime = 0;
	dwExecLastTime = timeGetTime();
	//�E�B���h�E�̕\��
	ShowWindow(hWnd, SW_SHOWMAXIMIZED);
	UpdateWindow(hWnd);
	dwFrameCnt = 0;
	dwFPSLastTime = timeGetTime();
	//���b�Z�[�W���[�v
	while(1)// (GetMessage(&msg, NULL, 0, 0) != 0)
	{
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
			{//windows�̏���
				if(msg.message==WM_QUIT)
				{//WM_QUIT���b�Z�[�W���󂯎�����烁�b�Z�[�W���[�v�𔲂���
					break;
				}
			else
			{//���b�Z�[�W�̐ݒ�
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
			else
			{//DirectX�̏���
				dwCurrentTime = timeGetTime();//���ݎ������擾
				if ((dwCurrentTime - dwFPSLastTime) >= 500)
				{
					g_nCntFPS = (dwFrameCnt * 1000) / (dwCurrentTime - dwFPSLastTime);
					dwFPSLastTime = dwCurrentTime;
					dwFrameCnt = 0;
				}
				if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
				{//60����1�b�o��
					dwExecLastTime = dwCurrentTime;//�����J�n������ۑ�
					//�X�V����
					Update();
					//�`�揈��
					Draw();
					dwFrameCnt++;
				}
			
			}
	}
	//�I������
	Uninit();
	timeEndPeriod(1);
	//�E�B���h�E�̓o�^������
	UnregisterClass(CLASS_NAME, wcex.hInstance);
	return (int)msg.wParam;
}

//====================
//�v���V�[�W��
//====================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			//�E�B���h�E��j������
			DestroyWindow(hWnd);
			break;
		}
		break;
	}
  	return DefWindowProc(hWnd,uMsg,wParam,lParam);
}

//=======================
//�f�o�C�X�̎擾
//=======================
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}

//=======================
//����������
//=======================
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;
	D3DPRESENT_PARAMETERS d3dpp;
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}
	//�f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp));//�p�����[�^�̃[���N���A

	d3dpp.BackBufferWidth = SCREEN_WIDTH;						//�Q�[����ʃT�C�Y(��)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;						//�Q�[����ʃT�C�Y(����)
	d3dpp.BackBufferFormat = d3ddm.Format;						//�o�b�N�o�b�t�@�̌`��
	d3dpp.BackBufferCount = 1;									//�o�b�N�o�b�t�@�̐�
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;					//�_�u���o�b�t�@�̐؂�ւ�(�f���M���ɓ���)
	d3dpp.EnableAutoDepthStencil = TRUE;						//�f�u�X�o�b�t�@�ƃX�e���V�u���o�b�t�@���쐬
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;					//�f�u�X�o�b�t�@�Ƃ���16bit���g��
	d3dpp.Windowed = bWindow;									//�E�B���h�E���[�h
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;	//���t���b�V�����[�g
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;	//�C���^�[�o��

	//Direct3D�f�o�C�X�̐���(�`�揈���ƒ��_�������n�[�h�E�F�A�ōs�Ȃ�)
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&g_pD3DDevice)))
	{
		//DirectX3D�f�o�C�X�̐���(�`�揈����CPU�ōs�Ȃ�)
		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&g_pD3DDevice)))
		{
			//Direct3D�f�o�C�X�ɐ���(�`�揈���ƒ��_������CPU�ōs�Ȃ�)
			if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&g_pD3DDevice)))
			{
				return E_FAIL;
			}
		}
	}

	//�f�o�b�O�t�H���g�̐���
	D3DXCreateFont(g_pD3DDevice, 18, 0, 0, 0,
		FALSE,
		SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH,
		"Terminal", &g_pFont);
	//�����_�[�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);			//�J�����O�̐ݒ�
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE);          //======================
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);    //�A���t�@�u�����h�̐ݒ�
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);//======================
	//�T���v���[�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
	//�e�N�X�`���X�e�[�W�X�e�[�g
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	//�e��I�u�W�F�N�g�̏���������

	//�L�[�{�[�h�̏���������
	if (FAILED(InitKeyboard(hInstance, hWnd)))
	{
		return E_FAIL;
	}
	//�W���C�p�b�h�̏���������
	if (FAILED(InitJoypad()))
	{
		return E_FAIL;
	}


	InitSound(hWnd);

	SetMode(g_mode);

	InitFade(g_mode);



	return S_OK;
}
//==================
//�I������
//==================
void Uninit(void)
{


	//�f�o�b�O�\���p�̃t�H���g��j��
	if (g_pFont != NULL)
	{
		g_pFont->Release();
		g_pFont = NULL;
	}

	//�e�I�u�W�F�N�g�̏I������

	//�t�F�[�h�̏I������
	UninitFade();

	//�T�E���h�̏I������
	UninitSound();

	//�L�[�{�[�h�̏I������
	UninitKeyboard();

	//�W���C�p�b�h�̏I������
	UninitJoypad();

	//Direct3D�f�o�C�X�̔j��
	if (g_pD3DDevice != NULL)
	{
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}
	//Direct3D�I�u�W�F�N�g�̔j��
	if (g_pD3D != NULL)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}

}

//==================
//�X�V����
//==================
void Update(void)
{
	XINPUT_STATE* pStick = GetJoypad();
	//�e��I�u�W�F�N�g�̍X�V����


	//�L�[�{�[�h�̍X�V����
	UpdateKeyboard();

	//�W���C�p�b�h�̍X�V����
	UpdateJoypad();

	switch (g_mode)
	{
	case MODE_TITLE://�^�C�g�����

		UpdateTitle();//�^�C�g���̍X�V����
		break;
	case MODE_TUTORIAL://�`���[�g���A�����

		UpdateTutorial();//�`���[�g���A���̍X�V����
		break;
	case MODE_GAME://�Q�[�����

		if (KeyboardTrigger(DIK_E) == true || KeyboardTrigger(DIK_Q) == true|| JoyPadTrigger(JOYKEY_LEFT)==true|| JoyPadTrigger(JOYKEY_RIGHT)==true||pStick->Gamepad.sThumbLX <= -20000 || pStick->Gamepad.sThumbLX >= 20000)
		{
			g_Start = true;
		}
		if(g_Start == true)
		{
			UpdateGame();//�Q�[���̍X�V����
		}
		break;
	case MODE_RESULT://���U���g���

		UpdateResult();//���U���g�̍X�V����
		break;
	case MODE_RANKING://�����L���O���

		break;

	case MODE_EDIT://�G�f�B�b�g���

		UpdateEdit();//�G�f�B�b�g�̍X�V����
		break;
	case MODE_STAGESELECT://�X�e�[�W�I�����

		UpdateStageSelect();//�X�e�[�W�I���̍X�V����
		break;

	case MODE_BLOCKINFO://�X�e�[�W�I�����

		UpdateBlockInfo();//�X�e�[�W�I���̍X�V����
		break;
	}
	//�t�F�[�h�̍X�V����
	UpdateFade();

}

//=========
//�`�揈��
//=========
void Draw(void)
{
	//��ʂ̃N���A(�o�b�N�o�b�t�@��Z�o�b�t�@�̃N���A)
	g_pD3DDevice->Clear(0, NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	//�`�揈��
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{//�`��J�n�����������ꍇ
		switch (g_mode)
		{
		case MODE_TITLE://�^�C�g�����

			DrawTitle();//�^�C�g���̕`�揈��
			break;
		case MODE_TUTORIAL://�^�C�g�����

			DrawTutorial();//�`���[�g���A���̕`�揈��
			break;
		case MODE_GAME://�Q�[�����

			DrawGame();//�Q�[���̕`�揈��
			break;
		case MODE_RESULT://���U���g���

			DrawResult();//���U���g�̕`�揈��
			break;
		case MODE_RANKING://���U���g���

			break;
		case MODE_EDIT://���U���g���

			DrawEdit();//�����L���O�̕`�揈��
			break;
		case MODE_STAGESELECT://���U���g���

			DrawStageSelect();//�����L���O�̕`�揈��
			break;
		case MODE_BLOCKINFO://�X�e�[�W�I�����

			DrawBlockInfo();//�X�e�[�W�I���̍X�V����
			break;
		}
		//�t�F�[�h�̕`�揈��
		DrawFade();

#ifdef _DEBUG//�f�o�b�O�̏ꍇ
		
		////FPS�̕`�揈��
		//DrawFPS();

		////�v���C���[���W�̕`�揈��
		//DrawPos();

		////�����蔻����W�̕`�揈��
		//DrawPosPGCircle();

		////�A�j���[�V�����p�^�[���̕`�揈��
		//DrawAnimPatten();

		////�A�j���[�V�����p�^�[���̕`�揈��
		//DrawPosPYCircle();

		////���[�u�l�̕`�揈��
		//DrawMove();

		////���݂̃X�e�[�W
		//DrawStage();


#endif
		//�`��I��
		g_pD3DDevice->EndScene();
	}
	//�o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//===================
//���[�h�̏�Ԑݒ�
//===================
void SetMode(MODE mode)
{
	//���݂̉�ʂ̏I������
	switch (g_mode)
	{
	case MODE_TITLE://�^�C�g�����

		UninitTitle();//�^�C�g���̏I������
		break;
	case MODE_TUTORIAL://�`���[�g���A�����

		UninitTutorial();//�`���[�g���A���̏I������
		break;
	case MODE_GAME://�Q�[�����

		UninitGame();//�Q�[���̏I������
		break;
	case MODE_RESULT://���U���g���

		UninitResult();//���U���g�̏I������
		break;
	case MODE_RANKING://�����L���O���

		break;
	case MODE_EDIT://���U���g���

		UninitEdit();//�����L���O�̕`�揈��
		break;
	case MODE_STAGESELECT://���U���g���

		UninitStageSelect();//�����L���O�̕`�揈��
		break;
	case MODE_BLOCKINFO://�X�e�[�W�I�����

		UninitBlockInfo();//�X�e�[�W�I���̍X�V����
		break;
	}
	//�V������ʂ̏���������
	switch (mode)
	{
	case MODE_TITLE://�^�C�g�����

		InitTitle();//�^�C�g���̏���������
		break;
	case MODE_TUTORIAL://�`���[�g���A�����

		InitTutorial();//�`���[�g���A���̏���������
		break;
	case MODE_GAME://�Q�[�����

		InitGame();//�Q�[���̏���������
		g_Start = false;
		break;
	case MODE_RESULT://���U���g���

		InitResult();//���U���g�̏���������
		break;
	case MODE_RANKING://���U���g���

		break;
	case MODE_EDIT://���U���g���

		InitEdit();//�����L���O�̕`�揈��
		break;
	case MODE_STAGESELECT:
		InitStageSelect();
		break;
	case MODE_BLOCKINFO://�X�e�[�W�I�����

		InitBlockInfo();//�X�e�[�W�I���̍X�V����
		break;
	}
	g_mode = mode;//���݂̉�ʂ�؂�ւ���
}
//==================
//���[�h�̎擾
//==================
MODE GetMode(void)
{
	return g_mode;
}

//===============
// FPS�̕`�揈��
//===============
void DrawFPS(void)
{
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];
	wsprintf(&aStr[0], "FPS:%d\n", g_nCntFPS);
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
}


//================================
// �v���C���[�̈ʒu���W�̕`�揈��
//================================
void DrawPos(void)
{
	RECT rect = { 0,15,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];
	Player* pPlayer = GetPlayer();
	float fX= pPlayer->pos.x, fY= pPlayer->pos.y;
	sprintf(&aStr[0], "�v���C���[���W�@X:%.2f�@Y:%.2f\n", pPlayer->pos.x,pPlayer->pos.y);
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
}

//==========================================
// �A�j���[�V�����p�^�[���J�E���g�̕`�揈��
//==========================================
void DrawAnimPatten(void)
{
	RECT rect = { 0,30,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];
	Player* pPlayer = GetPlayer();
	wsprintf(&aStr[0], "�A�j���[�V�����p�^�[���J�E���g:%d\n", pPlayer->nPatternAnim);
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
}

//================================
// �v���C���[�̈ʒu���W�̕`�揈��
//================================
void DrawPosPGCircle(void)
{
	RECT rect = { 0,45,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];
	Player* pPlayer = GetPlayer();
	float fX = pPlayer->pos.x, fY = pPlayer->pos.y;
	sprintf(&aStr[0], "�|�S�����蔻����W�@X:%.2f�@Y:%.2f\n", pPlayer->posPGCircle.x, pPlayer->posPGCircle.y);
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
}

//================================
// �v���C���[�̈ʒu���W�̕`�揈��
//================================
void DrawPosPYCircle(void)
{
	RECT rect = { 0,60,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];
	Player* pPlayer = GetPlayer();
	float fX = pPlayer->pos.x, fY = pPlayer->pos.y;
	sprintf(&aStr[0], "�v���C���[�����蔻����W�@X:%.2f�@Y:%.2f\n", pPlayer->posPYCircle.x, pPlayer->posPYCircle.y);
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
}

//================================
// �v���C���[�̈ʒu���W�̕`�揈��
//================================
void DrawMove(void)
{
	RECT rect = { 0,75,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];
	Player* pPlayer = GetPlayer();
	sprintf(&aStr[0], "���[�u�l�@X:%.2f�@Y:%.2f\n", pPlayer->move.x, pPlayer->move.y);
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
}

void DrawStage(void)
{
	RECT rect = { 0,90,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];
	int stage = GetStage();
	sprintf(&aStr[0], "�X�e�[�W%d\n", stage);
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
}