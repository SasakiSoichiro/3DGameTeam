//====================================================
//
//			リザルト			result.cpp
//				ryuusei.hirata
//
//=====================================================
#include "result.h"
#include "fade.h"

//	グローバル
LPDIRECT3DTEXTURE9 g_apTextureResult = NULL;			// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResult = NULL;		// 頂点バッファへのポインタ
Result g_result = {};
RESULT g_ResultType = RESULT_MAX;

//---------------
//	初期化処理
//---------------
void InitResult(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//	頂点バッファ
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffResult,
		NULL);

	VERTEX_2D* pVtx;
	//ロック
	g_pVtxBuffResult->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラー
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//テクスチャ座標の設定　　１２５
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// アンロック
	g_pVtxBuffResult->Unlock();
}

//---------------
//	終了処理
//---------------
void UinitResult(void)
{
	if (g_apTextureResult != NULL)
	{
		g_apTextureResult->Release();
		g_apTextureResult = NULL;
	}

	if (g_pVtxBuffResult != NULL)
	{
		g_pVtxBuffResult->Release();
		g_pVtxBuffResult = NULL;
	}
}

//---------------
//	更新処理
//----------------
void UpdateResult(void)
{
	if (KeybordTrigger(DIK_RETURN) == true)
	{//エンターが押されたら
		SetFade(MODE_RANKING);
	}
	else if (GetJoypadPress(JOYKEY_START) == true)
	{
		SetFade(MODE_RANKING);
	}
}

//---------------
//	描画処理
//---------------
void DrawResult(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//頂点フォーマットの設定
	pDevice->SetStreamSource(0, g_pVtxBuffResult, 0, sizeof(VERTEX_2D));

	//頂点フォーマット設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_apTextureResult);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

}

//---------------
//	配置処理
//---------------
void SetResult(RESULT type)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();
	g_ResultType = type;

	switch (type)
	{
	case RESULT_CLEAR:
		//	テクスチャ読み込み
		D3DXCreateTextureFromFile(pDevice,
			"data\\texture\\GameClear1.png",
			&g_apTextureResult);

		break;

	case RESULT_GAMEOVER:
		//	テクスチャ読み込み
		D3DXCreateTextureFromFile(pDevice,
			"data\\texture\\GameOver1.png",
			&g_apTextureResult);

		break;

	default:
		break;
	}
}

RESULT GetResult()
{
	return g_ResultType;
}