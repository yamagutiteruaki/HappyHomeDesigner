//=============================================================================
//
// 家具処理 [furniture.h]
// Author : GP12A295-19-千坂浩太
//
//=============================================================================
#ifndef _FURNITURE_H_
#define _FURNITURE_H_

#include "main.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	MAX_FURNITURE				(32)						// 家具最大数

//**************************************
// 種類
//**************************************
enum
{
	FURNITURETYPE_COIN = 0,		// コイン
	FURNITURETYPE_LIFE,			// ライフ
	FURNITURETYPE_TIMER,		// タイマー
	FURNITURETYPE_MAX
};

//*****************************************************************************
// クラス定義
//*****************************************************************************
class FURNITURE
{
public:
	bool		use;				// 使用しているかどうか

	D3DXVECTOR3	pos;				// 現在の位置
	D3DXVECTOR3	rot;				// 現在の向き
	D3DXVECTOR3	rotDest;			// 目的の向き
	D3DXVECTOR3	scl;				// スケール

	int			type;				// 種類
	int			num;				// 番号
};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitFurniture(int nType);
void UninitFurniture(void);
void UpdateFurniture(void);
void DrawFurniture(void);

void SetFurniture(D3DXVECTOR3 pos, int nType, int life);
FURNITURE *GetFurniture(int no);

#endif
