
//***********************************************************
//timeeffect.cpp
// 
//
//***********************************************************
#include "main.h"
#include "timeeffect.h"
#include "input.h"
#include "fade.h"
#include "stage.h"
#include "clock.h"
#include "sound.h"

//***********************************************************
// プロトタイプ宣言
//***********************************************************
HRESULT MakeVertexTimeeffect(LPDIRECT3DDEVICE9 pDevice);

//***********************************************************
//グローバル宣言
//***********************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureTimeeff = NULL;		// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffTimeeff = NULL;		// 頂点バッファインターフェースへのポインタ

void SetColor(void);

float					g_fAlpha;
bool					g_bAlpha;
bool					g_bUseEffect;

//***********************************************************
// 初期化処理
//***********************************************************
HRESULT InitTimeeffect(int nType)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();



	MakeVertexTimeeffect(pDevice);							//頂点情報の作成

	if (nType == STAGE_INIT_FAST)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
			TEXTURE_TIME_EFF,				// ファイルの名前
			&g_pD3DTextureTimeeff);		// 読み込むメモリー
	}
	g_fAlpha = 0.0f;
	g_bAlpha = false;
	g_bUseEffect = false;

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitTimeeffect(void)
{
	if (g_pD3DTextureTimeeff != NULL)
	{// テクスチャの開放
		g_pD3DTextureTimeeff->Release();
		g_pD3DTextureTimeeff = NULL;
	}

	if (g_pD3DVtxBuffTimeeff!= NULL)
	{// 頂点バッファの開放
		g_pD3DVtxBuffTimeeff->Release();
		g_pD3DVtxBuffTimeeff = NULL;
	}

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateTimeeffect(void)
{
	CLOCK *clock = GetClock(0);

	if (clock->rot.z > WARNING_TIME
		&& g_bUseEffect ==false)
	{
		g_bUseEffect = true;
		g_bAlpha = true;

	}
	else if (clock->rot.z <= WARNING_TIME)
	{
		g_bUseEffect = false;
		g_bAlpha = false;
		g_fAlpha = 0.0f;
	}
	
	if (g_bUseEffect == true)
	{
		if (g_bAlpha == true)
		{
			g_fAlpha += ALPHA_RATE;
			if (g_fAlpha >= ALPHA_MAX)
			{
				g_bAlpha = false;
			}
		}
		else if (g_bAlpha == false)
		{
			g_fAlpha -= ALPHA_RATE;
			if (g_fAlpha <= 0.0f)
			{
				g_bAlpha = true;
			}
		}

		SetSe(SE_CHIME, E_DS8_FLAG_NONE, CONTINUITY_ON);
	}

	SetColor();
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawTimeeffect(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	if (g_bUseEffect==true)
	{
		// 頂点バッファをデバイスのデータストリームにバインド
		pDevice->SetStreamSource(0, g_pD3DVtxBuffTimeeff, 0, sizeof(VERTEX_2D));

		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		// テクスチャの設定
		pDevice->SetTexture(0, g_pD3DTextureTimeeff);

		// ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
	}


}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexTimeeffect(LPDIRECT3DDEVICE9 pDevice)
{
	// オブジェクトの頂点バッファを生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,	// 頂点データ用に確保するバッファサイズ(バイト単位)
		D3DUSAGE_WRITEONLY,			// 頂点バッファの使用法　
		FVF_VERTEX_2D,				// 使用する頂点フォーマット
		D3DPOOL_MANAGED,			// リソースのバッファを保持するメモリクラスを指定
		&g_pD3DVtxBuffTimeeff,		// 頂点バッファインターフェースへのポインタ
		NULL)))						// NULLに設定
	{
		return E_FAIL;
	}

	{//頂点バッファの中身を埋める
		VERTEX_2D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffTimeeff->Lock(0, 0, (void**)&pVtx, 0);

		// 頂点座標の設定
		pVtx[0].vtx = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(SCREEN_WIDTH , SCREEN_HEIGHT, 0.0f);

		// テクスチャのパースペクティブコレクト用
		pVtx[0].rhw =
			pVtx[1].rhw =
			pVtx[2].rhw =
			pVtx[3].rhw = 1.0f;

		// 反射光の設定
		pVtx[0].diffuse =
			pVtx[1].diffuse =
			pVtx[2].diffuse =
			pVtx[3].diffuse = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.5f);

		// テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		// 頂点データをアンロックする
		g_pD3DVtxBuffTimeeff->Unlock();
	}
	return S_OK;
}

//===========================================================================
//色セット
//===========================================================================
void SetColor(void)
{
	{//頂点バッファの中身を埋める
		VERTEX_2D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffTimeeff->Lock(0, 0, (void**)&pVtx, 0);

		// 反射光の設定
		pVtx[0].diffuse =
			pVtx[1].diffuse =
			pVtx[2].diffuse =
			pVtx[3].diffuse = D3DXCOLOR(1.0f, 0.0f, 0.0f, g_fAlpha);



		// 頂点データをアンロックする
		g_pD3DVtxBuffTimeeff->Unlock();
	}


}