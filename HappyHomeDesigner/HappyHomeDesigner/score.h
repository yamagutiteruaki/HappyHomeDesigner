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

#define	NUM_PLACE			(11)							// �X�R�A�̌��� stage.h��MAX_PRICE�ƌ������킹�邱��

#define	SCORE_POS_X			(SCREEN_CENTER_X-SCORE_SIZE_X*(5.5))						// �X�R�A�̕\����ʒu�w���W
#define	SCORE_POS_Y			(450.0f)				// �X�R�A�̕\����ʒu�x���W

#define SLOT_INTERVAL		(30)


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitScore(int nType);
void UninitScore(void);
void UpdateScore(void);
void DrawScore(void);
int GetSlotCount(void);

#endif
