//=============================================================================
//
// タイマー処理 [clock.h]
// Author : GP12B295 ⑫ 関口昂平
//
//=============================================================================
#ifndef _CLOCK_H_
#define _CLOCK_H_


//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	NUM_CLOCK				(2)			// ポリゴン数

#define TEXTURE_GAME_CLOCK			("data/TEXTURE/clock.png")				// タイマー画像
#define TEXTURE_GAME_CLOCKHAND		("data/TEXTURE/clockhand01.png")		// 針画像

#define CLOCK_POS_X				(SCREEN_CENTER_X)
#define CLOCK_POS_Y				(60)

#define	CLOCK_WIDTH		(100 / 2*SCREEN_SCALE)				// タイマーの幅
#define	CLOCK_HEIGHT	(100 / 2*SCREEN_SCALE)				// タイマーの高さ

#define TEXTURE_CLOCK_SIZE_X		(100/2)		// テクスチャサイズ
#define TEXTURE_CLOCK_SIZE_Y		(100/2)		// 同上
#define TEXTURE_CLOCKHAND_SIZE_X	(100/2)		// 同上
#define TEXTURE_CLOCKHAND_SIZE_Y	(100/2)		// 同上

#define TEXTURE_PATTERN_DIVIDE_X_CLOCKHAND	(1)	// アニメパターンのテクスチャ内分割数（X)
#define TEXTURE_PATTERN_DIVIDE_Y_CLOCKHAND	(1)	// アニメパターンのテクスチャ内分割数（Y)
#define ANIM_PATTERN_NUM_CLOCKHAND			(TEXTURE_PATTERN_DIVIDE_X_CLOCK*TEXTURE_PATTERN_DIVIDE_Y_CLOCK)	// アニメーションパターン数
#define TIME_ANIMATION_CLOCKHAND			(4)	// アニメーションの切り替わるカウント

#define CLOCK_MAX						(1) 

//*****************************************************************************
// 構造体宣言
//*****************************************************************************

typedef struct	// 針構造体
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
//CLOCK *StopClock(void);


#endif
