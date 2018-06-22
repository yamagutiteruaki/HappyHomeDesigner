//=============================================================================
//
// �X�e�[�W�J�ڏ��� [stage.h]
// Author : GP12B295 29 �R���P��
//
// �^�C�g���E�Q�[���E���U���g�̑J�ڊǗ�
//
//=============================================================================
#ifndef _STAGE_H_
#define _STAGE_H_

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define START_STAGE		(STAGE_TITLE)	// �J�n���̃X�e�[�W
#define STR(var) #var					// �����ɂ����ϐ���ϐ��������������񃊃e�����Ƃ��ĕԂ��}�N���֐�
#define START_PRICE		((long long)0)				//�������z
#define MAX_PRICE		((long long)99999999999)	//�ő���z�@score.h��NUM_PLACE�ƌ��������킹�邱��
/*******************************************************************************
* �\���̒�`
*******************************************************************************/

/*******************************************************************************
* �񋓌^��`
*******************************************************************************/
enum
{	// �X�e�[�W
	STAGE_TITLE,		//�^�C�g��
	STAGE_GAME,			//�Q�[��
	STAGE_GAME_END,		//�Q�[���I�������o
	STAGE_RESULT,		//���U���g
	STAGE_HOUSE1,		//��1
	STAGE_HOUSE2,		//��2
	STAGE_HOUSE3,		//��3
	STAGE_MYHOUSE,		//��4
	STAGE_MAX
};

enum
{
	STAGE_INIT_FAST,
	STAGE_INIT_LOOP
};

enum
{
	GAME_CLEAR,
	GAME_OVER
};
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT		InitStage(HINSTANCE hInstance, HWND hWnd);
HRESULT		InitStageEach(int nType);
void		UninitStage(void);
void		UpdateStage(void);
void		DrawStage(void);

void		SetStage(int nStage);
int			GetStage(void);
long long	GetPrice(void);
void		AddPrice(long long price);
void		SetGameEnd(int no);
int			GetGameEnd(void);

#endif