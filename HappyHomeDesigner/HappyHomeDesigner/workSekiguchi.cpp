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

	InitClock(0);

	InitResultLogo();

	InitScore();

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

		break;
	case STAGE_RESULT:

		 UpdateResultLogo();

		 UpdateScore();

		break;
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawWorkSekiguchi(void)
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

		DrawClock();

		break;
	case STAGE_RESULT:

		 DrawResultLogo();

		 DrawScore();

		break;
	}
}

