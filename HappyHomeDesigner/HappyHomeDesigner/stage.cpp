//=============================================================================
//
// �X�e�[�W�J�ڏ��� [stage.cpp]
// Author : GP12B295 29 �R���P��
//
// �^�C�g���E�Q�[���E���U���g�̑J�ڊǗ�
//
//=============================================================================
#include "main.h"
#include "stage.h"

/* Stage */
#include "game.h"

/* Camera */
#include "camera.h"

/* System */
#include "input.h"
#include "light.h"
#include "fade.h"
#include "sound.h"

/* Work */
#include "workChisaka.h"
#include "workMatsuo.h"
#include "workSon.h"
#include "workImagawa.h"
#include "workSekiguchi.h"
#include "workYamaguchi.h"

/* Debug */
#ifdef _DEBUG
#include "debugproc.h"
#endif

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
int					g_nStage;				// �����X�e�[�W
int					g_nPlayerWin;			// �����v���C���[

#ifdef _DEBUG
bool				g_bDispDebug = true;	// �f�o�b�O�\��ON/OFF
#endif

//=============================================================================
// ����������
//=============================================================================
HRESULT InitStage(HINSTANCE hInstance, HWND hWnd)
{
	// �O���[�o���ϐ��̏�����
	g_nStage = START_STAGE;			// �����X�e�[�W��ݒ�
	g_nPlayerWin = STAGE_WIN_NON;	// �����v���C���[��������

	InitInput(hInstance, hWnd);		// ����
	InitSound(hWnd);				// �T�E���h
	InitLight();					// ���C�g
	InitFade();						// �t�F�[�h
	InitStageEach(STAGE_INIT_FAST);	// �e�X�e�[�W�̏�����

#ifdef _DEBUG
	InitDebugProc();				// �f�o�b�O�\�������̏�����
#endif
	return S_OK;
}

//=============================================================================
// �ď���������
//=============================================================================
HRESULT InitStageEach(int nType)
{
	InitCamera();				// �J����
	InitGame(nType);			// �Q�[��
	InitWorkChisaka(nType);
	InitWorkSon(nType);
	InitWorkSekiguchi(nType);
	InitWorkMatsuo(nType);
	InitWorkImagawa(nType);
	InitWorkYamaguchi(nType);


	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitStage(void)
{
	UninitCamera();					// �J����
	UninitInput();					// ����
	UninitSound();					// �T�E���h
	UninitFade();					// �t�F�[�h
	UninitGame();					// �Q�[��


#ifdef _DEBUG
	UninitDebugProc();				// �f�o�b�O�\�������̏I������
#endif
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateStage(void)
{
#ifdef _DEBUG
	if (GetKeyboardTrigger(DIK_F1))
	{	// �f�o�b�O�\��ON/OFF
		g_bDispDebug = g_bDispDebug ? false : true;
	}
	UpdateDebugProc();				// �f�o�b�O

	PrintDebugProc("�y STAGE �z\n");
	switch (g_nStage)
	{
	case STAGE_TITLE:
		PrintDebugProc("%s (%d)\n", STR(STAGE_TITLE), g_nStage);
		if (GetKeyboardTrigger(DIK_RETURN))
		{
			SetFade(FADE_OUT, STAGE_GAME);
		}

		break;
	case STAGE_GAME:
		PrintDebugProc("%s (%d)\n", STR(STAGE_GAME), g_nStage);
		if (GetKeyboardTrigger(DIK_RETURN))
		{
			SetFade(FADE_OUT, STAGE_RESULT);
		}

		break;
	case STAGE_RESULT:
		PrintDebugProc("%s (%d)\n", STR(STAGE_RESULT), g_nStage);
		if (GetKeyboardTrigger(DIK_RETURN))
		{
			SetFade(FADE_OUT, STAGE_TITLE);
		}

		break;
	}
	PrintDebugProc("\n");
	// SE�e�X�g�isound.h��include���Ċ֐����Ăԁj
	if (GetKeyboardTrigger(DIK_1))
	{	// �^�C�g���E���U���g��ʂ̌���{�^��
		SetSe(SE_BUTTON, E_DS8_FLAG_NONE, CONTINUITY_ON);
	}
	if (GetKeyboardTrigger(DIK_2))
	{	// �o���b�g���ˉ�
		SetSe(SE_BULLET, E_DS8_FLAG_NONE, CONTINUITY_ON);
	}
	if (GetKeyboardTrigger(DIK_3))
	{	// �Q�[�W������Ȃ��Ƃ���MISS��
		SetSe(SE_MISS, E_DS8_FLAG_NONE, CONTINUITY_ON);
	}
	if (GetKeyboardTrigger(DIK_4))
	{	// �G�l�~�[�ƏՓˎ��̔�����
		SetSe(SE_BOMB, E_DS8_FLAG_NONE, CONTINUITY_ON);
	}
	if (GetKeyboardTrigger(DIK_5))
	{	// �A�C�e���擾��
		SetSe(SE_ITEM, E_DS8_FLAG_NONE, CONTINUITY_ON);
	}
#endif

	UpdateInput();					// ����
	UpdateSound();					// �T�E���h

	// �X�e�[�W�ɉ������X�V����
	switch (g_nStage)
	{
	case STAGE_TITLE:
		SetSoundBgm(STAGE_TITLE);
		break;
	case STAGE_GAME:
		UpdateGame();				// �Q�[��
		SetSoundBgm(STAGE_GAME);
		break;
	case STAGE_RESULT:
		SetSoundBgm(STAGE_RESULT);
		break;
	}
	UpdateCamera();					// �J����
	UpdateFade();					// �t�F�[�h
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawStage(void)
{
	SetCamera();					// �J�����̐ݒ菈��

									// �X�e�[�W�ɉ������`�揈��
	switch (g_nStage)
	{
	case STAGE_TITLE:
		break;
	case STAGE_GAME:
		DrawGame();					// �Q�[��
		break;
	case STAGE_RESULT:
		break;
	}

	DrawFade();						// �t�F�[�h

#ifdef _DEBUG
	if (g_bDispDebug)
	{	// �f�o�b�O�\������ꍇ
		DrawDebugProc();			// �f�o�b�O
	}
#endif
}

//=============================================================================
// �X�e�[�W�ݒ�֐�
//=============================================================================
void SetStage(int nStage)
{
	g_nStage = nStage;
}

//=============================================================================
// �X�e�[�W�擾�֐�
//=============================================================================
int GetStage(void)
{
	return (g_nStage);
}

//=============================================================================
// �����v���C���[�ݒ�֐�
//=============================================================================
void SetStageWinPlayer(int nPlayer)
{
	g_nPlayerWin = nPlayer;
}

//=============================================================================
// �����v���C���[�擾�֐�
//=============================================================================
int GetStageWinPlayer(void)
{
	return (g_nPlayerWin);
}