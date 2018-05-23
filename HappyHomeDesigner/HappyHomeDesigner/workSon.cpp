//=============================================================================
//
// 宋担当分 [workSon.cpp]
// Author GP12B295 29 山口輝明
// テストテストテストテストテストテストテストテストテストテストテストテストテストテストテストテストテストテストテストテストテストテストテスト
//
//=============================================================================
#include "workSon.h"
#include "stage.h"
#include "input.h"
#include "fade.h"
#include "Light.h"

#include "player.h"

// 宋担当分で必要なインクルード

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
HRESULT InitWorkSon(int nType)
{
	InitPlayer(nType);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitWorkSon(void)
{
	UninitPlayer();

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateWorkSon(void)
{
	UpdateLight();

	switch (GetStage())
	{
	case STAGE_TITLE:
		break;
	case STAGE_GAME || STAGE_HOUSE1 || STAGE_HOUSE2 || STAGE_HOUSE3 || STAGE_HOUSE4:
		UpdatePlayer();
		break;
	case STAGE_RESULT:
		break;
	}

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawWorkSon(void)
{
	switch (GetStage())
	{
	case STAGE_TITLE:
		break;
	case STAGE_GAME ||STAGE_HOUSE1|| STAGE_HOUSE2|| STAGE_HOUSE3|| STAGE_HOUSE4:

		DrawPlayer();
		break;
	case STAGE_RESULT:
		break;
	}
}

