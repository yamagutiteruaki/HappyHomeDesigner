//=============================================================================
//
// 地面処理 [field.cpp]
// Author : GP11B243　32 山口輝明
//
//=============================================================================
#include "field.h"
#include "debugproc.h"
#include "calculate.h"
#include "input.h"
#include "stage.h"

/* Debug */
#ifdef _DEBUG
#include "debugproc.h"
#endif

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

HRESULT MakeVertexField(LPDIRECT3DDEVICE9 pDevice);



//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureField = NULL;	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffField = NULL;	// 頂点バッファへのポインタ

LPDIRECT3DTEXTURE9		g_pD3DTextureHome = NULL;	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffHome = NULL;	// 頂点バッファへのポインタ

FIELD					g_aField[FIELD_MAX];
HOME					g_aHome[HOME_MAX];

LPD3DXMESH			g_pD3DXMeshHome[HOMECOUNT_MAX];			// ID3DXMeshインターフェイスへのポインタ
LPD3DXBUFFER		g_pD3DXBuffMatHome[HOMECOUNT_MAX];		// メッシュのマテリアル情報を格納
DWORD				g_nNumMatHome[HOMECOUNT_MAX];				// 属性情報の総数

const char *FileNameHome[HOMECOUNT_MAX] =
{
	"data/TEXTURE/field001.jpg",		// 家1
	"data/TEXTURE/field001.jpg",		// 家2
	"data/TEXTURE/field001.jpg",		// 家3
	"data/TEXTURE/field002.jpg",		// 自宅
};

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitField(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	FIELD *field = GetField(0);
	HOME  *home = GetHome(0);
	{
		MakeVertexField(pDevice);

		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,					// デバイスへのポインタ
			TEXTURE_FIELD,			// ファイルの名前
			&g_pD3DTextureField);	// 読み込むメモリー
									// テクスチャの読み込み

		D3DXCreateTextureFromFile(pDevice,					// デバイスへのポインタ
			TEXTURE_HOME,			// ファイルの名前
			&g_pD3DTextureHome);	// 読み込むメモリー
									// テクスチャの読み込み

	}


	for (int i = 0; i < FIELD_MAX; i++, field++)
	{
		field->Pos.x =0.0f;	//X座標の設定
		field->Pos.y = 0.0f;//Y座標は0固定
		field->Pos.z =0.0f;	//Z座標の設定

	}

	for (int i = 0; i < HOME_MAX; i++, home++)
	{
		home->Pos.x = -150.0f+i%2*300;	//X座標の設定
		home->Pos.y = 0.0f;//Y座標の設定
		home->Pos.z = 150.0f + i / 2 * (-300);	//Z座標の設定

	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitField(void)
{
	//フィールド
	if (g_pD3DTextureField != NULL)
	{// テクスチャの開放
		g_pD3DTextureField->Release();
		g_pD3DTextureField = NULL;
	}

	if (g_pD3DVtxBuffField != NULL)
	{// 頂点バッファの開放
		g_pD3DVtxBuffField->Release();
		g_pD3DVtxBuffField = NULL;
	}


	//家
	for ( int i=0; i < HOMECOUNT_MAX; i++)
	{
		if (g_pD3DTextureHome != NULL)
		{// テクスチャの開放
			g_pD3DTextureHome->Release();
			g_pD3DTextureHome = NULL;
		}

		if (g_pD3DVtxBuffHome != NULL)
		{// 頂点バッファの開放
			g_pD3DVtxBuffHome->Release();
			g_pD3DVtxBuffHome = NULL;
		}
	}

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateField(void)
{
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawField(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTranslate;
	FIELD *field = GetField(0);
	for (int i = 0; i < FIELD_MAX; i++, field++)
	{
		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&field->world);


		// 移動を反映
		D3DXMatrixTranslation(&mtxTranslate, field->Pos.x, field->Pos.y, field->Pos.z);
		D3DXMatrixMultiply(&field->world, &field->world, &mtxTranslate);

		// ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &field->world);

		// 頂点バッファをデバイスのデータストリームにバインド
		pDevice->SetStreamSource(0, g_pD3DVtxBuffField, 0, sizeof(VERTEX_3D));

		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_3D);

		// テクスチャの設定
		pDevice->SetTexture(0, g_pD3DTextureField);

		// ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * 4, NUM_POLYGON);
	}

	HOME *home = GetHome(0);
	for (int i = 0; i < HOME_MAX; i++, home++)
	{
		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&home->world);


		// 移動を反映
		D3DXMatrixTranslation(&mtxTranslate, home->Pos.x, home->Pos.y, home->Pos.z);
		D3DXMatrixMultiply(&home->world, &home->world, &mtxTranslate);

		// ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &home->world);

		// 頂点バッファをデバイスのデータストリームにバインド
		pDevice->SetStreamSource(0, g_pD3DVtxBuffHome, 0, sizeof(VERTEX_3D));

		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_3D);

		// テクスチャの設定
		pDevice->SetTexture(0, g_pD3DTextureHome);

		// ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * 4, NUM_POLYGON);
	}

}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexField(LPDIRECT3DDEVICE9 pDevice)
{

	// オブジェクトの頂点バッファを生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX* FIELD_MAX,	// 頂点データ用に確保するバッファサイズ(バイト単位)
		D3DUSAGE_WRITEONLY,			// 頂点バッファの使用法　
		FVF_VERTEX_3D,				// 使用する頂点フォーマット
		D3DPOOL_MANAGED,			// リソースのバッファを保持するメモリクラスを指定
		&g_pD3DVtxBuffField,		// 頂点バッファインターフェースへのポインタ
		NULL)))						// NULLに設定
	{
		return E_FAIL;
	}
	//for (int i = 0; i < FIELD_MAX; i++)
	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffField->Lock(0, 0, (void**)&pVtx, 0);

		for (int i = 0; i < FIELD_MAX; i++, pVtx += 4)

		{

			// 頂点座標の設定
			pVtx[0].vtx = D3DXVECTOR3(-FIELD_SIZE_X / 2, 0.0f, FIELD_SIZE_Z / 2);
			pVtx[1].vtx = D3DXVECTOR3(FIELD_SIZE_X / 2, 0.0f, FIELD_SIZE_Z / 2);
			pVtx[2].vtx = D3DXVECTOR3(-FIELD_SIZE_X / 2, 0.0f, -FIELD_SIZE_Z / 2);
			pVtx[3].vtx = D3DXVECTOR3(FIELD_SIZE_X / 2, 0.0f, -FIELD_SIZE_Z / 2);

			// 法線ベクトルの設定
			pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			// 反射光の設定
			pVtx[0].diffuse =
				pVtx[1].diffuse =
				pVtx[2].diffuse =
				pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			// テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		}
		// 頂点データをアンロックする
		g_pD3DVtxBuffField->Unlock();
	}

	// オブジェクトの頂点バッファを生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX* HOME_MAX,	// 頂点データ用に確保するバッファサイズ(バイト単位)
		D3DUSAGE_WRITEONLY,			// 頂点バッファの使用法　
		FVF_VERTEX_3D,				// 使用する頂点フォーマット
		D3DPOOL_MANAGED,			// リソースのバッファを保持するメモリクラスを指定
		&g_pD3DVtxBuffHome,		// 頂点バッファインターフェースへのポインタ
		NULL)))						// NULLに設定
	{
		return E_FAIL;
	}
	//for (int i = 0; i < FIELD_MAX; i++)
	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffHome->Lock(0, 0, (void**)&pVtx, 0);

		for (int i = 0; i < HOME_MAX; i++, pVtx += 4)

		{

			// 頂点座標の設定
			pVtx[0].vtx = D3DXVECTOR3(-HOME_SIZE_X / 2, 0.0f, HOME_SIZE_Z / 2);
			pVtx[1].vtx = D3DXVECTOR3(HOME_SIZE_X / 2, 0.0f, HOME_SIZE_Z / 2);
			pVtx[2].vtx = D3DXVECTOR3(-HOME_SIZE_X / 2, 0.0f, -HOME_SIZE_Z / 2);
			pVtx[3].vtx = D3DXVECTOR3(HOME_SIZE_X / 2, 0.0f, -HOME_SIZE_Z / 2);

			// 法線ベクトルの設定
			pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			// 反射光の設定
			pVtx[0].diffuse =
				pVtx[1].diffuse =
				pVtx[2].diffuse =
				pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			// テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		}
		// 頂点データをアンロックする
		g_pD3DVtxBuffField->Unlock();
	}


	return S_OK;
}

FIELD *GetField(int no)
{
	return &g_aField[no];
}

HOME *GetHome(int no)
{
	return &g_aHome[no];
}