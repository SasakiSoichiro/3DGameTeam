
//#include "edit.h"
////グローバル変数宣言
//EDITINFO g_Edit[NUM_BLOCK];
//EDITTEX g_EditTex[EDIT_MAX];
////初期化処理
//void InitBlock(void)
//{
//	LPDIRECT3DDEVICE9 pDevice;
//
//	pDevice = GetDevice();
//
//
//	for (int nCnt = 0; nCnt < NUM_BLOCK; nCnt++)
//	{
//		//各種変数の初期化
//		g_Edit[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//		g_Edit[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//		g_Edit[nCnt].nType = BLOCK_HOUSE00;
//		g_Edit[nCnt].bUse = false;
//	}
//
//
//	for (int nCnt = 0; nCnt <EDIT_MAX; nCnt++)
//	{
//		//xファイルの読み込み
//		D3DXLoadMeshFromX(X_EDIT[nCnt],
//			D3DXMESH_SYSTEMMEM,
//			pDevice,
//			NULL,
//			&g_EditTex[nCnt].pBuffMat,
//			NULL,
//			&g_EditTex[nCnt].dwNumMat,
//			&g_EditTex[nCnt].pMesh);
//	}
//
//	//マテリアルの取得
//	for (int nCnt = 0; nCnt < BLOCK_MAX; nCnt++)
//	{
//
//			D3DXMATERIAL* pMat;//マテリアルへのポインタ
//
//			//マテリアルデータへのポインタを取得
//			pMat = (D3DXMATERIAL*)g_EditTex[nCnt].pBuffMat->GetBufferPointer();
//
//			for (int nCntMat = 0; nCntMat < (int)g_EditTex[nCnt].dwNumMat; nCntMat++)
//			{
//				if (pMat[nCntMat].pTextureFilename != NULL)
//				{//テクスチャファイルが存在する
//						//テクスチャの読み込み
//					D3DXCreateTextureFromFile(pDevice,
//						pMat[nCntMat].pTextureFilename,
//						&g_EditTex[nCnt].apTexture[nCntMat]);
//				}
//			}
//
//	}
//}
//void UninitBlock(void)
//{
//	for (int nCntTex = 0; nCntTex < BLOCK_MAX; nCntTex++)
//	{
//
//		for (int nCntTexture = 0; nCntTexture < EDITTEXTURE; nCntTexture++)
//		{
//			if (g_EditTex[nCntTex].apTexture[nCntTexture] != NULL)
//			{
//				g_EditTex[nCntTex].apTexture[nCntTexture]->Release();
//				g_EditTex[nCntTex].apTexture[nCntTexture] = NULL;
//
//			}
//		}
//		if (g_EditTex[nCntTex].pMesh != NULL)
//		{
//			g_EditTex[nCntTex].pMesh->Release();
//			g_EditTex[nCntTex].pMesh = NULL;
//
//		}
//		//頂点バッファの解放
//		if (g_EditTex[nCntTex].pBuffMat != NULL)
//		{
//			g_EditTex[nCntTex].pBuffMat->Release();
//			g_EditTex[nCntTex].pBuffMat = NULL;
//		}
//
//	}
//	for (int nCntEdit = 0; nCntEdit < NUM_EDIT; nCntEdit++)
//	{
//		for (int nCntType = 0; nCntType < EDIT_MAX; nCntType++)
//		{
//			for (int nCntTexture = 0; nCntTexture < EDITTEXTURE; nCntTexture++)
//			{
//				if (g_Edit[nCntEdit].tex[nCntType].apTexture[nCntTexture] != NULL)
//				{
//					g_Edit[nCntEdit].tex[nCntType].apTexture[nCntTexture] = NULL;
//
//				}
//			}
//
//			if (g_Edit[nCntEdit].tex[nCntType].pMesh != NULL)
//			{
//				g_Edit[nCntEdit].tex[nCntType].pMesh = NULL;
//
//			}
//			//頂点バッファの解放
//			if (g_Edit[nCntEdit].tex[nCntType].pBuffMat != NULL)
//			{
//				g_Edit[nCntEdit].tex[nCntType].pBuffMat = NULL;
//			}
//
//		}
//	}
//
//
//
//
//}
//void UpdateBlock(void)
//{
//
//}
//void DrawBlock(void)
//{
//	LPDIRECT3DDEVICE9 pDevice;
//	pDevice = GetDevice();
//
//	//計算用マトリックス
//	D3DXMATRIX mtxRot, mtxTrans;
//	//現在のマテリアルの保存用
//	D3DMATERIAL9 matDef;//現在のマテリアルの保存用
//	D3DXMATERIAL* pMat;//マテリアルデータへのポインタ
//
//
//	for (int nCntBlock = 0; nCntBlock < NUM_BLOCK; nCntBlock++)
//	{
//		if (g_Edit[i][nCntBlock].bUse == true)
//		{
//			//ワールドマトリックスの初期化
//			D3DXMatrixIdentity(&g_Edit[i][nCntBlock].mtxWorld);
//			//向きを反映
//			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Edit[i][nCntBlock].rot.y, g_Edit[i][nCntBlock].rot.x, g_Edit[i][nCntBlock].rot.z);
//			D3DXMatrixMultiply(&g_Edit[i][nCntBlock].mtxWorld, &g_Edit[i][nCntBlock].mtxWorld, &mtxRot);
//
//			//位置を反映
//			D3DXMatrixTranslation(&mtxTrans, g_Edit[i][nCntBlock].pos.x, g_Edit[i][nCntBlock].pos.y, g_Edit[i][nCntBlock].pos.z);
//			D3DXMatrixMultiply(&g_Edit[i][nCntBlock].mtxWorld, &g_Edit[i][nCntBlock].mtxWorld, &mtxTrans);
//
//			pDevice->SetTransform(D3DTS_WORLD, &g_Edit[i][nCntBlock].mtxWorld);
//
//			pDevice->GetMaterial(&matDef);
//			//マテリアルデータへのポインタを取得
//			pMat = (D3DXMATERIAL*)g_Edit[i][nCntBlock].pBuffMat->GetBufferPointer();
//
//			for (int nCntMat = 0; nCntMat < (int)g_Edit[i][nCntBlock].dwNumMat; nCntMat++)
//			{
//				//マテリアルの設定
//				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
//
//				//テクスチャの設定
//				pDevice->SetTexture(0, g_Edit[i][nCntBlock].apTexture[nCntMat]);
//
//				//モデル（パーツ）の描画
//				g_Edit[i][nCntBlock].pMesh->DrawSubset(nCntMat);
//			}
//			pDevice->SetMaterial(&matDef);
//
//		}
//
//	}
//
//}
//
//
//void SetBlock(D3DXVECTOR3 pos, int nType)
//{
//	for (int nCnt = 0; nCnt < NUM_BLOCK; nCnt++)
//	{
//		if (g_Edit[nType][nCnt].bUse == false)
//		{
//			g_Edit[nType][nCnt].pos = pos;
//			g_Edit[nType][nCnt].nType = nType;
//			g_Edit[nType][nCnt].bUse = true;
//			break;
//		}
//	}
//}
//void CollisionBlock(D3DXVECTOR3* pPos,		//現在の位置
//	D3DXVECTOR3* pPosOld)	//前回の位置
//{
//	Player* pPlayer = GetPlayer();
//	D3DXVECTOR3* posOld = pPosOld;		//前フレームのプレイヤーの位置
//	D3DXVECTOR3* pos = pPos;			//現フレームのプレイヤーの位置
//
//
//
//	for (int i = 0; i < BLOCK_MAX; i++)
//	{
//		for (int nCnt = 0; nCnt < NUM_BLOCK; nCnt++)
//		{
//			if (g_Edit[i][nCnt].bUse == true)
//			{
//				//左右手前奥のめり込み判定
//				if (pos->y< g_Edit[i][nCnt].pos.y + g_Edit[i][nCnt].vtxMax.y && pos->y + (OBJ_P * 2.0f) > g_Edit[i][nCnt].pos.y + g_Edit[i][nCnt].vtxMin.y)
//				{
//					//左右のめり込み判定
//					if (pos->z - OBJ_P< g_Edit[i][nCnt].pos.z + g_Edit[i][nCnt].vtxMax.z && pos->z + OBJ_P > g_Edit[i][nCnt].pos.z + g_Edit[i][nCnt].vtxMin.z)//プレイヤーのｚの範囲がブロックに重なっている
//					{
//
//						if (posOld->x + OBJ_P< g_Edit[i][nCnt].pos.x + g_Edit[i][nCnt].vtxMin.x && pos->x + OBJ_P > g_Edit[i][nCnt].pos.x + g_Edit[i][nCnt].vtxMin.x)//Ｘが左から右にめり込んだ
//						{
//							//pPlayer->posをモデルの左側にくっつける
//							pos->x = g_Edit[i][nCnt].pos.x + g_Edit[i][nCnt].vtxMin.x - OBJ_P - 0.1f;
//
//						}
//						if (posOld->x - OBJ_P > g_Edit[i][nCnt].pos.x + g_Edit[i][nCnt].vtxMax.x && pos->x - OBJ_P < g_Edit[i][nCnt].pos.x + g_Edit[i][nCnt].vtxMax.x)//Ｘが左から右にめり込んだ
//						{
//							//pPlayer->posをモデルの右側にくっつける
//							pos->x = g_Edit[i][nCnt].pos.x + g_Edit[i][nCnt].vtxMax.x + OBJ_P + 0.1f;
//						}
//					}
//
//					//手前奥のめり込み判定
//					if (pos->x - OBJ_P< g_Edit[i][nCnt].pos.x + g_Edit[i][nCnt].vtxMax.x && pos->x + OBJ_P > g_Edit[i][nCnt].pos.x + g_Edit[i][nCnt].vtxMin.x)//プレイヤーxの範囲がブロックに重なっている
//					{
//
//						if (posOld->z + OBJ_P< g_Edit[i][nCnt].pos.z + g_Edit[i][nCnt].vtxMin.z && pos->z + OBJ_P > g_Edit[i][nCnt].pos.z + g_Edit[i][nCnt].vtxMin.z)//Zが下から上にめり込んだ
//						{
//							//pPlayer->posをモデルの手前側にくっつける
//							pos->z = g_Edit[i][nCnt].pos.z + g_Edit[i][nCnt].vtxMin.z - OBJ_P - 0.1f;
//						}
//						if (posOld->z - OBJ_P > g_Edit[i][nCnt].pos.z + g_Edit[i][nCnt].vtxMax.z && pos->z - OBJ_P < g_Edit[i][nCnt].pos.z + g_Edit[i][nCnt].vtxMax.z)//Zが上から下にめり込んだ
//						{
//							//pPlayer->posをモデルの奥側にくっつける
//							pos->z = g_Edit[i][nCnt].pos.z + g_Edit[i][nCnt].vtxMax.z + OBJ_P + 0.1f;
//						}
//					}
//
//				}
//				if (pos->z - OBJ_P< g_Edit[i][nCnt].pos.z + g_Edit[i][nCnt].vtxMax.z && pos->z + OBJ_P > g_Edit[i][nCnt].pos.z + g_Edit[i][nCnt].vtxMin.z
//					&& pos->x - OBJ_P< g_Edit[i][nCnt].pos.x + g_Edit[i][nCnt].vtxMax.x && pos->x + OBJ_P > g_Edit[i][nCnt].pos.x + g_Edit[i][nCnt].vtxMin.x)
//				{
//					if (posOld->y + (OBJ_P * 2.0f) < g_Edit[i][nCnt].pos.y + g_Edit[i][nCnt].vtxMin.y && pos->y + (OBJ_P * 2.0f) > g_Edit[i][nCnt].pos.y + g_Edit[i][nCnt].vtxMin.y)//Ｘが左から右にめり込んだ
//					{
//						//pPlayer->posをモデルの下側にくっつける
//						pos->y = g_Edit[i][nCnt].pos.y + g_Edit[i][nCnt].vtxMin.y - (OBJ_P * 2.0f) - 0.1f;
//					}
//					if (posOld->y > g_Edit[i][nCnt].pos.y + g_Edit[i][nCnt].vtxMax.y && pos->y < g_Edit[i][nCnt].pos.y + g_Edit[i][nCnt].vtxMax.y)//Ｘが左から右にめり込んだ
//					{
//						//pPlayer->posをモデルの上側にくっつける
//						pos->y = g_Edit[i][nCnt].pos.y + g_Edit[i][nCnt].vtxMax.y + 0.1f;
//					}
//
//				}
//
//			}
//
//		}
//
//	}
//
//
//}
