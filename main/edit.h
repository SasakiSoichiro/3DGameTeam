//=============================================================================
//
//	エディット処理 [edit.h]
// Author : 佐々木奏一郎
//
//=============================================================================
#ifndef _EDIT_H_//このマクロ定義がされていなかったら
#define _EDIT_H_//2銃インクルード防止のマクロ定義
#include "main.h"
#include "player.h"
#define NUM_EDIT (64)
#define EDITTEXTURE (128)	//テクスチャの最大数
#define EDIT_MOVE (2.0f)
#define TEXTFILE "data\\STAGE\\stage.txt"
typedef enum
{
	EDIT_HOUSE00 = 0,		//普通のブロック
	EDIT_HOUSE01,
	EDIT_WALL00,
	EDIT_WALL01,
	EDIT_MAX
}EDITTYPE;

typedef struct
{
	LPD3DXMESH pMesh;					//メッシュ（頂点情報)へのポインタ
	LPDIRECT3DTEXTURE9 apTexture[EDITTEXTURE];	//テクスチャへのポインタ
	LPD3DXBUFFER pBuffMat;				//マテリアルへのポインタ
	DWORD dwNumMat;						//マテリアルの数
}EDITTEX;

typedef struct
{
	EDITTEX tex[EDIT_MAX];				//テクスチャ情報
	D3DXVECTOR3 pos;					//位置
	D3DXVECTOR3 move;					//位置
	D3DXVECTOR3 rot;					//向き
	D3DXMATRIX mtxWorld;				//ワールドマトリックス
	D3DXVECTOR3 vtxMin, vtxMax;			//モデルの最小値,最大値
	int nType;
	bool bUse;

}EDITINFO;

static const char* X_EDIT[EDIT_MAX] =
{
	"data\\model\\house000.x",
	"data\\model\\house01.x",
	"data\\model\\wallmaria.x",
	"data\\model\\wallmaria2.x",
};

//プロトタイプ宣言
void InitEdit(void);
void UninitEdit(void);
void UpdateEdit(void);
void DrawEdit(void);
void SaveEdit(void);
void LoadEdit(void);
void ReloadEdit(void);
#endif