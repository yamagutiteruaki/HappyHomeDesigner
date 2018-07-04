////***********************************************************
////			levelchoice.cpp
////			今川乃流
////
////***********************************************************
////#include "main.h"
////#include "levelchoice.h"
////#include "input.h"
////#include "fade.h"
////#include "stage.h"
////#include "sound.h"
////#include "inputCtrl.h"
//
//
////***********************************************************
//// プロトタイプ宣言
////***********************************************************
//HRESULT MakeVertexMode(LPDIRECT3DDEVICE9 pDevice);
//
////***********************************************************
////グローバル宣言
////***********************************************************
//
//
////***********************************************************
//// 初期化処理
////***********************************************************
//HRESULT InitMode(void)
//{
//	LPDIRECT3DDEVICE9 pDevice = GetDevice();
//
//
//	MakeVertexMode(pDevice);							//頂点情報の作成
//
//#include "main.h"
//
//															// テクスチャの読み込み
//	D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
//		TEXTURE_MODE,				// ファイルの名前
//		&g_pD3DTextureMode);		// 読み込むメモリー
//
//
//	return S_OK;
//}
//
////=============================================================================
//// 終了処理
////=============================================================================
//void UninitMode(void)
//{
//	if (g_pD3DTextureMode != NULL)
//	{// テクスチャの開放
//		g_pD3DTextureMode->Release();
//		g_pD3DTextureMode = NULL;
//	}
//
//	if (g_pD3DVtxBuffMode != NULL)
//	{// 頂点バッファの開放
//		g_pD3DVtxBuffMode->Release();
//		g_pD3DVtxBuffMode = NULL;
//	}
//
//
//}
//
////=============================================================================
//// 更新処理
////=============================================================================
//void UpdateTitleMode(void)
//{
//	INPUTDEVICE *kb = GetInputDevice(INPUT_KEY);
//	INPUTDEVICE *gp = GetInputDevice(INPUT_GAMEPAD);
//
//#if 0
//	if (g_nCountAppearStart >= COUNT_APPERA_START)
//	{
//		g_nConutDemo++;
//		if (g_nConutDemo > COUNT_WAIT_DEMO)
//		{
//			SetFade(FADE_OUT, MODE_TITLE);
//		}
//	}
//#endif
//
//
//	if (GetKeyboardTrigger(DIK_START))//スタンプを　T=押してる　F=押してない
//	{
//		
//}
//
////=============================================================================
//// 描画処理
////=============================================================================
//void DrawTitleMode(void)
//{
//	LPDIRECT3DDEVICE9 pDevice = GetDevice();
//
//	// 頂点バッファをデバイスのデータストリームにバインド
//	pDevice->SetStreamSource(0, g_pD3DVtxBuffTitle, 0, sizeof(VERTEX_2D));
//
//	// 頂点フォーマットの設定
//	pDevice->SetFVF(FVF_VERTEX_2D);
//
//	// テクスチャの設定
//	pDevice->SetTexture(0, g_pD3DTextureMode);
//
//	// ポリゴンの描画
//	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
//
//}
//
////=============================================================================
//// 頂点の作成
////=============================================================================
//HRESULT MakeVertexTitleMode(LPDIRECT3DDEVICE9 pDevice)
//{
//	// オブジェクトの頂点バッファを生成
//	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,	// 頂点データ用に確保するバッファサイズ(バイト単位)
//		D3DUSAGE_WRITEONLY,			// 頂点バッファの使用法　
//		FVF_VERTEX_2D,				// 使用する頂点フォーマット
//		D3DPOOL_MANAGED,			// リソースのバッファを保持するメモリクラスを指定
//		&g_pD3DVtxBuffTitle,		// 頂点バッファインターフェースへのポインタ
//		NULL)))						// NULLに設定
//	{
//		return E_FAIL;
//	}
//
//	{//頂点バッファの中身を埋める
//		VERTEX_2D *pVtx;
//
//		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
//		g_pD3DVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);
//
//		// 頂点座標の設定
//		pVtx[0].vtx = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//		pVtx[1].vtx = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
//		pVtx[2].vtx = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
//		pVtx[3].vtx = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
//
//		// テクスチャのパースペクティブコレクト用
//		pVtx[0].rhw =
//			pVtx[1].rhw =
//			pVtx[2].rhw =
//			pVtx[3].rhw = 1.0f;
//
//		// 反射光の設定
//		pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//		pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//		pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//
//		// テクスチャ座標の設定
//		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
//		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
//		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
//		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
//
//		// 頂点データをアンロックする
//		g_pD3DVtxBuffTitle->Unlock();
//	}
//
//	return S_OK;
//}
//
//
