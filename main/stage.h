#ifndef _STAGE_H_
#define _STAGE_H_

#include "main.h"

typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXMATRIX mtxWorld;
}MESHFIELD;

//	プロトタイプ宣言
void InitStage(void);
void UninitStage(void);
void UpdataStage(void);
void DrawStage(void);
void LoadStage(void);

#endif // !_MESHFIELD_H_
