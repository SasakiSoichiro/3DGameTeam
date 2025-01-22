#pragma once
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"
#define MAX_CAMERA (2)

//構造体
typedef struct
{
	D3DXVECTOR3 posV;			//	視点
	D3DXVECTOR3 posR;			//	注視点
	D3DXVECTOR3 vecU;			//	上方向ベクトル
	D3DXMATRIX mtxProjection;	//	プロジェクションマトリックス
	D3DXMATRIX mtxView;			//	ビューマトリックス
	D3DXVECTOR3 rot;			//	向き
	float fDistance;			//	視点から注視点の距離
	D3DXVECTOR3 posRDest;
	D3DXVECTOR3 posVDest;
	D3DVIEWPORT9 viewport;
	float deltaX;
	float deltaY;
	POINT cursorPos;
	POINT prevCursorPos;
}Camera;

//	ぷろとたいぷ
void InitCamera(void);
void UninitCamera(void);
void UpdateCamera(void);
void SetCamera(int nIdx);
Camera* GetCamera(void);

#endif // !_CAMERA_H_
