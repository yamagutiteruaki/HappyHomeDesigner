
//=============================================================================
//
// タイトル画面処理 [title.h]
// Author : 
//
//=============================================================================
#ifndef _RANKPAPERLOGO_H_
#define _RANKPAPERLOGO_H_

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_RANKPAPER_BACK		"data/TEXTURE/field000.jpg"		// 読み込むテクスチャファイル名
#define	TEXTURE_RANKPAPER0			"data/TEXTURE/手配書.png"	// 読み込むテクスチャファイル名
#define	TEXTURE_RANKPAPER1			"data/TEXTURE/手配書.png"	// 読み込むテクスチャファイル名
#define	TEXTURE_RANKPAPER2			"data/TEXTURE/手配書.png"	// 読み込むテクスチャファイル名

#define	TEXTURE_FIRST				"data/TEXTURE/1st.png"	// 読み込むテクスチャファイル名
#define	TEXTURE_SECOND				"data/TEXTURE/2nd.png"			//読み込むテクスチャファイル名
#define	TEXTURE_THIRD				"data/TEXTURE/3rd.png"			//読み込むテクスチャファイル名


#define	RANKPAPERBACK_POS_X					(0)		// タイトルロゴの位置(X座標)
#define	RANKPAPERBACK_POS_Y					(0)		// タイトルロゴの位置(Y座標)
#define	RANKPAPERBACK_WIDTH					(SCREEN_WIDTH)		// タイトルロゴの幅
#define	RANKPAPERBACK_HEIGHT				(SCREEN_HEIGHT)		// タイトルロゴの高さ

#define	RANKPAPER0_POS_X					(SCREEN_WIDTH/3)		// タイトルロゴの位置(X座標)
#define	RANKPAPER0_POS_Y					(0)		// タイトルロゴの位置(Y座標)
#define	RANKPAPER0_WIDTH					(400)		// タイトルロゴの幅
#define	RANKPAPER0_HEIGHT				(400)		// タイトルロゴの高さ

#define	RANKPAPER1_POS_X					(20)		// タイトルロゴの位置(X座標)
#define	RANKPAPER1_POS_Y					(SCREEN_HEIGHT/3)		// タイトルロゴの位置(Y座標)
#define	RANKPAPER1_WIDTH					(400)		// タイトルロゴの幅
#define	RANKPAPER1_HEIGHT				(400)		// タイトルロゴの高さ

#define	RANKPAPER2_POS_X					(SCREEN_WIDTH-RANKPAPER2_WIDTH-20)		// タイトルロゴの位置(X座標)
#define	RANKPAPER2_POS_Y					(SCREEN_HEIGHT/3)		// タイトルロゴの位置(Y座標)
#define	RANKPAPER2_WIDTH					(400)		// タイトルロゴの幅
#define	RANKPAPER2_HEIGHT				(400)		// タイトルロゴの高さ

#define	RANKPAPER_FIRST_POS_X		(RANKPAPER0_POS_X+RANKPAPER0_WIDTH/4)		// タイトルロゴの位置(X座標)
#define	RANKPAPER_FIRST_POS_Y		(RANKPAPER0_HEIGHT-80)		// タイトルロゴの位置(Y座標)
#define	RANKPAPER_FIRST_WIDTH		(200)		// タイトルロゴの幅
#define	RANKPAPER_FIRST_HEIGHT		(200)		// タイトルロゴの高さ

#define	RANKPAPER_SECOND_POS_X		(RANKPAPER1_POS_X+RANKPAPER1_WIDTH/4)		// タイトルロゴの位置(X座標)
#define	RANKPAPER_SECOND_POS_Y		(SCREEN_HEIGHT/2+RANKPAPER1_HEIGHT/2)		// タイトルロゴの位置(Y座標)
#define	RANKPAPER_SECOND_WIDTH		(200)		// タイトルロゴの幅
#define	RANKPAPER_SECOND_HEIGHT		(200)		// タイトルロゴの高さ

#define	RANKPAPER_THIRD_POS_X		(RANKPAPER2_POS_X+RANKPAPER2_WIDTH/4)		// タイトルロゴの位置(X座標)
#define	RANKPAPER_THIRD_POS_Y		(SCREEN_HEIGHT/2+RANKPAPER2_HEIGHT/2)		// タイトルロゴの位置(Y座標)
#define	RANKPAPER_THIRD_WIDTH		(200)		// タイトルロゴの幅
#define	RANKPAPER_THIRD_HEIGHT		(200)		// タイトルロゴの高さ

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitRankpaper(void);
void UninitRankpaper(void);
void UpdateRankpaper(void);
void DrawRankpaper(void);

#endif