//====================================================
//
// 木の処理 [billboard.cpp]
// Author : yabuki yukito
//
//====================================================

#include "billboard.h"
#include "player.h"

//++++++++++++++++++++++++++++++++++++++++++++++++++++
// グローバル変数宣言
//++++++++++++++++++++++++++++++++++++++++++++++++++++
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffItem = NULL;				//頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureItem[ITEMTYPE_MAX] = {};		//テクスチャへのポインタ
Item g_Item[MAX_BILLBOARD];

//====================================================
//アイテムの初期化処理
//====================================================
void InitItem()
{
	LPDIRECT3DDEVICE9 pDevice;								//デバイスへのポインタ

	pDevice = GetDevice();									//デバイスの取得

	//テクスチャの読み込み
	for (int nCnt = 0; nCnt < ITEMTYPE_MAX; nCnt++)
	{
		D3DXCreateTextureFromFile(pDevice,
			ITEM_TEXTURE[nCnt],
			&g_pTextureItem[nCnt]);
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_BILLBOARD,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffItem, NULL);

	VERTEX_3D* pVtx = NULL;

	//頂点バッファをロック
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_BILLBOARD; nCnt++)
	{
		g_Item[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Item[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Item[nCnt].bUse = false;

		//頂点情報の設定
		pVtx[0].pos = D3DXVECTOR3(-15.0f, 15.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(15.0f, 15.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-15.0f, -15.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(15.0f, -15.0f, 0.0f);

		//各頂点の法線の設定(ベクトルの大きさは1にする)
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}
	//頂点バッファのアンロック
	g_pVtxBuffItem->Unlock();
}

//====================================================
//アイテムの終了処理
//====================================================
void UninitItem()
{
	//頂点バッファの解放
	if (g_pVtxBuffItem != NULL)
	{
		g_pVtxBuffItem->Release();
		g_pVtxBuffItem = NULL;
	}

	for (int nCnt = 0; nCnt < ITEMTYPE_MAX; nCnt++)
	{
		//テクスチャの破棄
		if (g_pTextureItem[nCnt] != NULL)
		{
			g_pTextureItem[nCnt]->Release();
			g_pTextureItem[nCnt] = NULL;
		}
	}
}

//====================================================
//アイテムの更新処理
//====================================================
void UpdateItem()
{

}

//====================================================
//アイテムの描画処理
//====================================================
void DrawItem()
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;

	//ライトを無効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	for (int nCnt = 0; nCnt < MAX_BILLBOARD; nCnt++)
	{
		if (g_Item[nCnt].bUse == true)
		{
			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_Item[nCnt].mtxWorld);

			D3DXMATRIX mtxView;
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//カメラの逆行列を指定
			g_Item[nCnt].mtxWorld._11 = mtxView._11;
			g_Item[nCnt].mtxWorld._12 = mtxView._21;
			g_Item[nCnt].mtxWorld._13 = mtxView._31;
			g_Item[nCnt].mtxWorld._21 = mtxView._12;
			g_Item[nCnt].mtxWorld._22 = mtxView._22;
			g_Item[nCnt].mtxWorld._23 = mtxView._32;
			g_Item[nCnt].mtxWorld._31 = mtxView._13;
			g_Item[nCnt].mtxWorld._32 = mtxView._23;
			g_Item[nCnt].mtxWorld._33 = mtxView._33;

			////向きを反映
			//D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotItem.y, g_rotItem.x, g_rotItem.z);
			//D3DXMatrixMultiply(&g_mtxWorldItem, &g_mtxWorldItem, &mtxRot);

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_Item[nCnt].pos.x, g_Item[nCnt].pos.y, g_Item[nCnt].pos.z);
			D3DXMatrixMultiply(&g_Item[nCnt].mtxWorld, &g_Item[nCnt].mtxWorld, &mtxTrans);

			////Zテスト
			//pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);		//Zの比較方法
			//pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);		//Zバッファを書き込まない

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_Item[nCnt].mtxWorld);

			//頂点バッファをデバイスのデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffItem, 0, sizeof(VERTEX_3D));

			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureItem[g_Item[nCnt].nType]);

			//頂点フォーマット
			pDevice->SetFVF(FVF_VERTEX_3D);

			//アイテムの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);

			////Zテスト
			//pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);	//Zの比較方法
			//pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);		//Zバッファを書き込む
		}
	}
	//ライトを有効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//====================================================
//アイテムの設定処理
//====================================================
void SetItem(D3DXVECTOR3 pos, D3DXVECTOR3 dir, TYPE nType)
{
	LPDIRECT3DDEVICE9 pDevice;								//デバイスへのポインタ

	pDevice = GetDevice();									//デバイスの取得

	for (int nCnt = 0; nCnt < MAX_BILLBOARD; nCnt++)
	{
		if (g_Item[nCnt].bUse == false)
		{
			g_Item[nCnt].pos = pos;							//位置
			g_Item[nCnt].nType = nType;						//種類
			g_Item[nCnt].bUse = true;						//使用しているとき

			//	//テクスチャの読み込み
			//for (int nCnt = 0; nCnt < ITEMTYPE_MAX; nCnt++)
			//{
			//	D3DXCreateTextureFromFile(pDevice,
			//		ITEM_TEXTURE[nCnt],
			//		&g_pTextureItem[nCnt]);
			//}
			break;
		}
	}
}
