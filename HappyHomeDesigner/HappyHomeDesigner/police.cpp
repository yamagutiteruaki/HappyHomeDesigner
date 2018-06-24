//=============================================================================
//
// ポリス処理 [police.cpp]
// Author : GP12A295-19-千坂浩太
//
//=============================================================================
#include "camera.h"
#include "debugproc.h"
#include "input.h"
#include "player.h"
#include "police.h"
#include "stage.h"
#include "field.h"
#include "collision.h"
#include "calculate.h"
#include "shadow.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InvalidCollision(int frame);
void PoliceCollision(void);
void SetPoliceMove(POLICE *police, int y, int x);
void PoliceMove(void);
void PoliceEachCollision(void);
void PoliceMoveControl(int frame);
//*****************************************************************************
// グローバル変数
//*****************************************************************************
// ポリス本体関係
LPDIRECT3DTEXTURE9	g_pD3DTexturePolice;									// テクスチャ読み込み場所
LPD3DXMESH			g_pD3DXMeshPolice;										// ID3DXMeshインターフェイスへのポインタ
LPD3DXBUFFER		g_pD3DXBuffMatPolice;									// メッシュのマテリアル情報を格納
DWORD				g_nNumMatPolice;										// 属性情報の総数
D3DXMATRIX			g_mtxWorldPolice;										// ワールドマトリックス
POLICE				policeWk[POLICE_MAX];									// ポリス格納ワーク
// ポリスアーム関係
LPDIRECT3DTEXTURE9	g_pD3DTexturePoliceArm[POLICE_ARM_TYPE_MAX];			// テクスチャ読み込み場所
LPD3DXMESH			g_pD3DXMeshPoliceArm[POLICE_ARM_TYPE_MAX];				// ID3DXMeshインターフェイスへのポインタ
LPD3DXBUFFER		g_pD3DXBuffMatPoliceArm[POLICE_ARM_TYPE_MAX];			// メッシュのマテリアル情報を格納
DWORD				g_nNumMatPoliceArm[POLICE_ARM_TYPE_MAX];				// 属性情報の総数
D3DXMATRIX			g_mtxWorldPoliceArm;									// ワールドマトリックス
POLICE_ARM			policeArmWk[POLICE_ARM_MAX];							// ポリスアーム格納ワーク
const char *FileNamePoliceArm[POLICE_ARM_TYPE_MAX] =
{	// 読み込むモデル
	"data/MODEL/POLICE/standing_R_hand.x",		// 右腕
	"data/MODEL/POLICE/standing_L_hand.x",		// 左腕
};
// ポリスのレッグ関係
LPDIRECT3DTEXTURE9	g_pD3DTexturePoliceLeg[POLICE_LEG_TYPE_MAX];			// テクスチャ読み込み場所
LPD3DXMESH			g_pD3DXMeshPoliceLeg[POLICE_LEG_TYPE_MAX];				// ID3DXMeshインターフェイスへのポインタ
LPD3DXBUFFER		g_pD3DXBuffMatPoliceLeg[POLICE_LEG_TYPE_MAX];			// メッシュのマテリアル情報を格納
DWORD				g_nNumMatPoliceLeg[POLICE_LEG_TYPE_MAX];				// 属性情報の総数
D3DXMATRIX			g_mtxWorldPoliceLeg;									// ワールドマトリックス
POLICE_LEG			policeLegWk[POLICE_LEG_MAX];							// ポリスレッグ格納ワーク
const char *FileNamePoliceLeg[POLICE_LEG_TYPE_MAX] =
{
	"data/MODEL/POLICE/standing_R_leg.x",		// 右足
	"data/MODEL/POLICE/standing_L_leg.x",		// 左足
};
// チェックポイント関係
D3DXVECTOR3			CheckPointWk[CHECK_POINT_Y_MAX][CHECK_POINT_X_MAX];		// チェックポイント格納ワーク
// その他
int					animCnt;												// アニメカウント
int					sp_Update;												// 更新頻度計算用
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitPolice(int nType)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	POLICE *police = &policeWk[0];
	POLICE_ARM *policeArm = &policeArmWk[0];
	POLICE_LEG *policeLeg = &policeLegWk[0];
	FIELD *field = GetField(0);

	// ポリス本体のモデル読み込み
	if (nType == STAGE_INIT_FAST)
	{
		g_pD3DTexturePolice = NULL;
		g_pD3DXMeshPolice = NULL;
		g_pD3DXBuffMatPolice = NULL;

		// Xファイルの読み込み
		if (FAILED(D3DXLoadMeshFromX(POLICE_MODEL,
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_pD3DXBuffMatPolice,
			NULL,
			&g_nNumMatPolice,
			&g_pD3DXMeshPolice)))
		{
			return E_FAIL;
		}
#if 0
		// テクスチャの読み込み
		//D3DXCreateTextureFromFile(pDevice,					// デバイスへのポインタ
		//	TEXTURE_FILENAME,		// ファイルの名前
		//	&g_pD3DTextureModel);	// 読み込むメモリー
#endif
		// アームのモデル読み込み
		for (int i = 0; i < POLICE_ARM_TYPE_MAX; i++)
		{
			g_pD3DTexturePoliceArm[i] = NULL;
			g_pD3DXMeshPoliceArm[i] = NULL;
			g_pD3DXBuffMatPoliceArm[i] = NULL;

			// Xファイルの読み込み
			if (FAILED(D3DXLoadMeshFromX(FileNamePoliceArm[i],
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&g_pD3DXBuffMatPoliceArm[i],
				NULL,
				&g_nNumMatPoliceArm[i],
				&g_pD3DXMeshPoliceArm[i])))
			{
				return E_FAIL;
			}
#if 0
			// テクスチャの読み込み
			//D3DXCreateTextureFromFile(pDevice,					// デバイスへのポインタ
			//	TEXTURE_FILENAME,		// ファイルの名前
			//	&g_pD3DTextureModel);	// 読み込むメモリー
#endif
		}
		// レッグのモデル読み込み
		for (int i = 0; i < POLICE_LEG_TYPE_MAX; i++)
		{
			g_pD3DTexturePoliceLeg[i] = NULL;
			g_pD3DXMeshPoliceLeg[i] = NULL;
			g_pD3DXBuffMatPoliceLeg[i] = NULL;

			// Xファイルの読み込み
			if (FAILED(D3DXLoadMeshFromX(FileNamePoliceLeg[i],
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&g_pD3DXBuffMatPoliceLeg[i],
				NULL,
				&g_nNumMatPoliceLeg[i],
				&g_pD3DXMeshPoliceLeg[i])))
			{
				return E_FAIL;
			}
#if 0
			// テクスチャの読み込み
			//D3DXCreateTextureFromFile(pDevice,					// デバイスへのポインタ
			//	TEXTURE_FILENAME,		// ファイルの名前
			//	&g_pD3DTextureModel);	// 読み込むメモリー
#endif
		}
	}

	// チェックポイントの初期設定
	CheckPointWk[0][0] = D3DXVECTOR3(-CHECK_POINT_X, 0.0f, CHECK_POINT_Z);		// 左上
	CheckPointWk[1][0] = D3DXVECTOR3(0.0f, 0.0f, CHECK_POINT_Z);				// 中心上
	CheckPointWk[2][0] = D3DXVECTOR3(CHECK_POINT_X, 0.0f, CHECK_POINT_Z);		// 右上
	CheckPointWk[0][1] = D3DXVECTOR3(-CHECK_POINT_X, 0.0f, 0.0f);				// 中心左
	CheckPointWk[1][1] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);							// 中心
	CheckPointWk[2][1] = D3DXVECTOR3(CHECK_POINT_X, 0.0f, 0.0f);				// 中心右
	CheckPointWk[0][2] = D3DXVECTOR3(-CHECK_POINT_X, 0.0f, -CHECK_POINT_Z);		// 左下
	CheckPointWk[1][2] = D3DXVECTOR3(-0.0f, 0.0f, -CHECK_POINT_Z);				// 中心下
	CheckPointWk[2][2] = D3DXVECTOR3(CHECK_POINT_X, 0.0f, -CHECK_POINT_Z);		// 右下

	// ポリス本体の初期化処理
	for (int i = 0; i < POLICE_MAX; i++, police++)
	{
		// ポリスの視点(位置座標)の初期化
		//police->Eye = D3DXVECTOR3(-CHECK_POINT_X / 2, 0.0f, CHECK_POINT_Z / 2);
		police->Eye = CheckPointWk[i][i];
		// ポリスの注視点の初期化
		police->At = D3DXVECTOR3(0.0f, 0.0f, 50.0f);
		// ポリスの上方向の初期化
		police->Up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		// ポリスの向きの初期化
		police->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		// ポリスの移動量の初期化
		police->move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		// 回転の中心点の初期設定(原点ではなく少しずらす）
		police->rotBasis = D3DXVECTOR3(0.0f, 30.0f, 0.0f);
		// ポリスのスケールの初期化
		police->scl = D3DXVECTOR3(POLICE_SCALE_X, POLICE_SCALE_Y, POLICE_SCALE_Z);
		// ポリスの回転軸の初期化
		police->axisXZ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		police->axisY = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		// ポリスの回転角度の初期化
		police->fangleXZ = 0.0f;
		police->fangleY = 0.0f;
		// useフラグをtrueに設定
		police->use = true;
		// 当たり判定有効フラグをtrueに設定
		police->able_hit = true;
		// ポリスのフレームカウント初期化
		police->key = 0;
		// 親子関係識別番号の初期設定(番号は1から)
		police->num = i + 1;
		// 回転切り替えフラグをNULLに
		police->rotf = NULL;
		// 本体のタイプをNULLに
		police->type = NULL;
		// 移動フラグの初期化
		police->movef = true;
		// 移動切り替え用カウンタの初期化
		police->key2 = 0;
	}
	// アームの初期化処理
	police = &policeWk[0];
	for (int i = 0; i < POLICE_ARM_MAX; i++, policeArm++)
	{
		// アームの視点(位置座標)の初期化
		//policeArm->Eye = D3DXVECTOR3(-CHECK_POINT_X / 2, 0.0f, CHECK_POINT_Z / 2);
		policeArm->Eye = D3DXVECTOR3(0.0f, 0.0f, 100.0f);
		// アームの注視点の初期化
		policeArm->At = D3DXVECTOR3(0.0f, 0.0f, 50.0f);
		// アームの上方向の初期化
		policeArm->Up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		// アームの向きの初期化
		policeArm->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		// アームの移動量の初期化
		policeArm->move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		// 回転の中心点の初期設定(原点ではなく少しずらす）
		policeArm->rotBasis = D3DXVECTOR3(POLICE_ARM_ROTBASIS_X * POLICE_SCALE_X, POLICE_ARM_ROTBASIS_Y * POLICE_SCALE_Y, POLICE_ARM_ROTBASIS_Z * POLICE_SCALE_Z);
		// アームのスケールの初期化
		//policeArm->scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		policeArm->scl = police->scl;
		// アームの回転軸の初期化
		policeArm->axisXZ = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		policeArm->axisY = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		// アームの回転角度の初期化
		policeArm->fangleXZ = 0.0f;
		policeArm->fangleY = 0.0f;
		// useフラグをtrueに設定
		policeArm->use = false;
		// アームのフレームカウント初期化
		policeArm->key = 0;
		// アームのタイプの初期化(右腕が0・左腕が1)
		if (i < POLICE_MAX)
		{	// 右腕をポリスの人数分用意
			policeArm->type = 0;
		}
		if (i >= POLICE_MAX)
		{	// 左腕をポリスの人数分用意
			policeArm->type = 1;
		}
		// 回転切り替えフラグをtrueに設定
		policeArm->rotf = true;
		// 親子関係識別番号の初期設定(未使用:0番,使用：本体と同じ番号)
		policeArm->num = 0;
	}
	// レッグの初期化処理
	police = &policeWk[0];
	for (int i = 0; i < POLICE_LEG_MAX; i++, policeLeg++)
	{
		// レッグの視点(位置座標)の初期化
		//policeLeg->Eye = D3DXVECTOR3(-CHECK_POINT_X / 2, 0.0f, CHECK_POINT_Z / 2);
		policeLeg->Eye = D3DXVECTOR3(0.0f, 0.0f, 100.0f);
		// レッグの注視点の初期化
		policeLeg->At = D3DXVECTOR3(0.0f, 0.0f, 50.0f);
		// レッグの上方向の初期化
		policeLeg->Up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		// レッグの向きの初期化
		policeLeg->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		// レッグの移動量の初期化
		policeLeg->move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		// 回転の中心点の初期設定(原点ではなく少しずらす）
		policeLeg->rotBasis = D3DXVECTOR3(POLICE_LEG_ROTBASIS_X * POLICE_SCALE_X, POLICE_LEG_ROTBASIS_Y * POLICE_SCALE_Y, POLICE_LEG_ROTBASIS_Z * POLICE_SCALE_Z);
		// レッグのスケールの初期化
		policeLeg->scl = police->scl;
		// レッグの回転軸の初期化
		policeLeg->axisXZ = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		policeLeg->axisY = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		// レッグの回転角度の初期化
		policeLeg->fangleXZ = 0.0f;
		policeLeg->fangleY = 0.0f;
		// useフラグをtrueに設定
		policeLeg->use = false;
		// レッグのフレームカウント初期化
		policeLeg->key = 0;
		// レッグのタイプの初期化(右足が0・左足が1)
		if (i < POLICE_MAX)
		{	// 右足をポリスの人数分用意
			policeLeg->type = 0;
		}
		if (i >= POLICE_MAX)
		{	// 左足をポリスの人数分用意
			policeLeg->type = 1;
		}
		// 回転切り替えフラグをfalseに設定
		policeLeg->rotf = false;
		// 親子関係識別番号の初期設定(未使用:0番,使用：本体と同じ番号)
		policeLeg->num = 0;
	}

	// 親子関係設定処理
	SetParts();

	return S_OK;
}
//=============================================================================
// 終了処理
//=============================================================================
void UninitPolice(void)
{
	// 本体
	if (g_pD3DTexturePolice != NULL)
	{// テクスチャの開放
		g_pD3DTexturePolice->Release();
		g_pD3DTexturePolice = NULL;
	}
	if (g_pD3DXMeshPolice != NULL)
	{// メッシュの開放
		g_pD3DXMeshPolice->Release();
		g_pD3DXMeshPolice = NULL;
	}
	if (g_pD3DXBuffMatPolice != NULL)
	{// マテリアルの開放
		g_pD3DXBuffMatPolice->Release();
		g_pD3DXBuffMatPolice = NULL;
	}
	// アーム
	for (int i = 0; i < POLICE_ARM_TYPE_MAX; i++)
	{
		if (g_pD3DTexturePoliceArm[i] != NULL)
		{// テクスチャの開放
			g_pD3DTexturePoliceArm[i]->Release();
			g_pD3DTexturePoliceArm[i] = NULL;
		}
		if (g_pD3DXMeshPoliceArm[i] != NULL)
		{// メッシュの開放
			g_pD3DXMeshPoliceArm[i]->Release();
			g_pD3DXMeshPoliceArm[i] = NULL;
		}
		if (g_pD3DXBuffMatPoliceArm[i] != NULL)
		{// マテリアルの開放
			g_pD3DXBuffMatPoliceArm[i]->Release();
			g_pD3DXBuffMatPoliceArm[i] = NULL;
		}
	}
	// レッグ
	for (int i = 0; i < POLICE_LEG_TYPE_MAX; i++)
	{
		if (g_pD3DTexturePoliceLeg[i] != NULL)
		{// テクスチャの開放
			g_pD3DTexturePoliceLeg[i]->Release();
			g_pD3DTexturePoliceLeg[i] = NULL;
		}
		if (g_pD3DXMeshPoliceLeg[i] != NULL)
		{// メッシュの開放
			g_pD3DXMeshPoliceLeg[i]->Release();
			g_pD3DXMeshPoliceLeg[i] = NULL;
		}
		if (g_pD3DXBuffMatPoliceLeg[i] != NULL)
		{// マテリアルの開放
			g_pD3DXBuffMatPoliceLeg[i]->Release();
			g_pD3DXBuffMatPoliceLeg[i] = NULL;
		}
	}
}
//=============================================================================
// 更新処理
//=============================================================================
void UpdatePolice(void)
{
	POLICE *police = &policeWk[0];
	POLICE_ARM *policeArm = &policeArmWk[0];
	POLICE_LEG *policeLeg = &policeLegWk[0];

	// 移動無効切り替え処理
	PoliceMoveControl(3 * 60);
	// 当たり判定の一定時間無効処理
	InvalidCollision(POLICE_COLLISION_FRAME);
	// ポリスの当たり判定処理
	PoliceCollision();
	// ポリス同士の当たり判定処理
	PoliceEachCollision();
	// ポリス移動処理
	PoliceMove();
	// アニメーション処理
	Animation();

#ifdef _DEBUG
	police = &policeWk[0];
	PrintDebugProc("[ポリスの位置  ：(%f : %f : %f)]\n", police->Eye.x, police->Eye.y, police->Eye.z);
	PrintDebugProc("[ポリスの注視点  ：(%f : %f : %f)]\n", police->At.x, police->At.y, police->At.z);
	PrintDebugProc("[ポリスの移動ベクトル  ：(%f : %f : %f)]\n", police->move.x, police->move.y, police->move.z);
	//PrintDebugProc("[ポリスの向き  ：(%f)]\n", police->rot);
	PrintDebugProc("[ポリスの使用状態  ：(%d)]\n", police->use);
	//PrintDebugProc("[右腕の回転角度  ：(%f)]\n", policeArm->fangleXZ);
	PrintDebugProc("[ポリスの当たり判定有効状態  ：(%d)]\n", police->able_hit);
#endif

	police = &policeWk[0];

	for (int i = 0; i < POLICE_MAX; i++, police++)
	{
		if (GetStage() == STAGE_GAME)
		{
			// シャドウ
			if (!police->bShadow)
			{	// シャドウ設置
				police->nIdxShadow = CreateShadow(police->Eye, 25.0f, 25.0f);
				police->fSizeShadow = PLAYER_SHADOW_SIZE;
				police->colShadow = D3DXCOLOR(0.7f, 0.7f, 0.7f, 0.7f);
				police->bShadow = true;
			}
			else
			{
				// シャドウ管理
				SetPositionShadow(police->nIdxShadow, D3DXVECTOR3(police->Eye.x, 0.2f, police->Eye.z));
				SetVertexShadow(police->nIdxShadow, police->fSizeShadow, police->fSizeShadow);
				SetColorShadow(police->nIdxShadow, police->colShadow);
			}
		}
		
	}

}
//=============================================================================
// 描画処理
//=============================================================================
void DrawPolice(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATERIAL *pD3DXMat;
	D3DMATERIAL9 matDef;
	POLICE *police = &policeWk[0];
	POLICE_ARM *policeArm = &policeArmWk[0];
	POLICE_LEG *policeLeg = &policeLegWk[0];

	// ポリス本体の描画処理
	for (int i = 0; i < POLICE_MAX; i++, police++)
	{
		if (police->use == true)
		{	// 使用状態なら描画する
			// ライトをon
			pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_mtxWorldPolice);
			// ワールドマトリックス作成
			D3DXMatrixTransformation(&g_mtxWorldPolice, NULL, NULL, &police->scl, &police->rotBasis, &police->qAnswer, &police->Eye);
			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldPolice);
			// 現在のマテリアルを取得
			pDevice->GetMaterial(&matDef);
			// マテリアル情報に対するポインタを取得
			pD3DXMat = (D3DXMATERIAL*)g_pD3DXBuffMatPolice->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_nNumMatPolice; nCntMat++)
			{
				// マテリアルの設定
				pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);
				// テクスチャの設定
				pDevice->SetTexture(0, g_pD3DTexturePolice);
				// 描画
				g_pD3DXMeshPolice->DrawSubset(nCntMat);
			}
			// ライトをoff
			pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
		}
	}
	// ポリスのアームの描画
	for (int i = 0; i < POLICE_ARM_MAX; i++, policeArm++)
	{
		if (policeArm->use == true)
		{	// 使用状態なら描画する
			// ライトをon
			pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_mtxWorldPoliceArm);
			// ワールドマトリックス作成
			D3DXMatrixTransformation(&g_mtxWorldPoliceArm, NULL, NULL, &policeArm->scl, &policeArm->rotBasis, &policeArm->qAnswer, &policeArm->Eye);
			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldPoliceArm);
			// 現在のマテリアルを取得
			pDevice->GetMaterial(&matDef);
			// マテリアル情報に対するポインタを取得
			pD3DXMat = (D3DXMATERIAL*)g_pD3DXBuffMatPoliceArm[policeArm->type]->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_nNumMatPoliceArm[policeArm->type]; nCntMat++)
			{
				// マテリアルの設定
				pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);
				// テクスチャの設定
				pDevice->SetTexture(0, g_pD3DTexturePoliceArm[policeArm->type]);
				// 描画
				g_pD3DXMeshPoliceArm[policeArm->type]->DrawSubset(nCntMat);

			}
			// ライトをoff
			pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
		}
	}
	// ポリスのレッグの描画
	for (int i = 0; i < POLICE_LEG_MAX; i++, policeLeg++)
	{
		if (policeLeg->use == true)
		{	// 使用状態なら描画する
			// ライトをon
			pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_mtxWorldPoliceLeg);
			// ワールドマトリックス作成
			D3DXMatrixTransformation(&g_mtxWorldPoliceLeg, NULL, NULL, &policeLeg->scl, &policeLeg->rotBasis, &policeLeg->qAnswer, &policeLeg->Eye);
			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldPoliceLeg);
			// 現在のマテリアルを取得
			pDevice->GetMaterial(&matDef);
			// マテリアル情報に対するポインタを取得
			pD3DXMat = (D3DXMATERIAL*)g_pD3DXBuffMatPoliceLeg[policeLeg->type]->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_nNumMatPoliceLeg[policeLeg->type]; nCntMat++)
			{
				// マテリアルの設定
				pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);
				// テクスチャの設定
				pDevice->SetTexture(0, g_pD3DTexturePoliceLeg[policeLeg->type]);
				// 描画
				g_pD3DXMeshPoliceLeg[policeLeg->type]->DrawSubset(nCntMat);
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
// ポリス取得関数
//=============================================================================
POLICE *GetPolice(int no)
{
	return(&policeWk[no]);
}
//=============================================================================
// 当たり判定無効処理関数(引数：当たり判定無効が解除されるまでのフレーム数)
//=============================================================================
void InvalidCollision(int frame)
{
	POLICE *police = &policeWk[0];

	for (int i = 0; i < POLICE_MAX; i++, police++)
	{
		if (!police->able_hit) police->key++;
		// 当たり判定無効時間の解除
		if (police->key % frame == 0)
		{
			police->key = 0;
			police->able_hit = true;
		}
	}
}
//=============================================================================
// 当たり判定処理関数
//=============================================================================
void PoliceCollision(void)
{
	POLICE *police = &policeWk[0];

	for (int k = 0; k < POLICE_MAX; k++, police++)
	{	// 当たり判定が有効なポリスのみチェック
		if (!police->able_hit) continue;
		for (int j = 0; j < CHECK_POINT_Y_MAX; j++)
		{	// 配列Y要素についてチェック
			for (int i = 0; i < CHECK_POINT_X_MAX; i++)
			{	// 配列X要素についてチェック
				if (CollisionBC(police->Eye, CheckPointWk[j][i], POLICE_RADIUS, CHECK_POINT_RADIUS))
				{	// チェックポイントに侵入したらポリスの移動設定
					SetPoliceMove(police, j, i);
					// 当たり判定有効フラグをfalseに
					police->able_hit = false;
					break;
				}
			}
		}
	}
}
//=============================================================================
// パーツ親子関係設定関数
//=============================================================================
void SetParts(void)
{
	POLICE *police = &policeWk[0];
	POLICE_ARM *policeArm = &policeArmWk[0];
	POLICE_LEG *policeLeg = &policeLegWk[0];

	// 本体に腕パーツを関連付ける
	police = &policeWk[0];
	for (int i = 0; i < POLICE_MAX; i++, police++)
	{
		// 使用状態のポリスにのみパーツをセット
		if (!police->use) continue;
		// 未使用の右腕パーツをセット
		policeArm = &policeArmWk[0];
		for (int j = 0; j < POLICE_ARM_MAX; j++, policeArm++)
		{	// 未使用かつ右腕であることのチェック
			if ((policeArm->use) || (policeArm->type == 1)) continue;
			// 本体と同じ番号をセット
			policeArm->num = police->num;
			// 使用状態にする
			policeArm->use = true;
			break;
		}
		// 未使用の左腕パーツをセット
		policeArm = &policeArmWk[0];
		for (int j = 0; j < POLICE_ARM_MAX; j++, policeArm++)
		{	// 未使用かつ左腕であることのチェック
			if ((policeArm->use) || (policeArm->type == 0)) continue;
			// 本体と同じ番号をセット
			policeArm->num = police->num;
			// 使用状態にする
			policeArm->use = true;
			break;
		}
	}
	// 本体に足パーツを関連付ける
	police = &policeWk[0];
	for (int i = 0; i < POLICE_MAX; i++, police++)
	{
		// 使用状態のポリスにのみパーツをセット
		if (!police->use) continue;
		// 未使用の右足パーツをセット
		policeLeg = &policeLegWk[0];
		for (int j = 0; j < POLICE_LEG_MAX; j++, policeLeg++)
		{	// 未使用かつ右足であることのチェック
			if ((policeLeg->use) || (policeLeg->type == 1)) continue;
			// 本体と同じ番号をセット
			policeLeg->num = police->num;
			// 使用状態にする
			policeLeg->use = true;
			break;
		}
		// 未使用の左足パーツをセット
		policeLeg = &policeLegWk[0];
		for (int j = 0; j < POLICE_LEG_MAX; j++, policeLeg++)
		{	// 未使用かつ左足であることのチェック
			if ((policeLeg->use) || (policeLeg->type == 0)) continue;
			// 本体と同じ番号をセット
			policeLeg->num = police->num;
			// 使用状態にする
			policeLeg->use = true;
			break;
		}
	}
}
//=============================================================================
// ポリスの移動設定関数(引数1:ポリス構造体へのポインタ,引数2:二次元配列のY要素,引数3:二次元配列のX要素)
//=============================================================================
void SetPoliceMove(POLICE *police, int y, int x)
{
	int n = 0;
	int m = 0;

	// ポリスランダム巡回移動処理
	while (1)
	{	// ランダムで次の目標ポイントを決定
		n = rand() % CHECK_POINT_Y_MAX;		// 配列のY要素番号をランダムで求める
		m = rand() % CHECK_POINT_X_MAX;		// 配列のX要素番号をランダムで求める
											// 上下左右なら許可
		if (n == y && m == x + 1 || n == y && m == x - 1 || m == x && n == y + 1 || m == x && n == y - 1) break;
	}
	// 注視点を次の目標ポイントにセット
	police->At = CheckPointWk[n][m];
	// 注視点を向くためのY軸回転角度を求める
	D3DXVECTOR3 vec = police->Eye - police->At;		// 注視点へのベクトルを求める
	police->fangleY = (atan2f(vec.x, vec.z));		// 回転角度を求める
													// 現在のポリスの座標から次の目標ポイントへの移動ベクトルを求める
	police->move = CheckPointWk[n][m] - police->Eye;
	// 移動ベクトルを正規化
	D3DXVec3Normalize(&police->move, &police->move);
	// 移動速度調整
	police->move = police->move * POLICE_SPEED;
}
//=============================================================================
// ポリスの移動関数
//=============================================================================
void PoliceMove(void)
{
	POLICE *police = &policeWk[0];
	POLICE_ARM *policeArm = &policeArmWk[0];
	POLICE_LEG *policeLeg = &policeLegWk[0];

	// ポリス本体の移動
	for (int i = 0; i < POLICE_MAX; i++, police++)
	{	// 移動フラグがtrueの時のみ移動
		if (!police->movef) continue;
		police->Eye.x += police->move.x;
		police->Eye.y += police->move.y;
		police->Eye.z += police->move.z;
	}
	// 本体と親子関係のパーツを移動
	police = &policeWk[0];
	for (int i = 0; i < POLICE_MAX; i++, police++)
	{
		// アームの移動
		policeArm = &policeArmWk[0];
		for (int j = 0; j < POLICE_ARM_MAX; j++, policeArm++)
		{
			if (!policeArm->use) continue;
			if (policeArm->num == police->num)
			{	// 本体の座標と一致させる
				policeArm->Eye = police->Eye;
				policeArm->At = police->At;
				// 本体と同じ注視点を向くためのY軸回転角度をセット
				policeArm->fangleY = police->fangleY;
			}
		}
		// レッグの移動
		policeLeg = &policeLegWk[0];
		for (int k = 0; k < POLICE_LEG_MAX; k++, policeLeg++)
		{	// 本体の座標と一致させる
			if (!policeLeg->use) continue;
			if (policeLeg->num == police->num)
			{
				policeLeg->Eye = police->Eye;
				policeLeg->At = police->At;
				// 本体と同じ注視点を向くためのY軸回転角度をセット
				policeLeg->fangleY = police->fangleY;
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
	if (pIn->use)
	{	// 使用か未使用かチェック
		// 回転軸XZの設定
		pIn->axisXZ = AxisXZ;
		// 回転軸Yの設定
		pIn->axisY = AxisY;
		// XZ軸回転角度の設定
		if (pIn->type == 0)
		{	// 右パーツの場合
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
		}
		if (pIn->type == 1)
		{	// 左パーツの場合
			if (pIn->fangleXZ >= fAngle)
			{	// 一定角度までパーツ上がったらフラグ切り替え
				pIn->rotf = true;
			}
			if (pIn->fangleXZ <= -fAngle)
			{	// 一定角度までパーツ上がったらフラグ切り替え
				pIn->rotf = false;
			}
			if (pIn->rotf == true)
			{	// 負の回転
				pIn->fangleXZ -= fAngle / frame;
				if (pIn->fangleXZ < -D3DX_PI)
				{
					pIn->fangleXZ += D3DX_PI * 2.0f;
				}
			}
			if (pIn->rotf == false)
			{	// 正の回転
				pIn->fangleXZ += fAngle / frame;
				if (pIn->fangleXZ > D3DX_PI)
				{
					pIn->fangleXZ -= D3DX_PI * 2.0f;
				}
			}
		}
		// XZ回転軸ベクトルが0の場合のエラー処理
		if (pIn->axisXZ == D3DXVECTOR3(0.0f, 0.0f, 0.0f))
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
//=============================================================================
// アニメーション処理関数
//=============================================================================
void Animation(void)
{
	POLICE *police = &policeWk[0];
	POLICE_ARM *policeArm = &policeArmWk[0];
	POLICE_LEG *policeLeg = &policeLegWk[0];

	// ポリス本体アニメーション処理
	for (int i = 0; i < POLICE_MAX; i++, police++)
	{
		SetAnimation(police, NULL, NULL,
			D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	}
	// アームアニメーション処理
	for (int i = 0; i < POLICE_ARM_MAX; i++, policeArm++)
	{
		SetAnimation(policeArm, POLICE_ARM_ANGLE, POLICE_ARM_ANIM_FRAME,
			D3DXVECTOR3(1.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	}
	// レッグアニメーション処理
	for (int i = 0; i < POLICE_LEG_MAX; i++, policeLeg++)
	{
		SetAnimation(policeLeg, POLICE_LEG_ANGLE, POLICE_LEG_ANIM_FRAME,
			D3DXVECTOR3(1.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	}
}
//=============================================================================
// ポリス同士の当たり判定処理関数
//=============================================================================
void PoliceEachCollision(void)
{
	POLICE *police = &policeWk[0];

	for (int i = 0; i < POLICE_MAX; i++)
	{	// 使用状態のポリスのみチェック
		if (!policeWk[i].use) continue;
		for (int j = i + 1; j < POLICE_MAX; j++)
		{	// 使用状態のポリスのみチェック
			if (!policeWk[j].use) continue;
			if (CollisionBC(policeWk[i].Eye, policeWk[j].Eye, POLICE_RADIUS + POLICE_RADIUS_VALUE, POLICE_RADIUS + POLICE_RADIUS_VALUE))
			{	// ポリス同士がぶつかったら
				// お互いのmoveベクトルを反転
				police[i].move = -police[i].move;
				police[j].move = -police[j].move;
				// 向きも反転(新しいY軸回転角度を求める)
				police[i].fangleY = police[i].fangleY + D3DX_PI;
				police[j].fangleY = police[j].fangleY + D3DX_PI;
				// チェックポイントとの当たり判定有効フラグをtrueに
				police[i].able_hit = true;
				police[j].able_hit = true;
			}
		}
	}
}
//=============================================================================
// 移動無効処理関数(引数：移動無効が解除されるまでのフレーム数)
//=============================================================================
void PoliceMoveControl(int frame)
{
	POLICE *police = &policeWk[0];

	for (int i = 0; i < POLICE_MAX; i++, police++)
	{
		if (!police->movef) police->key2++;
		// 移動無効時間の解除
		if (police->key2 % frame == 0)
		{
			police->key2 = 0;
			police->movef = true;
		}
	}
}
