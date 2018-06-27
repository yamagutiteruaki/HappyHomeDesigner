//=============================================================================
//
// 全体入力制御 [inputCtrl.cpp]
// Author : 宋彦霖
//
//=============================================================================
#include "inputCtrl.h"
#include "input.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define INPUTDEVICE_MAX		(2)		// 最大入力装置数

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitInputKeyboard(void);
void InitInputGamepad(void);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
INPUTDEVICE InputWk[INPUTDEVICE_MAX];		// ワーク

//=============================================================================
// 初期化処理
//=============================================================================
void InitInputDevice(void)
{
	INPUTDEVICE *b = GetInputDevice(0);

	for (int i = 0; i < INPUTDEVICE_MAX; i++, b++)
	{
		b->UP = -1;
		b->DOWN = -1;
		b->LEFT = -1;
		b->RIGHT = -1;

		b->UP_POV = -1;
		b->DOWN_POV = -1;
		b->LEFT_POV = -1;
		b->RIGHT_POV = -1;

		b->CAMERA_LEFT = -1;
		b->CAMERA_RIGHT = -1;
		b->CAMERA_RESET = -1;

		b->CAMERA_ZOOMIN = -1;
		b->CAMERA_ZOOMOUT = -1;

		b->DECIDE = -1;
		b->CANCEL = -1;

		b->TAKE = -1;
		b->PUT = -1;

		b->PAUSE = -1;
	}

	InitInputKeyboard();
	InitInputGamepad();
}

//=============================================================================
// ボタンの取得
//=============================================================================
INPUTDEVICE *GetInputDevice(int id)
{
	return (&InputWk[id]);
}

//=============================================================================
// 初期化処理（Keyboard）
//=============================================================================
void InitInputKeyboard(void)
{
	INPUTDEVICE *kb = GetInputDevice(INPUT_KEY);

	kb->UP =				DIK_UP;
	kb->DOWN =				DIK_DOWN;
	kb->LEFT =				DIK_LEFT;
	kb->RIGHT =				DIK_RIGHT;

	kb->CAMERA_LEFT =		DIK_C;
	kb->CAMERA_RIGHT =		DIK_Z;
	kb->CAMERA_RESET =		DIK_X;

	kb->CAMERA_ZOOMIN =		DIK_W;
	kb->CAMERA_ZOOMOUT =	DIK_S;

	kb->DECIDE =			DIK_RETURN;

	kb->TAKE =				DIK_E;
	kb->PUT =				DIK_G;

}

//=============================================================================
// 初期化処理（Gamepad）
//=============================================================================
void InitInputGamepad(void)
{
	INPUTDEVICE *gp = GetInputDevice(INPUT_GAMEPAD);

	gp->UP =				BUTTON_UP;
	gp->DOWN =				BUTTON_DOWN;
	gp->LEFT =				BUTTON_LEFT;
	gp->RIGHT =				BUTTON_RIGHT;

	gp->UP_POV =			BUTTON_POV_UP;
	gp->DOWN_POV =			BUTTON_POV_DOWN;
	gp->LEFT_POV =			BUTTON_POV_LEFT;
	gp->RIGHT_POV =			BUTTON_POV_RIGHT;

	gp->CAMERA_LEFT =		BUTTON_LZ_UP;
	gp->CAMERA_RIGHT =		BUTTON_LZ_DOWN;
	gp->CAMERA_RESET =		-1;

	gp->CAMERA_ZOOMIN =		BUTTON_LRZ_DOWN;
	gp->CAMERA_ZOOMOUT =	BUTTON_LRZ_UP;

	gp->DECIDE =			BUTTON_C;

	gp->TAKE =				BUTTON_X;
	gp->PUT =				BUTTON_B;

}
