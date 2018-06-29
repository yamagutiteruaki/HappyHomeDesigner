
//***********************************************************
//
// タイトル処理は松尾公平の担当です。
//
//***********************************************************
#include "main.h"
#include "rankpaper.h"
#include "input.h"
#include "fade.h"
#include "stage.h"
#include "debugproc.h"

//***********************************************************
// プロトタイプ宣言
//***********************************************************
HRESULT MakeVertexRankpaper(LPDIRECT3DDEVICE9 pDevice);
void SetColorRankpaper(void);

void SetVertexRankPaper(int no);
void SetVertexRank(int no);
void SetPaperPos(int no);
void SetRankPos(int no);
void SetVertexBg(void);





//***********************************************************
//グローバル宣言
//***********************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureRankpaper0 = NULL;		// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffRankpaper0 = NULL;		// 頂点バッファインターフェースへのポインタ
LPDIRECT3DTEXTURE9		g_pD3DTextureRankpaper1 = NULL;		// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffRankpaper1 = NULL;		// 頂点バッファインターフェースへのポインタ
LPDIRECT3DTEXTURE9		g_pD3DTextureRankpaper2 = NULL;		// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffRankpaper2 = NULL;		// 頂点バッファインターフェースへのポインタ

LPDIRECT3DTEXTURE9		g_pD3DTextureRankpaper_back = NULL;	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffRankpaper_back = NULL;	// 頂点バッファインターフェースへのポインタ
LPDIRECT3DTEXTURE9		g_pD3DTextureFirst = NULL;		// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffFirst = NULL;		// 頂点バッファインターフェースへのポインタ
LPDIRECT3DTEXTURE9		g_pD3DTextureSecond = NULL;		// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffSecond = NULL;		// 頂点バッファインターフェースへのポインタ
LPDIRECT3DTEXTURE9		g_pD3DTextureThird = NULL;		// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffThird = NULL;		// 頂点バッファインターフェースへのポインタ


RANKPAPER				rankpaperWk[RANKPAPER_MAX];
RANKINGNO				rankingnoWk[RANK_NO_MAX];


D3DXVECTOR3				rankbackpos;

//***********************************************************
// 初期化処理
//***********************************************************
HRESULT InitRankpaper(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();



	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
		TEXTURE_RANKPAPER_BACK,				// ファイルの名前
		&g_pD3DTextureRankpaper_back);		// 読み込むメモリー

	D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
		TEXTURE_RANKPAPER0,			// ファイルの名前
		&g_pD3DTextureRankpaper0);	// 読み込むメモリー

	D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
		TEXTURE_RANKPAPER1,			// ファイルの名前
		&g_pD3DTextureRankpaper1);	// 読み込むメモリー

	D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
		TEXTURE_RANKPAPER2,			// ファイルの名前
		&g_pD3DTextureRankpaper2);	// 読み込むメモリー


	D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
		TEXTURE_FIRST,			// ファイルの名前
		&g_pD3DTextureFirst);		// 読み込むメモリー

	D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
		TEXTURE_SECOND,			// ファイルの名前
		&g_pD3DTextureSecond);		// 読み込むメモリー

	D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
		TEXTURE_THIRD,			// ファイルの名前
		&g_pD3DTextureThird);		// 読み込むメモリー


	rankbackpos = D3DXVECTOR3(RANKPAPERBACK_POS_X, RANKPAPERBACK_POS_Y,0.0f);

	RANKPAPER *rankpaper = GetRankPaper(0);
	RANKINGNO *rankno = GetRankingNo(0);
	
	for (int i = 0; i < RANKPAPER_MAX; i++, rankpaper++, rankno++)
	{
		rankpaper->pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
		rankno->pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	}

	MakeVertexRankpaper(pDevice);							//頂点情報の作成


	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitRankpaper(void)
{
	if (g_pD3DTextureRankpaper0 != NULL)
	{// テクスチャの開放
		g_pD3DTextureRankpaper0->Release();
		g_pD3DTextureRankpaper0 = NULL;
	}

	if (g_pD3DVtxBuffRankpaper0 != NULL)
	{// 頂点バッファの開放
		g_pD3DVtxBuffRankpaper0->Release();
		g_pD3DVtxBuffRankpaper0 = NULL;
	}

	if (g_pD3DTextureRankpaper1 != NULL)
	{// テクスチャの開放
		g_pD3DTextureRankpaper1->Release();
		g_pD3DTextureRankpaper1 = NULL;
	}

	if (g_pD3DVtxBuffRankpaper1 != NULL)
	{// 頂点バッファの開放
		g_pD3DVtxBuffRankpaper1->Release();
		g_pD3DVtxBuffRankpaper1 = NULL;
	}

	if (g_pD3DTextureRankpaper2 != NULL)
	{// テクスチャの開放
		g_pD3DTextureRankpaper2->Release();
		g_pD3DTextureRankpaper2 = NULL;
	}

	if (g_pD3DVtxBuffRankpaper2 != NULL)
	{// 頂点バッファの開放
		g_pD3DVtxBuffRankpaper2->Release();
		g_pD3DVtxBuffRankpaper2 = NULL;
	}

	if (g_pD3DTextureRankpaper_back != NULL)
	{// テクスチャの開放
		g_pD3DTextureRankpaper_back->Release();
		g_pD3DTextureRankpaper_back = NULL;
	}

	if (g_pD3DVtxBuffRankpaper_back != NULL)
	{// 頂点バッファの開放
		g_pD3DVtxBuffRankpaper_back->Release();
		g_pD3DVtxBuffRankpaper_back = NULL;
	}

	if (g_pD3DTextureFirst != NULL)
	{// テクスチャの開放
		g_pD3DTextureFirst->Release();
		g_pD3DTextureFirst = NULL;
	}

	if (g_pD3DVtxBuffFirst != NULL)
	{// 頂点バッファの開放
		g_pD3DVtxBuffFirst->Release();
		g_pD3DVtxBuffFirst = NULL;
	}

	if (g_pD3DTextureSecond != NULL)
	{// テクスチャの開放
		g_pD3DTextureSecond->Release();
		g_pD3DTextureSecond = NULL;
	}

	if (g_pD3DVtxBuffSecond != NULL)
	{// 頂点バッファの開放
		g_pD3DVtxBuffSecond->Release();
		g_pD3DVtxBuffSecond = NULL;
	}

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateRankpaper(void)
{

	if (rankbackpos.y >= 0)
	{
		if (GetKeyboardTrigger(DIK_RETURN) || IsButtonTriggered(0, BUTTON_C))
		{
			SetFade(FADE_OUT, STAGE_TITLE, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
		}
	}

	rankbackpos.y+=10.0f;

	if (rankbackpos.y >= 0)
	{
		rankbackpos.y = 0;
	}

	for (int i = 0; i < RANKPAPER_MAX; i++)
	{
		SetPaperPos(i);
		SetRankPos(i);
		
		SetVertexRankPaper(i);
		SetVertexRank(i);


	}
	SetVertexBg();

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawRankpaper(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	/* 後ろ */


	// 頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, g_pD3DVtxBuffRankpaper_back, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pD3DTextureRankpaper_back);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

	/* 手配書0 */
	// 頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, g_pD3DVtxBuffRankpaper0, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pD3DTextureRankpaper0);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);


	/* 手配書1 */
	// 頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, g_pD3DVtxBuffRankpaper1, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pD3DTextureRankpaper1);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

	/* 手配書2 */
	// 頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, g_pD3DVtxBuffRankpaper2, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pD3DTextureRankpaper2);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);



		// 頂点バッファをデバイスのデータストリームにバインド
		pDevice->SetStreamSource(0, g_pD3DVtxBuffFirst, 0, sizeof(VERTEX_2D));

		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		// テクスチャの設定
		pDevice->SetTexture(0, g_pD3DTextureFirst);

		// ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);



		// 頂点バッファをデバイスのデータストリームにバインド
		pDevice->SetStreamSource(0, g_pD3DVtxBuffSecond, 0, sizeof(VERTEX_2D));

		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		// テクスチャの設定
		pDevice->SetTexture(0, g_pD3DTextureSecond);

		// ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);


		// 頂点バッファをデバイスのデータストリームにバインド
		pDevice->SetStreamSource(0, g_pD3DVtxBuffThird, 0, sizeof(VERTEX_2D));

		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		// テクスチャの設定
		pDevice->SetTexture(0, g_pD3DTextureThird);

		// ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexRankpaper(LPDIRECT3DDEVICE9 pDevice)
{
	// オブジェクトの頂点バッファを生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,	// 頂点データ用に確保するバッファサイズ(バイト単位)
		D3DUSAGE_WRITEONLY,			// 頂点バッファの使用法　
		FVF_VERTEX_2D,				// 使用する頂点フォーマット
		D3DPOOL_MANAGED,			// リソースのバッファを保持するメモリクラスを指定
		&g_pD3DVtxBuffRankpaper_back,		// 頂点バッファインターフェースへのポインタ
		NULL)))						// NULLに設定
	{
		return E_FAIL;
	}

	{//頂点バッファの中身を埋める
		VERTEX_2D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffRankpaper_back->Lock(0, 0, (void**)&pVtx, 0);

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
		g_pD3DVtxBuffRankpaper_back->Unlock();
	}
	//手配書==========================================

	// オブジェクトの頂点バッファを生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,	// 頂点データ用に確保するバッファサイズ(バイト単位)
		D3DUSAGE_WRITEONLY,			// 頂点バッファの使用法　
		FVF_VERTEX_2D,				// 使用する頂点フォーマット
		D3DPOOL_MANAGED,			// リソースのバッファを保持するメモリクラスを指定
		&g_pD3DVtxBuffRankpaper0,	// 頂点バッファインターフェースへのポインタ
		NULL)))						// NULLに設定
	{
		return E_FAIL;
	}

	{//頂点バッファの中身を埋める
		VERTEX_2D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffRankpaper0->Lock(0, 0, (void**)&pVtx, 0);

		// 頂点座標の設定
		pVtx[0].vtx = D3DXVECTOR3(RANKPAPER0_POS_X, RANKPAPER0_POS_Y, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(RANKPAPER0_POS_X + RANKPAPER0_WIDTH, RANKPAPER0_POS_Y, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(RANKPAPER0_POS_X, RANKPAPER0_POS_Y + RANKPAPER0_HEIGHT, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(RANKPAPER0_POS_X + RANKPAPER0_WIDTH, RANKPAPER0_POS_Y + RANKPAPER0_HEIGHT, 0.0f);

		
		
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
		g_pD3DVtxBuffRankpaper0->Unlock();
	}

	// オブジェクトの頂点バッファを生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,	// 頂点データ用に確保するバッファサイズ(バイト単位)
		D3DUSAGE_WRITEONLY,			// 頂点バッファの使用法　
		FVF_VERTEX_2D,				// 使用する頂点フォーマット
		D3DPOOL_MANAGED,			// リソースのバッファを保持するメモリクラスを指定
		&g_pD3DVtxBuffRankpaper1,	// 頂点バッファインターフェースへのポインタ
		NULL)))						// NULLに設定
	{
		return E_FAIL;
	}

	{//頂点バッファの中身を埋める
		VERTEX_2D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffRankpaper1->Lock(0, 0, (void**)&pVtx, 0);

		// 頂点座標の設定
		pVtx[0].vtx = D3DXVECTOR3(RANKPAPER1_POS_X, RANKPAPER1_POS_Y, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(RANKPAPER1_POS_X + RANKPAPER1_WIDTH, RANKPAPER1_POS_Y, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(RANKPAPER1_POS_X, RANKPAPER1_POS_Y + RANKPAPER1_HEIGHT, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(RANKPAPER1_POS_X + RANKPAPER1_WIDTH, RANKPAPER1_POS_Y + RANKPAPER1_HEIGHT, 0.0f);

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
		g_pD3DVtxBuffRankpaper1->Unlock();
	}

	// オブジェクトの頂点バッファを生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,	// 頂点データ用に確保するバッファサイズ(バイト単位)
		D3DUSAGE_WRITEONLY,			// 頂点バッファの使用法　
		FVF_VERTEX_2D,				// 使用する頂点フォーマット
		D3DPOOL_MANAGED,			// リソースのバッファを保持するメモリクラスを指定
		&g_pD3DVtxBuffRankpaper2,	// 頂点バッファインターフェースへのポインタ
		NULL)))						// NULLに設定
	{
		return E_FAIL;
	}

	{//頂点バッファの中身を埋める
		VERTEX_2D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffRankpaper2->Lock(0, 0, (void**)&pVtx, 0);

		// 頂点座標の設定
		pVtx[0].vtx = D3DXVECTOR3(RANKPAPER2_POS_X, RANKPAPER2_POS_Y, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(RANKPAPER2_POS_X + RANKPAPER2_WIDTH, RANKPAPER2_POS_Y, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(RANKPAPER2_POS_X, RANKPAPER2_POS_Y + RANKPAPER2_HEIGHT, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(RANKPAPER2_POS_X + RANKPAPER2_WIDTH, RANKPAPER2_POS_Y + RANKPAPER2_HEIGHT, 0.0f);

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
		g_pD3DVtxBuffRankpaper2->Unlock();
	}

	//1位===========================================

	// オブジェクトの頂点バッファを生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,	// 頂点データ用に確保するバッファサイズ(バイト単位)
		D3DUSAGE_WRITEONLY,			// 頂点バッファの使用法　
		FVF_VERTEX_2D,				// 使用する頂点フォーマット
		D3DPOOL_MANAGED,			// リソースのバッファを保持するメモリクラスを指定
		&g_pD3DVtxBuffFirst,		// 頂点バッファインターフェースへのポインタ
		NULL)))						// NULLに設定
	{
		return E_FAIL;
	}

	{//頂点バッファの中身を埋める
		VERTEX_2D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffFirst->Lock(0, 0, (void**)&pVtx, 0);

		// 頂点座標の設定
		pVtx[0].vtx = D3DXVECTOR3(RANKPAPER_FIRST_POS_X, RANKPAPER_FIRST_POS_Y, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(RANKPAPER_FIRST_POS_X + RANKPAPER_FIRST_WIDTH, RANKPAPER_FIRST_POS_Y, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(RANKPAPER_FIRST_POS_X, RANKPAPER_FIRST_POS_Y + RANKPAPER_FIRST_HEIGHT, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(RANKPAPER_FIRST_POS_X + RANKPAPER_FIRST_WIDTH, RANKPAPER_FIRST_POS_Y + RANKPAPER_FIRST_HEIGHT, 0.0f);

		// テクスチャのパースペクティブコレクト用
		pVtx[0].rhw =
			pVtx[1].rhw =
			pVtx[2].rhw =
			pVtx[3].rhw = 1.0f;

		// 反射光の設定
		pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 0, 1.0f);
		pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 0, 1.0f);
		pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 0, 1.0f);
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 0, 1.0f);

		// テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		// 頂点データをアンロックする
		g_pD3DVtxBuffFirst->Unlock();
	}

	// セカンド==============================

	// オブジェクトの頂点バッファを生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,	// 頂点データ用に確保するバッファサイズ(バイト単位)
		D3DUSAGE_WRITEONLY,			// 頂点バッファの使用法　
		FVF_VERTEX_2D,				// 使用する頂点フォーマット
		D3DPOOL_MANAGED,			// リソースのバッファを保持するメモリクラスを指定
		&g_pD3DVtxBuffSecond,		// 頂点バッファインターフェースへのポインタ
		NULL)))						// NULLに設定
	{
		return E_FAIL;
	}

	{//頂点バッファの中身を埋める
		VERTEX_2D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffSecond->Lock(0, 0, (void**)&pVtx, 0);

		pVtx[0].vtx = D3DXVECTOR3(RANKPAPER_SECOND_POS_X, RANKPAPER_SECOND_POS_Y, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(RANKPAPER_SECOND_POS_X + RANKPAPER_SECOND_WIDTH, RANKPAPER_SECOND_POS_Y, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(RANKPAPER_SECOND_POS_X, RANKPAPER_SECOND_POS_Y + RANKPAPER_SECOND_HEIGHT, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(RANKPAPER_SECOND_POS_X + RANKPAPER_SECOND_WIDTH, RANKPAPER_SECOND_POS_Y + RANKPAPER_SECOND_HEIGHT, 0.0f);


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
		g_pD3DVtxBuffSecond->Unlock();
	}


	// サード==============================

	// オブジェクトの頂点バッファを生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,	// 頂点データ用に確保するバッファサイズ(バイト単位)
		D3DUSAGE_WRITEONLY,			// 頂点バッファの使用法　
		FVF_VERTEX_2D,				// 使用する頂点フォーマット
		D3DPOOL_MANAGED,			// リソースのバッファを保持するメモリクラスを指定
		&g_pD3DVtxBuffThird,		// 頂点バッファインターフェースへのポインタ
		NULL)))						// NULLに設定
	{
		return E_FAIL;
	}

	{//頂点バッファの中身を埋める
		VERTEX_2D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffThird->Lock(0, 0, (void**)&pVtx, 0);

		pVtx[0].vtx = D3DXVECTOR3(RANKPAPER_THIRD_POS_X, RANKPAPER_THIRD_POS_Y, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(RANKPAPER_THIRD_POS_X + RANKPAPER_THIRD_WIDTH, RANKPAPER_THIRD_POS_Y, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(RANKPAPER_THIRD_POS_X, RANKPAPER_THIRD_POS_Y + RANKPAPER_THIRD_HEIGHT, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(RANKPAPER_THIRD_POS_X + RANKPAPER_THIRD_WIDTH, RANKPAPER_THIRD_POS_Y + RANKPAPER_THIRD_HEIGHT, 0.0f);


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
		g_pD3DVtxBuffSecond->Unlock();
	}

	return S_OK;
}

//=============================================================================
// テクスチャ座標の設定  ※手配書
//=============================================================================
void SetVertexRankPaper(int no)
{

	RANKPAPER *rankpaper = GetRankPaper(no);
	VERTEX_2D *pVtx;

	switch (no)
	{
	case 0:


		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffRankpaper0->Lock(0, 0, (void**)&pVtx, 0);

		// 頂点座標の設定
		pVtx[0].vtx = D3DXVECTOR3(rankpaper->pos.x - RANKPAPER0_WIDTH / 2, rankpaper->pos.y, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(rankpaper->pos.x + RANKPAPER0_WIDTH / 2, rankpaper->pos.y, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(rankpaper->pos.x - RANKPAPER0_WIDTH / 2, rankpaper->pos.y + RANKPAPER0_HEIGHT, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(rankpaper->pos.x + RANKPAPER0_WIDTH / 2, rankpaper->pos.y + RANKPAPER0_HEIGHT, 0.0f);


		// 頂点データをアンロックする
		g_pD3DVtxBuffRankpaper0->Unlock();


		break;

	case 1:

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffRankpaper1->Lock(0, 0, (void**)&pVtx, 0);

		// 頂点座標の設定
		pVtx[0].vtx = D3DXVECTOR3(rankpaper->pos.x - RANKPAPER1_WIDTH / 2, rankpaper->pos.y, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(rankpaper->pos.x + RANKPAPER1_WIDTH / 2, rankpaper->pos.y, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(rankpaper->pos.x - RANKPAPER1_WIDTH / 2, rankpaper->pos.y + RANKPAPER1_HEIGHT, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(rankpaper->pos.x + RANKPAPER1_WIDTH / 2, rankpaper->pos.y + RANKPAPER1_HEIGHT, 0.0f);

		// 頂点データをアンロックする
		g_pD3DVtxBuffRankpaper1->Unlock();
		break;


	case 2:

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffRankpaper2->Lock(0, 0, (void**)&pVtx, 0);

		// 頂点座標の設定
		pVtx[0].vtx = D3DXVECTOR3(rankpaper->pos.x - RANKPAPER2_WIDTH / 2, rankpaper->pos.y, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(rankpaper->pos.x + RANKPAPER2_WIDTH / 2, rankpaper->pos.y, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(rankpaper->pos.x - RANKPAPER2_WIDTH / 2, rankpaper->pos.y + RANKPAPER2_HEIGHT, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(rankpaper->pos.x + RANKPAPER2_WIDTH / 2, rankpaper->pos.y + RANKPAPER2_HEIGHT, 0.0f);

		// 頂点データをアンロックする
		g_pD3DVtxBuffRankpaper2->Unlock();
		break;


	}
}
//=============================================================================
// テクスチャ座標の設定　　※手配書
//=============================================================================
void SetPaperPos(int no)
{

	RANKPAPER *rankpaper = GetRankPaper(no);
	D3DXVECTOR3 BGpos = GetRankBackPos();

	switch (no)
	{
	case 0:
		rankpaper->pos.x = BGpos.x + RANKPAPER0_POS_X;
		rankpaper->pos.y = BGpos.y + RANKPAPER0_POS_Y;
		rankpaper->pos.z = BGpos.z;
		break;

	case 1:
		rankpaper->pos.x = BGpos.x + RANKPAPER1_POS_X;
		rankpaper->pos.y = BGpos.y + RANKPAPER1_POS_Y;
		rankpaper->pos.z = BGpos.z;
		break;

	case 2:
		rankpaper->pos.x = BGpos.x + RANKPAPER2_POS_X;
		rankpaper->pos.y = BGpos.y + RANKPAPER2_POS_Y;
		rankpaper->pos.z = BGpos.z;
		break;

	}
	PrintDebugProc("[手配書座標%d ：X(%f) Y(%f) Z(%f)]\n", no, rankpaper->pos.x, rankpaper->pos.y, rankpaper->pos.z);


}

//=============================================================================
// テクスチャ座標の設定　　※順位
//=============================================================================
void SetVertexRank(int no)
{
	VERTEX_2D *pVtx;

	RANKINGNO *rankingno = GetRankingNo(no);

	switch (no)
	{
	case 0:
		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffFirst->Lock(0, 0, (void**)&pVtx, 0);

		// 頂点座標の設定
		pVtx[0].vtx = D3DXVECTOR3(rankingno->pos.x - RANKPAPER_FIRST_WIDTH / 2, rankingno->pos.y, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(rankingno->pos.x + RANKPAPER_FIRST_WIDTH / 2, rankingno->pos.y, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(rankingno->pos.x - RANKPAPER_FIRST_WIDTH / 2, rankingno->pos.y + RANKPAPER_FIRST_HEIGHT, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(rankingno->pos.x + RANKPAPER_FIRST_WIDTH / 2, rankingno->pos.y + RANKPAPER_FIRST_HEIGHT, 0.0f);

		// 頂点データをアンロックする
		g_pD3DVtxBuffFirst->Unlock();
		break;

	case 1:
		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffSecond->Lock(0, 0, (void**)&pVtx, 0);

		// 頂点座標の設定
		pVtx[0].vtx = D3DXVECTOR3(rankingno->pos.x - RANKPAPER_SECOND_WIDTH / 2, rankingno->pos.y, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(rankingno->pos.x + RANKPAPER_SECOND_WIDTH / 2, rankingno->pos.y, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(rankingno->pos.x - RANKPAPER_SECOND_WIDTH / 2, rankingno->pos.y + RANKPAPER_SECOND_HEIGHT, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(rankingno->pos.x + RANKPAPER_SECOND_WIDTH / 2, rankingno->pos.y + RANKPAPER_SECOND_HEIGHT, 0.0f);

		// 頂点データをアンロックする
		g_pD3DVtxBuffSecond->Unlock();
		break;


	case 2:
		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffThird->Lock(0, 0, (void**)&pVtx, 0);

		// 頂点座標の設定
		pVtx[0].vtx = D3DXVECTOR3(rankingno->pos.x - RANKPAPER_THIRD_WIDTH / 2, rankingno->pos.y, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(rankingno->pos.x + RANKPAPER_THIRD_WIDTH / 2, rankingno->pos.y, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(rankingno->pos.x - RANKPAPER_THIRD_WIDTH / 2, rankingno->pos.y + RANKPAPER_THIRD_HEIGHT, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(rankingno->pos.x + RANKPAPER_THIRD_WIDTH / 2, rankingno->pos.y + RANKPAPER_THIRD_HEIGHT, 0.0f);

		// 頂点データをアンロックする
		g_pD3DVtxBuffThird->Unlock();
		break;


	}
}

//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetRankPos(int no)
{

	RANKPAPER *rankpaper = GetRankPaper(no);
	RANKINGNO *rankingno = GetRankingNo(no);

	switch (no)
	{
	case 0:
		rankingno->pos.x = rankpaper->pos.x;
		rankingno->pos.y = rankpaper->pos.y + RANKPAPER_FIRST_POS_Y;
		rankingno->pos.z = rankpaper->pos.z;
		break;
	case 1:
		rankingno->pos.x = rankpaper->pos.x;
		rankingno->pos.y = rankpaper->pos.y + RANKPAPER_SECOND_POS_Y;
		rankingno->pos.z = rankpaper->pos.z;
		break;
	case 2:
		rankingno->pos.x = rankpaper->pos.x;
		rankingno->pos.y = rankpaper->pos.y + RANKPAPER_THIRD_POS_Y;
		rankingno->pos.z = rankpaper->pos.z;
		break;
	}
	PrintDebugProc("[順位座標%d ：X(%f) Y(%f) Z(%f)]\n", no, rankingno->pos.x, rankingno->pos.y, rankingno->pos.z);

}

//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetVertexBg(void)
{
	VERTEX_2D *pVtx;

	D3DXVECTOR3 rankbackpos = GetRankBackPos();


		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffRankpaper_back->Lock(0, 0, (void**)&pVtx, 0);

		// 頂点座標の設定
		pVtx[0].vtx = D3DXVECTOR3(rankbackpos.x , rankbackpos.y, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(rankbackpos.x + RANKPAPERBACK_WIDTH , rankbackpos.y, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(rankbackpos.x , rankbackpos.y + RANKPAPERBACK_HEIGHT, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(rankbackpos.x + RANKPAPERBACK_WIDTH , rankbackpos.y + RANKPAPERBACK_HEIGHT, 0.0f);

		// 頂点データをアンロックする
		g_pD3DVtxBuffRankpaper_back->Unlock();
}

//=============================================================================
// 頂点の作成
//=============================================================================
void SetColorRankpaper(void)
{
	{//頂点バッファの中身を埋める
		VERTEX_2D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffRankpaper_back->Lock(0, 0, (void**)&pVtx, 0);

		// 反射光の設定
		pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f);



		// 頂点データをアンロックする
		g_pD3DVtxBuffRankpaper_back->Unlock();
	}

}

//==================================================================================
//手配書情報取得関数
//==================================================================================
RANKPAPER *GetRankPaper(int no)
{
	return &rankpaperWk[no];
}

//==================================================================================
//順位テクスチャ情報取得関数
//==================================================================================
RANKINGNO *GetRankingNo(int no)
{
	return &rankingnoWk[no];
}


//==================================================================================
//BG情報取得関数
//==================================================================================
D3DXVECTOR3 GetRankBackPos(void)
{
	return rankbackpos;
}