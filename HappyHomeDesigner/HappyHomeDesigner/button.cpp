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
void SetVertexButton(int no);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureButton[BUTTON_MAX] = { NULL ,NULL,NULL };		// テクスチャへのポリゴン

BUTTON					buttonWk[BUTTON_MAX];				// エネミー構造体

const char *FileNameButton[BUTTON_MAX] =
{
	TEXTURE_GAME_BUTTON_0,
	TEXTURE_GAME_BUTTON_3,
	TEXTURE_GAME_BUTTON_1,
	TEXTURE_GAME_BUTTON_2,
};
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitButton(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BUTTON *button = buttonWk;				// エネミーのポインターを初期化


	if (type == STAGE_INIT_FAST)
	{
		for (int i = 0; i < BUTTON_MAX; i++)
		{
			D3DXCreateTextureFromFile(pDevice,	// デバイスのポインタ
				FileNameButton[i],				// ファイルの名前
				&g_pD3DTextureButton[i]);			// 読み込むメモリのポインタ

		}
	}										// エネミーの初期化処理
	for (int i = 0; i < BUTTON_MAX; i++, button++)
	{
		button->use = false;										// 使用
		button->pos = D3DXVECTOR3(SCREEN_WIDTH + TEXTURE_BUTTON_SIZE_X, SCREEN_HEIGHT - TEXTURE_BUTTON_SIZE_Y, 0.0f);	// 座標データを初期化
		button->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// 回転データを初期化
		button->kind = 0;									// フレームを数えたい
		D3DXVECTOR2 temp = D3DXVECTOR2(TEXTURE_BUTTON_SIZE_X, TEXTURE_BUTTON_SIZE_Y);
		button->Radius = D3DXVec2Length(&temp);					// エネミーの半径を初期化
		button->BaseAngle = atan2f(TEXTURE_BUTTON_SIZE_Y, TEXTURE_BUTTON_SIZE_X);	// エネミーの角度を初期化

		button->Texture = g_pD3DTextureButton[i];					// テクスチャ情報
		
		button->rate = D3DXVECTOR2(10,10);

																	// テクスチャの読み込み


		MakeVertexButton(i);										// 頂点情報の作成
	}






	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitButton(void)
{
	for (int i = 0; i < BUTTON_MAX; i++)
	{
		if (g_pD3DTextureButton != NULL)
		{	// テクスチャの開放
			g_pD3DTextureButton[i]->Release();
			g_pD3DTextureButton[i] = NULL;
		}
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

		if (button->use == true)
		{
			if (button->rate.x > 0)
			{
				button->rate.x -= 0.5f;
			}
			if (button->pos.x < SCREEN_WIDTH - TEXTURE_BUTTON_SIZE_X)
			{
				button->pos.x = SCREEN_WIDTH - TEXTURE_BUTTON_SIZE_X;
				button->rate.x = 0;
			}
			else
			{
				button->pos.x -= 5 * button->rate.x;
			}

		}
		else
		{
			if (button->rate.x < 10)
			{
				button->rate.x += 0.5f;
			}
			if (button->pos.x > SCREEN_WIDTH + TEXTURE_BUTTON_SIZE_X)
			{
				button->pos.x = SCREEN_WIDTH + TEXTURE_BUTTON_SIZE_X;
				button->rate.x = 10;
				button->pos = D3DXVECTOR3(SCREEN_WIDTH + TEXTURE_BUTTON_SIZE_X, SCREEN_HEIGHT - TEXTURE_BUTTON_SIZE_Y, 0.0f);	// 座標データを初期化
			}
			else
			{
				button->pos.x += 5 * button->rate.x;
			}


		}
		SetVertexButton(i);	// 移動後の座標で頂点を設定
	}


	if (buttonWk[ENTER_BUTTON].use == true || buttonWk[GET_BUTTON].use == true|| buttonWk[EXIT_BUTTON].use == true)
	{
		if (buttonWk[PUT_BUTTON].rate.y > 0)
		{
			buttonWk[PUT_BUTTON].rate.y -= 0.5f;
		}
		if (buttonWk[PUT_BUTTON].pos.y < SCREEN_HEIGHT - (3 * TEXTURE_BUTTON_SIZE_Y))
		{
			buttonWk[PUT_BUTTON].pos.y = SCREEN_HEIGHT - (3 * TEXTURE_BUTTON_SIZE_Y);
			buttonWk[PUT_BUTTON].rate.y = 0;
		}
		else
		{
			buttonWk[PUT_BUTTON].pos.y -= 5 * buttonWk[PUT_BUTTON].rate.y;
		}

	}
	else if (buttonWk[ENTER_BUTTON].use == false && buttonWk[GET_BUTTON].use == false)
	{
		if (buttonWk[PUT_BUTTON].rate.y < 10)
		{
			buttonWk[PUT_BUTTON].rate.y += 0.5f;
		}
		if (buttonWk[PUT_BUTTON].pos.y >= SCREEN_HEIGHT - TEXTURE_BUTTON_SIZE_Y)
		{
			buttonWk[PUT_BUTTON].pos.y = SCREEN_HEIGHT - TEXTURE_BUTTON_SIZE_Y;
			buttonWk[PUT_BUTTON].rate.y = 10;
		}
		else
		{
			buttonWk[PUT_BUTTON].pos.y += 5 * buttonWk[PUT_BUTTON].rate.y;
		}


	}
	SetVertexButton(PUT_BUTTON);	// 移動後の座標で頂点を設定

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
	button->vertexWk[0].diffuse =
		button->vertexWk[1].diffuse =
		button->vertexWk[2].diffuse =
		button->vertexWk[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// テクスチャ座標の設定
	button->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	button->vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	button->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	button->vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
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
void Button(bool flag,int no)
{
	BUTTON *button = &buttonWk[no];				// エネミーのポインターを初期化

	button->use = flag;
}
