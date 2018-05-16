//=============================================================================
//
// 敵処理 [arrest.cpp]
// Author : 松尾公平
//
//=============================================================================
#include "main.h"
#include "arrest.h"
#include "clock.h"
#include "player.h"
#include "field.h"
#include "input.h"
#include "fade.h"
#include "stage.h"
#include "voice.h"
#include <time.h>

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexArrest(int no);
void SetTextureArrest(int no, int cntPattern);
void SetVertexArrest(int no);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureArrest = NULL;		// テクスチャへのポリゴン

ARREST					arrestWk[ARREST_MAX];				// エネミー構造体

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitArrest(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	ARREST *arrest = arrestWk;				// エネミーのポインターを初期化

										// テクスチャーの初期化を行う？
	if (type == 0)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,	// デバイスのポインタ
			TEXTURE_GAME_ARREST,				// ファイルの名前
			&g_pD3DTextureArrest);			// 読み込むメモリのポインタ
	}
	int cnt = 0;
	// エネミーの初期化処理
	for (int i = 0; i < ARREST_MAX; i++, arrest++, cnt++)
	{
		arrest->use = true;										// 使用
		arrest->pos = D3DXVECTOR3(SCREEN_WIDTH-TEXTURE_ARREST_SIZE_X, 50+100*i, 0.0f);	// 座標データを初期化
		arrest->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// 回転データを初期化
		arrest->cnt_frame = 0;									// フレームを数えたい
		D3DXVECTOR2 temp = D3DXVECTOR2(TEXTURE_ARREST_SIZE_X, TEXTURE_ARREST_SIZE_Y);
		arrest->Radius = D3DXVec2Length(&temp);					// エネミーの半径を初期化
		arrest->BaseAngle = atan2f(TEXTURE_ARREST_SIZE_Y, TEXTURE_ARREST_SIZE_X);	// エネミーの角度を初期化

		arrest->Texture = g_pD3DTextureArrest;					// テクスチャ情報
		MakeVertexArrest(i);										// 頂点情報の作成
	}



	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitArrest(void)
{
	if (g_pD3DTextureArrest != NULL)
	{	// テクスチャの開放
		g_pD3DTextureArrest->Release();
		g_pD3DTextureArrest = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateArrest(void)
{

	ARREST *arrest = arrestWk;				// エネミーのポインターを初期化
	VOICE *voice = GetVoice(0);

	for (int i = 0; i < ARREST_MAX; i++, arrest++)
	{
			SetVertexArrest(i);	// 移動後の座標で頂点を設定
	}

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawArrest(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	ARREST *arrest = arrestWk;				// エネミーのポインターを初期化
	VOICE *voice = GetVoice(0);

										// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < voice->count; i++, arrest++)
	{
		if (arrest->use == true)			// 使用している状態なら描画する
		{
			// テクスチャの設定
			pDevice->SetTexture(0, arrest->Texture);

			// ポリゴンの描画
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_ARREST, arrest->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexArrest(int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	ARREST *arrest = &arrestWk[no];			// エネミーのポインターを初期化

											// 頂点座標の設定
	SetVertexArrest(no);

	// rhwの設定
	arrest->vertexWk[0].rhw =
		arrest->vertexWk[1].rhw =
		arrest->vertexWk[2].rhw =
		arrest->vertexWk[3].rhw = 1.0f;

	// 反射光の設定
	arrest->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	arrest->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	arrest->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	arrest->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	arrest->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	arrest->vertexWk[1].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_ARREST, 0.0f);
	arrest->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_ARREST);
	arrest->vertexWk[3].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_ARREST, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_ARREST);

	//arrest->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	//arrest->vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	//arrest->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	//arrest->vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}

//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTextureArrest(int no, int cntPattern)
{
	ARREST *arrest = &arrestWk[no];			// エネミーのポインターを初期化

											// テクスチャ座標の設定
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_ARREST;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_ARREST;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_ARREST;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_ARREST;

	arrest->vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
	arrest->vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
	arrest->vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
	arrest->vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexArrest(int no)
{
	ARREST *arrest = &arrestWk[no];			// エネミーのポインターを初期化

											// 頂点座標の設定
	arrest->vertexWk[0].vtx.x = arrest->pos.x - cosf(arrest->BaseAngle + arrest->rot.z) * arrest->Radius;
	arrest->vertexWk[0].vtx.y = arrest->pos.y - sinf(arrest->BaseAngle + arrest->rot.z) * arrest->Radius;
	arrest->vertexWk[0].vtx.z = 0.0f;

	arrest->vertexWk[1].vtx.x = arrest->pos.x + cosf(arrest->BaseAngle - arrest->rot.z) * arrest->Radius;
	arrest->vertexWk[1].vtx.y = arrest->pos.y - sinf(arrest->BaseAngle - arrest->rot.z) * arrest->Radius;
	arrest->vertexWk[1].vtx.z = 0.0f;

	arrest->vertexWk[2].vtx.x = arrest->pos.x - cosf(arrest->BaseAngle - arrest->rot.z) * arrest->Radius;
	arrest->vertexWk[2].vtx.y = arrest->pos.y + sinf(arrest->BaseAngle - arrest->rot.z) * arrest->Radius;
	arrest->vertexWk[2].vtx.z = 0.0f;

	arrest->vertexWk[3].vtx.x = arrest->pos.x + cosf(arrest->BaseAngle + arrest->rot.z) * arrest->Radius;
	arrest->vertexWk[3].vtx.y = arrest->pos.y + sinf(arrest->BaseAngle + arrest->rot.z) * arrest->Radius;
	arrest->vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// エネミー取得関数
//=============================================================================
ARREST *GetArrest(int no)
{
	return(&arrestWk[no]);
}
