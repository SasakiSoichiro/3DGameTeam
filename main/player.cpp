//==========================================
//
//		プレイヤー		Player.cpp
//			ryuusei hirata
//
//=========================================
#include "main.h"
#include "player.h"
#include "input.h"
#include "camera.h"
#include "block.h"
#include "meshwall.h"
#include "gimmick.h"

//グローバル変数宣言
Player g_player;
Motion LoadMotion[2];
D3DXVECTOR3 g_Offpos[2];
int g_nIdxShadow;
int g_nCntPlayerState;
int g_nCntStop;
bool bLanding, bOldLanding;
int OldType;

//初期化処理
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

<<<<<<< HEAD

	//各種変数の初期化
	g_player.pos = D3DXVECTOR3(100.0f, 100.0f, 0.0f);
=======
	//各種変数の初期化
	g_player.pos = D3DXVECTOR3(1200.0f, 100.0f, 0.0f);
>>>>>>> 23891c79b96ee74a6351c6c16f6fc744b0b13246
	g_player.posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.nLife = 360;
	g_player.pState = PLAYERSTATE_NORMAL;
	g_nCntPlayerState = 0;
	g_player.motion.motionType = MOTIONTYPE_MOVE;
	bLanding = true;

	for (int nCntType = 0; nCntType < 2; nCntType++)
	{
		ReadScriptPlayer(nCntType);
	}
	g_Offpos[0] = D3DXVECTOR3(0.0f, 30.0f, 0.0f);
	g_Offpos[1] = D3DXVECTOR3(0.0f, 60.0f, 0.0f);
	g_player.Offpos = D3DXVECTOR3(0.0f, 30.0f, 0.0f);
	g_player.motion = LoadMotion[0];
	g_player.motion.nNumKey = 0;
	g_player.motion.nCntMotion = 0;


	for (int nCnt = 0; nCnt < g_player.motion.nNumModel; nCnt++)
	{
		g_player.motion.aModel[nCnt].posFirst = g_player.motion.aModel[nCnt].pos;
		g_player.motion.aModel[nCnt].rotFirst = g_player.motion.aModel[nCnt].rot;
	}

	//g_nIdxShadow = SetShadow(g_player.pos, g_player.rot, D3DXVECTOR3(10.0f, 1.0f, 10.0f));

}
void UninitPlayer(void)
{
	for (int nCntType = 0; nCntType < 2; nCntType++)
	{
		for (int nCntModel = 0; nCntModel < LoadMotion[nCntType].nNumModel; nCntModel++)
		{
			if (LoadMotion[nCntType].aModel[nCntModel].pMesh != NULL)
			{
				LoadMotion[nCntType].aModel[nCntModel].pMesh->Release();
				LoadMotion[nCntType].aModel[nCntModel].pMesh = NULL;

			}
		}

		for (int nCntModel = 0; nCntModel < LoadMotion[nCntType].nNumModel; nCntModel++)
		{
			//頂点バッファの解放
			if (LoadMotion[nCntType].aModel[nCntModel].pBuffMat != NULL)
			{
				LoadMotion[nCntType].aModel[nCntModel].pBuffMat->Release();
				LoadMotion[nCntType].aModel[nCntModel].pBuffMat = NULL;
			}
		}

	}
}
void UpdatePlayer(void)
{
	Camera* pCamera = GetCamera();

<<<<<<< HEAD
=======
	XINPUT_STATE* pStick;
	pStick = GetJoyStickAngle();

>>>>>>> 23891c79b96ee74a6351c6c16f6fc744b0b13246
	g_nCntStop++;
	OldType = g_player.nType;
	g_player.motion.motionTypeOld = g_player.motion.motionType;//モーションの種類
	switch (g_player.pState)
	{
	case PLAYERSTATE_NORMAL:
		break;
	case PLAYERSTATE_DAMAGE:
		g_nCntPlayerState++;
		if (g_nCntPlayerState >= 120)
		{
			g_player.pState = PLAYERSTATE_NORMAL;
			g_nCntPlayerState = 0;
		}
		break;
	case PLAYERSTATE_MOVE:
		g_player.motion.motionType = MOTIONTYPE_MOVE;
		break;
	case PLAYERSTATE_JUMP:
		g_player.motion.motionType = MOTIONTYPE_JUMP;
		if (bLanding == true)
		{
			g_player.pState = PLAYERSTATE_NORMAL;
		}

		break;
	case PLAYERSTATE_ACTION:
		g_nCntPlayerState++;
		if (g_nCntPlayerState >= 60)
		{
			g_player.pState = PLAYERSTATE_NORMAL;
			g_nCntPlayerState = 0;
		}
		break;
	}

	switch (g_player.motion.motionType)
	{
	case MOTIONTYPE_NEUTRAL:
		break;
	case MOTIONTYPE_MOVE:
		break;
	case MOTIONTYPE_ACTION:
		break;
	case MOTIONTYPE_JUMP:
		break;
	case MOTIONTYPE_LANDING:
		break;
	}

	g_player.posOld = g_player.pos;

	//重力加算
	g_player.move.y -= GRAVI;

	if (GetKeyboardPress(DIK_A) == true)
	{//Aキーが押された
		if (GetKeyboardPress(DIK_W) == true)
<<<<<<< HEAD
		{
			if (g_player.pState == PLAYERSTATE_JUMP)
			{
				g_player.pos.x -= sinf(pCamera->rot.y - D3DX_PI * 0.25f) * 1.0f;
				g_player.pos.z -= cosf(pCamera->rot.y - D3DX_PI * 0.25f) * 1.0f;
				g_player.rotDest.y = pCamera->rot.y - D3DX_PI * 0.25f;
			}
			else
			{
				g_player.motion.motionType = MOTIONTYPE_MOVE;
				g_player.pos.x -= sinf(pCamera->rot.y - D3DX_PI * 0.25f) * 2.0f;
				g_player.pos.z -= cosf(pCamera->rot.y - D3DX_PI * 0.25f) * 2.0f;
				g_player.rotDest.y = pCamera->rot.y - D3DX_PI * 0.25f;
			}
		}
		else if (GetKeyboardPress(DIK_S) == true)
		{
			if (g_player.pState == PLAYERSTATE_JUMP)
			{
				g_player.pos.x -= sinf(pCamera->rot.y - D3DX_PI * 0.75f) * 1.0f;
				g_player.pos.z -= cosf(pCamera->rot.y - D3DX_PI * 0.75f) * 1.0f;
				g_player.rotDest.y = pCamera->rot.y - D3DX_PI * 0.75f;
			}
			else
			{
				g_player.pos.x -= sinf(pCamera->rot.y - D3DX_PI * 0.75f) * 2.0f;
				g_player.pos.z -= cosf(pCamera->rot.y - D3DX_PI * 0.75f) * 2.0f;
				g_player.rotDest.y = pCamera->rot.y - D3DX_PI * 0.75f;
			}
		}
		else
		{
			if (g_player.pState == PLAYERSTATE_JUMP)
			{
				g_player.pos.x -= sinf(pCamera->rot.y - D3DX_PI * 0.5f) * 1.0f;
				g_player.pos.z -= cosf(pCamera->rot.y - D3DX_PI * 0.5f) * 1.0f;
				g_player.rotDest.y = pCamera->rot.y - D3DX_PI * 0.5f;
			}
			else
			{
				g_player.motion.motionType = MOTIONTYPE_MOVE;
				g_player.pos.x -= sinf(pCamera->rot.y - D3DX_PI * 0.5f) * 2.0f;
				g_player.pos.z -= cosf(pCamera->rot.y - D3DX_PI * 0.5f) * 2.0f;
				g_player.rotDest.y = pCamera->rot.y - D3DX_PI * 0.5f;
			}
=======
		{//左上
			g_player.pos.x += sinf(pCamera->rot.y + D3DX_PI * 0.75f) * 2.0f;
			g_player.pos.z += cosf(pCamera->rot.y + D3DX_PI * 0.75f) * 2.0f;
			g_player.rotDest.y = pCamera->rot.y + D3DX_PI * 0.75f;
			g_player.motion.motionType = MOTIONTYPE_MOVE;


		}
		else if (GetKeyboardPress(DIK_S) == true)
		{//左下

			g_player.motion.motionType = MOTIONTYPE_MOVE;
			g_player.pos.x -= sinf(pCamera->rot.y - D3DX_PI * 0.75f) * 2.0f;
			g_player.pos.z -= cosf(pCamera->rot.y - D3DX_PI * 0.75f) * 2.0f;
			g_player.rotDest.y = pCamera->rot.y - D3DX_PI * 0.75f;

		}
		else
		{//左
			g_player.motion.motionType = MOTIONTYPE_MOVE;
			g_player.pos.x -= cosf(pCamera->rot.y - D3DX_PI) * 2.0f;
			g_player.pos.z += sinf(pCamera->rot.y - D3DX_PI) * 2.0f;
			g_player.rotDest.y = pCamera->rot.y - D3DX_PI * 0.5f;

>>>>>>> 23891c79b96ee74a6351c6c16f6fc744b0b13246
		}
	}

	else if (GetKeyboardPress(DIK_D) == true)
	{//Dキーが押された


<<<<<<< HEAD

		if (GetKeyboardPress(DIK_W) == true)
		{
			if (g_player.pState == PLAYERSTATE_JUMP)
			{
				g_player.pos.x -= sinf(pCamera->rot.y + D3DX_PI * 0.25f) * 1.0f;
				g_player.pos.z -= cosf(pCamera->rot.y + D3DX_PI * 0.25f) * 1.0f;
				g_player.rotDest.y = pCamera->rot.y + D3DX_PI * 0.25f;
			}
			else
			{
				g_player.pos.x -= sinf(pCamera->rot.y + D3DX_PI * 0.25f) * 2.0f;
				g_player.pos.z -= cosf(pCamera->rot.y + D3DX_PI * 0.25f) * 2.0f;
				g_player.rotDest.y = pCamera->rot.y + D3DX_PI * 0.25f;
				g_player.motion.motionType = MOTIONTYPE_MOVE;
			}
		}
		else if (GetKeyboardPress(DIK_S) == true)
		{
			if (g_player.pState == PLAYERSTATE_JUMP)
			{
				g_player.pos.x -= sinf(pCamera->rot.y + D3DX_PI * 0.75f) * 1.0f;
				g_player.pos.z -= cosf(pCamera->rot.y + D3DX_PI * 0.75f) * 1.0f;
				g_player.rotDest.y = pCamera->rot.y + D3DX_PI * 0.75f;
			}
			else
			{
				g_player.pos.x -= sinf(pCamera->rot.y + D3DX_PI * 0.75f) * 2.0f;
				g_player.pos.z -= cosf(pCamera->rot.y + D3DX_PI * 0.75f) * 2.0f;
				g_player.rotDest.y = pCamera->rot.y + D3DX_PI * 0.75f;
				g_player.motion.motionType = MOTIONTYPE_MOVE;
			}
		}
		else
		{
			if (g_player.pState == PLAYERSTATE_JUMP)
			{
				g_player.pos.x -= sinf(pCamera->rot.y + D3DX_PI * 0.5f) * 1.0f;
				g_player.pos.z -= cosf(pCamera->rot.y + D3DX_PI * 0.5f) * 1.0f;
				g_player.rotDest.y = pCamera->rot.y + D3DX_PI * 0.5f;
			}
			else
			{
				g_player.pos.x -= sinf(pCamera->rot.y + D3DX_PI * 0.5f) * 2.0f;
				g_player.pos.z -= cosf(pCamera->rot.y + D3DX_PI * 0.5f) * 2.0f;
				g_player.rotDest.y = pCamera->rot.y + D3DX_PI * 0.5f;
				g_player.motion.motionType = MOTIONTYPE_MOVE;
			}
=======
		if (GetKeyboardPress(DIK_W) == true)
		{//右上
			g_player.motion.motionType = MOTIONTYPE_MOVE;
			g_player.pos.x += sinf(pCamera->rot.y - D3DX_PI * 0.75f) * 2.0f;
			g_player.pos.z += cosf(pCamera->rot.y - D3DX_PI * 0.75f) * 2.0f;
			g_player.rotDest.y = pCamera->rot.y - D3DX_PI * 0.75f;


		}
		else if (GetKeyboardPress(DIK_S) == true)
		{//右下
			g_player.pos.x -= sinf(pCamera->rot.y + D3DX_PI * 0.75f) * 2.0f;
			g_player.pos.z -= cosf(pCamera->rot.y + D3DX_PI * 0.75f) * 2.0f;
			g_player.rotDest.y = pCamera->rot.y + D3DX_PI * 0.75f;
			g_player.motion.motionType = MOTIONTYPE_MOVE;

		}
		else
		{//右

			g_player.motion.motionType = MOTIONTYPE_MOVE;
			g_player.pos.x += cosf(pCamera->rot.y - D3DX_PI) * 2.0f;
			g_player.pos.z -= sinf(pCamera->rot.y - D3DX_PI) * 2.0f;
			g_player.rotDest.y = pCamera->rot.y + D3DX_PI * 0.5f;

>>>>>>> 23891c79b96ee74a6351c6c16f6fc744b0b13246
		}
	}

	else if (GetKeyboardPress(DIK_W) == true)
	{//Wキーが押された
<<<<<<< HEAD


		if (g_player.pState == PLAYERSTATE_JUMP)
		{
			g_player.pos.x -= sinf(pCamera->rot.y) * 1.0f;
			g_player.pos.z -= cosf(pCamera->rot.y) * 1.0f;
=======
		if (GetKeyboardPress(DIK_LSHIFT) == true)
		{
			//	LShift押されたら
			g_player.motion.motionType = MOTIONTYPE_MOVE;
			g_player.pos.x -= sinf(pCamera->rot.y) * 5.0f;
			g_player.pos.z -= cosf(pCamera->rot.y) * 5.0f;
>>>>>>> 23891c79b96ee74a6351c6c16f6fc744b0b13246
			g_player.rotDest.y = pCamera->rot.y;
		}
		else
		{
			g_player.motion.motionType = MOTIONTYPE_MOVE;
			g_player.pos.x -= sinf(pCamera->rot.y) * 2.0f;
			g_player.pos.z -= cosf(pCamera->rot.y) * 2.0f;
			g_player.rotDest.y = pCamera->rot.y;
		}
	}
	else if (GetKeyboardPress(DIK_S) == true)
	{//Sキーが押された
<<<<<<< HEAD


		if (g_player.pState == PLAYERSTATE_JUMP)
		{
			g_player.pos.x -= sinf(pCamera->rot.y + D3DX_PI) * 1.0f;
			g_player.pos.z -= cosf(pCamera->rot.y + D3DX_PI) * 1.0f;
			g_player.rotDest.y = pCamera->rot.y + D3DX_PI;
		}
		else
		{
			g_player.motion.motionType = MOTIONTYPE_MOVE;
			g_player.pos.x -= sinf(pCamera->rot.y + D3DX_PI) * 2.0f;
			g_player.pos.z -= cosf(pCamera->rot.y + D3DX_PI) * 2.0f;
			g_player.rotDest.y = pCamera->rot.y + D3DX_PI;
		}
	}

=======

		g_player.motion.motionType = MOTIONTYPE_MOVE;
		g_player.pos.x -= sinf(pCamera->rot.y + D3DX_PI) * 2.0f;
		g_player.pos.z -= cosf(pCamera->rot.y + D3DX_PI) * 2.0f;
		g_player.rotDest.y = pCamera->rot.y + D3DX_PI;

	}
>>>>>>> 23891c79b96ee74a6351c6c16f6fc744b0b13246
	else
	{
		if (g_player.motion.motionType == MOTIONTYPE_MOVE)
		{
			g_player.motion.motionType = MOTIONTYPE_NEUTRAL;
		}
	}

<<<<<<< HEAD
	if (KeybordTrigger(DIK_SPACE) == true && bLanding == true)
	{//Sキーが押された
		g_player.pState = PLAYERSTATE_JUMP;
		g_player.move.y = JUMP;
		bLanding = false;
	}


	if (g_player.rotDest.y - g_player.rot.y > D3DX_PI)
	{
		g_player.rot.y = g_player.rot.y + (D3DX_PI * 2);
	}
	else if (g_player.rot.y - g_player.rotDest.y > D3DX_PI)
	{
		g_player.rot.y = g_player.rot.y - (D3DX_PI * 2);
	}

=======
	if (g_player.rotDest.y - g_player.rot.y > D3DX_PI)
	{
		g_player.rot.y = g_player.rot.y + (D3DX_PI * 2);
	}
	else if (g_player.rot.y - g_player.rotDest.y > D3DX_PI)
	{
		g_player.rot.y = g_player.rot.y - (D3DX_PI * 2);
	}

>>>>>>> 23891c79b96ee74a6351c6c16f6fc744b0b13246
	g_player.move.x += (0.0f - g_player.move.x) * 0.05f;
	g_player.move.z += (0.0f - g_player.move.z) * 0.05f;


	g_player.pos += g_player.move;

	float SposX = g_player.motion.aModel[15].mtxWorld._41 + (g_player.SwordmtxWorld._41 - g_player.motion.aModel[15].mtxWorld._41) * 0.5f;
	float SposY = g_player.motion.aModel[15].mtxWorld._42 + (g_player.SwordmtxWorld._42 - g_player.motion.aModel[15].mtxWorld._42) * 0.5f;
	float SposZ = g_player.motion.aModel[15].mtxWorld._43 + (g_player.SwordmtxWorld._43 - g_player.motion.aModel[15].mtxWorld._43) * 0.5f;

	if (g_player.pos.y < 0.0f)
	{
		bLanding = true;
		//g_player.pState = PLAYERSTATE_NORMAL;
		g_player.pos.y = 0.0f;
	}

<<<<<<< HEAD
	g_player.rot.y += (g_player.rotDest.y - g_player.rot.y) * 0.2f;
	//CollisionBlock(&g_player.pos, &g_player.posOld);
=======
	//左スティック移動
	if (GetJoyStick() == true)
	{
		if (pStick->Gamepad.sThumbLX > 10922)
		{
			//右移動
			g_player.motion.motionType = MOTIONTYPE_MOVE;
			g_player.pos.x += cosf(pCamera->rot.y - D3DX_PI) * 2.0f;
			g_player.pos.z -= sinf(pCamera->rot.y - D3DX_PI) * 2.0f;
			g_player.rotDest.y = pCamera->rot.y + D3DX_PI * 0.5f;

		}
		else if (pStick->Gamepad.sThumbLX < -10922)
		{
			//左移動
			g_player.motion.motionType = MOTIONTYPE_MOVE;
			g_player.pos.x -= cosf(pCamera->rot.y - D3DX_PI) * 2.0f;
			g_player.pos.z += sinf(pCamera->rot.y - D3DX_PI) * 2.0f;
			g_player.rotDest.y = pCamera->rot.y - D3DX_PI * 0.5f;

		}
		else if (pStick->Gamepad.sThumbLY > 10922)
		{
			//上移動
			g_player.motion.motionType = MOTIONTYPE_MOVE;
			g_player.pos.x -= sinf(pCamera->rot.y) * 2.0f;
			g_player.pos.z -= cosf(pCamera->rot.y) * 2.0f;
			g_player.rotDest.y = pCamera->rot.y;

		}
		else if (pStick->Gamepad.sThumbLY < -10922)
		{
			//下移動
			g_player.motion.motionType = MOTIONTYPE_MOVE;
			g_player.pos.x -= sinf(pCamera->rot.y + D3DX_PI) * 2.0f;
			g_player.pos.z -= cosf(pCamera->rot.y + D3DX_PI) * 2.0f;
			g_player.rotDest.y = pCamera->rot.y + D3DX_PI;

		}
	}

	g_player.rot.y += (g_player.rotDest.y - g_player.rot.y) * 0.2f;
	CollisionBlock(&g_player.pos, &g_player.posOld);
	CollisionGimmick(&g_player.pos, &g_player.posOld);
>>>>>>> 23891c79b96ee74a6351c6c16f6fc744b0b13246
	//CollisionWall(&g_player.pos, &g_player.posOld);
	//CollisionCyrynder();
	//SetPositionShadow(g_nIdxShadow, D3DXVECTOR3(g_player.pos.x, 1.0f, g_player.pos.z), g_player.pos.y);
	bOldLanding = bLanding;
	UpdateMotion();


}
void DrawPlayer(void)
{
<<<<<<< HEAD
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;
	//現在のマテリアルの保存用
	D3DMATERIAL9 matDef;//現在のマテリアルの保存用
	D3DXMATERIAL* pMat;//マテリアルデータへのポインタ
	int nCnt = 0;

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_player.mtxWorld);
	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_player.rot.y, g_player.rot.x, g_player.rot.z);
	D3DXMatrixMultiply(&g_player.mtxWorld, &g_player.mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_player.pos.x, g_player.pos.y, g_player.pos.z);
	D3DXMatrixMultiply(&g_player.mtxWorld, &g_player.mtxWorld, &mtxTrans);

	pDevice->SetTransform(D3DTS_WORLD, &g_player.mtxWorld);

	pDevice->GetMaterial(&matDef);
	//全モデル（パーツ）の描画
	for (int nCntModel = 0; nCntModel < g_player.motion.nNumModel; nCntModel++)
	{
		//計算用マトリックス
		D3DXMATRIX mtxRotModel, mtxTransModel;
		D3DXMATRIX mtxParent;//親のマトリックス

		//パーツのワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_player.motion.aModel[nCntModel].mtxWorld);

		//向きを反映
		D3DXMatrixRotationYawPitchRoll(&mtxRotModel, g_player.motion.aModel[nCntModel].rot.y, g_player.motion.aModel[nCntModel].rot.x, g_player.motion.aModel[nCntModel].rot.z);
		D3DXMatrixMultiply(&g_player.motion.aModel[nCntModel].mtxWorld, &g_player.motion.aModel[nCntModel].mtxWorld, &mtxRotModel);

		//位置を反映
		D3DXMatrixTranslation(&mtxTransModel, g_player.motion.aModel[nCntModel].pos.x, g_player.motion.aModel[nCntModel].pos.y, g_player.motion.aModel[nCntModel].pos.z);
		D3DXMatrixMultiply(&g_player.motion.aModel[nCntModel].mtxWorld, &g_player.motion.aModel[nCntModel].mtxWorld, &mtxTransModel);

		//パーツの「親のマトリックス」を設定
		if (g_player.motion.aModel[nCntModel].nIdxModelParent != -1)
		{//親モデルがある場合
			mtxParent = g_player.motion.aModel[g_player.motion.aModel[nCntModel].nIdxModelParent].mtxWorld;

		}
		else
		{
			mtxParent = g_player.mtxWorld;
		}

		//算出した「パーツのワールドマトリックス」と「親のマトリックス」を掛け合わせる
		D3DXMatrixMultiply(&g_player.motion.aModel[nCntModel].mtxWorld,
			&g_player.motion.aModel[nCntModel].mtxWorld,
			&mtxParent);
		//パーツのワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD,
			&g_player.motion.aModel[nCntModel].mtxWorld);


		//マテリアルデータへのポインタを取得
		pMat = (D3DXMATERIAL*)g_player.motion.aModel[nCntModel].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_player.motion.aModel[nCntModel].dwNumMat; nCntMat++)
		{

			//マテリアルの設定
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			//テクスチャの設定
			pDevice->SetTexture(0, g_player.motion.aModel[nCntModel].apTexture[nCntMat]);

			//モデル（パーツ）の描画
			g_player.motion.aModel[nCntModel].pMesh->DrawSubset(nCntMat);

		}
		nCnt++;
		if (nCnt == 15)
		{
			SetMatrix();
		}
	}

	pDevice->SetMaterial(&matDef);
=======
	//LPDIRECT3DDEVICE9 pDevice;
	//pDevice = GetDevice();

	////計算用マトリックス
	//D3DXMATRIX mtxRot, mtxTrans;
	////現在のマテリアルの保存用
	//D3DMATERIAL9 matDef;//現在のマテリアルの保存用
	//D3DXMATERIAL* pMat;//マテリアルデータへのポインタ
	//int nCnt = 0;

	////ワールドマトリックスの初期化
	//D3DXMatrixIdentity(&g_player.mtxWorld);
	////向きを反映
	//D3DXMatrixRotationYawPitchRoll(&mtxRot, g_player.rot.y, g_player.rot.x, g_player.rot.z);
	//D3DXMatrixMultiply(&g_player.mtxWorld, &g_player.mtxWorld, &mtxRot);

	////位置を反映
	//D3DXMatrixTranslation(&mtxTrans, g_player.pos.x, g_player.pos.y, g_player.pos.z);
	//D3DXMatrixMultiply(&g_player.mtxWorld, &g_player.mtxWorld, &mtxTrans);

	//pDevice->SetTransform(D3DTS_WORLD, &g_player.mtxWorld);

	//pDevice->GetMaterial(&matDef);
	////全モデル（パーツ）の描画
	//for (int nCntModel = 0; nCntModel < g_player.motion.nNumModel; nCntModel++)
	//{
	//	//計算用マトリックス
	//	D3DXMATRIX mtxRotModel, mtxTransModel;
	//	D3DXMATRIX mtxParent;//親のマトリックス

	//	//パーツのワールドマトリックスの初期化
	//	D3DXMatrixIdentity(&g_player.motion.aModel[nCntModel].mtxWorld);

	//	//向きを反映
	//	D3DXMatrixRotationYawPitchRoll(&mtxRotModel, g_player.motion.aModel[nCntModel].rot.y, g_player.motion.aModel[nCntModel].rot.x, g_player.motion.aModel[nCntModel].rot.z);
	//	D3DXMatrixMultiply(&g_player.motion.aModel[nCntModel].mtxWorld, &g_player.motion.aModel[nCntModel].mtxWorld, &mtxRotModel);

	//	//位置を反映
	//	D3DXMatrixTranslation(&mtxTransModel, g_player.motion.aModel[nCntModel].pos.x, g_player.motion.aModel[nCntModel].pos.y, g_player.motion.aModel[nCntModel].pos.z);
	//	D3DXMatrixMultiply(&g_player.motion.aModel[nCntModel].mtxWorld, &g_player.motion.aModel[nCntModel].mtxWorld, &mtxTransModel);

	//	//パーツの「親のマトリックス」を設定
	//	if (g_player.motion.aModel[nCntModel].nIdxModelParent != -1)
	//	{//親モデルがある場合
	//		mtxParent = g_player.motion.aModel[g_player.motion.aModel[nCntModel].nIdxModelParent].mtxWorld;

	//	}
	//	else
	//	{
	//		mtxParent = g_player.mtxWorld;
	//	}

	//	//算出した「パーツのワールドマトリックス」と「親のマトリックス」を掛け合わせる
	//	D3DXMatrixMultiply(&g_player.motion.aModel[nCntModel].mtxWorld,
	//		&g_player.motion.aModel[nCntModel].mtxWorld,
	//		&mtxParent);
	//	//パーツのワールドマトリックスの設定
	//	pDevice->SetTransform(D3DTS_WORLD,
	//		&g_player.motion.aModel[nCntModel].mtxWorld);


	//	//マテリアルデータへのポインタを取得
	//	pMat = (D3DXMATERIAL*)g_player.motion.aModel[nCntModel].pBuffMat->GetBufferPointer();

	//	for (int nCntMat = 0; nCntMat < (int)g_player.motion.aModel[nCntModel].dwNumMat; nCntMat++)
	//	{

	//		//マテリアルの設定
	//		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

	//		//テクスチャの設定
	//		pDevice->SetTexture(0, g_player.motion.aModel[nCntModel].apTexture[nCntMat]);

	//		//モデル（パーツ）の描画
	//		g_player.motion.aModel[nCntModel].pMesh->DrawSubset(nCntMat);

	//	}
	//	nCnt++;
	//	if (nCnt == 15)
	//	{
	//		SetMatrix();
	//	}
	//}

	//pDevice->SetMaterial(&matDef);
>>>>>>> 23891c79b96ee74a6351c6c16f6fc744b0b13246
}

void SetMatrix(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;
<<<<<<< HEAD
	//現在のマテリアルの保存用
	D3DMATERIAL9 matDef;//現在のマテリアルの保存用
	D3DXMATERIAL* pMat;//マテリアルデータへのポインタ
=======

	//現在のマテリアルの保存用
>>>>>>> 23891c79b96ee74a6351c6c16f6fc744b0b13246
	D3DXMATRIX mtxParent;//親のマトリックス

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_player.SwordmtxWorld);
	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_player.motion.aModel[15].rot.y, g_player.motion.aModel[15].rot.x, g_player.motion.aModel[15].rot.z);
	D3DXMatrixMultiply(&g_player.SwordmtxWorld, &g_player.SwordmtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_player.Offpos.x, g_player.Offpos.y, g_player.Offpos.z);
	D3DXMatrixMultiply(&g_player.SwordmtxWorld, &g_player.SwordmtxWorld, &mtxTrans);



	mtxParent = g_player.motion.aModel[15].mtxWorld;

	//算出した「パーツのワールドマトリックス」と「親のマトリックス」を掛け合わせる
	D3DXMatrixMultiply(&g_player.SwordmtxWorld,
		&g_player.SwordmtxWorld,
		&mtxParent);

	pDevice->SetTransform(D3DTS_WORLD, &g_player.SwordmtxWorld);

}
void SetMotion(int nType)
{
	g_player.motion = LoadMotion[nType];
}
Player* GetPlayer(void)
{
	return &g_player;
}
void ReadScriptPlayer(int nType)
{
	FILE* pFile;
	switch (nType)
	{
	case 0:
		pFile = fopen("data\\MOTION\\motion05.txt", "r");
		break;
	case 1:
		pFile = fopen("data\\MOTION\\motion06.txt", "r");
		break;
	default:
		pFile = NULL;
		break;
	}

	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();
	int nCntModel = 0, nCntParts = 0, nIdx = 0, nParents = 0, nCntKey = 0, nCntMotion = 0;
	int nBool;
	char str[MAX_WORD];
	char FileName[30][MAX_WORD];
	D3DXVECTOR3 pos, rot;


	if (pFile != NULL)
	{
		char aString[MAX_WORD];//文字数を格納

		while (1)
		{
			//ファイルを読み込む
			fscanf(pFile, "%s", &aString[0]);


			if (strcmp(aString, "SCRIPT") == 0)
			{
				while (1)
				{
					//ファイルを読み込む
					fscanf(pFile, "%s", &aString[0]);

					if (strcmp(aString, "NUM_MODEL") == 0)
					{
						fscanf(pFile, "%s", &str[0]);
						fscanf(pFile, "%d", &LoadMotion[nType].nNumModel);
						while (nCntModel < LoadMotion[nType].nNumModel)
						{
							//ファイルを読み込む
							fscanf(pFile, "%s", &aString[0]);

							if (strcmp(aString, "MODEL_FILENAME") == 0)
							{
								fscanf(pFile, "%s", &str[0]);
								fscanf(pFile, "%s", &FileName[nCntModel][0]);

								//xファイルの読み込み
								D3DXLoadMeshFromX(FileName[nCntModel],
									D3DXMESH_SYSTEMMEM,
									pDevice,
									NULL,
									&LoadMotion[nType].aModel[nCntModel].pBuffMat,
									NULL,
									&LoadMotion[nType].aModel[nCntModel].dwNumMat,
									&LoadMotion[nType].aModel[nCntModel].pMesh);

								nCntModel++;
							}
						}
					}

					if (strcmp(aString, "CHARACTERSET") == 0)
					{
						while (1)
						{
							//ファイルを読み込む
							fscanf(pFile, "%s", &aString[0]);

							if (strcmp(aString, "NUM_PARTS") == 0)
							{
								fscanf(pFile, "%s", &str[0]);
								fscanf(pFile, "%d", &LoadMotion[nType].nNumModel);

							}
							while (nCntParts < LoadMotion[nType].nNumModel)
							{
								//ファイルを読み込む
								fscanf(pFile, "%s", &aString[0]);

								if (strcmp(aString, "PARTSSET") == 0)
								{
									while (1)
									{
										//ファイルを読み込む
										fscanf(pFile, "%s", &aString[0]);

										if (strcmp(aString, "INDEX") == 0)
										{
											fscanf(pFile, "%s", &str[0]);
											fscanf(pFile, "%d", &nIdx);
										}
										else if (strcmp(aString, "PARENT") == 0)
										{
											fscanf(pFile, "%s", &str[0]);
											fscanf(pFile, "%d", &LoadMotion[nType].aModel[nIdx].nIdxModelParent);

										}
										else if (strcmp(aString, "POS") == 0)
										{
											fscanf(pFile, "%s", &str[0]);
											fscanf(pFile, "%f", &LoadMotion[nType].aModel[nIdx].pos.x);
											fscanf(pFile, "%f", &LoadMotion[nType].aModel[nIdx].pos.y);
											fscanf(pFile, "%f", &LoadMotion[nType].aModel[nIdx].pos.z);
										}
										else if (strcmp(aString, "ROT") == 0)
										{
											fscanf(pFile, "%s", &str[0]);
											fscanf(pFile, "%f", &LoadMotion[nType].aModel[nIdx].rot.x);
											fscanf(pFile, "%f", &LoadMotion[nType].aModel[nIdx].rot.y);
											fscanf(pFile, "%f", &LoadMotion[nType].aModel[nIdx].rot.z);

										}
										else if (strcmp(aString, "END_PARTSSET") == 0)
										{
											nCntParts++;
											break;
										}
									}

								}

							}
							if (strcmp(aString, "END_CHARACTERSET") == 0)
							{
								break;
							}

						}
					}
					if (strcmp(aString, "MOTIONSET") == 0)
					{
						while (1)
						{
							//ファイルを読み込む
							fscanf(pFile, "%s", &aString[0]);

							if (strcmp(aString, "LOOP") == 0)
							{
								fscanf(pFile, "%s", &str[0]);
								fscanf(pFile, "%d", &nBool);
								if (nBool == 0)
								{
									LoadMotion[nType].aMotionInfo[nCntMotion].bLoop = false;
								}
								else
								{
									LoadMotion[nType].aMotionInfo[nCntMotion].bLoop = true;
								}
							}

							if (strcmp(aString, "NUM_KEY") == 0)
							{
								fscanf(pFile, "%s", &str[0]);
								fscanf(pFile, "%d", &LoadMotion[nType].aMotionInfo[nCntMotion].nNumKey);

								while (nCntKey < LoadMotion[nType].aMotionInfo[nCntMotion].nNumKey)
								{
									//ファイルを読み込む
									fscanf(pFile, "%s", &aString[0]);

									if (strcmp(aString, "KEYSET") == 0)
									{
										nCntParts = 0;
										while (1)
										{
											//ファイルを読み込む
											fscanf(pFile, "%s", &aString[0]);

											if (strcmp(aString, "FRAME") == 0)
											{
												fscanf(pFile, "%s", &str[0]);
												fscanf(pFile, "%d", &LoadMotion[nType].aMotionInfo[nCntMotion].aKeyInfo[nCntKey].nFlame);
												break;
											}
										}

										while (1)
										{
											//ファイルを読み込む
											fscanf(pFile, "%s", &aString[0]);

											if (strcmp(aString, "KEY") == 0)
											{
												while (1)
												{
													//ファイルを読み込む
													fscanf(pFile, "%s", &aString[0]);

													if (strcmp(aString, "POS") == 0)
													{
														fscanf(pFile, "%s", &str[0]);
														fscanf(pFile, "%f", &LoadMotion[nType].aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntParts].fPosX);
														fscanf(pFile, "%f", &LoadMotion[nType].aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntParts].fPosY);
														fscanf(pFile, "%f", &LoadMotion[nType].aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntParts].fPosZ);
													}
													if (strcmp(aString, "ROT") == 0)
													{
														fscanf(pFile, "%s", &str[0]);
														fscanf(pFile, "%f", &LoadMotion[nType].aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntParts].fRotX);
														fscanf(pFile, "%f", &LoadMotion[nType].aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntParts].fRotY);
														fscanf(pFile, "%f", &LoadMotion[nType].aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntParts].fRotZ);
													}
													if (strcmp(aString, "END_KEY") == 0)
													{
														nCntParts++;
														break;
													}
												}
											}
											if (strcmp(aString, "END_KEYSET") == 0)
											{
												nCntKey++;
												break;
											}

										}
									}


								}

							}

							if (strcmp(aString, "END_MOTIONSET") == 0)
							{
								nCntMotion++;
								nCntKey = 0;
								break;
							}
						}
					}
					if (strcmp(aString, "END_SCRIPT") == 0)
					{
						break;
					}
				}
				break;

			}
		}
	}
	for (int nCnt = 0; nCnt < LoadMotion[nType].nNumModel; nCnt++)
	{
		LoadMotion[nType].aModel[nCnt].posFirst = LoadMotion[nType].aModel[nCnt].pos;
		LoadMotion[nType].aModel[nCnt].rotFirst = LoadMotion[nType].aModel[nCnt].rot;
	}
}