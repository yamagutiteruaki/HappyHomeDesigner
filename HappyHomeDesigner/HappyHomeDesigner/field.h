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
#define TEXTURE_FIELD1	"data/TEXTURE/Floor.jpg"



#define	FIELD_SIZE_X			(1000.0f)										// 地面のサイズ(X方向)
#define	FIELD_SIZE_Z			(1000.0f)										// 地面のサイズ(Z方向)

#define FIELD_MAX				(2)
#define HOME_MAX				(4)

#define HOME_DISTANCE  (FIELD_SIZE_X/4-FIELD_SIZE_X/50-10)
//=============================================================================
// 構造体宣言
//=============================================================================

typedef struct // フィールド構造体
{
	D3DXMATRIX		world;						// ワールドマトリックス
	D3DXVECTOR3		Pos;						// ポリゴン表示位置の中心座標
	D3DXVECTOR3		Size;						//サイズ

}FIELD;

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
HRESULT InitField(void);
void UninitField(void);
void UpdateField(void);
void DrawField(void);

FIELD *GetField(int no);
HOME  *GetHome(int no);
DOOR *GetDoor(int no);

#endif