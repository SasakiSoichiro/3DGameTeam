#include "block.h"
//グローバル変数宣言
BLOCK g_Block[BLOCK_MAX][NUM_BLOCK];
BoolPressurePlate g_bPlate;
//初期化処理
void InitBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	pDevice = GetDevice();

	g_bPlate.red = true;
	g_bPlate.blue = false;
	g_bPlate.green = false;

	for (int i = 0; i < BLOCK_MAX; i++)
	{
		for (int nCnt = 0; nCnt < NUM_BLOCK; nCnt++)
		{
			//各種変数の初期化
			g_Block[i][nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_Block[i][nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_Block[i][nCnt].nType = BLOCK_NORMAL;
			g_Block[i][nCnt].bUse = false;
		}

	}
	for (int i = 0; i < BLOCK_MAX; i++)
	{
		for (int nCnt = 0; nCnt < NUM_BLOCK; nCnt++)
		{
			//xファイルの読み込み
			D3DXLoadMeshFromX(X_BLOCK[i],
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&g_Block[i][nCnt].pBuffMat,
				NULL,
				&g_Block[i][nCnt].dwNumMat,
				&g_Block[i][nCnt].pMesh);

		}

	}

	int nNumVtx;//頂点数
	DWORD sizeFVF;//頂点フォーマットのサイズ
	BYTE* pVtxBuff;//頂点バッファへのポインタ

	//頂点数の取得
	for (int i = 0; i < BLOCK_MAX; i++)
	{
		for (int nCnt = 0; nCnt < NUM_BLOCK; nCnt++)
		{
			nNumVtx = g_Block[i][nCnt].pMesh->GetNumVertices();
			sizeFVF = D3DXGetFVFVertexSize(g_Block[i][nCnt].pMesh->GetFVF());
			//頂点バッファのロック
			g_Block[i][nCnt].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);
			
			for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
			{
				//頂点座標の代入
				D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

				//頂点座標を比較してモデルの最小値最大値を取得
				//X============================
				if (vtx.x > g_Block[i][nCnt].vtxMax.x)
				{
					g_Block[i][nCnt].vtxMax.x = vtx.x;
				}

				if (vtx.x < g_Block[i][nCnt].vtxMin.x)
				{
					g_Block[i][nCnt].vtxMin.x = vtx.x;
				}
				//Y============================
				if (vtx.y > g_Block[i][nCnt].vtxMax.y)
				{
					g_Block[i][nCnt].vtxMax.y = vtx.y;
				}

				if (vtx.y < g_Block[i][nCnt].vtxMin.y)
				{
					g_Block[i][nCnt].vtxMin.y = vtx.y;
				}
				//Z=============================
				if (vtx.z > g_Block[i][nCnt].vtxMax.z)
				{
					g_Block[i][nCnt].vtxMax.z = vtx.z;
				}

				if (vtx.z < g_Block[i][nCnt].vtxMin.z)
				{
					g_Block[i][nCnt].vtxMin.z = vtx.z;
				}

				//頂点フォーマットのサイズ分ポインタを進める
				pVtxBuff += sizeFVF;
			}
			//頂点バッファのアンロック
			g_Block[i][nCnt].pMesh->UnlockVertexBuffer();

			D3DXMATERIAL* pMat;//マテリアルへのポインタ

			//マテリアルデータへのポインタを取得
			pMat = (D3DXMATERIAL*)g_Block[i][nCnt].pBuffMat->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_Block[i][nCnt].dwNumMat; nCntMat++)
			{
				if (pMat[nCntMat].pTextureFilename != NULL)
				{//テクスチャファイルが存在する
						//テクスチャの読み込み
					D3DXCreateTextureFromFile(pDevice,
						pMat[nCntMat].pTextureFilename,
						&g_Block[i][nCnt].apTexture[nCntMat]);
				}
			}

		}

	}
}
void UninitBlock(void)
{
	for (int i = 0; i < BLOCK_MAX; i++)
	{

		for (int nCnt = 0; nCnt < NUM_BLOCK; nCnt++)
		{
			if (g_Block[i][nCnt].pMesh != NULL)
			{
				g_Block[i][nCnt].pMesh->Release();
				g_Block[i][nCnt].pMesh = NULL;

			}
			//頂点バッファの解放
			if (g_Block[i][nCnt].pBuffMat != NULL)
			{
				g_Block[i][nCnt].pBuffMat->Release();
				g_Block[i][nCnt].pBuffMat = NULL;
			}

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
			if (g_Block[i][nCntBlock].bUse == true)
			{
				//ワールドマトリックスの初期化
				D3DXMatrixIdentity(&g_Block[i][nCntBlock].mtxWorld);
				//向きを反映
				D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Block[i][nCntBlock].rot.y, g_Block[i][nCntBlock].rot.x, g_Block[i][nCntBlock].rot.z);
				D3DXMatrixMultiply(&g_Block[i][nCntBlock].mtxWorld, &g_Block[i][nCntBlock].mtxWorld, &mtxRot);

				//位置を反映
				D3DXMatrixTranslation(&mtxTrans, g_Block[i][nCntBlock].pos.x, g_Block[i][nCntBlock].pos.y, g_Block[i][nCntBlock].pos.z);
				D3DXMatrixMultiply(&g_Block[i][nCntBlock].mtxWorld, &g_Block[i][nCntBlock].mtxWorld, &mtxTrans);

				pDevice->SetTransform(D3DTS_WORLD, &g_Block[i][nCntBlock].mtxWorld);

				pDevice->GetMaterial(&matDef);
				//マテリアルデータへのポインタを取得
				pMat = (D3DXMATERIAL*)g_Block[i][nCntBlock].pBuffMat->GetBufferPointer();

				for (int nCntMat = 0; nCntMat < (int)g_Block[i][nCntBlock].dwNumMat; nCntMat++)
				{
					//マテリアルの設定
					pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

					//テクスチャの設定
					pDevice->SetTexture(0, g_Block[i][nCntBlock].apTexture[nCntMat]);

					//モデル（パーツ）の描画
					g_Block[i][nCntBlock].pMesh->DrawSubset(nCntMat);
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
		if (g_Block[nType][nCnt].bUse == false)
		{
			g_Block[nType][nCnt].pos = pos;
			g_Block[nType][nCnt].nType = nType;
			g_Block[nType][nCnt].bUse = true;
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



	for (int i = 0; i < BLOCK_MAX; i++)
	{
		for (int nCnt = 0; nCnt < NUM_BLOCK; nCnt++)
		{
			if (g_Block[i][nCnt].bUse == true)
			{
				//左右手前奥のめり込み判定
				if (pos->y< g_Block[i][nCnt].pos.y + g_Block[i][nCnt].vtxMax.y && pos->y + (OBJ_P * 2.0f) > g_Block[i][nCnt].pos.y + g_Block[i][nCnt].vtxMin.y)
				{
					//左右のめり込み判定
					if (pos->z - OBJ_P< g_Block[i][nCnt].pos.z + g_Block[i][nCnt].vtxMax.z && pos->z + OBJ_P > g_Block[i][nCnt].pos.z + g_Block[i][nCnt].vtxMin.z)//プレイヤーのｚの範囲がブロックに重なっている
					{

						if (posOld->x + OBJ_P< g_Block[i][nCnt].pos.x + g_Block[i][nCnt].vtxMin.x && pos->x + OBJ_P > g_Block[i][nCnt].pos.x + g_Block[i][nCnt].vtxMin.x)//Ｘが左から右にめり込んだ
						{
							//pPlayer->posをモデルの左側にくっつける
							pos->x = g_Block[i][nCnt].pos.x + g_Block[i][nCnt].vtxMin.x - OBJ_P - 0.1f;

							GimmickBlock(i);

						}
						if (posOld->x - OBJ_P > g_Block[i][nCnt].pos.x + g_Block[i][nCnt].vtxMax.x && pos->x - OBJ_P < g_Block[i][nCnt].pos.x + g_Block[i][nCnt].vtxMax.x)//Ｘが左から右にめり込んだ
						{
							//pPlayer->posをモデルの右側にくっつける
							pos->x = g_Block[i][nCnt].pos.x + g_Block[i][nCnt].vtxMax.x + OBJ_P + 0.1f;
							GimmickBlock(i);
						}
					}

					//手前奥のめり込み判定
					if (pos->x - OBJ_P< g_Block[i][nCnt].pos.x + g_Block[i][nCnt].vtxMax.x && pos->x + OBJ_P > g_Block[i][nCnt].pos.x + g_Block[i][nCnt].vtxMin.x)//プレイヤーxの範囲がブロックに重なっている
					{

						if (posOld->z + OBJ_P< g_Block[i][nCnt].pos.z + g_Block[i][nCnt].vtxMin.z && pos->z + OBJ_P > g_Block[i][nCnt].pos.z + g_Block[i][nCnt].vtxMin.z)//Zが下から上にめり込んだ
						{
							//pPlayer->posをモデルの手前側にくっつける
							pos->z = g_Block[i][nCnt].pos.z + g_Block[i][nCnt].vtxMin.z - OBJ_P - 0.1f;
							GimmickBlock(i);
						}
						if (posOld->z - OBJ_P > g_Block[i][nCnt].pos.z + g_Block[i][nCnt].vtxMax.z && pos->z - OBJ_P < g_Block[i][nCnt].pos.z + g_Block[i][nCnt].vtxMax.z)//Zが上から下にめり込んだ
						{
							//pPlayer->posをモデルの奥側にくっつける
							pos->z = g_Block[i][nCnt].pos.z + g_Block[i][nCnt].vtxMax.z + OBJ_P + 0.1f;
							GimmickBlock(i);
						}
					}

				}
				if (pos->z - OBJ_P< g_Block[i][nCnt].pos.z + g_Block[i][nCnt].vtxMax.z && pos->z + OBJ_P > g_Block[i][nCnt].pos.z + g_Block[i][nCnt].vtxMin.z
					&& pos->x - OBJ_P< g_Block[i][nCnt].pos.x + g_Block[i][nCnt].vtxMax.x && pos->x + OBJ_P > g_Block[i][nCnt].pos.x + g_Block[i][nCnt].vtxMin.x)
				{
					if (posOld->y + (OBJ_P * 2.0f) < g_Block[i][nCnt].pos.y + g_Block[i][nCnt].vtxMin.y && pos->y + (OBJ_P * 2.0f) > g_Block[i][nCnt].pos.y + g_Block[i][nCnt].vtxMin.y)//Ｘが左から右にめり込んだ
					{
						//pPlayer->posをモデルの下側にくっつける
						pos->y = g_Block[i][nCnt].pos.y + g_Block[i][nCnt].vtxMin.y - (OBJ_P * 2.0f) - 0.1f;
						GimmickBlock(i);
					}
					if (posOld->y > g_Block[i][nCnt].pos.y + g_Block[i][nCnt].vtxMax.y && pos->y < g_Block[i][nCnt].pos.y + g_Block[i][nCnt].vtxMax.y)//Ｘが左から右にめり込んだ
					{
						//pPlayer->posをモデルの上側にくっつける
						pos->y = g_Block[i][nCnt].pos.y + g_Block[i][nCnt].vtxMax.y + 0.1f;
						GimmickBlock(i);
					}

				}

			}

		}

	}


}

void GimmickBlock(int nType)
{
	int Type = nType;
	switch(Type)
	{
	case BLOCK_PRESSUREPLATERED:
		g_bPlate.red = true;
		g_bPlate.blue = false;
		g_bPlate.green = false;

		break;
	case BLOCK_PRESSUREPLATEBLUE:
		g_bPlate.red = false;
		g_bPlate.blue = true;
		g_bPlate.green = false;
		break;
	case BLOCK_PRESSUREPLATEGREEN:
		g_bPlate.red = false;
		g_bPlate.blue = false;
		g_bPlate.green = true;
		break;
	default:
		break;
	}
}

BoolPressurePlate GetPlate(void)
{
	return g_bPlate;
}
