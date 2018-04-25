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
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitWorkImagawa(void)
{
	UninitField();

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
		UpdateField();
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
		DrawField();
		break;
	case STAGE_RESULT:
		break;
	}
}

