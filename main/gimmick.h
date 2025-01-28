#pragma once
#ifndef _GIMMICK_H_
#define _GIMMICK_H_


#include "main.h"
#include "player.h"

#define MAX_DOOR (1)	//ドアの最大数

//ブロックの構造体
typedef struct
{
	D3DXVECTOR3 pos;				//位置
	D3DXVECTOR3 rot;				//向き
	D3DXVECTOR3 move;				//移動
	D3DXVECTOR3 size;				//サイズ
	D3DXVECTOR3 vtxMin, vtxMax;	//頂点の最小最大
	D3DXMATRIX mtxWorld;			//マトリックス
	LPD3DXMESH pMesh;
	LPD3DXBUFFER pBuffMat;
	DWORD dwNumMat;
	bool bLanding;
	bool bUse;
	//bool bGoal;
	bool bMove;
}BLOCK;

//プロトタイプ宣言
void InitBlock(void);
void UninitBlock(void);
void UpdateBlock(void);
void DrawBlock(void);
bool CollisionBlock(void);
void SetBlock(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
BLOCK* GetBlock(void);
bool IsGoal();
bool IsBill();

#endif
