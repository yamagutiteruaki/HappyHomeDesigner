//=============================================================================
//
// ���U���g��ʏ��� [resultlogo.h]
// Author : GP12B295 �K �֌��V��
//
//=============================================================================
#ifndef _RESULTLOGO_H_
#define _RESULTLOGO_H_

#include "main.h"


//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_RESULT			"data/TEXTURE/rouya.jpg"		// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_RESULT_LOGO		"data/TEXTURE/result.png"		// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_RESULT_LOGO2	"data/TEXTURE/��Q���z.png"			// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_RESULT_GAMEOVER	"data/TEXTURE/GAMEOVER00.png"			// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_RESULT_CLEAR	"data/TEXTURE/GAME_RESULT00.png"			// �ǂݍ��ރe�N�X�`���t�@�C����
#define	RESULT_LOGO2_WIDTH	(1200)				// ���U���g���S�̕�
#define	RESULT_LOGO2_HEIGHT	(480)				// ���U���g���S�̍���


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitResultLogo(void);
void UninitResultLogo(void);
void UpdateResultLogo(void);
void DrawResultLogo(void);

#endif
