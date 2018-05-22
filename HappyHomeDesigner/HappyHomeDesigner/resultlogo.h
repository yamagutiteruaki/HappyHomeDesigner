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
#define	TEXTURE_RESULT			"data/TEXTURE/rouya.jpg"		// 読み込むテクスチャファイル名
#define	TEXTURE_RESULT_LOGO		"data/TEXTURE/result.png"		// 読み込むテクスチャファイル名
#define	TEXTURE_RESULT_LOGO2	"data/TEXTURE/被害総額.png"			// 読み込むテクスチャファイル名

//#define	RESULT_LOGO_POS_X	(SCREEN_CENTER_X)					// リザルトロゴの位置(X座標)
//#define	RESULT_LOGO_POS_Y	(100*SCREEN_SCALE)					// リザルトロゴの位置(Y座標)
//#define	RESULT_LOGO_WIDTH	(800 / 2*SCREEN_SCALE)				// リザルトロゴの幅
//#define	RESULT_LOGO_HEIGHT	(240 / 2*SCREEN_SCALE)				// リザルトロゴの高さ

#define	RESULT_LOGO2_POS_X	(SCREEN_CENTER_X)					// リザルトロゴの位置(X座標)
#define	RESULT_LOGO2_POS_Y	(100*SCREEN_SCALE)					// リザルトロゴの位置(Y座標)
#define	RESULT_LOGO2_WIDTH	(800 / 2*SCREEN_SCALE)				// リザルトロゴの幅
#define	RESULT_LOGO2_HEIGHT	(240 / 2*SCREEN_SCALE)				// リザルトロゴの高さ


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitResultLogo(void);
void UninitResultLogo(void);
void UpdateResultLogo(void);
void DrawResultLogo(void);

#endif
