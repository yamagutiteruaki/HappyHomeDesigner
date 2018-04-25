//=============================================================================
//
// 松尾担当分 [workMatsuo.h]
// Author : GP12B295 29 山口輝明
//
//=============================================================================
#ifndef _WORKMATSUO_H_
#define _WORKMATSUO_H_

#include "main.h"
#include "title.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

/*******************************************************************************
* 構造体定義
*******************************************************************************/

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitWorkMatsuo(int nType);
void UninitWorkMatsuo(void);
void UpdateWorkMatsuo(void);
void DrawWorkMatsuo(void);

#endif
