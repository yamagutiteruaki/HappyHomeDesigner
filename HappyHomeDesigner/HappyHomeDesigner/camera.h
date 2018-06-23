//=============================================================================
//
// カメラ処理 [camera.h]
// Author  GP11B243　32 山口輝明
//          宋彦霖
//
//=============================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define CAMERA_ANGLE_MARGIN		(0.1f)

#define CAMERA_MOVE_SPEED		(7)
#define CAMERA_MOVE_SLANT		(CAMERA_MOVE_SPEED * 0.71f)
#define CAMERA_ROT_SPEED		(0.05f)
#define CAMERA_ROT_SLANT		(CAMERA_ROT_SPEED * 0.71f)
#define CAMERA_ROT_SPEED_AUTO	(0.2f)


#define CAMERA_V_ANGLE			(D3DX_PI)
#define CAMERA_H_ANGLE			(D3DX_PI * 0.5f)

#define CAMERA_H_ANGLE_MARGIN		(D3DX_PI / 180 * 45)
#define CAMERA_MARGIN_SPEED			(D3DX_PI / 180)
#define CAMERA_LENGTH_SPEED			(10.0f)
#define CAMERA_LENGTH_AUTO_SPEED	(30.0f)
#define CAMERA_LENGTH				(200.0f)
#define CAMERA_LENGTH_MIN			(100.0f)
#define CAMERA_LENGTH_MAX			(300.0f)


#define CAMERA_ROT_MOUSE_X			(0.002f)
#define CAMERA_ROT_MOUSE_Y			(0.002f)


#define ROOT_2					(1.414213f)

#define	POS_X_CAM				(0.0f)					// カメラの初期位置(X座標)
#define	POS_Y_CAM				(50.0f)										// カメラの初期位置(Y座標)
#define	POS_Z_CAM				(-100.0f)										// カメラの初期位置(Z座標)

#define	POS_X_CAM_AT			(POS_X_CAM)
#define	POS_Y_CAM_AT			(0.0f)
#define	POS_Z_CAM_AT			(0.0f)

#define	VIEW_ANGLE				(D3DXToRadian(35.0f))							// ビュー平面の視野角
#define	VIEW_ASPECT				((float)SCREEN_WIDTH / (float)SCREEN_HEIGHT)	// ビュー平面のアスペクト比	
#define	VIEW_NEAR_Z				(10.0f)											// ビュー平面のNearZ値
#define	VIEW_FAR_Z				(5000.0f)										// ビュー平面のFarZ値

#define	VALUE_ROTATE_CAMERA	(D3DX_PI * 0.01f)									// カメラの移動量


typedef struct
{
	D3DXVECTOR3			posCameraEye;				// カメラの視点
	D3DXVECTOR3			posCameraAt;				// カメラの注視点
	D3DXVECTOR3			vecCameraUp;				// カメラの上方向ベクトル
	D3DXVECTOR3			rotCamera;					// カメラの回転
	D3DXVECTOR3			vecTag;

	float				rotDest;					// カメラの目標角度

	D3DXVECTOR3			posCameraAtTps;				// ポジション
	D3DXVECTOR3			posCameraAtNormal;			// ポジション

	D3DXVECTOR3			vecCameraAtPos;

	D3DXMATRIX			mtxView;				// ビューマトリックス
	D3DXMATRIX			mtxProjection;			// プロジェクションマトリックス
	D3DXMATRIX			mtxWorld;				// ワールドマトリックス

	float				fHAngleMargin;
	float				fHAngle;
	float				fVAngle;
	float				fHAngleDiff;
	float				fVAngleDiff;
	float				fLength;				//注視点とカメラの距離
	float				fChaseLength;			//fLengthを保存するため　カメラの制限時に使用
	float				fLengthTemp;
	float				fMoveSpeed;
	float				fRotSpeed;

	int					nCameraMode;
	int					nSetCount;

	bool				bCameraReverse;
}CAMERA;

enum
{
	CAMERA_GAME,
	CAMERA_VIEW
};

enum
{
	CAMERA_NORMAL,
	CAMERA_TPS,
	CAMERA_TARGET
};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT			InitCamera(int nType);
void			UninitCamera(void);
void			UpdateCamera(void);
void			SetCamera(void);
D3DXVECTOR3		GetRotCamera(void);
D3DXMATRIX		GetMtxView(void);
D3DXMATRIX		GetMtxProjection(void);
CAMERA			*GetCamera(void);
#endif