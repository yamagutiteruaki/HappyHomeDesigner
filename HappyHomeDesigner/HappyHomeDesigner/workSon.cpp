//=============================================================================
//
// �v�S���� [workSon.cpp]
// Author GP12B295 29 �R���P��
// �e�X�g�e�X�g�e�X�g�e�X�g�e�X�g�e�X�g�e�X�g�e�X�g�e�X�g�e�X�g�e�X�g�e�X�g�e�X�g�e�X�g�e�X�g�e�X�g�e�X�g�e�X�g�e�X�g�e�X�g�e�X�g�e�X�g�e�X�g
//
//=============================================================================
#include "workSon.h"
#include "stage.h"
#include "game.h"

// �v�S�����ŕK�v�ȃC���N���[�h

#include "player.h"
#include "wwwwwwww.h"
#include "inputCtrl.h"

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
	InitWWWW(nType);
	InitInputDevice();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitWorkSon(void)
{
	UninitPlayer();
	UninitWWWW();

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
		UpdatePlayer();
		UpdateWWWW();
		break;
	case STAGE_HOUSE1:
	case STAGE_HOUSE2:
	case STAGE_HOUSE3:
	case STAGE_MYHOUSE:
		UpdatePlayer();
		break;
	case STAGE_RESULT:
		break;
	}

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawWorkSon(int no)
{
	switch (GetStage())
	{
	case STAGE_TITLE:
		break;
	case STAGE_GAME:
		if (no == GAME_PLAYER)	DrawPlayer();
		if (no == GAME_WWWW)	DrawWWWW();
		break;
	case STAGE_HOUSE1:
	case STAGE_HOUSE2:
	case STAGE_HOUSE3:
	case STAGE_MYHOUSE:
		if (no == GAME_PLAYER)	DrawPlayer();
		break;
	case STAGE_RESULT:
		break;
	}
}

