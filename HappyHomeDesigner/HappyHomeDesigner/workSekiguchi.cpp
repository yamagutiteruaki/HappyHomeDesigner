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

	InitClock(0);

	InitResultLogo();

	InitScore();

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

		break;
	case STAGE_RESULT:

		 UpdateResultLogo();

		 UpdateScore();

		break;
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawWorkSekiguchi(void)
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

		DrawClock();

		break;
	case STAGE_RESULT:

		 DrawResultLogo();

		 DrawScore();

		break;
	}
}

