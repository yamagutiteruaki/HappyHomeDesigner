//=============================================================================
//
// �^�C�}�[���� [clock.h]
// Author : 
//
//=============================================================================
#ifndef _WEIGHT_H_
#define _WEIGHT_H_


// �}�N����`
#define	NUM_WEIGHT				(4)			// �|���S����

#define TEXTURE_WEIGHT		("data/TEXTURE/power01.png")	// �摜
#define TEXTURE_WEIGHT2		("data/TEXTURE/power01.png")	// �摜
#define TEXTURE_WEIGHT_SIZE_X	(120*SCREEN_SCALE)		// �e�N�X�`���T�C�Y
#define TEXTURE_WEIGHT_SIZE_Y	(120*SCREEN_SCALE)		// ����
#define TEXTURE_WEIGHT_POS_X	(10*SCREEN_SCALE)		// �e�N�X�`���T�C�Y
#define TEXTURE_WEIGHT_POS_Y	(10*SCREEN_SCALE)		// ����
#define WEIGHT_MAX						(4) // �͂̍ő吔

//*****************************************************************************
// �\���̐錾
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitWeight(int type);
void UninitWeight(void);
void UpdateWeight(void);
void DrawWeight(void);


#endif
