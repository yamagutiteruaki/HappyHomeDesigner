//=============================================================================
//
// 地面処理 [field.cpp]
// Author : GP11B243　32 山口輝明
//
//=============================================================================
#include "home.h"
#include "debugproc.h"
#include "calculate.h"
#include "input.h"
#include "stage.h"
#include "fade.h"
#include "player.h"
#include "collision.h"


/* Debug */
#ifdef _DEBUG
#include "debugproc.h"
#endif

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MOVE_LIMIT				(0)
#define HOUSE_LEN				(200.0f)
#define HOUSE_WID				(170.0f)

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void AreaHouse(void);

//*****************************************************************************
// グローバル変数
//*****************************************************************************

LPDIRECT3DTEXTURE9		g_pD3DTextureHome[HOME_MAX];	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffHome[HOME_MAX];	// 頂点バッファへのポインタ

LPDIRECT3DTEXTURE9		g_pD3DTextureDoor[HOME_MAX];	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffDoor[HOME_MAX];	// 頂点バッファへのポインタ

HOME					g_aHome[HOME_MAX];
DOOR					g_aDoor[HOME_MAX];

LPD3DXMESH			g_pD3DXMeshHome[HOME_MAX];			// ID3DXMeshインターフェイスへのポインタ
LPD3DXBUFFER		g_pD3DXBuffMatHome[HOME_MAX];		// メッシュのマテリアル情報を格納
DWORD				g_nNumMatHome[HOME_MAX];				// 属性情報の総数

LPD3DXMESH			g_pD3DXMeshDoor[HOME_MAX];			// ID3DXMeshインターフェイスへのポインタ
LPD3DXBUFFER		g_pD3DXBuffMatDoor[HOME_MAX];		// メッシュのマテリアル情報を格納
DWORD				g_nNumMatDoor[HOME_MAX];				// 属性情報の総数

const char *FileNameHome[HOME_MAX] =
{
	"data/MODEL/HOUSE/house_nobi.x",		// 家1
	"data/MODEL/HOUSE/house_nobi.x",		// 家2
	"data/MODEL/HOUSE/house_nobi.x",		// 家3
	"data/MODEL/HOUSE/house03.x",		// 自宅
};

const char *FileNameDoor[HOME_MAX] =
{
	"data/MODEL/ITEM/doa.x",		// ドア1
	"data/MODEL/ITEM/doa.x",		// ドア2
	"data/MODEL/ITEM/doa.x",		// ドア3
	"data/MODEL/ITEM/doa.x",		// ドア4
};
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitHome(int nType)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	HOME  *home = GetHome(0);


	//家の設定
	for (int i = 0; i < HOME_MAX; i++, home++)
	{
		if (nType == STAGE_INIT_FAST)
		{
			// Xファイルの読み込み
			if (FAILED(D3DXLoadMeshFromX(FileNameHome[i],
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&g_pD3DXBuffMatHome[i],
				NULL,
				&g_nNumMatHome[i],
				&g_pD3DXMeshHome[i])))
			{
				return E_FAIL;
			}
		}

		home->Pos.x = -(HOME_DISTANCE)+i % 2 * (HOME_DISTANCE * 2);	//X座標の設定
		home->Pos.y = 0.0f;//Y座標の設定
		home->Pos.z = HOME_DISTANCE + i / 2 * (-HOME_DISTANCE * 2);	//Z座標の設定

		home->Rot.y = D3DX_PI / 2;

		home->Scl.x = 1.0f;
		home->Scl.y = 1.0f;
		home->Scl.z = 1.0f;

		home->len = HOUSE_LEN;
		home->wid = HOUSE_WID;

	}

	home = GetHome(0);
	DOOR *door = GetDoor(0);
	//ドアの設定
	for (int i = 0; i < HOME_MAX; i++, door++, home++)
	{
		if (nType == STAGE_INIT_FAST)
		{
			// Xファイルの読み込み
			if (FAILED(D3DXLoadMeshFromX(FileNameDoor[i],
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&g_pD3DXBuffMatDoor[i],
				NULL,
				&g_nNumMatDoor[i],
				&g_pD3DXMeshDoor[i])))
			{
				return E_FAIL;
			}
		}
		door->Pos.x = home->Pos.x + 70.0f*home->Scl.x;	//X座標の設定
		door->Pos.y = home->Pos.y;		//Y座標の設定
		door->Pos.z = home->Pos.z - 75.0f*home->Scl.z;	//Z座標の設定


		door->Rot.y = 0.0f;

		door->Scl.x = 2.0f;
		door->Scl.y = 2.0f;
		door->Scl.z = 1.0f;

		door->Homeno = STAGE_HOUSE1 + i;
		door->Use = true;


	}


	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitHome(void)
{

	//家
	for (int i = 0; i < HOME_MAX; i++)
	{
		if (g_pD3DTextureHome[i] != NULL)
		{// テクスチャの開放
			g_pD3DTextureHome[i]->Release();
			g_pD3DTextureHome[i] = NULL;
		}

		if (g_pD3DXMeshHome[i] != NULL)
		{// メッシュの開放
			g_pD3DXMeshHome[i]->Release();
			g_pD3DXMeshHome[i] = NULL;
		}

		if (g_pD3DXBuffMatHome[i] != NULL)
		{// マテリアルの開放
			g_pD3DXBuffMatHome[i]->Release();
			g_pD3DXBuffMatHome[i] = NULL;
		}

	}

	//ドア
	for (int i = 0; i < HOME_MAX; i++)
	{
		if (g_pD3DTextureDoor[i] != NULL)
		{// テクスチャの開放
			g_pD3DTextureDoor[i]->Release();
			g_pD3DTextureDoor[i] = NULL;
		}

		if (g_pD3DXMeshDoor[i] != NULL)
		{// メッシュの開放
			g_pD3DXMeshDoor[i]->Release();
			g_pD3DXMeshDoor[i] = NULL;
		}

		if (g_pD3DXBuffMatDoor[i] != NULL)
		{// マテリアルの開放
			g_pD3DXBuffMatDoor[i]->Release();
			g_pD3DXBuffMatDoor[i] = NULL;
		}

	}

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateHome(void)
{
	AreaHouse();

#ifdef _DEBUG
	if (GetKeyboardTrigger(DIK_F1))
	{
		SetFade(FADE_OUT, STAGE_HOUSE1, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
	}
	else if (GetKeyboardTrigger(DIK_F2))
	{
		SetFade(FADE_OUT, STAGE_HOUSE2, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
	}
	else if (GetKeyboardTrigger(DIK_F3))
	{
		SetFade(FADE_OUT, STAGE_HOUSE3, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
	}
	else if (GetKeyboardTrigger(DIK_F4))
	{
		SetFade(FADE_OUT, STAGE_MYHOUSE, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
	}
	else if (GetKeyboardTrigger(DIK_F5))
	{
		SetFade(FADE_OUT, STAGE_GAME, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
	}
#endif


	DOOR *door = GetDoor(0);
	HOME *home = GetHome(0);
	if (GetStage() == STAGE_GAME)
	{
		for (int i = 0; i < HOME_MAX; i++, home++, door++)
		{
			door->Pos.x = home->Pos.x + 70.0f*home->Scl.x;	//X座標の設定
			door->Pos.y = home->Pos.y;		//Y座標の設定
			door->Pos.z = home->Pos.z - 75.0f*home->Scl.z;	//Z座標の設定
			door->Use = true;
		}
	}
	else if (GetStage() == STAGE_HOUSE1
		|| GetStage() == STAGE_HOUSE2
		|| GetStage() == STAGE_HOUSE3
		|| GetStage() == STAGE_MYHOUSE)
	{
		for (int i = 0; i < HOME_MAX; i++, door++)
		{
			door->Pos = D3DXVECTOR3(90.0f, 0.0f, -125.0f);
			door->Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			if (GetStage() == i + 4)
			{
				door->Use = true;
				PrintDebugProc("DOORNO: %d\n", door->Homeno);

			}
			else
			{
				door->Use = false;
			}
		}
	}
	//HOME *House = GetHome(0);
	//PrintDebugProc("House 0: %f, %f\n", (House + 0)->Pos.x, (House + 0)->Pos.z);
	//PrintDebugProc("House 1: %f, %f\n", (House + 1)->Pos.x, (House + 1)->Pos.z);
	//PrintDebugProc("House 2: %f, %f\n", (House + 2)->Pos.x, (House + 2)->Pos.z);
	//PrintDebugProc("House 3: %f, %f\n", (House + 3)->Pos.x, (House + 3)->Pos.z);
	//PrintDebugProc("\n");


}

//=============================================================================
// 描画処理
//=============================================================================
void DrawHome(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTranslate, mtxScale;
	D3DXMATERIAL *pD3DXMat;
	D3DXMATERIAL matDef;
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

	HOME *home = GetHome(0);

	if (GetStage() == STAGE_GAME)
	{
		for (int i = 0; i < HOME_MAX; i++, home++)
		{
			// ライトをon
			pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&home->world);

			// スケールを反映
			D3DXMatrixScaling(&mtxScale, home->Scl.x,
				home->Scl.y,
				home->Scl.z);
			D3DXMatrixMultiply(&home->world,
				&home->world, &mtxScale);

			// 回転を反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, home->Rot.y, home->Rot.x, home->Rot.z);
			D3DXMatrixMultiply(&home->world, &home->world, &mtxRot);

			// 移動を反映
			D3DXMatrixTranslation(&mtxTranslate, home->Pos.x, home->Pos.y, home->Pos.z);
			D3DXMatrixMultiply(&home->world, &home->world, &mtxTranslate);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &home->world);

			// 現在のマテリアルを取得
			pDevice->GetMaterial(&matDef.MatD3D);



			// マテリアル情報に対するポインタを取得
			pD3DXMat = (D3DXMATERIAL*)g_pD3DXBuffMatHome[i]->GetBufferPointer();

			for (int j = 0; j < (int)g_nNumMatHome[i]; j++)
			{
				// マテリアルの設定
				pDevice->SetMaterial(&pD3DXMat[j].MatD3D);

				// テクスチャの設定
				pDevice->SetTexture(0, g_pD3DTextureHome[i]);

				// 描画
				g_pD3DXMeshHome[i]->DrawSubset(j);
			}

			// ライトをoff
			pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);


			//D3DXMATERIAL mat;
			//
			//mat.MatD3D.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
			//mat.MatD3D.Ambient = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
			//mat.MatD3D.Emissive = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);

			// マテリアルをデフォルトに戻す
			pDevice->SetMaterial(&matDef.MatD3D);
		}
	}

	DOOR *door = GetDoor(0);
	for (int i = 0; i < HOME_MAX; i++, home++, door++)
	{
		if (door->Use == true)
		{
			// ライトをon
			pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&door->world);

			// スケールを反映
			D3DXMatrixScaling(&mtxScale, door->Scl.x,
				door->Scl.y,
				door->Scl.z);
			D3DXMatrixMultiply(&door->world,
				&door->world, &mtxScale);


			// 回転を反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, door->Rot.y, door->Rot.x, door->Rot.z);
			D3DXMatrixMultiply(&door->world, &door->world, &mtxRot);

			// 移動を反映
			D3DXMatrixTranslation(&mtxTranslate, door->Pos.x, door->Pos.y, door->Pos.z);
			D3DXMatrixMultiply(&door->world, &door->world, &mtxTranslate);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &door->world);

			// 現在のマテリアルを取得
			pDevice->GetMaterial(&matDef.MatD3D);



			// マテリアル情報に対するポインタを取得
			pD3DXMat = (D3DXMATERIAL*)g_pD3DXBuffMatDoor[i]->GetBufferPointer();

			for (int j = 0; j < (int)g_nNumMatDoor[i]; j++)
			{
				// マテリアルの設定
				pDevice->SetMaterial(&pD3DXMat[j].MatD3D);

				// テクスチャの設定
				pDevice->SetTexture(0, g_pD3DTextureDoor[i]);

				// 描画
				g_pD3DXMeshDoor[i]->DrawSubset(j);
			}

			// ライトをoff
			pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);


			//D3DXMATERIAL mat;
			//
			//mat.MatD3D.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
			//mat.MatD3D.Ambient = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
			//mat.MatD3D.Emissive = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);

			// マテリアルをデフォルトに戻す
			pDevice->SetMaterial(&matDef.MatD3D);
		}
	}
}



HOME *GetHome(int no)
{
	return &g_aHome[no];
}
DOOR *GetDoor(int no)
{
	return &g_aDoor[no];
}

//=============================================================================
// 家
//=============================================================================
void AreaHouse()
{
	PLAYER *player = GetPlayer(0);
	HOME *house = GetHome(0);

	for (int i = 0; i < HOME_MAX; i++, house++)
	{
		if (CollisionBoxToPos(house->Pos, player->Eye, D3DXVECTOR2((house->len / 2), (house->wid / 2))) == TRUE)
		{

			//player->Eye = player->tmpPos;

			//PlyColiObj(house->Pos, (house->len / 2), (house->wid / 2));

			CBTP_resetPos(
				&(player->Eye),
				player->posTmp,
				house->Pos,
				(house->len / 2),
				(house->wid / 2)
			);
		}

	}

}