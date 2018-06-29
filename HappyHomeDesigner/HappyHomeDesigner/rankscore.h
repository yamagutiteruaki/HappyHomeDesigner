//=============================================================================
//
// スコア処理 [score.h]
// Author : 
//
//=============================================================================
#ifndef _RANKSCORE_H_
#define _RANKSCORE_H_

#include "main.h"
#include "rankpaper.h"


//*****************************************************************************
// マクロ定義
// 1位のX			(500)
// 1位のY			(280)
// 2位のX			(90)
// 2位のY			(520)
// 3位のX			(930)
// 3位のY			(520)
//*****************************************************************************
#define	TEXTURE_RANKSCORE		"data/TEXTURE/deg_number3.png"	// 読み込むテクスチャファイル名
#define	RANKSCORE_SIZE_X		(25.0f)							// スコアの数字の幅
#define	RANKSCORE_SIZE_Y		(80.0f)						// スコアの数字の高さ
#define	RANKSCORE_INTERVAL_X	(0.0f)							// スコアの数字の表示間隔

#define	NUM_PLACE			(11)							// スコアの桁数 stage.hのMAX_PRICEと桁数合わせること

#define	RANKSCORE_POS_X			((float)(-RANKSCORE_SIZE_X*NUM_PLACE/2)+10)						// スコアの表示基準位置Ｘ座標
#define	RANKSCORE_POS_Y			(280)				// スコアの表示基準位置Ｙ座標


#define SLOT_INTERVAL		(30)

#define RANKSCORE_MAX			(3)


//*******************************************************************************
// 構造体宣言
//*******************************************************************************
typedef struct
{
	D3DXVECTOR3				pos;						// 位置
	long long			rankscore;						// 表示スコア
	long long			maxrankscore;						//取得スコア


}RANKSCORE;
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitRankscore(int nType);
void UninitRankscore(void);
void UpdateRankscore(void);
void DrawRankscore(void);
int GetSlotCount(void);

#endif
