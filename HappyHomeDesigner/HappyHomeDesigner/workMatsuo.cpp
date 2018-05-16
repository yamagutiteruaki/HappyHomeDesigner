//=============================================================================
//
// 松尾担当分 [workMatsuo.cpp]
// Author GP12A295 28 松尾公平
//
//=============================================================================
#include "workMatsuo.h"
#include "stage.h"
#include "input.h"
#include "fade.h"

// 松尾担当分で必要なインクルード
#include "title.h"
#include "titlelogo.h"
#include "weight.h"
#include "voice.h"
#include "arrest.h"
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
HRESULT InitWorkMatsuo(int nType)
{
	InitTitlelogo();
	InitWeight(0);
	InitVoice(0);
	InitArrest(0);
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitWorkMatsuo(void)
{
	UninitTitlelogo();
	UninitWeight();
	UninitVoice();
	UninitArrest();
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateWorkMatsuo(void)
{
	switch (GetStage())
	{
	case STAGE_TITLE:
		UpdateTitlelogo();

		break;
	case STAGE_GAME:
		UpdateWeight();
		UpdateVoice();
		UpdateArrest();
		break;
	case STAGE_RESULT:

		break;
	}

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawWorkMatsuo(void)
{
	switch (GetStage())
	{
	case STAGE_TITLE:
		DrawTitlelogo();
		break;
	case STAGE_GAME:
		DrawWeight();
		DrawVoice();
		DrawArrest();
		break;
	case STAGE_RESULT:
		break;
	}
}

