//=============================================================================
//
//	メッシュフィールド処理 [Meshfield.h]
// Author : 佐々木奏一郎
//
//=============================================================================
#ifndef _MESHFIELD_H_//このマクロ定義がされていなかったら
#define _MESHFIELD_H_//2銃インクルード防止のマクロ定義
#include "main.h"
#define OBJ_X (500.0f)
#define OBJ_Z (500.0f)
#define XMESH (4)
#define ZMESH (8)
#define VTXCNT ((XMESH+1)*(ZMESH+1))
#define POLYCNT ((2*XMESH*ZMESH)+4*(ZMESH-1))
#define IDXCNT (((XMESH+1)*2*ZMESH)+(ZMESH-1)*4)

//プロトタイプ宣言
void InitMeshfield(void);
void UninitMeshfield(void);
void UpdateMeshfield(void);
void DrawMeshfield(void);

#endif