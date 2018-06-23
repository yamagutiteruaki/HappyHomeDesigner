//=============================================================================
//
// スコア処理 [score.h]
// Author : 
//
//=============================================================================
#ifndef _SCORE_H_
#define _SCORE_H_

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_SCORE		"data/TEXTURE/deg_number3.png"	// 読み込むテクスチャファイル名
#define	SCORE_SIZE_X		(105.0f)							// スコアの数字の幅
#define	SCORE_SIZE_Y		(225.0f)						// スコアの数字の高さ
#define	SCORE_INTERVAL_X	(0.0f)							// スコアの数字の表示間隔

#define	NUM_PLACE			(11)							// スコアの桁数 stage.hのMAX_PRICEと桁数合わせること

#define	SCORE_POS_X			(SCREEN_CENTER_X-SCORE_SIZE_X*(5.5))						// スコアの表示基準位置Ｘ座標
#define	SCORE_POS_Y			(450.0f)				// スコアの表示基準位置Ｙ座標

#define SLOT_INTERVAL		(30)


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitScore(int nType);
void UninitScore(void);
void UpdateScore(void);
void DrawScore(void);
int GetSlotCount(void);

#endif
