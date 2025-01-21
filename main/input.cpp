//================================================
//
// 入力処理　[input.cpp]
// Athor : HRT ryuusei
// 
//================================================

#include "input.h"

//================================================
// マクロ
//================================================
#define NUM_KEY_MAX (256)				//キーの最大数
#define NUM_MAUSE_MAX (3)				//マウスの最大数
#define MAX_PAD (2)		//	コントローラー

//================================================
// グローバル
//================================================
XINPUT_STATE g_joyKeyState;					//ジョイパッドのプレス情報
XINPUT_STATE g_OldKeyState;
XINPUT_STATE g_joyKeyStateTrigger;
LPDIRECTINPUT8 g_pInput = NULL;				//DeirectInputへのポインタ
LPDIRECTINPUTDEVICE8 g_pDevKeyboard = NULL;	//入力デバイスへのポインタ
LPDIRECTINPUT8 g_pInputMause = NULL;				//DeirectInputへのポインタ
LPDIRECTINPUTDEVICE8 g_pDevMause = NULL;	//入力デバイスへのポインタ
BYTE g_aKeyState[NUM_KEY_MAX];
BYTE g_aOldState[NUM_KEY_MAX];
BYTE g_aMauseState[NUM_MAUSE_MAX];
BYTE g_aOldMauseState[NUM_MAUSE_MAX];
DIMOUSESTATE g_CurrentMouseState;		//!< マウスの現在の入力情報
DIMOUSESTATE g_PrevMouseState;			//!< マウスの一フレーム前の入力情報
DIMOUSESTATE g_Oldpos;		//!< マウスの現在の入力情報

//	初期化処理
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd)
{
	//	Directinputオブジェクトの生成
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&g_pInput, NULL)))
	{
		return E_FAIL;
	}

	//	入力デバイスの生成
	if (FAILED(g_pInput->CreateDevice(GUID_SysKeyboard, &g_pDevKeyboard, NULL)))
	{
		return E_FAIL;
	}

	//	データフォーマットの設定
	if (FAILED(g_pDevKeyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	//	協調モード
	if (FAILED(g_pDevKeyboard->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE)))
	{
		return E_FAIL;
	}

	//	キーボードへのアクセス剣を獲得
	g_pDevKeyboard->Acquire();

	return S_OK;
}
//	終了処理
void UninitKeyboard(void)
{
	//	入力デバイスの破棄
	if (g_pDevKeyboard != NULL)
	{
		g_pDevKeyboard->Unacquire();		//キーボードへのアクセス権を破棄
		g_pDevKeyboard->Release();
		g_pDevKeyboard = NULL;
	}

	//	DirectInputオブジェクトの破棄
	if (g_pInput != NULL)
	{
		g_pInput->Release();
		g_pInput = NULL;
	}
}
//	更新処理
void UpdateKeyboard(void)
{
	BYTE aKeyState[NUM_KEY_MAX];	//	キーボードの入力情報
	int nCntKey;

	for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
	{
		g_aOldState[nCntKey] = g_aKeyState[nCntKey];		//	キーボードプレス情報を保存
	}

	// 入力デバイスからデータを取得
	if (SUCCEEDED(g_pDevKeyboard->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			g_aKeyState[nCntKey] = aKeyState[nCntKey];		//	キーボードプレス情報を保存
		}
	}
	else
	{
		g_pDevKeyboard->Acquire();
	}
}

bool GetKeyboardPress(int nKey)
{// 押されてるキー
	return (g_aKeyState[nKey] & 0x80) ? true : false;
}
bool KeybordTrigger(int nKey)
{// 一歩だけ
	bool Trigger = false;
	if (g_aKeyState[nKey] & 0x80 && !(g_aOldState[nKey] & 0x80))
	{
		Trigger = true;
	}
	return Trigger;
}
bool KeybordRelease(int nKey)
{// 長押し
	bool Trigger = false;
	if (g_aOldState[nKey] & 0x80 && !(g_aKeyState[nKey] & 0x80))
	{
		Trigger = true;
	}
	return Trigger;
}
bool KeybordRepeat(int nKey)
{// 押されてる間
	bool Trigger = false;
	if (g_aOldState[nKey] & 0x80 && (g_aKeyState[nKey] & 0x80))
	{
		Trigger = true;
	}
	return Trigger;
}

//================================================================
// ジョイパッドの処理
//================================================================
//===================
// 初期化処理
//===================
HRESULT InitJoypad(void)
{
	//メモリのクリア
	memset(&g_joyKeyState, 0, sizeof(XINPUT_STATE));

	//xinputのステートの設定(有効にする
	XInputEnable(true);

	return S_OK;
}
//===================
// 終了処理
//===================
void UninitJoypad(void)
{
	//	xinputのステートの設定(無効にする
	XInputEnable(false);
}
//===================
// 更新処理
//===================
void UpdateJoypad(void)
{
	XINPUT_STATE joyKeyState;		//	入力情報

	g_OldKeyState = g_joyKeyState;		//	キーボードプレス情報を保存

	//	ジョイパッドの状態を取得
	if (XInputGetState(0, &joyKeyState) == ERROR_SUCCESS)
	{
		WORD Button = joyKeyState.Gamepad.wButtons;
		WORD OldButton = g_joyKeyState.Gamepad.wButtons;

		g_joyKeyStateTrigger.Gamepad.wButtons = Button & ~OldButton;

		g_joyKeyState = joyKeyState;		//	ジョイパッドのプレス情報を保存
	}
}
//===================
// プレス情報を取得
//===================
bool GetJoypadPress(JOYKEY key)
{
	return (g_joyKeyState.Gamepad.wButtons & (0x01 << key)) ? true : false;
}
//===================
// トリガー情報を取得
//===================
bool JoyPadTrigger(JOYKEY key)
{
	return (g_joyKeyStateTrigger.Gamepad.wButtons & (0x01 << key)) ? true : false;
}
//===========================
//
//	スティックそうさ
//
//===========================
bool GetJoyStick(void)
{
	bool joykey = false;

	if (g_joyKeyState.Gamepad.sThumbLX >= 100 ||
		g_joyKeyState.Gamepad.sThumbLX <= -100 ||
		g_joyKeyState.Gamepad.sThumbLY >= 100 ||
		g_joyKeyState.Gamepad.sThumbLY <= -100)
	{
		joykey = true;
	}

	return joykey;
}
//==========================
//	スティックの情報取得
//===========================
XINPUT_STATE* GetJoyStickAngle(void)
{
	return &g_joyKeyState;
}

//====================================
// 
//		マウス操作
// 
//====================================
HRESULT InitMausu(HINSTANCE hInstance, HWND hWnd)
{
	//	Directinputオブジェクトの生成
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&g_pInputMause, NULL)))
	{
		return E_FAIL;
	}

	//	入力デバイスの生成
	if (FAILED(g_pInput->CreateDevice(GUID_SysMouse, &g_pDevMause, NULL)))
	{
		return E_FAIL;
	}

	//	データフォーマットの設定
	if (FAILED(g_pDevMause->SetDataFormat(&c_dfDIMouse)))
	{
		return E_FAIL;
	}

	//	協調モード
	if (FAILED(g_pDevMause->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE)))
	{
		return E_FAIL;
	}

	//	キーボードへのアクセス剣を獲得
	g_pDevMause->Acquire();

	return S_OK;

}

void UninitMausu(void)
{
	if (g_pDevMause != NULL)
	{
		g_pDevMause->Unacquire();		//キーボードへのアクセス権を破棄
		g_pDevMause->Release();
		g_pDevMause = NULL;
	}

	//	DirectInputオブジェクトの破棄
	if (g_pInputMause != NULL)
	{
		g_pInputMause->Release();
		g_pInputMause = NULL;
	}
}

void UpdateMausu(void)
{
	g_Oldpos = g_CurrentMouseState;

	// 更新前に最新マウス情報を保存する
	g_PrevMouseState = g_CurrentMouseState;

	// 最新のマウスの状態を更新
	HRESULT	hr1 = g_pDevMause->GetDeviceState(sizeof(DIMOUSESTATE), &g_CurrentMouseState);

	if (FAILED(hr1))
	{
		g_pDevMause->Acquire();
		hr1 = g_pDevMause->GetDeviceState(sizeof(DIMOUSESTATE), &g_CurrentMouseState);
	}

	POINT p;
	GetCursorPos(&p);

	// スクリーン座標をクライアント座標に変換する
	ScreenToClient(FindWindowA(CLASS_NAME, nullptr), &p);

	g_CurrentMouseState.lX = p.x;
	g_CurrentMouseState.lY = p.y;

}

bool OnMouseDown(MouseButton button_type)
{
	if (!(g_PrevMouseState.rgbButtons[button_type] & (0x80)) &&
		g_CurrentMouseState.rgbButtons[button_type] & (0x80))
	{
		return true;
	}

	return false;
}

bool OnMouseUp(MouseButton button_type)
{
	if (g_PrevMouseState.rgbButtons[button_type] & 0x80 &&
		!(g_CurrentMouseState.rgbButtons[button_type] & 0x80))
	{
		return true;
	}

	return false;
}

D3DXVECTOR2 GetMouseVelocity()
{
	return D3DXVECTOR2((float)g_CurrentMouseState.lX, (float)g_CurrentMouseState.lY);
}

D3DXVECTOR2 GetMouseVelocityOld()
{
	return D3DXVECTOR2((float)g_Oldpos.lX, (float)g_Oldpos.lY);
}