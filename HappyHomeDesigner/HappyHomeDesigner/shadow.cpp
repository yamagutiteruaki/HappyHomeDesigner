//=============================================================================
//
// 影処理 [shadow.cpp]
// Author : GP11B243 24 人見友基
//
//=============================================================================
#include "shadow.h"
#include "stage.h"
#include "police.h"


// デバッグ用
#ifdef _DEBUG
#include "debugproc.h"
#endif

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexShadow(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureShadow = NULL;		// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffShadow = NULL;		// 頂点バッファインターフェースへのポインタ

SHADOW					g_aShadow[MAX_SHADOW];			// 影ワーク

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitShadow(int nType)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	if (nType == STAGE_INIT_FAST)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
			TEXTURE_SHADOW,				// ファイルの名前
			&g_pD3DTextureShadow);		// 読み込むメモリー
	}

	for(int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		g_aShadow[nCntShadow].pos = D3DXVECTOR3(0.0f, 0.2f, 0.0f);
		g_aShadow[nCntShadow].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aShadow[nCntShadow].bUse = false;
		g_aShadow[nCntShadow].bDraw = true;
	}

	// 頂点情報の作成
	MakeVertexShadow(pDevice);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitShadow(void)
{
	if(g_pD3DTextureShadow != NULL)
	{// テクスチャの開放
		g_pD3DTextureShadow->Release();
		g_pD3DTextureShadow = NULL;
	}

	if(g_pD3DVtxBuffShadow != NULL)
	{// 頂点バッファの開放
		g_pD3DVtxBuffShadow->Release();
		g_pD3DVtxBuffShadow = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateShadow(void)
{
	SHADOW *shadow = &g_aShadow[0];

#ifdef _DEBUG
	PrintDebugProc("使用シャドウ:");

	for (int i = 0; i < MAX_SHADOW; i++, shadow++)
	{
		if (shadow->bUse == true)
		{
			PrintDebugProc("[%d]", i);
		}
	}
	PrintDebugProc("\n");
#endif
	POLICE *police = GetPolice(0);

	for (int i = 0; i < POLICE_MAX; i++, police++)
	{
		if (GetStage() != STAGE_GAME)
		{
			ReleaseShadow(police->nIdxShadow);
			police->bShadow = false;
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawShadow(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTranslate;
#ifdef _DEBUG
	PrintDebugProc("【 SHADOW 】\n");
	int nShadowCountDebug = 0;
#endif
	// 減算合成
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// Z比較なし
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);

	// αテストを有効に
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, SHADOW_ALPHA);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	for(int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		if(g_aShadow[nCntShadow].bUse && g_aShadow[nCntShadow].bDraw)
		{
#ifdef _DEBUG
			nShadowCountDebug++;
#endif
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_aShadow[nCntShadow].mtxWorld);

			// 回転を反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aShadow[nCntShadow].rot.y, g_aShadow[nCntShadow].rot.x, g_aShadow[nCntShadow].rot.z);
			D3DXMatrixMultiply(&g_aShadow[nCntShadow].mtxWorld, &g_aShadow[nCntShadow].mtxWorld, &mtxRot);

			// 移動を反映
			D3DXMatrixTranslation(&mtxTranslate, g_aShadow[nCntShadow].pos.x,
													g_aShadow[nCntShadow].pos.y,
													g_aShadow[nCntShadow].pos.z);
			D3DXMatrixMultiply(&g_aShadow[nCntShadow].mtxWorld,
										&g_aShadow[nCntShadow].mtxWorld, &mtxTranslate);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aShadow[nCntShadow].mtxWorld);

			// 頂点バッファをレンダリングパイプラインに設定
			pDevice->SetStreamSource(0, g_pD3DVtxBuffShadow, 0, sizeof(VERTEX_3D));

			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			// テクスチャの設定
			pDevice->SetTexture(0, g_pD3DTextureShadow);

			// ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, (nCntShadow * 4), NUM_POLYGON);
		}
	}
#ifdef _DEBUG
	PrintDebugProc("ShadowCount[%d]\n", nShadowCountDebug);
#endif
	// 通常ブレンド
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// Z比較あり
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

	// αテストを無効に
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
HRESULT MakeVertexShadow(LPDIRECT3DDEVICE9 pDevice)
{
	// オブジェクトの頂点バッファを生成
	if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX * MAX_SHADOW,	// 頂点データ用に確保するバッファサイズ(バイト単位)
												D3DUSAGE_WRITEONLY,						// 頂点バッファの使用法　
												FVF_VERTEX_3D,							// 使用する頂点フォーマット
												D3DPOOL_MANAGED,						// リソースのバッファを保持するメモリクラスを指定
												&g_pD3DVtxBuffShadow,					// 頂点バッファインターフェースへのポインタ
												NULL)))									// NULLに設定
	{
		return E_FAIL;
	}

	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

		for(int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++, pVtx += 4)
		{
			// 頂点座標の設定
			pVtx[0].vtx = D3DXVECTOR3(-SHADOW_SIZE_X / 2, 0.0f, SHADOW_SIZE_Z / 2);
			pVtx[1].vtx = D3DXVECTOR3(SHADOW_SIZE_X / 2, 0.0f, SHADOW_SIZE_Z / 2);
			pVtx[2].vtx = D3DXVECTOR3(-SHADOW_SIZE_X / 2, 0.0f, -SHADOW_SIZE_Z / 2);
			pVtx[3].vtx = D3DXVECTOR3(SHADOW_SIZE_X / 2, 0.0f, -SHADOW_SIZE_Z / 2);

			// 法線の設定
			pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			// 反射光の設定
			pVtx[0].diffuse = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f);
			pVtx[1].diffuse = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f);
			pVtx[2].diffuse = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f);
			pVtx[3].diffuse = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f);

			// テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		}

		// 頂点データをアンロックする
		g_pD3DVtxBuffShadow->Unlock();
	}

	return S_OK;
}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexShadow(int nIdxShadow, float fSizeX, float fSizeZ)
{
	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += (nIdxShadow * 4);

		// 頂点座標の設定
		pVtx[0].vtx = D3DXVECTOR3(-fSizeX / 2, 0.0f, fSizeZ / 2);
		pVtx[1].vtx = D3DXVECTOR3(fSizeX / 2, 0.0f, fSizeZ / 2);
		pVtx[2].vtx = D3DXVECTOR3(-fSizeX / 2, 0.0f, -fSizeZ / 2);
		pVtx[3].vtx = D3DXVECTOR3(fSizeX / 2, 0.0f, -fSizeZ / 2);

		// 頂点データをアンロックする
		g_pD3DVtxBuffShadow->Unlock();
	}
}

//=============================================================================
// 頂点カラーの設定
//=============================================================================
void SetColorShadow(int nIdxShadow, D3DXCOLOR col)
{

	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += (nIdxShadow * 4);

		// 頂点座標の設定
		pVtx[0].diffuse =
		pVtx[1].diffuse =
		pVtx[2].diffuse =
		pVtx[3].diffuse = col;

		// 頂点データをアンロックする
		g_pD3DVtxBuffShadow->Unlock();
	}
}

//=============================================================================
// 影の作成
//=============================================================================
int CreateShadow(D3DXVECTOR3 pos, float fSizeX, float fSizeZ)
{
	int nIdxShadow = -1;

	for(int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		if(!g_aShadow[nCntShadow].bUse)
		{
			g_aShadow[nCntShadow].pos = pos;
			g_aShadow[nCntShadow].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aShadow[nCntShadow].bUse = true;

			SetVertexShadow(nCntShadow, fSizeX, fSizeZ);

			nIdxShadow = nCntShadow;
			break;
		}
	}

	return nIdxShadow;
}

//=============================================================================
// 影の破棄
//=============================================================================
void ReleaseShadow(int nIdxShadow)
{
	if(nIdxShadow >= 0 && nIdxShadow < MAX_SHADOW)
	{
		g_aShadow[nIdxShadow].bUse = false;
	}
}

//=============================================================================
// 位置の設定
//=============================================================================
void SetPositionShadow(int nIdxShadow, D3DXVECTOR3 pos)
{
	g_aShadow[nIdxShadow].pos.x = pos.x;
	g_aShadow[nIdxShadow].pos.y = SHADOW_POS_Y;
	g_aShadow[nIdxShadow].pos.z = pos.z;

	if (pos.y <= 0.0f)
	{
		g_aShadow[nIdxShadow].bDraw = false;
	}
	else
	{
		g_aShadow[nIdxShadow].bDraw = true;
	}
}

LPDIRECT3DVERTEXBUFFER9 DebugShadow(void)
{
	return g_pD3DVtxBuffShadow;
}