

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
//#include "shadow.h"


//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void SetPoliceAnimation(int sec);
D3DXMATRIX* PoliceLookAtMatrix(D3DXMATRIX *pout, D3DXVECTOR3 *pEye, D3DXVECTOR3 *pAt, D3DXVECTOR3 *pUp);
void SetPoliceHoming(int no, int frequency, float speedup);


//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9	g_pD3DTexturePolice[POLICE_ANIM_MAX];			// テクスチャ読み込み場所
LPD3DXMESH			g_pD3DXMeshPolice[POLICE_ANIM_MAX];			// ID3DXMeshインターフェイスへのポインタ
LPD3DXBUFFER		g_pD3DXBuffMatPolice[POLICE_ANIM_MAX];		// メッシュのマテリアル情報を格納
DWORD				g_nNumMatPolice[POLICE_ANIM_MAX];				// 属性情報の総数

D3DXMATRIX			g_mtxWorldPolice;							// ワールドマトリックス

float				g_fSizeShadowE;								// 影のサイズ
D3DXCOLOR			g_colShadowE;								// 影の色

POLICE				policeWk[POLICE_MAX];							// ポリス格納ワーク

int					animCnt;									// アニメカウント
int					key;										// フレームカウント
int					sp_Update;									// 更新頻度計算用


const char *FileNamePolice[POLICE_ANIM_MAX] =
{
	"data/MODEL/POLICE/police_a00.x",		// 直立
	"data/MODEL/POLICE/police_a01.x",		// 左足前１
	"data/MODEL/POLICE/police_a02.x",		// 左足前２
	"data/MODEL/POLICE/police_a03.x",		// 左足前３
	"data/MODEL/POLICE/police_a02.x",		// 左足前２
	"data/MODEL/POLICE/police_a01.x",		// 左足前１
	"data/MODEL/POLICE/police_a00.x",		// 直立
	"data/MODEL/POLICE/police_a11.x",		// 右足前１
	"data/MODEL/POLICE/police_a12.x",		// 右足前２
	"data/MODEL/POLICE/police_a13.x",		// 右足前３
	"data/MODEL/POLICE/police_a12.x",		// 右足前２
	"data/MODEL/POLICE/police_a11.x"		// 右足前１

};

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
		for (int nCntPoliceAnim = 0; nCntPoliceAnim < POLICE_ANIM_MAX; nCntPoliceAnim++)
		{
			g_pD3DTexturePolice[nCntPoliceAnim] = NULL;
			g_pD3DXMeshPolice[nCntPoliceAnim] = NULL;
			g_pD3DXBuffMatPolice[nCntPoliceAnim] = NULL;


			// Xファイルの読み込み
			if (FAILED(D3DXLoadMeshFromX(FileNamePolice[nCntPoliceAnim],
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&g_pD3DXBuffMatPolice[nCntPoliceAnim],
				NULL,
				&g_nNumMatPolice[nCntPoliceAnim],
				&g_pD3DXMeshPolice[nCntPoliceAnim])))
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

	// ポリスの初期化処理
	for (int i = 0; i < POLICE_MAX; i++, police++)
	{
		//PANEL *panel = GetPanel(GetPanelNumber(1, 8));
		// ポリスの視点の初期化
		police->Eye = field->Pos;
		// ポリスの注視点の初期化
		police->At = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		// ポリスの上方向の初期化
		police->Up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		// ポリスの向きの初期化
		police->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		// ポリスの移動量の初期化
		police->move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		// ポリスのスケールの初期化
		police->scl = D3DXVECTOR3(0.9f, 0.9f, 0.9f);

		// useフラグをtrueに設定
		police->use = true;

		// ポリスの移動速度初期化
		police->speed = VALUE_MOVE_POLICE;

		// アニメーション番号初期化
		// 最初は直立状態に設定
		police->anim = 0;

		// アニメーションカウント初期化
		animCnt = 0;

		// 更新頻度初期化
		sp_Update = 0;

		// 追尾プレイヤー番号初期化
		key = 0;
		// ランダムで最初に追尾するプレイヤーを選ぶ
		//key = rand() % PLAYER_MAX;

		// シャドウ用
		police->nIdxShadow = 0;
		police->fSizeShadow = 0.0f;
		police->colShadow = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.8f);
		police->bShadow = false;
	}



	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitPolice(void)
{
	for (int nCntPoliceAnim = 0; nCntPoliceAnim < POLICE_ANIM_MAX; nCntPoliceAnim++)
	{
		if (g_pD3DTexturePolice[nCntPoliceAnim] != NULL)
		{// テクスチャの開放
			g_pD3DTexturePolice[nCntPoliceAnim]->Release();
			g_pD3DTexturePolice[nCntPoliceAnim] = NULL;
		}

		if (g_pD3DXMeshPolice[nCntPoliceAnim] != NULL)
		{// メッシュの開放
			g_pD3DXMeshPolice[nCntPoliceAnim]->Release();
			g_pD3DXMeshPolice[nCntPoliceAnim] = NULL;
		}

		if (g_pD3DXBuffMatPolice[nCntPoliceAnim] != NULL)
		{// マテリアルの開放
			g_pD3DXBuffMatPolice[nCntPoliceAnim]->Release();
			g_pD3DXBuffMatPolice[nCntPoliceAnim] = NULL;
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
	//PANEL *panel = GetPanel(0);
	//PLAYER *player = GetPlayer(0);

	// アニメーション
	SetPoliceAnimation(POLICE_ANIM_SEC);


	// ボタンで追尾対象切り替える
#ifdef _DEBUG
	if (GetKeyboardTrigger(DIK_1))
	{
		key = 0;
	}
	if (GetKeyboardTrigger(DIK_2))
	{
		key = 1;
	}
#endif


	// ゲージの少ないほうを追尾
	//if (player[0].item < player[1].item)
	//{	// 1Pのほうがゲージが少ない場合

	//	// 1Pを追尾
	//	key = 0;
	//}
	//if (player[0].item > player[1].item)
	//{	// 2Pのほうがゲージが少ない場合

	//	// 2Pを追尾
	//	key = 1;
	//}
	// 追尾をセット
	SetPoliceHoming(key, POLICE_SPEED_FREQUENCY, POLICE_SPEEDUP);


	// デバッグ時に手動でポリス移動
#ifdef _DEBUG
	if (GetKeyboardPress(DIK_LEFT))
	{
		if (GetKeyboardPress(DIK_UP))
		{// 左前移動
			police->move.x -= cosf(camera->rotCamera.y + D3DX_PI * 0.25f) * VALUE_MOVE_POLICE;
			police->move.z += sinf(camera->rotCamera.y + D3DX_PI * 0.25f) * VALUE_MOVE_POLICE;
		}
		else if (GetKeyboardPress(DIK_DOWN))
		{// 左後移動
			police->move.x -= cosf(camera->rotCamera.y - D3DX_PI * 0.25f) * VALUE_MOVE_POLICE;
			police->move.z += sinf(camera->rotCamera.y - D3DX_PI * 0.25f) * VALUE_MOVE_POLICE;
		}
		else
		{// 左移動
			police->move.x -= cosf(camera->rotCamera.y) * VALUE_MOVE_POLICE;
			police->move.z += sinf(camera->rotCamera.y) * VALUE_MOVE_POLICE;
		}
	}
	else if (GetKeyboardPress(DIK_RIGHT))
	{
		if (GetKeyboardPress(DIK_UP))
		{// 右前移動
			police->move.x += cosf(camera->rotCamera.y - D3DX_PI * 0.25f) * VALUE_MOVE_POLICE;
			police->move.z -= sinf(camera->rotCamera.y - D3DX_PI * 0.25f) * VALUE_MOVE_POLICE;
		}
		else if (GetKeyboardPress(DIK_DOWN))
		{// 右後移動
			police->move.x += cosf(camera->rotCamera.y + D3DX_PI * 0.25f) * VALUE_MOVE_POLICE;
			police->move.z -= sinf(camera->rotCamera.y + D3DX_PI * 0.25f) * VALUE_MOVE_POLICE;
		}
		else
		{// 右移動
			police->move.x += cosf(camera->rotCamera.y) * VALUE_MOVE_POLICE;
			police->move.z -= sinf(camera->rotCamera.y) * VALUE_MOVE_POLICE;
		}
	}
	else if (GetKeyboardPress(DIK_UP))
	{// 前移動
		police->move.x += sinf(camera->rotCamera.y) * VALUE_MOVE_POLICE;
		police->move.z += cosf(camera->rotCamera.y) * VALUE_MOVE_POLICE;
	}
	else if (GetKeyboardPress(DIK_DOWN))
	{// 後移動
		police->move.x -= sinf(camera->rotCamera.y) * VALUE_MOVE_POLICE;
		police->move.z -= cosf(camera->rotCamera.y) * VALUE_MOVE_POLICE;
	}




#endif

	// ポリス移動処理

	// 移動量に慣性をかける
	police->move.x += (0.0f - police->move.x) * RATE_MOVE_POLICE;
	police->move.y += (0.0f - police->move.y) * RATE_MOVE_POLICE;
	police->move.z += (0.0f - police->move.z) * RATE_MOVE_POLICE;

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


	police = &policeWk[0];
#ifdef _DEBUG
	PrintDebugProc("[ポリスの位置  ：(%f : %f : %f)]\n", police->Eye.x, police->Eye.y, police->Eye.z);
	//PrintDebugProc("\n");
#endif

	// シャドウ
	//if (!police->bShadow)
	//{	// シャドウ設置
	//	police->nIdxShadow = CreateShadow(police->Eye, 25.0f, 25.0f);
	//	police->fSizeShadow = POLICE_SHADOW_SIZE;
	//	police->colShadow = D3DXCOLOR(0.7f, 0.7f, 0.7f, 0.7f);
	//	police->bShadow = true;
	//}
	//else
	//{
	//	// シャドウ管理
	//	SetPositionShadow(police->nIdxShadow, D3DXVECTOR3(police->Eye.x, 0.2f, police->Eye.z));
	//	SetVertexShadow(police->nIdxShadow, police->fSizeShadow, police->fSizeShadow);
	//	SetColorShadow(police->nIdxShadow, police->colShadow);
	//}
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

			//// 移動を反映
			D3DXMatrixTranslation(&mtxTranslate, police->Eye.x, police->Eye.y, police->Eye.z);
			D3DXMatrixMultiply(&g_mtxWorldPolice, &g_mtxWorldPolice, &mtxTranslate);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldPolice);

			// 現在のマテリアルを取得
			pDevice->GetMaterial(&matDef);

			// マテリアル情報に対するポインタを取得
			// 今は直立を設定してる０
			pD3DXMat = (D3DXMATERIAL*)g_pD3DXBuffMatPolice[police->anim]->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_nNumMatPolice[police->anim]; nCntMat++)
			{
				// マテリアルの設定
				pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);

				// テクスチャの設定
				pDevice->SetTexture(0, g_pD3DTexturePolice[police->anim]);

				// 描画
				g_pD3DXMeshPolice[police->anim]->DrawSubset(nCntMat);

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
	D = *pAt - *pEye;
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
// ポリスアニメーション設定関数
// 引数：アニメーション一巡にかかる秒数）
//=============================================================================
void SetPoliceAnimation(int sec)
{
	POLICE *police = &policeWk[0];

	// アニメーションカウント
	animCnt++;

	// 秒数の絶対値を求める
	sec = abs(sec);

	// アニメーションを切り替えるフレーム数を求める
	sec = (60 * sec) / POLICE_ANIM_MAX;

	if (animCnt % sec == 0)
	{	// アニメーションを切り替える
		police->anim++;
		if (police->anim >= POLICE_ANIM_MAX)
		{	// 一巡したら最初に戻す
			police->anim = 0;
		}
	}

}
//=============================================================================
// ポリス追尾設定関数
// 引数１：追尾したいプレイヤー番号
// 引数２：移動速度の更新頻度（とりまフレーム数渡す）
// 引数３：更新一回当たりの移動速度の変化量
//=============================================================================
void SetPoliceHoming(int no, int frequency, float speedup)
{
	POLICE *police = &policeWk[0];

	// 移動速度更新頻度カウント
	sp_Update++;

	// 追尾対象にポリスの注視点をセット
	//police->At = GetPosPlayer(no);

	// 追尾対象への移動ベクトルを求める
	//police->move = GetPosPlayer(no) - police->Eye;

	// 移動ベクトルを正規化
	D3DXVec3Normalize(&police->move, &police->move);

	// ポリスの速度調整

	// 速度を一定間隔で更新
	if (sp_Update % frequency == 0)
	{	// 速度up
		police->speed += speedup;
		// 移動速度更新頻度カウントをゼロに戻す
		sp_Update = 0;
	}

	// 速度設定
	police->move *= police->speed;

}