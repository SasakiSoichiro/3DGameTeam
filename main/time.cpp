//=============================================================================
//
// タイマー処理 [time.cpp]
// Author:Marina Harada
//
//=============================================================================
#include"time.h"

//=============================================================================
//グローバル宣言
//=============================================================================
LPDIRECT3DTEXTURE9 g_pTexturetime[MAX_TEX] = {}; //テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBufftime = NULL; //頂点バッファへのポインタ（秒）
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTime = NULL; //頂点バッファへのポインタ（分）
D3DXVECTOR3 g_postime;//タイマーの位置
int g_ntime = 0;//タイマーの値
int g_ns = 0;//秒
int g_min = 0;//分

//=============================================================================
//タイマーの初期化処理
//=============================================================================
void InitTime(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

    //デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\number005.png",
		&g_pTexturetime[0]
	);

	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\number004.png",
		&g_pTexturetime[1]
	);

	//位置を初期化する
	g_postime = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//値を初期化する
	g_ntime = 0;

	//分
	g_min = MAX_MIN;

	//秒ポリゴン
	//頂点バッファの生成
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4 * MAX_TIME,//確保するバッファのサイズ、*数は必要な頂点数
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,//頂点フォーマット
		D3DPOOL_MANAGED,
		&g_pVtxBufftime,
		NULL
	);

	//頂点情報へのポインタ
	VERTEX_2D* pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBufftime->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntS = 0; nCntS < MAX_TIME; nCntS++)
	{
		//使用状態
		bool bUse = true;

		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(530.0f + nCntS * 50.0f,		 0.0f,  0.0f);
		pVtx[1].pos = D3DXVECTOR3(530.0f + nCntS * 50.0f + 50.0f, 0.0f,  0.0f);
		pVtx[2].pos = D3DXVECTOR3(530.0f + nCntS * 50.0f,		 50.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(530.0f + nCntS * 50.0f + 50.0f, 50.0f, 0.0f);

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		
		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBufftime->Unlock();

	//分ポリゴン
	//頂点バッファの生成
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4 * MAX_TIME,//確保するバッファのサイズ、*数は必要な頂点数
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,//頂点フォーマット
		D3DPOOL_MANAGED,
		&g_pVtxBuffTime,
		NULL
	);

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffTime->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntS = 0; nCntS < MAX_TIME; nCntS++)
	{
		//使用状態
		bool bUse = true;

		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(400.0f + nCntS * 50.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(400.0f + nCntS * 50.0f + 50.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(400.0f + nCntS * 50.0f, 50.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(400.0f + nCntS * 50.0f + 50.0f, 50.0f, 0.0f);

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffTime->Unlock();

}
//=============================================================================
//タイマーの終了処理
//=============================================================================
void UninitTime(void)
{
	//テクスチャの破棄
	for (int nCnt = 0; nCnt < MAX_TEX; nCnt++)
	{
		
		if (g_pTexturetime[nCnt] != NULL)
		{
			g_pTexturetime[nCnt]->Release();

			g_pTexturetime[nCnt] = NULL;
		}
	}

	//頂点バッファの破棄（秒）
	if (g_pVtxBufftime != NULL)
	{
		g_pVtxBufftime->Release();

		g_pVtxBufftime = NULL;
	}

	//頂点バッファの破棄（分）
	if (g_pVtxBuffTime != NULL)
	{
		g_pVtxBuffTime->Release();

		g_pVtxBuffTime = NULL;
	}

}
//=============================================================================
//タイマーの更新処理
//=============================================================================
void UpdateTime(void)
{

	g_ns++;

	//1秒経過
	if (g_ns >= 60)
	{
		SubTime(1);

		g_ns = 0;
	}

	//1分経過
	if (g_ntime <= 0)
	{
		
		SubTime(-60);

		Subtime(1);
		;
	}

	//ゲーム終わらせる処理
	if (g_ntime <= 0&& g_min <= 0)
	{

		
	}

}
//=============================================================================
//タイマーの描画処理
//=============================================================================
void DrawTime(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	int nCnttime;

    //デバイスの取得
	pDevice = GetDevice();

	//秒の描画
	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(
		0,
		g_pVtxBufftime,
		0,
		sizeof(VERTEX_2D)
	);

	//頂点情報へのポインタ
	VERTEX_2D* pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBufftime->Lock(0, 0, (void**)&pVtx, 0);

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCnttime = 0; nCnttime < MAX_TIME; nCnttime++)
	{
			    
			//90秒経過
			if (g_ntime <= 30 && g_min <= 0)
			{

				//テクスチャの設定
				pDevice->SetTexture(0, g_pTexturetime[1]);

			}
			else
			{

				//テクスチャの設定
				pDevice->SetTexture(0, g_pTexturetime[0]);

			}

			//タイマーの描画
			pDevice->DrawPrimitive(
				D3DPT_TRIANGLESTRIP,//プリミティブの種類
				4 * nCnttime,//描画する最初の頂点インデックス
				2//プリミティブ（タイマー）の数
			);
	}

	//頂点バッファをアンロックする
	g_pVtxBufftime->Unlock();

	//分の描画
	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(
		0,
		g_pVtxBuffTime,
		0,
		sizeof(VERTEX_2D)
	);

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffTime->Lock(0, 0, (void**)&pVtx, 0);

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCnttime = 0; nCnttime < MAX_TIME; nCnttime++)
	{
		//90秒経過
		if (g_ntime <= 30 && g_min <= 0)
		{

			//テクスチャの設定
			pDevice->SetTexture(0, g_pTexturetime[1]);

		}
		else
		{

			//テクスチャの設定
			pDevice->SetTexture(0, g_pTexturetime[0]);

		}

		//タイマーの描画
		pDevice->DrawPrimitive(
			D3DPT_TRIANGLESTRIP,//プリミティブの種類
			4 * nCnttime,//描画する最初の頂点インデックス
			2//プリミティブ（タイマー）の数
		);
	}

	//頂点バッファをアンロックする
	g_pVtxBuffTime->Unlock();

}
//=============================================================================
//タイマーの設定処理
//=============================================================================
void SetTime(int ntime)
{
	//秒数
	int aPosTexU[MAX_TIME] = {};//各桁の数字を格納
	int nData = 100;//3桁
	int nData1 = 10;//2桁

	g_ntime += ntime;

	//頂点情報へのポインタ
	VERTEX_2D* pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBufftime->Lock(0, 0, (void**)&pVtx, 0);

	for (int ncount = 0; ncount < MAX_TIME; ncount++)
	{
		if (ncount == 0)
		{
			//0番目だったら
			aPosTexU[0] = g_ntime / nData;

		}
		else
		{
			//0番目以外
			aPosTexU[ncount] = (g_ntime % nData) / nData1;
			nData = nData / 10;
			nData1 = nData1 / 10;
		}

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f + (0.1f * aPosTexU[ncount]), 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f + (0.1f * aPosTexU[ncount]), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + (0.1f * aPosTexU[ncount]), 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f + (0.1f * aPosTexU[ncount]), 1.0f);

		pVtx += 4;

	}

	//頂点バッファをアンロックする
	g_pVtxBufftime->Unlock();

	//分数
	int aPosTexu[MAX_TIME] = {};//各桁の数字を格納
	int nData2 = 100;//3桁
	int nData3 = 10;//2桁

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffTime->Lock(0, 0, (void**)&pVtx, 0);

	for (int ncount = 0; ncount < MAX_TIME; ncount++)
	{
		if (ncount == 0)
		{
			//0番目だったら
			aPosTexu[0] = g_min / nData2;

		}
		else
		{
			//0番目以外
			aPosTexu[ncount] = (g_min % nData2) / nData3;
			nData2 = nData2 / 10;
			nData3 = nData3 / 10;
		}

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f + (0.1f * aPosTexu[ncount]), 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f + (0.1f * aPosTexu[ncount]), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + (0.1f * aPosTexu[ncount]), 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f + (0.1f * aPosTexu[ncount]), 1.0f);

		pVtx += 4;

	}

	//頂点バッファをアンロックする
	g_pVtxBuffTime->Unlock();

}
//=============================================================================
//タイマーの秒減算処理
//=============================================================================
void SubTime(int nValue)
{
	int aPosTexU[MAX_TIME] = {};//各桁の数字を格納
	int nData = 100;//3桁
	int nData1 = 10;//2桁

	g_ntime -= nValue;

	//頂点情報へのポインタ
	VERTEX_2D* pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBufftime->Lock(0, 0, (void**)&pVtx, 0);

	for (int ncount = 0; ncount < MAX_TIME; ncount++)
	{
		//0番目以外
		aPosTexU[ncount] = (g_ntime % nData) / nData1;
		nData = nData / 10;
		nData1 = nData1 / 10;

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f + (0.1f * aPosTexU[ncount]), 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f + (0.1f * aPosTexU[ncount]), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + (0.1f * aPosTexU[ncount]), 1.0f);
 		pVtx[3].tex = D3DXVECTOR2(0.1f + (0.1f * aPosTexU[ncount]), 1.0f);

		pVtx += 4;

	}

	//頂点バッファをアンロックする
	g_pVtxBufftime->Unlock();
}
//=============================================================================
//タイマーの分減算処理
//=============================================================================
void Subtime(int nValue)
{
	int aPosTexU[MAX_TIME] = {};//各桁の数字を格納
	int nData = 100;//3桁
	int nData1 = 10;//2桁

	g_min -= nValue;

	//頂点情報へのポインタ
	VERTEX_2D* pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffTime->Lock(0, 0, (void**)&pVtx, 0);

	for (int ncount = 0; ncount < MAX_TIME; ncount++)
	{
		//0番目以外
		aPosTexU[ncount] = (g_min % nData) / nData1;
		nData = nData / 10;
		nData1 = nData1 / 10;

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f + (0.1f * aPosTexU[ncount]), 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f + (0.1f * aPosTexU[ncount]), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + (0.1f * aPosTexU[ncount]), 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f + (0.1f * aPosTexU[ncount]), 1.0f);

		pVtx += 4;

	}

	//頂点バッファをアンロックする
	g_pVtxBuffTime->Unlock();
}
//=============================================================================
//タイマーの秒取得
//=============================================================================
int GetTime(void)
{
	return g_ntime;
}
//=============================================================================
//タイマーの分取得
//=============================================================================
int Gettime(void)
{
	return g_min;
}