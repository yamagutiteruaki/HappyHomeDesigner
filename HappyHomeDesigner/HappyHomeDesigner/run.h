//=============================================================================
//
// プレイヤー処理 [run.h]
// Author : 
//
//=============================================================================
#ifndef _RUN_H_
#define _RUN_H_
#include <time.h>
#include "main.h"


// マクロ定義
#define	NUM_RUN		(2)					// ポリゴン数

#define TEXTURE_GAME_RUN	("data/TEXTURE/runningman002.png")	// 画像
#define TEXTURE_RUN_SIZE_X	(900) // テクスチャサイズ
#define TEXTURE_RUN_SIZE_Y	(900) // 同上

#define TEXTURE_PATTERN_DIVIDE_X	(5)	// アニメパターンのテクスチャ内分割数（X)
#define TEXTURE_PATTERN_DIVIDE_Y	(2)	// アニメパターンのテクスチャ内分割数（Y)
#define ANIM_PATTERN_NUM			(TEXTURE_PATTERN_DIVIDE_X*TEXTURE_PATTERN_DIVIDE_Y)	// アニメーションパターン数
#define TIME_ANIMATION				(2)	// アニメーションの切り替わるカウント

#define RUN_MAX					(1) // プレイヤーの最大数


//*****************************************************************************
// 構造体宣言
//*****************************************************************************

typedef struct	// プレイヤー構造体
{
	bool			use;						// true:使用  false:未使用
	D3DXVECTOR3		pos;						// ポリゴンの移動量
	D3DXVECTOR3		rot;						// ポリゴンの回転量
	int				PatternAnim;				// アニメーションパターンナンバー
	int				CountAnim;					// アニメーションカウント

	LPDIRECT3DTEXTURE9	Texture;				// テクスチャ情報
	VERTEX_2D		vertexWk[NUM_VERTEX];		// 頂点情報格納ワーク

	float			Radius;						// プレイヤーの半径
	float			BaseAngle;					// プレイヤーの角度

} RUN;


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitRun(int type);
void UninitRun(void);
void UpdateRun(void);
void DrawRun(void);
RUN *GetRun(int no);


#endif
