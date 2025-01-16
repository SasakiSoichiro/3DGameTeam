//=============================================================
//
//			壁			meshwall.cpp
//
//		Athor : ryuusei hirata
//
//==============================================================
#include "main.h"
#include "meshwall.h"

//	グローバル
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshWall = NULL;	//	頂点バッファのポインタ
LPDIRECT3DTEXTURE9 g_apTextureMeshWall = NULL;		//	テクスチャのポインタ
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshWall = NULL;	//	インデックスのポインタ
MESHWALL g_MeshWall = {};

//---------------
//	初期化処理	
//---------------
void InitMeshWall(void)
{
	//	デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//頂点バッファの設定
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MESHWALL_T,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshWall,
		NULL);

	//	テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\texture\\ground02.png",
		&g_apTextureMeshWall);

	//	インデックスバッファの生成
	pDevice->CreateIndexBuffer(sizeof(WORD) * MESHWALL_I,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffMeshWall,
		NULL);

	//	pVtxの初期化
	VERTEX_3D* pVtx = NULL;
	WORD* pIdx = NULL;

	//	頂点バッファのロック
	g_pVtxBuffMeshWall->Lock(0, 0, (void**)&pVtx, 0);

	g_MeshWall.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MeshWall.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	int count = 0;
	float radius = 200.0f;
	D3DXVECTOR3 unti;

	for (int nCntZ = 0; nCntZ <= SUITYOKU; nCntZ++)
	{
		//	人による処理ある

		for (int nCntX = 0; nCntX <= SUIHEI; nCntX++)
		{
			//	角度
			float Angle = D3DX_PI * 2.0f / (float)SUIHEI * -1.0f;

			//	座標
			pVtx[count].pos = D3DXVECTOR3(sinf(Angle * nCntX) * radius,
											nCntZ * 100.0f,
											cosf(Angle * nCntX) * radius);

			//	法線
			unti = pVtx[count].pos - g_MeshWall.pos;
			D3DXVec3Normalize(&pVtx[count].nor, &unti);

			//	カラー
			pVtx[count].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//	テクスチャ
			pVtx[count].tex.x = 0.125f * nCntX;
			pVtx[count].tex.y = 0.125f * nCntZ;

			//	大智
			count++;
		}
	}

	//	頂点バッファのアンロック
	g_pVtxBuffMeshWall->Unlock();

	//	インデックスのロック
	g_pIdxBuffMeshWall->Lock(0, 0, (void**)&pIdx, 0);

	//	インデックスの設定
	int count2 = 0;
	int count3 = 0;
	int count4 = SUIHEI + 1;

	//	インデックスの設定
	for (int nCntX = 0; nCntX < SUITYOKU; nCntX++)
	{
		for (int nCntZ = 0; nCntZ <= SUIHEI; nCntZ++)
		{
			pIdx[count2] = count4;
			pIdx[count2 + 1] = count3;

			count2 += 2;
			count3++;
			count4++;
		}

		pIdx[count2] = count3 - 1;
		pIdx[count2 + 1] = count4;
		count2 += 2;
	}

	//	インデックスのアンロック
	g_pIdxBuffMeshWall->Unlock();

}

//---------------
//	終了処理	
//---------------
void UninitMeshWall(void)
{
	if (g_pVtxBuffMeshWall != NULL)
	{
		g_pVtxBuffMeshWall->Release();
		g_pVtxBuffMeshWall = NULL;
	}

	if (g_apTextureMeshWall != NULL)
	{
		g_apTextureMeshWall->Release();
		g_apTextureMeshWall = NULL;
	}

	if (g_pIdxBuffMeshWall != NULL)
	{
		g_pIdxBuffMeshWall->Release();
		g_pIdxBuffMeshWall = NULL;
	}
}

//---------------
//	更新処理	
//---------------
void UpdataMeshWall(void)
{

}

//---------------
//	描画処理	
//---------------
void DrawMeshWall(void)
{
	//	デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//	計算マトリックス
	D3DXMATRIX mtxRot, mtxTrans;

	//	ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_MeshWall.mtxWorld);

	//	向き反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_MeshWall.rot.y, g_MeshWall.rot.x, g_MeshWall.rot.z);
	D3DXMatrixMultiply(&g_MeshWall.mtxWorld, &g_MeshWall.mtxWorld, &mtxRot);

	//	位置の反映
	D3DXMatrixTranslation(&mtxTrans, g_MeshWall.pos.x, g_MeshWall.pos.y, g_MeshWall.pos.z);
	D3DXMatrixMultiply(&g_MeshWall.mtxWorld, &g_MeshWall.mtxWorld, &mtxTrans);

	//	ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_MeshWall.mtxWorld);

	//	頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffMeshWall, 0, sizeof(VERTEX_3D));

	//	インデックスをデバイスのデータストリームに設定
	pDevice->SetIndices(g_pIdxBuffMeshWall);

	//	テクスチャの設定
	pDevice->SetTexture(0, g_apTextureMeshWall);

	//	頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//	ポリゴンの描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, MESHWALL_T, 0, MESHWALL_P);
}