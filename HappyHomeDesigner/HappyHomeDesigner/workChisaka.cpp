//=============================================================================
//
// ���S���� [workChisaka.cpp]
// Author GP12B295 29 �R���P��
//
//=============================================================================
#include "workChisaka.h"
#include "stage.h"
#include "input.h"
#include "fade.h"
#include "game.h"

// ���S�����ŕK�v�ȃC���N���[�h
#include "police.h"
#include "search.h"
#include "furniture.h"
#include "minimap.h"
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
HRESULT InitWorkChisaka(int nType)
{
	InitPolice(nType);
	InitSearch(nType);
	InitFurniture(nType);
	InitMinimap(nType);
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitWorkChisaka(void)
{
	UninitPolice();
	UninitSearch();
	UninitFurniture();
	UninitMinimap();
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateWorkChisaka(void)
{
	switch (GetStage())
	{
	case STAGE_TITLE:
		break;
	case STAGE_GAME:
		UpdatePolice();
		UpdateSearch();
		UpdateFurniture();
		UpdateMinimap();
		break;
	case STAGE_HOUSE1:
	case STAGE_HOUSE2:
	case STAGE_HOUSE3:
	case STAGE_MYHOUSE:
		UpdateFurniture();
		break;
	case STAGE_RESULT:
	case STAGE_RANKING:
		UpdateFurniture();
		break;
	}

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawWorkChisaka(int no)
{
	switch (GetStage())
	{
	case STAGE_TITLE:
		break;
	case STAGE_GAME:
		if (no == GAME_POLICE)	DrawPolice();
		if (no == GAME_SEARCH)	DrawSearch();
		if (no == GAME_MINIMAP)	DrawMinimap();
		break;
	case STAGE_HOUSE1:
	case STAGE_HOUSE2:
	case STAGE_HOUSE3:
	case STAGE_MYHOUSE:
		if (no == GAME_FURNITURE)	DrawFurniture();
		break;
	case STAGE_RESULT:
		DrawFurniture();
		break;
	}
}

