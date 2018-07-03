//=============================================================================
//
// プレイヤー処理 [run.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "run.h"
#include "input.h"
#include "stage.h"
#include "rankpaper.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexRun(int no);
void SetTextureRun(int no, int cntPattern);
void SetVertexRun(int no);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureRun = NULL;		// テクスチャへのポリゴン

RUN					runWk[RUN_MAX];			// プレイヤー構造体


//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitRun(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	RUN *run = &runWk[0];

	// テクスチャーの初期化を行う？
	if (type == STAGE_INIT_FAST)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,		// デバイスのポインタ
			TEXTURE_GAME_RUN,				// ファイルの名前
			&g_pD3DTextureRun);				// 読み込むメモリのポインタ
	}

	// プレイヤーの初期化処理
	for (int i = 0; i < RUN_MAX; i++, run++)
	{
		run->use = true;									// 使用
		run->pos = D3DXVECTOR3(SCREEN_WIDTH+TEXTURE_RUN_SIZE_X, 900.0f, 0.0f);	// 座標データを初期化
		run->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 回転データを初期化
		run->PatternAnim = rand() % ANIM_PATTERN_NUM;	// アニメパターン番号をランダムで初期化
		run->CountAnim = 0;								// アニメカウントを初期化

		D3DXVECTOR2 temp = D3DXVECTOR2(TEXTURE_RUN_SIZE_X, TEXTURE_RUN_SIZE_Y);
		run->Radius = D3DXVec2Length(&temp);				// プレイヤーの半径を初期化
		run->BaseAngle = atan2f(TEXTURE_RUN_SIZE_Y, TEXTURE_RUN_SIZE_X);	// プレイヤーの角度を初期化

		run->Texture = g_pD3DTextureRun;				// テクスチャ情報
		MakeVertexRun(i);								// 頂点情報の作成
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitRun(void)
{
	if (g_pD3DTextureRun != NULL)
	{	// テクスチャの開放
		g_pD3DTextureRun->Release();
		g_pD3DTextureRun = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateRun(void)
{
	D3DXVECTOR3 Bgpos = GetRankBackPos();

	if (Bgpos.y >= 0)
	{
		RUN *run = &runWk[0];

		for (int i = 0; i < RUN_MAX; i++, run++)
		{
			if (run->use == true)			// 使用している状態なら更新する
			{
				run->pos.x -= 20;
				// アニメーション
				run->CountAnim++;
				if ((run->CountAnim % TIME_ANIMATION) == 0)
				{
					// パターンの切り替え
					run->PatternAnim = (run->PatternAnim + 1) % ANIM_PATTERN_NUM;

					// テクスチャ座標を設定
					SetTextureRun(i, run->PatternAnim);
				}
				// 移動後の座標で頂点を設定
				SetVertexRun(i);
			}
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawRun(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	RUN *run = &runWk[0];

	//// αテストを有効に
	//pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	//pDevice->SetRenderState(D3DRS_ALPHAREF, 128);
	//pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	//pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < RUN_MAX; i++, run++)
	{
		if (run->use == true)			// 使用している状態なら描画する
		{
			// テクスチャの設定
			pDevice->SetTexture(0, run->Texture);

			// ポリゴンの描画
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_RUN, run->vertexWk, sizeof(VERTEX_2D));
		}
	}

	//// αテストを無効に
	//pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexRun(int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	RUN *run = &runWk[no];

	// 頂点座標の設定
	SetVertexRun(no);

	// rhwの設定
	run->vertexWk[0].rhw =
		run->vertexWk[1].rhw =
		run->vertexWk[2].rhw =
		run->vertexWk[3].rhw = 1.0f;

	// 反射光の設定
	run->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	run->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	run->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 0);
	run->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 0);

	// テクスチャ座標の設定
	run->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	run->vertexWk[1].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X, 0.0f);
	run->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_PATTERN_DIVIDE_Y);
	run->vertexWk[3].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X, 1.0f / TEXTURE_PATTERN_DIVIDE_Y);

	return S_OK;
}

//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTextureRun(int no, int cntPattern)
{
	RUN *run = &runWk[no];

	// テクスチャ座標の設定
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y;

	run->vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
	run->vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
	run->vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
	run->vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexRun(int no)
{
	RUN *run = &runWk[no];

	// 頂点座標の設定
	run->vertexWk[0].vtx.x = run->pos.x - cosf(run->BaseAngle + run->rot.z) * run->Radius;
	run->vertexWk[0].vtx.y = run->pos.y - sinf(run->BaseAngle + run->rot.z) * run->Radius;
	run->vertexWk[0].vtx.z = 0.0f;

	run->vertexWk[1].vtx.x = run->pos.x + cosf(run->BaseAngle - run->rot.z) * run->Radius;
	run->vertexWk[1].vtx.y = run->pos.y - sinf(run->BaseAngle - run->rot.z) * run->Radius;
	run->vertexWk[1].vtx.z = 0.0f;

	run->vertexWk[2].vtx.x = run->pos.x - cosf(run->BaseAngle - run->rot.z) * run->Radius;
	run->vertexWk[2].vtx.y = run->pos.y + sinf(run->BaseAngle - run->rot.z) * run->Radius;
	run->vertexWk[2].vtx.z = 0.0f;

	run->vertexWk[3].vtx.x = run->pos.x + cosf(run->BaseAngle + run->rot.z) * run->Radius;
	run->vertexWk[3].vtx.y = run->pos.y + sinf(run->BaseAngle + run->rot.z) * run->Radius;
	run->vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// プレイヤー取得関数
//=============================================================================
RUN *GetRun(int no)
{
	return(&runWk[no]);
}

