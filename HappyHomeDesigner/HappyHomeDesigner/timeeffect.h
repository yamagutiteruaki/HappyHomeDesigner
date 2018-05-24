
//=============================================================================
//
// timeeffect.h
// Author : 
//
//=============================================================================
#ifndef _TIMEEFFECT_H_
#define _TIMEEFFECT_H_

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_TIME_EFF		"data/TEXTURE/effect001.png"		// 読み込むテクスチャファイル名

#define WARNING_TIME		(2 * D3DX_PI * 10 / 12)
#define ALPHA_RATE			(0.02f)
#define ALPHA_MAX			(0.4f)

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitTimeeffect(void);
void UninitTimeeffect(void);
void UpdateTimeeffect(void);
void DrawTimeeffect(void);

#endif