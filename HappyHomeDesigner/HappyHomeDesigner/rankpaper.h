
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
#define	TEXTURE_RANKPAPER0			"data/TEXTURE/手配書.png"		// 読み込むテクスチャファイル名
#define	TEXTURE_RANKPAPER1			"data/TEXTURE/手配書.png"		// 読み込むテクスチャファイル名
#define	TEXTURE_RANKPAPER2			"data/TEXTURE/手配書.png"		// 読み込むテクスチャファイル名

#define	TEXTURE_FIRST				"data/TEXTURE/1st.png"			// 読み込むテクスチャファイル名
#define	TEXTURE_SECOND				"data/TEXTURE/2nd.png"			//読み込むテクスチャファイル名
#define	TEXTURE_THIRD				"data/TEXTURE/3rd.png"			//読み込むテクスチャファイル名


#define	RANKPAPERBACK_WIDTH			(SCREEN_WIDTH)					// タイトルロゴの幅
#define	RANKPAPERBACK_HEIGHT		(SCREEN_HEIGHT)					// タイトルロゴの高さ
#define	RANKPAPERBACK_POS_X			(0)								// タイトルロゴの位置(X座標)
#define	RANKPAPERBACK_POS_Y			(-SCREEN_WIDTH)								// タイトルロゴの位置(Y座標)

#define	RANKPAPER0_WIDTH			(400*SCREEN_SCALE)							// タイトルロゴの幅
#define	RANKPAPER0_HEIGHT			(400*SCREEN_SCALE)							// タイトルロゴの高さ
#define	RANKPAPER0_POS_X			(SCREEN_WIDTH/2)				// タイトルロゴの位置(X座標)
#define	RANKPAPER0_POS_Y			(0)								// タイトルロゴの位置(Y座標)

#define	RANKPAPER1_WIDTH			(400*SCREEN_SCALE)							// タイトルロゴの幅
#define	RANKPAPER1_HEIGHT			(400*SCREEN_SCALE)							// タイトルロゴの高さ
#define	RANKPAPER1_POS_X			(20+RANKPAPER1_WIDTH/2)							// タイトルロゴの位置(X座標)
#define	RANKPAPER1_POS_Y			(SCREEN_HEIGHT/3)				// タイトルロゴの位置(Y座標)

#define	RANKPAPER2_WIDTH			(400*SCREEN_SCALE)							// タイトルロゴの幅
#define	RANKPAPER2_HEIGHT			(400*SCREEN_SCALE)							// タイトルロゴの高さ
#define	RANKPAPER2_POS_X			(SCREEN_WIDTH-RANKPAPER2_WIDTH/2-20)		// タイトルロゴの位置(X座標)
#define	RANKPAPER2_POS_Y			(SCREEN_HEIGHT/3)				// タイトルロゴの位置(Y座標)

#define RANKPAPER_MAX				(3)								//手配書使用枚数	


#define	RANKPAPER_FIRST_POS_X		(RANKPAPER0_POS_X)		// タイトルロゴの位置(X座標)
#define	RANKPAPER_FIRST_POS_Y		(RANKPAPER0_HEIGHT-80*SCREEN_SCALE)		// タイトルロゴの位置(Y座標)
#define	RANKPAPER_FIRST_WIDTH		(200*SCREEN_SCALE)		// タイトルロゴの幅
#define	RANKPAPER_FIRST_HEIGHT		(200*SCREEN_SCALE)		// タイトルロゴの高さ

#define	RANKPAPER_SECOND_POS_X		(RANKPAPER1_POS_X)		// タイトルロゴの位置(X座標)
#define	RANKPAPER_SECOND_POS_Y		(RANKPAPER1_HEIGHT-80*SCREEN_SCALE)		// タイトルロゴの位置(Y座標)
#define	RANKPAPER_SECOND_WIDTH		(200*SCREEN_SCALE)		// タイトルロゴの幅
#define	RANKPAPER_SECOND_HEIGHT		(200*SCREEN_SCALE)		// タイトルロゴの高さ

#define	RANKPAPER_THIRD_POS_X		(RANKPAPER2_POS_X)		// タイトルロゴの位置(X座標)
#define	RANKPAPER_THIRD_POS_Y		(RANKPAPER2_HEIGHT-80*SCREEN_SCALE)		// タイトルロゴの位置(Y座標)
#define	RANKPAPER_THIRD_WIDTH		(200*SCREEN_SCALE)		// タイトルロゴの幅
#define	RANKPAPER_THIRD_HEIGHT		(200*SCREEN_SCALE)		// タイトルロゴの高さ

#define	RANK_NO_MAX					(RANKPAPER_MAX)					//ランキング順位使用数


typedef struct
{
	D3DXVECTOR3	pos;
}RANKPAPER;//手配書用構造体

typedef struct
{
	D3DXVECTOR3	pos;
}RANKINGNO;//順位用構造体

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitRankpaper(void);
void UninitRankpaper(void);
void UpdateRankpaper(void);
void DrawRankpaper(void);

RANKPAPER *GetRankPaper(int no);
RANKINGNO *GetRankingNo(int no);
D3DXVECTOR3 GetRankBackPos(void);

#endif