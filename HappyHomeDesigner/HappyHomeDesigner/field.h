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
#define	TEXTURE_FIELD	"data/TEXTURE/field_glass.jpg"								// 読み込むテクスチャファイル名
#define	TEXTURE_HOME	"data/TEXTURE/field001.jpg"							// 読み込むテクスチャファイル名

#define	FIELD_SIZE_X			(600.0f)										// 地面のサイズ(X方向)
#define	FIELD_SIZE_Z			(600.0f)										// 地面のサイズ(Z方向)

#define HOME_SIZE_X		(100.0f)										//家の床のサイズ(X方向)
#define HOME_SIZE_Z		(100.0f)										//家の床のサイズ(Y方向)

#define FIELD_MAX				(1)
#define HOME_MAX				(4)

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

}HOME;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitField(void);
void UninitField(void);
void UpdateField(void);
void DrawField(void);

FIELD *GetField(int no);
HOME  *GetHome(int no);
#endif