//=============================================================================
//
// プレイヤー処理 [player.cpp]
// Author : 宋彦霖
//
//=============================================================================
#include "debugproc.h"
#include "player.h"
#include "camera.h"
#include "input.h"
#include "stage.h"
#include "home.h"
#include "calculate.h"
#include "collision.h"
#include "fade.h"
#include "button.h"
#include "shadow.h"
#include "inputCtrl.h"
#include "police.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	VALUE_MOVE_PLAYER		(1.00f)						// 移動速度係数
#define	RATE_MOVE_PLAYER		(0.20f)						// 移動慣性係数
#define	VALUE_ROTATE_PLAYER		(D3DX_PI * 0.05f)			// 回転速度
#define	RATE_ROTATE_PLAYER		(0.20f)						// 回転慣性係数
#define MOVE_LIMIT				(10)
#define PLAYER_POS_ADJ			(20.0f)						// 初期位置調整値
#define PLAYER_WT_ADJ			(0.08f)						// 移動速度調整値
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void PlayerMove(void);
void PlayerMoveWt(void);
void PlayerBorder(void);
void PlayerEntrance(void);
void PlayerPosReset(void);

void PlayerPartsMove(void);
void PlayerAnimation(void);
void SetPlayerParts(void);
//*****************************************************************************
// グローバル変数
//*****************************************************************************
// プレイヤー本体関係
LPDIRECT3DTEXTURE9	g_pD3DTexturePlayer;				// テクスチャ読み込み場所
LPD3DXMESH			g_pD3DXMeshPlayer;					// ID3DXMeshインターフェイスへのポインタ
LPD3DXBUFFER		g_pD3DXBuffMatPlayer;				// メッシュのマテリアル情報を格納
DWORD				g_nNumMatPlayer;					// 属性情報の総数
D3DXMATRIX			g_mtxWorldPlayer;					// ワールドマトリックス
PLAYER				playerWk[PLAYER_MAX];				// プレイヤー格納ワーク
// プレイヤー右アーム関係
LPDIRECT3DTEXTURE9	g_pD3DTexturePlayer_R_Arm;			// テクスチャ読み込み場所
LPD3DXMESH			g_pD3DXMeshPlayer_R_Arm;			// ID3DXMeshインターフェイスへのポインタ
LPD3DXBUFFER		g_pD3DXBuffMatPlayer_R_Arm;			// メッシュのマテリアル情報を格納
DWORD				g_nNumMatPlayer_R_Arm;				// 属性情報の総数
D3DXMATRIX			g_mtxWorldPlayer_R_Arm;				// ワールドマトリックス
PLAYER_R_ARM		player_R_ArmWk[PLAYER_R_ARM_MAX];	// プレイヤー右アーム格納ワーク
// プレイヤー左アーム関係
LPDIRECT3DTEXTURE9	g_pD3DTexturePlayer_L_Arm;			// テクスチャ読み込み場所
LPD3DXMESH			g_pD3DXMeshPlayer_L_Arm;			// ID3DXMeshインターフェイスへのポインタ
LPD3DXBUFFER		g_pD3DXBuffMatPlayer_L_Arm;			// メッシュのマテリアル情報を格納
DWORD				g_nNumMatPlayer_L_Arm;				// 属性情報の総数
D3DXMATRIX			g_mtxWorldPlayer_L_Arm;				// ワールドマトリックス
PLAYER_L_ARM		player_L_ArmWk[PLAYER_L_ARM_MAX];	// プレイヤー左アーム格納ワーク
// プレイヤーの右レッグ関係
LPDIRECT3DTEXTURE9	g_pD3DTexturePlayer_R_Leg;			// テクスチャ読み込み場所
LPD3DXMESH			g_pD3DXMeshPlayer_R_Leg;			// ID3DXMeshインターフェイスへのポインタ
LPD3DXBUFFER		g_pD3DXBuffMatPlayer_R_Leg;			// メッシュのマテリアル情報を格納
DWORD				g_nNumMatPlayer_R_Leg;				// 属性情報の総数
D3DXMATRIX			g_mtxWorldPlayer_R_Leg;				// ワールドマトリックス
PLAYER_R_LEG		player_R_LegWk[PLAYER_R_LEG_MAX];	// プレイヤー右レッグ格納ワーク
// プレイヤーの左レッグ関係
LPDIRECT3DTEXTURE9	g_pD3DTexturePlayer_L_Leg;			// テクスチャ読み込み場所
LPD3DXMESH			g_pD3DXMeshPlayer_L_Leg;			// ID3DXMeshインターフェイスへのポインタ
LPD3DXBUFFER		g_pD3DXBuffMatPlayer_L_Leg;			// メッシュのマテリアル情報を格納
DWORD				g_nNumMatPlayer_L_Leg;				// 属性情報の総数
D3DXMATRIX			g_mtxWorldPlayer_L_Leg;				// ワールドマトリックス
PLAYER_L_LEG		player_L_LegWk[PLAYER_L_LEG_MAX];	// プレイヤー左レッグ格納ワーク
// その他
bool dash = FALSE;
int dashTimer = 0;
float vel = 0.0f;
const float velRate = 0.4f;
int resetno;

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitPlayer(int nType)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	PLAYER *player = &playerWk[0];
	PLAYER_R_ARM *player_R_Arm = &player_R_ArmWk[0];	// プレイヤー右アームポインタ初期化
	PLAYER_L_ARM *player_L_Arm = &player_L_ArmWk[0];	// プレイヤー左アームポインタ初期化
	PLAYER_R_LEG *player_R_Leg = &player_R_LegWk[0];	// プレイヤー右レッグポインタ初期化
	PLAYER_L_LEG *player_L_Leg = &player_L_LegWk[0];	// プレイヤー左レッグポインタ初期化
	FIELD *field = GetField(0);

	if (nType == STAGE_INIT_FAST)
	{
		// プレイヤー本体のモデル読み込み
		g_pD3DTexturePlayer = NULL;
		g_pD3DXMeshPlayer = NULL;
		g_pD3DXBuffMatPlayer = NULL;
		if (FAILED(D3DXLoadMeshFromX(PLAYER_MODEL,
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_pD3DXBuffMatPlayer,
			NULL,
			&g_nNumMatPlayer,
			&g_pD3DXMeshPlayer)))
		{
			return E_FAIL;
		}
		// 右アームのモデル読み込み
		g_pD3DTexturePlayer_R_Arm = NULL;
		g_pD3DXMeshPlayer_R_Arm = NULL;
		g_pD3DXBuffMatPlayer_R_Arm = NULL;
		if (FAILED(D3DXLoadMeshFromX(PLAYER_R_ARM_MODEL,
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_pD3DXBuffMatPlayer_R_Arm,
			NULL,
			&g_nNumMatPlayer_R_Arm,
			&g_pD3DXMeshPlayer_R_Arm)))
		{
			return E_FAIL;
		}
		// 左アームのモデル読み込み
		g_pD3DTexturePlayer_L_Arm = NULL;
		g_pD3DXMeshPlayer_L_Arm = NULL;
		g_pD3DXBuffMatPlayer_L_Arm = NULL;
		if (FAILED(D3DXLoadMeshFromX(PLAYER_L_ARM_MODEL,
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_pD3DXBuffMatPlayer_L_Arm,
			NULL,
			&g_nNumMatPlayer_L_Arm,
			&g_pD3DXMeshPlayer_L_Arm)))
		{
			return E_FAIL;
		}
		// 右レッグのモデル読み込み
		g_pD3DTexturePlayer_R_Leg = NULL;
		g_pD3DXMeshPlayer_R_Leg = NULL;
		g_pD3DXBuffMatPlayer_R_Leg = NULL;
		if (FAILED(D3DXLoadMeshFromX(PLAYER_R_LEG_MODEL,
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_pD3DXBuffMatPlayer_R_Leg,
			NULL,
			&g_nNumMatPlayer_R_Leg,
			&g_pD3DXMeshPlayer_R_Leg)))
		{
			return E_FAIL;
		}
		// 左レッグのモデル読み込み
		g_pD3DTexturePlayer_L_Leg = NULL;
		g_pD3DXMeshPlayer_L_Leg = NULL;
		g_pD3DXBuffMatPlayer_L_Leg = NULL;
		if (FAILED(D3DXLoadMeshFromX(PLAYER_L_LEG_MODEL,
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_pD3DXBuffMatPlayer_L_Leg,
			NULL,
			&g_nNumMatPlayer_L_Leg,
			&g_pD3DXMeshPlayer_L_Leg)))
		{
			return E_FAIL;
		}
	}
	// プレイヤーの初期化処理
	for (int i = 0; i < PLAYER_MAX; i++, player++)
	{
		// プレイヤーの視点の初期化
		player->Eye = D3DXVECTOR3(275.0f, 0.0f, -330.0f);
		// プレイヤーの注視点の初期化
		player->At = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		// プレイヤーの上方向の初期化
		player->Up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		// プレイヤーの向きの初期化
		player->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		// プレイヤーの目的の向きの初期化
		player->rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		// プレイヤーの移動量の初期化
		player->move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		// プレイヤーのスケールの初期化
		player->scl = D3DXVECTOR3(0.9f, 0.9f, 0.9f);
		// プレイヤーの視点（一時保存）の初期化
		player->posTmp = D3DXVECTOR3(0.0f, 0.0f, 0.0f);;
		// useフラグをtrueに設定
		player->use = true;
		// プレイヤーの移動速度初期化
		player->speed = VALUE_MOVE_PLAYER;
		// 持ち物の総重量
		player->weight = 0;
		// プレイヤーの持ち物
		for (int j = 0; j < HAVE_MAX; j++)
		{
			player->havenum[j] = -1;
		}
		// 影
		player->nIdxShadow = -1;
		player->fSizeShadow= PLAYER_SHADOW_SIZE;
		player->colShadow= D3DXCOLOR(0.7f, 0.7f, 0.7f, 0.7f);
		player->bShadow=false;

		// 回転の中心点の初期設定(原点ではなく少しずらす）
		player->rotBasis = D3DXVECTOR3(0.0f, 30.0f, 0.0f);
		// プレイヤーの回転軸の初期化
		player->axisXZ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		player->axisY = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		// プレイヤーの回転角度の初期化
		player->fangleXZ = 0.0f;
		player->fangleY = 0.0f;
		// プレイヤーのフレームカウント初期化
		player->key = 0;
		// 親子関係識別番号の初期設定(番号は1から)
		player->num = i + 1;
	}
	// 右アームの初期化処理
	player = &playerWk[0];
	for (int i = 0; i < PLAYER_R_ARM_MAX; i++, player_R_Arm++)
	{
		// アームの視点(位置座標)の初期化
		player_R_Arm->Eye = D3DXVECTOR3(0.0f, 0.0f, 100.0f);
		// アームの注視点の初期化
		player_R_Arm->At = D3DXVECTOR3(0.0f, 0.0f, 50.0f);
		// アームの上方向の初期化
		player_R_Arm->Up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		// アームの向きの初期化
		player_R_Arm->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		// アームの移動量の初期化
		player_R_Arm->move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		// 回転の中心点の初期設定(原点ではなく少しずらす）
		player_R_Arm->rotBasis = 
			D3DXVECTOR3(PLAYER_R_ARM_ROTBASIS_X * PLAYER_SCALE_X, PLAYER_R_ARM_ROTBASIS_Y * PLAYER_SCALE_Y, PLAYER_R_ARM_ROTBASIS_Z * PLAYER_SCALE_Z);
		// アームのスケールの初期化
		//player_R_Arm->scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		player_R_Arm->scl = player->scl;
		// アームの回転軸の初期化
		player_R_Arm->axisXZ = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		player_R_Arm->axisY = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		// アームの回転角度の初期化
		player_R_Arm->fangleXZ = 0.0f;
		player_R_Arm->fangleY = 0.0f;
		// useフラグをtrueに設定
		player_R_Arm->use = false;
		// アームのフレームカウント初期化
		player_R_Arm->key = 0;
		// 回転切り替えフラグをtrueに設定
		player_R_Arm->rotf = true;
		// 親子関係識別番号の初期設定(未使用:0番,使用：本体と同じ番号)
		player_R_Arm->num = 0;
	}
	// 左アームの初期化処理
	player = &playerWk[0];
	for (int i = 0; i <PLAYER_L_ARM_MAX; i++, player_L_Arm++)
	{
		// アームの視点(位置座標)の初期化
		player_L_Arm->Eye = D3DXVECTOR3(0.0f, 0.0f, 100.0f);
		// アームの注視点の初期化
		player_L_Arm->At = D3DXVECTOR3(0.0f, 0.0f, 50.0f);
		// アームの上方向の初期化
		player_L_Arm->Up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		// アームの向きの初期化
		player_L_Arm->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		// アームの移動量の初期化
		player_L_Arm->move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		// 回転の中心点の初期設定(原点ではなく少しずらす）
		player_L_Arm->rotBasis =
			D3DXVECTOR3(PLAYER_L_ARM_ROTBASIS_X * PLAYER_SCALE_X, PLAYER_L_ARM_ROTBASIS_Y * PLAYER_SCALE_Y, PLAYER_L_ARM_ROTBASIS_Z * PLAYER_SCALE_Z);
		// アームのスケールの初期化
		//player_L_Arm->scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		player_L_Arm->scl = player->scl;
		// アームの回転軸の初期化
		player_L_Arm->axisXZ = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		player_L_Arm->axisY = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		// アームの回転角度の初期化
		player_L_Arm->fangleXZ = 0.0f;
		player_L_Arm->fangleY = 0.0f;
		// useフラグをtrueに設定
		player_L_Arm->use = false;
		// アームのフレームカウント初期化
		player_L_Arm->key = 0;
		// 回転切り替えフラグをtrueに設定
		player_L_Arm->rotf = false;
		// 親子関係識別番号の初期設定(未使用:0番,使用：本体と同じ番号)
		player_L_Arm->num = 0;
	}
	// 右レッグの初期化処理
	player = &playerWk[0];
	for (int i = 0; i <PLAYER_R_LEG_MAX; i++, player_R_Leg++)
	{
		// アームの視点(位置座標)の初期化
		player_R_Leg->Eye = D3DXVECTOR3(0.0f, 0.0f, 100.0f);
		// アームの注視点の初期化
		player_R_Leg->At = D3DXVECTOR3(0.0f, 0.0f, 50.0f);
		// アームの上方向の初期化
		player_R_Leg->Up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		// アームの向きの初期化
		player_R_Leg->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		// アームの移動量の初期化
		player_R_Leg->move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		// 回転の中心点の初期設定(原点ではなく少しずらす）
		player_R_Leg->rotBasis =
			D3DXVECTOR3(PLAYER_R_LEG_ROTBASIS_X * PLAYER_SCALE_X, PLAYER_R_LEG_ROTBASIS_Y * PLAYER_SCALE_Y, PLAYER_R_LEG_ROTBASIS_Z * PLAYER_SCALE_Z);
		// アームのスケールの初期化
		//player_R_Leg->scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		player_R_Leg->scl = player->scl;
		// アームの回転軸の初期化
		player_R_Leg->axisXZ = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		player_R_Leg->axisY = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		// アームの回転角度の初期化
		player_R_Leg->fangleXZ = 0.0f;
		player_R_Leg->fangleY = 0.0f;
		// useフラグをtrueに設定
		player_R_Leg->use = false;
		// アームのフレームカウント初期化
		player_R_Leg->key = 0;
		// 回転切り替えフラグをtrueに設定
		player_R_Leg->rotf = false;
		// 親子関係識別番号の初期設定(未使用:0番,使用：本体と同じ番号)
		player_R_Leg->num = 0;
	}
	// 左レッグの初期化処理
	player = &playerWk[0];
	for (int i = 0; i <PLAYER_L_LEG_MAX; i++, player_L_Leg++)
	{
		// アームの視点(位置座標)の初期化
		player_L_Leg->Eye = D3DXVECTOR3(0.0f, 0.0f, 100.0f);
		// アームの注視点の初期化
		player_L_Leg->At = D3DXVECTOR3(0.0f, 0.0f, 50.0f);
		// アームの上方向の初期化
		player_L_Leg->Up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		// アームの向きの初期化
		player_L_Leg->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		// アームの移動量の初期化
		player_L_Leg->move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		// 回転の中心点の初期設定(原点ではなく少しずらす）
		player_L_Leg->rotBasis =
			D3DXVECTOR3(PLAYER_L_LEG_ROTBASIS_X * PLAYER_SCALE_X, PLAYER_L_LEG_ROTBASIS_Y * PLAYER_SCALE_Y, PLAYER_L_LEG_ROTBASIS_Z * PLAYER_SCALE_Z);
		// アームのスケールの初期化
		//player_L_Leg->scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		player_L_Leg->scl = player->scl;
		// アームの回転軸の初期化
		player_L_Leg->axisXZ = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		player_L_Leg->axisY = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		// アームの回転角度の初期化
		player_L_Leg->fangleXZ = 0.0f;
		player_L_Leg->fangleY = 0.0f;
		// useフラグをtrueに設定
		player_L_Leg->use = false;
		// アームのフレームカウント初期化
		player_L_Leg->key = 0;
		// 回転切り替えフラグをtrueに設定
		player_L_Leg->rotf = true;
		// 親子関係識別番号の初期設定(未使用:0番,使用：本体と同じ番号)
		player_L_Leg->num = 0;
	}
	// パーツ親子関係設定
	SetPlayerParts();
	resetno = 3;
	return S_OK;
}
//=============================================================================
// 終了処理
//=============================================================================
void UninitPlayer(void)
{
	// 本体
	if (g_pD3DTexturePlayer != NULL)
	{// テクスチャの開放
		g_pD3DTexturePlayer->Release();
		g_pD3DTexturePlayer = NULL;
	}
	if (g_pD3DXMeshPlayer != NULL)
	{// メッシュの開放
		g_pD3DXMeshPlayer->Release();
		g_pD3DXMeshPlayer = NULL;
	}
	if (g_pD3DXBuffMatPlayer != NULL)
	{// マテリアルの開放
		g_pD3DXBuffMatPlayer->Release();
		g_pD3DXBuffMatPlayer = NULL;
	}
	// 右アーム
	if (g_pD3DTexturePlayer_R_Arm != NULL)
	{// テクスチャの開放
		g_pD3DTexturePlayer_R_Arm->Release();
		g_pD3DTexturePlayer_R_Arm = NULL;
	}
	if (g_pD3DXMeshPlayer_R_Arm != NULL)
	{// メッシュの開放
		g_pD3DXMeshPlayer_R_Arm->Release();
		g_pD3DXMeshPlayer_R_Arm = NULL;
	}
	if (g_pD3DXBuffMatPlayer_R_Arm != NULL)
	{// マテリアルの開放
		g_pD3DXBuffMatPlayer_R_Arm->Release();
		g_pD3DXBuffMatPlayer_R_Arm = NULL;
	}
	// 左アーム
	if (g_pD3DTexturePlayer_L_Arm != NULL)
	{// テクスチャの開放
		g_pD3DTexturePlayer_L_Arm->Release();
		g_pD3DTexturePlayer_L_Arm = NULL;
	}
	if (g_pD3DXMeshPlayer_L_Arm != NULL)
	{// メッシュの開放
		g_pD3DXMeshPlayer_L_Arm->Release();
		g_pD3DXMeshPlayer_L_Arm = NULL;
	}
	if (g_pD3DXBuffMatPlayer_L_Arm != NULL)
	{// マテリアルの開放
		g_pD3DXBuffMatPlayer_L_Arm->Release();
		g_pD3DXBuffMatPlayer_L_Arm = NULL;
	}
	// 右レッグ
	if (g_pD3DTexturePlayer_R_Leg != NULL)
	{// テクスチャの開放
		g_pD3DTexturePlayer_R_Leg->Release();
		g_pD3DTexturePlayer_R_Leg = NULL;
	}
	if (g_pD3DXMeshPlayer_R_Leg != NULL)
	{// メッシュの開放
		g_pD3DXMeshPlayer_R_Leg->Release();
		g_pD3DXMeshPlayer_R_Leg = NULL;
	}
	if (g_pD3DXBuffMatPlayer_R_Leg != NULL)
	{// マテリアルの開放
		g_pD3DXBuffMatPlayer_R_Leg->Release();
		g_pD3DXBuffMatPlayer_R_Leg = NULL;
	}
	// 左レッグ
	if (g_pD3DTexturePlayer_L_Leg != NULL)
	{// テクスチャの開放
		g_pD3DTexturePlayer_L_Leg->Release();
		g_pD3DTexturePlayer_L_Leg = NULL;
	}
	if (g_pD3DXMeshPlayer_L_Leg != NULL)
	{// メッシュの開放
		g_pD3DXMeshPlayer_L_Leg->Release();
		g_pD3DXMeshPlayer_L_Leg = NULL;
	}
	if (g_pD3DXBuffMatPlayer_L_Leg != NULL)
	{// マテリアルの開放
		g_pD3DXBuffMatPlayer_L_Leg->Release();
		g_pD3DXBuffMatPlayer_L_Leg = NULL;
	}

	//for (int i = 0; i < PLAYER_ANIM_MAX; i++)
	//{
	//	if (g_pD3DTexturePlayer[i] != NULL)
	//	{// テクスチャの開放
	//		g_pD3DTexturePlayer[i]->Release();
	//		g_pD3DTexturePlayer[i] = NULL;
	//	}

	//	if (g_pD3DXMeshPlayer[i] != NULL)
	//	{// メッシュの開放
	//		g_pD3DXMeshPlayer[i]->Release();
	//		g_pD3DXMeshPlayer[i] = NULL;
	//	}

	//	if (g_pD3DXBuffMatPlayer[i] != NULL)
	//	{// マテリアルの開放
	//		g_pD3DXBuffMatPlayer[i]->Release();
	//		g_pD3DXBuffMatPlayer[i] = NULL;
	//	}
	//}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawPlayer(void)
{
	//LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//D3DXMATRIX mtxRot, mtxTranslate, mtxScale;
	//D3DXMATERIAL *pD3DXMat;
	//D3DMATERIAL9 matDef;

	//PLAYER *player = &playerWk[0];

	//for (int i = 0; i < PLAYER_MAX; i++, player++)
	//{
	//	if (player->use == true)	// 使用状態なら描画する
	//	{
	//		// ライトをon
	//		pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	//		// ワールドマトリックスの初期化
	//		D3DXMatrixIdentity(&g_mtxWorldPlayer);

	//		// スケールを反映
	//		D3DXMatrixScaling(&mtxScale, player->scl.x,
	//			player->scl.y,
	//			player->scl.z);
	//		D3DXMatrixMultiply(&g_mtxWorldPlayer,
	//			&g_mtxWorldPlayer, &mtxScale);

	//		// 回転を反映
	//		D3DXMatrixRotationYawPitchRoll(&mtxRot, player->rot.y, player->rot.x, player->rot.z);
	//		D3DXMatrixMultiply(&g_mtxWorldPlayer, &g_mtxWorldPlayer, &mtxRot);

	//		//// 移動を反映
	//		D3DXMatrixTranslation(&mtxTranslate, player->Eye.x, player->Eye.y, player->Eye.z);
	//		D3DXMatrixMultiply(&g_mtxWorldPlayer, &g_mtxWorldPlayer, &mtxTranslate);

	//		// ワールドマトリックスの設定
	//		pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldPlayer);

	//		// 現在のマテリアルを取得
	//		pDevice->GetMaterial(&matDef);

	//		// マテリアル情報に対するポインタを取得
	//		pD3DXMat = (D3DXMATERIAL*)g_pD3DXBuffMatPlayer->GetBufferPointer();

	//		for (int i = 0; i < (int)g_nNumMatPlayer; i++)
	//		{
	//			// マテリアルの設定
	//			pDevice->SetMaterial(&pD3DXMat[i].MatD3D);

	//			// テクスチャの設定
	//			pDevice->SetTexture(0, g_pD3DTexturePlayer);

	//			// 描画
	//			g_pD3DXMeshPlayer->DrawSubset(i);

	//		}

	//		// ライトをoff
	//		pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//	}

	//}


	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATERIAL *pD3DXMat;
	D3DMATERIAL9 matDef;
	PLAYER *player = &playerWk[0];						// プレイヤー本体ポインタ初期化
	PLAYER_R_ARM *player_R_Arm = &player_R_ArmWk[0];	// プレイヤー右アームポインタ初期化
	PLAYER_L_ARM *player_L_Arm = &player_L_ArmWk[0];	// プレイヤー左アームポインタ初期化
	PLAYER_R_LEG *player_R_Leg = &player_R_LegWk[0];	// プレイヤー右レッグポインタ初期化
	PLAYER_L_LEG *player_L_Leg = &player_L_LegWk[0];	// プレイヤー左レッグポインタ初期化

	// プレイヤー本体の描画処理
	for (int i = 0; i < PLAYER_MAX; i++, player++)
	{
		if (player->use == true)
		{	// 使用状態なら描画する
			// ライトをon
			pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_mtxWorldPlayer);
			// ワールドマトリックス作成
			D3DXMatrixTransformation(&g_mtxWorldPlayer, NULL, NULL, &player->scl, &player->rotBasis, &player->qAnswer, &player->Eye);
			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldPlayer);
			// 現在のマテリアルを取得
			pDevice->GetMaterial(&matDef);
			// マテリアル情報に対するポインタを取得
			pD3DXMat = (D3DXMATERIAL*)g_pD3DXBuffMatPlayer->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_nNumMatPlayer; nCntMat++)
			{
				// マテリアルの設定
				pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);
				// テクスチャの設定
				pDevice->SetTexture(0, g_pD3DTexturePlayer);
				// 描画
				g_pD3DXMeshPlayer->DrawSubset(nCntMat);
			}
			// ライトをoff
			pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
		}
	}
	// プレイヤーの右アームの描画
	for (int i = 0; i < PLAYER_R_ARM_MAX; i++, player_R_Arm++)
	{
		if (player_R_Arm->use == true)
		{	// 使用状態なら描画する
			// ライトをon
			pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_mtxWorldPlayer_R_Arm);
			// ワールドマトリックス作成
			D3DXMatrixTransformation(&g_mtxWorldPlayer_R_Arm, NULL, NULL, &player_R_Arm->scl, &player_R_Arm->rotBasis, &player_R_Arm->qAnswer, &player_R_Arm->Eye);
			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldPlayer_R_Arm);
			// 現在のマテリアルを取得
			pDevice->GetMaterial(&matDef);
			// マテリアル情報に対するポインタを取得
			pD3DXMat = (D3DXMATERIAL*)g_pD3DXBuffMatPlayer_R_Arm->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_nNumMatPlayer_R_Arm; nCntMat++)
			{
				// マテリアルの設定
				pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);
				// テクスチャの設定
				pDevice->SetTexture(0, g_pD3DTexturePlayer_R_Arm);
				// 描画
				g_pD3DXMeshPlayer_R_Arm->DrawSubset(nCntMat);

			}
			// ライトをoff
			pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
		}
	}
	// プレイヤーの左アームの描画
	for (int i = 0; i < PLAYER_L_ARM_MAX; i++, player_L_Arm++)
	{
		if (player_L_Arm->use == true)
		{	// 使用状態なら描画する
			// ライトをon
			pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_mtxWorldPlayer_L_Arm);
			// ワールドマトリックス作成
			D3DXMatrixTransformation(&g_mtxWorldPlayer_L_Arm, NULL, NULL, &player_L_Arm->scl, &player_L_Arm->rotBasis, &player_L_Arm->qAnswer, &player_L_Arm->Eye);
			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldPlayer_L_Arm);
			// 現在のマテリアルを取得
			pDevice->GetMaterial(&matDef);
			// マテリアル情報に対するポインタを取得
			pD3DXMat = (D3DXMATERIAL*)g_pD3DXBuffMatPlayer_L_Arm->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_nNumMatPlayer_L_Arm; nCntMat++)
			{
				// マテリアルの設定
				pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);
				// テクスチャの設定
				pDevice->SetTexture(0, g_pD3DTexturePlayer_L_Arm);
				// 描画
				g_pD3DXMeshPlayer_L_Arm->DrawSubset(nCntMat);

			}
			// ライトをoff
			pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
		}
	}
	// プレイヤーの右レッグの描画
	for (int i = 0; i < PLAYER_R_LEG_MAX; i++, player_R_Leg++)
	{
		if (player_R_Leg->use == true)
		{	// 使用状態なら描画する
			// ライトをon
			pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_mtxWorldPlayer_R_Leg);
			// ワールドマトリックス作成
			D3DXMatrixTransformation(&g_mtxWorldPlayer_R_Leg, NULL, NULL, &player_R_Leg->scl, &player_R_Leg->rotBasis, &player_R_Leg->qAnswer, &player_R_Leg->Eye);
			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldPlayer_R_Leg);
			// 現在のマテリアルを取得
			pDevice->GetMaterial(&matDef);
			// マテリアル情報に対するポインタを取得
			pD3DXMat = (D3DXMATERIAL*)g_pD3DXBuffMatPlayer_R_Leg->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_nNumMatPlayer_R_Leg; nCntMat++)
			{
				// マテリアルの設定
				pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);
				// テクスチャの設定
				pDevice->SetTexture(0, g_pD3DTexturePlayer_R_Leg);
				// 描画
				g_pD3DXMeshPlayer_R_Leg->DrawSubset(nCntMat);
			}
			// ライトをoff
			pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
		}
	}
	// プレイヤーの左レッグの描画
	for (int i = 0; i < PLAYER_L_LEG_MAX; i++, player_L_Leg++)
	{
		if (player_L_Leg->use == true)
		{	// 使用状態なら描画する
			// ライトをon
			pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_mtxWorldPlayer_L_Leg);
			// ワールドマトリックス作成
			D3DXMatrixTransformation(&g_mtxWorldPlayer_L_Leg, NULL, NULL, &player_L_Leg->scl, &player_L_Leg->rotBasis, &player_L_Leg->qAnswer, &player_L_Leg->Eye);
			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldPlayer_L_Leg);
			// 現在のマテリアルを取得
			pDevice->GetMaterial(&matDef);
			// マテリアル情報に対するポインタを取得
			pD3DXMat = (D3DXMATERIAL*)g_pD3DXBuffMatPlayer_L_Leg->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_nNumMatPlayer_L_Leg; nCntMat++)
			{
				// マテリアルの設定
				pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);
				// テクスチャの設定
				pDevice->SetTexture(0, g_pD3DTexturePlayer_L_Leg);
				// 描画
				g_pD3DXMeshPlayer_L_Leg->DrawSubset(nCntMat);
			}
			// ライトをoff
			pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
		}
	}

	{// マテリアルをデフォルトに戻す
		D3DXMATERIAL mat;

		mat.MatD3D.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
		mat.MatD3D.Ambient = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		mat.MatD3D.Emissive = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);

		pDevice->SetMaterial(&mat.MatD3D);
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdatePlayer(void)
{
	PLAYER *player = GetPlayer(0);
	PlayerBorder();

	player->posTmp = player->Eye;

	PlayerMove();

	//AreaHouse(tempPos);
	PlayerEntrance();

	// アニメーション処理
	PlayerAnimation();

	PrintDebugProc("player pos: %f %f %f\n", player->Eye.x, player->Eye.y, player->Eye.z);
	PrintDebugProc("player move: %f %f %f\n", player->move.x, player->move.y, player->move.z);

#ifdef _DEBUG
	CAMERA *camera = GetCamera();

	//PrintDebugProc("\n");

	//PrintDebugProc("player rot: %f\n", player->rotDest.y);
	//PrintDebugProc("\n");

	//PrintDebugProc("camera rot: %f\n", camera->rotCamera.y);
	//PrintDebugProc("\n");

	//PrintDebugProc("camera rotDest: %f\n", camera->rotDest);
	//PrintDebugProc("\n");

	PrintDebugProc("space 0: %d\n", player->havenum[0]);
	PrintDebugProc("space 1: %d\n", player->havenum[1]);
	PrintDebugProc("space 2: %d\n", player->havenum[2]);
	PrintDebugProc("space 3: %d\n", player->havenum[3]);
	PrintDebugProc("space 4: %d\n", player->havenum[4]);
	PrintDebugProc("wt: %d\n", player->weight);
	PrintDebugProc("dash: %f\n", vel);

	if (GetKeyboardTrigger(DIK_V))
	{
		dash = TRUE;
		dashTimer = 0;
		vel = 16.0f;


	}

	if (dash == TRUE)
	{
		player->move.x = -sinf(player->rot.y) * vel;
		player->move.z = -cosf(player->rot.y) * vel;

		dashTimer++;
		vel -= velRate;

		if (dashTimer >= 10)
		{
			dash = FALSE;
			dashTimer = 0;
		}
	}


#endif

	// 角度を修正
	player->rot.y = PiCalculate360(player->rot.y);
	player->rotDest.y = PiCalculate360(player->rotDest.y);

	if (GetStage() == STAGE_GAME
		||GetStage() == STAGE_HOUSE1
		||GetStage() == STAGE_HOUSE2
		||GetStage() == STAGE_HOUSE3
		||GetStage() == STAGE_MYHOUSE)
	{
		// シャドウ
		if (!player->bShadow)
		{	// シャドウ設置
			player->nIdxShadow = CreateShadow(player->Eye, 25.0f, 25.0f);
			player->fSizeShadow = PLAYER_SHADOW_SIZE;
			player->colShadow = D3DXCOLOR(0.7f, 0.7f, 0.7f, 0.7f);
			player->bShadow = true;
		}
		else
		{
			// シャドウ管理
			SetPositionShadow(player->nIdxShadow, D3DXVECTOR3(player->Eye.x, 0.2f, player->Eye.z));
			SetVertexShadow(player->nIdxShadow, player->fSizeShadow, player->fSizeShadow);
			SetColorShadow(player->nIdxShadow, player->colShadow);
		}
	}
	else if (GetStage() == STAGE_RESULT)
	{
		ReleaseShadow(player->nIdxShadow);
		player->bShadow = false;
	}
}

//=============================================================================
// プレイヤーの取得
//=============================================================================
PLAYER *GetPlayer(int no)
{
	return(&playerWk[no]);
}

//=============================================================================
// プレイヤーの移動
//=============================================================================
void PlayerMove(void)
{
	PLAYER *player = &playerWk[0];
	CAMERA *camera = GetCamera();
	INPUTDEVICE *kb = GetInputDevice(INPUT_KEY);
	INPUTDEVICE *gp = GetInputDevice(INPUT_GAMEPAD);

	float fDiffRotY;

	if (GetKeyboardPress(kb->LEFT)||IsButtonPressed(0, gp->LEFT) || IsButtonPressed(0, gp->LEFT_POV))
	{
		if (GetKeyboardPress(kb->UP) || IsButtonPressed(0, gp->UP) || IsButtonPressed(0, gp->UP_POV))
		{// 左前移動
			player->move.x -= cosf(camera->rotCamera.y + D3DX_PI * 0.25f) * VALUE_MOVE_PLAYER;
			player->move.z += sinf(camera->rotCamera.y + D3DX_PI * 0.25f) * VALUE_MOVE_PLAYER;
		
			player->rotDest.y = camera->rotCamera.y + D3DX_PI * 0.75f;
		}
		else if (GetKeyboardPress(kb->DOWN) || IsButtonPressed(0, gp->DOWN) || IsButtonPressed(0, gp->DOWN_POV))
		{// 左後移動
			player->move.x -= cosf(camera->rotCamera.y - D3DX_PI * 0.25f) * VALUE_MOVE_PLAYER;
			player->move.z += sinf(camera->rotCamera.y - D3DX_PI * 0.25f) * VALUE_MOVE_PLAYER;
		
			player->rotDest.y = camera->rotCamera.y + D3DX_PI * 0.25f;
		}
		else
		{// 左移動
			player->move.x -= cosf(camera->rotCamera.y) * VALUE_MOVE_PLAYER;
			player->move.z += sinf(camera->rotCamera.y) * VALUE_MOVE_PLAYER;
			
			player->rotDest.y = camera->rotCamera.y + D3DX_PI * 0.50f;

		}
	}
	else if (GetKeyboardPress(kb->RIGHT) || IsButtonPressed(0, gp->RIGHT) || IsButtonPressed(0, gp->RIGHT_POV))
	{
		if (GetKeyboardPress(kb->UP) || IsButtonPressed(0, gp->UP) || IsButtonPressed(0, gp->UP_POV))
		{// 右前移動
			player->move.x += cosf(camera->rotCamera.y - D3DX_PI * 0.25f) * VALUE_MOVE_PLAYER;
			player->move.z -= sinf(camera->rotCamera.y - D3DX_PI * 0.25f) * VALUE_MOVE_PLAYER;
		
			player->rotDest.y = camera->rotCamera.y - D3DX_PI * 0.75f;
		}
		else if (GetKeyboardPress(kb->DOWN) || IsButtonPressed(0, gp->DOWN) || IsButtonPressed(0, gp->DOWN_POV))
		{// 右後移動
			player->move.x += cosf(camera->rotCamera.y + D3DX_PI * 0.25f) * VALUE_MOVE_PLAYER;
			player->move.z -= sinf(camera->rotCamera.y + D3DX_PI * 0.25f) * VALUE_MOVE_PLAYER;
		
			player->rotDest.y = camera->rotCamera.y - D3DX_PI * 0.25f;
		}
		else
		{// 右移動
			player->move.x += cosf(camera->rotCamera.y) * VALUE_MOVE_PLAYER;
			player->move.z -= sinf(camera->rotCamera.y) * VALUE_MOVE_PLAYER;
		
			player->rotDest.y = camera->rotCamera.y - D3DX_PI * 0.50f;
		}
	}
	else if (GetKeyboardPress(kb->UP) || IsButtonPressed(0, gp->UP) || IsButtonPressed(0, gp->UP_POV))
	{// 前移動
		player->move.x += sinf(camera->rotCamera.y) * VALUE_MOVE_PLAYER;
		player->move.z += cosf(camera->rotCamera.y) * VALUE_MOVE_PLAYER;

		player->rotDest.y = D3DX_PI + camera->rotCamera.y;
	}
	else if (GetKeyboardPress(kb->DOWN) || IsButtonPressed(0, gp->DOWN) || IsButtonPressed(0, gp->DOWN_POV))
	{// 後移動
		player->move.x -= sinf(camera->rotCamera.y) * VALUE_MOVE_PLAYER;
		player->move.z -= cosf(camera->rotCamera.y) * VALUE_MOVE_PLAYER;

		player->rotDest.y = camera->rotCamera.y;
	}

	// 移動量に慣性をかける
	player->move.x += (0.0f - player->move.x) * RATE_MOVE_PLAYER;
	player->move.y += (0.0f - player->move.y) * RATE_MOVE_PLAYER;
	player->move.z += (0.0f - player->move.z) * RATE_MOVE_PLAYER;

	// 所持重量によって移動速度の修正
	// PlayerMoveWt();



	// 位置移動
	player->Eye.x += player->move.x;
	player->Eye.y += player->move.y;
	player->Eye.z += player->move.z;
	// プレイヤーのパーツ移動
	PlayerPartsMove();

	// 目的の角度までの差分
	fDiffRotY = player->rotDest.y - player->rot.y;
	if (fDiffRotY > D3DX_PI)
	{
		fDiffRotY -= D3DX_PI * 2.0f;
	}
	if (fDiffRotY < -D3DX_PI)
	{
		fDiffRotY += D3DX_PI * 2.0f;
	}

	// 目的の角度まで慣性をかける
	player->rot.y += fDiffRotY * RATE_ROTATE_PLAYER;
	if (player->rot.y > D3DX_PI)
	{
		player->rot.y -= D3DX_PI * 2.0f;
	}
	if (player->rot.y < -D3DX_PI)
	{
		player->rot.y += D3DX_PI * 2.0f;
	}

	// 角度を修正
	player->rot.y = PiCalculate360(player->rot.y);

	// 注視点を向くためのY軸回転角度を求める
	player->fangleY = player->rot.y;		// 回転角度を求める

}

//=============================================================================
// プレイヤーの移動制限（フィールド）
//=============================================================================
void PlayerBorder(void)
{
	PLAYER *player = &playerWk[0];
	int fieldnum;

	if (GetStage() == STAGE_GAME)
	{
		fieldnum = 0;
	}
	else if (GetStage() == STAGE_HOUSE1
		|| GetStage() == STAGE_HOUSE2
		|| GetStage() == STAGE_HOUSE3
		|| GetStage() == STAGE_MYHOUSE)
	{
		fieldnum = 1;
	}
	FIELD *field = GetField(fieldnum);


	// 左の壁
	if (player->Eye.x < -field->Size.x / 2 + MOVE_LIMIT)
	{
		player->Eye.x = -field->Size.x / 2 + MOVE_LIMIT;
	}

	// 右の壁
	if (player->Eye.x > field->Size.x / 2 - MOVE_LIMIT)
	{
		player->Eye.x = field->Size.x / 2 - MOVE_LIMIT;
	}

	// 後ろの壁
	if (player->Eye.z < -field->Size.z / 2 + MOVE_LIMIT)
	{
		player->Eye.z = -field->Size.z / 2 + MOVE_LIMIT;
	}

	// 前の壁
	if (player->Eye.z > field->Size.z / 2 - MOVE_LIMIT)
	{
		player->Eye.z = field->Size.z / 2 - MOVE_LIMIT;
	}

}

//=============================================================================
// プレイヤーの移動速度の修正
//=============================================================================
void PlayerMoveWt(void)
{
	PLAYER *player = GetPlayer(0);

	player->move.x *= (1 - PLAYER_WT_ADJ * player->weight);
	player->move.y *= (1 - PLAYER_WT_ADJ * player->weight);
	player->move.z *= (1 - PLAYER_WT_ADJ * player->weight);

}

//=============================================================================
// プレイヤーの移動制限（オブジェクト）
//=============================================================================
//void PlyColiObj(D3DXVECTOR3 objPos, float objLen, float objWid)
//{
//	PLAYER *player = GetPlayer(0);
//	
//	if (player->posTmp.x >= objPos.x + objLen)
//	{
//		player->Eye.x = player->posTmp.x;
//	}
//
//	else if (player->posTmp.x <= objPos.x - objLen)
//	{
//		player->Eye.x = player->posTmp.x;
//	}
//
//	else if (player->posTmp.z <= objPos.z - objWid)
//	{
//		player->Eye.z = player->posTmp.z;
//	}
//
//	else if (player->posTmp.z >= objPos.z + objWid)
//	{
//		player->Eye.z = player->posTmp.z;
//	}
//
//}

//=============================================================================
// 家の入出処理
//=============================================================================
void PlayerEntrance(void)
{
	PLAYER *player = &playerWk[0];
	DOOR *door = GetDoor(0);
	INPUTDEVICE *kb = GetInputDevice(INPUT_KEY);
	INPUTDEVICE *gp = GetInputDevice(INPUT_GAMEPAD);

	bool hitflag = false;
	for (int i = 0; i < HOME_MAX; i++, door++)
	{
		if (door->Use == true)
		{
			D3DXVECTOR3 doorpos(door->Pos.x - 16, door->Pos.y, door->Pos.z);
			if (CollisionBoxToPos(doorpos, player->Eye, D3DXVECTOR2(20.0f, 15.0f)) == true)
			{
				if (GetKeyboardTrigger(kb->NEXTDOOR) || IsButtonTriggered(0, gp->DECIDE))
				{
					if (GetStage() == STAGE_GAME)
					{
						SetFade(FADE_OUT, door->Homeno, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));

					}
					else if (GetStage() == STAGE_HOUSE1
						|| GetStage() == STAGE_HOUSE2
						|| GetStage() == STAGE_HOUSE3
						|| GetStage() == STAGE_MYHOUSE)
					{
						SetFade(FADE_OUT, STAGE_GAME, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
					}
					
					resetno = i;

				}
				hitflag = true;
			}
		}

	}

	if (GetFade() == FADE_IN)
	{
		PlayerPosReset();
	}

	if (GetStage() == STAGE_GAME)
	{
		Button(hitflag, ENTER_BUTTON);
		Button(false, EXIT_BUTTON);
	}
	else
	{
		Button(hitflag, EXIT_BUTTON);
		Button(false, ENTER_BUTTON);
	}
}

//=================================================================
//プレーヤーポジションの再セット関数
//=================================================================
void PlayerPosReset(void)
{
	DOOR *door = GetDoor(resetno);
	PLAYER *player = GetPlayer(0);
	

	if (GetStage() == STAGE_GAME)
	{
		player->rot =
			player->rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		player->Eye = D3DXVECTOR3(door->Pos.x - 10.0f, door->Pos.y, door->Pos.z - 10.0f);

	}
	else
	{
		player->rot =
			player->rotDest = D3DXVECTOR3(0.0f, D3DX_PI, 0.0f);
		player->Eye = D3DXVECTOR3(door->Pos.x - 5.0f, door->Pos.y, door->Pos.z + 25.0f);

	}


}

//================================================================-
//リセットナンバーの設定(番号の玄関の前にセットされる)
//================================================================
void SetResetno(int no)
{
	resetno = no;
}
//=============================================================================
// プレイヤーパーツ親子関係設定関数
//=============================================================================
void SetPlayerParts(void)
{
	PLAYER *player = &playerWk[0];						// プレイヤー本体ポインタ初期化
	PLAYER_R_ARM *player_R_Arm = &player_R_ArmWk[0];	// プレイヤー右アームポインタ初期化
	PLAYER_L_ARM *player_L_Arm = &player_L_ArmWk[0];	// プレイヤー左アームポインタ初期化
	PLAYER_R_LEG *player_R_Leg = &player_R_LegWk[0];	// プレイヤー右レッグポインタ初期化
	PLAYER_L_LEG *player_L_Leg = &player_L_LegWk[0];	// プレイヤー左レッグポインタ初期化

	// 本体に右腕パーツを関連付ける
	for (int i = 0; i < PLAYER_MAX; i++, player++)
	{	// 使用状態のポリスにのみパーツをセット
		if (!player->use) continue;
		// 未使用の右腕パーツをセット
		player_R_Arm = &player_R_ArmWk[0];
		for (int j = 0; j < PLAYER_R_ARM_MAX; j++, player_R_Arm++)
		{	// 本体と同じ番号をセット
			player_R_Arm->num = player->num;
			// 使用状態にする
			player_R_Arm->use = true;
			break;
		}
	}
	// 本体に左腕パーツを関連付ける
	player = &playerWk[0];
	for (int i = 0; i < PLAYER_MAX; i++, player++)
	{	// 未使用の左腕パーツをセット
		player_L_Arm = &player_L_ArmWk[0];
		for (int j = 0; j < PLAYER_R_ARM_MAX; j++, player_L_Arm++)
		{	// 本体と同じ番号をセット
			player_L_Arm->num = player->num;
			// 使用状態にする
			player_L_Arm->use = true;
			break;
		}
	}
	// 本体に右足パーツを関連付ける
	player = &playerWk[0];
	for (int i = 0; i < PLAYER_MAX; i++, player++)
	{	// 未使用の左腕パーツをセット
		player_R_Leg = &player_R_LegWk[0];
		for (int j = 0; j < PLAYER_R_ARM_MAX; j++, player_R_Leg++)
		{	// 本体と同じ番号をセット
			player_R_Leg->num = player->num;
			// 使用状態にする
			player_R_Leg->use = true;
			break;
		}
	}
	// 本体に左足パーツを関連付ける
	player = &playerWk[0];
	for (int i = 0; i < PLAYER_MAX; i++, player++)
	{	// 未使用の左腕パーツをセット
		player_L_Leg = &player_L_LegWk[0];
		for (int j = 0; j < PLAYER_R_ARM_MAX; j++, player_L_Leg++)
		{	// 本体と同じ番号をセット
			player_L_Leg->num = player->num;
			// 使用状態にする
			player_L_Leg->use = true;
			break;
		}
	}
}
//=============================================================================
// アニメーション処理関数
//=============================================================================
void PlayerAnimation(void)
{
	PLAYER *player = &playerWk[0];						// プレイヤー本体ポインタ初期化
	PLAYER_R_ARM *player_R_Arm = &player_R_ArmWk[0];	// プレイヤー右アームポインタ初期化
	PLAYER_L_ARM *player_L_Arm = &player_L_ArmWk[0];	// プレイヤー左アームポインタ初期化
	PLAYER_R_LEG *player_R_Leg = &player_R_LegWk[0];	// プレイヤー右レッグポインタ初期化
	PLAYER_L_LEG *player_L_Leg = &player_L_LegWk[0];	// プレイヤー左レッグポインタ初期化

	// ポリス本体アニメーション処理
	for (int i = 0; i < PLAYER_MAX; i++, player++)
	{
		SetAnimation(player, NULL, NULL,
			D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	}
	// 右アームアニメーション処理
	for (int i = 0; i < PLAYER_R_ARM_MAX; i++, player_R_Arm++)
	{
		SetAnimation(player_R_Arm, PLAYER_R_ARM_ANGLE, PLAYER_R_ARM_ANIM_FRAME,
			D3DXVECTOR3(1.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	}
	// 左アームアニメーション処理
	for (int i = 0; i < PLAYER_L_ARM_MAX; i++, player_L_Arm++)
	{
		SetAnimation(player_L_Arm, PLAYER_L_ARM_ANGLE, PLAYER_L_ARM_ANIM_FRAME,
			D3DXVECTOR3(1.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	}
	// 右レッグアニメーション処理
	for (int i = 0; i < PLAYER_R_LEG_MAX; i++, player_R_Leg++)
	{
		SetAnimation(player_R_Leg, PLAYER_R_LEG_ANGLE, PLAYER_R_LEG_ANIM_FRAME,
			D3DXVECTOR3(1.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	}
	// 左レッグアニメーション処理
	for (int i = 0; i < PLAYER_L_LEG_MAX; i++, player_L_Leg++)
	{
		SetAnimation(player_L_Leg, PLAYER_L_LEG_ANGLE, PLAYER_L_LEG_ANIM_FRAME,
			D3DXVECTOR3(1.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	}
}
//=============================================================================
// プレイヤーパーツ移動処理関数
//=============================================================================
void PlayerPartsMove(void)
{
	PLAYER *player = &playerWk[0];						// プレイヤー本体ポインタ初期化
	PLAYER_R_ARM *player_R_Arm = &player_R_ArmWk[0];	// プレイヤー右アームポインタ初期化
	PLAYER_L_ARM *player_L_Arm = &player_L_ArmWk[0];	// プレイヤー左アームポインタ初期化
	PLAYER_R_LEG *player_R_Leg = &player_R_LegWk[0];	// プレイヤー右レッグポインタ初期化
	PLAYER_L_LEG *player_L_Leg = &player_L_LegWk[0];	// プレイヤー左レッグポインタ初期化

	// 本体と親子関係のパーツを移動
	for (int i = 0; i < PLAYER_MAX; i++, player++)
	{
		// 右アームの移動
		player_R_Arm = &player_R_ArmWk[0];
		for (int j = 0; j < PLAYER_R_ARM_MAX; j++, player_R_Arm++)
		{
			if (!player_R_Arm->use) continue;
			if (player_R_Arm->num == player->num)
			{	// 本体の座標と一致させる
				player_R_Arm->Eye = player->Eye;
				player_R_Arm->At = player->At;
				// 本体と同じ注視点を向くためのY軸回転角度をセット
				player_R_Arm->fangleY = player->fangleY;
			}
		}
		// 左アームの移動
		player_L_Arm = &player_L_ArmWk[0];
		for (int j = 0; j < PLAYER_L_ARM_MAX; j++, player_L_Arm++)
		{
			if (!player_L_Arm->use) continue;
			if (player_L_Arm->num == player->num)
			{	// 本体の座標と一致させる
				player_L_Arm->Eye = player->Eye;
				player_L_Arm->At = player->At;
				// 本体と同じ注視点を向くためのY軸回転角度をセット
				player_L_Arm->fangleY = player->fangleY;
			}
		}
		// 右レッグの移動
		player_R_Leg = &player_R_LegWk[0];
		for (int j = 0; j < PLAYER_R_LEG_MAX; j++, player_R_Leg++)
		{
			if (!player_R_Leg->use) continue;
			if (player_R_Leg->num == player->num)
			{	// 本体の座標と一致させる
				player_R_Leg->Eye = player->Eye;
				player_R_Leg->At = player->At;
				// 本体と同じ注視点を向くためのY軸回転角度をセット
				player_R_Leg->fangleY = player->fangleY;
			}
		}
		// 左レッグの移動
		player_L_Leg = &player_L_LegWk[0];
		for (int j = 0; j < PLAYER_L_LEG_MAX; j++, player_L_Leg++)
		{
			if (!player_L_Leg->use) continue;
			if (player_L_Leg->num == player->num)
			{	// 本体の座標と一致させる
				player_L_Leg->Eye = player->Eye;
				player_L_Leg->At = player->At;
				// 本体と同じ注視点を向くためのY軸回転角度をセット
				player_L_Leg->fangleY = player->fangleY;
			}
		}
	}
}
//=============================================================================
// アニメーション設定関数
// (引数1:設定対象のクラスへのポインタ,
//  引数2:XZ軸回転角度,
//  引数3:一往復にかかるフレーム数,
//  引数4:回転軸XZ,
//  引数5:回転軸Y)
//=============================================================================
template <typename CLASS> void SetAnimation(CLASS *pIn, float fAngle, int frame, D3DXVECTOR3 AxisXZ, D3DXVECTOR3 AxisY)		// メモ:typenameはclassと書いてもよい
{
	PLAYER *player = &playerWk[0];						// プレイヤー本体ポインタ初期化
	float move = D3DXVec3Length(&player->move);			// 移動ベクトルの大きさ計算

	if (pIn->use)
	{	// 使用か未使用かチェック
		// 回転軸XZの設定
		pIn->axisXZ = AxisXZ;
		// 回転軸Yの設定
		pIn->axisY = AxisY;
		// XZ軸回転角度の設定
		if (pIn->fangleXZ >= fAngle)
		{	// 一定角度までパーツ上がったらフラグ切り替え
			pIn->rotf = false;
		}
		if (pIn->fangleXZ <= -fAngle)
		{	// 一定角度までパーツ上がったらフラグ切り替え
			pIn->rotf = true;
		}
		if (pIn->rotf == true)
		{	// 正の回転
			pIn->fangleXZ += fAngle / frame;
			if (pIn->fangleXZ > D3DX_PI)
			{
				pIn->fangleXZ -= D3DX_PI * 2.0f;
			}
		}
		if (pIn->rotf == false)
		{	// 負の回転
			pIn->fangleXZ -= fAngle / frame;
			if (pIn->fangleXZ < -D3DX_PI)
			{
				pIn->fangleXZ += D3DX_PI * 2.0f;
			}
		}
		// XZ回転軸ベクトルが0の場合のエラー処理
		if (pIn->axisXZ == D3DXVECTOR3(0.0f, 0.0f, 0.0f) || (move < 0.001f))
		{	// 回転角度を0にする
			pIn->fangleXZ = 0.0f;
		}
		// Y回転軸ベクトルが0の場合のエラー処理
		if (pIn->axisY == D3DXVECTOR3(0.0f, 0.0f, 0.0f))
		{	// 回転角度を0にする
			pIn->fangleY = 0.0f;
		}
		// 回転クォータニオンを生成
		D3DXQuaternionRotationAxis(&pIn->qRotateXZ, &pIn->axisXZ, pIn->fangleXZ);	// XZ軸回転クォータニオン生成
		D3DXQuaternionRotationAxis(&pIn->qRotateY, &pIn->axisY, pIn->fangleY);		// Y軸回転クォータニオン生成(Atに向かせる)
		D3DXQuaternionMultiply(&pIn->qAnswer, &pIn->qRotateXZ, &pIn->qRotateY);		// 回転クォータニオンを合成
	}
}
