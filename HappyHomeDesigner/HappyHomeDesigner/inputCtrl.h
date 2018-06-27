//=============================================================================
//
// �S�̓��͐��� [inputCtrl.h]
// Author : �v�F��
//
//=============================================================================
#ifndef _INPUTCTRL_H_
#define _INPUTCTRL_H_

#include "main.h"

//*****************************************************************************
// �񋓌^
//*****************************************************************************
enum
{
	INPUT_KEY = 0,
	INPUT_GAMEPAD,

	INPUT_MAX,
};

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct
{
	int UP;
	int DOWN;
	int LEFT;
	int RIGHT;

	int UP_POV;
	int DOWN_POV;
	int LEFT_POV;
	int RIGHT_POV;

	int CAMERA_LEFT;
	int CAMERA_RIGHT;
	int CAMERA_RESET;

	int CAMERA_ZOOMIN;
	int CAMERA_ZOOMOUT;

	int DECIDE;
	int CANCEL;

	int TAKE;
	int PUT;

	int PAUSE;

} INPUTDEVICE;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitInputDevice(void);
void UpdateInputCtrl(void);
INPUTDEVICE *GetInputDevice(int id);

#endif