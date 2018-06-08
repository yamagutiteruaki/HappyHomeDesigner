//=============================================================================
//
// 地面処理 [field.cpp]
// Author : GP11B243　32 山口輝明
//
//=============================================================================
#include "field.h"
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
HRESULT MakeVertexField(LPDIRECT3DDEVICE9 pDevice);
void AreaHouse(void);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureField[FIELD_MAX];	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffField[FIELD_MAX];	// 頂点バッファへのポインタ

LPDIRECT3DTEXTURE9		g_pD3DTextureHome [HOME_MAX];	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffHome [HOME_MAX];	// 頂点バッファへのポインタ

LPDIRECT3DTEXTURE9		g_pD3DTextureDoor[HOME_MAX];	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffDoor[HOME_MAX];	// 頂点バッファへのポインタ

FIELD					g_aField[FIELD_MAX];
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
const char *FileNameField[FIELD_MAX] =
{
	TEXTURE_FIELD,		// 家1
	TEXTURE_FIELD1,		// 家2
};
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitField(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	FIELD *field = GetField(0);
	HOME  *home = GetHome(0);

	for (int i = 0; i < FIELD_MAX; i++, field++)
	{

		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,					// デバイスへのポインタ
			FileNameField[i],			// ファイルの名前
			&g_pD3DTextureField[i]);	// 読み込むメモリー


		field->Pos.x = 0.0f;	//X座標の設定
		field->Pos.y = 0.0f;//Y座標は0固定
		field->Pos.z = 0.0f;	//Z座標の設定

		field->Size = D3DXVECTOR3(FIELD_SIZE_X / (i*3 + 1), 0.0f, FIELD_SIZE_Z / (i*3 + 1));
		//field->Size = D3DXVECTOR3(FIELD_SIZE_X/2, 0.0f, FIELD_SIZE_Z/2);

	}
		MakeVertexField(pDevice);

	//家の設定
	for (int i = 0; i < HOME_MAX; i++, home++)
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

		home->Pos.x = -(HOME_DISTANCE) + i % 2 * (HOME_DISTANCE*2);	//X座標の設定
		home->Pos.y = 0.0f;//Y座標の設定
		home->Pos.z = HOME_DISTANCE + i / 2 * (-HOME_DISTANCE *2);	//Z座標の設定

		home->Rot.y = D3DX_PI / 2 ;

		home->Scl.x = 1.0f;
		home->Scl.y = 1.0f;
		home->Scl.z = 1.0f;

		home->len = HOUSE_LEN;
		home->wid = HOUSE_WID;

	}

	home = GetHome(0);
	DOOR *door = GetDoor(0);
	//ドアの設定
	for (int i = 0; i < HOME_MAX; i++, door++ ,home++)
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

		door->Pos.x = home->Pos.x+70.0f*home->Scl.x;	//X座標の設定
		door->Pos.y = home->Pos.y;		//Y座標の設定
		door->Pos.z = home->Pos.z -75.0f*home->Scl.z;	//Z座標の設定


		door->Rot.y = 0.0f;
		
		door->Scl.x = 2.0f;
		door->Scl.y = 2.0f;
		door->Scl.z = 1.0f;

		door->Homeno = STAGE_HOUSE1 + i;


	}


	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitField(void)
{
	for (int i = 0; i < FIELD_MAX; i++)
	{
		//フィールド
		if (g_pD3DTextureField != NULL)
		{// テクスチャの開放
			g_pD3DTextureField[i]->Release();
			g_pD3DTextureField[i] = NULL;
		}

		if (g_pD3DVtxBuffField != NULL)
		{// 頂点バッファの開放
			g_pD3DVtxBuffField[i]->Release();
			g_pD3DVtxBuffField[i] = NULL;
		}
	}

	//家
	for ( int i=0; i < HOME_MAX; i++)
	{
		if (g_pD3DTextureHome[i]!= NULL)
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
void UpdateField(void)
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

	//HOME *House = GetHome(0);
	//PrintDebugProc("House 0: %f, %f\n", (House + 0)->Pos.x, (House + 0)->Pos.z);
	//PrintDebugProc("House 1: %f, %f\n", (House + 1)->Pos.x, (House + 1)->Pos.z);
	//PrintDebugProc("House 2: %f, %f\n", (House + 2)->Pos.x, (House + 2)->Pos.z);
	//PrintDebugProc("House 3: %f, %f\n", (House + 3)->Pos.x, (House + 3)->Pos.z);
	//PrintDebugProc("\n");

#endif

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawField(void)
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
	FIELD *field = GetField(fieldnum);

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&field->world);


	// 移動を反映
	D3DXMatrixTranslation(&mtxTranslate, field->Pos.x, field->Pos.y, field->Pos.z);
	D3DXMatrixMultiply(&field->world, &field->world, &mtxTranslate);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &field->world);

	// 頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, g_pD3DVtxBuffField[fieldnum], 0, sizeof(VERTEX_3D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pD3DTextureField[fieldnum]);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

	HOME *home = GetHome(0);

	if (GetStage() == STAGE_GAME)
	{
		for (int i = 0; i < HOME_MAX; i++, home++)
		{
			// ライトをon
			pDevice->SetRenderState(D3DRS_LIGHTING,TRUE);

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


		DOOR *door = GetDoor(0);
		for (int i = 0; i < HOME_MAX; i++, home++, door++)
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

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexField(LPDIRECT3DDEVICE9 pDevice)
{	
	FIELD *field = GetField(0);
	VERTEX_3D *pVtx;
	for (int i = 0; i < FIELD_MAX; i++, field++, pVtx += 4)
	{
		// オブジェクトの頂点バッファを生成
		if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX* FIELD_MAX,	// 頂点データ用に確保するバッファサイズ(バイト単位)
			D3DUSAGE_WRITEONLY,			// 頂点バッファの使用法　
			FVF_VERTEX_3D,				// 使用する頂点フォーマット
			D3DPOOL_MANAGED,			// リソースのバッファを保持するメモリクラスを指定
			&g_pD3DVtxBuffField[i],		// 頂点バッファインターフェースへのポインタ
			NULL)))						// NULLに設定
		{
			return E_FAIL;
		}
		//for (int i = 0; i < FIELD_MAX; i++)
		{//頂点バッファの中身を埋める

			// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
			g_pD3DVtxBuffField[i]->Lock(0, 0, (void**)&pVtx, 0);



			{
				// 頂点座標の設定
				pVtx[0].vtx = D3DXVECTOR3(-field->Size.x / 2, 0.0f, field->Size.z / 2);
				pVtx[1].vtx = D3DXVECTOR3(field->Size.x / 2, 0.0f, field->Size.z / 2);
				pVtx[2].vtx = D3DXVECTOR3(-field->Size.x / 2, 0.0f, -field->Size.z / 2);
				pVtx[3].vtx = D3DXVECTOR3(field->Size.x / 2, 0.0f, -field->Size.z / 2);

				// 法線ベクトルの設定
				pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
				pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
				pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
				pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

				// 反射光の設定
				pVtx[0].diffuse =
					pVtx[1].diffuse =
					pVtx[2].diffuse =
					pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

				// テクスチャ座標の設定
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
			}
			// 頂点データをアンロックする
			g_pD3DVtxBuffField[i]->Unlock();
		}
	}
	return S_OK;
}

FIELD *GetField(int no)
{
	return &g_aField[no];
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