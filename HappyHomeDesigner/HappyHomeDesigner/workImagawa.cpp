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

// ����S�����ŕK�v�ȃC���N���[�h
#include "field.h"
#include "wall.h"
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
	InitField();
	InitWall();
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitWorkImagawa(void)
{
	UninitField();
	UninitWall();
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
		break;
	case STAGE_RESULT:
		break;
	}

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawWorkImagawa(void)
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
		DrawField();
		DrawWall();
		break;
	case STAGE_RESULT:
		break;
	}
}

