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
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	MAX_FURNITURE				(128)						// 家具最大数
#define	VALUE_MOVE_FURNITURE		(1.00f)						// 移動速度係数
#define	RATE_MOVE_FURNITURE			(0.20f)						// 移動慣性係数
#define	VALUE_ROTATE_FURNITURE		(D3DX_PI * 0.05f)			// 回転速度
#define	RATE_ROTATE_FURNITURE		(0.20f)						// 回転慣性係数
#define	VALUE_SCALE_FURNITURE		(0.05f)						// スケール拡大・縮小速度
//**************************************
// 種類
//**************************************
enum
{
	kabin = 0,			// 花瓶
	isu,				// 椅子
	buta,				// 豚の貯金箱
	yubiwa,				// 指輪
	toire,				// トイレ
	tukue,				// 机
	terebi,				// テレビ
	kinko,				// 金庫
	tansu,				// タンス
	bed,				// ベッド
	FURNITURE_TYPE_MAX	// 家具の種類の最大数
};

//*****************************************************************************
// クラス定義
//*****************************************************************************
class FURNITURE
{
public:
	bool		use;				// 使用しているかどうか
	bool		own;				// プレイヤーに所有されているかどうか(true:所有されている,false:所有されていない)

	D3DXVECTOR3	pos;				// 現在の位置
	D3DXVECTOR3	rot;				// 現在の向き
	D3DXVECTOR3	rotDest;			// 目的の向き
	D3DXVECTOR3	scl;				// スケール
	D3DXVECTOR3	move;				// 移動量

	int			type;				// 種類
	int			house_num;			// 所属している家の番号
	int			weight;				// 重さ
	int			price;				// 金額
	int			ratio;				// 確率

	char		name[64];			// CSVファイルの家具の名前
};
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitFurniture(int nType);
void UninitFurniture(void);
void UpdateFurniture(void);
void DrawFurniture(void);
FURNITURE *GetFurniture(int no);
int GetFurnitureNum(void);

#endif
