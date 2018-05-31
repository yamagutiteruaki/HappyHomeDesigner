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
void SetTextureScore(void);
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

LPDIRECT3DTEXTURE9		g_pD3DTextureScore = NULL;		// テクスチャへのポリゴン
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffResultScore = NULL;	// 頂点バッファインターフェースへのポインタ
VERTEX_2D				g_vertexWkScore[SCORE_DIGIT][NUM_VERTEX];	// 頂点情報格納ワーク

D3DXVECTOR3				g_posScore;						// ポリゴンの移動量

int						g_nScore;						// スコア

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
		TEXTURE_RESULT_GAMEOVER,					// ファイルの名前
		&g_pD3DTextureResultGameOver);				// 読み込むメモリー


	D3DXCreateTextureFromFile(pDevice,		// デバイスのポインタ
		TEXTURE_GAME_SCORE00,				// ファイルの名前
		&g_pD3DTextureScore);				// 読み込むメモリのポインタ

	g_posScore = D3DXVECTOR3((float)SCORE_POS_X, (float)SCORE_POS_Y, 0.0f);
	g_nScore = 0;


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


	if (g_pD3DTextureScore != NULL)
	{	// テクスチャの開放
		g_pD3DTextureScore->Release();
		g_pD3DTextureScore = NULL;
	}

	if (g_pD3DVtxBuffResultScore != NULL)
	{	// 頂点バッファの開放
		g_pD3DVtxBuffResultScore->Release();
		g_pD3DVtxBuffResultScore = NULL;
	}

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateResultLogo(void)
{

	PrintDebugProc("[クリア状況  ：(%d)]\n", GetGameEnd());

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawResultLogo(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int i;

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



	// テクスチャの設定
	pDevice->SetTexture(0, g_pD3DTextureScore);

	// スコア
	for (i = 0; i < SCORE_DIGIT; i++)
	{
		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		// ポリゴンの描画
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkScore[i], sizeof(VERTEX_2D));
	}

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
		pVtx[1].vtx = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(0.0f, SCREEN_HEIGHT/2, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT/2, 0.0f);

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

	int i;
	float habaX = 16.0f;	// 数字の横幅

							// オブジェクトの頂点バッファを生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,	// 頂点データ用に確保するバッファサイズ(バイト単位)
		D3DUSAGE_WRITEONLY,			// 頂点バッファの使用法　
		FVF_VERTEX_2D,				// 使用する頂点フォーマット
		D3DPOOL_MANAGED,			// リソースのバッファを保持するメモリクラスを指定
		&g_pD3DVtxBuffResultScore,	// 頂点バッファインターフェースへのポインタ
		NULL)))						// NULLに設定
	{
		return E_FAIL;
	}

	{//頂点バッファの中身を埋める
		VERTEX_2D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffResultScore->Lock(0, 0, (void**)&pVtx, 0);

		// 頂点座標の設定
		pVtx[0].vtx = D3DXVECTOR3(0.0f, SCREEN_HEIGHT / 3, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT / 3, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

		// 桁数分処理する
		for (i = 0; i < SCORE_DIGIT; i++)
		{
			// 頂点座標の設定
			g_vertexWkScore[i][0].vtx.x = -habaX * i + g_posScore.x;
			g_vertexWkScore[i][0].vtx.y = g_posScore.y;
			g_vertexWkScore[i][0].vtx.z = 0.0f;
			g_vertexWkScore[i][1].vtx.x = -habaX * i + g_posScore.x + TEXTURE_SCORE00_SIZE_X;
			g_vertexWkScore[i][1].vtx.y = g_posScore.y;
			g_vertexWkScore[i][1].vtx.z = 0.0f;
			g_vertexWkScore[i][2].vtx.x = -habaX * i + g_posScore.x;
			g_vertexWkScore[i][2].vtx.y = g_posScore.y + TEXTURE_SCORE00_SIZE_Y;
			g_vertexWkScore[i][2].vtx.z = 0.0f;
			g_vertexWkScore[i][3].vtx.x = -habaX * i + g_posScore.x + TEXTURE_SCORE00_SIZE_X;
			g_vertexWkScore[i][3].vtx.y = g_posScore.y + TEXTURE_SCORE00_SIZE_Y;
			g_vertexWkScore[i][3].vtx.z = 0.0f;
			//g_vertexWkScore[i][4].vtx.x = -habaX * i + g_posScore.x + TEXTURE_SCORE00_SIZE_X;
			//g_vertexWkScore[i][4].vtx.y = g_posScore.y + TEXTURE_SCORE00_SIZE_Y;
			//g_vertexWkScore[i][4].vtx.z = 0.0f;
			//g_vertexWkScore[i][5].vtx.x = -habaX * i + g_posScore.x + TEXTURE_SCORE00_SIZE_X;
			//g_vertexWkScore[i][5].vtx.y = g_posScore.y + TEXTURE_SCORE00_SIZE_Y;
			//g_vertexWkScore[i][5].vtx.z = 0.0f;
			//g_vertexWkScore[i][6].vtx.x = -habaX * i + g_posScore.x + TEXTURE_SCORE00_SIZE_X;
			//g_vertexWkScore[i][6].vtx.y = g_posScore.y + TEXTURE_SCORE00_SIZE_Y;
			//g_vertexWkScore[i][6].vtx.z = 0.0f;
			//g_vertexWkScore[i][7].vtx.x = -habaX * i + g_posScore.x + TEXTURE_SCORE00_SIZE_X;
			//g_vertexWkScore[i][7].vtx.y = g_posScore.y + TEXTURE_SCORE00_SIZE_Y;
			//g_vertexWkScore[i][7].vtx.z = 0.0f;
			//g_vertexWkScore[i][8].vtx.x = -habaX * i + g_posScore.x + TEXTURE_SCORE00_SIZE_X;
			//g_vertexWkScore[i][8].vtx.y = g_posScore.y + TEXTURE_SCORE00_SIZE_Y;
			//g_vertexWkScore[i][8].vtx.z = 0.0f;
			//g_vertexWkScore[i][9].vtx.x = -habaX * i + g_posScore.x + TEXTURE_SCORE00_SIZE_X;
			//g_vertexWkScore[i][9].vtx.y = g_posScore.y + TEXTURE_SCORE00_SIZE_Y;
			//g_vertexWkScore[i][9].vtx.z = 0.0f;

			// rhwの設定
			g_vertexWkScore[i][0].rhw =
				g_vertexWkScore[i][1].rhw =
				g_vertexWkScore[i][2].rhw =
				g_vertexWkScore[i][3].rhw = 1.0f;

			// 反射光の設定
			g_vertexWkScore[i][0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
			g_vertexWkScore[i][1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
			g_vertexWkScore[i][2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
			g_vertexWkScore[i][3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

			// テクスチャ座標の設定
			g_vertexWkScore[i][0].tex = D3DXVECTOR2(0.0f, 0.0f);
			g_vertexWkScore[i][1].tex = D3DXVECTOR2(1.0f, 0.0f);
			g_vertexWkScore[i][2].tex = D3DXVECTOR2(0.0f, 1.0f);
			g_vertexWkScore[i][3].tex = D3DXVECTOR2(1.0f, 1.0f);
		}
	}
	return S_OK;
}
//=============================================================================
// 頂点座標の設定
//=============================================================================
//void SetTextureScore(void)
//{
//	int i;
//	int number = g_nScore;
//
//	for (i = 0; i < SCORE_DIGIT; i++)
//	{
//		// テクスチャ座標の設定
//		float x = (float)(number % 10);
//		g_vertexWkScore[i][0].tex = D3DXVECTOR2(0.1f * x, 0.0f);
//		g_vertexWkScore[i][1].tex = D3DXVECTOR2(0.1f * (x + 1), 0.0f);
//		g_vertexWkScore[i][2].tex = D3DXVECTOR2(0.1f * x, 1.0f);
//		g_vertexWkScore[i][3].tex = D3DXVECTOR2(0.1f * (x + 1), 1.0f);
//		number /= 10;
//	}
//
//
//	return S_OK;
//}

	
