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
#define	NUM_MINIMAP							(2)										// ポリゴン数

#define TEXTURE_MINIMAP_FIELD				("data/TEXTURE/clock.png")				// ミニマップ画像
#define TEXTURE_MINIMAP_PLAYER				("data/TEXTURE/clock.png")				// プレイヤー画像
#define TEXTURE_MINIMAP_POLICE				("data/TEXTURE/clock.png")				// ポリス画像

#define MINIMAP_POS_X						(SCREEN_CENTER_X)
#define MINIMAP_POS_Y						(60)

#define	MINIMAP_WIDTH						(100 / 2*SCREEN_SCALE)					// タイマーの幅
#define	MINIMAP_HEIGHT						(100 / 2*SCREEN_SCALE)					// タイマーの高さ

#define TEXTURE_MINIMAP_FIELD_SIZE_X		(100/2)									// テクスチャサイズ
#define TEXTURE_MINIMAP_FIELD_SIZE_Y		(100/2)									// 同上
#define TEXTURE_MINIMAP_PLAYER_SIZE_X		(100/2)									// テクスチャサイズ
#define TEXTURE_MINIMAP_PLAYER_SIZE_Y		(100/2)									// 同上
#define TEXTURE_MINIMAP_POLICE_SIZE_X		(100/2)									// テクスチャサイズ
#define TEXTURE_MINIMAP_POLICE_SIZE_Y		(100/2)									// 同上

#define MINIMAP_MAX							(1) 

//*****************************************************************************
// 構造体宣言
//*****************************************************************************
typedef struct		// ミニマップ構造体
{
	bool			use;					// true:使用  false:未使用
	D3DXVECTOR3		pos;					// ポリゴンの移動量
	D3DXVECTOR3		rot;					// ポリゴンの回転量
	VERTEX_2D		vertexWk[NUM_VERTEX];	// 頂点情報格納ワーク

} MINIMAP;
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitMinimap(int type);
void UninitMinimap(void);
void UpdateMinimap(void);
void DrawMinimap(void);
MINIMAP *GetMinimap(int no);


#endif
