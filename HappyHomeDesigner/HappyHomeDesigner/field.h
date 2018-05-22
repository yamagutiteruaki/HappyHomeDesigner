#pragma once
//=============================================================================
//
// 地面処理 [field.h]
// Author : 今川乃流
//
//=============================================================================
#ifndef _FIELD_H_
#define _FIELD_H_

#include "main.h"


//*****************************************************************************
// マクロ定義
//*****************************************************************************

#define	TEXTURE_FIELD	"data/TEXTURE/field_stone.jpg"								// 読み込むテクスチャファイル名



#define	FIELD_SIZE_X			(1000.0f)										// 地面のサイズ(X方向)
#define	FIELD_SIZE_Z			(1000.0f)										// 地面のサイズ(Z方向)

#define HOME_SIZE_X		(100.0f)										//家の床のサイズ(X方向)
#define HOME_SIZE_Z		(100.0f)										//家の床のサイズ(Y方向)

#define	DOOR_SIZE_X			(1000.0f)										// ドアのサイズ(X方向)
#define	DOOR_SIZE_Z			(1000.0f)										// ドアのサイズ(Z方向)

#define FIELD_MAX				(1)
#define HOME_MAX				(4)

#define HOME_DISTANCE  (FIELD_SIZE_X/4-FIELD_SIZE_X/50)
//=============================================================================
// 構造体宣言
//=============================================================================

typedef struct // フィールド構造体
{
	D3DXMATRIX		world;						// ワールドマトリックス
	D3DXVECTOR3		Pos;						// ポリゴン表示位置の中心座標

}FIELD;

typedef struct // フィールド構造体
{
	D3DXMATRIX		world;						// ワールドマトリックス
	D3DXVECTOR3		Pos;						// ポリゴン表示位置の中心座標
	D3DXVECTOR3		Rot;
	D3DXVECTOR3		Scl;
}HOME;

typedef struct // ドアの構造体
{
	D3DXMATRIX		world;						// ワールドマトリックス
	D3DXVECTOR3		Pos;						// ポリゴン表示位置の中心座標
	D3DXVECTOR3		Rot;
	D3DXVECTOR3		Scl;
}DOOR;


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitField(void);
void UninitField(void);
void UpdateField(void);
void DrawField(void);

FIELD *GetField(int no);
HOME  *GetHome(int no);
DOOR *GetDoor(int no);

#endif