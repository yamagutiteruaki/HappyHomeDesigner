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

// �����S�����ŕK�v�ȃC���N���[�h
#include "title.h"
#include "titlelogo.h"
#include "weight.h"
#include "voice.h"
#include "arrest.h"
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
	InitWeight(0);
	InitVoice(0);
	InitArrest(0);
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
		UpdateWeight();
		UpdateVoice();
		UpdateArrest();
		break;
	case STAGE_RESULT:

		break;
	}

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawWorkMatsuo(void)
{
	switch (GetStage())
	{
	case STAGE_TITLE:
		DrawTitlelogo();
		break;
	case STAGE_GAME:
		DrawWeight();
		DrawVoice();
		DrawArrest();
		break;
	case STAGE_RESULT:
		break;
	}
}

