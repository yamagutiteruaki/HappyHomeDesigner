//=============================================================================
//
// �R���S���� [workYamaguchi.cpp]
// Author GP12B295 29 �R���P��
//
//=============================================================================
#include "workYamaguchi.h"
#include "stage.h"
#include "input.h"
#include "fade.h"
#include "game.h"

// �R���S�����ŕK�v�ȃC���N���[�h
#include "ranking.h"
#include "timeeffect.h"
#include "shadow.h"
#include "GetUI.h"

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
HRESULT InitWorkYamaguchi(int nType)
{
	InitTimeeffect(nType);
	InitShadow(nType);
	InitGetUI(nType);
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitWorkYamaguchi(void)
{
	UninitTimeeffect();
	UninitShadow();
	UninitGetUI();

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateWorkYamaguchi(void)
{
	switch (GetStage())
	{
	case STAGE_GAME:
	case STAGE_HOUSE1:
	case STAGE_HOUSE2:
	case STAGE_HOUSE3:
	case STAGE_MYHOUSE:

		UpdateTimeeffect();
		UpdateShadow();
		UpdateGetUI();
		break;
	}

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawWorkYamaguchi(int no)
{
	switch (GetStage())
	{
	case STAGE_GAME:
	case STAGE_HOUSE1:
	case STAGE_HOUSE2:
	case STAGE_HOUSE3:
	case STAGE_MYHOUSE:
		if (no == GAME_SHADOW)	DrawShadow();
		if (no == GAME_TIMEEFF)	DrawTimeeffect();
		if (no == GAME_GETUI)	DrawGetUI();
		break;
	}
}

