//=============================================================================
//
// 地面処理 [wall.h]
// Author : 今川乃流
	//
//=============================================================================
#ifndef _WALL_H_
#define _WALL_H_

#include "main.h"
#include "field.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_WALL	"data/TEXTURE/wall005_a.jpg"								// 読み込むテクスチャファイル名
#define	TEXTURE_WALL1	"data/TEXTURE/Floor_wall.jpg"								// 読み込むテクスチャファイル名

#define	WALL_SIZE_X			(FIELD_SIZE_X)										// 地面のサイズ(X方向)
#define	WALL_SIZE_Z			(200.0f)										// 地面のサイズ(Z方向)

#define WALL_MAX				(4)
#define WALL_KIND				(2)

//=============================================================================
// 構造体宣言
//=============================================================================

typedef struct // フィールド構造体
{
	D3DXMATRIX		world;						// ワールドマトリックス
	D3DXVECTOR3		Pos;						// ポリゴン表示位置の中心座標
	D3DXVECTOR3		Rot;						// ポリゴン表示位置の回転座標
	D3DXVECTOR3		Size;

}WALL;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitWall(int nType);
void UninitWall(void);
void UpdateWall(void);
void DrawWall(void);

WALL *GetWall(int no);
#endif