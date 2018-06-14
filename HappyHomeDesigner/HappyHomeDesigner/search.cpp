//=============================================================================
//
// 索敵範囲描画処理 [search.cpp]
// Author : GP12A295-19-千坂浩太
//
//=============================================================================
#include "search.h"
#include "camera.h"
#include "debugproc.h"
#include "input.h"
#include "player.h"
#include "police.h"
#include "stage.h"
#include "field.h"
#include "collision.h"
#include "calculate.h"
#include "voice.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexSearch(void);
void SetSearchParts(void);
void SearchMove(void);
void SearchRotation(void);
void SearchCollision(void);
//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureSearch = NULL;	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffSearch = NULL;	// 頂点バッファへのポインタ
D3DXMATRIX				g_mtxWorldSearch;			// ワールドマトリックス
SEARCH					searchWk[SEARCH_MAX];		// サーチ格納ワーク
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitSearch(int nType)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	SEARCH *search = &searchWk[0];

	if (nType == STAGE_INIT_FAST)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,					// デバイスへのポインタ
			TEXTURE_SEARCH,			// ファイルの名前
			&g_pD3DTextureSearch);	// 読み込むメモリー
	}

	for (int i = 0; i < SEARCH_MAX; i++, search++)
	{
		// 位置、向きの初期設定
		search->Eye = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		search->rotBasis = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		search->scl = D3DXVECTOR3(1.0f * 1, 1.0f * 1, 1.0f * 1);
		search->axisY = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		search->use = false;

		// 親子関係識別番号の初期設定(未使用:0番,使用：本体と同じ番号)
		search->num = 0;

		search->cos = 0.0f;
		search->sita = 0.0f;

	}
	// 親子関係の設定
	SetSearchParts();
	return S_OK;
}
//=============================================================================
// 終了処理
//=============================================================================
void UninitSearch(void)
{
	if (g_pD3DTextureSearch != NULL)
	{// テクスチャの開放
		g_pD3DTextureSearch->Release();
		g_pD3DTextureSearch = NULL;
	}
	if (g_pD3DVtxBuffSearch != NULL)
	{// 頂点バッファの開放
		g_pD3DVtxBuffSearch->Release();
		g_pD3DVtxBuffSearch = NULL;
	}
}
//=============================================================================
// 更新処理
//=============================================================================
void UpdateSearch(void)
{
	// 索敵範囲の移動
	SearchMove();
	// 索敵範囲の回転
	SearchRotation();
	// 索敵処理
	SearchCollision();
	// 頂点の作成
	MakeVertexSearch();
}
//=============================================================================
// 描画処理
//=============================================================================
void DrawSearch(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	SEARCH *search = &searchWk[0];

	for (int i = 0; i < SEARCH_MAX; i++, search++)
	{
		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_mtxWorldSearch);
		// ワールドマトリックス作成
		D3DXMatrixTransformation(&g_mtxWorldSearch, NULL, NULL, &search->scl, &search->rotBasis, &search->qRotateY, &search->Eye);
		// ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldSearch);
		// 頂点バッファをデバイスのデータストリームにバインド
		pDevice->SetStreamSource(0, g_pD3DVtxBuffSearch, 0, sizeof(VERTEX_3D));
		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_3D);
		// テクスチャの設定
		pDevice->SetTexture(0, g_pD3DTextureSearch);
		// ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
	}
}
//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexSearch(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// オブジェクトの頂点バッファを生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX,	// 頂点データ用に確保するバッファサイズ(バイト単位)
		D3DUSAGE_WRITEONLY,			// 頂点バッファの使用法　
		FVF_VERTEX_3D,				// 使用する頂点フォーマット
		D3DPOOL_MANAGED,			// リソースのバッファを保持するメモリクラスを指定
		&g_pD3DVtxBuffSearch,		// 頂点バッファインターフェースへのポインタ
		NULL)))						// NULLに設定
	{
		return E_FAIL;
	}

	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffSearch->Lock(0, 0, (void**)&pVtx, 0);

		// 頂点座標の設定
		pVtx[0].vtx = D3DXVECTOR3(-7.0f, 0.0f, -10.0f);
		pVtx[1].vtx = D3DXVECTOR3(7.0f, 0.0f, -10.0f);
		pVtx[2].vtx = D3DXVECTOR3(-(SEARCH_LENGTH * sinf(SEARCH_ANGLE / 2.0f)), 0.0f, -SEARCH_LENGTH);		// ANGLEとLENGTH
		pVtx[3].vtx = D3DXVECTOR3(SEARCH_LENGTH * sinf(SEARCH_ANGLE / 2.0f), 0.0f, -SEARCH_LENGTH);			// によって自動的に形変わる

																											// 法線ベクトルの設定
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		// 反射光の設定
		pVtx[0].diffuse =
			pVtx[1].diffuse =
			pVtx[2].diffuse =
			pVtx[3].diffuse = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.3f);

		// テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		// 頂点データをアンロックする
		g_pD3DVtxBuffSearch->Unlock();
	}
	return S_OK;
}
//=============================================================================
// 索敵範囲親子関係設定関数
//=============================================================================
void SetSearchParts(void)
{
	POLICE *police = GetPolice(0);
	SEARCH *search = &searchWk[0];

	// 本体に索敵範囲を関連付ける
	for (int i = 0; i < POLICE_MAX; i++, police++)
	{	// 使用状態のポリスにのみ索敵範囲をセット
		if (!police->use) continue;
		// 未使用の索敵範囲をセット
		search = &searchWk[0];
		for (int j = 0; j < SEARCH_MAX; j++, search++)
		{	// 未使用のチェック
			if (search->use) continue;
			// 本体と同じ番号をセット
			search->num = police->num;
			// 使用状態にする
			search->use = true;
			break;
		}
	}
}
//=============================================================================
// 索敵範囲の移動関数
//=============================================================================
void SearchMove(void)
{
	POLICE *police = GetPolice(0);
	SEARCH *search = &searchWk[0];

	// 本体と親子関係の索敵範囲を移動
	for (int i = 0; i < POLICE_MAX; i++, police++)
	{
		// 索敵範囲の移動
		search = &searchWk[0];
		for (int j = 0; j < SEARCH_MAX; j++, search++)
		{
			if (!search->use) continue;
			if (search->num == police->num)
			{	// 本体の座標のほんの少し上にセット
				search->Eye.x = police->Eye.x;
				search->Eye.y = police->Eye.y + 0.1f;
				search->Eye.z = police->Eye.z;
				// 本体と同じ注視点を向くためのY軸回転角度をセット
				search->fangleY = police->fangleY;
				// 本体と同じ進行ベクトルを取得
				search->move = police->move;
				break;
			}
		}
	}
}
//=============================================================================
// 索敵範囲の回転関数
//=============================================================================
void SearchRotation(void)
{
	SEARCH *search = &searchWk[0];

	// 回転クォータニオンを生成
	for (int i = 0; i < SEARCH_MAX; i++, search++)
	{	// Y軸回転(ポリスと同じ方向に向かせる)
		D3DXQuaternionRotationAxis(&search->qRotateY, &search->axisY, search->fangleY);
	}
}
//=============================================================================
// 索敵処理関数
//=============================================================================
void SearchCollision(void)
{
	SEARCH *search = &searchWk[0];
	PLAYER *player = GetPlayer(0);
	VOICE *voice = GetVoice(0);
	POLICE *police = GetPolice(0);

	// 視野内外判定
	for (int i = 0; i < PLAYER_MAX; i++, player++)
	{	// 使用状態のプレイヤーのみ判定
		if (!player->use) continue;
		// ポインタ初期化
		search = &searchWk[0];
		for (int j = 0; j < SEARCH_MAX; j++, search++)
		{	// 使用状態の索敵範囲のみ判定
			if (!search->use) continue;
			// ポリスの進行ベクトル(正面のベクトル)を取得
			D3DXVECTOR3 vecA = search->move;
			// ポリスからプレイヤーへのベクトルを求める
			D3DXVECTOR3 vecB = (player->Eye - search->Eye);
			// それぞれのベクトルの長さを求める
			float lenA = D3DXVec3Length(&vecA);
			float lenB = D3DXVec3Length(&vecB);
			// 距離的に範囲内の可能性があるかを判定
			if (!(lenB < SEARCH_LENGTH)) continue;
			// 内積とベクトルの長さからcosを求める
			search->cos = D3DXVec3Dot(&vecA, &vecB) / (lenA*lenB);
			// プレイヤーとポリスの前後の位置関係をチェック(プレイヤーがポリスの後ろなら後の処理スキップ)
			if (search->cos < 0) continue;
			// cosから進行ベクトルとプレイヤーへのベクトルのなす角を求める
			search->sita = acosf(search->cos);
			// なす角がポリス索敵視野角の二分の一以下なら視野内にいる
			if (search->sita < (SEARCH_ANGLE / 2.0f))
			{	// 視野内にプレイヤーがいた場合の処理
				// プレイヤーを消す
				//player->use = false;
				// 松尾君のアレ描画
				voice->use = true;

				// ポリスの動きを止める
				police = GetPolice(0);
				for (int k = 0; k < POLICE_MAX; k++, police++)
				{	// ポリスの移動フラグをfalseに
					//police->movef = false;
				}
			}
		}
	}
}