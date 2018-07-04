//=============================================================================
//
// ミニマップ処理 [minimap.cpp]
// Author : GP12A295-19-千坂浩太
//
//=============================================================================
#include "main.h"
#include "minimap.h"
#include "input.h"
#include "fade.h"
#include "stage.h"
#include "calculate.h"
#include "debugproc.h"
#include "player.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexMinimap(void);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureMinimapField = NULL;		// テクスチャへのポリゴン
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffMinimapField = NULL;		// 頂点バッファインターフェースへのポインタ
MINIMAP					minimapWk[MINIMAP_MAX];					// ミニマップ構造体

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitMinimap(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	MINIMAP *minimap = &minimapWk[0];												// ミニマップのポインターを初期化
	
	// ミニマップの初期化処理
	if (type == STAGE_INIT_FAST)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,											// デバイスのポインタ
			TEXTURE_MINIMAP_FIELD,													// ファイルの名前
			&g_pD3DTextureMinimapField);											// 読み込むメモリのポインタ
		// フィールド
		for (int i = 0; i < MINIMAP_MAX; i++, minimap++)
		{
			minimap->use = true;													// 使用
			minimap->pos = D3DXVECTOR3(MINIMAP_POS_X, MINIMAP_POS_Y, 0.0f);			// 座標データを初期化
			minimap->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);							// 回転データを初期化
			MakeVertexMinimap();													// 頂点情報の作成
		}

	}


	return S_OK;
}
//=============================================================================
// 終了処理
//=============================================================================
void UninitMinimap(void)
{
	if (g_pD3DTextureMinimapField != NULL)
	{	// テクスチャの開放
		g_pD3DTextureMinimapField->Release();
		g_pD3DTextureMinimapField = NULL;
	}
	if (g_pD3DVtxBuffMinimapField != NULL)
	{	// 頂点バッファの開放
		g_pD3DVtxBuffMinimapField->Release();
		g_pD3DVtxBuffMinimapField = NULL;
	}
}
//=============================================================================
// 更新処理
//=============================================================================
void UpdateMinimap(void)
{
	MINIMAP *minimap = &minimapWk[0];				// ミニマップのポインターを初期化

}
//=============================================================================
// 描画処理
//=============================================================================
void DrawMinimap(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	MINIMAP *minimap = &minimapWk[0];				// ミニマップのポインターを初期化

	for (int i = 0; i < MINIMAP_MAX; i++, minimap++)
	{
		if (minimap->use == true)					// 使用している状態なら描画する
		{
			// 頂点バッファをデバイスのデータストリームにバインド
			pDevice->SetStreamSource(0, g_pD3DVtxBuffMinimapField, 0, sizeof(VERTEX_2D));
			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_2D);
			// テクスチャの設定
			pDevice->SetTexture(0, g_pD3DTextureMinimapField);
			// ポリゴンの描画
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_MINIMAP, minimap->vertexWk, sizeof(VERTEX_2D));
		}
	}
	

}
//=============================================================================
// ミニマップ取得関数
//=============================================================================
MINIMAP *GetMinimap(int no)
{
	return(&minimapWk[no]);
}
//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexMinimap(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ミニマップフィールド描画
	// オブジェクトの頂点バッファを生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,	// 頂点データ用に確保するバッファサイズ(バイト単位)
		D3DUSAGE_WRITEONLY,													// 頂点バッファの使用法　
		FVF_VERTEX_2D,														// 使用する頂点フォーマット
		D3DPOOL_MANAGED,													// リソースのバッファを保持するメモリクラスを指定
		&g_pD3DVtxBuffMinimapField,											// 頂点バッファインターフェースへのポインタ
		NULL)))																// NULLに設定
	{
		return E_FAIL;
	}
	//頂点バッファの中身を埋める
	VERTEX_2D *pVtx;
	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	g_pD3DVtxBuffMinimapField->Lock(0, 0, (void**)&pVtx, 0);
	// 頂点座標の設定
	pVtx[0].vtx = D3DXVECTOR3(MINIMAP_POS_X - MINIMAP_WIDTH, MINIMAP_POS_Y - MINIMAP_HEIGHT, 0.0f);
	pVtx[1].vtx = D3DXVECTOR3(MINIMAP_POS_X + MINIMAP_WIDTH, MINIMAP_POS_Y - MINIMAP_HEIGHT, 0.0f);
	pVtx[2].vtx = D3DXVECTOR3(MINIMAP_POS_X - MINIMAP_WIDTH, MINIMAP_POS_Y + MINIMAP_HEIGHT, 0.0f);
	pVtx[3].vtx = D3DXVECTOR3(MINIMAP_POS_X + MINIMAP_WIDTH, MINIMAP_POS_Y + MINIMAP_HEIGHT, 0.0f);
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
	g_pD3DVtxBuffMinimapField->Unlock();


	return S_OK;
}
//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexPlayerPoint(int no)
{
	PLAYER *player = GetPlayer(0);
	MINIMAP *minimap = &minimapWk[0];				// ミニマップのポインターを初期化

	// 頂点座標の設定
	//player->vertexWk[0].vtx.x = player->pos.x - cosf(player->BaseAngle + player->rot.z) * player->Radius;
	//player->vertexWk[0].vtx.y = player->pos.y - sinf(player->BaseAngle + player->rot.z) * player->Radius;
	//player->vertexWk[0].vtx.z = 0.0f;

	//player->vertexWk[1].vtx.x = player->pos.x + cosf(player->BaseAngle - player->rot.z) * player->Radius;
	//player->vertexWk[1].vtx.y = player->pos.y - sinf(player->BaseAngle - player->rot.z) * player->Radius;
	//player->vertexWk[1].vtx.z = 0.0f;

	//player->vertexWk[2].vtx.x = player->pos.x - cosf(player->BaseAngle - player->rot.z) * player->Radius;
	//player->vertexWk[2].vtx.y = player->pos.y + sinf(player->BaseAngle - player->rot.z) * player->Radius;
	//player->vertexWk[2].vtx.z = 0.0f;

	//player->vertexWk[3].vtx.x = player->pos.x + cosf(player->BaseAngle + player->rot.z) * player->Radius;
	//player->vertexWk[3].vtx.y = player->pos.y + sinf(player->BaseAngle + player->rot.z) * player->Radius;
	//player->vertexWk[3].vtx.z = 0.0f;
}
