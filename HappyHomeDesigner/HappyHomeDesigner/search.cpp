//=============================================================================
//
// 索敵範囲描画処理 [search.cpp]
// Author : GP12A295-19-千坂浩太
//
//=============================================================================
#include "search.h"
#include "camera.h"
#include "debugproc.h"
#include "input.h"
#include "player.h"
#include "police.h"
#include "stage.h"
#include "field.h"
#include "collision.h"
#include "calculate.h"


//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexSearch(D3DXVECTOR3 pos);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureSearch = NULL;	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffSearch = NULL;	// 頂点バッファへのポインタ

D3DXMATRIX				g_mtxWorldSearch;			// ワールドマトリックス
SEARCH					searchWk[SEARCH_MAX];		// サーチ格納ワーク

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitSearch(int nType)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice(); 
	SEARCH *search = &searchWk[0];

	if (nType == STAGE_INIT_FAST)
	{

		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,					// デバイスへのポインタ
			TEXTURE_SEARCH,			// ファイルの名前
			&g_pD3DTextureSearch);	// 読み込むメモリー
	}
		// 位置、向きの初期設定
		search->Eye = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		search->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		search->rotBasis = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		search->scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		search->axisY = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitSearch(void)
{
	if(g_pD3DTextureSearch != NULL)
	{// テクスチャの開放
		g_pD3DTextureSearch->Release();
		g_pD3DTextureSearch = NULL;
	}

	if(g_pD3DVtxBuffSearch != NULL)
	{// 頂点バッファの開放
		g_pD3DVtxBuffSearch->Release();
		g_pD3DVtxBuffSearch = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateSearch(void)
{
	POLICE *police = GetPolice(0);
	SEARCH *search = &searchWk[0];

	search->Eye.x = police->Eye.x;
	search->Eye.y = police->Eye.y + 0.1f;
	search->Eye.z = police->Eye.z;


	// 頂点の作成
	MakeVertexSearch(police->Eye);

	// Y軸回転角度をポリスと一致させる
	search->fangleY = police->fangleY;

	// 回転クォータニオンを生成
	D3DXQuaternionRotationAxis(&search->qRotateY, &search->axisY, search->fangleY);		// Y軸回転クォータニオン生成(Atに向かせる)


}

//=============================================================================
// 描画処理
//=============================================================================
void DrawSearch(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice(); 
	D3DXMATRIX mtxRot, mtxTranslate;
	SEARCH *search = &searchWk[0];

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_mtxWorldSearch);
	// ワールドマトリックス作成
	D3DXMatrixTransformation(&g_mtxWorldSearch, NULL, NULL, &search->scl, &search->rotBasis, &search->qRotateY, &search->Eye);
	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldSearch);
	// 頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, g_pD3DVtxBuffSearch, 0, sizeof(VERTEX_3D));
	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);
	// テクスチャの設定
	pDevice->SetTexture(0, g_pD3DTextureSearch);
	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexSearch(D3DXVECTOR3 pos)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// オブジェクトの頂点バッファを生成
	if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX,	// 頂点データ用に確保するバッファサイズ(バイト単位)
												D3DUSAGE_WRITEONLY,			// 頂点バッファの使用法　
												FVF_VERTEX_3D,				// 使用する頂点フォーマット
												D3DPOOL_MANAGED,			// リソースのバッファを保持するメモリクラスを指定
												&g_pD3DVtxBuffSearch,		// 頂点バッファインターフェースへのポインタ
												NULL)))						// NULLに設定
	{
		return E_FAIL;
	}

	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffSearch->Lock(0, 0, (void**)&pVtx, 0);

		// 頂点座標の設定
		pVtx[0].vtx = D3DXVECTOR3(-10.0f, 0.0f, 10.0f);
		pVtx[1].vtx = D3DXVECTOR3(10.0f,  0.0f, 10.0f);
		pVtx[2].vtx = D3DXVECTOR3(-50.0f, 0.0f, -100.0f);
		pVtx[3].vtx = D3DXVECTOR3(50.0f,  0.0f, -100.0f);

		// 法線ベクトルの設定
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		// 反射光の設定
		pVtx[0].diffuse = 
		pVtx[1].diffuse = 
		pVtx[2].diffuse = 
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.8f);

		// テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		// 頂点データをアンロックする
		g_pD3DVtxBuffSearch->Unlock();
	}
	return S_OK;
}

