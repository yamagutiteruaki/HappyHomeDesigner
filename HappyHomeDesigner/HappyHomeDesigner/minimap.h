//=============================================================================
//
// ミニマップ処理 [minimap.h]
// Author : GP12A295-19-千坂浩太
//
//=============================================================================
#ifndef _MINIMAP_H_
#define _MINIMAP_H_

#include "field.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
// ミニマップフレーム
#define TEXTURE_MINIMAP_FRAME				("data/TEXTURE/スマホ枠.png")	// ミニマップ画像
#define MINIMAP_FRAME_POS_X					(TEXTURE_MINIMAP_FRAME_SIZE_X)
#define MINIMAP_FRAME_POS_Y					(SCREEN_HEIGHT - TEXTURE_MINIMAP_FRAME_SIZE_Y + 50.0f)
#define TEXTURE_MINIMAP_FRAME_SIZE_X		(250 / 2 * SCREEN_SCALE)			// テクスチャサイズ
#define TEXTURE_MINIMAP_FRAME_SIZE_Y		(375 / 2 * SCREEN_SCALE)			// 同上
#define MINIMAP_FRAME_MAX					(1)								// ミニマップ最大数

// ミニマップフィールド
#define TEXTURE_MINIMAP_FIELD				("data/TEXTURE/スマホ枠1.png")// ミニマップ画像
#define MINIMAP_FIELD_POS_X					(TEXTURE_MINIMAP_FIELD_SIZE_X)
#define MINIMAP_FIELD_POS_Y					(SCREEN_HEIGHT - TEXTURE_MINIMAP_FIELD_SIZE_Y + 50.0f)
#define TEXTURE_MINIMAP_FIELD_SIZE_X		(250 / 2 * SCREEN_SCALE)			// テクスチャサイズ
#define TEXTURE_MINIMAP_FIELD_SIZE_Y		(375 / 2 * SCREEN_SCALE)			// 同上
#define MINIMAP_FIELD_SCALE					((float)(TEXTURE_MINIMAP_FIELD_SIZE_X - 20)/(FIELD_SIZE_X / 2))		// ミニマップの縮尺
#define MINIMAP_FIELD_MAX					(1)								// ミニマップ最大数

// ミニマッププレイヤー
#define TEXTURE_MINIMAP_PLAYER				("data/TEXTURE/プレイヤミニマップ.png")		// プレイヤー画像
#define MINIMAP_PLAYER_POS_X				(TEXTURE_MINIMAP_PLAYER_SIZE_X)
#define MINIMAP_PLAYER_POS_Y				(SCREEN_HEIGHT - TEXTURE_MINIMAP_PLAYER_SIZE_Y)
#define TEXTURE_MINIMAP_PLAYER_SIZE_X		(15 / 2*SCREEN_SCALE)			// テクスチャサイズ
#define TEXTURE_MINIMAP_PLAYER_SIZE_Y		(15 / 2*SCREEN_SCALE)			// 同上
#define MINIMAP_PLAYER_MAX					(1)								// ミニマッププレイヤー最大数
#define MINIMAP_PLAYER_RANGE				(15.0f)							// ミニマッププレイヤーの位置制御(スマホの枠からはみ出ないように)

// ミニマップポリス
#define TEXTURE_MINIMAP_POLICE				("data/TEXTURE/スマホ枠.png")	// ポリス画像
#define MINIMAP_POLICE_POS_X				(SCREEN_CENTER_X)
#define MINIMAP_POLICE_POS_Y				(60)
#define TEXTURE_MINIMAP_POLICE_SIZE_X		(100 / 2*SCREEN_SCALE)			// テクスチャサイズ
#define TEXTURE_MINIMAP_POLICE_SIZE_Y		(100 / 2*SCREEN_SCALE)			// 同上
#define MINIMAP_POLICE_MAX					(1)								// ミニマップポリス最大数

// その他
#define	NUM_MINIMAP							(2)								// ポリゴン数

//*****************************************************************************
// 構造体宣言
//*****************************************************************************
class MINI_FRAME							// ミニマップフィールドクラス
{
public:
	bool			use;					// true:使用  false:未使用
};
class MINI_FIELD :public MINI_FRAME			// ミニマップフィールドクラス
{
};
class MINI_PLAYER :public MINI_FRAME		// ミニマッププレイヤークラス
{
public:
	D3DXVECTOR3		pos;					// 位置座標
	D3DXVECTOR3		rot;					// 回転
};
class MINI_POLICE :public MINI_FRAME		// ミニマップポリスクラス
{
public:
	D3DXVECTOR3		pos;					// 位置座標
	D3DXVECTOR3		rot;					// 回転
};
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitMinimap(int type);
void UninitMinimap(void);
void UpdateMinimap(void);
void DrawMinimap(void);
MINI_FIELD *GetMiniField(int no);

#endif
