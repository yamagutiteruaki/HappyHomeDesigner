//=============================================================================
//
// ゲーム処理 [game.cpp]
// Author : GP12B295 29 山口輝明
//
//=============================================================================
#include "game.h"
#include "stage.h"
#include "input.h"
#include "fade.h"

// ゲームで必要なインクルード


// 担当ワーク
#include "workChisaka.h"
#include "workMatsuo.h"
#include "workSon.h"
#include "workImagawa.h"
#include "workSekiguchi.h"
#include "workYamaguchi.h"

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
HRESULT InitGame(int nType)
{

	InitWorkChisaka(0);
	InitWorkSon(0);
	InitWorkSekiguchi(0);
	InitWorkMatsuo(0);
	InitWorkImagawa(0);
	InitWorkYamaguchi(0);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitGame(void)
{
	UninitWorkChisaka();
	UninitWorkSon();
	UninitWorkSekiguchi();
	UninitWorkMatsuo();
	UninitWorkImagawa();
	UninitWorkYamaguchi();

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateGame(void)
{

	UpdateWorkChisaka();
	UpdateWorkSon();
	UpdateWorkSekiguchi();
	UpdateWorkMatsuo();
	UpdateWorkImagawa();
	UpdateWorkYamaguchi();
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawGame(void)
{

	DrawWorkChisaka();
	DrawWorkSon();
	DrawWorkSekiguchi();
	DrawWorkMatsuo();
	DrawWorkImagawa();
	DrawWorkYamaguchi();
}

