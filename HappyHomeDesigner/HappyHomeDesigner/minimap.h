//=============================================================================
//
// ミニマップ処理 [minimap.h]
// Author : GP12A295-19-千坂浩太
//
//=============================================================================
#ifndef _MINIMAP_H_
#define _MINIMAP_H_

//*****************************************************************************
// マクロ定義
//*****************************************************************************
// ミニマップフィールド
#define TEXTURE_MINIMAP_FIELD				("data/TEXTURE/スマホ枠.png")	// ミニマップ画像
#define MINIMAP_FIELD_POS_X					(SCREEN_CENTER_X)
#define MINIMAP_FIELD_POS_Y					(60)
#define	MINIMAP_FIELD_WIDTH					(100 / 2*SCREEN_SCALE)			// ミニマップフィールドの幅
#define	MINIMAP_FIELD_HEIGHT				(100 / 2*SCREEN_SCALE)			// ミニマップフィールドの高さ
#define TEXTURE_MINIMAP_FIELD_SIZE_X		(100/2)							// テクスチャサイズ
#define TEXTURE_MINIMAP_FIELD_SIZE_Y		(100/2)							// 同上
#define MINIMAP_FIELD_MAX					(1)								// ミニマップ最大数

// ミニマッププレイヤー
#define TEXTURE_MINIMAP_PLAYER				("data/TEXTURE/スマホ枠.png")		// プレイヤー画像
#define MINIMAP_PLAYER_POS_X				(SCREEN_CENTER_X)
#define MINIMAP_PLAYER_POS_Y				(160)
#define	MINIMAP_PLAYER_WIDTH				(100 / 2*SCREEN_SCALE)			// ミニマッププレイヤーの幅
#define	MINIMAP_PLAYER_HEIGHT				(100 / 2*SCREEN_SCALE)			// ミニマッププレイヤーの高さ
#define TEXTURE_MINIMAP_PLAYER_SIZE_X		(100/2)							// テクスチャサイズ
#define TEXTURE_MINIMAP_PLAYER_SIZE_Y		(100/2)							// 同上
#define MINIMAP_PLAYER_MAX					(1)								// ミニマッププレイヤー最大数

// ミニマップポリス
#define TEXTURE_MINIMAP_POLICE				("data/TEXTURE/スマホ枠.png")		// ポリス画像
#define MINIMAP_POLICE_POS_X				(SCREEN_CENTER_X)
#define MINIMAP_POLICE_POS_Y				(60)
#define	MINIMAP_POLICE_WIDTH				(100 / 2*SCREEN_SCALE)			// ミニマップポリスの幅
#define	MINIMAP_POLICE_HEIGHT				(100 / 2*SCREEN_SCALE)			// ミニマップポリスの高さ
#define TEXTURE_MINIMAP_POLICE_SIZE_X		(100/2)							// テクスチャサイズ
#define TEXTURE_MINIMAP_POLICE_SIZE_Y		(100/2)							// 同上
#define MINIMAP_POLICE_MAX					(1)								// ミニマップポリス最大数

// その他
#define	NUM_MINIMAP							(2)								// ポリゴン数

//*****************************************************************************
// 構造体宣言
//*****************************************************************************
class MINI_FIELD							// ミニマップフィールドクラス
{
public:
	bool			use;					// true:使用  false:未使用
	VERTEX_2D		vertexWk[NUM_VERTEX];	// 頂点情報格納ワーク
};
class MINI_PLAYER :public MINI_FIELD		// ミニマッププレイヤークラス
{
public:
	D3DXVECTOR3		pos;					// 位置座標
	D3DXVECTOR3		rot;					// 回転
};
class MINI_POLICE :public MINI_FIELD		// ミニマップポリスクラス
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
