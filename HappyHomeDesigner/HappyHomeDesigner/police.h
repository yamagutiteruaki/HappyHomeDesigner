//=============================================================================
//
// ポリス処理 [enemy.h]
// Author : GP11B243-18-千坂浩太
//
//=============================================================================
#ifndef _POLICE_H_
#define _POLICE_H_

#include "main.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************

// ポリス本体関係
#define	VALUE_MOVE_POLICE		(1.00f)											// 移動速度係数
#define	RATE_MOVE_POLICE			(0.20f)										// 移動慣性係数
#define	VALUE_ROTATE_POLICE		(D3DX_PI * 0.05f)								// 回転速度
#define	RATE_ROTATE_POLICE		(0.20f)											// 回転慣性係数
#define	POLICE_MAX				(1)												// ポリスの最大数 /////まだ複数対応してないのでいじらないで！！/////
#define	POLICE_SIZE_X			(10.0f)											// ポリスの幅
#define	POLICE_SIZE_Y			(20.0f)											// ポリスの高さ
#define	POLICE_ANIM_MAX			(12)											// ポリスのアニメーションパターン数
#define	POLICE_ANIM_SEC			(1)												// アニメーション一巡にかかる秒数
#define	POLICE_SPEED_FREQUENCY	(60*10)											// ポリスの移動速度の更新頻度(フレーム×秒数)
#define	POLICE_SPEEDUP			(0.2f)											// ポリスの移動速度変化量
#define POLICE_SHADOW_SIZE		(53.0f)											// ポリスの影サイズ
#define	POLICE_MODEL			"data/MODEL/POLICE/standing_body.x"				// 読み込むモデル名
// ポリスアーム関係
#define	POLICE_ARM_TYPE_MAX		(2)												// ポリスの腕の種類(右腕・左腕)
#define	POLICE_ARM_MAX			(POLICE_MAX * 2)								// ポリスの腕の最大数(両腕の合計数)
#define	POLICE_ARM_ANIM_FRAME	(1 * 60)										// アニメーション一往復にかかるフレーム数(秒数 * 60フレーム)
// ポリスのレッグ関係
#define	POLICE_LEG_TYPE_MAX		(2)												// ポリスの足の種類(右足・左足)
#define	POLICE_LEG_MAX			(POLICE_MAX * 2)								// ポリスの足の最大数(両足の合計数)
#define	POLICE_LEG_ANIM_FRAME	(1 * 60)										// アニメーション一往復にかかるフレーム数(秒数 * 60フレーム)
// チェックポイント関係
#define	CHECK_POINT_X_MAX		(3)												// 横方向のチェックポイントの最大数
#define	CHECK_POINT_Y_MAX		(3)												// 縦方向のチェックポイントの最大数
#define	CHECK_POINT_MAX			(CHECK_POINT_X_MAX * CHECK_POINT_Y_MAX)			// チェックポイントの合計
//**************************************
// 設定対象の構造体へのポインタ識別番号
//**************************************
enum
{
	TYPE_BODY = 0,		// 本体
	TYPE_ARM,			// アーム
	TYPE_LEG,			// レッグ
	FURNITURETYPE_MAX
};

//*****************************************************************************
// 構造体宣言
//*****************************************************************************

typedef struct		// ポリス構造体
{
	bool			use;							// true:使用  false:未使用
	bool			able_hit;						// true:当たり判定有効  false:当たり判定無効

	D3DXVECTOR3		scl;							// スケール
	D3DXVECTOR3		Eye;							// ポリスの視点(位置座標)
	D3DXVECTOR3		At;								// ポリスの注視点(ポリスが見ている座標)
	D3DXVECTOR3		Up;								// ポリスの上方向
	D3DXVECTOR3		rot;							// ポリスの向き
	D3DXVECTOR3		move;							// ポリスの移動量
	D3DXVECTOR3		rotBasis;						// ポリスの回転の中心点(原点から少し調整するため）
	D3DXVECTOR3		axisXZ;							// ポリスの回転軸(XZ)
	D3DXVECTOR3		axisY;							// ポリスの回転軸(Y)

	D3DXQUATERNION	qRotateXZ;						// ポリスのXZ軸回転クォータニオン
	D3DXQUATERNION	qRotateY;						// ポリスのY軸回転クォータニオン
	D3DXQUATERNION	qAnswer;						// ポリスの合成後回転クォータニオン

	float			speed;							// 移動速度係数
	float			fangleXZ;						// 回転角度(XZ)
	float			fangleY;						// 回転角度(Y)

	int				anim;							// アニメーション番号
	int				key;							// フレームカウント用

} POLICE;

typedef struct		// ポリスアーム構造体
{
	bool			use;							// true:使用  false:未使用
	bool			rotf;							// 回転方向の切り替えフラグ

	D3DXVECTOR3		scl;							// スケール
	D3DXVECTOR3		Eye;							// アームの視点(位置座標)
	D3DXVECTOR3		At;								// アームの注視点(アームが見ている座標)
	D3DXVECTOR3		Up;								// アームの上方向
	D3DXVECTOR3		rot;							// アームの向き
	D3DXVECTOR3		move;							// アームの移動量
	D3DXVECTOR3		rotBasis;						// アームの回転の中心点(原点から少し調整するため）
	D3DXVECTOR3		axisXZ;							// アームの回転軸(XZ)
	D3DXVECTOR3		axisY;							// アームの回転軸(Y)

	D3DXQUATERNION	qRotateXZ;						// アームのXZ軸回転クォータニオン
	D3DXQUATERNION	qRotateY;						// アームのY軸回転クォータニオン
	D3DXQUATERNION	qAnswer;						// アームの合成後回転クォータニオン

	float			speed;							// 移動速度係数
	float			fangleXZ;						// 回転角度(XZ)
	float			fangleY;						// 回転角度(Y)

	int				anim;							// アニメーション番号
	int				key;							// フレームカウント用
	int				type;							// アームの種類(右腕が0・左腕が1)

} POLICE_ARM;

typedef struct		// ポリスレッグ構造体
{
	bool			use;							// true:使用  false:未使用
	bool			rotf;							// 回転方向の切り替えフラグ

	D3DXVECTOR3		scl;							// スケール
	D3DXVECTOR3		Eye;							// レッグの視点(位置座標)
	D3DXVECTOR3		At;								// レッグの注視点(レッグが見ている座標)
	D3DXVECTOR3		Up;								// レッグの上方向
	D3DXVECTOR3		rot;							// レッグの向き
	D3DXVECTOR3		move;							// レッグの移動量
	D3DXVECTOR3		rotBasis;						// レッグの回転の中心点(原点から少し調整するため）
	D3DXVECTOR3		axisXZ;							// レッグの回転軸(XZ)
	D3DXVECTOR3		axisY;							// レッグの回転軸(Y)

	D3DXQUATERNION	qRotateXZ;						// レッグのXZ軸回転クォータニオン
	D3DXQUATERNION	qRotateY;						// レッグのY軸回転クォータニオン
	D3DXQUATERNION	qAnswer;						// レッグの合成後回転クォータニオン

	float			speed;							// 移動速度係数
	float			fangleXZ;						// 回転角度(XZ)
	float			fangleY;						// 回転角度(Y)

	int				anim;							// アニメーション番号
	int				key;							// フレームカウント用
	int				type;							// アームの種類(右腕が0・左腕が1)

} POLICE_LEG;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitPolice(int nType);
void UninitPolice(void);
void UpdatePolice(void);
void DrawPolice(void);

POLICE *GetPolice(int no);

#endif
