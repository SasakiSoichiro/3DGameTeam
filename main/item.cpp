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

	for (int count = 0; count < MAX_ITEM; count++)
	{
		g_item[count].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_item[count].bUse = false;

		//	Xファイルの読み込み
		D3DXLoadMeshFromX("data\\Item\\house000.x",
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_pBufferMatItem[count],
			NULL,
			&g_dwNuMatItem[count],
			&g_pMeshItem[count]);

		//	テクスチャの読み込み
		pMat = (D3DXMATERIAL*)g_pBufferMatItem[count]->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_dwNuMatItem; nCntMat++)
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

}

//	更新処理
void UpdateItem(void)
{

}

//	描画処理
void DrawItem(void)
{

}

//	取得処理
ITEM* GetItem(void)
{
	return &g_item[0];
}