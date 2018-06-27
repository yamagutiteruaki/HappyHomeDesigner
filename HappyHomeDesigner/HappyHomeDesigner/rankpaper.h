
//=============================================================================
//
// �^�C�g����ʏ��� [title.h]
// Author : 
//
//=============================================================================
#ifndef _RANKPAPERLOGO_H_
#define _RANKPAPERLOGO_H_

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_RANKPAPER_BACK		"data/TEXTURE/field000.jpg"		// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_RANKPAPER0			"data/TEXTURE/��z��.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_RANKPAPER1			"data/TEXTURE/��z��.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_RANKPAPER2			"data/TEXTURE/��z��.png"	// �ǂݍ��ރe�N�X�`���t�@�C����

#define	TEXTURE_FIRST				"data/TEXTURE/1st.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_SECOND				"data/TEXTURE/2nd.png"			//�ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_THIRD				"data/TEXTURE/3rd.png"			//�ǂݍ��ރe�N�X�`���t�@�C����


#define	RANKPAPERBACK_POS_X					(0)		// �^�C�g�����S�̈ʒu(X���W)
#define	RANKPAPERBACK_POS_Y					(0)		// �^�C�g�����S�̈ʒu(Y���W)
#define	RANKPAPERBACK_WIDTH					(SCREEN_WIDTH)		// �^�C�g�����S�̕�
#define	RANKPAPERBACK_HEIGHT				(SCREEN_HEIGHT)		// �^�C�g�����S�̍���

#define	RANKPAPER0_POS_X					(SCREEN_WIDTH/3)		// �^�C�g�����S�̈ʒu(X���W)
#define	RANKPAPER0_POS_Y					(0)		// �^�C�g�����S�̈ʒu(Y���W)
#define	RANKPAPER0_WIDTH					(400)		// �^�C�g�����S�̕�
#define	RANKPAPER0_HEIGHT				(400)		// �^�C�g�����S�̍���

#define	RANKPAPER1_POS_X					(20)		// �^�C�g�����S�̈ʒu(X���W)
#define	RANKPAPER1_POS_Y					(SCREEN_HEIGHT/3)		// �^�C�g�����S�̈ʒu(Y���W)
#define	RANKPAPER1_WIDTH					(400)		// �^�C�g�����S�̕�
#define	RANKPAPER1_HEIGHT				(400)		// �^�C�g�����S�̍���

#define	RANKPAPER2_POS_X					(SCREEN_WIDTH-RANKPAPER2_WIDTH-20)		// �^�C�g�����S�̈ʒu(X���W)
#define	RANKPAPER2_POS_Y					(SCREEN_HEIGHT/3)		// �^�C�g�����S�̈ʒu(Y���W)
#define	RANKPAPER2_WIDTH					(400)		// �^�C�g�����S�̕�
#define	RANKPAPER2_HEIGHT				(400)		// �^�C�g�����S�̍���

#define	RANKPAPER_FIRST_POS_X		(RANKPAPER0_POS_X+RANKPAPER0_WIDTH/4)		// �^�C�g�����S�̈ʒu(X���W)
#define	RANKPAPER_FIRST_POS_Y		(RANKPAPER0_HEIGHT-80)		// �^�C�g�����S�̈ʒu(Y���W)
#define	RANKPAPER_FIRST_WIDTH		(200)		// �^�C�g�����S�̕�
#define	RANKPAPER_FIRST_HEIGHT		(200)		// �^�C�g�����S�̍���

#define	RANKPAPER_SECOND_POS_X		(RANKPAPER1_POS_X+RANKPAPER1_WIDTH/4)		// �^�C�g�����S�̈ʒu(X���W)
#define	RANKPAPER_SECOND_POS_Y		(SCREEN_HEIGHT/2+RANKPAPER1_HEIGHT/2)		// �^�C�g�����S�̈ʒu(Y���W)
#define	RANKPAPER_SECOND_WIDTH		(200)		// �^�C�g�����S�̕�
#define	RANKPAPER_SECOND_HEIGHT		(200)		// �^�C�g�����S�̍���

#define	RANKPAPER_THIRD_POS_X		(RANKPAPER2_POS_X+RANKPAPER2_WIDTH/4)		// �^�C�g�����S�̈ʒu(X���W)
#define	RANKPAPER_THIRD_POS_Y		(SCREEN_HEIGHT/2+RANKPAPER2_HEIGHT/2)		// �^�C�g�����S�̈ʒu(Y���W)
#define	RANKPAPER_THIRD_WIDTH		(200)		// �^�C�g�����S�̕�
#define	RANKPAPER_THIRD_HEIGHT		(200)		// �^�C�g�����S�̍���

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitRankpaper(void);
void UninitRankpaper(void);
void UpdateRankpaper(void);
void DrawRankpaper(void);

#endif