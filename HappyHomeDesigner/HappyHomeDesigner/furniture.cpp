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
//#include "shadow.h"

//#include "stdlib.h"
//#include "shadow.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	VALUE_ROTATE_FURNITURE		(D3DX_PI * 0.025f)		// 回転速度
#define	FURNITURE_RADIUS				(10.0f)					// 半径

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9	g_pD3DTextureFurniture[FURNITURETYPE_MAX];	// テクスチャ読み込み場所
LPD3DXMESH			g_pMeshFurniture[FURNITURETYPE_MAX];			// ID3DXMeshインターフェイスへのポインタ
LPD3DXBUFFER		g_pD3DXMatBuffFurniture[FURNITURETYPE_MAX];	// メッシュのマテリアル情報を格納
DWORD				g_aNumMatFurniture[FURNITURETYPE_MAX];		// 属性情報の総数

D3DXMATRIX			g_mtxWorldFurniture;						// ワールドマトリックス

FURNITURE				furnitureWk[MAX_FURNITURE];					// アイテムワーク

int					poptime;							// ポップする間隔

const char *FileNameFurniture[FURNITURETYPE_MAX] =
{
	"data/MODEL/FURNITURE/furniture.x",			// コイン
	"data/MODEL/FURNITURE/furniture001.x",		// ライフ
	"data/MODEL/FURNITURE/furniture002.x"			// タイマー
};

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitFurniture(int nType)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	FURNITURE *furniture = &furnitureWk[0];
	int one = 0;

	if (nType == STAGE_INIT_FAST)
	{
		for (int nCntFurnitureType = 0; nCntFurnitureType < FURNITURETYPE_MAX; nCntFurnitureType++)
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

	for (int nCntFurniture = 0; nCntFurniture < MAX_FURNITURE; nCntFurniture++, furniture++)
	{
		furniture->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		furniture->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		furniture->scl = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		furniture->fRadius = 0.0f;
		furniture->nIdxShadow = -1;
		furniture->nType = FURNITURETYPE_COIN;
		furniture->life = 0;
		furniture->no = 0;
		furniture->use = false;

		// シャドウ用
		furniture->nIdxShadow = 0;
		furniture->fSizeShadow = 0.0f;
		furniture->colShadow = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.8f);
		furniture->bShadow = false;
	}

	poptime = 0;

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitFurniture(void)
{
	for (int nCntFurnitureType = 0; nCntFurnitureType < FURNITURETYPE_MAX; nCntFurnitureType++)
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
	//PANEL *panel = GetPanel(0);


	// アイテムを一定間隔でポップさせる
	if (poptime % FURNITURE_POP_FREQUENCY == 0)
	{
		SetFurniture(D3DXVECTOR3(0.0f, 10.0f, 0.0f), FURNITURETYPE_COIN, FURNITURE_LIFE);
		poptime = 0;
	}
	poptime++;

	for (int nCntFurniture = 0; nCntFurniture < MAX_FURNITURE; nCntFurniture++, furniture++)
	{
		if (furniture->use)
		{
			// アイテムを回転させる
			furniture->rot.y += VALUE_ROTATE_FURNITURE;
			if (furniture->rot.y > D3DX_PI)
			{
				furniture->rot.y -= D3DX_PI * 2.0f;
			}

			// スケールを少しづつ拡大
			furniture->scl.x += 0.05f;
			furniture->scl.y += 0.05f;
			furniture->scl.z += 0.05f;

			// アイテムが完全にポップしたら（スケールが最大まで拡大されたら）
			if (furniture->scl.x >= 1.0f)
			{
				// スケールをそれ以上大きくならないようにする
				furniture->scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

				// アイテムの寿命を減らす
				furniture->life--;

			}


			if (furniture->life <= 0)
			{	// アイテムを徐々に下方向に移動
				furniture->pos.y -= VALUE_MOVE_FURNITURE;
			}


			//if (furniture->life <= 0)
			//{	// 寿命が尽きたアイテムを消去
			//	furniture->use = false;
			//}

			// シャドウ
			//if (!furniture->bShadow)
			//{	// シャドウ設置
			//	furniture->nIdxShadow = CreateShadow(furniture->pos, 25.0f, 25.0f);
			//	furniture->fSizeShadow = FURNITURE_SHADOW_SIZE;
			//	furniture->colShadow = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.7f);
			//	furniture->bShadow = true;
			//}
			//else
			//{
			//	// シャドウ管理
			//	SetPositionShadow(furniture->nIdxShadow, D3DXVECTOR3(furniture->pos.x, 0.2f, furniture->pos.z));
			//	SetVertexShadow(furniture->nIdxShadow, furniture->fSizeShadow, furniture->fSizeShadow);
			//	SetColorShadow(furniture->nIdxShadow, furniture->colShadow);
			//}

			//if (furniture->pos.y < FURNITURE_SHADOW_REREASE && furniture->bShadow)
			//{
			//	// アイテムの影を削除
			//	ReleaseShadow(furniture->nIdxShadow);
			//	furniture->bShadow = false;
			//}
			// 完全にフィールドの下に行ったら消去
			if (furniture->pos.y < -FURNITURE_SIZE_Y)
			{
				// アイテムを消去
				furniture->use = false;
				// パネルをセット状態から解放してあげる
				//panel[furniture->no].FurnitureSet = false;

			}

			// 影の位置設定
			//SetPositionShadow(furniture->nIdxShadow, D3DXVECTOR3(furniture->pos.x, 0.1f, furniture->pos.z));

			float fSizeX = 20.0f + (furniture->pos.y - 10.0f) * 0.05f;
			if (fSizeX < 20.0f)
			{
				fSizeX = 20.0f;
			}
			float fSizeY = 20.0f + (furniture->pos.y - 10.0f) * 0.05f;
			if (fSizeY < 20.0f)
			{
				fSizeY = 20.0f;
			}

			//SetVertexShadow(furniture->nIdxShadow, fSizeX, fSizeY);

			float colA = (200.0f - (furniture->pos.y - 10.0f)) / 400.0f;
			if (colA < 0.0f)
			{
				colA = 0.0f;
			}
			//SetColorShadow(furniture->nIdxShadow, D3DXCOLOR(1.0f, 1.0f, 1.0f, colA));
		}
	}


#ifdef _DEBUG
	PrintDebugProc("[アイテムの生存数]  ：(%d)]\n", GetExistFurnitureNum());
	PrintDebugProc("\n");
#endif

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
	{
		if (furniture->use)
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

			D3DXMATERIAL *pD3DXMat = (D3DXMATERIAL*)g_pD3DXMatBuffFurniture[furniture->nType]->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_aNumMatFurniture[furniture->nType]; nCntMat++)
			{
				// マテリアルの設定
				pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);

				// テクスチャの設定
				pDevice->SetTexture(0, g_pD3DTextureFurniture[furniture->nType]);

				// 描画
				g_pMeshFurniture[furniture->nType]->DrawSubset(nCntMat);
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
// アイテムの設定
// 引数１：ポップさせる座標調整用
// 引数２：アイテムの種類
// 引数３：アイテムがポップしてから消えるまでの時間
//=============================================================================
void SetFurniture(D3DXVECTOR3 pos, int nType, int life)
{
	FURNITURE *furniture = &furnitureWk[0];
	//PANEL *panel = GetPanel(0);
	int no = 0;		// パネル番号格納

	for (int i = 0; i < NUM_POP; i++)
	{	// アイテムをポップさせる分だけループ

		furniture = &furnitureWk[0];

		//while (1)
		//{
		//	no = rand() % PANEL_MAX;

		//	panel = GetPanel(no);

		//	// 選ばれたパネルが使用中かどうかのチェック
		//	if (!panel->FurnitureSet)
		//	{	// 未使用ならば

		//		// アイテムセット状態にする
		//		panel->FurnitureSet = true;


		//		break;
		//	}

		//}

		for (int nCntFurniture = 0; nCntFurniture < MAX_FURNITURE; nCntFurniture++, furniture++)
		{
			if (!furniture->use)
			{
				// アイテムをセットしたパネルの番号を保存
				furniture->no = no;

				// アイテムのスケールをゼロにする
				furniture->scl = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

				// ポップ位置の設定
				//furniture->pos = panel->Pos;		// ランダムで選んだパネルの座標にセット
											// ポップ位置を微調整
				furniture->pos.x += pos.x;
				furniture->pos.y += pos.y;
				furniture->pos.z += pos.z;

				furniture->fRadius = FURNITURE_RADIUS;
				furniture->nType = nType;
				furniture->life = life;
				furniture->use = true;

				// 影の設定
				//furniture->nIdxShadow = SetShadow(furniture->pos, furniture->fRadius * 2.0f, furniture->fRadius * 2.0f);

				break;
			}
		}

		// アイテムの生存数がMAXになったら抜ける
		if (GetExistFurnitureNum() >= MAX_FURNITURE_POP) break;

	}
}
//=============================================================================
// アイテムの取得
//=============================================================================
FURNITURE *GetFurniture(int no)
{
	return &furnitureWk[no];
}
//=============================================================================
// アイテムの生存数取得
//=============================================================================
int GetExistFurnitureNum(void)
{
	FURNITURE *furniture = &furnitureWk[0];
	int Cnt = 0;

	for (int i = 0; i < MAX_FURNITURE; i++, furniture++)
	{
		if (furniture->use)
		{
			Cnt++;
		}
	}

	return Cnt;
}