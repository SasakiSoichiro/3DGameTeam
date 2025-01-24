//=============================================================================
//
//	ブロック処理 [block.h]
// Author : 佐々木奏一郎
//
//=============================================================================
#ifndef _BLOCK_H_//このマクロ定義がされていなかったら
#define _BLOCK_H_//2銃インクルード防止のマクロ定義
#include "main.h"
#include "player.h"
#define NUM_BLOCK (16)
typedef enum
{
	BLOCK_HOUSE00=0,		//普通のブロック
	BLOCK_HOUSE01,
	BLOCK_WALL00,
	BLOCK_WALL01,
	BLOCK_MAX
}BLOCKTYPE;

typedef struct
{
	LPD3DXMESH pMesh;					//メッシュ（頂点情報)へのポインタ
	LPDIRECT3DTEXTURE9 apTexture[128];	//テクスチャへのポインタ
	LPD3DXBUFFER pBuffMat;				//マテリアルへのポインタ
	DWORD dwNumMat;						//マテリアルの数
	D3DXVECTOR3 pos;					//位置
	D3DXVECTOR3 rot;					//向き
	D3DXMATRIX mtxWorld;				//ワールドマトリックス
	D3DXVECTOR3 vtxMin, vtxMax;			//モデルの最小値,最大値
	int nType;
	bool bUse;

}BLOCK;

static const char* X_BLOCK[BLOCK_MAX] =
{
	"data\\model\\house000.x",
	"data\\model\\house01.x",
	"data\\model\\wallmaria.x",
	"data\\model\\wallmaria2.x",
};

//プロトタイプ宣言
void InitBlock(void);
void UninitBlock(void);
void UpdateBlock(void);
void DrawBlock(void);
void SetBlock(D3DXVECTOR3 pos, int nType);
void CollisionBlock(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld);

#endif