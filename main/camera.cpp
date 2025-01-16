//========================================================
//
//			カメラ	camera.cpp
//				ryuusei hirata
//
//========================================================
#include "main.h"
#include "camera.h"
#include "input.h"

//	グローバル
Camera g_camera = {};	//カメラ情報

//====================
//	初期化処理
//====================
void InitCamera(void)
{
	//	視点・注視点・上方向を設定する
	g_camera.posV = D3DXVECTOR3(0.0f, 150.0f, -400.0f);
	g_camera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.posVDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.posRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	g_camera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.fDistance = sqrtf((g_camera.posV.x - g_camera.posR.x) * (g_camera.posV.x - g_camera.posR.x) + (g_camera.posV.y - g_camera.posR.y) * (g_camera.posV.y - g_camera.posR.y) + (g_camera.posV.z - g_camera.posR.z) * (g_camera.posV.z - g_camera.posR.z));
}

void UninitCamera(void)
{

}

void UpdateCamera(void)
{

	//================================
	//		注視点の旋回
	//================================
	if (GetKeyboardPress(DIK_Q) == true)
	{
		//	回転量
		g_camera.rot.y -= 0.05f;

		//	角度の正規化
		if (g_camera.rot.y < -D3DX_PI)
		{
			g_camera.rot.y = g_camera.rot.y - D3DX_PI * 2.0f;
		}

		g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * g_camera.fDistance;
		g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * g_camera.fDistance;
	}
	else if (GetKeyboardPress(DIK_E) == true)
	{
		//	回転量
		g_camera.rot.y += 0.05f;

		//	角度の正規化
		if (g_camera.rot.y > D3DX_PI)
		{
			g_camera.rot.y = g_camera.rot.y + D3DX_PI * 2.0f;
		}

		g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * g_camera.fDistance;
		g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * g_camera.fDistance;
	}

	////================================
	////		視点の旋回
	////================================
	if (GetKeyboardPress(DIK_Z) == true)
	{
		//	回転量
		g_camera.rot.y += 0.05f;

		//	角度の正規化
		if (g_camera.rot.y > D3DX_PI)
		{
			g_camera.rot.y = g_camera.rot.y + D3DX_PI * 2.0f;
		}

		g_camera.posV.x = g_camera.posR.x + sinf(g_camera.rot.y) * g_camera.fDistance;
		g_camera.posV.z = g_camera.posR.z + cosf(g_camera.rot.y) * g_camera.fDistance;
	}

	if (GetKeyboardPress(DIK_C) == true)
	{
		//	回転量
		g_camera.rot.y -= 0.05f;

		//	角度の正規化
		if (g_camera.rot.y < -D3DX_PI)
		{
			g_camera.rot.y = g_camera.rot.y - D3DX_PI * 2.0f;
		}

		g_camera.posV.x = g_camera.posR.x + sinf(g_camera.rot.y) * g_camera.fDistance;
		g_camera.posV.z = g_camera.posR.z + cosf(g_camera.rot.y) * g_camera.fDistance;
	}
}

void SetCamera(void)
{
	//	デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//	ビューマトリックスの初期化
	D3DXMatrixIdentity(&g_camera.mtxView);

	//	ビューマトリックスの作成
	D3DXMatrixLookAtLH(&g_camera.mtxView,
		&g_camera.posV,
		&g_camera.posR,
		&g_camera.vecU);

	//	ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &g_camera.mtxView);

	//	プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&g_camera.mtxProjection);

	//	プロジェクションマトリックスの初期化
	D3DXMatrixPerspectiveFovLH(&g_camera.mtxProjection,
		D3DXToRadian(45.0f),								//	視野角
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,			//	アスペクト比
		10.0f,												//	どこからどこまで
		1000.0f);											//	カメラで表示するか

	//	プロジェクトマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &g_camera.mtxProjection);
}

Camera* GetCamera(void)
{
	return &g_camera;
}