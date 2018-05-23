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

// 今川担当分で必要なインクルード
#include "field.h"
#include "wall.h"
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
	InitField();
	InitWall();
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitWorkImagawa(void)
{
	UninitField();
	UninitWall();
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
		break;
	case STAGE_RESULT:
		break;
	}

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawWorkImagawa(void)
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
		DrawField();
		DrawWall();
		break;
	case STAGE_RESULT:
		break;
	}
}

