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
#define	TEXTURE_RESULT_GAMEOVER	"data/TEXTURE/GAMEOVER00.png"			// 読み込むテクスチャファイル名
#define	TEXTURE_RESULT_CLEAR	"data/TEXTURE/GAME_RESULT00.png"			// 読み込むテクスチャファイル名
#define	RESULT_LOGO2_WIDTH	(1200)				// リザルトロゴの幅
#define	RESULT_LOGO2_HEIGHT	(480)				// リザルトロゴの高さ


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitResultLogo(void);
void UninitResultLogo(void);
void UpdateResultLogo(void);
void DrawResultLogo(void);

#endif
