//=============================================================================
//
// プレイヤー処理 [player.h]
// Author : 宋彦霖
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	PLAYER_MAX			(1)			// ポリスの最大数

#define	PLAYER_WID			(10.0f)		// ポリスの幅
#define	PLAYER_HEI			(20.0f)		// ポリスの高さ

#define HAVE_MAX			(5)			// 家具を持てる最大数
#define WT_MAX				(5)			// 所持重量制限

#define PLAYER_SHADOW_SIZE	(23.0f)			// プレイヤーの影サイズ

//*****************************************************************************
// 構造体宣言
//*****************************************************************************
typedef struct		// プレイヤー構造体
{
	bool			use;							// true:使用  false:未使用

	int				hp;								// HP

	D3DXVECTOR3		scl;							// スケール

	D3DXVECTOR3		Eye;							// プレイヤーの視点
	D3DXVECTOR3		At;								// プレイヤーの注視点
	D3DXVECTOR3		Up;								// プレイヤーの上方向
	D3DXVECTOR3		rot;							// プレイヤーの向き
	D3DXVECTOR3		rotDest;						// プレイヤーの目的の向き
	D3DXVECTOR3		move;							// プレイヤーの移動量

	D3DXVECTOR3		posTmp;							// プレイヤーの視点（一時保存）


	VERTEX_2D		vertexWk[NUM_VERTEX];			// 頂点情報格納ワーク

	int				anim;							// アニメーション番号

	float			speed;							// 移動速度係数

	int				weight;

	int				havenum[HAVE_MAX];	

	int				nIdxShadow;
	float			fSizeShadow;
	D3DXCOLOR		colShadow;
	bool			bShadow;

} PLAYER;


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitPlayer(int nType);
void UninitPlayer(void);
void DrawPlayer(void);
void UpdatePlayer(void);

PLAYER *GetPlayer(int no);
void SetResetno(int no);


#endif
