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
D3DXMATRIX* FixedPostureLookAtMatrix(D3DXMATRIX *pout, D3DXVECTOR3 *pEye, D3DXVECTOR3 *pAt, D3DXVECTOR3 *pUp);
D3DXMATRIX* VariablePostureLookAtMatrix(D3DXMATRIX *pout, D3DXVECTOR3 *pEye, D3DXVECTOR3 *pAt, D3DXVECTOR3 *pUp);

void PoliceMove(POLICE *police, int y, int x);


//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9	g_pD3DTexturePolice;									// テクスチャ読み込み場所
LPD3DXMESH			g_pD3DXMeshPolice;										// ID3DXMeshインターフェイスへのポインタ
LPD3DXBUFFER		g_pD3DXBuffMatPolice;									// メッシュのマテリアル情報を格納
DWORD				g_nNumMatPolice;										// 属性情報の総数

D3DXMATRIX			g_mtxWorldPolice;										// ワールドマトリックス

POLICE				policeWk[POLICE_MAX];									// ポリス格納ワーク

D3DXVECTOR3			CheckPointWk[CHECK_POINT_Y_MAX][CHECK_POINT_X_MAX];		// チェックポイント格納ワーク

int					animCnt;												// アニメカウント
int					sp_Update;												// 更新頻度計算用


//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitPolice(int nType)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	POLICE *police = &policeWk[0];
	FIELD *field = GetField(0);

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

	}

	// 方向転換点の初期設定
	CheckPointWk[0][0] = D3DXVECTOR3(-FIELD_SIZE_X / 2, 0.0f, FIELD_SIZE_Z / 2);		// 左上(-300,0,300)
	CheckPointWk[1][0] = D3DXVECTOR3(0.0f, 0.0f, FIELD_SIZE_Z / 2);						// 中心上(0,0,300)
	CheckPointWk[2][0] = D3DXVECTOR3(FIELD_SIZE_X / 2, 0.0f, FIELD_SIZE_Z / 2);			// 右上(300,0,300)
	CheckPointWk[0][1] = D3DXVECTOR3(-FIELD_SIZE_X / 2, 0.0f, 0.0f);					// 中心左(-300,0,0)
	CheckPointWk[1][1] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);									// 中心(0,0,0)
	CheckPointWk[2][1] = D3DXVECTOR3(FIELD_SIZE_X / 2, 0.0f, 0.0f);						// 中心右(300,0,0)
	CheckPointWk[0][2] = D3DXVECTOR3(-FIELD_SIZE_X / 2, 0.0f, -FIELD_SIZE_Z / 2);		// 左下(-300,0,-300)
	CheckPointWk[1][2] = D3DXVECTOR3(-0.0f, 0.0f, -FIELD_SIZE_Z / 2);					// 中心下(0,0,-300)
	CheckPointWk[2][2] = D3DXVECTOR3(FIELD_SIZE_X / 2, 0.0f, -FIELD_SIZE_Z / 2);		// 右下(300,0,-300)


	// ポリスの初期化処理
	for (int i = 0; i < POLICE_MAX; i++, police++)
	{
		// ポリスの視点(位置座標)の初期化
		//police->Eye = D3DXVECTOR3(-FIELD_SIZE_X / 2, 0.0f, FIELD_SIZE_Z / 2);
		police->Eye = D3DXVECTOR3(0.0f, 0.0f, 100.0f);

		// ポリスの注視点の初期化
		police->At = D3DXVECTOR3(0.0f, 0.0f, 50.0f);
		// ポリスの上方向の初期化
		police->Up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		// ポリスの向きの初期化
		police->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		//police->rot = 0.0f;

		// ポリスの移動量の初期化
		police->move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		//police->move = CheckPointWk[0][0] - CheckPointWk[0][1];
		//D3DXVec3Normalize(&police->move, &police->move);

		//police->move = CheckPointWk[1][1] - CheckPointWk[0][0];
		//D3DXVec3Normalize(&police->move, &police->move);

		// 回転の中心点の初期設定(原点ではなく少しずらす）
		police->rotBasis = D3DXVECTOR3(0.0f, 60.0f, 0.0f);

		// ポリスのスケールの初期化
		police->scl = D3DXVECTOR3(1.0f * 2, 1.0f * 2, 1.0f * 2);

		// ポリスの回転軸の初期化
		police->axisXZ = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
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




	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitPolice(void)
{
	for (int nCntPoliceAnim = 0; nCntPoliceAnim < POLICE_MAX; nCntPoliceAnim++)
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
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdatePolice(void)
{
	POLICE *police = &policeWk[0];
	CAMERA *camera = GetCamera();
	PLAYER *player = GetPlayer(0);

	// 当たり判定の一定時間無効処理
	for (int i = 0; i < POLICE_MAX; i++, police++)
	{
		police->key++;
		// 当たり判定無効時間の解除
		if (police->key % 120 == 0)
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
					if (CollisionBC(police->Eye, CheckPointWk[j][i], 70.0f, 70.0f))
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

	// ポリス回転処理
	police = &policeWk[0];
	for (int i = 0; i < POLICE_MAX; i++, police++)
	{
		// クォータニオンによる回転のXZ軸回転軸を求める
		// 空方向のベクトルと進行方向のベクトルの外積が回転軸
		//D3DXVec3Cross(&police->axis, D3DXVec3Normalize(&police->rotBasis, &police->rotBasis), D3DXVec3Normalize(&police->move, &police->move));
		D3DXVec3Normalize(&police->axisXZ, &police->axisXZ);
		D3DXVec3Normalize(&police->axisY, &police->axisY);

		// 回転角度の設定
		police->fangleXZ += VALUE_ROTATE_CAMERA / 1.0f;
		if (police->fangleXZ > D3DX_PI)
		{
			police->fangleXZ -= D3DX_PI * 2.0f;
		}
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

	police = &policeWk[0];
#ifdef _DEBUG
	PrintDebugProc("[ポリスの位置  ：(%f : %f : %f)]\n", police->Eye.x, police->Eye.y, police->Eye.z);
	PrintDebugProc("[ポリスの注視点  ：(%f : %f : %f)]\n", police->At.x, police->At.y, police->At.z);
	PrintDebugProc("[ポリスの移動ベクトル  ：(%f : %f : %f)]\n", police->move.x, police->move.y, police->move.z);
	PrintDebugProc("[ポリスの向き  ：(%f)]\n", police->rot);
	PrintDebugProc("[ポリスの使用状態  ：(%d)]\n", police->use);

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
void PoliceMove(POLICE *police, int y, int x)
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
	police->move = police->move * VALUE_MOVE_POLICE;
}
