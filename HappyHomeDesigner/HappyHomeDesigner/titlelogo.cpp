
//***********************************************************
//
// タイトル処理は松尾公平の担当です。
//
//***********************************************************
#include "main.h"
#include "title.h"
#include "titlelogo.h"
#include "input.h"
#include "fade.h"
#include "stage.h"
#include "sound.h"
#include "inputCtrl.h"

//***********************************************************
// プロトタイプ宣言
//***********************************************************
HRESULT MakeVertexTitlelogo(LPDIRECT3DDEVICE9 pDevice);
void SetColorTitleLogo(void);
//***********************************************************
//グローバル宣言
//***********************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureTitle = NULL;		// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffTitle = NULL;		// 頂点バッファインターフェースへのポインタ
LPDIRECT3DTEXTURE9		g_pD3DTextureTitleLogo = NULL;	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffTitleLogo = NULL;	// 頂点バッファインターフェースへのポインタ
LPDIRECT3DTEXTURE9		g_pD3DTextureStart = NULL;		// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffStart = NULL;		// 頂点バッファインターフェースへのポインタ
LPDIRECT3DTEXTURE9		g_pD3DTextureStamp = NULL;		// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffStamp = NULL;		// 頂点バッファインターフェースへのポインタ

int						g_nCountAppearStart = 0;		//
int						stampCount;
float					g_fAlphaLogo = 0.0f;			//
int						g_nCountDisp = 0;				// 
bool					g_bDispStart = false;			// スタートが出てくるまで
int						g_nConutDemo = 0;				//
bool					g_bStamp;						//スタンプの有無
float					BaseAngle;						//中心
float					Radius;							//半径


//***********************************************************
// 初期化処理
//***********************************************************
HRESULT InitTitlelogo(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	g_nCountAppearStart = 0;
	g_fAlphaLogo = 0.0f;
	g_nCountDisp = 0;
	g_bDispStart = false;
	g_nConutDemo = 0;
	g_bStamp = false;
	stampCount = 0;

	D3DXVECTOR2 temp = D3DXVECTOR2(STAMP_HEIGHT, STAMP_WIDTH);

	Radius = D3DXVec2Length(&temp);					// エネミーの半径を初期化
	BaseAngle = atan2f(STAMP_HEIGHT, STAMP_WIDTH);	// エネミーの角度を初期化

	MakeVertexTitlelogo(pDevice);							//頂点情報の作成


	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
		TEXTURE_TITLE,				// ファイルの名前
		&g_pD3DTextureTitle);		// 読み込むメモリー

	D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
		TEXTURE_TITLE_LOGO,			// ファイルの名前
		&g_pD3DTextureTitleLogo);	// 読み込むメモリー


	D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
		TEXTURE_LOGO_START,			// ファイルの名前
		&g_pD3DTextureStart);		// 読み込むメモリー

	D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
		TEXTURE_STAMP,			// ファイルの名前
		&g_pD3DTextureStamp);		// 読み込むメモリー


	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitTitlelogo(void)
{
	if (g_pD3DTextureTitle != NULL)
	{// テクスチャの開放
		g_pD3DTextureTitle->Release();
		g_pD3DTextureTitle = NULL;
	}

	if (g_pD3DVtxBuffTitle != NULL)
	{// 頂点バッファの開放
		g_pD3DVtxBuffTitle->Release();
		g_pD3DVtxBuffTitle = NULL;
	}

	if (g_pD3DTextureTitleLogo != NULL)
	{// テクスチャの開放
		g_pD3DTextureTitleLogo->Release();
		g_pD3DTextureTitleLogo = NULL;
	}

	if (g_pD3DVtxBuffTitleLogo != NULL)
	{// 頂点バッファの開放
		g_pD3DVtxBuffTitleLogo->Release();
		g_pD3DVtxBuffTitleLogo = NULL;
	}

	if (g_pD3DTextureStart != NULL)
	{// テクスチャの開放
		g_pD3DTextureStart->Release();
		g_pD3DTextureStart = NULL;
	}

	if (g_pD3DVtxBuffStart != NULL)
	{// 頂点バッファの開放
		g_pD3DVtxBuffStart->Release();
		g_pD3DVtxBuffStart = NULL;
	}

	if (g_pD3DTextureStamp != NULL)
	{// テクスチャの開放
		g_pD3DTextureStamp->Release();
		g_pD3DTextureStamp = NULL;
	}

	if (g_pD3DVtxBuffStamp != NULL)
	{// 頂点バッファの開放
		g_pD3DVtxBuffStamp->Release();
		g_pD3DVtxBuffStamp = NULL;
	}

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateTitlelogo(void)
{
	INPUTDEVICE *kb = GetInputDevice(INPUT_KEY);
	INPUTDEVICE *gp = GetInputDevice(INPUT_GAMEPAD);

#if 0
	if (g_nCountAppearStart >= COUNT_APPERA_START)
	{
		g_nConutDemo++;
		if (g_nConutDemo > COUNT_WAIT_DEMO)
		{
			SetFade(FADE_OUT, MODE_TITLE);
		}
	}
#endif

	if (g_fAlphaLogo < 1.0f)
	{
		g_fAlphaLogo += 0.005f;
		if (g_fAlphaLogo >= 1.0f)
		{
			g_fAlphaLogo = 1.0f;
		}
		SetColorTitleLogo();
	}
	else
	{
		g_nCountAppearStart++;
		if (g_nCountAppearStart > COUNT_APPERA_START)
		{
			g_nCountDisp = (g_nCountDisp + 1) % 80;
			if (g_nCountDisp > INTERVAL_DISP_START)
			{
				g_bDispStart = false;
			}
			else
			{
				g_bDispStart = true;
			}
		}
	}

	if (GetKeyboardTrigger(DIK_A))//スタンプを　T=押してる　F=押してない
	{
		g_bStamp = g_bStamp ? false : true;
	}
	if (GetKeyboardTrigger(kb->DECIDE) || IsButtonTriggered(0, gp->DECIDE))
	{

		if (g_nCountAppearStart == 0)
		{// タイトル登場スキップ
			g_fAlphaLogo = 1.0f;
			SetColorTitleLogo();

			g_nCountAppearStart = COUNT_APPERA_START;
		}
		else
		{// ゲームへ
			g_bStamp = true;
			SetSe(SE_DECI, E_DS8_FLAG_NONE, CONTINUITY_OFF);

		}
	}

	if (g_bStamp == true)
	{
		stampCount++;
	}
	if (stampCount >= 60)
	{
		SetFade(FADE_OUT, STAGE_GAME, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
		
	}
	

	if (g_bStamp == true)				//スタンプが押されてる時
	{
		g_bDispStart = true;

		SetColorTitleLogo();
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawTitlelogo(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, g_pD3DVtxBuffTitle, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pD3DTextureTitle);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);


	// 頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, g_pD3DVtxBuffTitleLogo, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pD3DTextureTitleLogo);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

	if (g_bDispStart == true)
	{
		// 頂点バッファをデバイスのデータストリームにバインド
		pDevice->SetStreamSource(0, g_pD3DVtxBuffStart, 0, sizeof(VERTEX_2D));

		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		// テクスチャの設定
		pDevice->SetTexture(0, g_pD3DTextureStart);

		// ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
	}

	if (g_bStamp == true)
	{
		// 頂点バッファをデバイスのデータストリームにバインド
		pDevice->SetStreamSource(0, g_pD3DVtxBuffStamp, 0, sizeof(VERTEX_2D));

		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		// テクスチャの設定
		pDevice->SetTexture(0, g_pD3DTextureStamp);

		// ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
	}

}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexTitlelogo(LPDIRECT3DDEVICE9 pDevice)
{
	// オブジェクトの頂点バッファを生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,	// 頂点データ用に確保するバッファサイズ(バイト単位)
		D3DUSAGE_WRITEONLY,			// 頂点バッファの使用法　
		FVF_VERTEX_2D,				// 使用する頂点フォーマット
		D3DPOOL_MANAGED,			// リソースのバッファを保持するメモリクラスを指定
		&g_pD3DVtxBuffTitle,		// 頂点バッファインターフェースへのポインタ
		NULL)))						// NULLに設定
	{
		return E_FAIL;
	}

	{//頂点バッファの中身を埋める
		VERTEX_2D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

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
		g_pD3DVtxBuffTitle->Unlock();
	}
	//ロゴ==========================================

	// オブジェクトの頂点バッファを生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,	// 頂点データ用に確保するバッファサイズ(バイト単位)
		D3DUSAGE_WRITEONLY,			// 頂点バッファの使用法　
		FVF_VERTEX_2D,				// 使用する頂点フォーマット
		D3DPOOL_MANAGED,			// リソースのバッファを保持するメモリクラスを指定
		&g_pD3DVtxBuffTitleLogo,	// 頂点バッファインターフェースへのポインタ
		NULL)))						// NULLに設定
	{
		return E_FAIL;
	}

	{//頂点バッファの中身を埋める
		VERTEX_2D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffTitleLogo->Lock(0, 0, (void**)&pVtx, 0);

		// 頂点座標の設定
		pVtx[0].vtx = D3DXVECTOR3(TITLE_LOGO_POS_X, TITLE_LOGO_POS_Y, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(TITLE_LOGO_POS_X + TITLE_LOGO_WIDTH, TITLE_LOGO_POS_Y, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(TITLE_LOGO_POS_X, TITLE_LOGO_POS_Y + TITLE_LOGO_HEIGHT, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(TITLE_LOGO_POS_X + TITLE_LOGO_WIDTH, TITLE_LOGO_POS_Y + TITLE_LOGO_HEIGHT, 0.0f);

		// テクスチャのパースペクティブコレクト用
		pVtx[0].rhw =
			pVtx[1].rhw =
			pVtx[2].rhw =
			pVtx[3].rhw = 1.0f;

		// 反射光の設定
		pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fAlphaLogo);
		pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fAlphaLogo);
		pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fAlphaLogo);
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fAlphaLogo);

		// テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		// 頂点データをアンロックする
		g_pD3DVtxBuffTitleLogo->Unlock();
	}

	//スタート===========================================

	// オブジェクトの頂点バッファを生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,	// 頂点データ用に確保するバッファサイズ(バイト単位)
		D3DUSAGE_WRITEONLY,			// 頂点バッファの使用法　
		FVF_VERTEX_2D,				// 使用する頂点フォーマット
		D3DPOOL_MANAGED,			// リソースのバッファを保持するメモリクラスを指定
		&g_pD3DVtxBuffStart,		// 頂点バッファインターフェースへのポインタ
		NULL)))						// NULLに設定
	{
		return E_FAIL;
	}

	{//頂点バッファの中身を埋める
		VERTEX_2D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffStart->Lock(0, 0, (void**)&pVtx, 0);

		// 頂点座標の設定
		pVtx[0].vtx = D3DXVECTOR3(START_POS_X, START_POS_Y, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(START_POS_X + START_WIDTH, START_POS_Y, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(START_POS_X, START_POS_Y + START_HEIGHT, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(START_POS_X + START_WIDTH, START_POS_Y + START_HEIGHT, 0.0f);

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
		g_pD3DVtxBuffStart->Unlock();
	}

	// スタンプ==============================

	// オブジェクトの頂点バッファを生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,	// 頂点データ用に確保するバッファサイズ(バイト単位)
		D3DUSAGE_WRITEONLY,			// 頂点バッファの使用法　
		FVF_VERTEX_2D,				// 使用する頂点フォーマット
		D3DPOOL_MANAGED,			// リソースのバッファを保持するメモリクラスを指定
		&g_pD3DVtxBuffStamp,		// 頂点バッファインターフェースへのポインタ
		NULL)))						// NULLに設定
	{
		return E_FAIL;
	}

	{//頂点バッファの中身を埋める
		VERTEX_2D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffStamp->Lock(0, 0, (void**)&pVtx, 0);

		// 頂点座標の設定
		pVtx[0].vtx.x = STAMP_POS_X - cosf(BaseAngle +ROT_STAMP) * Radius;
		pVtx[0].vtx.y = STAMP_POS_Y - sinf(BaseAngle +ROT_STAMP) * Radius;
		pVtx[0].vtx.z = 0.0f;

		pVtx[1].vtx.x = STAMP_POS_X + cosf(BaseAngle- ROT_STAMP) *Radius;
		pVtx[1].vtx.y = STAMP_POS_Y - sinf(BaseAngle-ROT_STAMP) *Radius;
		pVtx[1].vtx.z = 0.0f;

		pVtx[2].vtx.x = STAMP_POS_X - cosf(BaseAngle-ROT_STAMP) *Radius;
		pVtx[2].vtx.y = STAMP_POS_Y + sinf(BaseAngle-ROT_STAMP) *Radius;
		pVtx[2].vtx.z = 0.0f;

		pVtx[3].vtx.x = STAMP_POS_X + cosf(BaseAngle+ ROT_STAMP) *Radius;
		pVtx[3].vtx.y = STAMP_POS_Y + sinf(BaseAngle+ ROT_STAMP) *Radius;
		pVtx[3].vtx.z = 0.0f;


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
		g_pD3DVtxBuffStamp->Unlock();
	}

	return S_OK;
}


//=============================================================================
// 頂点の作成
//=============================================================================
void SetColorTitleLogo(void)
{
	{//頂点バッファの中身を埋める
		VERTEX_2D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffTitleLogo->Lock(0, 0, (void**)&pVtx, 0);

		// 反射光の設定
		pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fAlphaLogo);
		pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fAlphaLogo);
		pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fAlphaLogo);
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fAlphaLogo);



		// 頂点データをアンロックする
		g_pD3DVtxBuffTitleLogo->Unlock();
	}

}
