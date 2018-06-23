//=============================================================================
//
// 今川担当分 [workImagawa.cpp]
// Author GP12B295 29 山口輝明
//
//=============================================================================
#include "workImagawa.h"
#include "stage.h"
#include "input.h"
#include "fade.h"
#include "game.h"


// 今川担当分で必要なインクルード
#include "field.h"
#include "wall.h"
#include "home.h"
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
HRESULT InitWorkImagawa(int nType)
{
	InitField(nType);
	InitWall(nType);
	InitHome(nType);
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitWorkImagawa(void)
{
	UninitField();
	UninitWall();
	UninitHome();
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateWorkImagawa(void)
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
		UpdateField();
		UpdateWall();
		UpdateHome();
		break;
	case STAGE_RESULT:
		break;
	}

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawWorkImagawa(int no)
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

		if (no==GAME_FIELD)		DrawField();
		if (no == GAME_WALL)	DrawWall();
		if (no == GAME_HOME)	DrawHome();
		break;
	case STAGE_RESULT:
		break;
	}
}

