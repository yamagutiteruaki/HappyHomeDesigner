//=============================================================================
//
// ゲーム処理 [result.cpp]
// Author : GP12B295 �K 関口昂平
//
//=============================================================================
#include "result.h"
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
HRESULT InitResult(void)
{
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitResult(void)
{

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateResult(void)
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
void DrawResult(void)
{
	DrawWorkImagawa(0);
	DrawWorkChisaka(0);
	DrawWorkSon(0);
	DrawWorkSekiguchi(0);
	DrawWorkMatsuo(0);
	DrawWorkYamaguchi(0);
}

