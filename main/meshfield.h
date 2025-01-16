#pragma once
#ifndef _MESHFIELD_H_
#define _MESHFIELD_H_

#include "main.h"

#define MESHFIELD_X (200)		//	X軸
#define MESHFIELD_Z (200)		//	Z軸
#define MESHFIELD_T ((MESHFIELD_X + 1) * (MESHFIELD_Z + 1))		//	頂点数
#define MESHFIELD_P ((MESHFIELD_X * MESHFIELD_Z * 2 + (MESHFIELD_Z - 1) * 4))		//	ポリゴン数
#define MESHFIELD_I ((MESHFIELD_X + 1) * 2 * MESHFIELD_Z + (MESHFIELD_Z - 1) * 2)	//	インデックス数

typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXMATRIX mtxWorld;
}MESHFIELD;

//	プロトタイプ宣言
void InitMeshfield(void);
void UninitMeshfield(void);
void UpdataMeshfield(void);
void DrawMeshfield(void);

#endif // !_MESHFIELD_H_
