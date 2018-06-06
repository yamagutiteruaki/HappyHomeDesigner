//=============================================================================
//
// 敵処理 [arrest.h]
// Author : 
//
//=============================================================================
#ifndef _ARREST_H_
#define _ARREST_H_


// マクロ定義
#define	NUM_ARREST				(2)			// ポリゴン数

#define TEXTURE_GAME_ARREST		("data/TEXTURE/police.png")	// 画像
#define TEXTURE_ARREST_SIZE_X	(150/2*SCREEN_SCALE)		// テクスチャサイズ
#define TEXTURE_ARREST_SIZE_Y	(150/2*SCREEN_SCALE)		// 同上

#define TEXTURE_PATTERN_DIVIDE_X_ARREST	(1)	// アニメパターンのテクスチャ内分割数（X)
#define TEXTURE_PATTERN_DIVIDE_Y_ARREST	(1)	// アニメパターンのテクスチャ内分割数（Y)
#define ANIM_PATTERN_NUM_ARREST			(TEXTURE_PATTERN_DIVIDE_X_ARREST*TEXTURE_PATTERN_DIVIDE_Y_ARREST)	// アニメーションパターン数
#define TIME_ANIMATION_ARREST			(1)	// アニメーションの切り替わるカウント

#define ARREST_MAX						(10) // 見つかれる最大数
#define ARREST_SPEED						(300) //声のスピード
//*****************************************************************************
// 構造体宣言
//*****************************************************************************

typedef struct	// エネミー構造体
{
	bool			use;						// true:使用  false:未使用
	D3DXVECTOR3		pos;						// ポリゴンの移動量
	D3DXVECTOR3		rot;						// ポリゴンの回転量
	int				cnt_frame;					// カウント
	LPDIRECT3DTEXTURE9	Texture;				// テクスチャ情報
	VERTEX_2D		vertexWk[NUM_VERTEX];		// 頂点情報格納ワーク

	float			Radius;						// エネミーの半径
	float			BaseAngle;					// エネミーの角度

} ARREST;



//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitArrest(int type);
void UninitArrest(void);
void UpdateArrest(void);
void DrawArrest(void);
ARREST *GetArrest(int no);


#endif
