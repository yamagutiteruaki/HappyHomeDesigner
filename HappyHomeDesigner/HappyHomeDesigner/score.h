//=============================================================================
//
// �X�R�A���� [score.h]
// Author : 
//
//=============================================================================
#ifndef _SCORE_H_
#define _SCORE_H_

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_SCORE		"data/TEXTURE/deg_number3.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	SCORE_SIZE_X		(105.0f)							// �X�R�A�̐����̕�
#define	SCORE_SIZE_Y		(225.0f)						// �X�R�A�̐����̍���
#define	SCORE_INTERVAL_X	(0.0f)							// �X�R�A�̐����̕\���Ԋu

#define	NUM_PLACE			(10)							// �X�R�A�̌���

#define	SCORE_POS_X			(SCREEN_CENTER_X-SCORE_SIZE_X*(NUM_PLACE/2))						// �X�R�A�̕\����ʒu�w���W
#define	SCORE_POS_Y			(450.0f)				// �X�R�A�̕\����ʒu�x���W


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitScore(void);
void UninitScore(void);
void UpdateScore(void);
void DrawScore(void);

#endif
