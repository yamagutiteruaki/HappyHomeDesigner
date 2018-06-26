//=============================================================================
//
// ビルボード処理 [billboard.h]
// Author : 
//
//=============================================================================
#ifndef _GETUI_H_
#define _GETUI_H_

#include "main.h"


#define	TEXTURE_BILLBOARD		"data/TEXTURE/itemget.png"	// 読み込むテクスチャファイル名
#define	BILLBOARD_SIZE_X		(30.0f)							// ビルボードの幅
#define	BILLBOARD_SIZE_Y		(20.0f)							// ビルボードの高さ
#define	VALUE_MOVE_BILLBOARD	(0.30f)							// 移動速度
#define	VALUE_JUMP				(10.0f)							// ジャンプ力
#define	VALUE_GRAVITY			(0.45f)							// 重力
#define	RATE_REGIST				(0.075f)						// 抵抗係数
#define	RATE_REFRECT			(-0.90f)						// 反射係数

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitGetUI(int nType);
void UninitGetUI(void);
void UpdateGetUI(void);
void DrawGetUI(void);
void SetGetUI(D3DXVECTOR3 pos);

#endif
