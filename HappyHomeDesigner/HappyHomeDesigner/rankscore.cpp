//=============================================================================
//
// スコア処理 [rankscore.cpp]
// Author : 
//
//=============================================================================
#include "rankscore.h"
#include "stage.h"
#include "calculate.h"
#include "debugproc.h"
#include "input.h"
#include "ranking.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexRankscore(LPDIRECT3DDEVICE9 pDevice);
void SetTextureRankscore(int idx, int number);

//*****************************************************************************
// グローバル変数宣言
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureRankscore = {NULL};	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffRankscore = NULL;		// 頂点バッファインターフェースへのポインタ

RANKSCORE			rankscoreWk[RANKSCORE_MAX];


//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitRankscore(int nType)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	RANKSCORE *rankscore = &rankscoreWk[0];

	if (nType == STAGE_INIT_FAST)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,					// デバイスへのポインタ
			TEXTURE_RANKSCORE,			// ファイルの名前
			&g_pD3DTextureRankscore);	// 読み込むメモリー
	}

	for (int i = 0; i < RANKSCORE_MAX; i++, rankscore++)
	{
		// スコアの初期化
		rankscore->rankscore = 0;
		rankscore->maxrankscore = 0;

		switch (i)
		{
		case 0:
			rankscore->pos = D3DXVECTOR3(500.0f, 280.0f, 0.0f);
			break;
		case 1:
			rankscore->pos = D3DXVECTOR3(90.0f, 520.0f, 0.0f);
			break;

		case 2:
			rankscore->pos = D3DXVECTOR3(930.0f, 520.0f, 0.0f);
			break;
		}
	}


	// 頂点情報の作成
	MakeVertexRankscore(pDevice);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitRankscore(void)
{
	RANKSCORE *rankscore = &rankscoreWk[0];

	for (int i = 0; i < RANKSCORE_MAX; i++, rankscore++)
	{
		if (g_pD3DTextureRankscore != NULL)
		{// テクスチャの開放
			g_pD3DTextureRankscore->Release();
			g_pD3DTextureRankscore = NULL;
		}

		if (g_pD3DVtxBuffRankscore != NULL)
		{// 頂点バッファの開放
			g_pD3DVtxBuffRankscore->Release();
			g_pD3DVtxBuffRankscore = NULL;
		}
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateRankscore(void)
{
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawRankscore(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	RANKSCORE *rankscore = &rankscoreWk[0];


	for (int i = 0; i < RANKSCORE_MAX; i++, rankscore++)
	{
		// 頂点バッファをデバイスのデータストリームにバインド
		pDevice->SetStreamSource(0, g_pD3DVtxBuffRankscore, 0, sizeof(VERTEX_2D));

		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);


		// テクスチャの設定
		pDevice->SetTexture(0, g_pD3DTextureRankscore);

		// ポリゴンの描画
		for (int nCntPlace = 0; nCntPlace < NUM_PLACE; nCntPlace++)
		{
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, (nCntPlace * 4+(i*4* NUM_PLACE)), NUM_POLYGON);
		}

		// テクスチャの設定
		pDevice->SetTexture(0, g_pD3DTextureRankscore);

		// ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, NUM_PLACE*4 * RANKSCORE_MAX, NUM_POLYGON);
	}
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexRankscore(LPDIRECT3DDEVICE9 pDevice)
{
	// オブジェクトの頂点バッファを生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * (NUM_VERTEX * NUM_PLACE*RANKSCORE_MAX ),	// 頂点データ用に確保するバッファサイズ(バイト単位)
		D3DUSAGE_WRITEONLY,								// 頂点バッファの使用法　
		FVF_VERTEX_2D,									// 使用する頂点フォーマット
		D3DPOOL_MANAGED,								// リソースのバッファを保持するメモリクラスを指定
		&g_pD3DVtxBuffRankscore,							// 頂点バッファインターフェースへのポインタ
		NULL)))											// NULLに設定
	{
		return E_FAIL;
	}

	{//頂点バッファの中身を埋める
		VERTEX_2D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffRankscore->Lock(0, 0, (void**)&pVtx, 0);

		for (int i = 0; i < RANKSCORE_MAX; i++)
		{
			RANKSCORE *ras = &rankscoreWk[i];
			for (int nCntPlace = 0; nCntPlace < NUM_PLACE; nCntPlace++, pVtx += 4)
			{
				// 頂点座標の設定
				pVtx[0].vtx = D3DXVECTOR3(ras->pos.x + nCntPlace * RANKSCORE_SIZE_X + RANKSCORE_INTERVAL_X, ras->pos.y, 0.0f);
				pVtx[1].vtx = D3DXVECTOR3(ras->pos.x + nCntPlace * (RANKSCORE_INTERVAL_X + RANKSCORE_SIZE_X) + RANKSCORE_SIZE_X, ras->pos.y, 0.0f);
				pVtx[2].vtx = D3DXVECTOR3(ras->pos.x + nCntPlace * RANKSCORE_SIZE_X + RANKSCORE_INTERVAL_X, ras->pos.y + RANKSCORE_SIZE_Y, 0.0f);
				pVtx[3].vtx = D3DXVECTOR3(ras->pos.x + nCntPlace * (RANKSCORE_INTERVAL_X + RANKSCORE_SIZE_X) + RANKSCORE_SIZE_X, ras->pos.y + RANKSCORE_SIZE_Y, 0.0f);

				// rhwの設定
				pVtx[0].rhw =
					pVtx[1].rhw =
					pVtx[2].rhw =
					pVtx[3].rhw = 1.0f;

				// 反射光の設定
				pVtx[0].diffuse =
					pVtx[1].diffuse =
					pVtx[2].diffuse =
					pVtx[3].diffuse = SetColorPallet(COLOR_PALLET_BROWN);

				// テクスチャ座標の設定
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);
			}
		}

		// 頂点データをアンロックする
		g_pD3DVtxBuffRankscore->Unlock();
	}

	return S_OK;
}

//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTextureRankscore(int idx, int number)
{
	VERTEX_2D *pVtx;

	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	g_pD3DVtxBuffRankscore->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += (idx * 4);

	// 頂点座標の設定
	pVtx[0].tex = D3DXVECTOR2(number * 0.1f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(number * 0.1f + 0.1f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(number * 0.1f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(number * 0.1f + 0.1f, 1.0f);

	// 頂点データをアンロックする
	g_pD3DVtxBuffRankscore->Unlock();
}
