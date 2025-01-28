#include "block.h"
//グローバル変数宣言
BLOCK g_Block[NUM_BLOCK];
BLOCKTEX g_BlockTex[BLOCK_MAX];
//初期化処理
void InitBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	pDevice = GetDevice();

	for (int nCnt = 0; nCnt < NUM_BLOCK; nCnt++)
	{
		//各種変数の初期化
		g_Block[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Block[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Block[nCnt].nType = BLOCK_HOUSE00_L;
		g_Block[nCnt].bUse = false;
	}


	for (int nCnt = 0; nCnt < BLOCK_MAX; nCnt++)
	{
		//xファイルの読み込み
		D3DXLoadMeshFromX(X_BLOCK[nCnt],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_BlockTex[nCnt].pBuffMat,
			NULL,
			&g_BlockTex[nCnt].dwNumMat,
			&g_BlockTex[nCnt].pMesh);
	}

	int nNumVtx=0;//頂点数
	DWORD sizeFVF;//頂点フォーマットのサイズ
	BYTE* pVtxBuff;//頂点バッファへのポインタ

	//頂点数の取得
	for (int nCnt = 0; nCnt < BLOCK_MAX; nCnt++)
	{

		nNumVtx = g_BlockTex[nCnt].pMesh->GetNumVertices();
		sizeFVF = D3DXGetFVFVertexSize(g_BlockTex[nCnt].pMesh->GetFVF());
		//頂点バッファのロック
		g_BlockTex[nCnt].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);
		
		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			//頂点座標の代入
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

			//頂点座標を比較してモデルの最小値最大値を取得
			//X============================
			if (vtx.x > g_BlockTex[nCnt].vtxMax.x)
			{
				g_BlockTex[nCnt].vtxMax.x = vtx.x;
			}

			if (vtx.x < g_BlockTex[nCnt].vtxMin.x)
			{
				g_BlockTex[nCnt].vtxMin.x = vtx.x;
			}
			//Y============================
			if (vtx.y > g_BlockTex[nCnt].vtxMax.y)
			{
				g_BlockTex[nCnt].vtxMax.y = vtx.y;
			}

			if (vtx.y < g_BlockTex[nCnt].vtxMin.y)
			{
				g_BlockTex[nCnt].vtxMin.y = vtx.y;
			}
			//Z=============================
			if (vtx.z > g_BlockTex[nCnt].vtxMax.z)
			{
				g_BlockTex[nCnt].vtxMax.z = vtx.z;
			}

			if (vtx.z < g_BlockTex[nCnt].vtxMin.z)
			{
				g_BlockTex[nCnt].vtxMin.z = vtx.z;
			}

			//頂点フォーマットのサイズ分ポインタを進める
			pVtxBuff += sizeFVF;
		}
		//頂点バッファのアンロック
		g_BlockTex[nCnt].pMesh->UnlockVertexBuffer();

		D3DXMATERIAL* pMat;//マテリアルへのポインタ

		//マテリアルデータへのポインタを取得
		pMat = (D3DXMATERIAL*)g_BlockTex[nCnt].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_BlockTex[nCnt].dwNumMat; nCntMat++)
		{
			if (pMat[nCntMat].pTextureFilename != NULL)
			{//テクスチャファイルが存在する
					//テクスチャの読み込み
				D3DXCreateTextureFromFile(pDevice,
					pMat[nCntMat].pTextureFilename,
					&g_BlockTex[nCnt].apTexture[nCntMat]);
			}
		}

	}
}
void UninitBlock(void)
{
	for (int nCntTex = 0; nCntTex < BLOCK_MAX; nCntTex++)
	{

		for (int nCntTexture = 0; nCntTexture < BLOCK_TEXTURE; nCntTexture++)
		{
			if (g_BlockTex[nCntTex].apTexture[nCntTexture] != NULL)
			{
				g_BlockTex[nCntTex].apTexture[nCntTexture]->Release();
				g_BlockTex[nCntTex].apTexture[nCntTexture] = NULL;

			}
		}
		if (g_BlockTex[nCntTex].pMesh != NULL)
		{
			g_BlockTex[nCntTex].pMesh->Release();
			g_BlockTex[nCntTex].pMesh = NULL;

		}
		//頂点バッファの解放
		if (g_BlockTex[nCntTex].pBuffMat != NULL)
		{
			g_BlockTex[nCntTex].pBuffMat->Release();
			g_BlockTex[nCntTex].pBuffMat = NULL;
		}

	}
	for (int nCntEdit = 0; nCntEdit < NUM_BLOCK; nCntEdit++)
	{

		for (int nCntTexture = 0; nCntTexture < BLOCK_TEXTURE; nCntTexture++)
		{
			if (g_Block[nCntEdit].tex.apTexture[nCntTexture] != NULL)
			{
				g_Block[nCntEdit].tex.apTexture[nCntTexture] = NULL;

			}
		}

		if (g_Block[nCntEdit].tex.pMesh != NULL)
		{
			g_Block[nCntEdit].tex.pMesh = NULL;

		}
		//頂点バッファの解放
		if (g_Block[nCntEdit].tex.pBuffMat != NULL)
		{
			g_Block[nCntEdit].tex.pBuffMat = NULL;
		}

	}
}
void UpdateBlock(void)
{

}
void DrawBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;
	//現在のマテリアルの保存用
	D3DMATERIAL9 matDef;//現在のマテリアルの保存用
	D3DXMATERIAL* pMat;//マテリアルデータへのポインタ
	for (int i = 0; i < BLOCK_MAX; i++)
	{

		for (int nCntBlock = 0; nCntBlock < NUM_BLOCK; nCntBlock++)
		{
			if (g_Block[nCntBlock].bUse == true)
			{
				//ワールドマトリックスの初期化
				D3DXMatrixIdentity(&g_Block[nCntBlock].mtxWorld);
				//向きを反映
				D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Block[nCntBlock].rot.y, g_Block[nCntBlock].rot.x, g_Block[nCntBlock].rot.z);
				D3DXMatrixMultiply(&g_Block[nCntBlock].mtxWorld, &g_Block[nCntBlock].mtxWorld, &mtxRot);

				//位置を反映
				D3DXMatrixTranslation(&mtxTrans, g_Block[nCntBlock].pos.x, g_Block[nCntBlock].pos.y, g_Block[nCntBlock].pos.z);
				D3DXMatrixMultiply(&g_Block[nCntBlock].mtxWorld, &g_Block[nCntBlock].mtxWorld, &mtxTrans);

				pDevice->SetTransform(D3DTS_WORLD, &g_Block[nCntBlock].mtxWorld);

				pDevice->GetMaterial(&matDef);
				//マテリアルデータへのポインタを取得
				pMat = (D3DXMATERIAL*)g_Block[nCntBlock].tex.pBuffMat->GetBufferPointer();

				for (int nCntMat = 0; nCntMat < (int)g_Block[nCntBlock].tex.dwNumMat; nCntMat++)
				{
					//マテリアルの設定
					pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

					//テクスチャの設定
					pDevice->SetTexture(0, g_Block[nCntBlock].tex.apTexture[nCntMat]);

					//モデル（パーツ）の描画
					g_Block[nCntBlock].tex.pMesh->DrawSubset(nCntMat);
				}
				pDevice->SetMaterial(&matDef);

			}

		}

	}
}


void SetBlock(D3DXVECTOR3 pos,int nType)
{
	for (int nCnt = 0; nCnt < NUM_BLOCK; nCnt++)
	{
		if (g_Block[nCnt].bUse == false)
		{
			g_Block[nCnt].pos = pos;
			g_Block[nCnt].nType = nType;
			g_Block[nCnt].tex = g_BlockTex[nType];
			g_Block[nCnt].bUse = true;
			break;
		}
	}
}
void CollisionBlock(D3DXVECTOR3* pPos,		//現在の位置
					D3DXVECTOR3* pPosOld)	//前回の位置
{					
	Player* pPlayer = GetPlayer();
	D3DXVECTOR3* posOld = pPosOld;		//前フレームのプレイヤーの位置
	D3DXVECTOR3* pos = pPos;			//現フレームのプレイヤーの位置




	for (int nCnt = 0; nCnt < NUM_BLOCK; nCnt++)
	{
		if (g_Block[nCnt].bUse == true)
		{
			//左右手前奥のめり込み判定
			if (pos->y< g_Block[nCnt].pos.y + g_Block[nCnt].tex.vtxMax.y && pos->y + (OBJ_P * 2.0f) > g_Block[nCnt].pos.y + g_Block[nCnt].tex.vtxMin.y)
			{
				//左右のめり込み判定
				if (pos->z - OBJ_P< g_Block[nCnt].pos.z + g_Block[nCnt].tex.vtxMax.z && pos->z + OBJ_P > g_Block[nCnt].pos.z + g_Block[nCnt].tex.vtxMin.z)//プレイヤーのｚの範囲がブロックに重なっている
				{

					if (posOld->x + OBJ_P< g_Block[nCnt].pos.x + g_Block[nCnt].tex.vtxMin.x && pos->x + OBJ_P > g_Block[nCnt].pos.x + g_Block[nCnt].tex.vtxMin.x)//Ｘが左から右にめり込んだ
					{
						//pPlayer->posをモデルの左側にくっつける
						pos->x = g_Block[nCnt].pos.x + g_Block[nCnt].tex.vtxMin.x - OBJ_P - 0.1f;

					}
					if (posOld->x - OBJ_P > g_Block[nCnt].pos.x + g_Block[nCnt].tex.vtxMax.x && pos->x - OBJ_P < g_Block[nCnt].pos.x + g_Block[nCnt].tex.vtxMax.x)//Ｘが左から右にめり込んだ
					{
						//pPlayer->posをモデルの右側にくっつける
						pos->x = g_Block[nCnt].pos.x + g_Block[nCnt].tex.vtxMax.x + OBJ_P + 0.1f;
					}
				}

				//手前奥のめり込み判定
				if (pos->x - OBJ_P< g_Block[nCnt].pos.x + g_Block[nCnt].tex.vtxMax.x && pos->x + OBJ_P > g_Block[nCnt].pos.x + g_Block[nCnt].tex.vtxMin.x)//プレイヤーxの範囲がブロックに重なっている
				{

					if (posOld->z + OBJ_P< g_Block[nCnt].pos.z + g_Block[nCnt].tex.vtxMin.z && pos->z + OBJ_P > g_Block[nCnt].pos.z + g_Block[nCnt].tex.vtxMin.z)//Zが下から上にめり込んだ
					{
						//pPlayer->posをモデルの手前側にくっつける
						pos->z = g_Block[nCnt].pos.z + g_Block[nCnt].tex.vtxMin.z - OBJ_P - 0.1f;
					}
					if (posOld->z - OBJ_P > g_Block[nCnt].pos.z + g_Block[nCnt].tex.vtxMax.z && pos->z - OBJ_P < g_Block[nCnt].pos.z + g_Block[nCnt].tex.vtxMax.z)//Zが上から下にめり込んだ
					{
						//pPlayer->posをモデルの奥側にくっつける
						pos->z = g_Block[nCnt].pos.z + g_Block[nCnt].tex.vtxMax.z + OBJ_P + 0.1f;
					}
				}

			}
			if (pos->z - OBJ_P< g_Block[nCnt].pos.z + g_Block[nCnt].tex.vtxMax.z && pos->z + OBJ_P > g_Block[nCnt].pos.z + g_Block[nCnt].tex.vtxMin.z
				&& pos->x - OBJ_P< g_Block[nCnt].pos.x + g_Block[nCnt].tex.vtxMax.x && pos->x + OBJ_P > g_Block[nCnt].pos.x + g_Block[nCnt].tex.vtxMin.x)
			{
				if (posOld->y + (OBJ_P * 2.0f) < g_Block[nCnt].pos.y + g_Block[nCnt].tex.vtxMin.y && pos->y + (OBJ_P * 2.0f) > g_Block[nCnt].pos.y + g_Block[nCnt].tex.vtxMin.y)//Ｘが左から右にめり込んだ
				{
					//pPlayer->posをモデルの下側にくっつける
					pos->y = g_Block[nCnt].pos.y + g_Block[nCnt].tex.vtxMin.y - (OBJ_P * 2.0f) - 0.1f;
				}
				if (posOld->y > g_Block[nCnt].pos.y + g_Block[nCnt].tex.vtxMax.y && pos->y < g_Block[nCnt].pos.y + g_Block[nCnt].tex.vtxMax.y)//Ｘが左から右にめり込んだ
				{
					//pPlayer->posをモデルの上側にくっつける
					pos->y = g_Block[nCnt].pos.y + g_Block[nCnt].tex.vtxMax.y + 0.1f;
				}

			}

		}

	}


}

