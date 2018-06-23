//=============================================================================
//
// リザルト画面処理 [resultlogo.cpp]
// Author : GP12B295 ⑫ 関口昂平
//
//=============================================================================
#include "resultlogo.h"
#include "input.h"
#include "fade.h"
#include "debugproc.h"
#include "stage.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexResultLogo(LPDIRECT3DDEVICE9 pDevice);
void SetVertexTexture(void);


//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureResult = NULL;			// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffResult = NULL;			// 頂点バッファインターフェースへのポインタ
LPDIRECT3DTEXTURE9		g_pD3DTextureResultLogo2 = NULL;	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffResultLogo2 = NULL;	// 頂点バッファインターフェースへのポインタ
//LPDIRECT3DTEXTURE9		g_pD3DTextureResultClear = NULL;	// テクスチャへのポインタ
//LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffResultClear = NULL;	// 頂点バッファインターフェースへのポインタ
LPDIRECT3DTEXTURE9		g_pD3DTextureResultGameOver = NULL;	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffResultGameOver = NULL;	// 頂点バッファインターフェースへのポインタ

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitResultLogo(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点情報の作成
	MakeVertexResultLogo(pDevice);

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,			// デバイスへのポインタ
		TEXTURE_RESULT,							// ファイルの名前
		&g_pD3DTextureResult);					// 読み込むメモリー

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,			// デバイスへのポインタ
		TEXTURE_RESULT_LOGO2,					// ファイルの名前
		&g_pD3DTextureResultLogo2);				// 読み込むメモリー

												// テクスチャの読み込み
	//D3DXCreateTextureFromFile(pDevice,			// デバイスへのポインタ
	//	TEXTURE_RESULT_CLEAR,					// ファイルの名前
	//	&g_pD3DTextureResultClear);				// 読み込むメモリー

												// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,			// デバイスへのポインタ
		TEXTURE_RESULT_CLEAR,					// ファイルの名前
		&g_pD3DTextureResultGameOver);				// 読み込むメモリー


	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitResultLogo(void)
{
	if (g_pD3DTextureResult != NULL)
	{	// テクスチャの開放
		g_pD3DTextureResult->Release();
		g_pD3DTextureResult = NULL;
	}

	if (g_pD3DVtxBuffResult != NULL)
	{	// 頂点バッファの開放
		g_pD3DVtxBuffResult->Release();
		g_pD3DVtxBuffResult = NULL;
	}

	if (g_pD3DTextureResultLogo2 != NULL)
	{	// テクスチャの開放
		g_pD3DTextureResultLogo2->Release();
		g_pD3DTextureResultLogo2 = NULL;
	}

	if (g_pD3DVtxBuffResultLogo2 != NULL)
	{	// 頂点バッファの開放
		g_pD3DVtxBuffResultLogo2->Release();
		g_pD3DVtxBuffResultLogo2 = NULL;
	}

	//if (g_pD3DTextureResultClear != NULL)
	//{	// テクスチャの開放
	//	g_pD3DTextureResultClear->Release();
	//	g_pD3DTextureResultClear = NULL;
	//}

	//if (g_pD3DVtxBuffResultClear != NULL)
	//{	// 頂点バッファの開放
	//	g_pD3DVtxBuffResultClear->Release();
	//	g_pD3DVtxBuffResultClear = NULL;
	//}

	if (g_pD3DTextureResultGameOver != NULL)
	{	// テクスチャの開放
		g_pD3DTextureResultGameOver->Release();
		g_pD3DTextureResultGameOver = NULL;
	}

	if (g_pD3DVtxBuffResultGameOver != NULL)
	{	// 頂点バッファの開放
		g_pD3DVtxBuffResultGameOver->Release();
		g_pD3DVtxBuffResultGameOver = NULL;
	}

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateResultLogo(void)
{

	PrintDebugProc("[クリア状況  ：(%d)]\n", GetGameEnd());
	SetVertexTexture();

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawResultLogo(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, g_pD3DVtxBuffResult, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pD3DTextureResult);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);


	//// 頂点バッファをデバイスのデータストリームにバインド
	//pDevice->SetStreamSource(0, g_pD3DVtxBuffResultClear, 0, sizeof(VERTEX_2D));

	//// 頂点フォーマットの設定
	//pDevice->SetFVF(FVF_VERTEX_2D);

	//// テクスチャの設定
	//pDevice->SetTexture(0, g_pD3DTextureResultClear);

	//// ポリゴンの描画
	//pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);



	// 頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, g_pD3DVtxBuffResultGameOver, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pD3DTextureResultGameOver);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);


	// 頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, g_pD3DVtxBuffResultLogo2, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pD3DTextureResultLogo2);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexResultLogo(LPDIRECT3DDEVICE9 pDevice)
{
	// オブジェクトの頂点バッファを生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,	// 頂点データ用に確保するバッファサイズ(バイト単位)
		D3DUSAGE_WRITEONLY,			// 頂点バッファの使用法　
		FVF_VERTEX_2D,				// 使用する頂点フォーマット
		D3DPOOL_MANAGED,			// リソースのバッファを保持するメモリクラスを指定
		&g_pD3DVtxBuffResult,		// 頂点バッファインターフェースへのポインタ
		NULL)))						// NULLに設定
	{
		return E_FAIL;
	}

	{//頂点バッファの中身を埋める
		VERTEX_2D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffResult->Lock(0, 0, (void**)&pVtx, 0);

		// 頂点座標の設定
		pVtx[0].vtx = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

		// テクスチャのパースペクティブコレクト用
		pVtx[0].rhw =
		pVtx[1].rhw =
		pVtx[2].rhw =
		pVtx[3].rhw = 1.0f;

		// 反射光の設定
		pVtx[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

		// テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		// 頂点データをアンロックする
		g_pD3DVtxBuffResult->Unlock();
	}


	// オブジェクトの頂点バッファを生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,	// 頂点データ用に確保するバッファサイズ(バイト単位)
		D3DUSAGE_WRITEONLY,			// 頂点バッファの使用法　
		FVF_VERTEX_2D,				// 使用する頂点フォーマット
		D3DPOOL_MANAGED,			// リソースのバッファを保持するメモリクラスを指定
		&g_pD3DVtxBuffResultGameOver,	// 頂点バッファインターフェースへのポインタ
		NULL)))						// NULLに設定
	{
		return E_FAIL;
	}

	{//頂点バッファの中身を埋める
		VERTEX_2D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffResultGameOver->Lock(0, 0, (void**)&pVtx, 0);

		// 頂点座標の設定
		pVtx[0].vtx = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(850, 0.0f, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(0.0f, 240, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(850, 240, 0.0f);

		// テクスチャのパースペクティブコレクト用
		pVtx[0].rhw =
			pVtx[1].rhw =
			pVtx[2].rhw =
			pVtx[3].rhw = 1.0f;

		// 反射光の設定
		pVtx[0].diffuse = 
		pVtx[1].diffuse = 
		pVtx[2].diffuse = 
		pVtx[3].diffuse = D3DXCOLOR(0.0f, 0.9f, 0.9f, 1.0f);

		// テクスチャ座標の設定
		//pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		//pVtx[1].tex = D3DXVECTOR2(0.5f, 0.0f);
		//pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		//pVtx[3].tex = D3DXVECTOR2(0.5f, 1.0f);
		SetVertexTexture();

		// 頂点データをアンロックする
		g_pD3DVtxBuffResultGameOver->Unlock();
	}

	// オブジェクトの頂点バッファを生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,	// 頂点データ用に確保するバッファサイズ(バイト単位)
		D3DUSAGE_WRITEONLY,			// 頂点バッファの使用法　
		FVF_VERTEX_2D,				// 使用する頂点フォーマット
		D3DPOOL_MANAGED,			// リソースのバッファを保持するメモリクラスを指定
		&g_pD3DVtxBuffResultLogo2,	// 頂点バッファインターフェースへのポインタ
		NULL)))						// NULLに設定
	{
		return E_FAIL;
	}

	{//頂点バッファの中身を埋める
		VERTEX_2D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffResultLogo2->Lock(0, 0, (void**)&pVtx, 0);

		// 頂点座標の設定
		pVtx[0].vtx = D3DXVECTOR3(0.0f, RESULT_LOGO2_HEIGHT / 2, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(RESULT_LOGO2_WIDTH, RESULT_LOGO2_HEIGHT / 2, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(0.0f, RESULT_LOGO2_HEIGHT, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(RESULT_LOGO2_WIDTH, RESULT_LOGO2_HEIGHT, 0.0f);

		// テクスチャのパースペクティブコレクト用
		pVtx[0].rhw =
			pVtx[1].rhw =
			pVtx[2].rhw =
			pVtx[3].rhw = 1.0f;

		// 反射光の設定
		pVtx[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

		// テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		// 頂点データをアンロックする
		g_pD3DVtxBuffResultLogo2->Unlock();
	}

	return S_OK;
}
	
void SetVertexTexture(void)
{
	int Texptern=GetGameEnd();


	{//頂点バッファの中身を埋める
		VERTEX_2D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffResultGameOver->Lock(0, 0, (void**)&pVtx, 0);

		pVtx[0].tex = D3DXVECTOR2(Texptern*0.5f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(Texptern*0.5f + 0.5f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(Texptern*0.5f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(Texptern*0.5f + 0.5f, 1.0f);



		// 頂点データをアンロックする
		g_pD3DVtxBuffResultGameOver->Unlock();
	}
}