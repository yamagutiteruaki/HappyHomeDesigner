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
#define	TEXTURE_RESULT_GAMEOVER	"data/TEXTURE/GAME_OVER.png"			// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_RESULT_CLEAR	"data/TEXTURE/GAME_CLEAR.png"			// �ǂݍ��ރe�N�X�`���t�@�C����
#define	RESULT_LOGO2_WIDTH	(1200)				// ���U���g���S�̕�
#define	RESULT_LOGO2_HEIGHT	(480)				// ���U���g���S�̍���

//#define TEXTURE_GAME_SCORE00	("data/TEXTURE/deg_number3.png")	// �T���v���p�摜
//#define TEXTURE_SCORE00_SIZE_X	(1000)	// �e�N�X�`���T�C�Y
//#define TEXTURE_SCORE00_SIZE_Y	(500)	// ����
//#define SCORE_POS_X			(1500)		// �|���S���̏����ʒuX
//#define SCORE_POS_Y			(2000)		// ����
//#define SCORE_MAX			(999999999)		// �X�R�A�̍ő�l
//#define SCORE_DIGIT			(1)			

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitResultLogo(void);
void UninitResultLogo(void);
void UpdateResultLogo(void);
void DrawResultLogo(void);

#endif
