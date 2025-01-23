//=============================================================================
//
//	敵の処理 [enemy.h]
// Author : 佐々木奏一郎
//
//=============================================================================
#ifndef _ENEMY_H_//このマクロ定義がされていなかったら
#define _ENEMY_H_//2銃インクルード防止のマクロ定義
#include "main.h"
#include "model.h"
#include "typeUI.h"
#define GRAVI (0.05f)			//重力
#define JUMP (2.0f)
#define OBJ_E (20.0f)
#define EPARTS_MAX (2)
#define EUSEPARTS_MAX (2)

//敵の状態
typedef enum
{
	ENEMYSTATE_NORMAL = 0,
	ENEMYSTATE_DAMAGE,
	ENEMYSTATE_ACTION,
	ENEMYSTATE_MAX
}ENEMYSTATE;


//モーションの種類
typedef enum
{
	EMOTIONTYPE_NEUTRAL = 0,//着地
	EMOTIONTYPE_MOVE,//移動
	EMOTIONTYPE_ACTION,//アクション
	EMOTIONTYPE_JUMP,//ジャンプ
	EMOTIONTYPE_LANDING,//着地
	EMOTIONTYPE_MAX
}EMOTIONTYPE;

//キーの構造体
typedef struct
{
	float fPosX;//位置
	float fPosY;
	float fPosZ;
	float fRotX;//向き
	float fRotY;
	float fRotZ;
}EKEY;

//キー情報の構造体
typedef struct
{
	int nFlame;//再生フレーム
	EKEY aKey[2];//パーツの最大数を入れる//キー情報

}EKEY_INFO;

//モーション情報の構造体
typedef struct
{
	bool bLoop;//ループするかどうか
	int nNumKey;//キーの総数
	EKEY_INFO aKeyInfo[2];//キーの最大数//キー情報
}EMOTION_INFO;

typedef enum
{
	ETYPE_RED=0,
	ETYPE_BLUE,
	ETYPE_GREEN,
	ETYPE_MAX
}ETYPE;

//プレイヤー構造体
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 posOld;
	D3DXVECTOR3 size;
	D3DXVECTOR3 move;
	D3DXVECTOR3 rot;
	D3DXVECTOR3 rotDest;
	D3DXMATRIX mtxWorld;//ワールドマトリックス
	int nLife;
	int nType;
	int State;
	float fRad;
	bool bUse;

	Model aModel[2];	//モデルのパーツ数
	int nNumModel;		//モデルのパーツ総数

	EMOTION_INFO aMotionInfo[1];//モーションの最大数
	int nNumMotion;//モーションの総数
	EMOTIONTYPE motionType;//モーションの種類
	bool bLoopMotion;//ループするかどうか
	int nNumKey;//キーの総数
	int nKey;//現在のキーNo.
	int nCntMotion;//モーションカウンター

	int nIdxLife;//ライフバーのIdx
	int IdxShadow;
}Enemy;

//プロトタイプ宣言
void InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
void SetEnemy(D3DXVECTOR3 pos, int nType);
void LoadEnemy(int nType);
void CollisionEnemy(void);
void HitEnemy(int nCnt, int nDamage);
void CollisionEnemytoEnemy(int nCnt);
Enemy*GetEnemy(void);
int GetNumEnemy();
static const char* EPARTS_FILE[EPARTS_MAX] =
{
	"data\\model\\redcar000.x",//胴
	"data\\model\\spear.x",		//頭
};


#endif