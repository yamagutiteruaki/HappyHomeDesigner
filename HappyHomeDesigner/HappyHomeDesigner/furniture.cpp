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
#include "input.h"
#include "write_csv.h"
#include "camera.h"
#include "calculate.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
int FurnitureColi(void);
void FurnitureGetDAZE(int no);
void FurniturePut(void);
int BagCheck(int func);
bool WeightCheck(int no);

//void FurnitureWt(void);
void FurnitureMove(int no);
void FurnitureRotate(int no);
void FurnitureScaling(int no);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9	g_pD3DTextureFurniture[FURNITURE_TYPE_MAX];		// テクスチャ読み込み場所
LPD3DXMESH			g_pMeshFurniture[FURNITURE_TYPE_MAX];			// ID3DXMeshインターフェイスへのポインタ
LPD3DXBUFFER		g_pD3DXMatBuffFurniture[FURNITURE_TYPE_MAX];	// メッシュのマテリアル情報を格納
DWORD				g_aNumMatFurniture[FURNITURE_TYPE_MAX];			// 属性情報の総数
D3DXMATRIX			g_mtxWorldFurniture;							// ワールドマトリックス
FURNITURE			furnitureWk[MAX_FURNITURE];						// 家具格納ワーク

int					FurnitureNum;									// 操作する家具の番号指定用

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

	FurnitureNum = 0;

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

	FurnitureColi();
	//FurnitureGetDAZE();
	FurniturePut();

#ifdef _DEBUG
	// 動かす家具を決定
	if (GetKeyboardTrigger(DIK_L))
	{
		FurnitureNum++;
		if (FurnitureNum >= GetFurnitureCnt())
		{	// ポインタエラー防止
			FurnitureNum--;
		}
	}
	else if (GetKeyboardTrigger(DIK_K))
	{
		FurnitureNum--;
		if (FurnitureNum < 0)
		{	// ポインタエラー防止
			FurnitureNum = 0;
		}
	}
	// 指定した家具を移動
	FurnitureMove(FurnitureNum);
	// 指定した家具をY軸回転
	FurnitureRotate(FurnitureNum);
	// 指定したスケール拡大・縮小
	FurnitureScaling(FurnitureNum);

	// csvファイル新規作成
	if (GetKeyboardTrigger(DIK_M))
	{
		WriteCsv(CREATE);
	}
	// csvファイルに上書き
	if (GetKeyboardTrigger(DIK_Q))
	{
		WriteCsv(OVERWRITE);
	}

	// デバッグフォント表示
	PrintDebugProc("\n\n現在の家番号:       %d \n", GetStage());
	PrintDebugProc("編集中の家具の名前: %s \n\n", furnitureWk[FurnitureNum].name);
	PrintDebugProc("家具のpos:       [%f %f %f]\n",
		furnitureWk[FurnitureNum].pos.x,
		furnitureWk[FurnitureNum].pos.y,
		furnitureWk[FurnitureNum].pos.z);
	PrintDebugProc("家具のrot:       [%f %f %f]\n",
		furnitureWk[FurnitureNum].rot.x,
		furnitureWk[FurnitureNum].rot.y,
		furnitureWk[FurnitureNum].rot.z);
	PrintDebugProc("家具のscl:       [%f %f %f]\n",
		furnitureWk[FurnitureNum].scl.x,
		furnitureWk[FurnitureNum].scl.y,
		furnitureWk[FurnitureNum].scl.z);
	PrintDebugProc("家具のid:        [%d]\n", furnitureWk[FurnitureNum].id);
	PrintDebugProc("家具のuse:       [%d]\n", furnitureWk[FurnitureNum].use);
	PrintDebugProc("家具のtype:      [%d]\n", furnitureWk[FurnitureNum].type);
	PrintDebugProc("家具のhouse_num: [%d]\n", furnitureWk[FurnitureNum].house_num);
	PrintDebugProc("家具のweight:    [%f]\n", furnitureWk[FurnitureNum].weight);
	PrintDebugProc("家具のprice:     [%d]\n", furnitureWk[FurnitureNum].price);
	PrintDebugProc("家具のratio:     [%d]\n", furnitureWk[FurnitureNum].ratio);
	PrintDebugProc("\n家具の操作方法一覧\n");
	PrintDebugProc("家具を選択:               [KキーorLキー]\n");
	PrintDebugProc("家具の移動:               [前移動Tキー], [後移動Gキー], [左移動Fキー], [右移動Hキー]\n");
	PrintDebugProc("家具のY軸回転:            [RキーorEキー]\n");
	PrintDebugProc("家具のスケール拡大と縮小: [IキーorJキー]\n\n");
	PrintDebugProc("CSVファイルの上書き保存:  [Qキー]\n\n");
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
// 家具指定番号の取得
//=============================================================================
int GetFurnitureNum(void)
{
	return FurnitureNum;
}
//=============================================================================
// 家具の当たり判定処理
//=============================================================================
int FurnitureColi()
{
	PLAYER *ply = GetPlayer(0);
	FURNITURE *fnt = GetFurniture(0);
	int no = -1;
	float dist = 0.0;
	const float distCheck = 32.0f;

	for (int i = 0; i < MAX_FURNITURE; i++, fnt++)
	{
		// 存在しているのか
		if (fnt->use == FALSE) continue;
		if (fnt->house_num != GetStage()) continue;

		// 距離を計算
		dist = float(sqrt(pow((fnt->pos.x - ply->Eye.x), 2) + pow((fnt->pos.z - ply->Eye.z), 2)));
		#ifdef _DEBUG
		PrintDebugProc("NO.%d dist = %f\n", fnt->id, dist);
		#endif

		// 取れる範囲内かとうか
		if (dist <= distCheck)
		{
			// メッセージ表示
			#ifdef _DEBUG
			PrintDebugProc("取得可能 ");
			#endif

			// 番号を取得
			#ifdef _DEBUG
			PrintDebugProc("家具ID: %d\n", fnt->id);
			PrintDebugProc("家具金額: %g\n", fnt->price);

			#endif

			no = i;

			// ボタン入力
			if (GetKeyboardTrigger(DIK_E))
			{
				FurnitureGetDAZE(no);
				//fnt = GetFurniture(0);
				//(fnt + no)->use = FALSE;
				
			}

		}
		else
		{
			no = -1;
		}

	}

	return no;
}

//=============================================================================
// 家具
//=============================================================================
void FurnitureGetDAZE(int no)
{
	PLAYER *ply = GetPlayer(0);
	FURNITURE *fnt = GetFurniture(0);

	// 所持数チェック、カバンの中で空いている場所を探す
	int space = -1;
	space = BagCheck(0);

	if ((space >= 0 && space < HAVE_MAX) &&	// 所持数チェック、カバンの中で空いている場所を探す
		WeightCheck(no) == TRUE)			// 所持重量チェック
	{
		// カバンに入れる
		ply->havenum[space] = (fnt + no)->id;

		// 所持重量処理
		ply->weight += (fnt + no)->weight;

		// フィールド上のオブジェクトを削除
		(fnt + no)->use = FALSE;
	}

}

//=============================================================================
// 所持品チェック
// 引数：0 取る 1 手放す
//=============================================================================
int BagCheck(int func)
{
	PLAYER *ply = GetPlayer(0);
	int no = -1;

	switch (func)
	{
	case 0:
		// カバンの中で空いている場所を探す
		for (int i = 0; i < HAVE_MAX; i++)
		{
			if (ply->havenum[i] == -1)
			{
				no = i;
				break;
			}
		}
		break;

	case 1:
		// カバンの中で一番上のアイテムを探す
		for (int i = 0; i < HAVE_MAX; i++)
		{
			if (ply->havenum[i] != -1)
			{
				no = i;
			}
		}
		break;

	}
	
	return no;

}

//=============================================================================
// 所持重量チェック
//=============================================================================
bool WeightCheck(int no)
{
	PLAYER *ply = GetPlayer(0);
	FURNITURE *fnt = GetFurniture(0);
	if (ply->weight + (fnt + no)->weight <= WT_MAX)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}

}

//=============================================================================
// 家具を置く
//=============================================================================
void FurniturePut()
{
	PLAYER *ply = GetPlayer(0);
	FURNITURE *fnt = GetFurniture(0);
	int no = -1;
	int id = -1;

	// ボタン入力
	if (GetKeyboardTrigger(DIK_B))
	{
		// 置ける場所チェック（いらない）

		// カバンの中身を取得
		no = BagCheck(1);

		// 所持品チェック
		if (no != -1)
		{
			// カバンの中身を取得
			id = ply->havenum[no];

			// プレイヤー位置を取得、プット
			(fnt + id)->pos = ply->Eye;
			(fnt + id)->house_num = GetStage();
			(fnt + id)->use = TRUE;

			//被害金額加算
			if (GetStage() == STAGE_MYHOUSE)
			{
				AddPrice((fnt + id)->price);
			}
			// 所持品処理
			ply->havenum[no] = -1;

			// 所持重量処理
			ply->weight -= (fnt + id)->weight;

		}

	}

}

//=============================================================================
// 家具の移動
//=============================================================================
void FurnitureMove(int no)
{
	FURNITURE *furniture = &furnitureWk[no];
	CAMERA *camera = GetCamera();

	float fDiffRotY;

	if (furniture == NULL)
	{
		furniture = &furnitureWk[0];
	}

	if (GetKeyboardPress(DIK_F))
	{
		if (GetKeyboardPress(DIK_T))
		{// 左前移動
			furniture->move.x -= cosf(camera->rotCamera.y + D3DX_PI * 0.25f) * VALUE_MOVE_FURNITURE;
			furniture->move.z += sinf(camera->rotCamera.y + D3DX_PI * 0.25f) * VALUE_MOVE_FURNITURE;

			furniture->rotDest.y = camera->rotCamera.y + D3DX_PI * 0.75f;
		}
		else if (GetKeyboardPress(DIK_G))
		{// 左後移動
			furniture->move.x -= cosf(camera->rotCamera.y - D3DX_PI * 0.25f) * VALUE_MOVE_FURNITURE;
			furniture->move.z += sinf(camera->rotCamera.y - D3DX_PI * 0.25f) * VALUE_MOVE_FURNITURE;

			furniture->rotDest.y = camera->rotCamera.y + D3DX_PI * 0.25f;
		}
		else
		{// 左移動
			furniture->move.x -= cosf(camera->rotCamera.y) * VALUE_MOVE_FURNITURE;
			furniture->move.z += sinf(camera->rotCamera.y) * VALUE_MOVE_FURNITURE;

			furniture->rotDest.y = camera->rotCamera.y + D3DX_PI * 0.50f;

		}
	}
	else if (GetKeyboardPress(DIK_H))
	{
		if (GetKeyboardPress(DIK_T))
		{// 右前移動
			furniture->move.x += cosf(camera->rotCamera.y - D3DX_PI * 0.25f) * VALUE_MOVE_FURNITURE;
			furniture->move.z -= sinf(camera->rotCamera.y - D3DX_PI * 0.25f) * VALUE_MOVE_FURNITURE;

			furniture->rotDest.y = camera->rotCamera.y - D3DX_PI * 0.75f;
		}
		else if (GetKeyboardPress(DIK_G))
		{// 右後移動
			furniture->move.x += cosf(camera->rotCamera.y + D3DX_PI * 0.25f) * VALUE_MOVE_FURNITURE;
			furniture->move.z -= sinf(camera->rotCamera.y + D3DX_PI * 0.25f) * VALUE_MOVE_FURNITURE;

			furniture->rotDest.y = camera->rotCamera.y - D3DX_PI * 0.25f;
		}
		else
		{// 右移動
			furniture->move.x += cosf(camera->rotCamera.y) * VALUE_MOVE_FURNITURE;
			furniture->move.z -= sinf(camera->rotCamera.y) * VALUE_MOVE_FURNITURE;

			furniture->rotDest.y = camera->rotCamera.y - D3DX_PI * 0.50f;
		}
	}
	else if (GetKeyboardPress(DIK_T))
	{// 前移動
		furniture->move.x += sinf(camera->rotCamera.y) * VALUE_MOVE_FURNITURE;
		furniture->move.z += cosf(camera->rotCamera.y) * VALUE_MOVE_FURNITURE;

		furniture->rotDest.y = D3DX_PI + camera->rotCamera.y;
	}
	else if (GetKeyboardPress(DIK_G))
	{// 後移動
		furniture->move.x -= sinf(camera->rotCamera.y) * VALUE_MOVE_FURNITURE;
		furniture->move.z -= cosf(camera->rotCamera.y) * VALUE_MOVE_FURNITURE;

		furniture->rotDest.y = camera->rotCamera.y;
	}

	// 移動量に慣性をかける
	furniture->move.x += (0.0f - furniture->move.x) * RATE_MOVE_FURNITURE;
	furniture->move.y += (0.0f - furniture->move.y) * RATE_MOVE_FURNITURE;
	furniture->move.z += (0.0f - furniture->move.z) * RATE_MOVE_FURNITURE;

	// 位置移動
	furniture->pos.x += furniture->move.x;
	furniture->pos.y += furniture->move.y;
	furniture->pos.z += furniture->move.z;

	// 目的の角度までの差分
	fDiffRotY = furniture->rotDest.y - furniture->rot.y;
	if (fDiffRotY > D3DX_PI)
	{
		fDiffRotY -= D3DX_PI * 2.0f;
	}
	if (fDiffRotY < -D3DX_PI)
	{
		fDiffRotY += D3DX_PI * 2.0f;
	}

	// 目的の角度まで慣性をかける
	furniture->rot.y += fDiffRotY * RATE_ROTATE_FURNITURE;
	if (furniture->rot.y > D3DX_PI)
	{
		furniture->rot.y -= D3DX_PI * 2.0f;
	}
	if (furniture->rot.y < -D3DX_PI)
	{
		furniture->rot.y += D3DX_PI * 2.0f;
	}

	// 角度を修正
	furniture->rot.y = PiCalculate360(furniture->rot.y);

}
//=============================================================================
// 家具のY軸回転
//=============================================================================
void FurnitureRotate(int no)
{
	FURNITURE *furniture = &furnitureWk[no];
	CAMERA *camera = GetCamera();

	float fDiffRotY;

	if (furniture == NULL)
	{
		furniture = &furnitureWk[0];
	}

	if (GetKeyboardPress(DIK_E))
	{// 左回転
		furniture->rotDest.y -= VALUE_ROTATE_FURNITURE;
		if (furniture->rotDest.y < -D3DX_PI)
		{
			furniture->rotDest.y += D3DX_PI * 2.0f;
		}
	}
	if (GetKeyboardPress(DIK_R))
	{// 右回転
		furniture->rotDest.y += VALUE_ROTATE_FURNITURE;
		if (furniture->rotDest.y > D3DX_PI)
		{
			furniture->rotDest.y -= D3DX_PI * 2.0f;
		}
	}

	// 目的の角度までの差分
	fDiffRotY = furniture->rotDest.y - furniture->rot.y;
	if (fDiffRotY > D3DX_PI)
	{
		fDiffRotY -= D3DX_PI * 2.0f;
	}
	if (fDiffRotY < -D3DX_PI)
	{
		fDiffRotY += D3DX_PI * 2.0f;
	}

	// 目的の角度まで慣性をかける
	furniture->rot.y += fDiffRotY * RATE_ROTATE_FURNITURE;
	if (furniture->rot.y > D3DX_PI)
	{
		furniture->rot.y -= D3DX_PI * 2.0f;
	}
	if (furniture->rot.y < -D3DX_PI)
	{
		furniture->rot.y += D3DX_PI * 2.0f;
	}

	// 角度を修正
	furniture->rot.y = PiCalculate360(furniture->rot.y);

}
//=============================================================================
// 家具のスケール拡大・縮小
//=============================================================================
void FurnitureScaling(int no)
{
	FURNITURE *furniture = &furnitureWk[no];

	if (furniture == NULL)
	{
		furniture = &furnitureWk[0];
	}

	if (GetKeyboardPress(DIK_I))
	{// 拡大
		furniture->scl.x += VALUE_SCALE_FURNITURE;
		furniture->scl.y += VALUE_SCALE_FURNITURE;
		furniture->scl.z += VALUE_SCALE_FURNITURE;
	}
	if (GetKeyboardPress(DIK_J))
	{// 縮小
		furniture->scl.x -= VALUE_SCALE_FURNITURE;
		furniture->scl.y -= VALUE_SCALE_FURNITURE;
		furniture->scl.z -= VALUE_SCALE_FURNITURE;
	}
}
