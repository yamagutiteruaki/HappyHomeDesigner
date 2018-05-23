//=============================================================================
//
// ポリス処理 [police.h]
// Author : GP12A295-19-千坂浩太
//
//=============================================================================
#ifndef _POLICE_H_
#define _POLICE_H_

#include "main.h"
#include "field.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
// ポリス本体関係
#define	POLICE_SPEED			(1.20f)											// 移動速度係数
#define	POLICE_MAX				(3)												// ポリスの最大数
#define	POLICE_MODEL			"data/MODEL/POLICE/standing_body.x"				// 読み込むモデル名
#define	POLICE_SCALE_X			(1.0f * 1.2)									// スケールのX成分
#define	POLICE_SCALE_Y			(1.0f * 1.2)									// スケールのY成分
#define	POLICE_SCALE_Z			(1.0f * 1.2)									// スケールのZ成分
#define	POLICE_ROTBASIS_X		(0.0f)											// 回転基準点のX座標
#define	POLICE_ROTBASIS_Y		(60.0f)											// 回転基準点のY座標
#define	POLICE_ROTBASIS_Z		(0.0f)											// 回転基準点のZ座標
#define	POLICE_COLLISION_FRAME	(5 * 60)										// 当たり判定の無効状態の解除にかかるフレーム数(秒数 * 60フレーム)
// ポリスアーム関係
#define	POLICE_ARM_TYPE_MAX		(2)												// ポリスの腕の種類(右腕・左腕)
#define	POLICE_ARM_MAX			(POLICE_MAX * 2)								// ポリスの腕の最大数(両腕の合計数)
#define	POLICE_ARM_ANIM_FRAME	(1 * 60 / 4)									// アニメーション一往復にかかるフレーム数(秒数 * 60フレーム)
#define	POLICE_ARM_ANGLE		(D3DX_PI / 4 / 2)								// アニメーションの回転角度(180度 / 適当な角度)
#define	POLICE_ARM_ROTBASIS_X	(0.0f)											// 回転基準点のX座標
#define	POLICE_ARM_ROTBASIS_Y	(30.0f)											// 回転基準点のY座標
#define	POLICE_ARM_ROTBASIS_Z	(0.0f)											// 回転基準点のZ座標
// ポリスのレッグ関係
#define	POLICE_LEG_TYPE_MAX		(2)												// ポリスの足の種類(右足・左足)
#define	POLICE_LEG_MAX			(POLICE_MAX * 2)								// ポリスの足の最大数(両足の合計数)
#define	POLICE_LEG_ANIM_FRAME	(1 * 60 / 4)									// アニメーション一往復にかかるフレーム数(秒数 * 60フレーム)
#define	POLICE_LEG_ANGLE		(D3DX_PI / 4 / 2)								// アニメーションの回転角度(180度 / 適当な角度)
#define	POLICE_LEG_ROTBASIS_X	(0.0f)											// 回転基準点のX座標
#define	POLICE_LEG_ROTBASIS_Y	(20.0f)											// 回転基準点のY座標
#define	POLICE_LEG_ROTBASIS_Z	(0.0f)											// 回転基準点のZ座標
// チェックポイント関係
#define	CHECK_POINT_X_MAX		(3)												// 横方向のチェックポイントの最大数
#define	CHECK_POINT_Y_MAX		(3)												// 縦方向のチェックポイントの最大数
#define	CHECK_POINT_MAX			(FIELD_SIZE_X_MAX * CHECK_POINT_Y_MAX)			// チェックポイントの合計数
#define	CHECK_POINT_X			(FIELD_SIZE_X / 2 - FIELD_SIZE_X / 16)			// チェックポイントのX座標
#define	CHECK_POINT_Z			(FIELD_SIZE_Z / 2 - FIELD_SIZE_Z / 16)			// チェックポイントのZ座標
//*****************************************************************************
// クラス定義
//*****************************************************************************
class POLICE						// ポリスクラス
{
public:
	bool			use;							// true:使用  false:未使用
	bool			able_hit;						// true:当たり判定有効  false:当たり判定無効
	bool			rotf;							// 回転方向の切り替えフラグ(今は使わないのでNULL)
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
	float			fangleXZ;						// 回転角度(XZ)
	float			fangleY;						// 回転角度(Y)
	int				key;							// フレームカウント用
	int				num;							// 親子関係識別用
	int				type;							// 本体の種類(今は使わないのでNULL)
};
class POLICE_ARM :public POLICE		// ポリスアームクラス
{
};
class POLICE_LEG :public POLICE		// ポリスレッグクラス
{
};
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitPolice(int nType);
void UninitPolice(void);
void UpdatePolice(void);
void DrawPolice(void);
POLICE *GetPolice(int no);
void SetParts(void);
template <typename CLASS> void SetAnimation(CLASS *pIn, float fAngle, int frame, D3DXVECTOR3 AxisXZ, D3DXVECTOR3 AxisY);
void Animation(void);
#endif