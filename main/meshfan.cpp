#include "meshwall.h"
#include "meshfan.h"
#include "player.h"

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_pTextureMeshFan = NULL;//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshFan = NULL;//頂点バッファへのポインタ
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshFan = NULL;//インデックスバッファへのポインタ
MeshFan g_MeshFan;

void InitMeshFan(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\texture\\Fan004.png",
		&g_pTextureMeshFan);

	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * CORNERCNT+1,//(sizeof(VERTEX_3D)*必要な頂点数
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshFan,
		NULL);

	pDevice->CreateIndexBuffer(sizeof(VERTEX_3D) * CORNERCNT+1,//(sizeof(VERTEX_3D)*必要な頂点数
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffMeshFan,
		NULL);

	VERTEX_3D* pVtx = 0;//頂点情報へのポインタ


//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffMeshFan->Lock(0, 0, (void**)&pVtx, 0);

	int nCntPOS = 0;
	int radius = 400;
	float Vmesh = (float)(VMESH);
	float Hmesh = (float)(HMESH);
	D3DXVECTOR3 nor;
	D3DXVECTOR3 vec1, vec2; // ベクトル
	// 外積を求める

	int nCnt = 0;
	pVtx[nCnt].pos = D3DXVECTOR3(0.0f,400.0f,0.0f);

	for (nCnt = 1; nCnt < CORNERCNT + 1; nCnt++)
	{
			float Angle = ((D3DX_PI * 2) / (CORNERCNT) * -nCnt) + D3DX_PI;
			pVtx[nCnt].pos = D3DXVECTOR3(sinf(-Angle) * radius, OBJ_V, cosf(-Angle) * radius);
			nor = pVtx[nCnt].pos - g_MeshFan.pos;
			D3DXVec3Normalize(&pVtx[nCnt].nor, &nor);
			pVtx[nCnt].col = D3DXCOLOR(1.0f, 0.5f, 0.5f, 1.0f);
			pVtx[nCnt].tex = D3DXVECTOR2((1.0f / Vmesh) * nCnt, ((1.0f / Hmesh) * nCnt));
	}

	//頂点バッファをアンロックする
	g_pVtxBuffMeshFan->Unlock();

	//インデックスバッファをロック
	WORD* pIdx;
	g_pIdxBuffMeshFan->Lock(0, 0, (void**)&pIdx, 0);


	for (nCnt = 0; nCnt < CORNERCNT + 1; nCnt++)
	{
		pIdx[nCnt] = nCnt;

	}

	//頂点バッファをアンロックする
	g_pIdxBuffMeshFan->Unlock();

}

void UninitMeshFan(void)
{

	//テクスチャの破棄
	if (g_pTextureMeshFan != NULL)
	{
		g_pTextureMeshFan->Release();
		g_pTextureMeshFan = NULL;
	}


	//頂点バッファの解放
	if (g_pVtxBuffMeshFan != NULL)
	{
		g_pVtxBuffMeshFan->Release();
		g_pVtxBuffMeshFan = NULL;
	}


	//インデックスバッファの解放
	if (g_pIdxBuffMeshFan != NULL)
	{
		g_pIdxBuffMeshFan->Release();
		g_pIdxBuffMeshFan = NULL;
	}

}
void UpdateMeshFan(void)
{

}

void DrawMeshFan(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();
	//計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;
	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_MeshFan.mtxWorld);
	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_MeshFan.rot.y, g_MeshFan.rot.x, g_MeshFan.rot.z);
	D3DXMatrixMultiply(&g_MeshFan.mtxWorld, &g_MeshFan.mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_MeshFan.pos.x, g_MeshFan.pos.y, g_MeshFan.pos.z);
	D3DXMatrixMultiply(&g_MeshFan.mtxWorld, &g_MeshFan.mtxWorld, &mtxTrans);

	pDevice->SetTransform(D3DTS_WORLD, &g_MeshFan.mtxWorld);
	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffMeshFan, 0, sizeof(VERTEX_3D));
	//インデックスバッファをデータストリームに設定
	pDevice->SetIndices(g_pIdxBuffMeshFan);
	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureMeshFan);
	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);
	//ポリゴンの描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLEFAN, 0, 0, CORNERCNT, 0, POLYCNT);
}
