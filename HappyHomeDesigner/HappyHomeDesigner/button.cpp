//=============================================================================
//
// 敵処理 [button.cpp]
// Author : 松尾公平
//
//=============================================================================
#include "main.h"
#include "button.h"
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
HRESULT MakeVertexButton(int no);
void SetTextureButton(int no, int cntPattern);
void SetVertexButton(int no);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureButton = NULL;		// テクスチャへのポリゴン

BUTTON					buttonWk[BUTTON_MAX];				// エネミー構造体
float rate;
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitButton(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BUTTON *button = buttonWk;				// エネミーのポインターを初期化

											// テクスチャーの初期化を行う？
	if (button->kind == 0)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,	// デバイスのポインタ
			TEXTURE_GAME_BUTTON_0,				// ファイルの名前
			&g_pD3DTextureButton);			// 読み込むメモリのポインタ
	}
	if (button->kind == 1)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,	// デバイスのポインタ
			TEXTURE_GAME_BUTTON_1,				// ファイルの名前
			&g_pD3DTextureButton);			// 読み込むメモリのポインタ
	}
	if (button->kind == 2)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,	// デバイスのポインタ
			TEXTURE_GAME_BUTTON_2,				// ファイルの名前
			&g_pD3DTextureButton);			// 読み込むメモリのポインタ
	}

	rate = 10;

	// エネミーの初期化処理
	for (int i = 0; i < BUTTON_MAX; i++, button++)
	{
		button->use = false;										// 使用
		button->pos = D3DXVECTOR3(SCREEN_WIDTH + TEXTURE_BUTTON_SIZE_X,SCREEN_HEIGHT-TEXTURE_BUTTON_SIZE_Y, 0.0f);	// 座標データを初期化
		button->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// 回転データを初期化
		button->kind = 0;									// フレームを数えたい
		D3DXVECTOR2 temp = D3DXVECTOR2(TEXTURE_BUTTON_SIZE_X, TEXTURE_BUTTON_SIZE_Y);
		button->Radius = D3DXVec2Length(&temp);					// エネミーの半径を初期化
		button->BaseAngle = atan2f(TEXTURE_BUTTON_SIZE_Y, TEXTURE_BUTTON_SIZE_X);	// エネミーの角度を初期化

		button->Texture = g_pD3DTextureButton;					// テクスチャ情報
		MakeVertexButton(i);										// 頂点情報の作成
	}



	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitButton(void)
{
	if (g_pD3DTextureButton != NULL)
	{	// テクスチャの開放
		g_pD3DTextureButton->Release();
		g_pD3DTextureButton = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateButton(void)
{

	BUTTON *button = buttonWk;				// エネミーのポインターを初期化
	VOICE *voice = GetVoice(0);
	for (int i = 0; i < BUTTON_MAX; i++, button++)
	{
		if (GetKeyboardTrigger(DIK_Q))
		{
			SetFade(FADE_OUT, STAGE_HOUSE2);
		}
#ifdef DEBUG
		if (GetKeyboardTrigger(DIK_B))
		{
			Button();
		}
#endif

		if (button->use == true)
		{
			if (rate > 0)
			{
				rate -= 0.5f;
			}
			if (button->pos.x < SCREEN_WIDTH - TEXTURE_BUTTON_SIZE_X)
			{
				button->pos.x = SCREEN_WIDTH - TEXTURE_BUTTON_SIZE_X;
				rate = 0;
			}
			else
			{
				button->pos.x -= 5 * rate;
			}

		}
		else
		{

			button->use = false;
			rate = 10;

			button->pos = D3DXVECTOR3(SCREEN_WIDTH + TEXTURE_BUTTON_SIZE_X, SCREEN_HEIGHT - TEXTURE_BUTTON_SIZE_Y, 0.0f);	// 座標データを初期化
		}
		SetVertexButton(i);	// 移動後の座標で頂点を設定
	}

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawButton(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BUTTON *button = buttonWk;				// エネミーのポインターを初期化
	VOICE *voice = GetVoice(0);

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < BUTTON_MAX; i++, button++)
	{
			// テクスチャの設定
			pDevice->SetTexture(0, button->Texture);

			// ポリゴンの描画
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_BUTTON, button->vertexWk, sizeof(VERTEX_2D));
	}
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexButton(int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BUTTON *button = &buttonWk[no];			// エネミーのポインターを初期化

											// 頂点座標の設定
	SetVertexButton(no);

	// rhwの設定
	button->vertexWk[0].rhw =
		button->vertexWk[1].rhw =
		button->vertexWk[2].rhw =
		button->vertexWk[3].rhw = 1.0f;

	// 反射光の設定
	button->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	button->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	button->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	button->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	button->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	button->vertexWk[1].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_BUTTON, 0.0f);
	button->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_BUTTON);
	button->vertexWk[3].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_BUTTON, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_BUTTON);

	//button->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	//button->vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	//button->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	//button->vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}

//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTextureButton(int no, int cntPattern)
{
	BUTTON *button = &buttonWk[no];			// エネミーのポインターを初期化

											// テクスチャ座標の設定
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_BUTTON;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_BUTTON;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_BUTTON;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_BUTTON;

	button->vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
	button->vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
	button->vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
	button->vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexButton(int no)
{
	BUTTON *button = &buttonWk[no];			// エネミーのポインターを初期化

											// 頂点座標の設定
	button->vertexWk[0].vtx.x = button->pos.x - cosf(button->BaseAngle + button->rot.z) * button->Radius;
	button->vertexWk[0].vtx.y = button->pos.y - sinf(button->BaseAngle + button->rot.z) * button->Radius;
	button->vertexWk[0].vtx.z = 0.0f;

	button->vertexWk[1].vtx.x = button->pos.x + cosf(button->BaseAngle - button->rot.z) * button->Radius;
	button->vertexWk[1].vtx.y = button->pos.y - sinf(button->BaseAngle - button->rot.z) * button->Radius;
	button->vertexWk[1].vtx.z = 0.0f;

	button->vertexWk[2].vtx.x = button->pos.x - cosf(button->BaseAngle - button->rot.z) * button->Radius;
	button->vertexWk[2].vtx.y = button->pos.y + sinf(button->BaseAngle - button->rot.z) * button->Radius;
	button->vertexWk[2].vtx.z = 0.0f;

	button->vertexWk[3].vtx.x = button->pos.x + cosf(button->BaseAngle + button->rot.z) * button->Radius;
	button->vertexWk[3].vtx.y = button->pos.y + sinf(button->BaseAngle + button->rot.z) * button->Radius;
	button->vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// エネミー取得関数
//=============================================================================
BUTTON *GetButton(int no)
{
	return(&buttonWk[no]);
}

//========================================================
// ボタンの表示　falseならtrueを、trueならfalseを。
//========================================================
bool Button(void)
{
	BUTTON *button = buttonWk;				// エネミーのポインターを初期化

	return button->use = button->use ? false : true;
	//return button->use = true;

}
