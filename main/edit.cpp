#include "block.h"
#include "edit.h"
#include "input.h"
//グローバル変数宣言
EDITINFO g_Edit[NUM_BLOCK];
EDITTEX g_EditTex[EDIT_MAX];
int g_EditCnt;
int g_nReloadCnt;
//初期化処理
void InitEdit(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	pDevice = GetDevice();


	for (int nCnt = 0; nCnt < NUM_BLOCK; nCnt++)
	{
		//各種変数の初期化
		g_Edit[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Edit[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Edit[nCnt].nType = BLOCK_HOUSE00;
		g_Edit[nCnt].bUse = false;
	}


	for (int nCnt = 0; nCnt <EDIT_MAX; nCnt++)
	{
		//xファイルの読み込み
		D3DXLoadMeshFromX(X_EDIT[nCnt],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_EditTex[nCnt].pBuffMat,
			NULL,
			&g_EditTex[nCnt].dwNumMat,
			&g_EditTex[nCnt].pMesh);
	}

	//マテリアルの取得
	for (int nCnt = 0; nCnt < BLOCK_MAX; nCnt++)
	{

			D3DXMATERIAL* pMat;//マテリアルへのポインタ

			//マテリアルデータへのポインタを取得
			pMat = (D3DXMATERIAL*)g_EditTex[nCnt].pBuffMat->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_EditTex[nCnt].dwNumMat; nCntMat++)
			{
				if (pMat[nCntMat].pTextureFilename != NULL)
				{//テクスチャファイルが存在する
						//テクスチャの読み込み
					D3DXCreateTextureFromFile(pDevice,
						pMat[nCntMat].pTextureFilename,
						&g_EditTex[nCnt].apTexture[nCntMat]);
				}
			}

	}

	//1番目をtrueにする
	g_Edit[0].bUse = true;

	//変数を代入する
	g_Edit[0].tex[0] = g_EditTex[0];

	//カウントを初期化する
	g_EditCnt = 0;
}
void UninitEdit(void)
{
	for (int nCntTex = 0; nCntTex < BLOCK_MAX; nCntTex++)
	{

		for (int nCntTexture = 0; nCntTexture < EDITTEXTURE; nCntTexture++)
		{
			if (g_EditTex[nCntTex].apTexture[nCntTexture] != NULL)
			{
				g_EditTex[nCntTex].apTexture[nCntTexture]->Release();
				g_EditTex[nCntTex].apTexture[nCntTexture] = NULL;

			}
		}
		if (g_EditTex[nCntTex].pMesh != NULL)
		{
			g_EditTex[nCntTex].pMesh->Release();
			g_EditTex[nCntTex].pMesh = NULL;

		}
		//頂点バッファの解放
		if (g_EditTex[nCntTex].pBuffMat != NULL)
		{
			g_EditTex[nCntTex].pBuffMat->Release();
			g_EditTex[nCntTex].pBuffMat = NULL;
		}

	}
	for (int nCntEdit = 0; nCntEdit < NUM_EDIT; nCntEdit++)
	{
		for (int nCntType = 0; nCntType < EDIT_MAX; nCntType++)
		{
			for (int nCntTexture = 0; nCntTexture < EDITTEXTURE; nCntTexture++)
			{
				if (g_Edit[nCntEdit].tex[nCntType].apTexture[nCntTexture] != NULL)
				{
					g_Edit[nCntEdit].tex[nCntType].apTexture[nCntTexture] = NULL;

				}
			}

			if (g_Edit[nCntEdit].tex[nCntType].pMesh != NULL)
			{
				g_Edit[nCntEdit].tex[nCntType].pMesh = NULL;

			}
			//頂点バッファの解放
			if (g_Edit[nCntEdit].tex[nCntType].pBuffMat != NULL)
			{
				g_Edit[nCntEdit].tex[nCntType].pBuffMat = NULL;
			}

		}
	}




}
void UpdateEdit(void)
{

	if (g_Edit[g_EditCnt].bUse == true)
	{
		g_Edit[g_EditCnt].pos.x += g_Edit[g_EditCnt].move.x;

		if (GetKeyboardPress(DIK_A) == true)
		{
			g_Edit[g_EditCnt].move.x -= 2.0f;
		}

		if (KeybordTrigger(DIK_RETURN) == true)
		{
			g_Edit[g_EditCnt + 1].pos = g_Edit[g_EditCnt].pos;

			g_Edit[g_EditCnt + 1].bUse = true;

			g_Edit[g_EditCnt + 1].tex[g_Edit[g_EditCnt + 1].nType] =g_EditTex[g_Edit[g_EditCnt].nType];

			g_EditCnt++;


		}

	}

	if (KeybordTrigger(DIK_F7) == true)
	{
		SaveEdit();
	}
	if (KeybordTrigger(DIK_F8) == true)
	{
		ReloadEdit();
	}
}
void DrawEdit(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;
	//現在のマテリアルの保存用
	D3DMATERIAL9 matDef;//現在のマテリアルの保存用
	D3DXMATERIAL* pMat;//マテリアルデータへのポインタ


	for (int nCntBlock = 0; nCntBlock < NUM_BLOCK; nCntBlock++)
	{
		if (g_Edit[nCntBlock].bUse == false)
		{
			continue;
		}
		int nType = g_Edit[nCntBlock].nType;
		//ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_Edit[nCntBlock].mtxWorld);
		//向きを反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Edit[nCntBlock].rot.y, g_Edit[nCntBlock].rot.x, g_Edit[nCntBlock].rot.z);
		D3DXMatrixMultiply(&g_Edit[nCntBlock].mtxWorld, &g_Edit[nCntBlock].mtxWorld, &mtxRot);

		//位置を反映
		D3DXMatrixTranslation(&mtxTrans, g_Edit[nCntBlock].pos.x, g_Edit[nCntBlock].pos.y, g_Edit[nCntBlock].pos.z);
		D3DXMatrixMultiply(&g_Edit[nCntBlock].mtxWorld, &g_Edit[nCntBlock].mtxWorld, &mtxTrans);

		pDevice->SetTransform(D3DTS_WORLD, &g_Edit[nCntBlock].mtxWorld);

		pDevice->GetMaterial(&matDef);
		//マテリアルデータへのポインタを取得
		pMat = (D3DXMATERIAL*)g_Edit[nCntBlock].tex[nType].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_Edit[nCntBlock].tex[nType].dwNumMat; nCntMat++)
		{
			//マテリアルの設定
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			//テクスチャの設定
			pDevice->SetTexture(0, g_Edit[nCntBlock].tex[nType].apTexture[nCntMat]);

			//モデル（パーツ）の描画
			g_Edit[nCntBlock].tex[nType].pMesh->DrawSubset(nCntMat);
		}
		pDevice->SetMaterial(&matDef);

	}

}

void SaveEdit(void)
{
	//ファイルポインタを宣言
	FILE* pFile;

	D3DXVECTOR3 pos = {};
	int nType = 0;


	pFile = fopen(TEXTFILE, "w");

	if (pFile != NULL)
	{
		fwrite(&g_EditCnt, sizeof(int), 0, pFile);

		for (int nCnt = 0; nCnt < g_EditCnt; nCnt++)
		{
			if (g_Edit[nCnt].bUse == true)
			{
				fprintf(pFile, "BLOCKSET\n\n");
				fprintf(pFile, "POS %f %f %f\n\n", g_Edit[nCnt].pos.x, g_Edit[nCnt].pos.y, g_Edit[nCnt].pos.z);
				fprintf(pFile, "TYPE %d\n\n", g_Edit[nCnt].nType);
				fprintf(pFile, "END_BLOCKSET\n\n");
			}
		}
		fprintf(pFile, "EDITCNT %d\n\n",g_EditCnt);
		fprintf(pFile, "END_SCRIPT\n\n\n");
		fclose(pFile);
	}
	else
	{//開けなかったときの処理
		return;
	}

}

void LoadEdit(void)
{
	FILE* pFile;

	D3DXVECTOR3 pos = {};
	int nType = 0;
	pFile = fopen(TEXTFILE, "r");

	if (pFile != NULL)
	{
		char aString[MAX_WORD];//文字数を格納
		//全部のテキストに書かれた情報を読み取りが終わるまで回す
		while (1)
		{
			//ファイルを読み込む
			fscanf(pFile, "%s", &aString[0]);

			//読み取る特定の文字列が一致していたら
			if (strcmp(aString, "BLOCKSET") == 0)
			{
				while (1)
				{
					//ファイルを読み込む
					fscanf(pFile, "%s", &aString[0]);

					if (strcmp(aString, "POS") == 0)
					{//POSを読み取ったら
						fscanf(pFile, "%f", &pos.x);
						fscanf(pFile, "%f", &pos.y);
						fscanf(pFile, "%f", &pos.z);
					}
					else if (strcmp(aString, "TYPE") == 0)
					{
						fscanf(pFile, "%d", &nType);
					}

					else if (strcmp(aString, "END_BLOCKSET") == 0)
					{
						SetBlock(pos,nType);
						break;
					}
				}
			}
			else if (strcmp(aString, "EDITCNT") == 0)
			{
				fscanf(pFile, "%d", &g_nReloadCnt);
			}
			if (strcmp(aString, "END_SCRIPT") == 0)
			{
				//whileを抜けるため
				break;
			}
		}
		//ファイルを閉じる
		fclose(pFile);
	}
	else
	{//開けなかったときの処理
		return;
	}

}

void ReloadEdit(void)
{
	FILE* pFile;

	D3DXVECTOR3 pos = {};
	int nCnt = 0;
	pFile = fopen(TEXTFILE, "r");

	if (pFile != NULL)
	{
		char aString[MAX_WORD];//文字数を格納
		//全部のテキストに書かれた情報を読み取りが終わるまで回す
		while (1)
		{
			//ファイルを読み込む
			fscanf(pFile, "%s", &aString[0]);

			//読み取る特定の文字列が一致していたら
			if (strcmp(aString, "BLOCKSET") == 0)
			{
				while (1)
				{
					//ファイルを読み込む
					fscanf(pFile, "%s", &aString[0]);

					if (strcmp(aString, "POS") == 0)
					{//POSを読み取ったら
						fscanf(pFile, "%f", &g_Edit[nCnt].pos.x);
						fscanf(pFile, "%f", &g_Edit[nCnt].pos.y);
						fscanf(pFile, "%f", &g_Edit[nCnt].pos.z);
					}
					else if (strcmp(aString, "TYPE") == 0)
					{
						fscanf(pFile, "%d", &g_Edit[nCnt].nType);
					}

					else if (strcmp(aString, "END_BLOCKSET") == 0)
					{
						nCnt++;
						break;
					}
				}
			}
			if (strcmp(aString, "EDITCNT") == 0)
			{
				fscanf(pFile, "%d", &g_nReloadCnt);
			}
			if (strcmp(aString, "END_SCRIPT") == 0)
			{
				//whileを抜けるため
				break;
			}
		}
		//ファイルを閉じる
		fclose(pFile);
	}
	else
	{//開けなかったときの処理
		return;
	}
	for (int nCntReload = 0; nCntReload < g_nReloadCnt; nCntReload++)
	{
		g_Edit[g_EditCnt + 1].bUse = true;

		g_Edit[g_EditCnt + 1].tex[g_Edit[nCntReload].nType] = g_EditTex[g_Edit[nCntReload].nType];

		g_EditCnt++;
	}
}
