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

// ���S�����ŕK�v�ȃC���N���[�h
#include "police.h"
#include "search.h"
#include "furniture.h"
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
		break;
	case STAGE_HOUSE1:
	case STAGE_HOUSE2:
	case STAGE_HOUSE3:
	case STAGE_MYHOUSE:
		UpdateFurniture();
		break;
	case STAGE_RESULT:
		break;
	}

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawWorkChisaka(void)
{
	switch (GetStage())
	{
	case STAGE_TITLE:
		break;
	case STAGE_GAME:
		DrawPolice();
		DrawSearch();
		DrawFurniture();
		break;
	case STAGE_HOUSE1:
	case STAGE_HOUSE2:
	case STAGE_HOUSE3:
	case STAGE_MYHOUSE:
		DrawFurniture();
		break;
	case STAGE_RESULT:
		break;
	}
}

