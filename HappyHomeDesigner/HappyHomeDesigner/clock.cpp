//=============================================================================
//
// タイマー処理 [clock.cpp]
// Author : GP12B295 ⑫ 関口昂平
//
//=============================================================================
#include "main.h"
#include "clock.h"
#include "input.h"
#include "fade.h"
#include "stage.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexClock(int no);
void SetVertexClockHand(int no);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureClock = NULL;				// テクスチャへのポリゴン
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffClock = NULL;				// 頂点バッファインターフェースへのポインタ
LPDIRECT3DTEXTURE9		g_pD3DTextureClockHand = NULL;			// テクスチャへのポリゴン
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffClockHand = NULL;			// 頂点バッファインターフェースへのポインタ


CLOCK					clockWk[CLOCK_MAX];				// タイマー構造体

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitClock(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	CLOCK *clock = clockWk;				// タイマーのポインターを初期化

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,	// デバイスのポインタ
		TEXTURE_GAME_CLOCK,				// ファイルの名前
		&g_pD3DTextureClock);			// 読み込むメモリのポインタ


	// タイマーの初期化処理
	if (type == 0)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,		// デバイスのポインタ
			TEXTURE_GAME_CLOCKHAND,				// ファイルの名前
			&g_pD3DTextureClockHand);			// 読み込むメモリのポインタ
	}

	// 針の初期化処理
	for (int i = 0; i < CLOCK_MAX; i++, clock++)
	{
		clock->use = true;										// 使用
		clock->pos = D3DXVECTOR3(CLOCK_POS_X, CLOCK_POS_Y, 0.0f);			// 座標データを初期化
		clock->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);							// 回転データを初期化
		clock->PatternAnim = 0;												// アニメパターン番号をランダムで初期化
		clock->CountAnim = 0;												// アニメカウントを初期化

		D3DXVECTOR2 temp = D3DXVECTOR2(TEXTURE_CLOCKHAND_SIZE_X, TEXTURE_CLOCKHAND_SIZE_Y);
		clock->Radius = D3DXVec2Length(&temp);					// 針の半径を初期化
		clock->BaseAngle = atan2f(TEXTURE_CLOCKHAND_SIZE_Y, TEXTURE_CLOCKHAND_SIZE_X);	// 針の角度を初期化

		clock->Texture = g_pD3DTextureClockHand;					// テクスチャ情報
		MakeVertexClock(i);											// 頂点情報の作成
	}


	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitClock(void)
{
	if (g_pD3DTextureClock != NULL)
	{	// テクスチャの開放
		g_pD3DTextureClock->Release();
		g_pD3DTextureClock = NULL;
	}

	if (g_pD3DVtxBuffClock != NULL)
	{	// 頂点バッファの開放
		g_pD3DVtxBuffClock->Release();
		g_pD3DVtxBuffClock = NULL;
	}


	if (g_pD3DTextureClockHand != NULL)
	{	// テクスチャの開放
		g_pD3DTextureClockHand->Release();
		g_pD3DTextureClockHand = NULL;
	}

	if (g_pD3DVtxBuffClockHand != NULL)
	{	// 頂点バッファの開放
		g_pD3DVtxBuffClockHand->Release();
		g_pD3DVtxBuffClockHand = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateClock(void)
{
	CLOCK *clock = clockWk;				// タイマーのポインターを初期化

	for (int i = 0; i < CLOCK_MAX; i++, clock++)
	{
		if (clock->use == true)			// 使用している状態なら更新する
		{
			// アニメーション
			
			clock->rot.z += 0.01f;
			
			SetVertexClockHand(i);		// 移動後の座標で頂点を設定

		}
		//if (clock->rot.z > D3DX_PI * 2)
		//{
		//	SetFade(FADE_OUT, STAGE_RESULT);
		//}
	}

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawClock(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	CLOCK *clock = clockWk;				// タイマーのポインターを初期化

	// 頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, g_pD3DVtxBuffClock, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pD3DTextureClock);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);


	for (int i = 0; i < CLOCK_MAX; i++, clock++)
	{
		if (clock->use == true)			// 使用している状態なら描画する
		{
			// 頂点バッファをデバイスのデータストリームにバインド
			pDevice->SetStreamSource(0, g_pD3DVtxBuffClockHand, 0, sizeof(VERTEX_2D));

			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_2D);

			// テクスチャの設定
			pDevice->SetTexture(0, clock->Texture);

			// ポリゴンの描画
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_CLOCK, clock->vertexWk, sizeof(VERTEX_2D));
		
		

		}
	}
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexClock(int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	CLOCK *clock = &clockWk[no];			// タイマーのポインターを初期化

	// オブジェクトの頂点バッファを生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,	// 頂点データ用に確保するバッファサイズ(バイト単位)
		D3DUSAGE_WRITEONLY,			// 頂点バッファの使用法　
		FVF_VERTEX_2D,				// 使用する頂点フォーマット
		D3DPOOL_MANAGED,			// リソースのバッファを保持するメモリクラスを指定
		&g_pD3DVtxBuffClock,		// 頂点バッファインターフェースへのポインタ
		NULL)))						// NULLに設定
	{
		return E_FAIL;
	}

	{//頂点バッファの中身を埋める
		VERTEX_2D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffClock->Lock(0, 0, (void**)&pVtx, 0);

		// 頂点座標の設定
		pVtx[0].vtx = D3DXVECTOR3(CLOCK_POS_X - CLOCK_WIDTH, CLOCK_POS_Y - CLOCK_HEIGHT, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(CLOCK_POS_X + CLOCK_WIDTH, CLOCK_POS_Y - CLOCK_HEIGHT, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(CLOCK_POS_X - CLOCK_WIDTH, CLOCK_POS_Y + CLOCK_HEIGHT, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(CLOCK_POS_X + CLOCK_WIDTH, CLOCK_POS_Y + CLOCK_HEIGHT, 0.0f);

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
		g_pD3DVtxBuffClock->Unlock();
	}


	// 頂点座標の設定
	SetVertexClockHand(no);

	// テクスチャのパースペクティブコレクト用
	clock->vertexWk[0].rhw =
	clock->vertexWk[1].rhw =
	clock->vertexWk[2].rhw =
	clock->vertexWk[3].rhw = 1.0f;

	// 反射光の設定
	clock->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	clock->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	clock->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	clock->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	clock->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	clock->vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	clock->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	clock->vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexClockHand(int no)
{
	CLOCK *clock = &clockWk[no];			// タイマーのポインターを初期化

	// 頂点座標の設定
	clock->vertexWk[0].vtx.x = clock->pos.x - cosf(clock->BaseAngle+clock->rot.z) * clock->Radius;
	clock->vertexWk[0].vtx.y = clock->pos.y - sinf(clock->BaseAngle + clock->rot.z) * clock->Radius;
	clock->vertexWk[0].vtx.z = 0.0f;

	clock->vertexWk[1].vtx.x = clock->pos.x + cosf(clock->BaseAngle - clock->rot.z) * clock->Radius;
	clock->vertexWk[1].vtx.y = clock->pos.y - sinf(clock->BaseAngle - clock->rot.z) * clock->Radius;
	clock->vertexWk[1].vtx.z = 0.0f;

	clock->vertexWk[2].vtx.x = clock->pos.x - cosf(clock->BaseAngle - clock->rot.z) * clock->Radius;
	clock->vertexWk[2].vtx.y = clock->pos.y + sinf(clock->BaseAngle - clock->rot.z) * clock->Radius;
	clock->vertexWk[2].vtx.z = 0.0f;

	clock->vertexWk[3].vtx.x = clock->pos.x + cosf(clock->BaseAngle + clock->rot.z) * clock->Radius;
	clock->vertexWk[3].vtx.y = clock->pos.y + sinf(clock->BaseAngle + clock->rot.z) * clock->Radius;
	clock->vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// タイマー取得関数
//=============================================================================
CLOCK *GetClock(int no)
{
	return(&clockWk[no]);
}


