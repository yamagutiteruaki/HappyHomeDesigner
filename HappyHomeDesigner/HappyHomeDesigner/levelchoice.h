//=============================================================================
//
// 敵処理 [voice.h]
// Author : 
//
//=============================================================================
#ifndef _VOICE_H_
#define _VOICE_H_


// マクロ定義
#define	NUM_VOICE				(2)			// ポリゴン数

#define TEXTURE_GAME_VOICE		("data/TEXTURE/wait.png")	// 画像
#define TEXTURE_VOICE_SIZE_X	(900/2*SCREEN_SCALE)		// テクスチャサイズ
#define TEXTURE_VOICE_SIZE_Y	(550/2*SCREEN_SCALE)		// 同上

#define TEXTURE_PATTERN_DIVIDE_X_VOICE	(1)	// アニメパターンのテクスチャ内分割数（X)
#define TEXTURE_PATTERN_DIVIDE_Y_VOICE	(1)	// アニメパターンのテクスチャ内分割数（Y)
#define ANIM_PATTERN_NUM_VOICE			(TEXTURE_PATTERN_DIVIDE_X_VOICE*TEXTURE_PATTERN_DIVIDE_Y_VOICE)	// アニメーションパターン数
#define TIME_ANIMATION_VOICE			(1)	// アニメーションの切り替わるカウント

#define VOICE_MAX						(1) // 声の最大数
#define VOICE_SPEED						(300) //声のスピード
//*****************************************************************************
// 構造体宣言
//*****************************************************************************

typedef struct	// エネミー構造体
{
	bool			use;						// true:使用  false:未使用
	D3DXVECTOR3		pos;						// ポリゴンの移動量
	D3DXVECTOR3		rot;						// ポリゴンの回転量
	int				cnt_frame;					// カウント
	int				count;						// 回数
	LPDIRECT3DTEXTURE9	Texture;				// テクスチャ情報
	VERTEX_2D		vertexWk[NUM_VERTEX];		// 頂点情報格納ワーク

	float			Radius;						// エネミーの半径
	float			BaseAngle;					// エネミーの角度

} VOICE;



//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitVoice(int type);
void UninitVoice(void);
void UpdateVoice(void);
void DrawVoice(void);
VOICE *GetVoice(int no);


#endif
