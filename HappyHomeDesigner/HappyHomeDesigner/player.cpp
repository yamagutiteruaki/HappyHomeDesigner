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

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	VALUE_MOVE_PLAYER		(1.00f)						// 移動速度係数
#define	RATE_MOVE_PLAYER		(0.20f)						// 移動慣性係数
#define	VALUE_ROTATE_PLAYER		(D3DX_PI * 0.05f)			// 回転速度
#define	RATE_ROTATE_PLAYER		(0.20f)						// 回転慣性係数

#define	PLAYER_ANIM_MAX			(1)							// プレイヤーのアニメーションパターン数
#define	PLAYER_ANIM_SEC			(1)							// アニメーション一巡にかかる秒数

#define PLAYER_HP				(1)							// 残機

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void PlayerMove(void);

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
	"data/MODEL/PLAYER/player01.x",

};

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
		player->Eye = field->Pos;
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

		// useフラグをtrueに設定
		player->use = true;

		// プレイヤーのHP
		player->hp = PLAYER_HP;

		// プレイヤーの移動速度初期化
		player->speed = VALUE_MOVE_PLAYER;

		// アニメーション番号初期化
		// 最初は直立状態に設定
		player->anim = 0;

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
	PlayerMove();

#ifdef _DEBUG
	//PLAYER *player = &playerWk[0];
	//CAMERA *camera = GetCamera();

	//PrintDebugProc("player rot: %f\n", player->rotDest.y);
	//PrintDebugProc("\n");

	//PrintDebugProc("camera rot: %f\n", camera->rotCamera.y);
	//PrintDebugProc("\n");

	//PrintDebugProc("camera length: %f\n", camera->fLength);
	// PrintDebugProc("\n");
	
#endif

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

}