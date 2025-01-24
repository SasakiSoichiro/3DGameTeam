//=================================================================
//
//
//
//				あ　い　て　む　処　理　！！
//
//
//
//==================================================================
#include "item.h"
#include "player.h"

ITEM g_item[MAX_ITEM] = {};
LPD3DXMESH g_pMeshItem[MAX_ITEM] = { NULL };				//	頂点情報のポインター
LPDIRECT3DTEXTURE9 g_apTextureItem[128] = {};	//	テクスチャのポインター
LPD3DXBUFFER g_pBufferMatItem[MAX_ITEM] = { NULL };			//	マテリアルのポインター
DWORD g_dwNuMatItem[MAX_ITEM] = { 0 };						//	マテリアルの数

//	初期化処理
void InitItem(void)
{
	//	デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATERIAL* pMat;

	//	Xファイルの読み込み
	D3DXLoadMeshFromX("data\\model\\key_top.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBufferMatItem[0],
		NULL,
		&g_dwNuMatItem[0],
		&g_pMeshItem[0]);

	//	Xファイルの読み込み
	D3DXLoadMeshFromX("data\\model\\key_bottom.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBufferMatItem[1],
		NULL,
		&g_dwNuMatItem[1],
		&g_pMeshItem[1]);

	//	Xファイルの読み込み
	D3DXLoadMeshFromX("data\\model\\key.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBufferMatItem[2],
		NULL,
		&g_dwNuMatItem[2],
		&g_pMeshItem[2]);

	//	Xファイルの読み込み
	D3DXLoadMeshFromX("data\\model\\naginata.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBufferMatItem[3],
		NULL,
		&g_dwNuMatItem[3],
		&g_pMeshItem[3]);

	//	Xファイルの読み込み
	D3DXLoadMeshFromX("data\\model\\recovery.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBufferMatItem[4],
		NULL,
		&g_dwNuMatItem[4],
		&g_pMeshItem[4]);

	//	Xファイルの読み込み
	D3DXLoadMeshFromX("data\\model\\flashlight.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBufferMatItem[5],
		NULL,
		&g_dwNuMatItem[5],
		&g_pMeshItem[5]);

	for (int count = 0; count < MAX_ITEM; count++)
	{
		g_item[count].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_item[count].bUse = false;

		//	テクスチャの読み込み
		pMat = (D3DXMATERIAL*)g_pBufferMatItem[count]->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_dwNuMatItem[count]; nCntMat++)
		{
			if (pMat[nCntMat].pTextureFilename != NULL)
			{
				D3DXCreateTextureFromFile(pDevice,
					pMat[nCntMat].pTextureFilename,
					&g_apTextureItem[nCntMat]);
			}
		}
	}
}

//	終了処理
void UinitItem(void)
{
	for (int count = 0; count < MAX_ITEM; count++)
	{
		if (g_pMeshItem[count] != NULL)
		{
			g_pMeshItem[count]->Release();
			g_pMeshItem[count] = NULL;
		}

		//	マテリアルの破棄
		if (g_pBufferMatItem[count] != NULL)
		{
			g_pBufferMatItem[count]->Release();
			g_pBufferMatItem[count] = NULL;
		}
	}
}

//	更新処理
void UpdateItem(void)
{

}

//	描画処理
void DrawItem(void)
{
	//	デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;
	D3DMATERIAL9 matDef;
	D3DXMATERIAL* pMat;

	for (int count = 0; count < MAX_ITEM; count++)
	{
		//	ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_item[count].mtxWorld);

		//	位置の反映
		D3DXMatrixTranslation(&mtxTrans, g_item[count].pos.x, g_item[count].pos.y, g_item[count].pos.z);
		D3DXMatrixMultiply(&g_item[count].mtxWorld, &g_item[count].mtxWorld, &mtxTrans);

		//	ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_item[count].mtxWorld);

		//	現在のマテリアルを保存
		pDevice->GetMaterial(&matDef);


		for (int nCntModel = 0; nCntModel < MAX_ITEM; nCntModel++)
		{
			//	マテリアルデータへのポインタを取得
			pMat = (D3DXMATERIAL*)g_pBufferMatItem[nCntModel]->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < MAX_ITEM; nCntMat++)
			{
				if (g_item[nCntMat].bUse == true)
				{
					//	マテリアルの設定
					pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

					//	テクスチャの設定
					pDevice->SetTexture(0, g_apTextureItem[nCntMat]);

					//	モデルの描画
					g_pMeshItem[nCntModel]->DrawSubset(nCntMat);
				}
			}
		}
	}
	//	保存したマテリアルを戻す		
	pDevice->SetMaterial(&matDef);

}

//	取得処理
ITEM* GetItem(void)
{
	return &g_item[0];
}

//	配置処理
void SetItem(D3DXVECTOR3 pos, ITEMTYPE type)
{
	switch (type)
	{
	case ITEMTYPE_ONE:
		g_item[0].bUse = true;
		g_item[0].pos = pos;
		
		break;

	case ITEMTYPE_TWO:
		g_item[1].bUse = true;
		g_item[1].pos = pos;

		break;

	case ITEMTYPE_THREE:
		g_item[2].bUse = true;
		g_item[2].pos = pos;

		break;

	case ITEMTYPE_FOUR:
		g_item[3].bUse = true;
		g_item[3].pos = pos;

		break;

	case ITEMTYPE_FIVE:
		g_item[4].bUse = true;
		g_item[4].pos = pos;

		break;

	case ITEMTYPE_SIX:
		g_item[5].bUse = true;
		g_item[5].pos = pos;

		break;

	default:
		break;
	}
}

//	当たり判定処理
void CollisionItem(D3DXVECTOR3 pos, ITEMTYPE type)
{

}