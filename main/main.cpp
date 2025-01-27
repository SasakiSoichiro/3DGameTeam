//============================================================
//
//	DirectX基盤		[main.cpp]
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
#include "sound.h"

//=====================
//	グローバル宣言
//=====================
LPDIRECT3D9 g_pD3D = NULL;					//	Direct3Dへのポインタ
LPDIRECT3DDEVICE9 g_pD3DDeviec = NULL;		//	
MODE g_mode = MODE_TITLE;					//	現在のモード
bool g_isFullscreen = false;				//	ウィンドウを切り替えるためのフラグ
RECT g_windowRect;							//	ウィンドウを切り替えるための変数
LPD3DXFONT g_pFont = NULL;					//	フォントのポインタ
int g_nCntFPS = 0;							//	FPSカウント

//========================
//	デバイスの情報取得
//========================
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDeviec;
}

//=========================
//		メイン関数
//=========================
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hInstancePrev, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)		//_In_(ASL:ソースコード注釈言語)
{
	DWORD dwCurrentTime;	//	現在の時刻
	DWORD dwExeclastTime;	//	最後に処理した時刻

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

	HWND hWnd;	//	ウィンドウバンドル（識別子）
	MSG msg;	//	メッセージを格納する変数

	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };		//	画面サイズの構造体

	//	ウィンドウクラスの登録
	RegisterClassEx(&wcex);

	//	クライアント領域を指定のサイズに調整
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	//	ウィンドウの生成
	hWnd = CreateWindowEx(0,				//	拡張ウィンドウスタイル
		CLASS_NAME,							//	ウィンドウクラスの名前
		WINDOW_NAME,						//	ウィンドウの名前
		WS_OVERLAPPEDWINDOW,				//	ウィンドウスタイル
		CW_USEDEFAULT,						//	ウィンドウのｘ座標
		CW_USEDEFAULT,						//	ウィンドウのｙ座標
		(rect.right - rect.left),			//	ウィンドウの幅
		(rect.bottom - rect.top),			//	ウィンドウの高さ
		NULL,								//	親ウィンドウのハンドル
		NULL,								//	メニューウィンドウのハンドル（子ウィンドウ）
		hInstance,							//	インスタンスハンドル
		NULL);								//	ウィンドウ作成データ

	//===============
	//	初期化処理
	//===============
	if (FAILED(Init(hInstance, hWnd, TRUE)))
	{
		return -1;
	}

	//================
	//	分解能を設定
	//================
	timeBeginPeriod(1);
	dwCurrentTime = 0;					//	初期化
	dwExeclastTime = timeGetTime();		//	現在時刻を取得(保存)

	//===================
	//	ウィンドウ表示
	//===================
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	//==============
	//	FPSの処理
	//==============
	DWORD dwFrameCount;		// フレームカウント
	DWORD dwFPSLastTime;	// 最後にFPSを計測した時刻

	dwFrameCount = 0;
	dwFPSLastTime = timeGetTime();

	//====================
	//	メッセージループ
	//====================
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{//	windowの処理
			if (msg.message == WM_QUIT)
			{//	WM_QUITメッセージを受けっとったらループを抜ける
				break;
			}
			else
			{
				//====================
				//	メッセージ設定
				//====================
				TranslateMessage(&msg);		//	仮想キーメッセージを文字に変換
				DispatchMessage(&msg);		//	ウィンドウプロシージャへ送出
			}
		}
		else
		{
			//===================
			//	DirectXの処理
			//===================
			dwCurrentTime = timeGetTime();

			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{
				//===============
				//	0.5秒経過
				//	FPSを計測
				//===============
				g_nCntFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);

				dwFPSLastTime = dwCurrentTime;		//	計測した時刻を保存
				dwFrameCount = 0;					//	フレームカウントをクリア
			}

			if ((dwCurrentTime - dwExeclastTime) >= (1000 / 60))		//	60を変えればfps上がる
			{
				//==================
				//	60分の1秒経過
				//==================
				dwExeclastTime = dwCurrentTime;	//	処理開始の時刻[現在時刻]を保存

				//=============
				//	更新処理
				//=============
				Update();

				//=============
				//	描画処理
				//=============

				Draw();

				//===========================
				//	フレームカウント加算
				//===========================
				dwFrameCount++;

			}
		}
	}

	//============
	//	終了処理
	//============
	Uninit();

	//================
	//	分解能を戻す
	//================
	timeEndPeriod(1);

	//===========================
	//	ウィンドウクラスの解除
	//===========================
	UnregisterClass(CLASS_NAME, wcex.hInstance);
	return(int)msg.wParam;
}

//************************************************
// ウィンドウをフルスクリーンに変える処理
//************************************************
void ToggleFullscreen(HWND hWnd)
{
	//==================================
	//	現在のウィンドウスタイルを取得
	//==================================
	DWORD dwStyle = GetWindowLong(hWnd, GWL_STYLE);

	if (g_isFullscreen)
	{
		//=============================
		//	ウィンドウモードに切り替え
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
		//	フルスクリーンモードに切り替え
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
//ウィンドウプロシージャ
//----------------------
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	const RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };	//	ウィンドウの領域

	switch (uMsg)
	{
	case WM_DESTROY:				//	ウィンドウズを破棄する
		//WM_QUITメッセージ
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:				//	[ESC]キーが押された
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
		int zDelta = GET_WHEEL_DELTA_WPARAM(wParam);
		MouseWheel(zDelta);
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//----------------------------
//	初期化処理
// ----------------------------
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;
	D3DPRESENT_PARAMETERS d3dpp;

	//=====================
	//	オブジェクト生成
	//=====================
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}

	//=======================
	//	でぃすぷれいの取得
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

	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&g_pD3DDeviec)))
	{
		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_REF,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&g_pD3DDeviec)))

		{
			return E_FAIL;
		}
	}

	//===========================
	//	レンダーステートの設定
	//===========================
	g_pD3DDeviec->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	g_pD3DDeviec->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pD3DDeviec->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDeviec->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//=========================
	//	サンプラーステート
	//=========================
	g_pD3DDeviec->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	g_pD3DDeviec->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	g_pD3DDeviec->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	g_pD3DDeviec->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	//=====================================
	//	テクスチャステージステートの設定
	//=====================================
	g_pD3DDeviec->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDeviec->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDeviec->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);


	//================================
	//	デバック表示用フォントの生成
	//================================
	D3DXCreateFont(g_pD3DDeviec, 18, 0, 0, 0,
		FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH,
		"Terminal", &g_pFont);

	//	キーボードの初期化
	if (FAILED(InitKeyboard(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	//	ジョイパッドの初期化
	if (FAILED(InitJoypad()))
	{
		return E_FAIL;
	}

	//	
	if (FAILED(InitMausu(hInstance,hWnd)))
	{
		return E_FAIL;
	}

	InitSound(hWnd);

	SetMode(g_mode);

	InitFade(g_mode);

	return S_OK;
}
//==================
//	終了処理
//==================
void Uninit(void)
{
	//　音の終了
	UninitSound();

	//	キーボード終了
	UninitKeyboard();

	//	ジョイパッド終了
	UninitJoypad();

	//	まうす
	UninitMausu();
	
	//	タイトル終了
	UninitTitle3D();

	//	チュートリアル
	UinitTutrial();

	//	ゲームの終了
	UinitGame();

	//	リザルト
	UinitResult();

	//	フェード
	UninitFade();

	//	ランキング
	UninitRanking();

	// デバック表示用フォントの破棄
	if (g_pFont != NULL)
	{
		g_pFont->Release();
		g_pFont = NULL;
	}

	//	デバイスの破棄
	if (g_pD3DDeviec != NULL)
	{
		g_pD3DDeviec->Release();
		g_pD3DDeviec = NULL;
	}

	//	なんかの破棄
	if (g_pD3D != NULL)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}
}

//=======================
//	更新処理
//=======================
void Update(void)
{
	UpdateKeyboard();	//	キーボード
	UpdateJoypad();		//	ジョイパッド
	UpdateMausu();		//まうす

	switch (g_mode)
	{
	case MODE_TITLE:
		UpdateTitle3D();			//	タイトル画面
		break;

	case MODE_TUTRIAL:
		UpdateTutrial();		//	チュートリアル
		break;

	case MODE_GAME:
		UpdateGame();			//	ゲーム画面
		break;

	case MODE_RESULT:
		UpdateResult();			//	リザルト
		break;

	case MODE_RANKING:
		UpdateRanking();		//	ランキング
		break;
	}

	//	フェード更新
	UpdateFade();

}
//================
//	描画処理
//================
void Draw(void)
{
	Camera* pCamera = GetCamera();

	//	デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int n = 0; n < MAX_CAMERA; n++, pCamera++)
	{
		//	ビューポートの設定
		pDevice->SetViewport(&pCamera->viewport);

		//	画面クリア
		g_pD3DDeviec->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(255, 255, 255, 255), 1.0f, 0);

		//	描画開始
		if (SUCCEEDED(g_pD3DDeviec->BeginScene()))
		{
			//カメラを設定する
			SetCamera(n);

			switch (g_mode)
			{
			case MODE_TITLE:
				DrawTitle3D();		//	タイトル
				break;

			case MODE_TUTRIAL:
				DrawTutrial();		//	チュートリアル
				break;

			case MODE_GAME:
				DrawGame();			//	ゲーム
				break;

			case MODE_RESULT:
				DrawResult();		//	リザルト
				break;

			case MODE_RANKING:
				DrawRanking();		//	ランキング
				break;
			}

			//	フェード描画
			DrawFade();

#ifdef _DEBUG
			//	FPSの表示
			DrawFPS();

			//カメラ注視点の描画処理
			DrawCameraPosR();

			//カメラ視点の描画処理
			DrawCameraPosV();

			//カメラ向きの描画処理
			DrawCameraRot();

			//鍵を持っているかのデバッグ表示処理
			DrawDebugKey();

#endif // DEBUG

			//	終了
			g_pD3DDeviec->EndScene();
		}
	}

	//入れ替え
	g_pD3DDeviec->Present(NULL, NULL, NULL, NULL);
	
}

//	モードの設定
void SetMode(MODE mode)
{
	//現在のモードの終了処理
	switch (g_mode)
	{
	case MODE_TITLE:
		UninitTitle3D();		//	タイトル
		break;

	case MODE_TUTRIAL:
		UinitTutrial();		//	チュートリアル	
		break;

	case MODE_GAME:
		UinitGame();		//	ゲーム
		break;

	case MODE_RESULT:
		UinitResult();		//	リザルト
		break;

	case MODE_RANKING:
		UninitRanking();	//	ランキング
		break;
	}

	switch (mode)
	{
	case MODE_TITLE:
		InitTitle3D();		//	タイトル
		break;

	case MODE_TUTRIAL:		
		InitTutrial();		//	チュートリアル
		break;

	case MODE_GAME:
		InitGame();			//	ゲーム
		break;

	case MODE_RESULT:
		InitResult();		//	リザルト
		break;

	case MODE_RANKING:
		InitRanking();		//	ランキング
		break;
	}

	g_mode = mode;
}
//=================
//	モードの取得
//================
MODE GetMode(void)
{
	return g_mode;
}

//=====================
//	FPS表示
//=====================
void DrawFPS(void)
{
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];

	//==================
	//	文字列に代入
	//==================
	wsprintf(&aStr[0], "FPS:%d\n", g_nCntFPS);

	//===================
	//	テキスト表示
	//===================
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 0, 0, 255));
}

//================================
// カメラの位置座標の描画処理
//================================
void DrawCameraPosR(void)
{
	RECT rect = { 0,45,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];
	Camera* pCamera = GetCamera();
	sprintf(&aStr[0], "カメラ注視点座標　X:%.2f　Y:%.2f  Z:%.2f\n", pCamera->posR.x, pCamera->posR.y, pCamera->posR.z);
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(0, 0, 0, 255));
}

//================================
// カメラの位置座標の描画処理
//================================
void DrawCameraPosV(void)
{
	RECT rect = { 0,60,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];
	Camera* pCamera = GetCamera();
	sprintf(&aStr[0], "カメラ視点座標　X:%.2f　Y:%.2f  Z:%.2f\n", pCamera->posV.x, pCamera->posV.y, pCamera->posV.z);
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(0, 0, 0, 255));
}

//================================
// カメラの向きの描画処理
//================================
void DrawCameraRot(void)
{
	RECT rect = { 0,75,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];
	Camera* pCamera = GetCamera();
	sprintf(&aStr[0], "カメラの向き　X:%.2f　Y:%.2f  Z:%.2f\n", pCamera->rot.x, pCamera->rot.y, pCamera->rot.z);
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(0, 0, 0, 255));
}
void DrawDebugKey(void)
{
	ITEM* pITEM = Getitem();

	for (int count = 0; count < MAX_ITEM; count++, pITEM++)
	{
		RECT rect = { 0,90 + count * 15,SCREEN_WIDTH,SCREEN_HEIGHT };
		char aStr[MAX_ITEM][256];

		sprintf(&aStr[count][0], "アイテム%d : %d \n", count + 1,pITEM->bHave);

		g_pFont->DrawText(NULL, &aStr[count][0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(0, 0, 0, 255));
	}
}