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
void SetDiffuseField(int nField, D3DXCOLOR col);
void SetDiffuseHitPanel(int HitPanel, D3DXCOLOR col);
void SetVertexHitPanel(int no);



//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureField = NULL;	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffField = NULL;	// 頂点バッファへのポインタ

PANEL					g_aPanel[PANEL_MAX];

LPDIRECT3DTEXTURE9		g_pD3DTextureHitPanel = NULL;	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffHitPanel = NULL;	// 頂点バッファへのポインタ

HIT_PANEL				g_aHitPanel[PANEL_MAX];

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitField(int nType)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	PANEL *panel = GetPanel(0);
	HIT_PANEL *hitpanel = GetHitPanel(0);

	if (nType == STAGE_INIT_FAST)
	{
		MakeVertexField(pDevice);

		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,					// デバイスへのポインタ
			TEXTURE_PANEL,			// ファイルの名前
			&g_pD3DTextureField);	// 読み込むメモリー
									// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,					// デバイスへのポインタ
			TEXTURE_PANEL,			// ファイルの名前
			&g_pD3DTextureHitPanel);// 読み込むメモリー

	}


	for (int i = 0; i < PANEL_MAX; i++, panel++, hitpanel++)
	{
		panel->Pos.x = i % PANEL_NUM_X * PANEL_SIZE_X;	//X座標の設定
		panel->Pos.y = 0.0f;							//Y座標は0固定
		panel->Pos.z = i / PANEL_NUM_X * PANEL_SIZE_Z;	//Z座標の設定
		panel->PanelType = PANEL_NORMAL;				//パネルタイプ　基本はノーマル
		panel->PanelCol = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//パネルカラー 基本は白
		panel->ItemSet = false;
		panel->HitFlag = PANEL_NORMAL;

		hitpanel->Pos.x = panel->Pos.x;
		hitpanel->Pos.y = panel->Pos.y + 0.1f;
		hitpanel->Pos.z = panel->Pos.z;

		hitpanel->Size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		hitpanel->HitCol = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		hitpanel->Use = false;
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitField(void)
{
	//パネル
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

	//ヒットエフェクト
	if (g_pD3DTextureHitPanel != NULL)
	{// テクスチャの開放
		g_pD3DTextureHitPanel->Release();
		g_pD3DTextureHitPanel = NULL;
	}

	if (g_pD3DVtxBuffHitPanel != NULL)
	{// 頂点バッファの開放
		g_pD3DVtxBuffHitPanel->Release();
		g_pD3DVtxBuffHitPanel = NULL;
	}

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateField(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	PANEL *panel;
	HIT_PANEL *hitpanel;


#ifdef _DEBUG
	if (GetKeyboardTrigger(DIK_L))
	{
		{
			int p = rand() % 105;
			int num = rand() % 2;
			SetHitPanel(p, num);
		}
	}
#endif

	panel = GetPanel(0);
	hitpanel = GetHitPanel(0);

	for (int i = 0; i < PANEL_MAX; i++, panel++, hitpanel++)
	{
#ifdef _DEBUG
		PrintDebugProc("%d", panel->PanelType);
#endif
		if (hitpanel->Use == true)//ヒットパネルがonの時
		{
			hitpanel->Size.x++;//ヒットパネルのサイズを少しずつ大きく
			hitpanel->Size.z++;

			//ヒットパネルの色を設定
			if (panel->HitFlag == 1)
			{
				hitpanel->HitCol = SetColorPallet(COLOR_PALLET_RED);
			}
			else if (panel->HitFlag == 2)
			{
				hitpanel->HitCol = SetColorPallet(COLOR_PALLET_BLUE);
			}
			else if (panel->HitFlag == 0)
			{
				hitpanel->HitCol = SetColorPallet(COLOR_PALLET_WHITE);
			}

		}
		if (hitpanel->Size.x >= PANEL_SIZE_X)//ヒットパネルがパネルと同サイズになったら
		{
			hitpanel->Size.x = 0.0f;			//サイズを0に戻し
			hitpanel->Size.z = 0.0f;
			panel->PanelType = panel->HitFlag;	//パネルタイプを変更し
			panel->HitFlag = 0;					//パネルタイプをリセット
			hitpanel->Use = false;				//ヒットパネルをoff

		}
		SetVertexHitPanel(i);
		SetDiffuseHitPanel(i, hitpanel->HitCol);

	}



	panel = GetPanel(0);
	hitpanel = GetHitPanel(0);
	for (int i = 0; i < PANEL_MAX; i++, panel++)
	{
		if (panel->PanelType == PANEL_1P)	//パネルタイプが1Pに変わったら
		{
			panel->PanelCol = SetColorPallet(COLOR_PALLET_RED);	//パネルカラーを赤に
		}
		else if (panel->PanelType == PANEL_2P)	//パネルタイプが2Pになったら
		{
			panel->PanelCol = SetColorPallet(COLOR_PALLET_BLUE);//パネルカラーを青に
		}
		else if (panel->PanelType == PANEL_NORMAL)	//パネルタイプが2Pになったら
		{
			panel->PanelCol = SetColorPallet(COLOR_PALLET_WHITE);//パネルカラーを青に
		}

		SetDiffuseField(i, panel->PanelCol);
	}


#ifdef _DEBUG
	//パネル位置確認用
	//PANEL *panelcheck1 = GetPanel(GetPanelNumber(1, 1));
	//PANEL *panelcheck2 = GetPanel(GetPanelNumber(1, 15));
	//PANEL *panelcheck3 = GetPanel(GetPanelNumber(7, 1));
	//PANEL *panelcheck4 = GetPanel(GetPanelNumber(7, 15));
	//PrintDebugProc("パネル[ 1][ 1] : (%f,%f,%f)\n", panelcheck1->Pos.x, panelcheck1->Pos.y, panelcheck1->Pos.z);
	//PrintDebugProc("パネル[ 1][15] : (%f,%f,%f)\n", panelcheck2->Pos.x, panelcheck2->Pos.y, panelcheck2->Pos.z);
	//PrintDebugProc("パネル[ 7][ 1] : (%f,%f,%f)\n", panelcheck3->Pos.x, panelcheck3->Pos.y, panelcheck3->Pos.z);
	//PrintDebugProc("パネル[ 7][15] : (%f,%f,%f)\n", panelcheck4->Pos.x, panelcheck4->Pos.y, panelcheck4->Pos.z);

	/*GetPanel(1)->PanelCol = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);*/

#endif
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawField(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTranslate;
	PANEL *panel = GetPanel(0);
	for (int i = 0; i < PANEL_MAX; i++, panel++)
	{
		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&panel->mtxWorldField);


		// 移動を反映
		D3DXMatrixTranslation(&mtxTranslate, panel->Pos.x, panel->Pos.y, panel->Pos.z);
		D3DXMatrixMultiply(&panel->mtxWorldField, &panel->mtxWorldField, &mtxTranslate);

		// ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &panel->mtxWorldField);

		// 頂点バッファをデバイスのデータストリームにバインド
		pDevice->SetStreamSource(0, g_pD3DVtxBuffField, 0, sizeof(VERTEX_3D));

		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_3D);

		// テクスチャの設定
		pDevice->SetTexture(0, g_pD3DTextureField);

		// ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * 4, NUM_POLYGON);
	}

	HIT_PANEL *hitpanel = GetHitPanel(0);
	for (int i = 0; i < PANEL_MAX; i++, hitpanel++)
	{
		if (hitpanel->Use == true)
		{
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&hitpanel->mtxWorldHitPanel);


			// 移動を反映
			D3DXMatrixTranslation(&mtxTranslate, hitpanel->Pos.x, hitpanel->Pos.y, hitpanel->Pos.z);
			D3DXMatrixMultiply(&hitpanel->mtxWorldHitPanel, &hitpanel->mtxWorldHitPanel, &mtxTranslate);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &hitpanel->mtxWorldHitPanel);

			// 頂点バッファをデバイスのデータストリームにバインド
			pDevice->SetStreamSource(0, g_pD3DVtxBuffHitPanel, 0, sizeof(VERTEX_3D));

			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			// テクスチャの設定
			pDevice->SetTexture(0, g_pD3DTextureHitPanel);

			// ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * 4, NUM_POLYGON);
		}
	}

}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexField(LPDIRECT3DDEVICE9 pDevice)
{

	// オブジェクトの頂点バッファを生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX* PANEL_MAX,	// 頂点データ用に確保するバッファサイズ(バイト単位)
		D3DUSAGE_WRITEONLY,			// 頂点バッファの使用法　
		FVF_VERTEX_3D,				// 使用する頂点フォーマット
		D3DPOOL_MANAGED,			// リソースのバッファを保持するメモリクラスを指定
		&g_pD3DVtxBuffField,		// 頂点バッファインターフェースへのポインタ
		NULL)))						// NULLに設定
	{
		return E_FAIL;
	}
	//for (int i = 0; i < PANEL_MAX; i++)
	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffField->Lock(0, 0, (void**)&pVtx, 0);

		for (int i = 0; i < PANEL_MAX; i++, pVtx += 4)

		{

			// 頂点座標の設定
			pVtx[0].vtx = D3DXVECTOR3(-PANEL_SIZE_X / 2, 0.0f, PANEL_SIZE_Z / 2);
			pVtx[1].vtx = D3DXVECTOR3(PANEL_SIZE_X / 2, 0.0f, PANEL_SIZE_Z / 2);
			pVtx[2].vtx = D3DXVECTOR3(-PANEL_SIZE_X / 2, 0.0f, -PANEL_SIZE_Z / 2);
			pVtx[3].vtx = D3DXVECTOR3(PANEL_SIZE_X / 2, 0.0f, -PANEL_SIZE_Z / 2);

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
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX* PANEL_MAX,	// 頂点データ用に確保するバッファサイズ(バイト単位)
		D3DUSAGE_WRITEONLY,			// 頂点バッファの使用法　
		FVF_VERTEX_3D,				// 使用する頂点フォーマット
		D3DPOOL_MANAGED,			// リソースのバッファを保持するメモリクラスを指定
		&g_pD3DVtxBuffHitPanel,		// 頂点バッファインターフェースへのポインタ
		NULL)))						// NULLに設定
	{
		return E_FAIL;
	}
	//for (int i = 0; i < PANEL_MAX; i++)
	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;
		HIT_PANEL *hitpanel = GetHitPanel(0);

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffHitPanel->Lock(0, 0, (void**)&pVtx, 0);

		for (int i = 0; i < PANEL_MAX; i++, hitpanel++, pVtx += 4)

		{

			// 頂点座標の設定
			pVtx[0].vtx = D3DXVECTOR3(-hitpanel->Size.x / 2, 0.0f, hitpanel->Size.z / 2);
			pVtx[1].vtx = D3DXVECTOR3(hitpanel->Size.x / 2, 0.0f, hitpanel->Size.z / 2);
			pVtx[2].vtx = D3DXVECTOR3(-hitpanel->Size.x / 2, 0.0f, -hitpanel->Size.z / 2);
			pVtx[3].vtx = D3DXVECTOR3(hitpanel->Size.x / 2, 0.0f, -hitpanel->Size.z / 2);

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
		g_pD3DVtxBuffHitPanel->Unlock();
	}

	return S_OK;
}

//============================================================================= 
// 反射光の設定関数 
//============================================================================= 
void SetDiffuseField(int nField, D3DXCOLOR col)
{
	{// 頂点バッファの中身を埋める 
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得 
		g_pD3DVtxBuffField->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += (nField * 4);

		// 頂点座標の設定 
		pVtx[0].diffuse =
			pVtx[1].diffuse =
			pVtx[2].diffuse =
			pVtx[3].diffuse = col;


		// 頂点データをアンロックする 
		g_pD3DVtxBuffField->Unlock();
	}
}
//============================================================================= 
// 反射光の設定関数 
//============================================================================= 
void SetDiffuseHitPanel(int HitPanel, D3DXCOLOR col)
{
	{// 頂点バッファの中身を埋める 
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得 
		g_pD3DVtxBuffHitPanel->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += (HitPanel * 4);

		// 頂点座標の設定 
		pVtx[0].diffuse =
			pVtx[1].diffuse =
			pVtx[2].diffuse =
			pVtx[3].diffuse = col;


		// 頂点データをアンロックする 
		g_pD3DVtxBuffHitPanel->Unlock();
	}
}

//=============================================================================
//頂点座標
//=============================================================================
void SetVertexHitPanel(int no)
{
	HIT_PANEL *hitpanel = GetHitPanel(no);
	// 頂点バッファの中身を埋める 
	VERTEX_3D *pVtx;


	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	g_pD3DVtxBuffHitPanel->Lock(0, 0, (void**)&pVtx, 0);
	pVtx += (no * 4);

	// 頂点座標の設定
	pVtx[0].vtx = D3DXVECTOR3(-hitpanel->Size.x / 2, 0.0f, hitpanel->Size.z / 2);
	pVtx[1].vtx = D3DXVECTOR3(hitpanel->Size.x / 2, 0.0f, hitpanel->Size.z / 2);
	pVtx[2].vtx = D3DXVECTOR3(-hitpanel->Size.x / 2, 0.0f, -hitpanel->Size.z / 2);
	pVtx[3].vtx = D3DXVECTOR3(hitpanel->Size.x / 2, 0.0f, -hitpanel->Size.z / 2);

	// 頂点データをアンロックする
	g_pD3DVtxBuffHitPanel->Unlock();

}
//===========================================================
//パネルの取得
//===========================================================
PANEL *GetPanel(int no)
{
	return &g_aPanel[no];
}

//===========================================================
//ヒットパネルの取得
//===========================================================
HIT_PANEL *GetHitPanel(int no)
{
	return &g_aHitPanel[no];
}

//===========================================================
//パネル番号の計算
//height(引数１)	下(手前)から数えて何番目のパネルか
//width(引数２)		左から数えて何番目のパネルか
//===========================================================
int GetPanelNumber(int height, int width)
{
	return (height - 1)*PANEL_NUM_X + (width - 1);
}

//==========================================================
//パネル変更の準備
//no(引数１)		変えたいパネルの番号
//playernum(引数2)	変えようとしているプレイヤーの番号
//==========================================================
void SetHitPanel(int no, int playernum)
{
	PANEL *panel = GetPanel(no);
	HIT_PANEL *hitpanel = GetHitPanel(no);

	if (hitpanel->Use == false && panel->PanelType == PANEL_NORMAL)//ヒットパネルが使われてない　かつ　パネルタイプが0の時
	{
		panel->HitFlag = playernum + 1;	//プレイヤーナンバーに1足したフラグナンバーを立てる
										//※ 0番がノーマルパネルのため　1番分のずれが出ている

		hitpanel->Use = true;//ヒットパネルを使用状態に
	}
}