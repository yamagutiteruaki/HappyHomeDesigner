//=============================================================================
//
// フェード処理 [fade.h]
// Author : 
//
//=============================================================================
#ifndef ___FADE_H___
#define ___FADE_H___

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	FADE_RATE		(0.02f)		// フェード係数
#define	FADE_HALF		(0.3f)		// ハーフフェード

#define	FADE_COLOR_R	(0.0f)		// フェードカラーR
#define	FADE_COLOR_G	(0.0f)		// フェードカラーG
#define	FADE_COLOR_B	(0.0f)		// フェードカラーB

//*************************************
// フェードの状態
//*************************************
enum FADE
{
	FADE_NONE = 0,		// 何もない状態
	FADE_IN,			// フェードイン処理
	FADE_OUT,			// フェードアウト処理
	FADE_OUT_HALF,		// フェードアウト処理
	FADE_MAX
};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitFade(void);
void UninitFade(void);
void UpdateFade(void);
void DrawFade(void);

void SetFade(FADE fade, int next,D3DXCOLOR color);
FADE GetFade(void);
bool GetFadeFlag(void);
void SetFadeFlag(bool flag);



#endif
