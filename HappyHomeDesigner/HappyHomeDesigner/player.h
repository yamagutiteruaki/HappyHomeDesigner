//=============================================================================
//
// プレイヤー処理 [player.h]
// Author : 宋彦霖
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
// プレイヤー本体関係
#define	PLAYER_MAX					(1)										// プレイヤーの最大数
#define	PLAYER_WID					(10.0f)									// プレイヤーの幅
#define	PLAYER_HEI					(20.0f)									// プレイヤーの高さ
#define HAVE_MAX					(5)										// 家具を持てる最大数
#define WT_MAX						(5)										// 所持重量制限
#define PLAYER_SHADOW_SIZE			(23.0f)									// プレイヤーの影サイズ
#define	PLAYER_MODEL				"data/MODEL/PLAYER/standingman.x"		// 読み込むモデル名
#define	PLAYER_SCALE_X				(1.0f * 1.2)							// スケールのX成分
#define	PLAYER_SCALE_Y				(1.0f * 1.2)							// スケールのY成分
#define	PLAYER_SCALE_Z				(1.0f * 1.2)							// スケールのZ成分
// ポリス右アーム関係
#define	PLAYER_R_ARM_MAX			(PLAYER_MAX)							// ポリスの腕の最大数(両腕の合計数)
#define	PLAYER_R_ARM_ANIM_FRAME		(1 * 60 / 4)							// アニメーション一往復にかかるフレーム数(秒数 * 60フレーム)
#define	PLAYER_R_ARM_ANGLE			(D3DX_PI / 4 / 2)						// アニメーションの回転角度(180度 / 適当な角度)
#define	PLAYER_R_ARM_ROTBASIS_X		(0.0f)									// 回転基準点のX座標
#define	PLAYER_R_ARM_ROTBASIS_Y		(30.0f)									// 回転基準点のY座標
#define	PLAYER_R_ARM_ROTBASIS_Z		(0.0f)									// 回転基準点のZ座標
#define	PLAYER_R_ARM_MODEL			"data/MODEL/PLAYER/player_R_hand.x"		// 読み込むモデル
// ポリス左アーム関係
#define	PLAYER_L_ARM_MAX			(PLAYER_MAX)							// ポリスの腕の最大数(両腕の合計数)
#define	PLAYER_L_ARM_ANIM_FRAME		(1 * 60 / 4)							// アニメーション一往復にかかるフレーム数(秒数 * 60フレーム)
#define	PLAYER_L_ARM_ANGLE			(D3DX_PI / 4 / 2)						// アニメーションの回転角度(180度 / 適当な角度)
#define	PLAYER_L_ARM_ROTBASIS_X		(0.0f)									// 回転基準点のX座標
#define	PLAYER_L_ARM_ROTBASIS_Y		(30.0f)									// 回転基準点のY座標
#define	PLAYER_L_ARM_ROTBASIS_Z		(0.0f)									// 回転基準点のZ座標
#define	PLAYER_L_ARM_MODEL			"data/MODEL/PLAYER/player_L_hand.x"		// 読み込むモデル名
// ポリスの右レッグ関係
#define	PLAYER_R_LEG_TYPE_MAX		(2)										// ポリスの足の種類(右足・左足)
#define	PLAYER_R_LEG_MAX			(PLAYER_MAX)							// ポリスの足の最大数(両足の合計数)
#define	PLAYER_R_LEG_ANIM_FRAME		(1 * 60 / 4)							// アニメーション一往復にかかるフレーム数(秒数 * 60フレーム)
#define	PLAYER_R_LEG_ANGLE			(D3DX_PI / 4 / 2)						// アニメーションの回転角度(180度 / 適当な角度)
#define	PLAYER_R_LEG_ROTBASIS_X		(0.0f)									// 回転基準点のX座標
#define	PLAYER_R_LEG_ROTBASIS_Y		(20.0f)									// 回転基準点のY座標
#define	PLAYER_R_LEG_ROTBASIS_Z		(0.0f)									// 回転基準点のZ座標
#define	PLAYER_R_LEG_MODEL			"data/MODEL/PLAYER/player_R_leg.x"		// 読み込むモデル名
// ポリスの左レッグ関係
#define	PLAYER_L_LEG_TYPE_MAX		(2)										// ポリスの足の種類(右足・左足)
#define	PLAYER_L_LEG_MAX			(PLAYER_MAX)							// ポリスの足の最大数(両足の合計数)
#define	PLAYER_L_LEG_ANIM_FRAME		(1 * 60 / 4)							// アニメーション一往復にかかるフレーム数(秒数 * 60フレーム)
#define	PLAYER_L_LEG_ANGLE			(D3DX_PI / 4 / 2)						// アニメーションの回転角度(180度 / 適当な角度)
#define	PLAYER_L_LEG_ROTBASIS_X		(0.0f)									// 回転基準点のX座標
#define	PLAYER_L_LEG_ROTBASIS_Y		(20.0f)									// 回転基準点のY座標
#define	PLAYER_L_LEG_ROTBASIS_Z		(0.0f)									// 回転基準点のZ座標
#define	PLAYER_L_LEG_MODEL			"data/MODEL/PLAYER/player_L_leg.x"		// 読み込むモデル名

//*****************************************************************************
// 構造体宣言
//*****************************************************************************
typedef struct		// プレイヤー構造体
{
	bool			use;							// true:使用  false:未使用

	int				hp;								// HP

	D3DXVECTOR3		scl;							// スケール

	D3DXVECTOR3		Eye;							// プレイヤーの視点
	D3DXVECTOR3		At;								// プレイヤーの注視点
	D3DXVECTOR3		Up;								// プレイヤーの上方向
	D3DXVECTOR3		rot;							// プレイヤーの向き
	D3DXVECTOR3		rotDest;						// プレイヤーの目的の向き
	D3DXVECTOR3		move;							// プレイヤーの移動量

	D3DXVECTOR3		posTmp;							// プレイヤーの視点（一時保存）


	VERTEX_2D		vertexWk[NUM_VERTEX];			// 頂点情報格納ワーク

	int				anim;							// アニメーション番号

	float			speed;							// 移動速度係数

	int				weight;

	int				havenum[HAVE_MAX];	

	int				nIdxShadow;
	float			fSizeShadow;
	D3DXCOLOR		colShadow;
	bool			bShadow;

} PLAYER;
//class PLAYER										// プレイヤークラス
//{
//public:
//	bool			use;							// true:使用  false:未使用
//	bool			bShadow;
//	D3DXVECTOR3		scl;							// スケール
//	D3DXVECTOR3		Eye;							// プレイヤーの視点(位置座標)
//	D3DXVECTOR3		At;								// プレイヤーの注視点(プレイヤーが見ている座標)
//	D3DXVECTOR3		Up;								// プレイヤーの上方向
//	D3DXVECTOR3		rot;							// プレイヤーの向き
//	D3DXVECTOR3		rotDest;						// プレイヤーの目的の向き
//	D3DXVECTOR3		move;							// プレイヤーの移動量
//	D3DXVECTOR3		rotBasis;						// プレイヤーの回転の中心点(原点から少し調整するため）
//	D3DXVECTOR3		axisXZ;							// プレイヤーの回転軸(XZ)
//	D3DXVECTOR3		axisY;							// プレイヤーの回転軸(Y)
//	D3DXQUATERNION	qRotateXZ;						// プレイヤーのXZ軸回転クォータニオン
//	D3DXQUATERNION	qRotateY;						// プレイヤーのY軸回転クォータニオン
//	D3DXQUATERNION	qAnswer;						// プレイヤーの合成後回転クォータニオン
//	D3DXVECTOR3		posTmp;							// プレイヤーの視点（一時保存）
//	float			fangleXZ;						// 回転角度(XZ)
//	float			fangleY;						// 回転角度(Y)
//	float			speed;							// 移動速度係数
//	int				key;							// フレームカウント用
//	int				key2;							// 移動フラグ切り替えカウント用
//	int				num;							// 親子関係識別用
//	int				weight;
//	int				havenum[HAVE_MAX];
//	int				nIdxShadow;
//	float			fSizeShadow;
//	D3DXCOLOR		colShadow;
//};
//class PLAYER_R_ARM :public PLAYER					// プレイヤー右アームクラス
//{
//public:
//	bool			rotf;							// 回転方向の切り替えフラグ
//};
//class PLAYER_L_ARM :public PLAYER					// プレイヤー左アームクラス
//{
//public:
//	bool			rotf;							// 回転方向の切り替えフラグ
//};
//class PLAYER_R_LEG :public PLAYER					// プレイヤー右レッグクラス
//{
//public:
//	bool			rotf;							// 回転方向の切り替えフラグ
//};
//class PLAYER_L_LEG :public PLAYER					// プレイヤー左レッグクラス
//{
//public:
//	bool			rotf;							// 回転方向の切り替えフラグ
//};
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitPlayer(int nType);
void UninitPlayer(void);
void DrawPlayer(void);
void UpdatePlayer(void);

PLAYER *GetPlayer(int no);
void SetResetno(int no);

#endif
