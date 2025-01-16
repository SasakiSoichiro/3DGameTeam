//===============================================================-
//
//			メッシュフィールド			meshfield.cpp
//
//				Athor : ryuuseivhirata
//
//================================================================
#include "main.h"
#include "meshfield.h"

//	グローバル宣言
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshfield = NULL;	//	頂点バッファのポインタ
LPDIRECT3DTEXTURE9 g_apTextureMeshfield = NULL;		//	テクスチャのポインタ
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshField = NULL;	//	インデックスのポインタ
MESHFIELD g_MeshField = {};

//==================
//	初期化処理
//==================
void InitMeshfield(void)
{
	//	デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//頂点バッファの設定
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MESHFIELD_T,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshfield,
		NULL);

	//	テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\texture\\ground.png",
		&g_apTextureMeshfield);

	//	インデックスバッファの生成
	pDevice->CreateIndexBuffer(sizeof(WORD) * MESHFIELD_I,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffMeshField,
		NULL);

	//	pVtxの初期化
	VERTEX_3D* pVtx = NULL;
	WORD* pIdx = NULL;

	//	頂点バッファのロック
	g_pVtxBuffMeshfield->Lock(0, 0, (void**)&pVtx, 0);

	g_MeshField.pos = D3DXVECTOR3(-500.0f, 0.0f, 500.0f);
	g_MeshField.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	int count = 0;

	for (int nCntZ = 0; nCntZ <= MESHFIELD_Z; nCntZ++)
	{
		//	人による処理ある

		for (int nCntX = 0; nCntX <= MESHFIELD_X; nCntX++)
		{
			//	頂点情報の設定
			pVtx[count].pos.x = 50.0f * nCntX;
			pVtx[count].pos.y = 0.0f;
			pVtx[count].pos.z = -50.0f * nCntZ;

			//	テクスチャ
			pVtx[count].tex.x = 0.5f * nCntX;
			pVtx[count].tex.y = 0.5f * nCntZ;

			//	各頂点の法線の設定
			pVtx[count].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			//	頂点カラー
			pVtx[count].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//	大智
			count++;
		}
	}

	//	頂点バッファのアンロック
	g_pVtxBuffMeshfield->Unlock();

	//	インデックスのロック
	g_pIdxBuffMeshField->Lock(0, 0, (void**)&pIdx, 0);

	//	インデックスの設定
	int count2 = 0;
	int count3 = 0;
	int count4 = MESHFIELD_X + 1;
	int nCntZ = 0;

	//	インデックスの設定
	for (int nCntX = 0; nCntX < MESHFIELD_X; nCntX++)
	{
		for (nCntZ = 0; nCntZ <= MESHFIELD_Z; nCntZ++)
		{
			pIdx[count2] = count4;
			pIdx[count2 + 1] = count3;

			count2 += 2;
			count3++;
			count4++;
		}

		if (nCntZ <= MESHFIELD_Z)
		{
			pIdx[count2] = count3 - 1;
			pIdx[count2 + 1] = count4;
			count2 += 2;
		}
	}

	//	インデックスのアンロック
	g_pIdxBuffMeshField->Unlock();
}

//==================
//	終了処理
//==================
void UninitMeshfield(void)
{
	//	頂点バッファの破棄
	if (g_pVtxBuffMeshfield != NULL)
	{
		g_pVtxBuffMeshfield->Release();
		g_pVtxBuffMeshfield = NULL;
	}

	if (g_apTextureMeshfield != NULL)
	{
		g_apTextureMeshfield->Release();
		g_apTextureMeshfield = NULL;
	}

	if (g_pIdxBuffMeshField != NULL)
	{
		g_pIdxBuffMeshField->Release();
		g_pIdxBuffMeshField = NULL;
	}
}

//==================
//	更新処理
//==================
void UpdataMeshfield(void)
{

}

//==================
//	描画処理
//==================
void DrawMeshfield(void)
{
	//	デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//	計算マトリックス
	D3DXMATRIX mtxRot, mtxTrans;

	//	ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_MeshField.mtxWorld);

	//	向き反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_MeshField.rot.y, g_MeshField.rot.x, g_MeshField.rot.z);
	D3DXMatrixMultiply(&g_MeshField.mtxWorld, &g_MeshField.mtxWorld, &mtxRot);

	//	位置の反映
	D3DXMatrixTranslation(&mtxTrans, g_MeshField.pos.x, g_MeshField.pos.y, g_MeshField.pos.z);
	D3DXMatrixMultiply(&g_MeshField.mtxWorld, &g_MeshField.mtxWorld, &mtxTrans);

	//	ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_MeshField.mtxWorld);

	//	頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffMeshfield, 0, sizeof(VERTEX_3D));

	//	インデックスをデバイスのデータストリームに設定
	pDevice->SetIndices(g_pIdxBuffMeshField);

	//	テクスチャの設定
	pDevice->SetTexture(0, g_apTextureMeshfield);

	//	頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//	ポリゴンの描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, MESHFIELD_T, 0, MESHFIELD_P);
}
