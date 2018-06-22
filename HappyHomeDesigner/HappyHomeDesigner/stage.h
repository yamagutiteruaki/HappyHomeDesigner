//=============================================================================
//
// ステージ遷移処理 [stage.h]
// Author : GP12B295 29 山口輝明
//
// タイトル・ゲーム・リザルトの遷移管理
//
//=============================================================================
#ifndef _STAGE_H_
#define _STAGE_H_

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define START_STAGE		(STAGE_TITLE)	// 開始時のステージ
#define STR(var) #var					// 引数にした変数を変数名を示す文字列リテラルとして返すマクロ関数
#define START_PRICE		((long long)0)				//初期金額
#define MAX_PRICE		((long long)99999999999)	//最大金額　score.hのNUM_PLACEと桁数を合わせること
/*******************************************************************************
* 構造体定義
*******************************************************************************/

/*******************************************************************************
* 列挙型定義
*******************************************************************************/
enum
{	// ステージ
	STAGE_TITLE,		//タイトル
	STAGE_GAME,			//ゲーム
	STAGE_GAME_END,		//ゲーム終了時演出
	STAGE_RESULT,		//リザルト
	STAGE_HOUSE1,		//家1
	STAGE_HOUSE2,		//家2
	STAGE_HOUSE3,		//家3
	STAGE_MYHOUSE,		//家4
	STAGE_MAX
};

enum
{
	STAGE_INIT_FAST,
	STAGE_INIT_LOOP
};

enum
{
	GAME_CLEAR,
	GAME_OVER
};
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT		InitStage(HINSTANCE hInstance, HWND hWnd);
HRESULT		InitStageEach(int nType);
void		UninitStage(void);
void		UpdateStage(void);
void		DrawStage(void);

void		SetStage(int nStage);
int			GetStage(void);
long long	GetPrice(void);
void		AddPrice(long long price);
void		SetGameEnd(int no);
int			GetGameEnd(void);

#endif