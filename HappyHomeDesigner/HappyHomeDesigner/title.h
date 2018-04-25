
//=============================================================================
//
// �^�C�g����ʏ��� [title.h]
// Author : 
//
//=============================================================================
#ifndef _TITLE_H_
#define _TITLE_H_

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_TITLE		"data/TEXTURE/����̐��@�J����.png"		// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_TITLE_LOGO	"data/TEXTURE/Titlelogo_00.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_LOGO_START	"data/TEXTURE/Press_enter00.png"	// �ǂݍ��ރe�N�X�`���t�@�C����

#define	TITLE_LOGO_POS_X		(20)		// �^�C�g�����S�̈ʒu(X���W)
#define	TITLE_LOGO_POS_Y		(10)		// �^�C�g�����S�̈ʒu(Y���W)
#define	TITLE_LOGO_WIDTH		(SCREEN_WIDTH)		// �^�C�g�����S�̕�
#define	TITLE_LOGO_HEIGHT		(SCREEN_HEIGHT)		// �^�C�g�����S�̍���

#define	START_POS_X				(SCREEN_WIDTH/2)		// �X�^�[�g�{�^���̈ʒu(X���W)
#define	START_POS_Y				(SCREEN_HEIGHT/2)		// �X�^�[�g�{�^���̈ʒu(Y���W)
#define	START_WIDTH				(800/2)		// �X�^�[�g�{�^���̕�
#define	START_HEIGHT			(500/2)		// �X�^�[�g�{�^���̍���

#define	COUNT_APPERA_START		(60)		// �X�^�[�g�{�^���o���܂ł̎���
#define	INTERVAL_DISP_START		(60)		// �X�^�[�g�{�^���_�ł̎���

#define	COUNT_WAIT_DEMO			(60 * 5)	// �f���܂ł̑҂�����
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitTitle(void);
void UninitTitle(void);
void UpdateTitle(void);
void DrawTitle(void);

#endif