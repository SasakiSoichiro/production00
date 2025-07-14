//============================================================
//
//	DirectX���		[main.cpp]
//
//			Athor : ryuusei hirata 
// 
//===========================================================
#include "main.h"
#include "input.h"
#include "game.h"
#include "fade.h"
#include "title.h"
#include "result.h"
#include "ranking.h"
#include "tutrial.h"
#include "camera.h"
#include "title3D.h"
#include "item.h"
#include "enemy.h"
#include "sound.h"
#include "gimmick.h"

//=====================
//	�O���[�o���錾
//=====================
LPDIRECT3D9 g_pD3D = NULL;					//	Direct3D�ւ̃|�C���^
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;		//	Direct3D�f�o�C�X�ւ̃|�C���^	
MODE g_mode = MODE_TITLE;					//	���݂̃��[�h
bool g_isFullscreen = false;				//	�E�B���h�E��؂�ւ��邽�߂̃t���O
RECT g_windowRect;							//	�E�B���h�E��؂�ւ��邽�߂̕ϐ�
LPD3DXFONT g_pFont = NULL;					//	�t�H���g�̃|�C���^
int g_nCntFPS = 0;							//	FPS�J�E���g

//========================
//	�f�o�C�X�̏��擾
//========================
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}

//=========================
//		���C���֐�
//=========================
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hInstancePrev, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)		//_In_(ASL:�\�[�X�R�[�h���ߌ���)
{
	DWORD dwCurrentTime;	//	���݂̎���
	DWORD dwExeclastTime;	//	�Ō�ɏ�����������

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
		LoadIcon(NULL,IDI_APPLICATION),
	};

	HWND hWnd;	//	�E�B���h�E�o���h���i���ʎq�j
	MSG msg;	//	���b�Z�[�W���i�[����ϐ�

	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };		//	��ʃT�C�Y�̍\����

	//	�E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	//	�N���C�A���g�̈���w��̃T�C�Y�ɒ���
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	//	�E�B���h�E�̐���
	hWnd = CreateWindowEx(0,				//	�g���E�B���h�E�X�^�C��
		CLASS_NAME,							//	�E�B���h�E�N���X�̖��O
		WINDOW_NAME,						//	�E�B���h�E�̖��O
		WS_OVERLAPPEDWINDOW,				//	�E�B���h�E�X�^�C��
		CW_USEDEFAULT,						//	�E�B���h�E�̂����W
		CW_USEDEFAULT,						//	�E�B���h�E�̂����W
		SCREEN_WIDTH,						//	�E�B���h�E�̕�
		SCREEN_HEIGHT,						//	�E�B���h�E�̍���
		NULL,								//	�e�E�B���h�E�̃n���h��
		NULL,								//	���j���[�E�B���h�E�̃n���h���i�q�E�B���h�E�j
		hInstance,							//	�C���X�^���X�n���h��
		NULL);								//	�E�B���h�E�쐬�f�[�^

	//===============
	//	����������
	//===============
	if (FAILED(Init(hInstance, hWnd, TRUE)))
	{
		return -1;
	}

	//================
	//	����\��ݒ�
	//================
	timeBeginPeriod(1);
	dwCurrentTime = 0;					//	������
	dwExeclastTime = timeGetTime();		//	���ݎ������擾(�ۑ�)

	//===================
	//	�E�B���h�E�\��
	//===================
	ShowWindow(hWnd, SW_SHOWMAXIMIZED);
	UpdateWindow(hWnd);

	//==============
	//	FPS�̏���
	//==============
	DWORD dwFrameCount;		// �t���[���J�E���g
	DWORD dwFPSLastTime;	// �Ō��FPS���v����������

	dwFrameCount = 0;
	dwFPSLastTime = timeGetTime();

	//====================
	//	���b�Z�[�W���[�v
	//====================
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{//	window�̏���
			if (msg.message == WM_QUIT)
			{//	WM_QUIT���b�Z�[�W���󂯂��Ƃ����烋�[�v�𔲂���
				break;
			}
			else
			{
				//====================
				//	���b�Z�[�W�ݒ�
				//====================
				TranslateMessage(&msg);		//	���z�L�[���b�Z�[�W�𕶎��ɕϊ�
				DispatchMessage(&msg);		//	�E�B���h�E�v���V�[�W���֑��o
			}
		}
		else
		{
			//===================
			//	DirectX�̏���
			//===================
			dwCurrentTime = timeGetTime();

			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{
				//===============
				//	0.5�b�o��
				//	FPS���v��
				//===============
				g_nCntFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);

				dwFPSLastTime = dwCurrentTime;		//	�v������������ۑ�
				dwFrameCount = 0;					//	�t���[���J�E���g���N���A
			}

			if ((dwCurrentTime - dwExeclastTime) >= (1000 / 60))		//	60��ς����fps�オ��
			{
				//==================
				//	60����1�b�o��
				//==================
				dwExeclastTime = dwCurrentTime;	//	�����J�n�̎���[���ݎ���]��ۑ�

				//=============
				//	�X�V����
				//=============
				Update();

				//=============
				//	�`�揈��
				//=============

				Draw();

				//===========================
				//	�t���[���J�E���g���Z
				//===========================
				dwFrameCount++;

			}
		}
	}

	//============
	//	�I������
	//============
	Uninit();

	//================
	//	����\��߂�
	//================
	timeEndPeriod(1);

	//===========================
	//	�E�B���h�E�N���X�̉���
	//===========================
	UnregisterClass(CLASS_NAME, wcex.hInstance);
	return(int)msg.wParam;
}

//************************************************
// �E�B���h�E���t���X�N���[���ɕς��鏈��
//************************************************
void ToggleFullscreen(HWND hWnd)
{
	//==================================
	//	���݂̃E�B���h�E�X�^�C�����擾
	//==================================
	DWORD dwStyle = GetWindowLong(hWnd, GWL_STYLE);

	if (g_isFullscreen)
	{
		//=============================
		//	�E�B���h�E���[�h�ɐ؂�ւ�
		//=============================
		SetWindowLong(hWnd, GWL_STYLE, dwStyle | WS_OVERLAPPEDWINDOW);
		SetWindowPos(hWnd, HWND_TOP, g_windowRect.left, g_windowRect.top,
			g_windowRect.right - g_windowRect.left, g_windowRect.bottom - g_windowRect.top,
			SWP_FRAMECHANGED | SWP_NOACTIVATE);
		ShowWindow(hWnd, SW_NORMAL);
	}
	else
	{
		//==================================
		//	�t���X�N���[�����[�h�ɐ؂�ւ�
		//==================================
		GetWindowRect(hWnd, &g_windowRect);
		SetWindowLong(hWnd, GWL_STYLE, dwStyle & ~WS_OVERLAPPEDWINDOW);
		SetWindowPos(hWnd, HWND_TOP, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN),
			SWP_FRAMECHANGED | SWP_NOACTIVATE);
		ShowWindow(hWnd, SW_MAXIMIZE);
	}

	g_isFullscreen = !g_isFullscreen;
}

//-----------------------
//�E�B���h�E�v���V�[�W��
//----------------------
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	const RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };	//	�E�B���h�E�̗̈�
	bool bEdit=GetEditState();

	switch (uMsg)
	{
	case WM_DESTROY:				//	�E�B���h�E�Y��j������
		//WM_QUIT���b�Z�[�W
		PostQuitMessage(0);
		Cleanup();
		break;
	case WM_KEYDOWN:				//	[ESC]�L�[�������ꂽ
		switch (wParam)
		{
		case VK_ESCAPE:
			//int nID;
			DestroyWindow(hWnd);
			break;
		case VK_F11:
			ToggleFullscreen(hWnd);
			break;
		}
		break;
	case WM_MOUSEWHEEL:
		if (bEdit == true)
		{
			int zDelta = GET_WHEEL_DELTA_WPARAM(wParam);
			MouseWheel(zDelta);
		}
		break;

	case WM_PAINT:
		Render();
		ValidateRect(hWnd, NULL);
		break;

	case WM_SETCURSOR:
		ShowCursor(false);
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//----------------------------
//	����������
// ----------------------------
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;
	D3DPRESENT_PARAMETERS d3dpp;

	//=====================
	//	�I�u�W�F�N�g����
	//=====================
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}

	//=======================
	//	�ł����Ղꂢ�̎擾
	//=======================
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.BackBufferWidth = SCREEN_WIDTH;
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;
	d3dpp.BackBufferFormat = d3ddm.Format;
	d3dpp.BackBufferCount = 1;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	d3dpp.Windowed = bWindow;
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
	d3dpp.Windowed = TRUE;

	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&g_pD3DDevice)))
	{
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

	//===========================
	//	�����_�[�X�e�[�g�̐ݒ�
	//===========================
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//=========================
	//	�T���v���[�X�e�[�g
	//=========================
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	//=====================================
	//	�e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
	//=====================================
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);


	//================================
	//	�f�o�b�N�\���p�t�H���g�̐���
	//================================
	D3DXCreateFont(g_pD3DDevice, 18, 0, 0, 0,
		FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH,
		"Terminal", &g_pFont);

	//	�L�[�{�[�h�̏�����
	if (FAILED(InitKeyboard(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	//	�W���C�p�b�h�̏�����
	if (FAILED(InitJoypad()))
	{
		return E_FAIL;
	}

	//	�}�E�X�̏���������
	if (FAILED(InitMausu(hInstance,hWnd)))
	{
		return E_FAIL;
	}

	//���̏�����
	InitSound(hWnd);

	//���[�h�̏�����
	SetMode(g_mode);

	//�t�F�[�h�̏�����
	InitFade(g_mode);

	return S_OK;
}
//==================
//	�I������
//==================
void Uninit(void)
{
	//�@���̏I��
	//UninitSound();

	//	�L�[�{�[�h�I��
	UninitKeyboard();

	//	�W���C�p�b�h�I��
	UninitJoypad();

	//	�܂���
	UninitMausu();

	//	�t�F�[�h
	UninitFade();
	
	// �f�o�b�N�\���p�t�H���g�̔j��
	if (g_pFont != NULL)
	{
		g_pFont->Release();
		g_pFont = NULL;
	}

	//	�f�o�C�X�̔j��
	if (g_pD3DDevice != NULL)
	{
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}

	//	Direct3D�̔j��
	if (g_pD3D != NULL)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}
}

//=======================
//	�X�V����
//=======================
void Update(void)
{
	UpdateKeyboard();	//	�L�[�{�[�h
	UpdateJoypad();		//	�W���C�p�b�h
	UpdateMausu();		//  �}�E�X

	switch (g_mode)
	{
	case MODE_TITLE:
		UpdateTitle3D();	//	�^�C�g�����
		break;

	case MODE_TUTRIAL:
		UpdateTutrial();	//	�`���[�g���A��
		break;

	case MODE_GAME:
		UpdateGame();		//	�Q�[�����
		break;

	case MODE_RESULT:
		UpdateResult();		//	���U���g
		break;

	case MODE_RANKING:
		UpdateRanking();	//	�����L���O
		break;
	}

	//	�t�F�[�h�X�V
	UpdateFade();

}
//================
//	�`�揈��
//================
void Draw(void)
{
	Camera* pCamera = GetCamera();

	//	�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int n = 0; n < MAX_CAMERA; n++, pCamera++)
	{

		//	�r���[�|�[�g�̐ݒ�
		pDevice->SetViewport(&pCamera->viewport);

		//	��ʃN���A
		g_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 255), 1.0f, 0);

		//	�`��J�n
		if (SUCCEEDED(g_pD3DDevice->BeginScene()))
		{
			//�J������ݒ肷��
			SetCamera(n);

			switch (g_mode)
			{
			case MODE_TITLE:
				DrawTitle3D();		//	�^�C�g��
				break;

			case MODE_TUTRIAL:
				DrawTutrial();		//	�`���[�g���A��
				break;

			case MODE_GAME:
				DrawGame(n);			//	�Q�[��
				break;

			case MODE_RESULT:
				DrawResult();		//	���U���g
				break;

			case MODE_RANKING:
				DrawRanking();		//	�����L���O
				break;
			}

			//	�t�F�[�h�`��
			DrawFade();

#ifdef _DEBUG
			//	FPS�̕\��
			DrawFPS();

			//�J���������_�̕`�揈��
			DrawCameraPosR();

			//�J�������_�̕`�揈��
			DrawCameraPosV();

			//�J���������̕`�揈��
			DrawCameraRot();

			//���������Ă��邩�̃f�o�b�O�\������
			DrawDebugKey();

			//�G�l�~�[���W�̕`�揈��
			DrawEnemyPos();

			//	����������
			DrawHoldTime();

			//	�����Ă鎞��
			DrawNoTouchTime();
			
			//	���v����
			DrawTotalTime();

			DrawDebugPlayer();

#endif // DEBUG

			//	�I��
			g_pD3DDevice->EndScene();

			if (g_mode != MODE_GAME)
			{
				break;
			}
		}
	}

	//����ւ�
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
	
}

//	���[�h�̐ݒ�
void SetMode(MODE mode)
{
	//���݂̃��[�h�̏I������
	switch (g_mode)
	{
	case MODE_TITLE:
		UninitTitle3D();		//	�^�C�g��
		break;

	case MODE_TUTRIAL:
		UninitTutrial();		//	�`���[�g���A��	
		break;

	case MODE_GAME:
		UninitGame();		//	�Q�[��
		break;

	case MODE_RESULT:
		UninitResult();		//	���U���g
		break;

	case MODE_RANKING:
		UninitRanking();	//	�����L���O
		break;
	}

	g_mode = mode;

	switch (mode)
	{
	case MODE_TITLE:
		InitTitle3D();		//	�^�C�g��
		break;

	case MODE_TUTRIAL:		
		InitTutrial();		//	�`���[�g���A��
		break;

	case MODE_GAME:
		InitGame();			//	�Q�[��
		break;

	case MODE_RESULT:
		InitResult();		//	���U���g
		break;

	case MODE_RANKING:
		InitRanking();		//	�����L���O
		break;
	}
}
//=================
//	���[�h�̎擾
//================
MODE GetMode(void)
{
	return g_mode;
}

void SetupVertexFog(DWORD Color, DWORD Mode, BOOL UseRange, FLOAT Density)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	float Start = 10.0f,    // Linear fog distances
		End = 800.0f;

	// Enable fog blending.
	pDevice->SetRenderState(D3DRS_FOGENABLE, TRUE);

	// Set the fog color.
	pDevice->SetRenderState(D3DRS_FOGCOLOR, Color);

	// Set fog parameters.
	if (D3DFOG_LINEAR == Mode)
	{
		pDevice->SetRenderState(D3DRS_FOGVERTEXMODE, Mode);
		pDevice->SetRenderState(D3DRS_FOGSTART, *(DWORD*)(&Start));
		pDevice->SetRenderState(D3DRS_FOGEND, *(DWORD*)(&End));
	}
	else
	{
		pDevice->SetRenderState(D3DRS_FOGVERTEXMODE, Mode);
		pDevice->SetRenderState(D3DRS_FOGDENSITY, *(DWORD*)(&Density));
	}

	// Enable range-based fog if desired (only supported for
	//   vertex fog). For this example, it is assumed that UseRange
	//   is set to a nonzero value only if the driver exposes the 
	//   D3DPRASTERCAPS_FOGRANGE capability.
	// Note: This is slightly more performance intensive
	//   than non-range-based fog.
	if (UseRange)
		pDevice->SetRenderState(D3DRS_RANGEFOGENABLE, TRUE);
}


//=====================
//	FPS�\��
//=====================
void DrawFPS(void)
{
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];

	//==================
	//	������ɑ��
	//==================
	wsprintf(&aStr[0], "FPS:%d\n", g_nCntFPS);

	//===================
	//	�e�L�X�g�\��
	//===================
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 0, 0, 255));
}

//================================
// �J�����̈ʒu���W�̕`�揈��
//================================
void DrawCameraPosR(void)
{
	RECT rect = { 0,45,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];
	Camera* pCamera = GetCamera();
	sprintf(&aStr[0], "�J���������_���W�@X:%.2f�@Y:%.2f  Z:%.2f\n", pCamera->posR.x, pCamera->posR.y, pCamera->posR.z);
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(0, 0, 0, 255));
}

//================================
// �J�����̈ʒu���W�̕`�揈��
//================================
void DrawCameraPosV(void)
{
	RECT rect = { 0,60,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];
	Camera* pCamera = GetCamera();
	sprintf(&aStr[0], "�J�������_���W�@X:%.2f�@Y:%.2f  Z:%.2f\n", pCamera->posV.x, pCamera->posV.y, pCamera->posV.z);
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(0, 0, 0, 255));
}

//================================
// �J�����̌����̕`�揈��
//================================
void DrawCameraRot(void)
{
	RECT rect = { 0,75,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];
	Camera* pCamera = GetCamera();
	sprintf(&aStr[0], "�J�����̌����@X:%.2f�@Y:%.2f  Z:%.2f\n", pCamera->rot.x, pCamera->rot.y, pCamera->rot.z);
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(0, 0, 0, 255));
}
void DrawDebugKey(void)
{
	ITEM* pITEM = Getitem();

	for (int count = 0; count < MAX_ITEM; count++, pITEM++)
	{
		RECT rect = { 0,105 + count * 15,SCREEN_WIDTH,SCREEN_HEIGHT };
		char aStr[MAX_ITEM][256];

		sprintf(&aStr[count][0], "�A�C�e��%d : %d \n", count + 1,pITEM->bHave);

		g_pFont->DrawText(NULL, &aStr[count][0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(0, 0, 0, 255));
	}
}

//================================
// �J�����̈ʒu���W�̕`�揈��
//================================
void DrawEnemyPos(void)
{
	RECT rect = { 0,90,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];
	Enemy* pCamera = GetEnemy();
	sprintf(&aStr[0], "�J���������_���W�@X:%.2f�@Y:%.2f  Z:%.2f\n", pCamera->pos.x, pCamera->pos.y, pCamera->pos.z);
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 0, 0, 255));
}

//================================
//	�z�[���h����
//================================
void DrawHoldTime(void)
{
	HOLD* pHold = GetHold();

	RECT rect = { 0,210,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];
	sprintf(&aStr[0], "���������� : %d �b\n",pHold->nHoldCount);
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(0, 0, 0, 255));

}

//================================
//	�����Ă鎞��
//================================
void DrawNoTouchTime(void)
{
	HOLD* pHold = GetHold();

	RECT rect = { 0,225,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];
	sprintf(&aStr[0], "�����Ă鎞�� : %d �b\n", pHold->NoTouch);
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(0, 0, 0, 255));

}

void DrawTotalTime(void)
{
	HOLD* pHold = GetHold();

	RECT rect = { 0,240,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];
	sprintf(&aStr[0], "���݂̒��������� : %d �b\n", pHold->HolTime);
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(0, 0, 0, 255));

}
void DrawDebugPlayer(void)
{
	Player* pPlayer = GetPlayer();

	RECT rect = { 0,255,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];
	sprintf(&aStr[0], "Player->Pos.x = %.1f : Player->Pos.y = %.1f : Player->Pos.z = %.1f\n", pPlayer->pos.x,pPlayer->pos.y,pPlayer->pos.z);
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 0, 0, 255));
}
//-----------------------------------------------------------------------------
// �N���[���A�b�v
//-----------------------------------------------------------------------------
VOID Cleanup()
{
	if (g_pD3DDevice != NULL)
		g_pD3DDevice->Release();

	if (g_pD3D != NULL)
		g_pD3D->Release();
}
//-----------------------------------------------------------------------------
// �����_�[
//-----------------------------------------------------------------------------
VOID Render()
{
	if (NULL == g_pD3DDevice)
		return;

	// ���ŃN���A
	g_pD3DDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(255, 255, 255), 1.0f, 0);

	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{
		g_pD3DDevice->EndScene();
	}

	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}