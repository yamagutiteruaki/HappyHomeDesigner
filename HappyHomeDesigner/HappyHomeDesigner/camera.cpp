//=============================================================================
//
// カメラ処理 [camera.cpp]
// Author : GP12B295 29 山口輝明
//          宋彦霖
//
//=============================================================================
#include "camera.h"
#include "input.h"
#include "main.h"
#include "calculate.h"
#include "player.h"
#include "stage.h"
#include "field.h"
#include "furniture.h"

// デバッグ用
#ifdef _DEBUG
#include "debugproc.h"
#endif

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void CameraWork(D3DXVECTOR3 *at);
void CameraWorkReset();

//*****************************************************************************
// グローバル変数
//*****************************************************************************
CAMERA	cameraWk;
bool	CameraReset = false;	// カメラリセットのスイッチ

//=============================================================================
// 初期化処理
//=============================================================================

HRESULT InitCamera(int nType)
{
	CAMERA *camera = &cameraWk;

	camera->posCameraEye = D3DXVECTOR3(POS_X_CAM, POS_Y_CAM, POS_Z_CAM);
	camera->posCameraAt = D3DXVECTOR3(POS_X_CAM_AT, POS_Y_CAM_AT, POS_Z_CAM_AT);
	camera->vecCameraUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	camera->rotCamera = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	camera->fVAngle = CAMERA_V_ANGLE * 1.3f;
	camera->fHAngle = CAMERA_H_ANGLE;
	camera->fHAngleMargin = 0.0f;
	camera->fLength = CAMERA_LENGTH;
	camera->fChaseLength = CAMERA_LENGTH;
	camera->fLengthTemp = 0;

	camera->rotDest = 0.0f;


	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitCamera(void)
{

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateCamera(void)
{

#ifdef _DEBUG
#endif

	CAMERA *camera = GetCamera();
	PLAYER *player = GetPlayer(0);
	
	D3DXVECTOR3 limit;
	int fieldnum;

	if (GetStage() == STAGE_HOUSE1
		|| GetStage() == STAGE_HOUSE2
		|| GetStage() == STAGE_HOUSE3
		|| GetStage() == STAGE_MYHOUSE)
	{
		fieldnum = 1;
	}
	else
	{
		fieldnum = 0;
	}
FIELD *field = GetField(fieldnum);

	float limitpos_x=field->Size.x/2;
	float limitpos_z=field->Size.z/2;

	if (fabs(camera->posCameraEye.z) > limitpos_z
		|| fabs(camera->posCameraEye.x) > limitpos_x)

	{
		if (fabs(camera->posCameraEye.x) > fabs(camera->posCameraEye.z))
		{
			if (camera->posCameraEye.x < -limitpos_x)
			{

				limit = camera->posCameraEye - player->Eye;						//limitに座標差格納
				D3DXVec3Normalize(&limit, &limit);								//limitを正規化
				camera->fLength = (-limitpos_x - player->Eye.x) / limit.x;		//正規化したlimitから壁の外に出ないようにlengthの修正
				camera->posCameraEye = camera->fLength*limit;					//再設定したlengthからカメラ座標の再設定
																				//以下３つ同様
			}
			else if (camera->posCameraEye.x > limitpos_x)
			{

				limit = camera->posCameraEye - player->Eye;
				D3DXVec3Normalize(&limit, &limit);
				camera->fLength = (limitpos_x - player->Eye.x) / limit.x;
				camera->posCameraEye = camera->fLength*limit;

			}
			else
			{
				//camera->fLength = camera->fChaseLength;
			}

		}

		else if (fabs(camera->posCameraEye.x) < fabs(camera->posCameraEye.z))
		{
			if (camera->posCameraEye.z < -limitpos_z)
			{

				limit = camera->posCameraEye - player->Eye;
				D3DXVec3Normalize(&limit, &limit);
				camera->fLength = (-limitpos_z - player->Eye.z) / limit.z;
				camera->posCameraEye = camera->fLength*limit;

			}
			else if (camera->posCameraEye.z > limitpos_z)
			{

				limit = camera->posCameraEye - player->Eye;
				D3DXVec3Normalize(&limit, &limit);
				camera->fLength = (limitpos_z - player->Eye.z) / limit.z;
				camera->posCameraEye = camera->fLength*limit;

			}
			else
			{
				camera->fLength = camera->fChaseLength;
			}

		}
	}
	else if (fabs(camera->posCameraEye.z) < limitpos_z
		&& fabs(camera->posCameraEye.x) < limitpos_x)
	{
		camera->fLength = camera->fChaseLength;

	}
	if (camera->fLength > camera->fChaseLength)
	{
		camera->fLength = camera->fChaseLength;
	}



	//デバッグ時にZCでカメラ回転
	if (GetKeyboardPress(DIK_Z) || IsButtonPressed(0, BUTTON_LZ_UP))
	{// 視点旋回「左」
		camera->rotCamera.y += VALUE_ROTATE_CAMERA;
		if (camera->rotCamera.y > D3DX_PI)
		{
			camera->rotCamera.y -= D3DX_PI * 2.0f;
		}

		camera->posCameraEye.x = camera->posCameraAt.x - sinf(camera->rotCamera.y) * camera->fChaseLength;
		camera->posCameraEye.z = camera->posCameraAt.z - cosf(camera->rotCamera.y) * camera->fChaseLength;

		CameraReset = false;
	}
	if (GetKeyboardPress(DIK_C) || IsButtonPressed(0, BUTTON_LZ_DOWN))
	{// 視点旋回「右」
		camera->rotCamera.y -= VALUE_ROTATE_CAMERA;
		if (camera->rotCamera.y < -D3DX_PI)
		{
			camera->rotCamera.y += D3DX_PI * 2.0f;
		}

		camera->posCameraEye.x = camera->posCameraAt.x - sinf(camera->rotCamera.y) * camera->fChaseLength;
		camera->posCameraEye.z = camera->posCameraAt.z - cosf(camera->rotCamera.y) * camera->fChaseLength;

		CameraReset = false;
	}

	if (camera->fLength >= CAMERA_LENGTH_MIN
		&&camera->fLength <= CAMERA_LENGTH_MAX)
	{
		if (GetKeyboardPress(DIK_W) || IsButtonPressed(0, BUTTON_LRZ_DOWN))
		{// 視点移動「ズームイン」
			//camera->posCameraEye.y -= CAMERA_MOVE_SPEED;
			camera->fChaseLength -= CAMERA_MOVE_SPEED;

			// 移動制限
			if (camera->fChaseLength < CAMERA_LENGTH_MIN)
			{
				camera->fChaseLength = CAMERA_LENGTH_MIN;
			}
		camera->fLength = camera->fChaseLength;

		}
		if ((float)fabs(camera->posCameraEye.x) < limitpos_x && (float)fabs(camera->posCameraEye.z) < limitpos_z)
		{
			if (GetKeyboardPress(DIK_S) || IsButtonPressed(0, BUTTON_LRZ_UP))
			{// 視点移動「ズームアウト」
			 //camera->posCameraEye.y += CAMERA_MOVE_SPEED;
				camera->fChaseLength += CAMERA_MOVE_SPEED;

				// 移動制限
				if (camera->fChaseLength > CAMERA_LENGTH_MAX)
				{
					camera->fChaseLength = CAMERA_LENGTH_MAX;
				}
				camera->fLength = camera->fChaseLength;

			}
		}
	}

	// カメラリセット
	if (GetKeyboardTrigger(DIK_X))
	{
		camera->rotDest = player->rot.y + D3DX_PI;

		CameraReset = true;
	}

	// カメラリセットの演出
	if (CameraReset == true)
	{
		CameraWorkReset();
	}

	// カメラワーク
	CameraWork(&(player->Eye));

	// 角度の修正
	camera->rotCamera.y = PiCalculate360(camera->rotCamera.y);
	camera->rotDest = PiCalculate360(camera->rotDest);

#ifdef _DEBUG
	//PrintDebugProc("Camera[pos]: %f,%f,%f\n", camera->posCameraEye.x, camera->posCameraEye.y, camera->posCameraEye.z);
	//PrintDebugProc("CameraReset: %d\n", CameraReset);
	//PrintDebugProc("CameraLength: %f\n", camera->fLength);
	//PrintDebugProc("\n");

#endif
	


}

//=============================================================================
// カメラワーク
//=============================================================================
void CameraWork(D3DXVECTOR3 *at)
{
	D3DXVECTOR3 vec(0.0f, 0.25f, -1.0f);		// 正規化された注視点からの向き
	D3DXMATRIX	mtx;
	CAMERA *camera = GetCamera();

	camera->posCameraAt = *at;
	camera->posCameraAt.y += 40;

	// カメラの相対的な回転角度を行列に変換する
	D3DXMatrixRotationYawPitchRoll(&mtx, camera->rotCamera.y, camera->rotCamera.x, camera->rotCamera.z);

	// 正規化された点に回転行列を掛ける
	D3DXVec3TransformCoord(&vec, &vec, &mtx);

	// カメラの位置 = カメラの注視点 + (注視点からの角度 * 視点までの距離)
	camera->posCameraEye = camera->posCameraAt + (vec * camera->fLength);

}

//=============================================================================
// カメラリセットの演出
//=============================================================================
void CameraWorkReset()
{
	CAMERA *camera = GetCamera();
	float Diff;						// 差分

	// 目的の角度までの差分
	Diff = camera->rotDest - camera->rotCamera.y;
	if (Diff > D3DX_PI)
	{
		Diff -= D3DX_PI * 2.0f;
	}
	if (Diff < -D3DX_PI)
	{
		Diff += D3DX_PI * 2.0f;
	}

	// 目的の角度まで慣性をかける
	camera->rotCamera.y += (float)(Diff * 0.15);

	if (camera->rotCamera.y > D3DX_PI)
	{
		camera->rotCamera.y -= D3DX_PI * 2.0f;
	}
	if (camera->rotCamera.y < -D3DX_PI)
	{
		camera->rotCamera.y += D3DX_PI * 2.0f;
	}

}

//=============================================================================
// カメラの設定処理
//=============================================================================
void SetCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	CAMERA *camera = &cameraWk;
	/******************** ビューイング変換 ********************/
	// ビューマトリクスの初期化
	D3DXMatrixIdentity(&camera->mtxView);

	// ビューマトリクスの作成
	D3DXMatrixLookAtLH(&camera->mtxView,
		&camera->posCameraEye,	// 視点
		&camera->posCameraAt,	// 注視点
		&camera->vecCameraUp);	// 上方向

								// ビューマトリクスの設定
	pDevice->SetTransform(D3DTS_VIEW, &camera->mtxView);


	/******************** プロジェクション変換 ********************/
	// プロジェクションマトリクスの初期化
	D3DXMatrixIdentity(&camera->mtxProjection);

	// プロジェクションマトリクスの作成
	D3DXMatrixPerspectiveFovLH(&camera->mtxProjection,
		VIEW_ANGLE,			// ビュー平面の視野角
		VIEW_ASPECT,		// ビュー平面のアスペクト比
		VIEW_NEAR_Z,		// ビュー平面のNearZ値（近いと描画しない）
		VIEW_FAR_Z);		// ビュー平面のFarZ値（遠いと描画しない）

							// プロジェクションマトリクスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &camera->mtxProjection);

}

//=============================================================================
// カメラの向きの取得
//=============================================================================
D3DXVECTOR3 GetRotCamera(void)
{
	CAMERA	*camera = &cameraWk;
	return camera->rotCamera;
}

//=============================================================================
// ビューマトリックスの取得
//=============================================================================
D3DXMATRIX GetMtxView(void)
{
	CAMERA	*camera = &cameraWk;
	return camera->mtxView;
}

//=============================================================================
// プロジェクションマトリックスの取得
//=============================================================================
D3DXMATRIX GetMtxProjection(void)
{
	CAMERA	*camera = &cameraWk;
	return camera->mtxProjection;
}

//=============================================================================
// カメラ取得関数
//=============================================================================
CAMERA *GetCamera(void)
{
	return(&cameraWk);
}