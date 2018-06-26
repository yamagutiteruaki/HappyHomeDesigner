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
#include "game.h"

// 山口担当分で必要なインクルード
#include "ranking.h"
#include "timeeffect.h"
#include "shadow.h"
#include "GetUI.h"

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
	InitTimeeffect(nType);
	InitShadow(nType);
	InitGetUI(nType);
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitWorkYamaguchi(void)
{
	UninitTimeeffect();
	UninitShadow();
	UninitGetUI();

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateWorkYamaguchi(void)
{
	switch (GetStage())
	{
	case STAGE_GAME:
	case STAGE_HOUSE1:
	case STAGE_HOUSE2:
	case STAGE_HOUSE3:
	case STAGE_MYHOUSE:

		UpdateTimeeffect();
		UpdateShadow();
		UpdateGetUI();
		break;
	}

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawWorkYamaguchi(int no)
{
	switch (GetStage())
	{
	case STAGE_GAME:
	case STAGE_HOUSE1:
	case STAGE_HOUSE2:
	case STAGE_HOUSE3:
	case STAGE_MYHOUSE:
		if (no == GAME_SHADOW)	DrawShadow();
		if (no == GAME_TIMEEFF)	DrawTimeeffect();
		if (no == GAME_GETUI)	DrawGetUI();
		break;
	}
}

