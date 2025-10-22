//**********************************
//
// �����_���[���� [renderer.cpp]
// Author:Sasaki Soichiro
//
//**********************************

//*******************
// �C���N���[�h
//*******************
#include "renderer.h"
#include "object.h"
#include "debugproc.h"
#include "input.h"
#include "manager.h"
#include "blurManager.h"
#include "fade.h"

//===================
// �R���X�g���N�^
//===================
CRenderer::CRenderer() 
{
	m_pD3D = NULL;			// Direct3D�I�u�W�F�N�g�ւ̃|�C���^
	m_pD3DDevice = NULL;		// Direct3D�f�o�C�X�ւ̃|�C���^
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		m_pTextureMT[nCnt] = NULL;
		m_pRenderMT[nCnt] = NULL;
	}
	m_pZBuffMT = NULL;
	m_viewportMT = {};
	m_vtxBuffMT = NULL;
}
//===================
// �f�X�g���N�^
//===================
CRenderer::~CRenderer()
{
}
//=============
// ����������
//=============
HRESULT CRenderer::Init(HWND hWnd,BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;
	D3DPRESENT_PARAMETERS d3dpp;
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (m_pD3D == NULL)
	{
		return E_FAIL;
	}
	if (FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}
	//�f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp));//�p�����[�^�̃[���N���A

	d3dpp.BackBufferWidth = SCREEN_WIDTH;						// �Q�[����ʃT�C�Y(��)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;						// �Q�[����ʃT�C�Y(����)
	d3dpp.BackBufferFormat = d3ddm.Format;						// �o�b�N�o�b�t�@�̌`��
	d3dpp.BackBufferCount = 1;									// �o�b�N�o�b�t�@�̐�
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;					// �_�u���o�b�t�@�̐؂�ւ�(�f���M���ɓ���)
	d3dpp.EnableAutoDepthStencil = TRUE;						// �f�u�X�o�b�t�@�ƃX�e���V�u���o�b�t�@���쐬
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;				// Z�o�b�t�@:24bit �X�e���V��:8bit
	d3dpp.Windowed = bWindow;									// �E�B���h�E���[�h
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;	// ���t���b�V�����[�g
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;	// �C���^�[�o��

	//Direct3D�f�o�C�X�̐���(�`�揈���ƒ��_�������n�[�h�E�F�A�ōs�Ȃ�)
	if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&m_pD3DDevice)))
	{
		//DirectX3D�f�o�C�X�̐���(�`�揈����CPU�ōs�Ȃ�)
		if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&m_pD3DDevice)))
		{
			//Direct3D�f�o�C�X�ɐ���(�`�揈���ƒ��_������CPU�ōs�Ȃ�)
			if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&m_pD3DDevice)))
			{
				return E_FAIL;
			}
		}
	}
	//�����_�[�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);				// �J�����O�̐ݒ�
	m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);				//========================
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// �A���t�@�u�����h�̐ݒ�
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	//========================

	m_pD3DDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);

	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
	//�e�N�X�`���X�e�[�W�X�e�[�g
	m_pD3DDevice->SetTextureStageState(1, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	m_pD3DDevice->SetTextureStageState(1, D3DTSS_COLORARG2, D3DTA_CURRENT);
	m_pD3DDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_MODULATE);

	LPDIRECT3DSURFACE9 pRenderDef = nullptr, pZBuffDef = nullptr;

	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		// �����_�����O�^�[�Q�b�g�p�e�N�X�`���̐���
		m_pD3DDevice->CreateTexture(SCREEN_WIDTH,
			SCREEN_HEIGHT,
			1,
			D3DUSAGE_RENDERTARGET,
			D3DFMT_A8R8G8B8,
			D3DPOOL_DEFAULT,
			&m_pTextureMT[nCnt],
			NULL);

		// �e�N�X�`�������_�����O�p�C���^�[�t�F�[�X�̐���
		m_pTextureMT[nCnt]->GetSurfaceLevel(0, &m_pRenderMT[nCnt]);

	}

	// �e�N�X�`�������_�����O�pZ�o�b�t�@�̐���
	m_pD3DDevice->CreateDepthStencilSurface(SCREEN_WIDTH,
		SCREEN_HEIGHT,
		D3DFMT_D16,
		D3DMULTISAMPLE_NONE,
		0,
		TRUE,
		&m_pZBuffMT,
		NULL);

	// ���݂̃����_�����O�^�[�Q�b�g���擾(�ۑ�)
	m_pD3DDevice->GetRenderTarget(0, &pRenderDef);
	m_pD3DDevice->GetDepthStencilSurface(&pZBuffDef);
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		m_pD3DDevice->SetRenderTarget(0, m_pRenderMT[nCnt]);
	}
	m_pD3DDevice->SetDepthStencilSurface(m_pZBuffMT);
	m_pD3DDevice->Clear(0, NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 255), 1.0f, 0);
	m_pD3DDevice->SetRenderTarget(0, pRenderDef);
	m_pD3DDevice->SetDepthStencilSurface(pZBuffDef);

	// �e�N�X�`�������_�����O�p�r���[�|�[�g�̐ݒ�
	m_viewportMT.X = 0;
	m_viewportMT.Y = 0;
	m_viewportMT.Width = SCREEN_WIDTH;
	m_viewportMT.Height = SCREEN_HEIGHT;
	m_viewportMT.MinZ = 0.0f;
	m_viewportMT.MaxZ = 1.0f;

	m_pD3DDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,//(sizeof(VERTEX_3D)*�K�v�Ȓ��_��
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_vtxBuffMT,
		NULL);

	VERTEX_2D* pVtx = 0;//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_vtxBuffMT->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-0.5f, -0.5f, 0.0f);//���E���Őݒ肷��
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH - 0.5f, -0.5f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-0.5f, SCREEN_HEIGHT - 0.5f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH - 0.5f, SCREEN_HEIGHT - 0.5f, 0.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;
	//���_�J���[�̐ݒ�@�@�@�@
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);


	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_vtxBuffMT->Unlock();

	return S_OK;
}

//===========
// �I������
//===========
void CRenderer::Uninit(void)
{
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		if (m_pTextureMT[nCnt] != NULL)
		{
			m_pTextureMT[nCnt]->Release();
			m_pTextureMT[nCnt] = NULL;
		}

		if (m_pRenderMT[nCnt] != NULL)
		{
			m_pRenderMT[nCnt]->Release();
			m_pRenderMT[nCnt] = NULL;
		}

	}

	if (m_pZBuffMT != NULL)
	{
		m_pZBuffMT->Release();
		m_pZBuffMT = NULL;
	}

	//Direct3D�f�o�C�X�̔j��
	if (m_pD3DDevice != NULL)
	{
		m_pD3DDevice->Release();
		m_pD3DDevice = NULL;
	}
	//Direct3D�I�u�W�F�N�g�̔j��
	if (m_pD3D != NULL)
	{
		m_pD3D->Release();
		m_pD3D = NULL;
	}
}

//============
// �X�V����
//============
void CRenderer::Update(void)
{
	// �|���S���̍X�V
	CObject::UpdateAll();
	//m_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
}

//===========
// �`�揈��
//===========
void CRenderer::Draw(void)
{
	bool bBlur=CBlurManager::GetBool();
	CFade* pFade = CManager::GetFade();
	if (bBlur == true)
	{
		LPDIRECT3DSURFACE9 pRenderDef, pZBuffDef;
		LPDIRECT3DSURFACE9 pRenderWk;
		LPDIRECT3DTEXTURE9 pTextureWk;
		D3DVIEWPORT9 viewportDef;
		D3DXMATRIX mtxViewDef, mtxProjectionDef;

		VERTEX_2D* pVtx = 0;//���_���ւ̃|�C���^
		m_pD3DDevice->GetRenderTarget(0, &pRenderDef);
		m_pD3DDevice->GetDepthStencilSurface(&pZBuffDef);
		// ���݂̃r���[�|�[�g���擾
		m_pD3DDevice->GetViewport(&viewportDef);
		m_pD3DDevice->GetTransform(D3DTS_VIEW, &mtxViewDef);
		m_pD3DDevice->GetTransform(D3DTS_PROJECTION, &mtxProjectionDef);


		// ��ʂ̃N���A(�o�b�N�o�b�t�@��Z�o�b�t�@�̃N���A)
		m_pD3DDevice->Clear(0, NULL,
			(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
			D3DCOLOR_RGBA(175, 223, 228, 255), 1.0f, 0);

		ChangeTarget(D3DXVECTOR3(0.0f, 100.0f, 100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f));


		// ��ʂ̃N���A(�o�b�N�o�b�t�@��Z�o�b�t�@�̃N���A)
		m_pD3DDevice->Clear(0, NULL,
			(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
			D3DCOLOR_RGBA(175, 223, 228, 255), 1.0f, 0);


		// �`�揈��
		if (SUCCEEDED(m_pD3DDevice->BeginScene()))
		{// �`��J�n�����������ꍇ


			// �|���S���̕`��
			CObject::DrawAll();
			pFade->Draw();
			CDebugProc::Draw();
			m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);				//========================
			m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// �A���t�@�u�����h�̐ݒ�
			m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	//========================

			m_pD3DDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
			m_pD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
			m_pD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);

			m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
			m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
			m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);


			//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
			m_vtxBuffMT->Lock(0, 0, (void**)&pVtx, 0);

			//���_�J���[�̐ݒ�@�@�@�@
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.983f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.983f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.983f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.983f);

			//���_�o�b�t�@���A�����b�N����
			m_vtxBuffMT->Unlock();


			//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			m_pD3DDevice->SetStreamSource(0, m_vtxBuffMT, 0, sizeof(VERTEX_2D));
			//���_�t�H�[�}�b�g�̐ݒ�
			m_pD3DDevice->SetFVF(FVF_VERTEX_2D);

			//�e�N�X�`���̐ݒ�
			m_pD3DDevice->SetTexture(0, m_pTextureMT[1]);

			//�|���S���̕`��
			m_pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);


			m_pD3DDevice->SetRenderTarget(0, pRenderDef);
			m_pD3DDevice->SetDepthStencilSurface(pZBuffDef);

			//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
			m_vtxBuffMT->Lock(0, 0, (void**)&pVtx, 0);

			//���_�J���[�̐ݒ�@�@�@�@
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			//���_�o�b�t�@���A�����b�N����
			m_vtxBuffMT->Unlock();

			//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			m_pD3DDevice->SetStreamSource(0, m_vtxBuffMT, 0, sizeof(VERTEX_2D));
			//���_�t�H�[�}�b�g�̐ݒ�
			m_pD3DDevice->SetFVF(FVF_VERTEX_2D);
			//�e�N�X�`���̐ݒ�
			m_pD3DDevice->SetTexture(0, m_pTextureMT[0]);

			//�|���S���̕`��
			m_pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);


			// �`��I��
			m_pD3DDevice->EndScene();
		}
		// �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
		m_pD3DDevice->Present(NULL, NULL, NULL, NULL);

		// �e�N�X�`��[0]�ƃe�N�X�`��[1]�����ւ���
		pTextureWk = m_pTextureMT[0];
		m_pTextureMT[0] = m_pTextureMT[1];
		m_pTextureMT[1] = pTextureWk;

		pRenderWk = m_pRenderMT[0];
		m_pRenderMT[0] = m_pRenderMT[1];
		m_pRenderMT[1] = pRenderWk;
	}
	else
	{
		// ��ʂ̃N���A(�o�b�N�o�b�t�@��Z�o�b�t�@�̃N���A)
		m_pD3DDevice->Clear(0, NULL,
			(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL),
			D3DCOLOR_RGBA(175, 223, 228, 255), 1.0f, 0);
		// �`�揈��
		if (SUCCEEDED(m_pD3DDevice->BeginScene()))
		{// �`��J�n�����������ꍇ

			// �|���S���̕`��
			CObject::DrawAll();
			pFade->Draw();
			CDebugProc::Draw();
			// �`��I��
			m_pD3DDevice->EndScene();
		}
		// �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
		m_pD3DDevice->Present(NULL, NULL, NULL, NULL);

	}
}

//*****************
// �f�o�C�X�̎擾
//*****************
LPDIRECT3DDEVICE9 CRenderer::GetDevice(void)
{
	return m_pD3DDevice;
}

//******************************
// �����_�����O�^�[�Q�b�g�̕ύX
//******************************
void CRenderer::ChangeTarget(D3DXVECTOR3 posV, D3DXVECTOR3 posR, D3DXVECTOR3 vecU)
{
	D3DXMATRIX mtxView, mtxProjection;
	float fAspect;

	// �����_�����O�^�[�Q�b�g�𐶐��e�N�X�`���ɐݒ�
	m_pD3DDevice->SetRenderTarget(0, m_pRenderMT[0]);
	m_pD3DDevice->SetDepthStencilSurface(m_pZBuffMT);

	// �e�N�X�`�������_�����O�p�̃r���[�|�[�g��ݒ�
	m_pD3DDevice->SetViewport(&m_viewportMT);

	// �r���[�}�g���b�N�X������
	D3DXMatrixIdentity(&mtxView);

	//�r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&mtxView,
		&posV,
		&posR,
		&vecU);

	// �r���[�}�g���b�N�X�̐ݒ�
	m_pD3DDevice->SetTransform(D3DTS_VIEW, &mtxView);

	//�v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxProjection);

	fAspect = (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT;
	//�v���W�F�N�V�����}�g���b�N�X�̍쐬
	D3DXMatrixPerspectiveFovLH(&mtxProjection,
		D3DXToRadian(100.0f),						// ����p
		fAspect,									// �A�X�y�N�g��
		10.0f,										// �j�A �ǂ��܂ŋ߂����f����
		1000.0f);									// �t�@�[�@�ǂ��܂ŉ������f����

	//�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	m_pD3DDevice->SetTransform(D3DTS_PROJECTION, &mtxProjection);
}