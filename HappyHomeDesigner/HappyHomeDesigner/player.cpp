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
#include "field.h"
#include "calculate.h"
#include "collision.h"
#include "fade.h"
#include "button.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	VALUE_MOVE_PLAYER		(1.00f)						// 移動速度係数
#define	RATE_MOVE_PLAYER		(0.20f)						// 移動慣性係数
#define	VALUE_ROTATE_PLAYER		(D3DX_PI * 0.05f)			// 回転速度
#define	RATE_ROTATE_PLAYER		(0.20f)						// 回転慣性係数

#define	PLAYER_ANIM_MAX			(1)							// プレイヤーのアニメーションパターン数
#define	PLAYER_ANIM_SEC			(1)							// アニメーション一巡にかかる秒数

#define MOVE_LIMIT				(10)

#define PLAYER_HP				(1)							// 残機
#define PLAYER_POS_ADJ			(20.0f)						// 初期位置調整値
#define PLAYER_WT_ADJ			(0.08f)						// 移動速度調整値


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void PlayerMove(void);
void PlayerMoveWt(void);
void PlayerBorder(void);
void PlayerEntrance(void);


//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9	g_pD3DTexturePlayer[PLAYER_ANIM_MAX];		// テクスチャ読み込み場所
LPD3DXMESH			g_pD3DXMeshPlayer[PLAYER_ANIM_MAX];			// ID3DXMeshインターフェイスへのポインタ
LPD3DXBUFFER		g_pD3DXBuffMatPlayer[PLAYER_ANIM_MAX];		// メッシュのマテリアル情報を格納
DWORD				g_nNumMatPlayer[PLAYER_ANIM_MAX];			// 属性情報の総数

D3DXMATRIX			g_mtxWorldPlayer;							// ワールドマトリックス

PLAYER				playerWk[PLAYER_MAX];						// プレイヤー格納ワーク

const char *FileNamePlayer[PLAYER_ANIM_MAX] =					// モデル読み込む
{
	"data/MODEL/PLAYER/standingman.x",

};

bool dash = FALSE;
int dashTimer = 0;
float vel = 0.0f;
const float velRate = 0.4f;
int exitno = 0;


//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitPlayer(int nType)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	PLAYER *player = &playerWk[0];
	FIELD *field = GetField(0);

	if (nType == STAGE_INIT_FAST)
	{
		for (int i = 0; i < PLAYER_ANIM_MAX; i++)
		{
			g_pD3DTexturePlayer[i] = NULL;
			g_pD3DXMeshPlayer[i] = NULL;
			g_pD3DXBuffMatPlayer[i] = NULL;


			// Xファイルの読み込み
			if (FAILED(D3DXLoadMeshFromX(FileNamePlayer[i],
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&g_pD3DXBuffMatPlayer[i],
				NULL,
				&g_nNumMatPlayer[i],
				&g_pD3DXMeshPlayer[i])))
			{
				return E_FAIL;
			}

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

		// プレイヤーのHP
		player->hp = PLAYER_HP;

		// プレイヤーの移動速度初期化
		player->speed = VALUE_MOVE_PLAYER;

		// アニメーション番号初期化
		// 最初は直立状態に設定
		player->anim = 0;

		// 持ち物の総重量
		player->weight = 0;

		// プレイヤーの持ち物
		for (int j = 0; j < HAVE_MAX; j++)
		{
			player->havenum[j] = -1;
		}

	}

	return S_OK;

}
//=============================================================================
// 終了処理
//=============================================================================
void UninitPlayer(void)
{
	for (int i = 0; i < PLAYER_ANIM_MAX; i++)
	{
		if (g_pD3DTexturePlayer[i] != NULL)
		{// テクスチャの開放
			g_pD3DTexturePlayer[i]->Release();
			g_pD3DTexturePlayer[i] = NULL;
		}

		if (g_pD3DXMeshPlayer[i] != NULL)
		{// メッシュの開放
			g_pD3DXMeshPlayer[i]->Release();
			g_pD3DXMeshPlayer[i] = NULL;
		}

		if (g_pD3DXBuffMatPlayer[i] != NULL)
		{// マテリアルの開放
			g_pD3DXBuffMatPlayer[i]->Release();
			g_pD3DXBuffMatPlayer[i] = NULL;
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTranslate, mtxScale;
	D3DXMATERIAL *pD3DXMat;
	D3DMATERIAL9 matDef;

	PLAYER *player = &playerWk[0];

	for (int i = 0; i < PLAYER_MAX; i++, player++)
	{
		if (player->use == true)	// 使用状態なら描画する
		{
			// ライトをon
			pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_mtxWorldPlayer);

			// スケールを反映
			D3DXMatrixScaling(&mtxScale, player->scl.x,
				player->scl.y,
				player->scl.z);
			D3DXMatrixMultiply(&g_mtxWorldPlayer,
				&g_mtxWorldPlayer, &mtxScale);

			// 回転を反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, player->rot.y, player->rot.x, player->rot.z);
			D3DXMatrixMultiply(&g_mtxWorldPlayer, &g_mtxWorldPlayer, &mtxRot);

			//// 移動を反映
			D3DXMatrixTranslation(&mtxTranslate, player->Eye.x, player->Eye.y, player->Eye.z);
			D3DXMatrixMultiply(&g_mtxWorldPlayer, &g_mtxWorldPlayer, &mtxTranslate);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldPlayer);

			// 現在のマテリアルを取得
			pDevice->GetMaterial(&matDef);

			// マテリアル情報に対するポインタを取得
			pD3DXMat = (D3DXMATERIAL*)g_pD3DXBuffMatPlayer[player->anim]->GetBufferPointer();

			for (int i = 0; i < (int)g_nNumMatPlayer[player->anim]; i++)
			{
				// マテリアルの設定
				pDevice->SetMaterial(&pD3DXMat[i].MatD3D);

				// テクスチャの設定
				pDevice->SetTexture(0, g_pD3DTexturePlayer[player->anim]);

				// 描画
				g_pD3DXMeshPlayer[player->anim]->DrawSubset(i);

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

	player->posTmp = player->Eye;

	PlayerMove();

	//AreaHouse(tempPos);
	PlayerBorder();
	PlayerEntrance();

#ifdef _DEBUG
	CAMERA *camera = GetCamera();

	PrintDebugProc("player pos: %f %f %f\n", player->Eye.x, player->Eye.y , player->Eye.z);
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

	float fDiffRotY;

	if (GetKeyboardPress(DIK_LEFT))
	{
		if (GetKeyboardPress(DIK_UP))
		{// 左前移動
			player->move.x -= cosf(camera->rotCamera.y + D3DX_PI * 0.25f) * VALUE_MOVE_PLAYER;
			player->move.z += sinf(camera->rotCamera.y + D3DX_PI * 0.25f) * VALUE_MOVE_PLAYER;
		
			player->rotDest.y = camera->rotCamera.y + D3DX_PI * 0.75f;
		}
		else if (GetKeyboardPress(DIK_DOWN))
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
	else if (GetKeyboardPress(DIK_RIGHT))
	{
		if (GetKeyboardPress(DIK_UP))
		{// 右前移動
			player->move.x += cosf(camera->rotCamera.y - D3DX_PI * 0.25f) * VALUE_MOVE_PLAYER;
			player->move.z -= sinf(camera->rotCamera.y - D3DX_PI * 0.25f) * VALUE_MOVE_PLAYER;
		
			player->rotDest.y = camera->rotCamera.y - D3DX_PI * 0.75f;
		}
		else if (GetKeyboardPress(DIK_DOWN))
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
	else if (GetKeyboardPress(DIK_UP))
	{// 前移動
		player->move.x += sinf(camera->rotCamera.y) * VALUE_MOVE_PLAYER;
		player->move.z += cosf(camera->rotCamera.y) * VALUE_MOVE_PLAYER;

		player->rotDest.y = D3DX_PI + camera->rotCamera.y;
	}
	else if (GetKeyboardPress(DIK_DOWN))
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
void PlayerMoveWt()
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
// 家に入る処理
//=============================================================================
void PlayerEntrance(void)
{
	PLAYER *player = &playerWk[0];
	DOOR *door = GetDoor(0);

	bool hitflag = false;
	for (int i = 0; i < HOME_MAX; i++, door++)
	{
		if (door->Use == true)
		{
			D3DXVECTOR3 doorpos(door->Pos.x - 16, door->Pos.y, door->Pos.z);
			if (CollisionBoxToPos(doorpos, player->Eye, D3DXVECTOR2(20.0f, 15.0f)) == true)
			{
				if (GetKeyboardTrigger(DIK_SPACE))
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
						exitno = door->Homeno-4;
					}

				}
				hitflag = true;

			}
		}
	}

	if (GetFade() == FADE_IN)
	{
		if (GetStage() == STAGE_GAME)
		{
			door = GetDoor(exitno);
			player->Eye = D3DXVECTOR3(door->Pos.x-10.0f, 0.0f, door->Pos.z-10.0f);
			player->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			player->rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		}
		else if (GetStage() == STAGE_HOUSE1
			|| GetStage() == STAGE_HOUSE2
			|| GetStage() == STAGE_HOUSE3
			|| GetStage() == STAGE_MYHOUSE)
		{
			player->Eye = D3DXVECTOR3(100.0f, 0.0f, -110.0f);
			player->rot = D3DXVECTOR3(0.0f, D3DX_PI, 0.0f);
			player->rotDest = D3DXVECTOR3(0.0f, D3DX_PI, 0.0f);
		}

	}

	Button(hitflag);
}
