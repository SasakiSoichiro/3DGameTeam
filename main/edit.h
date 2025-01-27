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

//マクロ定義
#define NUM_EDIT (64)
#define EDITTEXTURE (128)	//テクスチャの最大数
#define EDIT_MOVE (2.0f)
#define TEXTFILE "data\\STAGE\\stage.txt"

typedef enum
{
	//家1
	EDIT_HOUSE00 = 0,		//普通のブロック
	EDIT_HOUSE00_L,
	EDIT_HOUSE00_R,
	EDIT_HOUSE00_B,

	//家2
	EDIT_HOUSE01,
	EDIT_HOUSE01_L,
	EDIT_HOUSE01_R,
	EDIT_HOUSE01_B,

	//家3
	EDIT_HOUSE02,
	EDIT_HOUSE02_L,
	EDIT_HOUSE02_R,
	EDIT_HOUSE02_B,

	//家3
	EDIT_HOUSE03,
	EDIT_HOUSE03_L,
	EDIT_HOUSE03_R,
	EDIT_HOUSE03_B,

	//壁
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
	//家1個目
	"data\\model\\house.x",
	"data\\model\\house_L.x",
	"data\\model\\house_R.x",
	"data\\model\\house_B.x",

	//家2個目
	"data\\model\\house000.x",
	"data\\model\\house000_L.x",
	"data\\model\\house000_r.x",
	"data\\model\\house000_b.x",

	//家3個目
	"data\\model\\house01.x",
	"data\\model\\house01_L.x",
	"data\\model\\house01_R.x",
	"data\\model\\house01_B.x",

	//家4個目
	"data\\model\\house04.x",
	"data\\model\\house04_L.x",
	"data\\model\\house04_R.x",
	"data\\model\\house04_B.x",


	//壁
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