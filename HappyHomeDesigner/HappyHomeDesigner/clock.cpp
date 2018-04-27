//=============================================================================
//
// タイマー処理 [clock.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "clock.h"
#include "input.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexClock(int no);
void SetVertexClock(int no);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureClock = NULL;		// テクスチャへのポリゴン
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffClock = NULL;		// 頂点バッファインターフェースへのポインタ


CLOCK					clockWk[CLOCK_MAX];				// タイマー構造体

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitClock(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	CLOCK *clock = clockWk;				// タイマーのポインターを初期化

	// テクスチャーの初期化を行う
	if (type == 0)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,	// デバイスのポインタ
			TEXTURE_GAME_CLOCK,				// ファイルの名前
			&g_pD3DTextureClock);			// 読み込むメモリのポインタ
	}

	// タイマーの初期化処理
	for (int i = 0; i < CLOCK_MAX; i++, clock++)
	{
		clock->use = true;										// 使用
		clock->pos = D3DXVECTOR3(150.0f, 100.0f, 0.0f);			// 座標データを初期化
		clock->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// 回転データを初期化
		clock->PatternAnim = 0;									// アニメパターン番号をランダムで初期化
		clock->CountAnim = 0;									// アニメカウントを初期化

		D3DXVECTOR2 temp = D3DXVECTOR2(TEXTURE_CLOCK_SIZE_X, TEXTURE_CLOCK_SIZE_Y);
		clock->Radius = D3DXVec2Length(&temp);					// タイマーの半径を初期化
		clock->BaseAngle =1.0f* D3DX_PI;	// タイマーの角度を初期化

		clock->Texture = g_pD3DTextureClock;					// テクスチャ情報
		MakeVertexClock(i);										// 頂点情報の作成
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
	{// 頂点バッファの開放
		g_pD3DVtxBuffClock->Release();
		g_pD3DVtxBuffClock = NULL;
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
			
				clock->rot.z -= 1.0f;
			
			SetVertexClock(i);	// 移動後の座標で頂点を設定
		}
	}

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawClock(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	CLOCK *clock = clockWk;				// タイマーのポインターを初期化

	for (int i = 0; i < CLOCK_MAX; i++, clock++)
	{
		if (clock->use == true)			// 使用している状態なら描画する
		{
			// 頂点バッファをデバイスのデータストリームにバインド
			pDevice->SetStreamSource(0, g_pD3DVtxBuffClock, 0, sizeof(VERTEX_2D));

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

	// 頂点座標の設定
	SetVertexClock(no);

	// rhwの設定
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
void SetVertexClock(int no)
{
	CLOCK *clock = &clockWk[no];			// タイマーのポインターを初期化

	// 頂点座標の設定
	clock->vertexWk[0].vtx.x = clock->pos.x - cosf(clock->BaseAngle) * clock->Radius;
	clock->vertexWk[0].vtx.y = clock->pos.y - sinf(clock->BaseAngle) * clock->Radius;
	clock->vertexWk[0].vtx.z = 0.0f;

	clock->vertexWk[1].vtx.x = clock->pos.x + cosf(clock->BaseAngle) * clock->Radius;
	clock->vertexWk[1].vtx.y = clock->pos.y - sinf(clock->BaseAngle) * clock->Radius;
	clock->vertexWk[1].vtx.z = 0.0f;

	clock->vertexWk[2].vtx.x = clock->pos.x - cosf(clock->BaseAngle) * clock->Radius;
	clock->vertexWk[2].vtx.y = clock->pos.y + sinf(clock->BaseAngle) * clock->Radius;
	clock->vertexWk[2].vtx.z = 0.0f;

	clock->vertexWk[3].vtx.x = clock->pos.x + cosf(clock->BaseAngle) * clock->Radius;
	clock->vertexWk[3].vtx.y = clock->pos.y + sinf(clock->BaseAngle) * clock->Radius;
	clock->vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// タイマー取得関数
//=============================================================================
CLOCK *GetClock(int no)
{
	return(&clockWk[no]);
}


