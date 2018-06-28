//=============================================================================
//
// 関口担当分 [workSekiguchi.cpp]
// Author GP12B295 ⑫ 関口昂平
//
//=============================================================================
#include "workSekiguchi.h"
#include "stage.h"
#include "input.h"
#include "fade.h"
#include "game.h"


// 関口担当分で必要なインクルード
#include "clock.h"
#include "result.h"
#include "resultlogo.h"
#include "score.h"

// デバッグ用
#ifdef _DEBUG
#include "debugproc.h"
#endif

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitWorkSekiguchi(int nType)
{

	InitClock(nType);

	InitResultLogo(nType);

	InitScore(nType);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitWorkSekiguchi(void)
{
	UninitClock();

	UninitResultLogo();

	UninitScore();
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateWorkSekiguchi(void)
{
	switch (GetStage())
	{
	case STAGE_TITLE:
		break;
	case STAGE_GAME:
	case STAGE_HOUSE1:
	case STAGE_HOUSE2:
	case STAGE_HOUSE3:
	case STAGE_MYHOUSE:

		UpdateClock();
		//UpdateScore();

		break;
	case STAGE_RESULT:
	case STAGE_RANKING:
		 UpdateResultLogo();

		 UpdateScore();

		break;
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawWorkSekiguchi(int no)
{
	switch (GetStage())
	{
	case STAGE_TITLE:
		break;
	case STAGE_GAME:
	case STAGE_HOUSE1:
	case STAGE_HOUSE2:
	case STAGE_HOUSE3:
	case STAGE_MYHOUSE:

		if (no == GAME_CLOCK)	DrawClock();

		break;
	case STAGE_RESULT:
	case STAGE_RANKING:

		 DrawResultLogo();

		 DrawScore();

		break;
	}
}

