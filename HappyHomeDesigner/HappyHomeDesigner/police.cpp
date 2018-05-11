

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


//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
D3DXMATRIX* PoliceLookAtMatrix(D3DXMATRIX *pout, D3DXVECTOR3 *pEye, D3DXVECTOR3 *pAt, D3DXVECTOR3 *pUp);
void PoliceMove(int y, int x);


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
int					key;													// フレームカウント
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
	CheckPointWk[0][0] = D3DXVECTOR3(-300.0f, 0.0f, 300.0f);	// 左上(-300,0,300)
	CheckPointWk[1][0] = D3DXVECTOR3(0.0f, 0.0f, 300.0f);		// 中心上(0,0,300)
	CheckPointWk[2][0] = D3DXVECTOR3(300.0f, 0.0f, 300.0f);		// 右上(300,0,300)
	CheckPointWk[0][1] = D3DXVECTOR3(-300.0f, 0.0f, 0.0f);		// 中心左(-300,0,0)
	CheckPointWk[1][1] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 中心(0,0,0)
	CheckPointWk[2][1] = D3DXVECTOR3(300.0f, 0.0f, 0.0f);		// 中心右(300,0,0)
	CheckPointWk[0][2] = D3DXVECTOR3(-300.0f, 0.0f, -300.0f);	// 左下(-300,0,-300)
	CheckPointWk[1][2] = D3DXVECTOR3(-0.0f, 0.0f, -300.0f);		// 中心下(0,0,-300)
	CheckPointWk[2][2] = D3DXVECTOR3(300.0f, 0.0f, -300.0f);	// 右下(300,0,-300)


	// ポリスの初期化処理
	for (int i = 0; i < POLICE_MAX; i++, police++)
	{
		// ポリスの視点(位置座標)の初期化
		police->Eye = D3DXVECTOR3(-300.0f, 0.0f, 300.0f);
		// ポリスの注視点の初期化
		police->At = D3DXVECTOR3(0.0f, 0.0f, 50.0f);
		// ポリスの上方向の初期化
		police->Up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		// ポリスの向きの初期化
		police->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		// ポリスの移動量の初期化
		police->move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		//police->move = CheckPointWk[0][0] - CheckPointWk[0][1];
		//D3DXVec3Normalize(&police->move, &police->move);

		//police->move = CheckPointWk[1][1] - CheckPointWk[0][0];
		//D3DXVec3Normalize(&police->move, &police->move);


		// ポリスのスケールの初期化
		police->scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

		// useフラグをtrueに設定
		police->use = true;

		// 当たり判定有効フラグをtrueに設定
		police->able_hit = true;

		// ポリスの移動速度初期化
		police->speed = VALUE_MOVE_POLICE;

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

	key++;		// フレームカウント

	// 当たり判定無効時間の解除
	if (key % 180 == 0)
	{
		key = 0;
		police->able_hit = true;
	}

	for (int k = 0; k < POLICE_MAX; k++, police++)
	{	// ポリスについてチェック
		if (police->able_hit)
		{	// 当たり判定が有効なポリスのみチェック
			for (int j = 0; j < CHECK_POINT_Y_MAX; j++)
			{	// 配列Y要素についてチェック
				for (int i = 0; i < CHECK_POINT_X_MAX; i++)
				{	// 配列X要素についてチェック
					if (CollisionBC(police->Eye, CheckPointWk[j][i], 30.0f, 30.0f))
					{	// チェックポイントに侵入したら方向転換し、移動ベクトル算出
						PoliceMove(j,i);
						// 当たり判定有効フラグをfalseに
						police->able_hit = false;
						break;
					}
				}
			}
		}
	}
	police = &policeWk[0];


	// デバッグ時に手動でポリス移動
//#ifdef _DEBUG
//	if (GetKeyboardPress(DIK_A))
//	{
//		if (GetKeyboardPress(DIK_W))
//		{// 左前移動
//			police->move.x -= cosf(camera->rotCamera.y + D3DX_PI * 0.25f) * VALUE_MOVE_POLICE;
//			police->move.z += sinf(camera->rotCamera.y + D3DX_PI * 0.25f) * VALUE_MOVE_POLICE;
//		}
//		else if (GetKeyboardPress(DIK_S))
//		{// 左後移動
//			police->move.x -= cosf(camera->rotCamera.y - D3DX_PI * 0.25f) * VALUE_MOVE_POLICE;
//			police->move.z += sinf(camera->rotCamera.y - D3DX_PI * 0.25f) * VALUE_MOVE_POLICE;
//		}
//		else
//		{// 左移動
//			police->move.x -= cosf(camera->rotCamera.y) * VALUE_MOVE_POLICE;
//			police->move.z += sinf(camera->rotCamera.y) * VALUE_MOVE_POLICE;
//		}
//	}
//	else if (GetKeyboardPress(DIK_D))
//	{
//		if (GetKeyboardPress(DIK_W))
//		{// 右前移動
//			police->move.x += cosf(camera->rotCamera.y - D3DX_PI * 0.25f) * VALUE_MOVE_POLICE;
//			police->move.z -= sinf(camera->rotCamera.y - D3DX_PI * 0.25f) * VALUE_MOVE_POLICE;
//		}
//		else if (GetKeyboardPress(DIK_S))
//		{// 右後移動
//			police->move.x += cosf(camera->rotCamera.y + D3DX_PI * 0.25f) * VALUE_MOVE_POLICE;
//			police->move.z -= sinf(camera->rotCamera.y + D3DX_PI * 0.25f) * VALUE_MOVE_POLICE;
//		}
//		else
//		{// 右移動
//			police->move.x += cosf(camera->rotCamera.y) * VALUE_MOVE_POLICE;
//			police->move.z -= sinf(camera->rotCamera.y) * VALUE_MOVE_POLICE;
//		}
//	}
//	else if (GetKeyboardPress(DIK_W))
//	{// 前移動
//		police->move.x += sinf(camera->rotCamera.y) * VALUE_MOVE_POLICE;
//		police->move.z += cosf(camera->rotCamera.y) * VALUE_MOVE_POLICE;
//	}
//	else if (GetKeyboardPress(DIK_S))
//	{// 後移動
//		police->move.x -= sinf(camera->rotCamera.y) * VALUE_MOVE_POLICE;
//		police->move.z -= cosf(camera->rotCamera.y) * VALUE_MOVE_POLICE;
//	}
//
//	
//#endif
//
	// ポリス移動処理

	// 移動量に慣性をかける
	//police->move.x += (0.0f - police->move.x) * RATE_MOVE_POLICE;
	//police->move.y += (0.0f - police->move.y) * RATE_MOVE_POLICE;
	//police->move.z += (0.0f - police->move.z) * RATE_MOVE_POLICE;

	/// 位置移動
	police->Eye.x += police->move.x;
	police->Eye.y += police->move.y;
	//if (police->Eye.y < 5.0f)
	//{
	//	police->Eye.y = 5.0f;
	//}
	//if (police->Eye.y > 75.0f)
	//{
	//	police->Eye.y = 75.0f;
	//}
	police->Eye.z += police->move.z;


	// ポリスの移動制限（場外に行かないようにする）
	// Z座標のマックスとX座標のマックスで制限かける
	//panel = GetPanel(GetPanelNumber(PANEL_NUM_Z, PANEL_NUM_X));		// 右上
	//if (police->Eye.x > panel->Pos.x)
	//{
	//	police->Eye.x = panel->Pos.x;
	//}
	//if (police->Eye.z > panel->Pos.z)
	//{
	//	police->Eye.z = panel->Pos.z;
	//}

	// Z座標のミニマムとX座標のミニマムで制限かける
	//panel = GetPanel(GetPanelNumber(1, 1));							// 左下
	//if (police->Eye.x < -panel->Pos.x)
	//{
	//	police->Eye.x = -panel->Pos.x;
	//}
	//if (police->Eye.z < -panel->Pos.z)
	//{
	//	police->Eye.z = -panel->Pos.z;
	//}



	// チェックポイントに入ったら方向転換

	// チェックポイントに入ったかの判定
	//if(CollisionBC(police->Eye, movePointWk[0], 30.0f, 30.0f));
	//{	// チェックポイントに入ったら

	//	// 向きをランダムで決定
	//	rand () % CHECK_POINT_MAX
	//}


	police = &policeWk[0];
#ifdef _DEBUG
	PrintDebugProc("[ポリスの位置  ：(%f : %f : %f)]\n", police->Eye.x, police->Eye.y, police->Eye.z);
	PrintDebugProc("[ポリスの移動ベクトル  ：(%f : %f : %f)]\n", police->move.x, police->move.y, police->move.z);
	PrintDebugProc("[ポリスの向き  ：(%f)]\n", police->rot.y);
	PrintDebugProc("[ポリスの使用状態  ：(%d)]\n", police->use);

#endif
}
//=============================================================================
// 描画処理
//=============================================================================
void DrawPolice(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTranslate, mtxScale;
	D3DXMATERIAL *pD3DXMat;
	D3DMATERIAL9 matDef;

	POLICE *police = &policeWk[0];

	for (int i = 0; i < POLICE_MAX; i++, police++)
	{
		if (police->use == true)	// 使用状態なら描画する
		{
			// ライトをon
			pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);


			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_mtxWorldPolice);

			// スケールを反映
			D3DXMatrixScaling(&mtxScale, police->scl.x,
				police->scl.y,
				police->scl.z);
			D3DXMatrixMultiply(&g_mtxWorldPolice,
				&g_mtxWorldPolice, &mtxScale);


			// 回転を反映
			//D3DXMatrixRotationYawPitchRoll(&mtxRot, police->rot.y, police->rot.x, police->rot.z);
			//D3DXMatrixMultiply(&g_mtxWorldPolice, &g_mtxWorldPolice, &mtxRot);
			PoliceLookAtMatrix(&mtxRot, &police->Eye, &police->At, &police->Up);

			D3DXMatrixMultiply(&g_mtxWorldPolice, &g_mtxWorldPolice, &mtxRot);

			// 移動を反映
			D3DXMatrixTranslation(&mtxTranslate, police->Eye.x, police->Eye.y, police->Eye.z);
			D3DXMatrixMultiply(&g_mtxWorldPolice, &g_mtxWorldPolice, &mtxTranslate);

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
// ポリスの回転行列算出関数
//=============================================================================
D3DXMATRIX* PoliceLookAtMatrix(D3DXMATRIX *pout, D3DXVECTOR3 *pEye, D3DXVECTOR3 *pAt, D3DXVECTOR3 *pUp)
{
	D3DXVECTOR3 X, Y, Z, D;
	D = *pEye - *pAt;
	//D = *pAt - *pEye;


	D3DXVec3Normalize(&D, &D);
	D3DXVec3Cross(&X, D3DXVec3Normalize(&Y, pUp), &D);
	D3DXVec3Normalize(&X, &X);
	D3DXVec3Normalize(&Z, D3DXVec3Cross(&Z, &X, &Y));


	pout->_11 = X.x; pout->_12 = X.y; pout->_13 = X.z; pout->_14 = 0;
	pout->_21 = Y.x; pout->_22 = Y.y; pout->_23 = Y.z; pout->_24 = 0;
	pout->_31 = Z.x; pout->_32 = Z.y; pout->_33 = Z.z; pout->_34 = 0;
	pout->_41 = 0.0f; pout->_42 = 0.0f; pout->_43 = 0.0f; pout->_44 = 1.0f;

	return pout;
}
//=============================================================================
// ポリスの移動関数
//=============================================================================
void PoliceMove(int y, int x)
{
	POLICE *police = &policeWk[0];

	// ポリスランダム巡回移動処理
	int n = 0;
	int m = 0;

	while (1)
	{	// ランダムで次の目標ポイントを決定
		n = rand() % CHECK_POINT_Y_MAX;		// 配列のY要素番号をランダムで求める
		m = rand() % CHECK_POINT_X_MAX;		// 配列のX要素番号をランダムで求める

		// 現在の配列要素番号との差が2より小さい場合ループから抜ける(進行可能なポイントの場合)
		//if (abs(y - n) < 2 && abs(x - m) < 2) break;

		// XY配列要素番号が負か最大値を超えているかチェック

		// 上下左右なら許可
		if (n == y && m == x + 1 || n == y && m == x - 1 || m == x && n == y + 1 || m == x && n == y - 1) break;
	}

	// 注視点を次の目標ポイントにセット
	police->At = CheckPointWk[n][m];

	// 現在のポイントから次の目標ポイントへの移動ベクトルを求める
	//police->move = CheckPointWk[n][m] - CheckPointWk[y][x];

	// 現在のポリスの座標から次の目標ポイントへの移動ベクトルを求める
	police->move = CheckPointWk[n][m] - police->Eye;

	// 移動ベクトルを正規化
	D3DXVec3Normalize(&police->move, &police->move);

	// 移動速度調整
	police->move = police->move * VALUE_MOVE_POLICE;

	//if (GetKeyboardPress(DIK_NUMPAD4))
	//{// 左を向く
	//	//police->rot.y = camera->rotCamera.y - D3DX_PI * 0.50f;

	//	// ここをフィールド基準で
	//	police->rot.y = - D3DX_PI * 0.50f;

	//	//if (police->rot.y < -D3DX_PI)
	//	//{
	//	//	police->rot.y += D3DX_PI * 2.0f;
	//	//}

	//	police->At.x = police->Eye.x - sinf(police->rot.y);
	//	police->At.z = police->Eye.z - cosf(police->rot.y);


	//	// 移動量計算
	//	//police->move.x -= cosf(police->rot.y) * VALUE_MOVE_POLICE;
	//	//police->move.z += sinf(police->rot.y) * VALUE_MOVE_POLICE;

	//	// 注視点の方向に進み続ける
	//	police->move += (police->Eye - police->At);


	//}
	//if (GetKeyboardPress(DIK_NUMPAD6))
	//{// 右を向く
	//	police->rot.y = D3DX_PI * 0.50f;


	//	//if (police->rot.y < -D3DX_PI)
	//	//{
	//	//	police->rot.y += D3DX_PI * 2.0f;
	//	//}

	//	police->At.x = police->Eye.x - sinf(police->rot.y);
	//	police->At.z = police->Eye.z - cosf(police->rot.y);

	//	// 移動量計算
	//	//police->move.x += cosf(police->rot.y) * VALUE_MOVE_POLICE;
	//	//police->move.z -= sinf(police->rot.y) * VALUE_MOVE_POLICE;

	//	// 注視点の方向に進み続ける
	//	police->move += (police->Eye - police->At);


	//}
	//if (GetKeyboardPress(DIK_NUMPAD8))
	//{// 前を向く
	//	police->rot.y = 0.0f;

	//	//if (police->rot.y < -D3DX_PI)
	//	//{
	//	//	police->rot.y += D3DX_PI * 2.0f;
	//	//}

	//	police->At.x = police->Eye.x - sinf(police->rot.y);
	//	police->At.z = police->Eye.z - cosf(police->rot.y);

	//	// 移動量計算
	//	//police->move.x += sinf(police->rot.y) * VALUE_MOVE_POLICE;
	//	//police->move.z += cosf(police->rot.y) * VALUE_MOVE_POLICE;

	//	// 注視点の方向に進み続ける
	//	police->move += (police->Eye - police->At);


	//}
	//if (GetKeyboardPress(DIK_NUMPAD2))
	//{// 後を向く
	//	police->rot.y = D3DX_PI;


	//	//if (police->rot.y < -D3DX_PI)
	//	//{
	//	//	police->rot.y += D3DX_PI * 2.0f;
	//	//}

	//	police->At.x = police->Eye.x - sinf(police->rot.y);
	//	police->At.z = police->Eye.z - cosf(police->rot.y);

	//	// 移動量計算
	//	//police->move.x -= sinf(police->rot.y) * VALUE_MOVE_POLICE;
	//	//police->move.z -= cosf(police->rot.y) * VALUE_MOVE_POLICE;

	//	// 注視点の方向に進み続ける
	//	police->move += (police->Eye - police->At);


	//}




}
