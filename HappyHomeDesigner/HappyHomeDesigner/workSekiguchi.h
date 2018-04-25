//=============================================================================
//
// 関口担当分 [workSekiguci.h]
// Author : GP12B295 �K 関口昂平
//
//=============================================================================
#ifndef _WORKSEKIGUCHI_H_
#define _WORKSEKIGUCHI_H_

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

/*******************************************************************************
* 構造体定義
*******************************************************************************/

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitWorkSekiguchi(int nType);
void UninitWorkSekiguchi(void);
void UpdateWorkSekiguchi(void);
void DrawWorkSekiguchi(void);

#endif
