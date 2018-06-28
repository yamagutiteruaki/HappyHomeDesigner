//=============================================================================
//
// �X�R�A���� [score.h]
// Author : 
//
//=============================================================================
#ifndef _RANKSCORE_H_
#define _RANKSCORE_H_

#include "main.h"
#include "rankpaper.h"


//*****************************************************************************
// �}�N����`
// 1�ʂ�X			(500)
// 1�ʂ�Y			(280)
// 2�ʂ�X			(90)
// 2�ʂ�Y			(520)
// 3�ʂ�X			(930)
// 3�ʂ�Y			(520)
//*****************************************************************************
#define	TEXTURE_RANKSCORE		"data/TEXTURE/deg_number3.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	RANKSCORE_SIZE_X		(25.0f)							// �X�R�A�̐����̕�
#define	RANKSCORE_SIZE_Y		(80.0f)						// �X�R�A�̐����̍���
#define	RANKSCORE_INTERVAL_X	(0.0f)							// �X�R�A�̐����̕\���Ԋu

#define	NUM_PLACE			(11)							// �X�R�A�̌��� stage.h��MAX_PRICE�ƌ������킹�邱��

#define	RANKSCORE_POS_X			((float)(-RANKSCORE_SIZE_X*NUM_PLACE/2)+10)						// �X�R�A�̕\����ʒu�w���W
#define	RANKSCORE_POS_Y			(280)				// �X�R�A�̕\����ʒu�x���W


#define SLOT_INTERVAL		(30)

#define RANKSCORE_MAX			(3)


//*******************************************************************************
// �\���̐錾
//*******************************************************************************
typedef struct
{
	D3DXVECTOR3				pos;						// �ʒu
	long long			rankscore;						// �\���X�R�A
	long long			maxrankscore;						//�擾�X�R�A


}RANKSCORE;
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitRankscore(int nType);
void UninitRankscore(void);
void UpdateRankscore(void);
void DrawRankscore(void);
int GetSlotCount(void);

#endif
