//==========================================
//
//		モデル			model.cpp
//			ryuusei hirata
//
//=========================================
#include "main.h"
#include "model.h"
#include "input.h"

//	グロバール
LPD3DXMESH g_pMeshModeel = NULL;				//	頂点情報のポインター
LPDIRECT3DTEXTURE9 g_apTextureModel[128] = {};	//	テクスチャのポインター
LPD3DXBUFFER g_pBufferMatModel = NULL;			//	マテリアルのポインター
DWORD g_dwNuMatModel = 0;						//	マテリアルの数
D3DXVECTOR3 g_posModel;							//	位置
D3DXVECTOR3 g_rotModel;							//	向き
D3DXMATRIX g_mtxWoldModel;						//	ワールドマトリックス

//========================
//		初期化処理
//========================
void InitModel(void)
{
	//	デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATERIAL* pMat;

	g_posModel = D3DXVECTOR3(300.0f, 0.0f, 0.0f);
	g_rotModel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//	Xファイルの読み込み
	D3DXLoadMeshFromX("data\\model\\house000.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBufferMatModel,
		NULL,
		&g_dwNuMatModel,
		&g_pMeshModeel);

	//	テクスチャの読み込み
	pMat = (D3DXMATERIAL*)g_pBufferMatModel->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_dwNuMatModel; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{
			D3DXCreateTextureFromFile(pDevice,
				pMat[nCntMat].pTextureFilename,
				&g_apTextureModel[nCntMat]);
		}
	}
}

//========================
//		終了処理
//========================
void UninitModel(void)
{
	//	メッシュの破棄
	if (g_pMeshModeel != NULL)
	{
		g_pMeshModeel->Release();
		g_pMeshModeel = NULL;
	}

	//	マテリアルの破棄
	if (g_pBufferMatModel != NULL)
	{
		g_pBufferMatModel->Release();
		g_pBufferMatModel = NULL;
	}
}

//========================
//		更新処理
//========================
void UpdateModel(void)
{

}

//=======================
//		描画処理
//=======================
void DrawModel(void)
{
	//	デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;
	D3DMATERIAL9 matDef;
	D3DXMATERIAL* pMat;

	//	ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_mtxWoldModel);

	//	向き反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotModel.y, g_rotModel.x, g_rotModel.z);
	D3DXMatrixMultiply(&g_mtxWoldModel, &g_mtxWoldModel, &mtxRot);

	//	位置の反映
	D3DXMatrixTranslation(&mtxTrans, g_posModel.x, g_posModel.y, g_posModel.z);
	D3DXMatrixMultiply(&g_mtxWoldModel, &g_mtxWoldModel, &mtxTrans);

	//	ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWoldModel);

	//	現在のマテリアルを保存
	pDevice->GetMaterial(&matDef);

	//	マテリアルデータへのポインタあーを取得
	pMat = (D3DXMATERIAL*)g_pBufferMatModel->GetBufferPointer();

	//	描画
	for (int nCntMat = 0; nCntMat < (int)g_dwNuMatModel; nCntMat++)
	{
		//	マテリアルの設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//	テクスチャの設定
		pDevice->SetTexture(0, g_apTextureModel[nCntMat]);

		//	モデルの描画
		g_pMeshModeel->DrawSubset(nCntMat);
	}

	//	保存したマテリアルを戻す
	pDevice->SetMaterial(&matDef);
}