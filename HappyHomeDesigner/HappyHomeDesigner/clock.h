//=============================================================================
//
// タイマー処理 [clock.h]
// Author : 
//
//=============================================================================
#ifndef _CLOCK_H_
#define _CLOCK_H_


// マクロ定義
#define	NUM_CLOCK				(2)			// ポリゴン数

#define TEXTURE_GAME_CLOCK		("data/TEXTURE/bullet_R1.png")	// 画像
#define TEXTURE_CLOCK_SIZE_X	(50/2)		// テクスチャサイズ
#define TEXTURE_CLOCK_SIZE_Y	(50/2)		// 同上

#define TEXTURE_PATTERN_DIVIDE_X_CLOCK	(1)	// アニメパターンのテクスチャ内分割数（X)
#define TEXTURE_PATTERN_DIVIDE_Y_CLOCK	(1)	// アニメパターンのテクスチャ内分割数（Y)
#define ANIM_PATTERN_NUM_CLOCK			(TEXTURE_PATTERN_DIVIDE_X_CLOCK*TEXTURE_PATTERN_DIVIDE_Y_CLOCK)	// アニメーションパターン数
#define TIME_ANIMATION_CLOCK			(4)	// アニメーションの切り替わるカウント

#define CLOCK_MAX						(1) // 敵の最大数

//*****************************************************************************
// 構造体宣言
//*****************************************************************************

typedef struct	// エネミー構造体
{
	bool			use;						// true:使用  false:未使用
	D3DXVECTOR3		pos;						// ポリゴンの移動量
	D3DXVECTOR3		rot;						// ポリゴンの回転量
	int				PatternAnim;				// アニメーションパターンナンバー
	int				CountAnim;					// アニメーションカウント

	LPDIRECT3DTEXTURE9	Texture;				// テクスチャ情報
	VERTEX_2D		vertexWk[NUM_VERTEX];		// 頂点情報格納ワーク

	float			Radius;						// エネミーの半径
	float			BaseAngle;					// エネミーの角度

} CLOCK;



//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitClock(int type);
void UninitClock(void);
void UpdateClock(void);
void DrawClock(void);
CLOCK *GetClock(int no);


#endif
