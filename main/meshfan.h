//=============================================================================
//
//	メッシュファン処理 [meshfan.h]
// Author : 佐々木奏一郎
//
//=============================================================================
#ifndef _MESHFAN_H_//このマクロ定義がされていなかったら
#define _MESHFAN_H_//2銃インクルード防止のマクロ定義
#include "main.h"

//マクロ定義
#define CORNERCNT (5)

typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXVECTOR3 VtxPos[CORNERCNT+1];
	D3DXMATRIX mtxWorld;
}MeshFan;
//プロトタイプ宣言
void InitMeshFan(void);
void UninitMeshFan(void);
void UpdateMeshFan(void);
void DrawMeshFan(void);
#endif