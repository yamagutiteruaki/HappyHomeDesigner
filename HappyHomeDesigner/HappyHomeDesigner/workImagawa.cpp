//=============================================================================
//
// ����S���� [workImagawa.cpp]
// Author GP12B295 29 �R���P��
//
//=============================================================================
#include "workImagawa.h"
#include "stage.h"
#include "input.h"
#include "fade.h"
#include "game.h"


// ����S�����ŕK�v�ȃC���N���[�h
#include "field.h"
#include "wall.h"
#include "home.h"
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
HRESULT InitWorkImagawa(int nType)
{
	InitField(nType);
	InitWall(nType);
	InitHome(nType);
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitWorkImagawa(void)
{
	UninitField();
	UninitWall();
	UninitHome();
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateWorkImagawa(void)
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
		UpdateField();
		UpdateWall();
		UpdateHome();
		break;
	case STAGE_RESULT:
		break;
	}

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawWorkImagawa(int no)
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

		if (no==GAME_FIELD)		DrawField();
		if (no == GAME_WALL)	DrawWall();
		if (no == GAME_HOME)	DrawHome();
		break;
	case STAGE_RESULT:
		break;
	}
}

