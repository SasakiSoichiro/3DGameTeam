//======================================================
//
//				ライト	light.cpp
//					ryuusei hirata
//
//======================================================
#include "light.h"
#include "main.h"

//	グローバル
D3DLIGHT9 g_light[MAX_LIGHT] = {};	//	ライト情報

void InitLighr(void)
{
	//	デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXVECTOR3 vecDir[MAX_LIGHT];

	//	ライトをクリアする
	ZeroMemory(&g_light, sizeof(D3DLIGHT9) * MAX_LIGHT);

	for (int nCntLight = 0; nCntLight < MAX_LIGHT; nCntLight++)
	{
		//	ライトの種類を設定
		g_light[nCntLight].Type = D3DLIGHT_DIRECTIONAL;

		//	ライトの拡散光
		g_light[nCntLight].Diffuse = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f);

		//	ライトの方向
		vecDir[0] = D3DXVECTOR3(-0.2f, -0.8f, -0.4f);
		vecDir[1] = D3DXVECTOR3(0.3f, -0.8f, 0.4f);
		vecDir[2] = D3DXVECTOR3(-0.4f, 0.8f, -0.9f);

		//	正規化する
		D3DXVec3Normalize(&vecDir[nCntLight], &vecDir[nCntLight]);
		g_light[nCntLight].Direction = vecDir[nCntLight];

		//	ライトを設定する
		pDevice->SetLight(nCntLight, &g_light[nCntLight]);

		//	ライトを有効にする
		pDevice->LightEnable(nCntLight, TRUE);
	}
}

void UninitLight(void)
{

}

void UpdateLight(void)
{

}