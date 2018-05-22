//=============================================================================
//
// �v�S���� [workSon.cpp]
// Author GP12B295 29 �R���P��
// �e�X�g�e�X�g�e�X�g�e�X�g�e�X�g�e�X�g�e�X�g�e�X�g�e�X�g�e�X�g�e�X�g�e�X�g�e�X�g�e�X�g�e�X�g�e�X�g�e�X�g�e�X�g�e�X�g�e�X�g�e�X�g�e�X�g�e�X�g
//
//=============================================================================
#include "workSon.h"
#include "stage.h"
#include "input.h"
#include "fade.h"
#include "Light.h"

#include "player.h"

// �v�S�����ŕK�v�ȃC���N���[�h

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
HRESULT InitWorkSon(int nType)
{
	InitPlayer(nType);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitWorkSon(void)
{
	UninitPlayer();

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateWorkSon(void)
{
	switch (GetStage())
	{
	case STAGE_TITLE:
		break;
	case STAGE_GAME:
	case STAGE_HOUSE1:
	case STAGE_HOUSE2:
	case STAGE_HOUSE3:
	case STAGE_HOUSE4:
		UpdatePlayer();
		break;
	case STAGE_RESULT:
		break;
	}

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawWorkSon(void)
{
	switch (GetStage())
	{
	case STAGE_TITLE:
		break;
	case STAGE_GAME:
	case STAGE_HOUSE1:
	case STAGE_HOUSE2:
	case STAGE_HOUSE3:
	case STAGE_HOUSE4:
		DrawPlayer();
		break;
	case STAGE_RESULT:
		break;
	}
}

