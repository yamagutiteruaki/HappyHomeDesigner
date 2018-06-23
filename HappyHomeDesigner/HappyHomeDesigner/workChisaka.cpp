//=============================================================================
//
// 千坂担当分 [workChisaka.cpp]
// Author GP12B295 29 山口輝明
//
//=============================================================================
#include "workChisaka.h"
#include "stage.h"
#include "input.h"
#include "fade.h"
#include "game.h"

// 千坂担当分で必要なインクルード
#include "police.h"
#include "search.h"
#include "furniture.h"
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
HRESULT InitWorkChisaka(int nType)
{
	InitPolice(nType);
	InitSearch(nType);
	InitFurniture(nType);
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitWorkChisaka(void)
{
	UninitPolice();
	UninitSearch();
	UninitFurniture();
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateWorkChisaka(void)
{
	switch (GetStage())
	{
	case STAGE_TITLE:
		break;
	case STAGE_GAME:
		UpdatePolice();
		UpdateSearch();
		UpdateFurniture();
		break;
	case STAGE_HOUSE1:
	case STAGE_HOUSE2:
	case STAGE_HOUSE3:
	case STAGE_MYHOUSE:
		UpdateFurniture();
		break;
	case STAGE_RESULT:
		break;
	}

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawWorkChisaka(int no)
{
	switch (GetStage())
	{
	case STAGE_TITLE:
		break;
	case STAGE_GAME:
		if (no == GAME_POLICE)	DrawPolice();
		if (no == GAME_SEARCH)	DrawSearch();
		break;
	case STAGE_HOUSE1:
	case STAGE_HOUSE2:
	case STAGE_HOUSE3:
	case STAGE_MYHOUSE:
		if (no == GAME_FURNITURE)	DrawFurniture();
		break;
	case STAGE_RESULT:
		break;
	}
}

