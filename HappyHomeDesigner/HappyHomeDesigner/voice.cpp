//=============================================================================
//
// 敵処理 [voice.cpp]
// Author : 松尾公平
//
//=============================================================================
#include "main.h"
#include "voice.h"
#include "clock.h"
#include "player.h"
#include "field.h"
#include "input.h"
#include "fade.h"
#include "stage.h"
#include "arrest.h"
#include <time.h>
#include "camera.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexVoice(int no);
void SetTextureVoice(int no, int cntPattern);
void SetVertexVoice(int no);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureVoice = NULL;		// テクスチャへのポリゴン

VOICE					voiceWk[VOICE_MAX];				// エネミー構造体

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitVoice(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	VOICE *voice = voiceWk;				// エネミーのポインターを初期化

										// テクスチャーの初期化を行う？
	if (type == 0)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,	// デバイスのポインタ
			TEXTURE_GAME_VOICE,				// ファイルの名前
			&g_pD3DTextureVoice);			// 読み込むメモリのポインタ
	}
	int cnt = 0;
	// エネミーの初期化処理
	for (int i = 0; i < VOICE_MAX; i++, voice++, cnt++)
	{
		voice->use = false;										// 使用
		voice->pos = D3DXVECTOR3(SCREEN_WIDTH*2, 350.0f, 0.0f);	// 座標データを初期化
		voice->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// 回転データを初期化
		voice->cnt_frame = 0;									// フレームを数えたい
		D3DXVECTOR2 temp = D3DXVECTOR2(TEXTURE_VOICE_SIZE_X, TEXTURE_VOICE_SIZE_Y);
		voice->Radius = D3DXVec2Length(&temp);					// エネミーの半径を初期化
		voice->BaseAngle = atan2f(TEXTURE_VOICE_SIZE_Y, TEXTURE_VOICE_SIZE_X);	// エネミーの角度を初期化
		voice->count = 0;

		voice->Texture = g_pD3DTextureVoice;					// テクスチャ情報
		MakeVertexVoice(i);										// 頂点情報の作成
	}



	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitVoice(void)
{
	if (g_pD3DTextureVoice != NULL)
	{	// テクスチャの開放
		g_pD3DTextureVoice->Release();
		g_pD3DTextureVoice = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateVoice(void)
{

	VOICE *voice = voiceWk;				// エネミーのポインターを初期化
	PLAYER *player = GetPlayer(0);
	FIELD *field = GetField(0);
	CAMERA *camera = GetCamera();


	for (int i = 0; i < VOICE_MAX; i++, voice++)
	{

		if (GetKeyboardTrigger(DIK_V))
		{
			voice->use = voice->use ? false : true;
		}
		if (voice->use == true)			// 使用している状態なら更新する
		{

			voice->cnt_frame++;
			if (voice->cnt_frame >= 60)
			{
				if (voice->count == ARREST_MAX)
				{
					SetFade(FADE_OUT, STAGE_RESULT);
				}
				else
				{
					SetFade(FADE_OUT, STAGE_GAME);
				}

				if (GetFade() == FADE_IN)
				{
					player->Eye = field->Pos;
					player->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
					player->rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
					camera->rotCamera = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
					voice->use = false;
					voice->count++;
				}
			}
			if (voice->pos.x > SCREEN_CENTER_X)
			{
				voice->pos.x -= VOICE_SPEED;
			}
			if (voice->pos.x < SCREEN_CENTER_X)
			{
				voice->pos.x += VOICE_SPEED/5;
			}
		

			SetVertexVoice(i);	// 移動後の座標で頂点を設定
		}
		else
		{
			voice->pos = D3DXVECTOR3(SCREEN_WIDTH * 2, 350.0f, 0.0f);
			voice->cnt_frame = 0;
		}
	}

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawVoice(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	VOICE *voice = voiceWk;				// エネミーのポインターを初期化

										// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < VOICE_MAX; i++, voice++)
	{
		if (voice->use == true)			// 使用している状態なら描画する
		{
			// テクスチャの設定
			pDevice->SetTexture(0, voice->Texture);

			// ポリゴンの描画
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_VOICE, voice->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexVoice(int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	VOICE *voice = &voiceWk[no];			// エネミーのポインターを初期化

											// 頂点座標の設定
	SetVertexVoice(no);

	// rhwの設定
	voice->vertexWk[0].rhw =
		voice->vertexWk[1].rhw =
		voice->vertexWk[2].rhw =
		voice->vertexWk[3].rhw = 1.0f;

	// 反射光の設定
	voice->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 0, 255);
	voice->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 0, 255);
	voice->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 0, 255);
	voice->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 0, 255);

	// テクスチャ座標の設定
	voice->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	voice->vertexWk[1].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_VOICE, 0.0f);
	voice->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_VOICE);
	voice->vertexWk[3].tex = D3DXVECTOR2(1.0f / TEXTURE_PATTERN_DIVIDE_X_VOICE, 1.0f / TEXTURE_PATTERN_DIVIDE_Y_VOICE);

	//voice->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	//voice->vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	//voice->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	//voice->vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}

//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTextureVoice(int no, int cntPattern)
{
	VOICE *voice = &voiceWk[no];			// エネミーのポインターを初期化

											// テクスチャ座標の設定
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_VOICE;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_VOICE;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_VOICE;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_VOICE;

	voice->vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
	voice->vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
	voice->vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
	voice->vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexVoice(int no)
{
	VOICE *voice = &voiceWk[no];			// エネミーのポインターを初期化

											// 頂点座標の設定
	voice->vertexWk[0].vtx.x = voice->pos.x - cosf(voice->BaseAngle + voice->rot.z) * voice->Radius;
	voice->vertexWk[0].vtx.y = voice->pos.y - sinf(voice->BaseAngle + voice->rot.z) * voice->Radius;
	voice->vertexWk[0].vtx.z = 0.0f;

	voice->vertexWk[1].vtx.x = voice->pos.x + cosf(voice->BaseAngle - voice->rot.z) * voice->Radius;
	voice->vertexWk[1].vtx.y = voice->pos.y - sinf(voice->BaseAngle - voice->rot.z) * voice->Radius;
	voice->vertexWk[1].vtx.z = 0.0f;

	voice->vertexWk[2].vtx.x = voice->pos.x - cosf(voice->BaseAngle - voice->rot.z) * voice->Radius;
	voice->vertexWk[2].vtx.y = voice->pos.y + sinf(voice->BaseAngle - voice->rot.z) * voice->Radius;
	voice->vertexWk[2].vtx.z = 0.0f;

	voice->vertexWk[3].vtx.x = voice->pos.x + cosf(voice->BaseAngle + voice->rot.z) * voice->Radius;
	voice->vertexWk[3].vtx.y = voice->pos.y + sinf(voice->BaseAngle + voice->rot.z) * voice->Radius;
	voice->vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// エネミー取得関数
//=============================================================================
VOICE *GetVoice(int no)
{
	return(&voiceWk[no]);
}
