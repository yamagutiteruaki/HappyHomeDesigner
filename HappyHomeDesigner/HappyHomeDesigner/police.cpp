//=============================================================================
//
// ポリス処理 [police.cpp]
// Author : GP11B243-18-千坂浩太
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

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void PoliceMove(void *pIn, int y, int x);
void SetAnimation(int pType, float fAngle, int frame,
	D3DXVECTOR3 AxisXZ, D3DXVECTOR3 AxisY, D3DXVECTOR3 basis);
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
POLICE_ARM			policeArmWk[POLICE_ARM_TYPE_MAX];						// ポリスアーム格納ワーク

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
POLICE_LEG			policeLegWk[POLICE_LEG_TYPE_MAX];						// ポリスアーム格納ワーク

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
		D3DXCreateTextureFromFile(pDevice,					// デバイスへのポインタ
			TEXTURE_FILENAME,		// ファイルの名前
			&g_pD3DTextureModel);	// 読み込むメモリー
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
			D3DXCreateTextureFromFile(pDevice,					// デバイスへのポインタ
				TEXTURE_FILENAME,		// ファイルの名前
				&g_pD3DTextureModel);	// 読み込むメモリー
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
			D3DXCreateTextureFromFile(pDevice,					// デバイスへのポインタ
				TEXTURE_FILENAME,		// ファイルの名前
				&g_pD3DTextureModel);	// 読み込むメモリー
#endif
		}
	}

	// ポリス本体の初期化処理
	for (int i = 0; i < POLICE_MAX; i++, police++)
	{
		// ポリスの視点(位置座標)の初期化
		//police->Eye = D3DXVECTOR3(-FIELD_SIZE_X / 2, 0.0f, FIELD_SIZE_Z / 2);
		police->Eye = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		// ポリスの注視点の初期化
		police->At = D3DXVECTOR3(0.0f, 0.0f, 50.0f);
		// ポリスの上方向の初期化
		police->Up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		// ポリスの向きの初期化
		police->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		// ポリスの移動量の初期化
		police->move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		// 回転の中心点の初期設定(原点ではなく少しずらす）
		police->rotBasis = D3DXVECTOR3(0.0f, 60.0f, 0.0f);
		// ポリスのスケールの初期化
		police->scl = D3DXVECTOR3(1.0f * 2, 1.0f * 2, 1.0f * 2);
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
		// ポリスの移動速度初期化
		police->speed = VALUE_MOVE_POLICE;
		// ポリスのフレームカウント初期化
		police->key = 0;
	}

	// アームの初期化処理
	for (int i = 0; i < POLICE_ARM_MAX; i++, policeArm++)
	{
		// アームの視点(位置座標)の初期化
		//policeArm->Eye = D3DXVECTOR3(-FIELD_SIZE_X / 2, 0.0f, FIELD_SIZE_Z / 2);
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
		policeArm->rotBasis = D3DXVECTOR3(0.0f, 60.0f, 0.0f);
		// アームのスケールの初期化
		policeArm->scl = D3DXVECTOR3(1.0f * 2, 1.0f * 2, 1.0f * 2);
		// アームの回転軸の初期化
		policeArm->axisXZ = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		policeArm->axisY = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		// アームの回転角度の初期化
		policeArm->fangleXZ = 0.0f;
		policeArm->fangleY = 0.0f;
		// useフラグをtrueに設定
		policeArm->use = true;
		// アームの移動速度初期化
		policeArm->speed = VALUE_MOVE_POLICE;
		// アームのフレームカウント初期化
		policeArm->key = 0;
		// アームのタイプの初期化(右腕が0・左腕が1)
		if(i < POLICE_MAX)
		{	// 右腕をポリスの人数分用意
			policeArm->type = 0;
		}
		if (i >= POLICE_MAX)
		{	// 左腕をポリスの人数分用意
			policeArm->type = 1;
		}
		// 回転切り替えフラグをtrueに設定
		policeArm->rotf = true;
	}

	// レッグの初期化処理
	for (int i = 0; i < POLICE_LEG_TYPE_MAX; i++, policeLeg++)
	{
		// レッグの視点(位置座標)の初期化
		//policeLeg->Eye = D3DXVECTOR3(-FIELD_SIZE_X / 2, 0.0f, FIELD_SIZE_Z / 2);
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
		policeLeg->rotBasis = D3DXVECTOR3(0.0f, 60.0f, 0.0f);
		// レッグのスケールの初期化
		policeLeg->scl = D3DXVECTOR3(1.0f * 2, 1.0f * 2, 1.0f * 2);
		// レッグの回転軸の初期化
		policeLeg->axisXZ = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		policeLeg->axisY = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		// レッグの回転角度の初期化
		policeLeg->fangleXZ = 0.0f;
		policeLeg->fangleY = 0.0f;
		// useフラグをtrueに設定
		policeLeg->use = true;
		// レッグの移動速度初期化
		policeLeg->speed = VALUE_MOVE_POLICE;
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
		// 回転切り替えフラグをtrueに設定
		policeLeg->rotf = true;
	}

	// チェックポイントの初期設定
	CheckPointWk[0][0] = D3DXVECTOR3(-FIELD_SIZE_X / 2, 0.0f, FIELD_SIZE_Z / 2);		// 左上(-300,0,300)
	CheckPointWk[1][0] = D3DXVECTOR3(0.0f, 0.0f, FIELD_SIZE_Z / 2);						// 中心上(0,0,300)
	CheckPointWk[2][0] = D3DXVECTOR3(FIELD_SIZE_X / 2, 0.0f, FIELD_SIZE_Z / 2);			// 右上(300,0,300)
	CheckPointWk[0][1] = D3DXVECTOR3(-FIELD_SIZE_X / 2, 0.0f, 0.0f);					// 中心左(-300,0,0)
	CheckPointWk[1][1] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);									// 中心(0,0,0)
	CheckPointWk[2][1] = D3DXVECTOR3(FIELD_SIZE_X / 2, 0.0f, 0.0f);						// 中心右(300,0,0)
	CheckPointWk[0][2] = D3DXVECTOR3(-FIELD_SIZE_X / 2, 0.0f, -FIELD_SIZE_Z / 2);		// 左下(-300,0,-300)
	CheckPointWk[1][2] = D3DXVECTOR3(-0.0f, 0.0f, -FIELD_SIZE_Z / 2);					// 中心下(0,0,-300)
	CheckPointWk[2][2] = D3DXVECTOR3(FIELD_SIZE_X / 2, 0.0f, -FIELD_SIZE_Z / 2);		// 右下(300,0,-300)

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitPolice(void)
{
	// 本体
	for (int i = 0; i < POLICE_MAX; i++)
	{
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
	}

	// アーム
	for (int i = 0; i < POLICE_ARM_MAX; i++)
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
	for (int i = 0; i < POLICE_LEG_MAX; i++)
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

	// 当たり判定の一定時間無効処理
	police = &policeWk[0];
	for (int i = 0; i < POLICE_MAX; i++, police++)
	{
		if (!police->able_hit) police->key++;
		// 当たり判定無効時間の解除
		if (police->key % 300 == 0)
		{
			police->key = 0;
			police->able_hit = true;
		}
	}
	// ポリスの当たり判定処理
	police = &policeWk[0];
	for (int k = 0; k < POLICE_MAX; k++, police++)
	{	// ポリスについてチェック
		if (police->able_hit)
		{	// 当たり判定が有効なポリスのみチェック
			for (int j = 0; j < CHECK_POINT_Y_MAX; j++)
			{	// 配列Y要素についてチェック
				for (int i = 0; i < CHECK_POINT_X_MAX; i++)
				{	// 配列X要素についてチェック
					if (CollisionBC(police->Eye, CheckPointWk[j][i], 20.0f, 20.0f))
					{	// チェックポイントに侵入したら方向転換し、移動ベクトル算出
						PoliceMove(police, j, i);
						// 当たり判定有効フラグをfalseに
						police->able_hit = false;
						break;
					}
				}
			}
		}
	}
	// ポリス移動処理
	police = &policeWk[0];
	for (int i = 0; i < POLICE_MAX; i++, police++)
	{
		// 位置移動
		police->Eye.x += police->move.x;
		police->Eye.y += police->move.y;
		police->Eye.z += police->move.z;
	}
	// アームとレッグの視点と注視点を本体と一致させる
	police = &policeWk[0];
	policeArm = &policeArmWk[0];
	policeLeg = &policeLegWk[0];
	for (int i = 0; i < POLICE_ARM_MAX; i++, policeArm++)
	{
		policeArm->Eye = police->Eye;
		policeArm->At = police->At;
	}
	for (int i = 0; i < POLICE_LEG_MAX; i++, policeLeg++)
	{
		policeLeg->Eye = police->Eye;
		policeLeg->At = police->At;
	}

	// アニメーション
	// ポリス本体アニメーション処理
	SetAnimation(TYPE_BODY, NULL, NULL,
		D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXVECTOR3(0.0f, 60.0f, 0.0f));
	// アームアニメーション処理
	SetAnimation(TYPE_ARM, POLICE_ARM_ANGLE, POLICE_ARM_ANIM_FRAME,
		D3DXVECTOR3(1.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXVECTOR3(0.0f, 60.0f, 0.0f));
	// レッグアニメーション処理
	SetAnimation(TYPE_LEG, POLICE_LEG_ANGLE, POLICE_LEG_ANIM_FRAME,
		D3DXVECTOR3(1.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXVECTOR3(0.0f, 40.0f, 0.0f));

	police = &policeWk[0];
	policeArm = &policeArmWk[0];
#ifdef _DEBUG
	PrintDebugProc("[ポリスの位置  ：(%f : %f : %f)]\n", police->Eye.x, police->Eye.y, police->Eye.z);
	PrintDebugProc("[ポリスの注視点  ：(%f : %f : %f)]\n", police->At.x, police->At.y, police->At.z);
	PrintDebugProc("[ポリスの移動ベクトル  ：(%f : %f : %f)]\n", police->move.x, police->move.y, police->move.z);
	//PrintDebugProc("[ポリスの向き  ：(%f)]\n", police->rot);
	PrintDebugProc("[ポリスの使用状態  ：(%d)]\n", police->use);
	PrintDebugProc("[右腕の回転角度  ：(%f)]\n", policeArm->fangleXZ);
	PrintDebugProc("[ポリスの当たり判定有効状態  ：(%d)]\n", police->able_hit);

#endif
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
// ポリスの移動処理関数(引数1:ポリスのポインタ,引数2:二次元配列のY要素,引数3:二次元配列のX要素)
//=============================================================================
void PoliceMove(void* pIn, int y, int x)
{
	POLICE *police;
	int n = 0;
	int m = 0;

	police = (POLICE*)pIn;

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
	police->move = police->move * VALUE_MOVE_POLICE;
}
//=============================================================================
// アニメーション設定関数
// (引数1:設定対象の構造体へのポインタ識別番号(0:本体,1:アーム,2:レッグ,etc...),
//  引数2:XZ軸回転角度,
//  引数3:一往復にかかるフレーム数,
//  引数4:回転軸XZ,
//  引数5:回転軸Y,
//  引数6:回転基準点,
//=============================================================================
void SetAnimation(int pType, float fAngle, int frame,
	D3DXVECTOR3 AxisXZ, D3DXVECTOR3 AxisY, D3DXVECTOR3 basis)
{
	POLICE *police;
	POLICE_ARM *policeArm;
	POLICE_LEG *policeLeg;

	switch (pType)
	{	// もとのポインタ型に代入しなおす
	case TYPE_BODY:
		// 本体回転処理
		police = &policeWk[0];
		for (int i = 0; i < POLICE_MAX; i++, police++)
		{
			// 回転基準点の設定
			police->rotBasis = basis;
			// 回転軸XZの設定
			police->axisXZ = AxisXZ;
			// 回転軸Yの設定
			police->axisY = AxisY;
			// XZ回転軸ベクトルが0の場合のエラー処理
			if (police->axisXZ == D3DXVECTOR3(0.0f, 0.0f, 0.0f))
			{	// 回転角度を0にする
				police->fangleXZ = 0.0f;
			}
			// Y回転軸ベクトルが0の場合のエラー処理
			if (police->axisY == D3DXVECTOR3(0.0f, 0.0f, 0.0f))
			{	// 回転角度を0にする
				police->fangleY = 0.0f;
			}
			// 回転クォータニオンを生成
			D3DXQuaternionRotationAxis(&police->qRotateXZ, &police->axisXZ, police->fangleXZ);		// XZ軸回転クォータニオン生成
			D3DXQuaternionRotationAxis(&police->qRotateY, &police->axisY, police->fangleY);			// Y軸回転クォータニオン生成(Atに向かせる)
			D3DXQuaternionMultiply(&police->qAnswer, &police->qRotateXZ, &police->qRotateY);		// 回転クォータニオンを合成
		}
		break;
	case TYPE_ARM:
		// アーム回転処理
		police = &policeWk[0];
		policeArm = &policeArmWk[0];
		for (int i = 0; i < POLICE_ARM_MAX; i++, policeArm++)
		{
			if (policeArm->use)
			{	// 使用か未使用かチェック
				// 回転基準点の設定
				policeArm->rotBasis = basis;
				// 回転軸XZの設定
				policeArm->axisXZ = AxisXZ;
				// 回転軸Yの設定
				policeArm->axisY = AxisY;
				// XZ軸回転角度の設定
				if (policeArm->type == 0)
				{	// 右腕の場合
					if (policeArm->fangleXZ >= fAngle)
					{	// 90度まで腕上がったらフラグ切り替え
						policeArm->rotf = false;
					}
					if (policeArm->fangleXZ <= -fAngle)
					{	// 90度まで腕上がったらフラグ切り替え
						policeArm->rotf = true;
					}
					if (policeArm->rotf == true)
					{	// 正の回転
						policeArm->fangleXZ += fAngle / frame;
						if (policeArm->fangleXZ > D3DX_PI)
						{
							policeArm->fangleXZ -= D3DX_PI * 2.0f;
						}
					}
					if (policeArm->rotf == false)
					{	// 負の回転
						policeArm->fangleXZ -= fAngle / frame;
						if (policeArm->fangleXZ < -D3DX_PI)
						{
							policeArm->fangleXZ += D3DX_PI * 2.0f;
						}
					}
				}
				if (policeArm->type == 1)
				{	// 左腕の場合
					if (policeArm->fangleXZ >= fAngle)
					{	// 90度まで腕上がったらフラグ切り替え
						policeArm->rotf = true;
					}
					if (policeArm->fangleXZ <= -fAngle)
					{	// 90度まで腕上がったらフラグ切り替え
						policeArm->rotf = false;
					}
					if (policeArm->rotf == true)
					{	// 負の回転
						policeArm->fangleXZ -= fAngle / frame;
						if (policeArm->fangleXZ < -D3DX_PI)
						{
							policeArm->fangleXZ += D3DX_PI * 2.0f;
						}
					}
					if (policeArm->rotf == false)
					{	// 正の回転
						policeArm->fangleXZ += fAngle / frame;
						if (policeArm->fangleXZ > D3DX_PI)
						{
							policeArm->fangleXZ -= D3DX_PI * 2.0f;
						}
					}
				}
				// 本体と同じ注視点を向くためのY軸回転角度をセット
				policeArm->fangleY = police->fangleY;			// 本体と一致

				// XZ回転軸ベクトルが0の場合のエラー処理
				if (policeArm->axisXZ == D3DXVECTOR3(0.0f, 0.0f, 0.0f))
				{	// 回転角度を0にする
					policeArm->fangleXZ = 0.0f;
				}
				// Y回転軸ベクトルが0の場合のエラー処理
				if (policeArm->axisY == D3DXVECTOR3(0.0f, 0.0f, 0.0f))
				{	// 回転角度を0にする
					policeArm->fangleY = 0.0f;
				}
				// 回転クォータニオンを生成
				D3DXQuaternionRotationAxis(&policeArm->qRotateXZ, &policeArm->axisXZ, policeArm->fangleXZ);		// XZ軸回転クォータニオン生成
				D3DXQuaternionRotationAxis(&policeArm->qRotateY, &policeArm->axisY, policeArm->fangleY);		// Y軸回転クォータニオン生成(Atに向かせる)
				D3DXQuaternionMultiply(&policeArm->qAnswer, &policeArm->qRotateXZ, &policeArm->qRotateY);		// 回転クォータニオンを合成
			}
		}
		break;
	case TYPE_LEG:
		// レッグ回転処理
		police = &policeWk[0];
		policeLeg = &policeLegWk[0];
		for (int i = 0; i < POLICE_LEG_MAX; i++, policeLeg++)
		{
			if (policeLeg->use)
			{	// 使用か未使用かチェック
				// 回転基準点の設定
				policeLeg->rotBasis = basis;
				// 回転軸XZの設定
				policeLeg->axisXZ = AxisXZ;
				// 回転軸Yの設定
				policeLeg->axisY = AxisY;
				// XZ軸回転角度の設定
				if (policeLeg->type == 0)
				{	// 右足の場合
					if (policeLeg->fangleXZ >= fAngle)
					{	// 90度まで足上がったらフラグ切り替え
						policeLeg->rotf = true;
					}
					if (policeLeg->fangleXZ <= -fAngle)
					{	// 90度まで足上がったらフラグ切り替え
						policeLeg->rotf = false;
					}
					if (policeLeg->rotf == true)
					{	// 負の回転
						policeLeg->fangleXZ -= fAngle / frame;
						if (policeLeg->fangleXZ < -D3DX_PI)
						{
							policeLeg->fangleXZ += D3DX_PI * 2.0f;
						}
					}
					if (policeLeg->rotf == false)
					{	// 正の回転
						policeLeg->fangleXZ += fAngle / frame;
						if (policeLeg->fangleXZ > D3DX_PI)
						{
							policeLeg->fangleXZ -= D3DX_PI * 2.0f;
						}
					}
				}
				if (policeLeg->type == 1)
				{	// 左足の場合
					if (policeLeg->fangleXZ >= fAngle)
					{	// 90度まで足上がったらフラグ切り替え
						policeLeg->rotf = false;
					}
					if (policeLeg->fangleXZ <= -fAngle)
					{	// 90度まで足上がったらフラグ切り替え
						policeLeg->rotf = true;
					}
					if (policeLeg->rotf == true)
					{	// 正の回転
						policeLeg->fangleXZ += fAngle / frame;
						if (policeLeg->fangleXZ > D3DX_PI)
						{
							policeLeg->fangleXZ -= D3DX_PI * 2.0f;
						}
					}
					if (policeLeg->rotf == false)
					{	// 負の回転
						policeLeg->fangleXZ -= fAngle / frame;
						if (policeLeg->fangleXZ < -D3DX_PI)
						{
							policeLeg->fangleXZ += D3DX_PI * 2.0f;
						}
					}
				}
				// 本体と同じ注視点を向くためのY軸回転角度をセット
				policeLeg->fangleY = police->fangleY;			// 本体と一致
				// XZ回転軸ベクトルが0の場合のエラー処理
				if (policeLeg->axisXZ == D3DXVECTOR3(0.0f, 0.0f, 0.0f))
				{	// 回転角度を0にする
					policeLeg->fangleXZ = 0.0f;
				}
				// Y回転軸ベクトルが0の場合のエラー処理
				if (policeLeg->axisY == D3DXVECTOR3(0.0f, 0.0f, 0.0f))
				{	// 回転角度を0にする
					policeLeg->fangleY = 0.0f;
				}
				// 回転クォータニオンを生成
				D3DXQuaternionRotationAxis(&policeLeg->qRotateXZ, &policeLeg->axisXZ, policeLeg->fangleXZ);		// XZ軸回転クォータニオン生成
				D3DXQuaternionRotationAxis(&policeLeg->qRotateY, &policeLeg->axisY, policeLeg->fangleY);		// Y軸回転クォータニオン生成(Atに向かせる)
				D3DXQuaternionMultiply(&policeLeg->qAnswer, &policeLeg->qRotateXZ, &policeLeg->qRotateY);		// 回転クォータニオンを合成
			}
		}
		break;
	}
	return;
}