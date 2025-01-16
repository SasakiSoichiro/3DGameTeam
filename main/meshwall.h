#pragma once
#ifndef _MESHWALL_H_

#include "main.h"

//	マクロ宣言
#define SUIHEI (8)
#define SUITYOKU (1)
#define MESHWALL_T ((SUIHEI + 1) * (SUITYOKU + 1))		//	頂点数
#define MESHWALL_P ((SUIHEI * SUITYOKU * 2 + (SUITYOKU - 1) * 4))		//	ポリゴン数
#define MESHWALL_I ((SUIHEI + 1) * 2 * SUITYOKU + (SUITYOKU - 1) * 2)	//	インデックス数

typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXMATRIX mtxWorld;
}MESHWALL;

//	プロトタイプ宣言
void InitMeshWall(void);
void UninitMeshWall(void);
void UpdataMeshWall(void);
void DrawMeshWall(void);

#endif // !_MESHWALL_H_
