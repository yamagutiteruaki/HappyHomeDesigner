//=============================================================================
//
// �����S���� [workMatsuo.cpp]
// Author GP12A295 28 ��������
//
//=============================================================================
#include "workMatsuo.h"
#include "stage.h"
#include "input.h"
#include "fade.h"
#include "game.h"


// �����S�����ŕK�v�ȃC���N���[�h
#include "title.h"
#include "titlelogo.h"
#include "weight.h"
#include "voice.h"
#include "arrest.h"
#include "button.h"
#include "rankscore.h"
#include "run.h"
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
HRESULT InitWorkMatsuo(int nType)
{
	InitTitlelogo();
	InitWeight(nType);
	InitVoice(nType);
	InitArrest(nType);
	InitButton(nType);
	InitRankscore(nType);
	InitRun(nType);
	InitRankpaper();
	InitRankscore(nType);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitWorkMatsuo(void)
{
	UninitTitlelogo();
	UninitWeight();
	UninitVoice();
	UninitArrest();
	UninitButton();
	UninitRankscore();
	UninitRun();
	UninitRankpaper();
	UninitRankscore();

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateWorkMatsuo(void)
{
	switch (GetStage())
	{
	case STAGE_TITLE:
		UpdateTitlelogo();

		break;
	case STAGE_GAME:
	case STAGE_HOUSE1:
	case STAGE_HOUSE2:
	case STAGE_HOUSE3:
	case STAGE_MYHOUSE:

		UpdateWeight();
		UpdateVoice();
		UpdateArrest();
		UpdateButton();
		break;
	case STAGE_RESULT:
		break;
	case STAGE_RANKING:
		UpdateRankpaper();
		UpdateRankscore();
		UpdateRun();


		break;
	}

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawWorkMatsuo(int no)
{
	switch (GetStage())
	{
	case STAGE_TITLE:
		DrawTitlelogo();
		break;
	case STAGE_GAME:
		if (no == GAME_VOICE)	DrawVoice();

	case STAGE_HOUSE1:
	case STAGE_HOUSE2:
	case STAGE_HOUSE3:
	case STAGE_MYHOUSE:
		if (no == GAME_ARREST)	DrawArrest();
		if (no == GAME_WEIGHT)	DrawWeight();
		if (no == GAME_BUTTON)	DrawButton();
		break;
	case STAGE_RESULT:
		break;
	case STAGE_RANKING:
		DrawRankpaper();
		DrawRankscore();
		DrawRun();

		break;

	}
}

