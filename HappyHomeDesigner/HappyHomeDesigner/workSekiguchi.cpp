//=============================================================================
//
// �֌��S���� [workSekiguchi.cpp]
// Author GP12B295 �K �֌��V��
//
//=============================================================================
#include "workSekiguchi.h"
#include "stage.h"
#include "input.h"
#include "fade.h"
#include "game.h"


// �֌��S�����ŕK�v�ȃC���N���[�h
#include "clock.h"
#include "result.h"
#include "resultlogo.h"
#include "score.h"

// �f�o�b�O�p
#ifdef _DEBUG
#include "debugproc.h"
#endif

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

//=============================================================================
// ����������
//=============================================================================
HRESULT InitWorkSekiguchi(int nType)
{

	InitClock(nType);

	InitResultLogo(nType);

	InitScore(nType);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitWorkSekiguchi(void)
{
	UninitClock();

	UninitResultLogo();

	UninitScore();
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateWorkSekiguchi(void)
{
	switch (GetStage())
	{
	case STAGE_TITLE:
		break;
	case STAGE_GAME:
	case STAGE_HOUSE1:
	case STAGE_HOUSE2:
	case STAGE_HOUSE3:
	case STAGE_MYHOUSE:

		UpdateClock();
		//UpdateScore();

		break;
	case STAGE_RESULT:
	case STAGE_RANKING:
		 UpdateResultLogo();

		 UpdateScore();

		break;
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawWorkSekiguchi(int no)
{
	switch (GetStage())
	{
	case STAGE_TITLE:
		break;
	case STAGE_GAME:
	case STAGE_HOUSE1:
	case STAGE_HOUSE2:
	case STAGE_HOUSE3:
	case STAGE_MYHOUSE:

		if (no == GAME_CLOCK)	DrawClock();

		break;
	case STAGE_RESULT:
	case STAGE_RANKING:

		 DrawResultLogo();

		 DrawScore();

		break;
	}
}

