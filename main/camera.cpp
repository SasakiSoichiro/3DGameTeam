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
#include "game.h"

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
		g_camera[count].posV = D3DXVECTOR3(100.0f, 60.0f, 0.0f);
		g_camera[count].posR = D3DXVECTOR3(100.0f, 50.0f, 0.0f);
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
	g_camera[0].viewport.Width = 1280.0f;
	g_camera[0].viewport.Height = 720.0f;
	g_camera[0].viewport.MinZ = 0.0f;
	g_camera[0].viewport.MaxZ = 1.0f;

	////	ビューポート構成の保存	右
	//g_camera[1].viewport.X = 640.0f;
	//g_camera[1].viewport.Y = 0.0f;
	//g_camera[1].viewport.Width = 640.0f;
	//g_camera[1].viewport.Height = 720.0f;
	//g_camera[1].viewport.MinZ = 0.0f;
	//g_camera[1].viewport.MaxZ = 1.0f;

	////	ビューポート構成の保存	真ん中
	//g_camera[2].viewport.X = 450.0f;
	//g_camera[2].viewport.Y = 420.0f;
	//g_camera[2].viewport.Width = 300.0f;
	//g_camera[2].viewport.Height = 200.0f;
	//g_camera[2].viewport.MinZ = 0.0f;
	//g_camera[2].viewport.MaxZ = 1.0f;

}

void UninitCamera(void)
{

}

void UpdateCamera(void)
{
	Player* pPlayer = GetPlayer();
	MODE mode = GetMode();
	XINPUT_STATE* pStick;
	pStick = GetJoyStickAngle();
	D3DXVECTOR2 a = GetMouseVelocity();
	D3DXVECTOR2 b = GetMouseVelocityOld();

	for (int nCnt = 0; nCnt < MAX_CAMERA; nCnt++)
	{
		if (GetEditState() == false&&mode==MODE_GAME)
		{
			static POINT prevCursorPos = { (long)(SCREEN_WIDTH / 1.5), (long)(SCREEN_HEIGHT / 1.5) };

			POINT cursorPos;

			GetCursorPos(&cursorPos);

			float DeltaX = (float)cursorPos.x - prevCursorPos.x;
			float DeltaY = (float)cursorPos.y - prevCursorPos.y;

			const float mouseSensitivity = 0.0009f;

			DeltaX *= mouseSensitivity;
			DeltaY *= mouseSensitivity;

			g_camera[nCnt].rot.x += DeltaY;
			g_camera[nCnt].rot.y += DeltaX;

			//右スティック視点
			if (GetJoyStick() == true)
			{
				if (pStick->Gamepad.sThumbRX > 10922)
				{
					if (pStick->Gamepad.sThumbRY > 10922)
					{
						//上
						g_camera[nCnt].rot.x -= 0.03f;
					}
					else if (pStick->Gamepad.sThumbRY < -10922)
					{
						//下
						g_camera[nCnt].rot.x += 0.03f;
					}

					//右回り
					g_camera[nCnt].rot.y += 0.03f;

				}
				else if (pStick->Gamepad.sThumbRX < -10922)
				{
					if (pStick->Gamepad.sThumbRY > 10922)
					{
						//上
						g_camera[nCnt].rot.x -= 0.03f;
					}
					else if (pStick->Gamepad.sThumbRY < -10922)
					{
						//下
						g_camera[nCnt].rot.x += 0.03f;
					}

					//左回り
					g_camera[nCnt].rot.y -= 0.03f;

				}
				else if (pStick->Gamepad.sThumbRY > 10922)
				{
					if (pStick->Gamepad.sThumbRX > 10922)
					{
						//右回り
						g_camera[nCnt].rot.y += 0.03f;
					}
					else if (pStick->Gamepad.sThumbRX < -10922)
					{
						//左回り
						g_camera[nCnt].rot.y -= 0.03f;
					}

					//上
					g_camera[nCnt].rot.x -= 0.03f;

				}
				else if (pStick->Gamepad.sThumbRY < -10922)
				{
					if (pStick->Gamepad.sThumbRX > 10922)
					{
						//右回り
						g_camera[nCnt].rot.y += 0.03f;
					}
					else if (pStick->Gamepad.sThumbRX < -10922)
					{
						//左回り
						g_camera[nCnt].rot.y -= 0.03f;
					}

					//下
					g_camera[nCnt].rot.x += 0.03f;

				}
			}

			//角度の正規化
			if (g_camera[nCnt].rot.y <= -D3DX_PI)
			{
				g_camera[nCnt].rot.y += D3DX_PI * 2.0f;
			}
			else if (g_camera[nCnt].rot.y >= D3DX_PI)
			{
				g_camera[nCnt].rot.y += -D3DX_PI * 2.0f;
			}

			//if (g_camera[nCnt].rot.x <= -D3DX_PI)
			//{
			//	g_camera[nCnt].rot.x += D3DX_PI * 2.0f;
			//}
			//else if (g_camera[nCnt].rot.x >= D3DX_PI)
			//{
			//	g_camera[nCnt].rot.x += -D3DX_PI * 2.0f;
			//}

			//角度制限
			if (g_camera[nCnt].rot.x > 1.57f)
			{
				g_camera[nCnt].rot.x = 1.57f;
			}
			else if (g_camera[nCnt].rot.x < -1.57f)
			{
				g_camera[nCnt].rot.x = -1.57f;
			}

			SetCursorPos(SCREEN_WIDTH / 1.5, SCREEN_HEIGHT / 1.5);

			prevCursorPos.x = SCREEN_WIDTH / 1.5;
			prevCursorPos.y = SCREEN_HEIGHT / 1.5;

			g_camera[nCnt].posV = pPlayer->pos;
			g_camera[nCnt].posV.y += 20.0f;

			g_camera[nCnt].posR.x = g_camera[nCnt].posV.x - sinf(g_camera[nCnt].rot.y) * cosf(g_camera[nCnt].rot.x);
			g_camera[nCnt].posR.y = g_camera[nCnt].posV.y - sinf(g_camera[nCnt].rot.x);
			g_camera[nCnt].posR.z = g_camera[nCnt].posV.z - cosf(g_camera[nCnt].rot.y) * cosf(g_camera[nCnt].rot.x);

		}
		else if (GetEditState() == true)
		{
			static POINT prevCursorPos = { (long)(SCREEN_WIDTH / 1.5), (long)(SCREEN_HEIGHT / 1.5) };

			POINT cursorPos;

			GetCursorPos(&cursorPos);

			float DeltaX = (float)cursorPos.x - prevCursorPos.x;
			float DeltaY = (float)cursorPos.y - prevCursorPos.y;

			const float mouseSensitivity = 0.0009f;

			DeltaX *= mouseSensitivity;
			DeltaY *= mouseSensitivity;

			g_camera[nCnt].rot.x += DeltaY;
			g_camera[nCnt].rot.y += DeltaX;

			//角度の正規化
			if (g_camera[nCnt].rot.y <= -D3DX_PI)
			{
				g_camera[nCnt].rot.y += D3DX_PI * 2.0f;
			}
			else if (g_camera[nCnt].rot.y >= D3DX_PI)
			{
				g_camera[nCnt].rot.y += -D3DX_PI * 2.0f;
			}
			SetCursorPos(SCREEN_WIDTH / 1.5, SCREEN_HEIGHT / 1.5);

			prevCursorPos.x = SCREEN_WIDTH / 1.5;
			prevCursorPos.y = SCREEN_HEIGHT / 1.5;

			g_camera[nCnt].posR.x = g_camera[nCnt].posV.x+ sinf(g_camera[nCnt].rot.x) * sinf(g_camera[nCnt].rot.y)* g_camera[nCnt].fDistance;
			g_camera[nCnt].posR.y = g_camera[nCnt].posV.y+ cosf(g_camera[nCnt].rot.x) * g_camera[nCnt].fDistance;
			g_camera[nCnt].posR.z = g_camera[nCnt].posV.z+ sinf(g_camera[nCnt].rot.x) * cosf(g_camera[nCnt].rot.y) * g_camera[nCnt].fDistance;

		}
	}
	
}

void SetCamera(int nIdx)
{
	//	デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();


		//	ビューマトリックスの初期化
		D3DXMatrixIdentity(&g_camera[nIdx].mtxView);

		//	ビューマトリックスの作成
		D3DXMatrixLookAtLH(&g_camera[nIdx].mtxView,
			&g_camera[nIdx].posV,
			&g_camera[nIdx].posR,
			&g_camera[nIdx].vecU);

		//	ビューマトリックスの設定
		pDevice->SetTransform(D3DTS_VIEW, &g_camera[nIdx].mtxView);

		//	プロジェクションマトリックスの初期化
		D3DXMatrixIdentity(&g_camera[nIdx].mtxProjection);

		//	プロジェクションマトリックスの初期化
		D3DXMatrixPerspectiveFovLH(&g_camera[nIdx].mtxProjection,
			D3DXToRadian(40.0f),								//	視野角
			SCREEN_WIDTH / SCREEN_HEIGHT,									//	アスペクト比
			10.0f,												//	どこからどこまで
			1000.0f);											//	カメラで表示するか

		//	プロジェクトマトリックスの設定
		pDevice->SetTransform(D3DTS_PROJECTION, &g_camera[nIdx].mtxProjection);
}
void MouseWheel(int zDelta)
{
	if (zDelta > 0)
	{
		g_camera[0].fDistance -= 15.0f;

	}
	else if (zDelta < 0)
	{
		g_camera[0].fDistance += 15.0f;

	}
	//カメラの視点の情報
	g_camera[0].posV.x = g_camera[0].posR.x - sinf(g_camera[0].rot.x) * sinf(g_camera[0].rot.y) * g_camera[0].fDistance;
	g_camera[0].posV.y = g_camera[0].posR.y - cosf(g_camera[0].rot.x) * g_camera[0].fDistance;
	g_camera[0].posV.z = g_camera[0].posR.z - sinf(g_camera[0].rot.x) * cosf(g_camera[0].rot.y) * g_camera[0].fDistance;

}


Camera* GetCamera(void)
{
	return &g_camera[0];
}