//========================================================
//
//			カメラ	camera.cpp
//				ryuusei hirata
// 
//========================================================
#include "main.h"
#include "camera.h"
#include "input.h"
#include "player.h"

//	グローバル
Camera g_camera[MAX_CAMERA] = {};	//カメラ情報

//====================
//	初期化処理
//====================
void InitCamera(void)
{
	//	視点・注視点・上方向を設定する
	for (int count = 0; count < MAX_CAMERA; count++)
	{
		g_camera[count].posV = D3DXVECTOR3(0.0f, 120.0f, -300.0f);
		g_camera[count].posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_camera[count].posVDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_camera[count].posRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_camera[count].vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		g_camera[count].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_camera[count].fDistance = sqrtf((g_camera[count].posV.x - g_camera[count].posR.x) 
			* (g_camera[count].posV.x - g_camera[count].posR.x) + (g_camera[count].posV.y - g_camera[count].posR.y) 
			* (g_camera[count].posV.y - g_camera[count].posR.y) + (g_camera[count].posV.z - g_camera[count].posR.z) 
			* (g_camera[count].posV.z - g_camera[count].posR.z));
		g_camera[count].deltaX = 0.0f;
		g_camera[count].deltaY = 0.0f;
	}

	//	ビューポート構成の保存	左
	g_camera[0].viewport.X = 0.0f;
	g_camera[0].viewport.Y = 0.0f;
	g_camera[0].viewport.Width = 640.0f;
	g_camera[0].viewport.Height = 720.0f;
	g_camera[0].viewport.MinZ = 0.0f;
	g_camera[0].viewport.MaxZ = 1.0f;

	//	ビューポート構成の保存	右
	g_camera[1].viewport.X = 640.0f;
	g_camera[1].viewport.Y = 0.0f;
	g_camera[1].viewport.Width = 640.0f;
	g_camera[1].viewport.Height = 720.0f;
	g_camera[1].viewport.MinZ = 0.0f;
	g_camera[1].viewport.MaxZ = 1.0f;

	//	ビューポート構成の保存	真ん中
	g_camera[2].viewport.X = 450.0f;
	g_camera[2].viewport.Y = 420.0f;
	g_camera[2].viewport.Width = 300.0f;
	g_camera[2].viewport.Height = 200.0f;
	g_camera[2].viewport.MinZ = 0.0f;
	g_camera[2].viewport.MaxZ = 1.0f;

}

void UninitCamera(void)
{

}

void UpdateCamera(void)
{
	Player* pPlayer = GetPlayer();

	D3DXVECTOR2 a = GetMouseVelocity();
	D3DXVECTOR2 b = GetMouseVelocityOld();

	for (int nCntCamera = 0; nCntCamera < MAX_CAMERA; nCntCamera++)
	{
		GetCursorPos(&g_camera[nCntCamera].cursorPos);

		g_camera[nCntCamera].prevCursorPos = { (long)(SCREEN_WIDTH / 1.5), (long)(SCREEN_HEIGHT / 1.5) };

		g_camera[nCntCamera].deltaX = g_camera[nCntCamera].cursorPos.x - g_camera[nCntCamera].prevCursorPos.x;
		g_camera[nCntCamera].deltaY = g_camera[nCntCamera].cursorPos.y - g_camera[nCntCamera].prevCursorPos.y;

		const float mouseSensitivity = 0.01f;

		g_camera[nCntCamera].deltaX *= a.x - b.x;
		g_camera[nCntCamera].deltaY *= a.y - b.y;

		g_camera[nCntCamera].rot.x += g_camera[nCntCamera].deltaY;
		g_camera[nCntCamera].rot.y += g_camera[nCntCamera].deltaX;

		if (g_camera[nCntCamera].rot.y <= -D3DX_PI)
		{
			g_camera[nCntCamera].rot.y += D3DX_PI * 2.0f;
		}
		else if (g_camera[nCntCamera].rot.y >= D3DX_PI)
		{
			g_camera[nCntCamera].rot.y += -D3DX_PI * 2.0f;
		}

		SetCursorPos(SCREEN_WIDTH / 1.5, SCREEN_HEIGHT / 1.5);

		g_camera[nCntCamera].prevCursorPos.x = SCREEN_WIDTH / 1.5;
		g_camera[nCntCamera].prevCursorPos.y = SCREEN_HEIGHT / 1.5;

		g_camera[nCntCamera].posR.x = pPlayer->pos.x - sinf(g_camera[nCntCamera].rot.y) * cosf(g_camera[nCntCamera].rot.x);
		g_camera[nCntCamera].posR.y = pPlayer->pos.y - sinf(g_camera[nCntCamera].rot.x);
		g_camera[nCntCamera].posR.z = pPlayer->pos.z - cosf(g_camera[nCntCamera].rot.y) * sinf(g_camera[nCntCamera].rot.x);

		//g_camera[nCntCamera].posV.x = pPlayer->pos.x - sinf(g_camera[nCntCamera].rot.x) * 15.0f + cosf(g_camera[nCntCamera].rot.y);
		//g_camera[nCntCamera].posV.y = pPlayer->pos.y - cosf(g_camera[nCntCamera].rot.x) + 30.0f;
		//g_camera[nCntCamera].posV.z = pPlayer->pos.z - cosf(g_camera[nCntCamera].rot.x) * 15.0f + sinf(g_camera[nCntCamera].rot.y);
	}
}

void SetCamera(void)
{
	//	デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int count = 0; count < MAX_CAMERA; count++)
	{
		//	ビューマトリックスの初期化
		D3DXMatrixIdentity(&g_camera[count].mtxView);

		//	ビューマトリックスの作成
		D3DXMatrixLookAtLH(&g_camera[count].mtxView,
			&g_camera[count].posV,
			&g_camera[count].posR,
			&g_camera[count].vecU);

		//	ビューマトリックスの設定
		pDevice->SetTransform(D3DTS_VIEW, &g_camera[count].mtxView);

		//	プロジェクションマトリックスの初期化
		D3DXMatrixIdentity(&g_camera[count].mtxProjection);

		//	プロジェクションマトリックスの初期化
		D3DXMatrixPerspectiveFovLH(&g_camera[count].mtxProjection,
			D3DXToRadian(70.0f),								//	視野角
			640.0f / 720.0f,									//	アスペクト比
			10.0f,												//	どこからどこまで
			1000.0f);											//	カメラで表示するか

		//	プロジェクトマトリックスの設定
		pDevice->SetTransform(D3DTS_PROJECTION, &g_camera[count].mtxProjection);
	}
}

Camera* GetCamera(void)
{
	return &g_camera[0];
}