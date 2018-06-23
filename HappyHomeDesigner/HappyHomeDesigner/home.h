//=============================================================================
//
// 地面処理 [field.h]
// Author : 今川乃流
//
//=============================================================================
#ifndef _HOME_H_
#define _HOME_H_

#include "main.h"
#include "field.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

#define HOME_MAX				(4)

#define HOME_DISTANCE  (FIELD_SIZE_X/4-FIELD_SIZE_X/50-10)
//#define HOME_DISTANCE  (1000)
//=============================================================================
// 構造体宣言
//=============================================================================

typedef struct // ホーム構造体
{
	D3DXMATRIX		world;						// ワールドマトリックス
	D3DXVECTOR3		Pos;						// ポリゴン表示位置の中心座標
	D3DXVECTOR3		Rot;
	D3DXVECTOR3		Scl;

	float			len;						// 長さ
	float			wid;						// 広さ

}HOME;

typedef struct // ドアの構造体
{
	D3DXMATRIX		world;						// ワールドマトリックス
	D3DXVECTOR3		Pos;						// ポリゴン表示位置の中心座標
	D3DXVECTOR3		Rot;
	D3DXVECTOR3		Scl;
	int				Homeno;
	bool			Use;
}DOOR;


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitHome(int nType);
void UninitHome(void);
void UpdateHome(void);
void DrawHome(void);

HOME  *GetHome(int no);
DOOR *GetDoor(int no);

#endif