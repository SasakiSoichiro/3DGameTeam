//====================================================
//
// 木の処理 [billboard.cpp]
// Author : yabuki yukito
//
//====================================================

#include "billboard.h"
#include "player.h"
#include "item.h"
#include "input.h"
#include "gimmick.h"

//++++++++++++++++++++++++++++++++++++++++++++++++++++
// グローバル変数宣言
//++++++++++++++++++++++++++++++++++++++++++++++++++++
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBillboard = NULL;				//頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureBillboard[BILLBOARDTYPE_MAX] = {};		//テクスチャへのポインタ
Billboard g_Billboard[MAX_BILLBOARD];
bool bExchange;
//====================================================
//アイテムの初期化処理
//====================================================
void InitBillboard()
{
	LPDIRECT3DDEVICE9 pDevice;								//デバイスへのポインタ

	pDevice = GetDevice();									//デバイスの取得

	//テクスチャの読み込み
	for (int nCnt = 0; nCnt < BILLBOARDTYPE_MAX; nCnt++)
	{
		D3DXCreateTextureFromFile(pDevice,
			ITEM_TEXTURE[nCnt],
			&g_pTextureBillboard[nCnt]);
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_BILLBOARD,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBillboard, NULL);

	VERTEX_3D* pVtx = NULL;

	//頂点バッファをロック
	g_pVtxBuffBillboard->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_BILLBOARD; nCnt++)
	{
		g_Billboard[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Billboard[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Billboard[nCnt].bTest = false;
		g_Billboard[nCnt].bDisplay = false;
		g_Billboard[nCnt].bUse = false;
		bExchange = false;
		//頂点情報の設定
		pVtx[0].pos = D3DXVECTOR3(-15.0f, 35.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(15.0f, 35.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-15.0f, -35.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(15.0f, -35.0f, 0.0f);

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
	g_pVtxBuffBillboard->Unlock();
}

//====================================================
//アイテムの終了処理
//====================================================
void UninitBillboard()
{
	//頂点バッファの解放
	if (g_pVtxBuffBillboard != NULL)
	{
		g_pVtxBuffBillboard->Release();
		g_pVtxBuffBillboard = NULL;
	}

	for (int nCnt = 0; nCnt < BILLBOARDTYPE_MAX; nCnt++)
	{
		//テクスチャの破棄
		if (g_pTextureBillboard[nCnt] != NULL)
		{
			g_pTextureBillboard[nCnt]->Release();
			g_pTextureBillboard[nCnt] = NULL;
		}
	}
}

//====================================================
//アイテムの更新処理
//====================================================
void UpdateBillboard()
{
	ITEM* pItem = Getitem();
	bool isbill = IsBill();
	for (int count = 0; count < MAX_ITEM; count++, pItem++)
	{
		if (pItem->bUse == true)
		{
			//プレイヤーの半径の算出用変数
			float fPRadPos = 28.0f;

			//アイテムの半径の算出用変数
			float fIRadPos = 28.0f;

			//プレやーの位置を取得
			D3DXVECTOR3 PlayerPos = GetPlayer()->pos;

			//アイテムのプレイヤーの距離の差
			D3DXVECTOR3 diff = PlayerPos - pItem->pos;

			//範囲計算
			float fDisX = PlayerPos.x - pItem->pos.x;
			float fDisY = PlayerPos.y - pItem->pos.y;
			float fDisZ = PlayerPos.z - pItem->pos.z;

			//二つの半径を求める
			float fRadX = fPRadPos + fIRadPos;

			for (int nCnt = 0; nCnt < MAX_BILLBOARD; nCnt++)
			{
				//プレイヤーがアイテムの範囲に入ったら
				if ((fDisX * fDisX) + (fDisY * fDisY) + (fDisZ * fDisZ) <= (fRadX * fRadX))
				{
					if (g_Billboard[nCnt].nType == BILLBOARDTYPE_1)
					{
						g_Billboard[nCnt].bUse = true;
						g_Billboard[nCnt].bDisplay = true;
						g_Billboard[nCnt].pos.x = pItem->pos.x;
						g_Billboard[nCnt].pos.y = pItem->pos.y + 10.0f;
						g_Billboard[nCnt].pos.z = pItem->pos.z;

						if (KeybordTrigger(DIK_F) == true)
						{//Fを押されたとき
							g_Billboard[nCnt].bUse = false;
						}
					}
				}
				else if ((fDisX * fDisX) + (fDisY * fDisY) + (fDisZ * fDisZ) > (fRadX * fRadX))
				{
					g_Billboard[nCnt].bDisplay = false;
				}
			}
		}
	}
	for (int nCnt = 0; nCnt < MAX_BILLBOARD; nCnt++)
	{
		if (g_Billboard[nCnt].bUse == true)
		{

			if (isbill == true)
			{
				if (pItem->bKey_Top == true && pItem->bKey_bottom == true)
				{
					bExchange = true;
				}

				else if (g_Billboard[nCnt].bTest == false)
				{
					bExchange = false;
				}
			}
		}
	}

}

//====================================================
//アイテムの描画処理
//====================================================
void DrawBillboard()
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;

	//ライトを無効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	for (int nCnt = 0; nCnt < MAX_BILLBOARD; nCnt++)
	{
		if (g_Billboard[nCnt].bUse == true&& g_Billboard[nCnt].bDisplay==true)
		{
			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_Billboard[nCnt].mtxWorld);

			D3DXMATRIX mtxView;
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//カメラの逆行列を指定
			g_Billboard[nCnt].mtxWorld._11 = mtxView._11;
			g_Billboard[nCnt].mtxWorld._12 = mtxView._21;
			g_Billboard[nCnt].mtxWorld._13 = mtxView._31;
			g_Billboard[nCnt].mtxWorld._21 = mtxView._12;
			g_Billboard[nCnt].mtxWorld._22 = mtxView._22;
			g_Billboard[nCnt].mtxWorld._23 = mtxView._32;
			g_Billboard[nCnt].mtxWorld._31 = mtxView._13;
			g_Billboard[nCnt].mtxWorld._32 = mtxView._23;
			g_Billboard[nCnt].mtxWorld._33 = mtxView._33;

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_Billboard[nCnt].pos.x, g_Billboard[nCnt].pos.y, g_Billboard[nCnt].pos.z);
			D3DXMatrixMultiply(&g_Billboard[nCnt].mtxWorld, &g_Billboard[nCnt].mtxWorld, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_Billboard[nCnt].mtxWorld);

			//頂点バッファをデバイスのデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffBillboard, 0, sizeof(VERTEX_3D));


			if(bExchange == false)
			{ 
				//テクスチャの設定
				pDevice->SetTexture(0, g_pTextureBillboard[2]);
			}
			else if (bExchange == true)
			{
				//テクスチャの設定
				pDevice->SetTexture(0, g_pTextureBillboard[3]);
			}
			else
			{
				//テクスチャの設定
				pDevice->SetTexture(0, g_pTextureBillboard[g_Billboard[nCnt].nType]);
			}
			//頂点フォーマット
			pDevice->SetFVF(FVF_VERTEX_3D);

			//アイテムの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);

		}
	}
	//ライトを有効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//====================================================
//アイテムの設定処理
//====================================================
void SetBillboard(D3DXVECTOR3 pos, D3DXVECTOR3 dir, TYPE nType, D3DXVECTOR3 size)
{
	VERTEX_3D* pVtx = NULL;
	LPDIRECT3DDEVICE9 pDevice;								//デバイスへのポインタ

	pDevice = GetDevice();									//デバイスの取得

		//頂点バッファをロック
	g_pVtxBuffBillboard->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_BILLBOARD; nCnt++)
	{
		if (g_Billboard[nCnt].bUse == false)
		{
			g_Billboard[nCnt].pos = pos;			//	位置
			g_Billboard[nCnt].nType = nType;		//	種類
			//if (nType == BILLBOARDTYPE_1)
			//{
			//	g_Billboard[nCnt].bUse = false;			//	使用しているとき
			//}
			//else
			//{
				g_Billboard[nCnt].bUse = true;			//	使用しているとき
			//}

			//	頂点情報の設定
			pVtx[0].pos = D3DXVECTOR3(-size.x, size.y, size.z);
			pVtx[1].pos = D3DXVECTOR3(size.x, size.y, size.z);
			pVtx[2].pos = D3DXVECTOR3(-size.x, -size.y, size.z);
			pVtx[3].pos = D3DXVECTOR3(size.x, -size.y, size.z);

			break;
		}

		pVtx += 4;
	}

	//頂点バッファのアンロック
	g_pVtxBuffBillboard->Unlock();
}
