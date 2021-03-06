//=============================================================================
//
// SΜόΝ§δ [inputCtrl.h]
// Author : vFθΑ
//
//=============================================================================
#ifndef _INPUTCTRL_H_
#define _INPUTCTRL_H_

#include "main.h"

//*****************************************************************************
// ρ^
//*****************************************************************************
enum
{
	INPUT_KEY = 0,
	INPUT_GAMEPAD,

	INPUT_MAX,
};

//*****************************************************************************
// \’Μθ`
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

	int NEXTDOOR;

	int TAKE;
	int PUT;

	int PAUSE;

} INPUTDEVICE;

//*****************************************************************************
// vg^CvιΎ
//*****************************************************************************
void InitInputDevice(void);
void UpdateInputCtrl(void);
INPUTDEVICE *GetInputDevice(int id);

#endif