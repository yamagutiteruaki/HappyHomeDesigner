//=============================================================================
//
// タイマー処理 [weight.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "weight.h"
#include "input.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexWeight(LPDIRECT3DDEVICE9 pDevice); 

void SetVertexWeight(void);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureWeight = NULL;		// テクスチャへのポリゴン
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffWeight = NULL;		// 頂点バッファインターフェースへのポインタ

LPDIRECT3DTEXTURE9		g_pD3DTextureWeightMeter = NULL;		// テクスチャへのポリゴン
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffWeightMeter = NULL;		// 頂点バッファインターフェースへのポインタ

//bool			use;						// true:使用  false:未使用
D3DXVECTOR3		pos;						// ポリゴンの移動量
D3DXVECTOR3		rot;						// ポリゴンの回転量

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitWeight(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//use = true;										// 使用
	pos = D3DXVECTOR3(TEXTURE_WEIGHT_SIZE_X, TEXTURE_WEIGHT_SIZE_Y, 0.0f);			// 座標データを初期化
	rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// 回転データを初期化

	MakeVertexWeight(pDevice);										// 頂点情報の作成

										// テクスチャーの初期化を行う
		// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,	// デバイスのポインタ
		TEXTURE_WEIGHT,				// ファイルの名前
		&g_pD3DTextureWeight);			// 読み込むメモリのポインタ

											// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,	// デバイスのポインタ
		TEXTURE_WEIGHT2,				// ファイルの名前
		&g_pD3DTextureWeightMeter);			// 読み込むメモリのポインタ



	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitWeight(void)
{
	if (g_pD3DTextureWeight != NULL)
	{	// テクスチャの開放
		g_pD3DTextureWeight->Release();
		g_pD3DTextureWeight = NULL;
	}

	if (g_pD3DVtxBuffWeight != NULL)
	{// 頂点バッファの開放
		g_pD3DVtxBuffWeight->Release();
		g_pD3DVtxBuffWeight = NULL;
	}

	if (g_pD3DTextureWeightMeter != NULL)
	{	// テクスチャの開放
		g_pD3DTextureWeightMeter->Release();
		g_pD3DTextureWeightMeter = NULL;
	}

	if (g_pD3DVtxBuffWeightMeter != NULL)
	{// 頂点バッファの開放
		g_pD3DVtxBuffWeightMeter->Release();
		g_pD3DVtxBuffWeightMeter = NULL;
	}

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateWeight(void)
{


}

//=============================================================================
// 描画処理
//=============================================================================
void DrawWeight(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

			// 頂点バッファをデバイスのデータストリームにバインド
			pDevice->SetStreamSource(0, g_pD3DVtxBuffWeight, 0, sizeof(VERTEX_2D));

			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_2D);

			// テクスチャの設定
			pDevice->SetTexture(0, g_pD3DTextureWeight);

			// ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_WEIGHT);


		//メーター
			// 頂点バッファをデバイスのデータストリームにバインド
			pDevice->SetStreamSource(0, g_pD3DVtxBuffWeightMeter, 0, sizeof(VERTEX_2D));

			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_2D);

			// テクスチャの設定
			pDevice->SetTexture(0, g_pD3DTextureWeightMeter);

			// ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,0, NUM_WEIGHT);

}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexWeight(LPDIRECT3DDEVICE9 pDevice)
{

	// オブジェクトの頂点バッファを生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,	// 頂点データ用に確保するバッファサイズ(バイト単位)
		D3DUSAGE_WRITEONLY,			// 頂点バッファの使用法　
		FVF_VERTEX_2D,				// 使用する頂点フォーマット
		D3DPOOL_MANAGED,			// リソースのバッファを保持するメモリクラスを指定
		&g_pD3DVtxBuffWeight,		// 頂点バッファインターフェースへのポインタ
		NULL)))						// NULLに設定
	{
		return E_FAIL;
	}

	{//頂点バッファの中身を埋める
		VERTEX_2D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffWeight->Lock(0, 0, (void**)&pVtx, 0);

		// 頂点座標の設定
		pVtx[0].vtx = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(TEXTURE_WEIGHT_SIZE_X, 0.0f, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(0.0f, TEXTURE_WEIGHT_SIZE_Y, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(TEXTURE_WEIGHT_SIZE_X, TEXTURE_WEIGHT_SIZE_Y, 0.0f);

		// テクスチャのパースペクティブコレクト用
		pVtx[0].rhw =
			pVtx[1].rhw =
			pVtx[2].rhw =
			pVtx[3].rhw = 1.0f;

		// 反射光の設定
		pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		// 頂点データをアンロックする
		g_pD3DVtxBuffWeight->Unlock();
	}


	return S_OK;

}

//=============================================================================
// 頂点の作成
//=============================================================================
void SetVertexWeight(void)
{
	{//頂点バッファの中身を埋める
		VERTEX_2D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffWeight->Lock(0, 0, (void**)&pVtx, 0);

		// 反射光の設定
		pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);



		// 頂点データをアンロックする
		g_pD3DVtxBuffWeight->Unlock();
	}

}
