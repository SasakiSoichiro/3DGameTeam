//==========================================
//
//		プレイヤー		Player.cpp
//			ryuusei hirata
//
//=========================================
#include "main.h"
#include "player.h"
#include "input.h"
#include "camera.h"

//	グロバール
Player g_player = {};

static KEY_INFO g_aKeyNeutral[] =
{
	//	キー1
	{40,
	{{0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.0f},

	{0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.0f},

	{0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.69f},

	{0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.0f},

	{0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, -0.66f},

	{0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.0f},

	{0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.0f},

	{0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.0f},

	{0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.0f},

	{0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.0f}}},

	//	キー2
	{40,
	{{0.0f, 0.0f, 0.0f,
	-0.16f, 0.0f, 0.0f},

	{0.0f, 0.0f, 0.0f,
	-0.16f, 0.0f, 0.0f},

	{0.0f, 0.0f, 0.0f,
	0.16f, 0.0f, 0.69f},

	{0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.0f},

	{0.0f, 0.0f, 0.0f,
	0.16f, 0.0f, -0.66f},

	{0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.0f},

	{0.0f, 0.0f, 0.0f,
	0.16f, 0.0f, 0.0f},

	{0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.00f},

	{0.0f, 0.0f, 0.0f,
	0.16f, 0.0f, 0.0f},

	{0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.0f}}}
};

static KEY_INFO g_aKeyMove[] =
{
	//	キー1
	{10,
	{{0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.0f},

	{0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.0f},

	{0.0f, 0.0f, 0.0f,
	-0.69f, 0.0f, 0.57f},

	{0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.0f},

	{0.0f, 0.0f, 0.0f,
	0.94f, 0.0f, -0.57f},

	{0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.0f},

	{0.0f, 0.0f, 0.0f,
	0.75f, 0.0f, 0.0f},

	{0.0f, 0.0f, 0.0f,
	0.03f, 0.0f, 0.0f},

	{0.0f, 0.0f, 0.0f,
	-0.75f, 0.0f, 0.0f},

	{0.0f, 0.0f, 0.0f,
	-0.13f, 0.0f, 0.0f}}},

	//	キー2
	{10,
	{{0.0f, 0.0f, 0.0f,
	-0.25f, 0.0f, 0.0f},

	{0.0f, 0.0f, 0.0f,
	-0.09f, 0.0f, 0.0f},

	{0.0f, 0.0f, 0.0f,
	-0.75f, 0.0f, 0.57f},

	{0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.0f},

	{0.0f, 0.0f, 0.0f,
	1.07f, 0.0f, -0.57f},

	{0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.0f},

	{0.0f, 0.0f, 0.0f,
	0.82f, 0.0f, 0.0f},

	{0.0f, 0.0f, 0.0f,
	-0.28f, 0.0f, 0.00f},

	{0.0f, 0.0f, 0.0f,
	-0.85f, 0.0f, 0.0f},

	{0.0f, 0.0f, 0.0f,
	-0.44f, 0.0f, 0.0f}}},

	//	キー3
	{10,
	{{0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.0f},

	{0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.0f},

	{0.0f, 0.0f, 0.0f,
	0.75f, 0.0f, 0.57f},

	{0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.0f},

	{0.0f, 0.0f, 0.0f,
	-0.79f, 0.0f, -0.57f},

	{0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.0f},

	{0.0f, 0.0f, 0.0f,
	-0.82f, 0.0f, 0.0f},

	{0.0f, 0.0f, 0.0f,
	0.03f, 0.0f, 0.00f},

	{0.0f, 0.0f, 0.0f,
	0.69f, 0.0f, 0.0f},

	{0.0f, 0.0f, 0.0f,
	-0.13f, 0.0f, 0.0f}}},

	//	キー4
	{10,
	{{0.0f, 0.0f, 0.0f,
	-0.16f, 0.0f, 0.0f},

	{0.0f, 0.0f, 0.0f,
	-0.09f, 0.0f, 0.0f},

	{0.0f, 0.0f, 0.0f,
	1.01f, 0.0f, 0.57f},

	{0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.0f},

	{0.0f, 0.0f, 0.0f,
	-0.85f, 0.0f, -0.57f},

	{0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.0f},

	{0.0f, 0.0f, 0.0f,
	-1.01f, -0.0f, 0.0f},

	{0.0f, 0.0f, 0.0f,
	-0.16f, 0.0f, 0.0f},

	{0.0f, 0.0f, 0.0f,
	0.79f, 0.0f, 0.0f},

	{0.0f, 0.0f, 0.0f,
	-0.25f, 0.0f, 0.0f}}},
};

//========================
//		初期化処理
//========================
void InitPlayer(void)
{
	//	デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATERIAL* pMat;

	g_player.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//g_player.moverot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//g_player.MotionType = MOTIONTYPE_NEUTRAL;
	//g_player.nextKey = 1;
	//g_player.nKey = 0;
	//g_player.bLoopMotion = false;
	//g_player.nCntMotion = 0;

	//g_player.aMotionInfo[0].aKeyinfo[0] = g_aKeyNeutral[0];
	//g_player.aMotionInfo[0].aKeyinfo[1] = g_aKeyNeutral[1];

	//g_player.aMotionInfo[1].aKeyinfo[0] = g_aKeyMove[0];
	//g_player.aMotionInfo[1].aKeyinfo[1] = g_aKeyMove[1];
	//g_player.aMotionInfo[1].aKeyinfo[2] = g_aKeyMove[2];
	//g_player.aMotionInfo[1].aKeyinfo[3] = g_aKeyMove[3];

	////	Xファイルの読み込み
	//D3DXLoadMeshFromX("data\\model\\player2\\00_body.x",
	//	D3DXMESH_SYSTEMMEM,
	//	pDevice,
	//	NULL,
	//	&g_player.aModel[0].pBuffMat,
	//	NULL,
	//	&g_player.aModel[0].dwNumMat,
	//	&g_player.aModel[0].pMesh);

	//D3DXLoadMeshFromX("data\\model\\player2\\01_head.x",
	//	D3DXMESH_SYSTEMMEM,
	//	pDevice,
	//	NULL,
	//	&g_player.aModel[1].pBuffMat,
	//	NULL,
	//	&g_player.aModel[1].dwNumMat,
	//	&g_player.aModel[1].pMesh);

	//D3DXLoadMeshFromX("data\\model\\player2\\02_armR.x",
	//	D3DXMESH_SYSTEMMEM,
	//	pDevice,
	//	NULL,
	//	&g_player.aModel[2].pBuffMat,
	//	NULL,
	//	&g_player.aModel[2].dwNumMat,
	//	&g_player.aModel[2].pMesh);

	//D3DXLoadMeshFromX("data\\model\\player2\\03_handR.x",
	//	D3DXMESH_SYSTEMMEM,
	//	pDevice,
	//	NULL,
	//	&g_player.aModel[3].pBuffMat,
	//	NULL,
	//	&g_player.aModel[3].dwNumMat,
	//	&g_player.aModel[3].pMesh);

	//D3DXLoadMeshFromX("data\\model\\player2\\04_armL.x",
	//	D3DXMESH_SYSTEMMEM,
	//	pDevice,
	//	NULL,
	//	&g_player.aModel[4].pBuffMat,
	//	NULL,
	//	&g_player.aModel[4].dwNumMat,
	//	&g_player.aModel[4].pMesh);

	//D3DXLoadMeshFromX("data\\model\\player2\\05_handL.x",
	//	D3DXMESH_SYSTEMMEM,
	//	pDevice,
	//	NULL,
	//	&g_player.aModel[5].pBuffMat,
	//	NULL,
	//	&g_player.aModel[5].dwNumMat,
	//	&g_player.aModel[5].pMesh);

	//D3DXLoadMeshFromX("data\\model\\player2\\06_legR.x",
	//	D3DXMESH_SYSTEMMEM,
	//	pDevice,
	//	NULL,
	//	&g_player.aModel[6].pBuffMat,
	//	NULL,
	//	&g_player.aModel[6].dwNumMat,
	//	&g_player.aModel[6].pMesh);

	//D3DXLoadMeshFromX("data\\model\\player2\\07_footR.x",
	//	D3DXMESH_SYSTEMMEM,
	//	pDevice,
	//	NULL,
	//	&g_player.aModel[7].pBuffMat,
	//	NULL,
	//	&g_player.aModel[7].dwNumMat,
	//	&g_player.aModel[7].pMesh);

	//D3DXLoadMeshFromX("data\\model\\player2\\08_legL.x",
	//	D3DXMESH_SYSTEMMEM,
	//	pDevice,
	//	NULL,
	//	&g_player.aModel[8].pBuffMat,
	//	NULL,
	//	&g_player.aModel[8].dwNumMat,
	//	&g_player.aModel[8].pMesh);

	//D3DXLoadMeshFromX("data\\model\\player2\\09_footL.x",
	//	D3DXMESH_SYSTEMMEM,
	//	pDevice,
	//	NULL,
	//	&g_player.aModel[9].pBuffMat,
	//	NULL,
	//	&g_player.aModel[9].dwNumMat,
	//	&g_player.aModel[9].pMesh);

	//g_player.nNumModel = 10;
	//g_player.nNumKey = 10;
	//g_player.nNumMotion = 10;

	////	階層構造の設定
	////	体
	//g_player.aModel[0].nIdxModelParent = -1;
	//g_player.aModel[0].pos = D3DXVECTOR3(0.0f, 12.0f, 0.0f);
	//g_player.aModel[0].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	////	頭
	//g_player.aModel[1].nIdxModelParent = 0;
	//g_player.aModel[1].pos = D3DXVECTOR3(0.0f, 13.0f, 0.0f);
	//g_player.aModel[1].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	////	右腕
	//g_player.aModel[2].nIdxModelParent = 0;
	//g_player.aModel[2].pos = D3DXVECTOR3(-5.0f, 12.0f, 0.0f);
	//g_player.aModel[2].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	////	右手
	//g_player.aModel[3].nIdxModelParent = 2;
	//g_player.aModel[3].pos = D3DXVECTOR3(-10.0f, 0.0f, 0.0f);
	//g_player.aModel[3].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	////	左腕
	//g_player.aModel[4].nIdxModelParent = 0;
	//g_player.aModel[4].pos = D3DXVECTOR3(5.0f, 12.0f, 0.0f);
	//g_player.aModel[4].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	////	左手
	//g_player.aModel[5].nIdxModelParent = 4;
	//g_player.aModel[5].pos = D3DXVECTOR3(10.0f, 0.0f, 0.0f);
	//g_player.aModel[5].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	////	右腿
	//g_player.aModel[6].nIdxModelParent = 0;
	//g_player.aModel[6].pos = D3DXVECTOR3(-3.0f, 0.0f, 0.0f);
	//g_player.aModel[6].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	////	右足
	//g_player.aModel[7].nIdxModelParent = 6;
	//g_player.aModel[7].pos = D3DXVECTOR3(0.0f, -8.0f, 0.0f);
	//g_player.aModel[7].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	////	左腿
	//g_player.aModel[8].nIdxModelParent = 0;
	//g_player.aModel[8].pos = D3DXVECTOR3(3.0f, 0.0f, 0.0f);
	//g_player.aModel[8].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	////	左足
	//g_player.aModel[9].nIdxModelParent = 8;
	//g_player.aModel[9].pos = D3DXVECTOR3(0.0f, -8.0f, 0.0f);
	//g_player.aModel[9].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	int nNumvtx;		//	頂点数
	DWORD sizeFVF;		//	頂点フォーマットのサイズ
	BYTE* pVtxBuff;		//	頂点バッファへのポインタ

	//	頂点数の取得
	//nNumvtx = g_player.aModel->pMesh->GetNumVertices();

	//	頂点フォーマットのサイズ取得
	//sizeFVF = D3DXGetFVFVertexSize(g_player.aModel->pMesh->GetFVF());

	//	頂点バッファのロック
	//g_player.aModel->pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	//for (int nCntVtx = 0; nCntVtx < nNumvtx; nCntVtx++)
	//{
	//	D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

	//	//	比較	X
	//	if (vtx.x > g_player.vtxMax.x)
	//	{
	//		g_player.vtxMax.x = vtx.x;
	//	}
	//	else if (vtx.x < g_player.vtxMin.x)
	//	{
	//		g_player.vtxMin.x = vtx.x;
	//	}

	//	//	比較	Y
	//	if (vtx.y > g_player.vtxMax.y)
	//	{
	//		g_player.vtxMax.y = vtx.y;
	//	}
	//	else if (vtx.y < g_player.vtxMin.y)
	//	{
	//		g_player.vtxMin.y = vtx.y;
	//	}

	//	//	比較	Z
	//	if (vtx.z > g_player.vtxMax.z)
	//	{
	//		g_player.vtxMax.z = vtx.z;
	//	}
	//	else if (vtx.z < g_player.vtxMin.z)
	//	{
	//		g_player.vtxMin.z = vtx.z;
	//	}

	//	//	頂点フォーマットのサイズ分ポインタを進める
	//	pVtxBuff += sizeFVF;
	//}

	//g_player.vtxMax.z = (float)((int)g_player.vtxMax.z / 1);
	//g_player.vtxMin.z = (float)((int)g_player.vtxMin.z / 1);

	//	アンロック
	//g_player.aModel->pMesh->UnlockVertexBuffer();

	//for (int nCntModel = 0; nCntModel < g_player.nNumModel; nCntModel++)
	//{
	//	//	テクスチャの読み込み
	//	pMat = (D3DXMATERIAL*)g_player.aModel[nCntModel].pBuffMat->GetBufferPointer();

	//	for (int nCntMat = 0; nCntMat < (int)g_player.aModel[nCntModel].dwNumMat; nCntMat++)
	//	{
	//		if (pMat[nCntMat].pTextureFilename != NULL)
	//		{
	//			D3DXCreateTextureFromFile(pDevice,
	//				pMat[nCntMat].pTextureFilename,
	//				&g_player.aModel[nCntModel].apTexture[nCntMat]);
	//		}
	//	}
	//}
}

//========================
//		終了処理
//========================
void UninitPlayer(void)
{
	//	メッシュの破棄
	//for (int count = 0; count < g_player.nNumModel; count++)
	//{
	//	if (g_player.aModel[count].pMesh != NULL)
	//	{
	//		g_player.aModel[count].pMesh->Release();
	//		g_player.aModel[count].pMesh = NULL;
	//	}

	//	//	マテリアルの破棄
	//	if (g_player.aModel[count].pBuffMat != NULL)
	//	{
	//		g_player.aModel[count].pBuffMat->Release();
	//		g_player.aModel[count].pBuffMat = NULL;
	//	}
	//}
}

//========================
//		更新処理
//========================
void UpdatePlayer(void)
{
	Camera* pCamera = GetCamera();
	float diff = 0.0f;
	//g_player.Oldpos = g_player.pos;

	if (GetKeyboardPress(DIK_W) == true)
	{
		g_player.move.x += sinf(pCamera->rot.y) * 4.0f;
		g_player.move.z += cosf(pCamera->rot.y) * 4.0f;
		g_player.rotDest.y = D3DX_PI;
	}
	else if (GetKeyboardPress(DIK_S) == true)
	{
		g_player.move.x -= sinf(pCamera->rot.y) * 4.0f;
		g_player.move.z -= cosf(pCamera->rot.y) * 4.0f;
		g_player.rotDest.y = 0.0f;
	}
	else if (GetKeyboardPress(DIK_A) == true)
	{
		g_player.move.x -= cosf(pCamera->rot.y) * 4.0f;
		g_player.move.z += sinf(pCamera->rot.y) * 4.0f;
		g_player.rotDest.y = D3DX_PI * 0.5f;
	}
	else if (GetKeyboardPress(DIK_D) == true)
	{
		g_player.move.x += cosf(pCamera->rot.y) * 4.0f;
		g_player.move.z -= sinf(pCamera->rot.y) * 4.0f;
		g_player.rotDest.y = -D3DX_PI * 0.5f;
	}

	//	角度の正規化
	if (g_player.rot.y > D3DX_PI)
	{
		g_player.rot.y = g_player.rot.y - D3DX_PI;
		g_player.rot.y = -D3DX_PI - g_player.rot.y;

	}
	else if (g_player.rot.y < -D3DX_PI)
	{
		g_player.rot.y = g_player.rot.y + D3DX_PI;
		g_player.rot.y = D3DX_PI + g_player.rot.y;
	}

	diff = g_player.rotDest.y - g_player.rot.y;

	if (diff > D3DX_PI)
	{
		diff = diff - D3DX_PI * 2.0f;
	}
	else if (diff < -D3DX_PI)
	{
		diff = diff + D3DX_PI * 2.0f;
	}

	g_player.rot.y += diff * 0.2f;


	//UpdateMotion(1);

	g_player.move = g_player.move * 0.6f;
	g_player.pos += g_player.move;

}

//=======================
//		描画処理
//=======================
void DrawPlayer(void)
{
	//	デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;
	D3DMATERIAL9 matDef;
	D3DXMATERIAL* pMat;

	//	ワールドマトリックスの初期化
	//D3DXMatrixIdentity(&g_player.mtxWold);

	//	向き反映
	//D3DXMatrixRotationYawPitchRoll(&mtxRot, g_player.rot.y, g_player.rot.x, g_player.rot.z);
	//D3DXMatrixMultiply(&g_player.mtxWold, &g_player.mtxWold, &mtxRot);

	//	位置の反映
	D3DXMatrixTranslation(&mtxTrans, g_player.pos.x, g_player.pos.y, g_player.pos.z);
	//D3DXMatrixMultiply(&g_player.mtxWold, &g_player.mtxWold, &mtxTrans);

	//	ワールドマトリックスの設定
	//pDevice->SetTransform(D3DTS_WORLD, &g_player.mtxWold);

	//	現在のマテリアルを保存
	pDevice->GetMaterial(&matDef);

	//for (int nCntModel = 0; nCntModel < g_player.nNumModel; nCntModel++)
	//{
	//	D3DXMATRIX mtxRotModel, mtxTransModel;	//	計算用
	//	D3DXMATRIX mtxParent;	//	親のマトリックス

	//	//	パーツの初期化
	//	D3DXMatrixIdentity(&g_player.aModel[nCntModel].mtxWorld);

	//	//	向き反映
	//	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_player.aModel[nCntModel].rot.y, g_player.aModel[nCntModel].rot.x, g_player.aModel[nCntModel].rot.z);
	//	D3DXMatrixMultiply(&g_player.aModel[nCntModel].mtxWorld, &g_player.aModel[nCntModel].mtxWorld, &mtxRot);

	//	//	位置の反映
	//	D3DXMatrixTranslation(&mtxTrans, g_player.aModel[nCntModel].pos.x, g_player.aModel[nCntModel].pos.y, g_player.aModel[nCntModel].pos.z);
	//	D3DXMatrixMultiply(&g_player.aModel[nCntModel].mtxWorld, &g_player.aModel[nCntModel].mtxWorld, &mtxTrans);

	//	//	親のパーツ設定
	//	if (g_player.aModel[nCntModel].nIdxModelParent != -1)
	//	{
	//		mtxParent = g_player.aModel[g_player.aModel[nCntModel].nIdxModelParent].mtxWorld;
	//	}
	//	else
	//	{
	//		mtxParent = g_player.mtxWold;
	//	}

	//	//	算出したマトリックスと親のマトリックスを掛け合わせる
	//	D3DXMatrixMultiply(&g_player.aModel[nCntModel].mtxWorld,
	//		&g_player.aModel[nCntModel].mtxWorld,
	//		&mtxParent);

	//	//	パーツのマトリックスの設定
	//	pDevice->SetTransform(D3DTS_WORLD,
	//		&g_player.aModel[nCntModel].mtxWorld);

	//	//	マテリアルデータへのポインタを取得
	//	pMat = (D3DXMATERIAL*)g_player.aModel[nCntModel].pBuffMat->GetBufferPointer();

	//	for (int nCntMat = 0; nCntMat < (int)g_player.aModel[nCntModel].dwNumMat; nCntMat++)
	//	{
	//		//	マテリアルの設定
	//		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

	//		//	テクスチャの設定
	//		pDevice->SetTexture(0, g_player.aModel[nCntModel].apTexture[nCntMat]);

	//		//	モデルの描画
	//		g_player.aModel[nCntModel].pMesh->DrawSubset(nCntMat);
	//	}
	//}

	//	保存したマテリアルを戻す		
	pDevice->SetMaterial(&matDef);
}

Player* GetPlayer(void)
{
	return &g_player;
}

//	モーション
void UpdateMotion(int count)
{
	KEY sabun;
	KEY motomeru;

	//for (int nCnt1 = 0; nCnt1 < 10; nCnt1++)
	//{
	//	sabun.fposx = g_player.aMotionInfo[count].aKeyinfo[g_player.nextKey].aKey[nCnt1].fposx - g_player.aMotionInfo[count].aKeyinfo[g_player.nKey].aKey[nCnt1].fposx;
	//	sabun.fposy = g_player.aMotionInfo[count].aKeyinfo[g_player.nextKey].aKey[nCnt1].fposy - g_player.aMotionInfo[count].aKeyinfo[g_player.nKey].aKey[nCnt1].fposy;
	//	sabun.fposz = g_player.aMotionInfo[count].aKeyinfo[g_player.nextKey].aKey[nCnt1].fposz - g_player.aMotionInfo[count].aKeyinfo[g_player.nKey].aKey[nCnt1].fposz;

	//	sabun.frotx = g_player.aMotionInfo[count].aKeyinfo[g_player.nextKey].aKey[nCnt1].frotx - g_player.aMotionInfo[count].aKeyinfo[g_player.nKey].aKey[nCnt1].frotx;
	//	sabun.froty = g_player.aMotionInfo[count].aKeyinfo[g_player.nextKey].aKey[nCnt1].froty - g_player.aMotionInfo[count].aKeyinfo[g_player.nKey].aKey[nCnt1].froty;
	//	sabun.frotz = g_player.aMotionInfo[count].aKeyinfo[g_player.nextKey].aKey[nCnt1].frotz - g_player.aMotionInfo[count].aKeyinfo[g_player.nKey].aKey[nCnt1].frotz;

	//	//motomeru.fposx = g_aKeyNeutral[g_player.nKey].aKey[nCnt1].fposx + sabun.fposx * (float)(g_player.nCntMotion / 120.0f);
	//	//motomeru.fposy = g_aKeyNeutral[g_player.nKey].aKey[nCnt1].fposy + sabun.fposy * (float)(g_player.nCntMotion / 120.0f);
	//	//motomeru.fposz = g_aKeyNeutral[g_player.nKey].aKey[nCnt1].fposz + sabun.fposz * (float)(g_player.nCntMotion / 120.0f);

	//	motomeru.frotx = g_player.aMotionInfo[count].aKeyinfo[g_player.nextKey].aKey[nCnt1].frotx + sabun.frotx * ((float)(g_player.nCntMotion / 20.0f));
	//	motomeru.froty = g_player.aMotionInfo[count].aKeyinfo[g_player.nextKey].aKey[nCnt1].froty + sabun.froty * ((float)(g_player.nCntMotion / 20.0f));
	//	motomeru.frotz = g_player.aMotionInfo[count].aKeyinfo[g_player.nextKey].aKey[nCnt1].frotz + sabun.frotz * ((float)(g_player.nCntMotion / 20.0f));

	//	//g_player.aModel[nCnt1].pos.x = motomeru.fposx;
	//	//g_player.aModel[nCnt1].pos.y = motomeru.fposy;
	//	//g_player.aModel[nCnt1].pos.z = motomeru.fposz;

	//	g_player.aModel[nCnt1].rot.x = motomeru.frotx;
	//	g_player.aModel[nCnt1].rot.y = motomeru.froty;
	//	g_player.aModel[nCnt1].rot.z = motomeru.frotz;
	//}

	//g_player.nCntMotion++;

	//if (g_player.nCntMotion >= 20)
	//{
	//	g_player.nCntMotion = 0;
	//	g_player.nextKey++;
	//	g_player.nKey++;

	//	if (g_player.nextKey >= 4)
	//	{
	//		g_player.nextKey = 0;
	//	}

	//	if (g_player.nKey >= 4)
	//	{
	//		g_player.nKey = 0;
	//	}
	//}
}