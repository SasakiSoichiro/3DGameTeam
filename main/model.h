#pragma once
#ifndef _MODEL_H_
#define _MODEL_H_

#include "main.h"

typedef struct
{
	LPD3DXMESH pMesh;
	LPD3DXBUFFER pBuffMat;
	DWORD dwNumMat;
	int nIdxModelParent;
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXMATRIX mtxWorld;
	D3DXVECTOR3 vtxMax;
	D3DXVECTOR3 vtxMin;
	LPDIRECT3DTEXTURE9 apTexture[128];	//	テクスチャのポインター
}Model;

//	プロトタイプ
void InitModel(void);
void UninitModel(void);
void UpdateModel(void);
void DrawModel(void);

#endif // !_MODEL_H_
