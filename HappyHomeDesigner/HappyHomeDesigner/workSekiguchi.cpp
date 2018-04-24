//=============================================================================
//
// 関口担当分 [workSekiguchi.cpp]
// Author GP12B295 �K 関口昂平
//
//=============================================================================
#include "workSekiguchi.h"
#include "stage.h"
#include "input.h"
#include "fade.h"

// 関口担当分で必要なインクルード
#include "result.h"

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

	InitResult();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitWorkSekiguchi(void)
{
	UninitResult();
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
		break;
	case STAGE_RESULT:
		 UpdateResult();
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
		break;
	case STAGE_RESULT:
		 DrawResult();
		break;
	}
}

