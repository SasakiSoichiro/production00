//**********************************
//
// ���C������ [main.cpp]
// Author:Sasaki Soichiro
//
//**********************************

//*******************
// �C���N���[�h
//*******************
#include "main.h"
#include "renderer.h"
#include "object.h"
#include "object2D.h"
#include<crtdbg.h>
#include "manager.h"
#include "debugproc.h"


//====================================
// ���C���֐�
//====================================
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_ HINSTANCE hInstanceprev, _In_ LPSTR bCmdLine, int nCmdShow)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF);			// ���������[�N���m�p�̃t���O
	DWORD dwCurrentTime;		// ���ݎ���
	DWORD dwExecLastTime;		// �Ō�ɏ�����������
	DWORD dwFrameCnt;
	DWORD dwFPSLastTime;
	CManager* pManager = new CManager;
	int nCntFPS=0;
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

	pManager->Init(hInstance,hWnd, TRUE);
	//����\��ݒ�
	timeBeginPeriod(1);
	dwCurrentTime = 0;
	dwExecLastTime = timeGetTime();
	//�E�B���h�E�̕\��
	ShowWindow(hWnd, nCmdShow);
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
					nCntFPS = (dwFrameCnt * 1000) / (dwCurrentTime - dwFPSLastTime);
					dwFPSLastTime = dwCurrentTime;
					dwFrameCnt = 0;
				}
				if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
				{//60����1�b�o��
					dwExecLastTime = dwCurrentTime;//�����J�n������ۑ�
					//�X�V����
					pManager->Update();
					CDebugProc::Print("FPS:%d",nCntFPS);
					//�`�揈��
					pManager->Draw();
					dwFrameCnt++;
				}
			
			}
	}
	if (pManager != NULL)
	{
		pManager->Uninit();
		delete pManager;
		pManager = NULL;
	}
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
