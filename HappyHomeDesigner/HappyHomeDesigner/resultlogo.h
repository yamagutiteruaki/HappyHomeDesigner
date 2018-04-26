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
#define	TEXTURE_RESULTLOGO			"data/TEXTURE/result.png"			// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_RESULTLOGO_LOGO	 	"data/TEXTURE/result_logo.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_RESULTLOGO_LOGO2	"data/TEXTURE/���S.png"		// �ǂݍ��ރe�N�X�`���t�@�C����

#define	RESULTLOGO_LOGO_POS_X	(SCREEN_CENTER_X)		// ���U���g���S�̈ʒu(X���W)
#define	RESULTLOGO_LOGO_POS_Y	(200*SCREEN_SCALE)					// ���U���g���S�̈ʒu(Y���W)
#define	RESULTLOGO_LOGO_WIDTH	(800 / 2*SCREEN_SCALE)				// ���U���g���S�̕�
#define	RESULTLOGO_LOGO_HEIGHT	(240 / 2*SCREEN_SCALE)				// ���U���g���S�̍���


#define	RESULTLOGO_LOGO2_POS_X	(SCREEN_CENTER_X)		// ���U���g���S�̈ʒu(X���W)
#define	RESULTLOGO_LOGO2_POS_Y	(500*SCREEN_SCALE)					// ���U���g���S�̈ʒu(Y���W)
#define	RESULTLOGO_LOGO2_WIDTH	(800 / 2*SCREEN_SCALE)				// ���U���g���S�̕�
#define	RESULTLOGO_LOGO2_HEIGHT	(240 / 2*SCREEN_SCALE)				// ���U���g���S�̍���

#define	COUNT_APPERA_RESULTLOGO	(3)		// ���U���g���S�o���܂ł̑҂�����	
#define	LIMIT_COUNT_WAIT	(60 * 15)	// �҂�����

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitResultlogo(int nType);
void UninitResultlogo(void);
void UpdateResultlogo(void);
void DrawResultlogo(void);

#endif
