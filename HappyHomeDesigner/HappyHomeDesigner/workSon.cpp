//=============================================================================
//
// 宋担当分 [workSon.cpp]
// Author GP12B295 29 山口輝明
// テストテストテストテストテストテストテストテストテストテストテストテストテストテストテストテストテストテストテストテストテストテストテスト
//
//=============================================================================
#include "workSon.h"
#include "stage.h"
#include "game.h"

// 宋担当分で必要なインクルード

#include "player.h"
#include "wwwwwwww.h"
#include "inputCtrl.h"

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
	InitWWWW(nType);
	InitInputDevice();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitWorkSon(void)
{
	UninitPlayer();
	UninitWWWW();

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateWorkSon(void)
{
	switch (GetStage())
	{
	case STAGE_TITLE:
		break;
	case STAGE_GAME:
		UpdatePlayer();
		UpdateWWWW();
		break;
	case STAGE_HOUSE1:
	case STAGE_HOUSE2:
	case STAGE_HOUSE3:
	case STAGE_MYHOUSE:
		UpdatePlayer();
		break;
	case STAGE_RESULT:
		break;
	}

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawWorkSon(int no)
{
	switch (GetStage())
	{
	case STAGE_TITLE:
		break;
	case STAGE_GAME:
		if (no == GAME_PLAYER)	DrawPlayer();
		if (no == GAME_WWWW)	DrawWWWW();
		break;
	case STAGE_HOUSE1:
	case STAGE_HOUSE2:
	case STAGE_HOUSE3:
	case STAGE_MYHOUSE:
		if (no == GAME_PLAYER)	DrawPlayer();
		break;
	case STAGE_RESULT:
		break;
	}
}

