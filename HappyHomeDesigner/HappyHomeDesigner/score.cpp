//=============================================================================
//
// スコア処理 [score.cpp]
// Author : 
//
//=============================================================================
#include "score.h"
#include "stage.h"
#include "calculate.h"
#include "debugproc.h"
#include "input.h"
#include "ranking.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexScore(LPDIRECT3DDEVICE9 pDevice);
void SetTextureScore(int idx, int number);

//*****************************************************************************
// グローバル変数宣言
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureScore[2] = {};	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffScore = NULL;		// 頂点バッファインターフェースへのポインタ

D3DXVECTOR3				g_posScore;						// 位置
D3DXVECTOR3				g_rotScore;						// 向き

long long			g_score;						// 表示スコア
long long			g_maxscore;						//取得スコア

int slotTimer ;									//スロットタイマー
int slotCount ;									//スロット桁数
bool slotStart;

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitScore(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	g_posScore = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_rotScore = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// スコアの初期化
	g_score = 0;
	g_maxscore = 0;

	slotTimer = 0;
	slotCount = 0;
	slotStart = false;

	// 頂点情報の作成
	MakeVertexScore(pDevice);

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,					// デバイスへのポインタ
		TEXTURE_SCORE,			// ファイルの名前
		&g_pD3DTextureScore[0]);	// 読み込むメモリー

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitScore(void)
{
	if (g_pD3DTextureScore[0] != NULL)
	{// テクスチャの開放
		g_pD3DTextureScore[0]->Release();
		g_pD3DTextureScore[0] = NULL;
	}
	if (g_pD3DTextureScore[1] != NULL)
	{// テクスチャの開放
		g_pD3DTextureScore[1]->Release();
		g_pD3DTextureScore[1] = NULL;
	}

	if (g_pD3DVtxBuffScore != NULL)
	{// 頂点バッファの開放
		g_pD3DVtxBuffScore->Release();
		g_pD3DVtxBuffScore = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateScore(void)
{

	g_maxscore = GetPrice();	//被害金額の取得

	long long slotadd=0;		//スロット加算数

	slotTimer++;				//タイマー加算
	
	if(slotTimer>60)
	{
		slotStart = true;
		slotTimer = 0;
	}
	if (slotStart == true)
	{
		for (int i = 0; i < NUM_PLACE - slotCount; i++)
		{

			slotadd = (long long)(powf(10.0f, (float)(NUM_PLACE - i - 1)));//加算演出
			g_score += slotadd;

			if (GetKeyboardTrigger(DIK_LSHIFT))//演出スキップ
			{
				g_score = g_maxscore;
				slotCount = NUM_PLACE;
			}

		}

		int number;
		int number2;

		number = (g_score % (long long)(powf(10.0f, (float)(slotCount + 1)))) / (long long)(powf(10.0f, (float)(slotCount)));	//指定桁確認
		number2 = (g_maxscore % (long long)(powf(10.0f, (float)(slotCount + 1)))) / (long long)(powf(10.0f, (float)(slotCount)));//指定桁確認

		if (slotTimer > SLOT_INTERVAL && number == number2)//演出ストップ処理
		{
			slotCount++;
			slotTimer = 0;
		}
		else if (slotTimer == NUM_PLACE)
		{
			g_score = g_maxscore;
		}

		for (int nCntPlace = 0; nCntPlace < NUM_PLACE; nCntPlace++)
		{
			int number;

			number = (g_score % (long long)(powf(10.0f, (float)(NUM_PLACE - nCntPlace)))) / (long long)(powf(10.0f, (float)(NUM_PLACE - nCntPlace - 1)));
			SetTextureScore(nCntPlace, number);
		}
	}
	PrintDebugProc("[スコア ：(%g)]\n", g_score);
	PrintDebugProc("[被害総額 ：(%g)]\n", g_maxscore);

	if (GetKeyboardTrigger(DIK_4))
	{
		// ランキングcsv更新
		Ranking();
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawScore(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, g_pD3DVtxBuffScore, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pD3DTextureScore[0]);

	// ポリゴンの描画
	for (int nCntPlace = 0; nCntPlace < NUM_PLACE; nCntPlace++)
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, (nCntPlace * 4), NUM_POLYGON);
	}

	// テクスチャの設定
	pDevice->SetTexture(0, g_pD3DTextureScore[1]);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, (NUM_PLACE * 4), NUM_POLYGON);
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexScore(LPDIRECT3DDEVICE9 pDevice)
{
	// オブジェクトの頂点バッファを生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * (NUM_VERTEX * NUM_PLACE + 4),	// 頂点データ用に確保するバッファサイズ(バイト単位)
		D3DUSAGE_WRITEONLY,								// 頂点バッファの使用法　
		FVF_VERTEX_2D,									// 使用する頂点フォーマット
		D3DPOOL_MANAGED,								// リソースのバッファを保持するメモリクラスを指定
		&g_pD3DVtxBuffScore,							// 頂点バッファインターフェースへのポインタ
		NULL)))											// NULLに設定
	{
		return E_FAIL;
	}

	{//頂点バッファの中身を埋める
		VERTEX_2D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

		for (int nCntPlace = 0; nCntPlace < NUM_PLACE; nCntPlace++, pVtx += 4)
		{
			// 頂点座標の設定
			pVtx[0].vtx = D3DXVECTOR3(SCORE_POS_X + nCntPlace * SCORE_SIZE_X + SCORE_INTERVAL_X, SCORE_POS_Y, 0.0f);
			pVtx[1].vtx = D3DXVECTOR3(SCORE_POS_X + nCntPlace * (SCORE_INTERVAL_X + SCORE_SIZE_X) + SCORE_SIZE_X, SCORE_POS_Y, 0.0f);
			pVtx[2].vtx = D3DXVECTOR3(SCORE_POS_X + nCntPlace * SCORE_SIZE_X + SCORE_INTERVAL_X, SCORE_POS_Y + SCORE_SIZE_Y, 0.0f);
			pVtx[3].vtx = D3DXVECTOR3(SCORE_POS_X + nCntPlace * (SCORE_INTERVAL_X + SCORE_SIZE_X) + SCORE_SIZE_X, SCORE_POS_Y + SCORE_SIZE_Y, 0.0f);

			// rhwの設定
			pVtx[0].rhw =
			pVtx[1].rhw =
			pVtx[2].rhw =
			pVtx[3].rhw = 1.0f;

			// 反射光の設定
			pVtx[0].diffuse = 
			pVtx[1].diffuse = 
			pVtx[2].diffuse = 
			pVtx[3].diffuse = SetColorPallet(COLOR_PALLET_CYAN);

			// テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);
		}


		// 頂点データをアンロックする
		g_pD3DVtxBuffScore->Unlock();
	}

	return S_OK;
}

//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTextureScore(int idx, int number)
{
	VERTEX_2D *pVtx;

	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	g_pD3DVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += (idx * 4);

	// 頂点座標の設定
	pVtx[0].tex = D3DXVECTOR2(number * 0.1f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(number * 0.1f + 0.1f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(number * 0.1f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(number * 0.1f + 0.1f, 1.0f);

	// 頂点データをアンロックする
	g_pD3DVtxBuffScore->Unlock();
}

