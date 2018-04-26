//=============================================================================
//
// リザルト画面処理 [resultlogo.cpp]
// Author : GP12B295 ⑫ 関口昂平
//
//=============================================================================
#include "resultlogo.h"
#include "input.h"
#include "fade.h"
#include "stage.h"
#include "sound.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexResultlogo(LPDIRECT3DDEVICE9 pDevice);
void SetColorResultlogoLogo(void);
void SetTextureResultlogologo(int no);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureResultlogo = NULL;		// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffResultlogo = NULL;		// 頂点バッファインターフェースへのポインタ

LPDIRECT3DTEXTURE9		g_pD3DTextureResultlogoLogo = NULL;	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffResultlogoLogo = NULL;	// 頂点バッファインターフェースへのポインタ

LPDIRECT3DTEXTURE9		g_pD3DTextureResultlogologo = NULL;		// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffResultlogologo = NULL;		// 頂点バッファインターフェースへのポインタ


int						g_nCountAppearResultlogo = 0;		// 出現までの待ち時間
int						g_nCountWaitResultlogo = 0;			// 待ち時間
float					g_fAlphaResultlogo = 0.0f;			// リザルトロゴのα値
bool					g_bResultFade;



//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitResultlogo(int nType)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	g_nCountAppearResultlogo = 0;
	g_nCountWaitResultlogo = 0;
	g_fAlphaResultlogo = 0.0f;
	g_bResultFade = false;



	// 頂点情報の作成
	MakeVertexResultlogo(pDevice);


	if (nType == STAGE_INIT_FAST)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
			TEXTURE_RESULTLOGO,				// ファイルの名前
			&g_pD3DTextureResultlogo);		// 読み込むメモリー

											// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
			TEXTURE_RESULTLOGO_LOGO,		// ファイルの名前
			&g_pD3DTextureResultlogoLogo);	// 読み込むメモリー

											// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
			TEXTURE_RESULTLOGO_LOGO2		// 読み込むメモリー
			,		// ファイルの名前
			&g_pD3DTextureResultlogologo);	// 読み込むメモリー


	}




	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitResultlogo(void)
{
	if (g_pD3DTextureResultlogo != NULL)
	{// テクスチャの開放
		g_pD3DTextureResultlogo->Release();
		g_pD3DTextureResultlogo = NULL;
	}

	if (g_pD3DVtxBuffResultlogo != NULL)
	{// 頂点バッファの開放
		g_pD3DVtxBuffResultlogo->Release();
		g_pD3DVtxBuffResultlogo = NULL;
	}

	if (g_pD3DTextureResultlogoLogo != NULL)
	{// テクスチャの開放
		g_pD3DTextureResultlogoLogo->Release();
		g_pD3DTextureResultlogoLogo = NULL;
	}

	if (g_pD3DVtxBuffResultlogoLogo != NULL)
	{// 頂点バッファの開放
		g_pD3DVtxBuffResultlogoLogo->Release();
		g_pD3DVtxBuffResultlogoLogo = NULL;
	}

	if (g_pD3DTextureResultlogologo != NULL)
	{// テクスチャの開放
		g_pD3DTextureResultlogologo->Release();
		g_pD3DTextureResultlogologo = NULL;
	}

	if (g_pD3DVtxBuffResultlogologo != NULL)
	{// 頂点バッファの開放
		g_pD3DVtxBuffResultlogologo->Release();
		g_pD3DVtxBuffResultlogologo = NULL;
	}



}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateResultlogo(void)
{
	g_nCountAppearResultlogo++;
	if (g_nCountAppearResultlogo >= COUNT_APPERA_RESULTLOGO)
	{
		if (g_fAlphaResultlogo < 1.0f)
		{
			g_fAlphaResultlogo += 0.05f;
			if (g_fAlphaResultlogo >= 1.0f)
			{
				g_fAlphaResultlogo = 1.0f;
			}

			SetColorResultlogoLogo();
		}
	}


	//SetTextureResultlogologo(GetStageWinPlayer());
	//SetTextureResultlogologo(1);


	if (GetKeyboardTrigger(DIK_RETURN) || IsButtonTriggered(1, BUTTON_C) || IsButtonTriggered(0, BUTTON_C))
	{// Enter押したら、フェードアウトしてモードを切り替えいく
		if (!g_bResultFade)
		{
			g_bResultFade = true;
			SetSe(SE_BUTTON, E_DS8_FLAG_NONE, CONTINUITY_ON);
			SetFade(FADE_OUT, STAGE_TITLE);
		}
	}

	g_nCountWaitResultlogo++;
	if (g_nCountWaitResultlogo == LIMIT_COUNT_WAIT)
	{
		if (!g_bResultFade)
		{
			g_bResultFade = true;
			SetFade(FADE_OUT, STAGE_TITLE);
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawResultlogo(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, g_pD3DVtxBuffResultlogo, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pD3DTextureResultlogo);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);



	// 頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, g_pD3DVtxBuffResultlogoLogo, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pD3DTextureResultlogoLogo);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);



	// 頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, g_pD3DVtxBuffResultlogologo, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pD3DTextureResultlogologo);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);




}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexResultlogo(LPDIRECT3DDEVICE9 pDevice)
{
	// オブジェクトの頂点バッファを生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,	// 頂点データ用に確保するバッファサイズ(バイト単位)
		D3DUSAGE_WRITEONLY,			// 頂点バッファの使用法　
		FVF_VERTEX_2D,				// 使用する頂点フォーマット
		D3DPOOL_MANAGED,			// リソースのバッファを保持するメモリクラスを指定
		&g_pD3DVtxBuffResultlogo,		// 頂点バッファインターフェースへのポインタ
		NULL)))						// NULLに設定
	{
		return E_FAIL;
	}

	{//頂点バッファの中身を埋める
		VERTEX_2D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffResultlogo->Lock(0, 0, (void**)&pVtx, 0);

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
		g_pD3DVtxBuffResultlogo->Unlock();
	}

	// オブジェクトの頂点バッファを生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,	// 頂点データ用に確保するバッファサイズ(バイト単位)
		D3DUSAGE_WRITEONLY,			// 頂点バッファの使用法　
		FVF_VERTEX_2D,				// 使用する頂点フォーマット
		D3DPOOL_MANAGED,			// リソースのバッファを保持するメモリクラスを指定
		&g_pD3DVtxBuffResultlogoLogo,	// 頂点バッファインターフェースへのポインタ
		NULL)))						// NULLに設定
	{
		return E_FAIL;
	}

	{//頂点バッファの中身を埋める
		VERTEX_2D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffResultlogoLogo->Lock(0, 0, (void**)&pVtx, 0);

		// 頂点座標の設定
		pVtx[0].vtx = D3DXVECTOR3(RESULTLOGO_LOGO_POS_X - RESULTLOGO_LOGO_WIDTH, RESULTLOGO_LOGO_POS_Y - RESULTLOGO_LOGO_HEIGHT, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(RESULTLOGO_LOGO_POS_X + RESULTLOGO_LOGO_WIDTH, RESULTLOGO_LOGO_POS_Y - RESULTLOGO_LOGO_HEIGHT, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(RESULTLOGO_LOGO_POS_X - RESULTLOGO_LOGO_WIDTH, RESULTLOGO_LOGO_POS_Y + RESULTLOGO_LOGO_HEIGHT, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(RESULTLOGO_LOGO_POS_X + RESULTLOGO_LOGO_WIDTH, RESULTLOGO_LOGO_POS_Y + RESULTLOGO_LOGO_HEIGHT, 0.0f);

		// テクスチャのパースペクティブコレクト用
		pVtx[0].rhw =
			pVtx[1].rhw =
			pVtx[2].rhw =
			pVtx[3].rhw = 1.0f;

		// 反射光の設定
		pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fAlphaResultlogo);
		pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fAlphaResultlogo);
		pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fAlphaResultlogo);
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fAlphaResultlogo);

		// テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		// 頂点データをアンロックする
		g_pD3DVtxBuffResultlogoLogo->Unlock();
	}


	// オブジェクトの頂点バッファを生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,	// 頂点データ用に確保するバッファサイズ(バイト単位)
		D3DUSAGE_WRITEONLY,			// 頂点バッファの使用法　
		FVF_VERTEX_2D,				// 使用する頂点フォーマット
		D3DPOOL_MANAGED,			// リソースのバッファを保持するメモリクラスを指定
		&g_pD3DVtxBuffResultlogologo,	// 頂点バッファインターフェースへのポインタ
		NULL)))						// NULLに設定
	{
		return E_FAIL;
	}

	{//頂点バッファの中身を埋める
		VERTEX_2D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffResultlogologo->Lock(0, 0, (void**)&pVtx, 0);

		// 頂点座標の設定
		pVtx[0].vtx = D3DXVECTOR3(RESULTLOGO_LOGO2_POS_X - RESULTLOGO_LOGO2_WIDTH, RESULTLOGO_LOGO2_POS_Y - RESULTLOGO_LOGO2_HEIGHT, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(RESULTLOGO_LOGO2_POS_X + RESULTLOGO_LOGO2_WIDTH, RESULTLOGO_LOGO2_POS_Y - RESULTLOGO_LOGO2_HEIGHT, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(RESULTLOGO_LOGO2_POS_X - RESULTLOGO_LOGO2_WIDTH, RESULTLOGO_LOGO2_POS_Y + RESULTLOGO_LOGO2_HEIGHT, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(RESULTLOGO_LOGO2_POS_X + RESULTLOGO_LOGO2_WIDTH, RESULTLOGO_LOGO2_POS_Y + RESULTLOGO_LOGO2_HEIGHT, 0.0f);

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
		g_pD3DVtxBuffResultlogologo->Unlock();
	}



	return S_OK;
}

//=============================================================================
// 頂点カラーの設定
//=============================================================================
void SetColorResultlogoLogo(void)
{
	{//頂点バッファの中身を埋める
		VERTEX_2D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffResultlogoLogo->Lock(0, 0, (void**)&pVtx, 0);

		// 反射光の設定
		pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fAlphaResultlogo);
		pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fAlphaResultlogo);
		pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fAlphaResultlogo);
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fAlphaResultlogo);

		// 頂点データをアンロックする
		g_pD3DVtxBuffResultlogoLogo->Unlock();
	}
}

//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTextureResultlogologo(int no)
{
	{//頂点バッファの中身を埋める
		VERTEX_2D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffResultlogologo->Lock(0, 0, (void**)&pVtx, 0);

		// テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2((no - 1)*0.5, 0.0f);
		pVtx[1].tex = D3DXVECTOR2((no - 1)*0.5 + 0.5, 0.0f);
		pVtx[2].tex = D3DXVECTOR2((no - 1)*0.5, 1.0f);
		pVtx[3].tex = D3DXVECTOR2((no - 1)*0.5 + 0.5, 1.0f);


		// 頂点データをアンロックする
		g_pD3DVtxBuffResultlogologo->Unlock();
	}



}

