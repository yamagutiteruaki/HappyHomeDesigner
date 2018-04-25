//=============================================================================
//
// 山口担当分 [workYamaguchi.cpp]
// Author GP12B295 29 山口輝明
//
//=============================================================================
#include "workYamaguchi.h"
#include "stage.h"
#include "input.h"
#include "fade.h"

// 山口担当分で必要なインクルード

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
HRESULT InitWorkYamaguchi(int nType)
{

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitWorkYamaguchi(void)
{
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateWorkYamaguchi(void)
{
	switch (GetStage())
	{
	case STAGE_TITLE:
		break;
	case STAGE_GAME:
		break;
	case STAGE_RESULT:
		break;
	}

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawWorkYamaguchi(void)
{
	switch (GetStage())
	{
	case STAGE_TITLE:
		break;
	case STAGE_GAME:
		break;
	case STAGE_RESULT:
		break;
	}
}

