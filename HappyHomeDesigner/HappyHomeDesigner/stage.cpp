//=============================================================================
//
// ステージ遷移処理 [stage.cpp]
// Author : GP12B295 29 山口輝明
//
// タイトル・ゲーム・リザルトの遷移管理
//
//=============================================================================
#include "main.h"
#include "stage.h"

/* Stage */
#include "game.h"
#include "title.h"
#include "result.h"

/* Camera */
#include "camera.h"

/* System */
#include "input.h"
#include "light.h"
#include "fade.h"
#include "sound.h"

/* Work */
#include "workChisaka.h"
#include "workMatsuo.h"
#include "workSon.h"
#include "workImagawa.h"
#include "workSekiguchi.h"
#include "workYamaguchi.h"

/* Debug */
#ifdef _DEBUG
#include "debugproc.h"
#endif

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************
int					g_nStage;				// 初期ステージ
long long			g_nPrice;				//盗難金額
int					g_nGameEnd;				//ゲームエンド状況

#ifdef _DEBUG
bool				g_bDispDebug = true;	// デバッグ表示ON/OFF
#endif

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitStage(HINSTANCE hInstance, HWND hWnd)
{
	// グローバル変数の初期化
	g_nStage = START_STAGE;			// 初期ステージを設定

	InitInput(hInstance, hWnd);		// 入力
	InitSound(hWnd);				// サウンド
	InitLight();					// ライト
	InitFade();						// フェード
	InitStageEach(STAGE_INIT_FAST);	// 各ステージの初期化

#ifdef _DEBUG
	InitDebugProc();				// デバッグ表示処理の初期化
#endif
	return S_OK;
}

//=============================================================================
// 再初期化処理
//=============================================================================
HRESULT InitStageEach(int nType)
{
	g_nGameEnd = GAME_CLEAR;		//クリア状況設定
	g_nPrice = START_PRICE;			//初期金額設定

	
	InitCamera(nType);			// カメラ
	InitTitle();				// タイトル
	InitGame(nType);			// ゲーム
	InitResult();				//リザルト


	InitWorkChisaka(nType);
	InitWorkSon(nType);
	InitWorkSekiguchi(nType);
	InitWorkMatsuo(nType);
	InitWorkImagawa(nType);
	InitWorkYamaguchi(nType);


	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitStage(void)
{
	UninitCamera();					// カメラ
	UninitInput();					// 入力
	UninitSound();					// サウンド
	UninitFade();					// フェード
	UninitGame();					// ゲーム
	UninitTitle();					// タイトル
	UninitResult();					//リザルト

	UninitWorkChisaka();
	UninitWorkSon();
	UninitWorkSekiguchi();
	UninitWorkMatsuo();
	UninitWorkImagawa();
	UninitWorkYamaguchi();


#ifdef _DEBUG
	UninitDebugProc();				// デバッグ表示処理の終了処理
#endif
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateStage(void)
{
#ifdef _DEBUG
	if (GetKeyboardTrigger(DIK_RSHIFT))
	{	// デバッグ表示ON/OFF
		g_bDispDebug = g_bDispDebug ? false : true;
	}
	UpdateDebugProc();				// デバッグ

	PrintDebugProc("【 STAGE 】\n");
	switch (g_nStage)
	{
	case STAGE_TITLE:
		PrintDebugProc("%s (%d)\n", STR(STAGE_TITLE), g_nStage);
		break;
	case STAGE_GAME:
		PrintDebugProc("%s (%d)\n", STR(STAGE_GAME), g_nStage);
		if (GetKeyboardTrigger(DIK_RETURN))
		{
			SetFade(FADE_OUT, STAGE_RESULT, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
		}
		break;

	case STAGE_HOUSE1:
		PrintDebugProc("%s (%d)\n", STR(STAGE_HOUSE1), g_nStage);
		break;
	case STAGE_HOUSE2:
		PrintDebugProc("%s (%d)\n", STR(STAGE_HOUSE2), g_nStage);
		break;
	case STAGE_HOUSE3:
		PrintDebugProc("%s (%d)\n", STR(STAGE_HOUSE3), g_nStage);
		break;
	case STAGE_MYHOUSE:
		PrintDebugProc("%s (%d)\n", STR(STAGE_MYHOUSE), g_nStage);
		break;

	case STAGE_RESULT:
		PrintDebugProc("%s (%d)\n", STR(STAGE_RESULT), g_nStage);
		if (GetKeyboardTrigger(DIK_RETURN))
		{
			SetFade(FADE_OUT, STAGE_TITLE, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
		}

		break;
	}
	PrintDebugProc("\n");
	// SEテスト（sound.hをincludeして関数を呼ぶ）
	if (GetKeyboardTrigger(DIK_1))
	{	// タイトル・リザルト画面の決定ボタン
		SetSe(SE_BUTTON, E_DS8_FLAG_NONE, CONTINUITY_ON);
	}
	if (GetKeyboardTrigger(DIK_2))
	{	// バレット発射音
		SetSe(SE_BULLET, E_DS8_FLAG_NONE, CONTINUITY_ON);
	}
	if (GetKeyboardTrigger(DIK_3))
	{	// ゲージが足りないときにMISS音
		SetSe(SE_MISS, E_DS8_FLAG_NONE, CONTINUITY_ON);
	}
	if (GetKeyboardTrigger(DIK_4))
	{	// エネミーと衝突時の爆発音
		SetSe(SE_BOMB, E_DS8_FLAG_NONE, CONTINUITY_ON);
	}
	if (GetKeyboardTrigger(DIK_5))
	{	// アイテム取得音
		SetSe(SE_ITEM, E_DS8_FLAG_NONE, CONTINUITY_ON);
	}
#endif

	UpdateInput();					// 入力
	UpdateSound();					// サウンド
	//UpdateLight();

	// ステージに応じた更新処理
	switch (g_nStage)
	{
	case STAGE_TITLE:
		UpdateTitle();				// タイトル
		SetSoundBgm(SOUND_BGM_TITLE);
		break;
	case STAGE_GAME:
	case STAGE_HOUSE1:
	case STAGE_HOUSE2:
	case STAGE_HOUSE3:
	case STAGE_MYHOUSE:
		UpdateGame();				// ゲーム
		SetSoundBgm(SOUND_BGM_GAME);
		break;
	case STAGE_RESULT:
		UpdateResult();				//リザルト
		SetSoundBgm(SOUND_BGM_RESULT);
		break;
	}
	UpdateCamera();					// カメラ
	UpdateFade();					// フェード
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawStage(void)
{
	SetCamera();					// カメラの設定処理

									// ステージに応じた描画処理
	switch (g_nStage)
	{
	case STAGE_TITLE:
		DrawTitle();					// タイトル
		break;
	case STAGE_GAME:
	case STAGE_HOUSE1:				// 左上の家
	case STAGE_HOUSE2:				// 右上の家
	case STAGE_HOUSE3:				// 左下の家
	case STAGE_MYHOUSE:				// 右下の自分の家
		DrawGame();					// ゲーム
		break;
	case STAGE_RESULT:
		DrawResult();				//リザルト
		break;
	}

	DrawFade();						// フェード

#ifdef _DEBUG
	if (g_bDispDebug)
	{	// デバッグ表示する場合
		DrawDebugProc();			// デバッグ
	}
#endif
}

//=============================================================================
// ステージ設定関数
//=============================================================================
void SetStage(int nStage)
{
	g_nStage = nStage;
}

//=============================================================================
// ステージ取得関数
//=============================================================================
int GetStage(void)
{
	return (g_nStage);
}

//=============================================================================
//盗難金額取得関数
//=============================================================================
long long GetPrice(void)
{
	return g_nPrice;
}

//=============================================================================
//盗難金額加算関数
//=============================================================================
void AddPrice(long long price)
{
	g_nPrice += price;
}

//==============================================================================
//ゲームエンドセット
//==============================================================================
void SetGameEnd(int no)
{
	g_nGameEnd = no;
}
//==============================================================================
//ゲームエンド取得
//==============================================================================
int GetGameEnd(void)
{
	return g_nGameEnd;
}
