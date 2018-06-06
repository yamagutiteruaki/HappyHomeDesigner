//=============================================================================
//
// タイマー処理 [clock.h]
// Author : 
//
//=============================================================================
#ifndef _WEIGHT_H_
#define _WEIGHT_H_


// マクロ定義
#define	NUM_WEIGHT				(4)			// ポリゴン数

#define TEXTURE_WEIGHT		("data/TEXTURE/power01.png")	// 画像
#define TEXTURE_WEIGHT2		("data/TEXTURE/power01.png")	// 画像
#define TEXTURE_WEIGHT_X	(150)		// テクスチャサイズ
#define TEXTURE_WEIGHT_Y	(150)		// 同上
#define TEXTURE_WEIGHT_SIZE_X	( TEXTURE_WEIGHT_X*SCREEN_SCALE)		// テクスチャサイズ
#define TEXTURE_WEIGHT_SIZE_Y	( TEXTURE_WEIGHT_Y*SCREEN_SCALE)		// 同上
#define TEXTURE_WEIGHT_POS_X	(10*SCREEN_SCALE)		// テクスチャサイズ
#define TEXTURE_WEIGHT_POS_Y	(10*SCREEN_SCALE)		// 同上
#define WEIGHT_MAX						(4) // 力の最大数

//*****************************************************************************
// 構造体宣言
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitWeight(int type);
void UninitWeight(void);
void UpdateWeight(void);
void DrawWeight(void);

#endif
