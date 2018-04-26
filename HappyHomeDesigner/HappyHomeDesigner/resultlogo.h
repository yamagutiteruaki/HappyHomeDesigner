//=============================================================================
//
// リザルト画面処理 [resultlogo.h]
// Author : GP12B295 ⑫ 関口昂平
//
//=============================================================================
#ifndef _RESULTLOGO_H_
#define _RESULTLOGO_H_

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_RESULTLOGO			"data/TEXTURE/result.png"			// 読み込むテクスチャファイル名
#define	TEXTURE_RESULTLOGO_LOGO	 	"data/TEXTURE/result_logo.png"	// 読み込むテクスチャファイル名
#define	TEXTURE_RESULTLOGO_LOGO2	"data/TEXTURE/ロゴ.png"		// 読み込むテクスチャファイル名

#define	RESULTLOGO_LOGO_POS_X	(SCREEN_CENTER_X)		// リザルトロゴの位置(X座標)
#define	RESULTLOGO_LOGO_POS_Y	(200*SCREEN_SCALE)					// リザルトロゴの位置(Y座標)
#define	RESULTLOGO_LOGO_WIDTH	(800 / 2*SCREEN_SCALE)				// リザルトロゴの幅
#define	RESULTLOGO_LOGO_HEIGHT	(240 / 2*SCREEN_SCALE)				// リザルトロゴの高さ


#define	RESULTLOGO_LOGO2_POS_X	(SCREEN_CENTER_X)		// リザルトロゴの位置(X座標)
#define	RESULTLOGO_LOGO2_POS_Y	(500*SCREEN_SCALE)					// リザルトロゴの位置(Y座標)
#define	RESULTLOGO_LOGO2_WIDTH	(800 / 2*SCREEN_SCALE)				// リザルトロゴの幅
#define	RESULTLOGO_LOGO2_HEIGHT	(240 / 2*SCREEN_SCALE)				// リザルトロゴの高さ

#define	COUNT_APPERA_RESULTLOGO	(3)		// リザルトロゴ出現までの待ち時間	
#define	LIMIT_COUNT_WAIT	(60 * 15)	// 待ち時間

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitResultlogo(int nType);
void UninitResultlogo(void);
void UpdateResultlogo(void);
void DrawResultlogo(void);

#endif
