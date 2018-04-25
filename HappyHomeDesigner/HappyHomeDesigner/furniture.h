//=============================================================================
//
// 家具処理 [furniture.h]
// Author : GP11B243-18-千坂浩太
//
//=============================================================================
#ifndef _FURNITURE_H_
#define _FURNITURE_H_

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	MAX_FURNITURE				(128)						// アイテム最大数
#define	MAX_FURNITURE_POP			(5)							// アイテム同時存在可能数
#define	NUM_POP					(2)							// SetFurniture関数で一回当たりポップさせる数
#define	FURNITURE_LIFE				(300)						// アイテムの寿命
#define	VALUE_MOVE_FURNITURE			(0.5f)						// アイテムの移動速度
#define	FURNITURE_SIZE_X				(10.0f)						// アイテムの幅
#define	FURNITURE_SIZE_Y				(40.0f)						// アイテムの高さ
#define	FURNITURE_POP_FREQUENCY		(60*3)						// アイテムのポップ頻度(フレーム×秒数)
#define FURNITURE_SHADOW_SIZE		(35.0f)						// アイテムの影サイズ
#define FURNITURE_SHADOW_REREASE		(-20.0f)					// アイテムの影を削除する高さ

//**************************************
// 種類
//**************************************
enum
{
	FURNITURETYPE_COIN = 0,		// コイン
	FURNITURETYPE_LIFE,			// ライフ
	FURNITURETYPE_TIMER,			// タイマー
	FURNITURETYPE_MAX
};

//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3	pos;				// 現在の位置
	D3DXVECTOR3	rot;				// 現在の向き
	D3DXVECTOR3	scl;				// スケール

	float		fRadius;			// 半径
	int			nType;				// 種類
	int			life;				// 寿命
	int			no;					// ポップしているパネル番号
	bool		use;				// 使用しているかどうか

									// シャドウ用
	int				nIdxShadow;
	float			fSizeShadow;
	D3DXCOLOR		colShadow;
	bool			bShadow;
} FURNITURE;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitFurniture(int nType);
void UninitFurniture(void);
void UpdateFurniture(void);
void DrawFurniture(void);

void SetFurniture(D3DXVECTOR3 pos, int nType, int life);
FURNITURE *GetFurniture(int no);
int GetExistFurnitureNum(void);

#endif
