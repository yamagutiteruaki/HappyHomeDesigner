
//=============================================================================
//
// timeeffect.h
// Author : 
//
//=============================================================================
#ifndef _TIMEEFFECT_H_
#define _TIMEEFFECT_H_

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_TIME_EFF		"data/TEXTURE/effect001.png"		// �ǂݍ��ރe�N�X�`���t�@�C����

#define WARNING_TIME		(2 * D3DX_PI * 10 / 12)
#define ALPHA_RATE			(0.02f)
#define ALPHA_MAX			(0.4f)

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitTimeeffect(void);
void UninitTimeeffect(void);
void UpdateTimeeffect(void);
void DrawTimeeffect(void);

#endif