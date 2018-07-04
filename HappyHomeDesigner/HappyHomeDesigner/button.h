//=============================================================================
//
// 敵処理 [button.h]
// Author : 
//
//=============================================================================
#ifndef _BUTTON_H_
#define _BUTTON_H_



// マクロ定義
#define	NUM_BUTTON				(2)			// ポリゴン数

#define TEXTURE_GAME_BUTTON_0		("data/TEXTURE/入る.png")	// 画像
#define TEXTURE_GAME_BUTTON_1		("data/TEXTURE/置く.png")	// 画像
#define TEXTURE_GAME_BUTTON_2		("data/TEXTURE/掴む.png")	// 画像
#define TEXTURE_GAME_BUTTON_3		("data/TEXTURE/出る.png")

#define TEXTURE_BUTTON_SIZE_X	(1000/6*SCREEN_SCALE)		// テクスチャサイズ
#define TEXTURE_BUTTON_SIZE_Y	(300/6*SCREEN_SCALE)		// 同上

#define TIME_ANIMATION_BUTTON			(1)	// アニメーションの切り替わるカウント

#define BUTTON_MAX						(4) // 見つかれる最大数
//*****************************************************************************
// 構造体宣言
//*****************************************************************************

typedef struct	// エネミー構造体
{
	bool			use;						// true:使用  false:未使用
	D3DXVECTOR3		pos;						// ポリゴンの移動量
	D3DXVECTOR3		rot;						// ポリゴンの回転量
	int				kind;					// 種類
	LPDIRECT3DTEXTURE9	Texture;				// テクスチャ情報
	VERTEX_2D		vertexWk[NUM_VERTEX];		// 頂点情報格納ワーク

	float			Radius;						// エネミーの半径
	float			BaseAngle;					// エネミーの角度

	D3DXVECTOR2		rate;


} BUTTON;

enum 
{
	ENTER_BUTTON,
	EXIT_BUTTON,
	PUT_BUTTON,
	GET_BUTTON
};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitButton(int type);
void UninitButton(void);
void UpdateButton(void);
void DrawButton(void);
BUTTON *GetButton(int no);
void Button(bool flag,int no);


#endif
