//=============================================================================
//
// ビルボード処理 [billboard.cpp]
// Author : 
//
//=============================================================================
#include "GetUI.h"
#include "input.h"
#include "camera.h"
#include "shadow.h"
#include "debugproc.h"
#include "stage.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexGetUI(LPDIRECT3DDEVICE9 pDevice);
void SetVertexGetUI(float alpha);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureGetUI = NULL;	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffGetUI = NULL;	// 頂点バッファインターフェースへのポインタ

D3DXMATRIX				g_mtxWorldGetUI;			// ワールドマトリックス
D3DXVECTOR3				g_posGetUI;					// 位置
D3DXVECTOR3				g_sclGetUI;					// スケール
D3DXVECTOR3				g_moveGetUI;				// 移動量
bool					g_bUse;
float					g_fUIalpha;



//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitGetUI(int nType)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点情報の作成
	MakeVertexGetUI(pDevice);

	if (nType == STAGE_INIT_FAST)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
			TEXTURE_BILLBOARD,			// ファイルの名前
			&g_pD3DTextureGetUI);	// 読み込むメモリー
	}
	g_posGetUI = D3DXVECTOR3(0.0f, 18.0f, 0.0f);
	g_sclGetUI = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	g_moveGetUI = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_bUse = false;
	g_fUIalpha = 1.0f;

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitGetUI(void)
{
	if (g_pD3DTextureGetUI != NULL)
	{// テクスチャの開放
		g_pD3DTextureGetUI->Release();
		g_pD3DTextureGetUI = NULL;
	}

	if (g_pD3DVtxBuffGetUI != NULL)
	{// 頂点バッファの開放
		g_pD3DVtxBuffGetUI->Release();
		g_pD3DVtxBuffGetUI = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateGetUI(void)
{
	if (g_bUse == true)
	{
		g_posGetUI.y += 0.3f;
		g_fUIalpha -= 0.01f;

		if (g_fUIalpha <= 0.0f)
		{
			g_bUse = false;
			g_fUIalpha = 1.0f;
		}
	}
	SetVertexGetUI(g_fUIalpha);

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawGetUI(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxView, mtxScale, mtxTranslate;

	if (g_bUse == true)
	{
		// ラインティングを無効にする
		pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

		// ビューマトリックスを取得
		mtxView = GetMtxView();

		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_mtxWorldGetUI);

		// ポリゴンを正面に向ける
		D3DXMatrixInverse(&g_mtxWorldGetUI, NULL, &mtxView);
		g_mtxWorldGetUI._41 = 0.0f;
		g_mtxWorldGetUI._42 = 0.0f;
		g_mtxWorldGetUI._43 = 0.0f;
		

		// スケールを反映
		D3DXMatrixScaling(&mtxScale, g_sclGetUI.x,
			g_sclGetUI.y,
			g_sclGetUI.z);
		D3DXMatrixMultiply(&g_mtxWorldGetUI,
			&g_mtxWorldGetUI, &mtxScale);

		// 移動を反映
		D3DXMatrixTranslation(&mtxTranslate, g_posGetUI.x,
			g_posGetUI.y,
			g_posGetUI.z);
		D3DXMatrixMultiply(&g_mtxWorldGetUI,
			&g_mtxWorldGetUI, &mtxTranslate);

		// ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldGetUI);

		// 頂点バッファをデバイスのデータストリームにバインド
		pDevice->SetStreamSource(0, g_pD3DVtxBuffGetUI, 0, sizeof(VERTEX_3D));

		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_3D);

		// テクスチャの設定
		pDevice->SetTexture(0, g_pD3DTextureGetUI);

		// ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

		// ラインティングを有効にする
		pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	}
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
HRESULT MakeVertexGetUI(LPDIRECT3DDEVICE9 pDevice)
{
	// オブジェクトの頂点バッファを生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX,	// 頂点データ用に確保するバッファサイズ(バイト単位)
		D3DUSAGE_WRITEONLY,			// 頂点バッファの使用法　
		FVF_VERTEX_3D,				// 使用する頂点フォーマット
		D3DPOOL_MANAGED,			// リソースのバッファを保持するメモリクラスを指定
		&g_pD3DVtxBuffGetUI,	// 頂点バッファインターフェースへのポインタ
		NULL)))						// NULLに設定
	{
		return E_FAIL;
	}

	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffGetUI->Lock(0, 0, (void**)&pVtx, 0);

		// 頂点座標の設定
		pVtx[0].vtx = D3DXVECTOR3(-BILLBOARD_SIZE_X / 2, -BILLBOARD_SIZE_Y / 2, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(-BILLBOARD_SIZE_X / 2, BILLBOARD_SIZE_Y / 2, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(BILLBOARD_SIZE_X / 2, -BILLBOARD_SIZE_Y / 2, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(BILLBOARD_SIZE_X / 2, BILLBOARD_SIZE_Y / 2, 0.0f);

		// 法線の設定
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		// 反射光の設定
		pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

		// 頂点データをアンロックする
		g_pD3DVtxBuffGetUI->Unlock();
	}

	return S_OK;
}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexGetUI(float alpha)
{
	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffGetUI->Lock(0, 0, (void**)&pVtx, 0);

		// 反射光の設定
		pVtx[0].diffuse =
			pVtx[1].diffuse =
			pVtx[2].diffuse =
			pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, alpha);

		// 頂点データをアンロックする
		g_pD3DVtxBuffGetUI->Unlock();
	}
}

void SetGetUI(D3DXVECTOR3 pos)
{
	g_bUse = true;
	g_posGetUI = D3DXVECTOR3(pos.x, pos.y + 30.0f, pos.z);
	g_fUIalpha = 1.0f;
}