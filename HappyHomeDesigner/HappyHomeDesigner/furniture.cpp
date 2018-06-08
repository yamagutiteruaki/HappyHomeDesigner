//=============================================================================
//
// 家具処理 [furniture.cpp]
// Author : GP12A295-19-千坂浩太
//
//=============================================================================
#include "furniture.h"
#include "field.h"
#include "main.h"
#include "debugproc.h"
#include "stage.h"
#include "load_csv.h"
#include "player.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void FurnitureColi(void);
void FurnitureWt(void);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9	g_pD3DTextureFurniture[FURNITURE_TYPE_MAX];		// テクスチャ読み込み場所
LPD3DXMESH			g_pMeshFurniture[FURNITURE_TYPE_MAX];			// ID3DXMeshインターフェイスへのポインタ
LPD3DXBUFFER		g_pD3DXMatBuffFurniture[FURNITURE_TYPE_MAX];	// メッシュのマテリアル情報を格納
DWORD				g_aNumMatFurniture[FURNITURE_TYPE_MAX];			// 属性情報の総数
D3DXMATRIX			g_mtxWorldFurniture;							// ワールドマトリックス
FURNITURE			furnitureWk[MAX_FURNITURE];						// 家具格納ワーク

const char *FileNameFurniture[FURNITURE_TYPE_MAX] =
{
	"data/MODEL/FURNITURE/kabin.x",		// 花瓶
	"data/MODEL/FURNITURE/isu.x",		// 椅子
	"data/MODEL/FURNITURE/pig.x",		// 豚の貯金箱
	"data/MODEL/FURNITURE/yubiwa.x",	// 指輪
	"data/MODEL/FURNITURE/toilet.x",	// トイレ
	"data/MODEL/FURNITURE/desk.x",		// 机
	"data/MODEL/FURNITURE/tv.x",		// テレビ
	"data/MODEL/FURNITURE/kinko.x",		// 金庫
	"data/MODEL/FURNITURE/tansu.x",		// タンス
	"data/MODEL/FURNITURE/bed.x"		// ベッド
};
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitFurniture(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	FURNITURE *furniture = &furnitureWk[0];

	if (type == STAGE_INIT_FAST)
	{
		for (int nCntFurnitureType = 0; nCntFurnitureType < FURNITURE_TYPE_MAX; nCntFurnitureType++)
		{
			g_pD3DTextureFurniture[nCntFurnitureType] = NULL;
			g_pMeshFurniture[nCntFurnitureType] = NULL;
			g_pD3DXMatBuffFurniture[nCntFurnitureType] = NULL;

			// Xファイルの読み込み
			if (FAILED(D3DXLoadMeshFromX(FileNameFurniture[nCntFurnitureType],
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&g_pD3DXMatBuffFurniture[nCntFurnitureType],
				NULL,
				&g_aNumMatFurniture[nCntFurnitureType],
				&g_pMeshFurniture[nCntFurnitureType])))
			{
				return E_FAIL;
			}

#if 0
			// テクスチャの読み込み
			D3DXCreateTextureFromFile(pDevice,									// デバイスへのポインタ
				TEXTURE_FILENAME,						// ファイルの名前
				&g_pD3DTextureModelFurniture[nCntFurnitureType]);	// 読み込むメモリー
#endif
		}
	}

	// 家具の初期化処理
	//for (int i = 0; i <MAX_FURNITURE; i++, furniture++)
	//{

	//}


	LoadCsv();			// CSVファイル読み込み
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitFurniture(void)
{
	for (int nCntFurnitureType = 0; nCntFurnitureType < FURNITURE_TYPE_MAX; nCntFurnitureType++)
	{
		if (g_pD3DTextureFurniture[nCntFurnitureType] != NULL)
		{// テクスチャの開放
			g_pD3DTextureFurniture[nCntFurnitureType]->Release();
			g_pD3DTextureFurniture[nCntFurnitureType] = NULL;
		}

		if (g_pMeshFurniture[nCntFurnitureType] != NULL)
		{// メッシュの開放
			g_pMeshFurniture[nCntFurnitureType]->Release();
			g_pMeshFurniture[nCntFurnitureType] = NULL;
		}

		if (g_pD3DXMatBuffFurniture[nCntFurnitureType] != NULL)
		{// マテリアルの開放
			g_pD3DXMatBuffFurniture[nCntFurnitureType]->Release();
			g_pD3DXMatBuffFurniture[nCntFurnitureType] = NULL;
		}
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateFurniture(void)
{
	FURNITURE *furniture = &furnitureWk[0];

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawFurniture(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTranslate, mtxScale;
	FURNITURE *furniture = &furnitureWk[0];

	for (int nCntFurniture = 0; nCntFurniture < MAX_FURNITURE; nCntFurniture++, furniture++)
	{	// 使用状態の家具のみ描画

		if (!furniture->use) continue;
		if (furniture->house_num == GetStage())// ステージ番号と同じ家番号の家具のみ描画
		{
			// ライトをon
			pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_mtxWorldFurniture);

			// スケールを反映
			D3DXMatrixScaling(&mtxScale, furniture->scl.x,
				furniture->scl.y,
				furniture->scl.z);
			D3DXMatrixMultiply(&g_mtxWorldFurniture,
				&g_mtxWorldFurniture, &mtxScale);

			// 回転を反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, furniture->rot.y, furniture->rot.x, furniture->rot.z);
			D3DXMatrixMultiply(&g_mtxWorldFurniture, &g_mtxWorldFurniture, &mtxRot);

			// 移動を反映
			D3DXMatrixTranslation(&mtxTranslate, furniture->pos.x, furniture->pos.y, furniture->pos.z);
			D3DXMatrixMultiply(&g_mtxWorldFurniture, &g_mtxWorldFurniture, &mtxTranslate);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldFurniture);

			D3DXMATERIAL *pD3DXMat = (D3DXMATERIAL*)g_pD3DXMatBuffFurniture[furniture->type]->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_aNumMatFurniture[furniture->type]; nCntMat++)
			{
				// マテリアルの設定
				pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);

				// テクスチャの設定
				pDevice->SetTexture(0, g_pD3DTextureFurniture[furniture->type]);

				// 描画
				g_pMeshFurniture[furniture->type]->DrawSubset(nCntMat);
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
// 家具の取得
//=============================================================================
FURNITURE *GetFurniture(int no)
{
	return &furnitureWk[no];
}

//=============================================================================
// 家具の当たり判定処理
//=============================================================================
void FurnitureColi()
{
	// 存在しているかとうか

	// 範囲内かとうか

	// ボタン入力

	// 所持数チェック

	// 所持重量チェック

	// カバンの空いている場所を探す

	// カバンに入れる

	// 所持重量処理

}

//=============================================================================
// 家具の重量の処理
//=============================================================================
void FurnitureWt()
{
	PLAYER *player = GetPlayer(0);
	FURNITURE *fnt = GetFurniture(0);

	player->weight = 0;

	for (int i = 0; i < HAVE_MAX; i++)
	{
		if (player->havenum[i] != -1) continue;
		
		int type_tem = player->havenum[i];

		player->weight += (fnt + type_tem)->weight;

		//for (int j = 0; j < FURNITURE_TYPE_MAX; j++)
		//{
		//	if (player->havenum[i] == (fnt + j)->type)
		//	{
		//		player->weight += (fnt + j)->weight;
		//	}

		//}

	}

}