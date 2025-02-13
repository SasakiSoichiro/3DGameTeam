//================================================
//
//		タイトル	title3D.cpp
//
//			ryuusei.hirata
//================================================
#include "title3D.h"
#include "fade.h"
#include "sound.h"
#include "camera.h"
#include "title.h"
#include "meshfield.h"
#include "light.h"
#include "model.h"

//タイトルの初期化
void InitTitle3D(void)
{
	InitCamera();
	InitTitle();
	InitMeshfield();
	InitLighr();
}

//タイトルの終了処理
void UninitTitle3D()
{
	UninitCamera();
	UninitTitle();
	UninitMeshfield();
	UninitLight();
}

//タイトルの更新処理
void UpdateTitle3D()
{
	UpdateCamera();
	UpdateTitle();
	UpdateMeshfield();
	UpdateLight();
}

//タイトルの描画処理
void DrawTitle3D()
{
	DrawMeshfield();
	DrawTitle();
}
