//=============================================================================
//
// �Q�[������ [result.cpp]
// Author : GP12B295 29 �R���P��
//
//=============================================================================
#include "result.h"
#include "stage.h"
#include "input.h"
#include "fade.h"

// �Q�[���ŕK�v�ȃC���N���[�h


// �S�����[�N
#include "workChisaka.h"
#include "workMatsuo.h"
#include "workSon.h"
#include "workImagawa.h"
#include "workSekiguchi.h"
#include "workYamaguchi.h"

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
HRESULT InitResult(int nType)
{

	InitWorkChisaka(0);
	InitWorkSon(0);
	InitWorkSekiguchi(0);
	InitWorkMatsuo(0);
	InitWorkImagawa(0);
	InitWorkYamaguchi(0);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitResult(void)
{
	UninitWorkChisaka();
	UninitWorkSon();
	UninitWorkSekiguchi();
	UninitWorkMatsuo();
	UninitWorkImagawa();
	UninitWorkYamaguchi();

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateResult(void)
{

	UpdateWorkChisaka();
	UpdateWorkSon();
	UpdateWorkSekiguchi();
	UpdateWorkMatsuo();
	UpdateWorkImagawa();
	UpdateWorkYamaguchi();
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawResult(void)
{

	DrawWorkChisaka();
	DrawWorkSon();
	DrawWorkSekiguchi();
	DrawWorkMatsuo();
	DrawWorkImagawa();
	DrawWorkYamaguchi();
}

