
//=============================================================================
//
// タイトル画面処理 [title.h]
// Author : 
//
//=============================================================================
#ifndef _TITLELOGO_H_
#define _TITLELOGO_H_

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_TITLE		"data/TEXTURE/HHD_title.jpg"		// 読み込むテクスチャファイル名
#define	TEXTURE_TITLE_LOGO	"data/TEXTURE/Titlelogo_00.png"	// 読み込むテクスチャファイル名
#define	TEXTURE_LOGO_START	"data/TEXTURE/Press_enter00.png"	// 読み込むテクスチャファイル名
#define	TEXTURE_STAMP		"data/TEXTURE/移Stamp.png"			//読み込むテクスチャファイル名

#define	TITLE_LOGO_POS_X		(20)		// タイトルロゴの位置(X座標)
#define	TITLE_LOGO_POS_Y		(10)		// タイトルロゴの位置(Y座標)
#define	TITLE_LOGO_WIDTH		(SCREEN_WIDTH)		// タイトルロゴの幅
#define	TITLE_LOGO_HEIGHT		(SCREEN_HEIGHT)		// タイトルロゴの高さ

#define	START_POS_X				(SCREEN_WIDTH/2)		// スタートボタンの位置(X座標)
#define	START_POS_Y				(SCREEN_HEIGHT/2)		// スタートボタンの位置(Y座標)
#define	START_WIDTH				(1200/2*SCREEN_SCALE)		// スタートボタンの幅
#define	START_HEIGHT			(750/2*SCREEN_SCALE)		// スタートボタンの高さ

#define	STAMP_POS_X				(SCREEN_WIDTH/2+30)		// スタﾝﾌﾟボタンの位置(X座標)
#define	STAMP_POS_Y				(SCREEN_HEIGHT/2)		// スタンプボタンの位置(Y座標)
#define	STAMP_WIDTH				(750/2*SCREEN_SCALE)		// スタンプボタンの幅
#define	STAMP_HEIGHT			(750/2*SCREEN_SCALE)		// スタンプボタンの高さ

#define	ROT_STAMP			(0.3f)

#define	COUNT_APPERA_START		(60)		// スタートボタン出現までの時間
#define	INTERVAL_DISP_START		(60)		// スタートボタン点滅の時間

#define	COUNT_WAIT_DEMO			(60 * 5)	// デモまでの待ち時間
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitTitlelogo(void);
void UninitTitlelogo(void);
void UpdateTitlelogo(void);
void DrawTitlelogo(void);

#endif