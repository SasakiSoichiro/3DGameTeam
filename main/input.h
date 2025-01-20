#pragma once
#ifndef _INPUT_H_
#define _INPUT_H_

#include "main.h"

//================
//	キーの種類
//================
typedef enum
{
	JOYKEY_UP = 0,	//	十字キー(↑)
	JOYKEY_DOWN,	//	十字キー(↓)
	JOYKEY_LEFT,	//	十字キー(←)
	JOYKEY_RIGHT,	//	十字キー(→)
	JOYKEY_START,	//	スタート
	JOYKEY_BACK,	//	バック
	JOYKEY_LPUSH,	//	スティック押し込み	左
	JOYKEY_RPUSH,	//	スティック押し込み	右
	JOYKEY_LB,		//	L1
	JOYKEY_RB,		//	R1
	JOYKEY_LT,		//	L2
	JOYKEY_RT,		//	R2
	JOYKEY_A,		//	Aボタン
	JOYKEY_B,		//	Bボタン
	JOYKEY_X,		//	Xボタン
	JOYKEY_Y,		//	Yボタン
	JOYKEY_MAX
}JOYKEY;

typedef enum
{
	MOUSE_L = 0,
	MOUSE_R,
	MOUSE_H,
	MOUSE_MAX
}MouseButton;

//==================
//プロトタイプ
//==================
//キーボード
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd);
void UninitKeyboard(void);
void UpdateKeyboard(void);
bool GetKeyboardPress(int nKey);
bool KeybordTrigger(int nKey);
bool KeybordRelease(int nKey);
bool KeybordRepeat(int nKey);

//ジョイパッド
HRESULT InitJoypad(void);
void UninitJoypad(void);
void UpdateJoypad(void);
bool GetJoypadPress(JOYKEY key);
bool JoyPadTrigger(JOYKEY key);
bool GetJoyStick(void);
XINPUT_STATE* GetJoyStickAngle(void);

//	マウス
HRESULT InitMausu(HINSTANCE hInstance, HWND hWnd);
void UninitMausu(void);
void UpdateMausu(void);
bool OnMouseDown(MouseButton button_type);
bool OnMouseUp(MouseButton button_type);
D3DXVECTOR2 GetMouseVelocity();
D3DXVECTOR2 GetMouseVelocityOld();

#endif