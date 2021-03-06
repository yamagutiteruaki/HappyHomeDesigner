//=============================================================================
//
// ミニマップ処理 [miniField.cpp]
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
#include "police.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexMinimap(void);
void SetVertexPlayerPoint(void);
void SetVertexPolicePoint(void);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
// ミニマップフレーム用
LPDIRECT3DTEXTURE9		g_pD3DTextureMinimapFrame = NULL;		// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffMinimapFrame = NULL;		// 頂点バッファインターフェースへのポインタ
MINI_FRAME				miniFrameWk[MINIMAP_FRAME_MAX];			// ミニマップフィールド構造体配列
// ミニマップフィールド用
LPDIRECT3DTEXTURE9		g_pD3DTextureMinimapField = NULL;		// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffMinimapField = NULL;		// 頂点バッファインターフェースへのポインタ
MINI_FIELD				miniFieldWk[MINIMAP_FIELD_MAX];			// ミニマップフィールド構造体配列
// ミニマッププレイヤー座標用
LPDIRECT3DTEXTURE9		g_pD3DTextureMinimapPlayer = NULL;		// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffMinimapPlayer = NULL;		// 頂点バッファインターフェースへのポインタ
MINI_PLAYER				miniPlayerWk[MINIMAP_PLAYER_MAX];		// ミニマッププレイヤー構造体配列
// ミニマップポリス座標用
LPDIRECT3DTEXTURE9		g_pD3DTextureMinimapPolice = NULL;		// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffMinimapPolice = NULL;		// 頂点バッファインターフェースへのポインタ
MINI_POLICE				miniPoliceWk[MINIMAP_POLICE_MAX];		// ミニマップポリス構造体配列
// その他

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitMinimap(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	MINI_FRAME *miniFrame = &miniFrameWk[0];										// ミニマップフレームのポインター初期化
	MINI_FIELD *miniField = &miniFieldWk[0];										// ミニマップフィールドのポインター初期化
	MINI_PLAYER *miniPlayer = &miniPlayerWk[0];										// ミニマッププレイヤーのポインター初期化
	MINI_POLICE *miniPolice = &miniPoliceWk[0];										// ミニマップポリスのポインター初期化

	if (type == STAGE_INIT_FAST)
	{
		// テクスチャの読み込み
		// ミニマップフレーム
		D3DXCreateTextureFromFile(pDevice,											// デバイスのポインタ
			TEXTURE_MINIMAP_FRAME,													// ファイルの名前
			&g_pD3DTextureMinimapFrame);											// 読み込むメモリのポインタ
		// ミニマップフィールド
		D3DXCreateTextureFromFile(pDevice,											// デバイスのポインタ
			TEXTURE_MINIMAP_FIELD,													// ファイルの名前
			&g_pD3DTextureMinimapField);											// 読み込むメモリのポインタ
		// ミニマッププレイヤー座標
		D3DXCreateTextureFromFile(pDevice,											// デバイスのポインタ
			TEXTURE_MINIMAP_PLAYER,													// ファイルの名前
			&g_pD3DTextureMinimapPlayer);											// 読み込むメモリのポインタ
		// ミニマップポリス座標
		D3DXCreateTextureFromFile(pDevice,											// デバイスのポインタ
			TEXTURE_MINIMAP_POLICE,													// ファイルの名前
			&g_pD3DTextureMinimapPolice);											// 読み込むメモリのポインタ
	}
	// ミニマップフレームの初期化処理
	for (int i = 0; i < MINIMAP_FRAME_MAX; i++, miniFrame++)
	{
		miniFrame->use = true;														// 使用
	}
	// ミニマップフィールドの初期化処理
	for (int i = 0; i < MINIMAP_FIELD_MAX; i++, miniField++)
	{
		miniField->use = true;														// 使用
	}
	// ミニマッププレイヤーの初期化処理
	for (int i = 0; i < MINIMAP_PLAYER_MAX; i++, miniPlayer++)
	{
		miniPlayer->use = true;														// 使用
		miniPlayer->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);							// ミニマッププレイヤー座標の初期化
		miniPlayer->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);							// ミニマッププレイヤー回転の初期化
	}
	// ミニマップポリスの初期化処理
	for (int i = 0; i < MINIMAP_POLICE_MAX; i++, miniPolice++)
	{
		miniPolice->use = true;														// 使用
		miniPolice->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);							// ミニマップポリス座標の初期化
		miniPolice->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);							// ミニマップポリス回転の初期化
	}

	MakeVertexMinimap();															// 頂点情報の作成

	return S_OK;
}
//=============================================================================
// 終了処理
//=============================================================================
void UninitMinimap(void)
{
	// ミニマップフレーム
	if (g_pD3DTextureMinimapFrame != NULL)
	{	// テクスチャの開放
		g_pD3DTextureMinimapFrame->Release();
		g_pD3DTextureMinimapFrame = NULL;
	}
	if (g_pD3DVtxBuffMinimapFrame != NULL)
	{	// 頂点バッファの開放
		g_pD3DVtxBuffMinimapFrame->Release();
		g_pD3DVtxBuffMinimapFrame = NULL;
	}
	// ミニマップフィールド
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
	// ミニマッププレイヤー座標
	if (g_pD3DTextureMinimapPlayer != NULL)
	{	// テクスチャの開放
		g_pD3DTextureMinimapPlayer->Release();
		g_pD3DTextureMinimapPlayer = NULL;
	}
	if (g_pD3DVtxBuffMinimapPlayer != NULL)
	{	// 頂点バッファの開放
		g_pD3DVtxBuffMinimapPlayer->Release();
		g_pD3DVtxBuffMinimapPlayer = NULL;
	}
	// ミニマップポリス座標
	if (g_pD3DTextureMinimapPolice != NULL)
	{	// テクスチャの開放
		g_pD3DTextureMinimapPolice->Release();
		g_pD3DTextureMinimapPolice = NULL;
	}
	if (g_pD3DVtxBuffMinimapPolice != NULL)
	{	// 頂点バッファの開放
		g_pD3DVtxBuffMinimapPolice->Release();
		g_pD3DVtxBuffMinimapPolice = NULL;
	}

}
//=============================================================================
// 更新処理
//=============================================================================
void UpdateMinimap(void)
{
	SetVertexPlayerPoint();								// ミニマッププレイヤの座標更新
	SetVertexPolicePoint();								// ミニマップポリスの座標更新
}
//=============================================================================
// 描画処理
//=============================================================================
void DrawMinimap(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	MINI_FRAME *miniFrame = &miniFrameWk[0];				// ミニマップフレームのポインター初期化
	MINI_FIELD *miniField = &miniFieldWk[0];				// ミニマップのポインターを初期化
	MINI_PLAYER *miniPlayer = &miniPlayerWk[0];				// ミニマッププレイヤーのポインター初期化
	MINI_POLICE *miniPolice = &miniPoliceWk[0];				// ミニマップポリスのポインター初期化

	// ミニマップフィールド描画
	for (int i = 0; i < MINIMAP_FIELD_MAX; i++, miniField++)
	{
		if (miniField->use == true)					// 使用している状態なら描画する
		{
			// 頂点バッファをデバイスのデータストリームにバインド
			pDevice->SetStreamSource(0, g_pD3DVtxBuffMinimapField, 0, sizeof(VERTEX_2D));
			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_2D);
			// テクスチャの設定
			pDevice->SetTexture(0, g_pD3DTextureMinimapField);
			// ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

		}
	}
	// ミニマップフレーム描画
	for (int i = 0; i < MINIMAP_FRAME_MAX; i++, miniFrame++)
	{
		if (miniFrame->use == true)					// 使用している状態なら描画する
		{
			// 頂点バッファをデバイスのデータストリームにバインド
			pDevice->SetStreamSource(0, g_pD3DVtxBuffMinimapFrame, 0, sizeof(VERTEX_2D));
			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_2D);
			// テクスチャの設定
			pDevice->SetTexture(0, g_pD3DTextureMinimapFrame);
			// ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

		}
	}

	// ミニマッププレイヤ描画
	for (int i = 0; i < MINIMAP_PLAYER_MAX; i++, miniPlayer++)
	{
		if (miniPlayer->use == true)					// 使用している状態なら描画する
		{
			// 頂点バッファをデバイスのデータストリームにバインド
			pDevice->SetStreamSource(0, g_pD3DVtxBuffMinimapPlayer, 0, sizeof(VERTEX_2D));
			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_2D);
			// テクスチャの設定
			pDevice->SetTexture(0, g_pD3DTextureMinimapPlayer);
			// ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
		}
	}
	// ミニマップポリス描画
	for (int i = 0; i < MINIMAP_POLICE_MAX; i++)
	{
		if (miniPolice->use == true)					// 使用している状態なら描画する
		{
			// 頂点バッファをデバイスのデータストリームにバインド
			pDevice->SetStreamSource(0, g_pD3DVtxBuffMinimapPolice, 0, sizeof(VERTEX_2D));
			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_2D);
			// テクスチャの設定
			pDevice->SetTexture(0, g_pD3DTextureMinimapPolice);
			// ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i*4, NUM_POLYGON);
		}
	}

}
//=============================================================================
// ミニマップフィールド取得関数
//=============================================================================
MINI_FIELD *GetMiniField(int no)
{
	return(&miniFieldWk[no]);
}
//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexMinimap(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ミニマップフレーム
	// オブジェクトの頂点バッファを生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,	// 頂点データ用に確保するバッファサイズ(バイト単位)
		D3DUSAGE_WRITEONLY,													// 頂点バッファの使用法　
		FVF_VERTEX_2D,														// 使用する頂点フォーマット
		D3DPOOL_MANAGED,													// リソースのバッファを保持するメモリクラスを指定
		&g_pD3DVtxBuffMinimapFrame,											// 頂点バッファインターフェースへのポインタ
		NULL)))																// NULLに設定
	{
		return E_FAIL;
	}
	{
		VERTEX_2D *pVtx;
		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffMinimapFrame->Lock(0, 0, (void**)&pVtx, 0);
		// 頂点座標の設定
		pVtx[0].vtx = D3DXVECTOR3(MINIMAP_FRAME_POS_X - TEXTURE_MINIMAP_FRAME_SIZE_X, MINIMAP_FRAME_POS_Y - TEXTURE_MINIMAP_FRAME_SIZE_Y, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(MINIMAP_FRAME_POS_X + TEXTURE_MINIMAP_FRAME_SIZE_X, MINIMAP_FRAME_POS_Y - TEXTURE_MINIMAP_FRAME_SIZE_Y, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(MINIMAP_FRAME_POS_X - TEXTURE_MINIMAP_FRAME_SIZE_X, MINIMAP_FRAME_POS_Y + TEXTURE_MINIMAP_FRAME_SIZE_Y, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(MINIMAP_FRAME_POS_X + TEXTURE_MINIMAP_FRAME_SIZE_X, MINIMAP_FRAME_POS_Y + TEXTURE_MINIMAP_FRAME_SIZE_Y, 0.0f);
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
		g_pD3DVtxBuffMinimapFrame->Unlock();
	}
	// ミニマップフィールド
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
	{
		VERTEX_2D *pVtx;
		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffMinimapField->Lock(0, 0, (void**)&pVtx, 0);
		// 頂点座標の設定
		pVtx[0].vtx = D3DXVECTOR3(MINIMAP_FIELD_POS_X - TEXTURE_MINIMAP_FIELD_SIZE_X, MINIMAP_FIELD_POS_Y - TEXTURE_MINIMAP_FIELD_SIZE_Y, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(MINIMAP_FIELD_POS_X + TEXTURE_MINIMAP_FIELD_SIZE_X, MINIMAP_FIELD_POS_Y - TEXTURE_MINIMAP_FIELD_SIZE_Y, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(MINIMAP_FIELD_POS_X - TEXTURE_MINIMAP_FIELD_SIZE_X, MINIMAP_FIELD_POS_Y + TEXTURE_MINIMAP_FIELD_SIZE_Y, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(MINIMAP_FIELD_POS_X + TEXTURE_MINIMAP_FIELD_SIZE_X, MINIMAP_FIELD_POS_Y + TEXTURE_MINIMAP_FIELD_SIZE_Y, 0.0f);
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
	}
	// ミニマッププレイヤー座標
	// オブジェクトの頂点バッファを生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,	// 頂点データ用に確保するバッファサイズ(バイト単位)
		D3DUSAGE_WRITEONLY,													// 頂点バッファの使用法　
		FVF_VERTEX_2D,														// 使用する頂点フォーマット
		D3DPOOL_MANAGED,													// リソースのバッファを保持するメモリクラスを指定
		&g_pD3DVtxBuffMinimapPlayer,											// 頂点バッファインターフェースへのポインタ
		NULL)))																// NULLに設定
	{
		return E_FAIL;
	}
	{
		VERTEX_2D *pVtx;
		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffMinimapPlayer->Lock(0, 0, (void**)&pVtx, 0);
		// 頂点座標の設定
		pVtx[0].vtx = D3DXVECTOR3(MINIMAP_PLAYER_POS_X - TEXTURE_MINIMAP_PLAYER_SIZE_X, MINIMAP_PLAYER_POS_Y - TEXTURE_MINIMAP_PLAYER_SIZE_Y, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(MINIMAP_PLAYER_POS_X + TEXTURE_MINIMAP_PLAYER_SIZE_X, MINIMAP_PLAYER_POS_Y - TEXTURE_MINIMAP_PLAYER_SIZE_Y, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(MINIMAP_PLAYER_POS_X - TEXTURE_MINIMAP_PLAYER_SIZE_X, MINIMAP_PLAYER_POS_Y + TEXTURE_MINIMAP_PLAYER_SIZE_Y, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(MINIMAP_PLAYER_POS_X + TEXTURE_MINIMAP_PLAYER_SIZE_X, MINIMAP_PLAYER_POS_Y + TEXTURE_MINIMAP_PLAYER_SIZE_Y, 0.0f);
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
		g_pD3DVtxBuffMinimapPlayer->Unlock();
	}
	// ミニマップポリス座標
	{
		// オブジェクトの頂点バッファを生成
		if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX*MINIMAP_POLICE_MAX,	// 頂点データ用に確保するバッファサイズ(バイト単位)
			D3DUSAGE_WRITEONLY,													// 頂点バッファの使用法　
			FVF_VERTEX_2D,														// 使用する頂点フォーマット
			D3DPOOL_MANAGED,													// リソースのバッファを保持するメモリクラスを指定
			&g_pD3DVtxBuffMinimapPolice,											// 頂点バッファインターフェースへのポインタ
			NULL)))																// NULLに設定
		{
			return E_FAIL;
		}

		VERTEX_2D *pVtx;
		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffMinimapPolice->Lock(0, 0, (void**)&pVtx, 0);
		for (int i = 0; i < MINIMAP_POLICE_MAX; i++, pVtx += 4)
		{
			// 頂点座標の設定
			pVtx[0].vtx = D3DXVECTOR3(MINIMAP_POLICE_POS_X - TEXTURE_MINIMAP_POLICE_SIZE_X, MINIMAP_POLICE_POS_Y - TEXTURE_MINIMAP_POLICE_SIZE_Y, 0.0f);
			pVtx[1].vtx = D3DXVECTOR3(MINIMAP_POLICE_POS_X + TEXTURE_MINIMAP_POLICE_SIZE_X, MINIMAP_POLICE_POS_Y - TEXTURE_MINIMAP_POLICE_SIZE_Y, 0.0f);
			pVtx[2].vtx = D3DXVECTOR3(MINIMAP_POLICE_POS_X - TEXTURE_MINIMAP_POLICE_SIZE_X, MINIMAP_POLICE_POS_Y + TEXTURE_MINIMAP_POLICE_SIZE_Y, 0.0f);
			pVtx[3].vtx = D3DXVECTOR3(MINIMAP_POLICE_POS_X + TEXTURE_MINIMAP_POLICE_SIZE_X, MINIMAP_POLICE_POS_Y + TEXTURE_MINIMAP_POLICE_SIZE_Y, 0.0f);
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
		}
		// 頂点データをアンロックする
		g_pD3DVtxBuffMinimapPolice->Unlock();
	}
	return S_OK;
}
//=============================================================================
// ミニマップ内プレイヤー頂点座標の設定
//=============================================================================
void SetVertexPlayerPoint(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	PLAYER *player = GetPlayer(0);
	VERTEX_2D *pVtx;

	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	g_pD3DVtxBuffMinimapPlayer->Lock(0, 0, (void**)&pVtx, 0);

	// ミニマッププレイヤー座標
	// 頂点座標の設定
	pVtx[0].vtx.x = (player->Eye.x * MINIMAP_FIELD_SCALE) - TEXTURE_MINIMAP_PLAYER_SIZE_X + MINIMAP_FIELD_POS_X ;
	pVtx[0].vtx.y = (-player->Eye.z * MINIMAP_FIELD_SCALE) - TEXTURE_MINIMAP_PLAYER_SIZE_Y + MINIMAP_FIELD_POS_Y - MINIMAP_PLAYER_RANGE;
	pVtx[0].vtx.z = 0.0f;

	pVtx[1].vtx.x = (player->Eye.x * MINIMAP_FIELD_SCALE) + TEXTURE_MINIMAP_PLAYER_SIZE_X + MINIMAP_FIELD_POS_X ;
	pVtx[1].vtx.y = (-player->Eye.z * MINIMAP_FIELD_SCALE) - TEXTURE_MINIMAP_PLAYER_SIZE_Y + MINIMAP_FIELD_POS_Y - MINIMAP_PLAYER_RANGE;
	pVtx[1].vtx.z = 0.0f;

	pVtx[2].vtx.x = (player->Eye.x * MINIMAP_FIELD_SCALE) - TEXTURE_MINIMAP_PLAYER_SIZE_X + MINIMAP_FIELD_POS_X ;
	pVtx[2].vtx.y = (-player->Eye.z * MINIMAP_FIELD_SCALE) + TEXTURE_MINIMAP_PLAYER_SIZE_Y + MINIMAP_FIELD_POS_Y - MINIMAP_PLAYER_RANGE;
	pVtx[2].vtx.z = 0.0f;

	pVtx[3].vtx.x = (player->Eye.x * MINIMAP_FIELD_SCALE) + TEXTURE_MINIMAP_PLAYER_SIZE_X + MINIMAP_FIELD_POS_X ;
	pVtx[3].vtx.y = (-player->Eye.z * MINIMAP_FIELD_SCALE) + TEXTURE_MINIMAP_PLAYER_SIZE_Y + MINIMAP_FIELD_POS_Y - MINIMAP_PLAYER_RANGE;
	pVtx[3].vtx.z = 0.0f;

	// 頂点データをアンロックする
	g_pD3DVtxBuffMinimapPlayer->Unlock();
}
//=============================================================================
// ミニマップ内ポリス頂点座標の設定
//=============================================================================
void SetVertexPolicePoint(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	POLICE *police = GetPolice(0);
	VERTEX_2D *pVtx;

	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	g_pD3DVtxBuffMinimapPolice->Lock(0, 0, (void**)&pVtx, 0);

	// ミニマップポリス座標
	for (int i = 0; i < MINIMAP_POLICE_MAX; i++,police++,pVtx += 4)
	{
		// 頂点座標の設定
		pVtx[0].vtx.x = (police->Eye.x * MINIMAP_FIELD_SCALE) - TEXTURE_MINIMAP_POLICE_SIZE_X + MINIMAP_FIELD_POS_X;
		pVtx[0].vtx.y = (-police->Eye.z * MINIMAP_FIELD_SCALE) - TEXTURE_MINIMAP_POLICE_SIZE_Y + MINIMAP_FIELD_POS_Y - MINIMAP_POLICE_RANGE;
		pVtx[0].vtx.z = 0.0f;

		pVtx[1].vtx.x = (police->Eye.x * MINIMAP_FIELD_SCALE) + TEXTURE_MINIMAP_POLICE_SIZE_X + MINIMAP_FIELD_POS_X;
		pVtx[1].vtx.y = (-police->Eye.z * MINIMAP_FIELD_SCALE) - TEXTURE_MINIMAP_POLICE_SIZE_Y + MINIMAP_FIELD_POS_Y - MINIMAP_POLICE_RANGE;
		pVtx[1].vtx.z = 0.0f;

		pVtx[2].vtx.x = (police->Eye.x * MINIMAP_FIELD_SCALE) - TEXTURE_MINIMAP_POLICE_SIZE_X + MINIMAP_FIELD_POS_X;
		pVtx[2].vtx.y = (-police->Eye.z * MINIMAP_FIELD_SCALE) + TEXTURE_MINIMAP_POLICE_SIZE_Y + MINIMAP_FIELD_POS_Y - MINIMAP_POLICE_RANGE;
		pVtx[2].vtx.z = 0.0f;

		pVtx[3].vtx.x = (police->Eye.x * MINIMAP_FIELD_SCALE) + TEXTURE_MINIMAP_POLICE_SIZE_X + MINIMAP_FIELD_POS_X;
		pVtx[3].vtx.y = (-police->Eye.z * MINIMAP_FIELD_SCALE) + TEXTURE_MINIMAP_POLICE_SIZE_Y + MINIMAP_FIELD_POS_Y - MINIMAP_POLICE_RANGE;
		pVtx[3].vtx.z = 0.0f;
	}
	// 頂点データをアンロックする
	g_pD3DVtxBuffMinimapPolice->Unlock();

}
